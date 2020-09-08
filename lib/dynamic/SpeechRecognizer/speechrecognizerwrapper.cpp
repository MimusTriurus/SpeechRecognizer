#include "speechrecognizerwrapper.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace {

constexpr int BUFFER_SIZE{ 2048 };
const string  YES{ "yes" };
const string  KWS_THRESHOLD{ "-kws_threshold" };
const string  KEYPHRASE_SEARCH{ "keyphrase_search" };

const arg_t cont_args_def[] = {
    POCKETSPHINX_OPTIONS,
    { "-argfile",
        ARG_STRING,
        NULL,
        "Argument file giving extra arguments." },
    { "-adcdev",
        ARG_STRING,
        NULL,
        "Name of audio device to use for input." },
    { "-infile",
        ARG_STRING,
        NULL,
        "Audio file to transcribe." },
    { "-inmic",
        ARG_BOOLEAN,
        "no",
        "Transcribe audio from microphone." },
    { "-time",
        ARG_BOOLEAN,
        "no",
        "Print word times in file transcription." },
    CMDLN_EMPTY_OPTION
};

}

namespace SpeechRecognizer {
// параметры по умолчанию для speech recognizer

void SpeechRecognizerWrapper::eventRecognitionResult ( const char *value ) {
    if ( recognitionResult != nullptr )
        ( *recognitionResult ) ( value );
}

void SpeechRecognizerWrapper::eventCrashMessage ( const char *value ) {
    if ( crashMessage != nullptr )
        ( *crashMessage ) ( value );
}

void SpeechRecognizerWrapper::eventLogMessage ( const char *value ) {
    if ( logMessage != nullptr )
        ( *logMessage ) ( value );
}

void SpeechRecognizerWrapper::recognizeFromMicrophone ( ) {
    if ( ( _ad = ad_open_dev ( cmd_ln_str_r ( _config, "-adcdev" ), (int)cmd_ln_float32_r ( _config, "-samprate" ) ) ) == nullptr ) {
        auto crashTxt = "Audio device:  " + string ( cmd_ln_str_r ( _config, "-adcdev" ) ) + " not found!";
        eventCrashMessage ( crashTxt.data ( ) );
        return;
    }
    if ( ad_start_rec ( _ad ) < 0 ) {
        eventCrashMessage ( "Failed to start recording" );
        return;
    }
    if ( ps_start_utt ( _ps ) < 0 ) {
        eventCrashMessage ( "Failed to start utt" );
        return;
    }
    _utt_started = FALSE;
    eventLogMessage ( "Ready..." );
}

bool SpeechRecognizerWrapper::checkAcousticModelFiles ( const char *assetsFilePath ) {
    auto fname = assetsFilePath + ASSEST_FILE_NAME;
    auto fs = ifstream ( fname );
    // если файла со списком файлов акустической модели не существует,
    // то предоставяем библиотеке возможность самой проверять наличие соответствующих файлов
    if ( !fs ) {
        eventLogMessage ( "File 'assets.lst' not found. Don't worry." );
        return true;
    }
    if ( !fs.is_open ( ) ) {
        eventCrashMessage ( "Can't open assets.lst file" );
        return false;
    }
    std::string assetFileName;
    while ( std::getline ( fs, assetFileName ) ) {
        auto path = string ( assetsFilePath + assetFileName );
        auto assetFile = ifstream ( fname );
        if ( !assetFile ) {
            eventCrashMessage ( string ( "Acoustic model. File " + path + " not found!" ).data ( ) );
            return false;
        }
    }
    return true;
}

void SpeechRecognizerWrapper::freeAllResources ( ) {
    if ( _ad != nullptr ) {
        ad_close ( _ad );
        _ad = nullptr;
    }
    if ( _ps != nullptr ) {
        ps_free ( _ps );
        _ps = nullptr;
    }
    if ( _config != nullptr ) {
        cmd_ln_free_r ( _config );
        _config = nullptr;
    }
}

SpeechRecognizerWrapper::SpeechRecognizerWrapper ( )
    : _ps{ nullptr }
    , _config{ nullptr }
    , _ad{ nullptr }
    , _utt_started{ FALSE }
    , _logIntoFile{ false }
    , _useKeyword{ false }
    , _threshold{ 1e+10f }
    , _vadThreshold{ 4.0 }
    , _baseGrammarName{ "" }
    , _inputDeviceName{ "sysdefault" }
    , ASSEST_FILE_NAME{ "assets.lst" } {
}

SpeechRecognizerWrapper::~SpeechRecognizerWrapper ( ) {
    logMessage = nullptr;
    recognitionResult = nullptr;
    crashMessage = nullptr;

    freeAllResources ( );
}

bool SpeechRecognizerWrapper::runRecognizerSetup ( const char *destination ) {
    auto hmmDest = string ( destination );
    _useKeyword = false;
    freeAllResources ( );

    if ( !checkAcousticModelFiles ( destination ) )
        return false;

    _config = cmd_ln_init ( nullptr, cont_args_def, TRUE,
        "-hmm", hmmDest.data ( ),
        "-remove_noise", YES.data ( ),
        "-inmic", YES.data ( ),
        "-vad_threshold", to_string ( _vadThreshold ).data( ),
        "-adcdev", _inputDeviceName.data ( ),
        "-remove_silence", YES.data ( ),
        nullptr );

    if ( _logIntoFile ) {
        auto logDest = string ( destination );
        logDest.append ( ".log" );
        cmd_ln_set_str_r ( _config, "-logfn", logDest.data ( ) );
    }

    char const *cfg;

    if ( _config && ( cfg = cmd_ln_str_r ( _config, "-argfile" ) ) != nullptr )
        _config = cmd_ln_parse_file_r ( _config, cont_args_def, cfg, FALSE );

    delete cfg;

    _ps = ps_init ( _config );

    if ( _ps == nullptr ) {
        cmd_ln_free_r ( _config );
        eventCrashMessage ( "error on init speechRecognizer!!!" );
        return false;
    }
    return true;
}

void SpeechRecognizerWrapper::setBaseGrammar ( const char *grammarName ) {
    _baseGrammarName = grammarName;
}

void SpeechRecognizerWrapper::setKeyword ( const char *keyword ) {
    _useKeyword = true;
    ps_set_keyphrase ( _ps, KEYPHRASE_SEARCH.data ( ), keyword );
}

void SpeechRecognizerWrapper::setThreshold ( const double threshold ) {
    _threshold = threshold;
}

void SpeechRecognizerWrapper::setVadThreshold ( const double threshold ) {
    _vadThreshold = threshold;
}

void SpeechRecognizerWrapper::switchGrammar ( const char *grammarName ) {
    if ( _ps == nullptr )
        return;
    int result = ps_set_search ( _ps, grammarName );
    if ( result != 0 )
        eventCrashMessage ( string ( "error on switch search:" + string ( grammarName ) ).data ( ) );
    else
        eventLogMessage ( string ( "switch grammar:" + string ( grammarName ) ).data ( ) );
}

void SpeechRecognizerWrapper::setSearchKeyword ( ) {
    if ( _useKeyword )
        cmd_ln_set_float_r ( _config, KWS_THRESHOLD.data ( ), _threshold );
    if ( ( _ps != nullptr ) & ( _useKeyword ) )
        ps_set_search ( _ps, KEYPHRASE_SEARCH.data ( ) );
}

bool SpeechRecognizerWrapper::addGrammar ( const char *grammarName, const char *grammarFileName ) {
    if ( _ps == nullptr )
        return false;
    int result = ps_set_jsgf_file ( _ps, grammarName, grammarFileName );
    if ( result != 0 ) {
        eventCrashMessage ( string ( "error on add grammar file:" + string ( grammarFileName ) ).data ( ) );
        return false;
    } else { // инициализируем базовую грамматику по умолчанию первой успешно добавленной в декодер
        if ( _baseGrammarName == "" )
            _baseGrammarName = grammarName;
        return true;
    }
}

bool SpeechRecognizerWrapper::addGrammarString ( const char *grammarName, const char *grammarString ) {
    if ( _ps == nullptr )
        return false;
    int result = ps_set_jsgf_string ( _ps, grammarName, grammarString );

    if ( result != 0 ) {
        eventCrashMessage ( string ( "Error on add grammar string:" + string ( grammarString ) ).data ( ) );
        return false;
    } else { // инициализируем базовую грамматику по умолчанию первой успешно добавленной в декодер
        if ( _baseGrammarName == "" )
            _baseGrammarName = grammarName;
        return true;
    }
}

bool SpeechRecognizerWrapper::addWordIntoDictionary ( const char *word, const char *phones ) {
    if ( ps_lookup_word ( _ps, word ) == NULL ) {
        return ( ps_add_word ( _ps, word, phones, 1 ) >= 0 );
    } else {
        eventCrashMessage ( string ( "Error on add word into dictionary:" + string ( word ) + " with phones:" + string ( phones ) ).data ( ) );
        return false;
    }
}

void SpeechRecognizerWrapper::startListening ( ) {
    eventLogMessage ( "Start listening" );
    if ( _useKeyword ) {
        eventLogMessage ( "Set search keyword" );
        ps_set_search ( _ps, KEYPHRASE_SEARCH.data ( ) );
    } else {
        ps_set_search ( _ps, _baseGrammarName.data ( ) );
        eventLogMessage ( string ( "Set search:" + _baseGrammarName ).data ( ) );
    }
    recognizeFromMicrophone ( );
}

void SpeechRecognizerWrapper::stopListening ( ) {
    if ( _ad == nullptr )
        return;
    eventLogMessage ( "Stop listening" );
    ad_stop_rec ( _ad );
}

void SpeechRecognizerWrapper::readMicrophoneBuffer ( ) {
    if ( _ad == nullptr )
        return;
    int32 k;
    int16 buffer[ BUFFER_SIZE ];
    uint8 in_speech;

    if ( ( k = ad_read ( _ad, buffer, BUFFER_SIZE ) ) < 0 ) {
        eventCrashMessage ( "Failed to read audio" );
        return;
    }
    ps_process_raw ( _ps, buffer, k, FALSE, FALSE );

    in_speech = ps_get_in_speech ( _ps );
    if ( in_speech && !_utt_started ) {
        _utt_started = TRUE;
        //eventLogMessage("Listening...");
    }
    if ( !in_speech && _utt_started ) {
        ps_end_utt ( _ps );
        auto hyp = ps_get_hyp ( _ps, nullptr );
        if ( hyp != NULL ) {
            string h{ hyp };
            if ( !h.empty ( ) )
                eventRecognitionResult ( h.data ( ) );
        }
        if ( ps_start_utt ( _ps ) < 0 ) {
            eventCrashMessage ( "Failed to start utt" );
        }
        _utt_started = FALSE;
    }
}

void SpeechRecognizerWrapper::saveLogIntoFile ( bool value ) {
    _logIntoFile = value;
}

void SpeechRecognizerWrapper::setInputDeviceName ( const char *name ) {
    _inputDeviceName = name;
}

}
