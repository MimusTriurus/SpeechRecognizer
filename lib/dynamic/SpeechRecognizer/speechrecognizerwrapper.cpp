#include "speechrecognizerwrapper.h"

#include <QDate>

namespace SpeechRecognizer {
// параметры по умолчанию для speech recognizer
    static const arg_t cont_args_def[ ] = {
        POCKETSPHINX_OPTIONS,
        /* Argument file. */
        {"-argfile",
         ARG_STRING,
         NULL,
         "Argument file giving extra arguments."},
         {"-adcdev",
         ARG_STRING,
         NULL,
         "Name of audio device to use for input."},
         {"-infile",
         ARG_STRING,
         NULL,
         "Audio file to transcribe."},
         {"-inmic",
         ARG_BOOLEAN,
         "no",
         "Transcribe audio from microphone."},
         {"-time",
         ARG_BOOLEAN,
         "no",
         "Print word times in file transcription."},
         CMDLN_EMPTY_OPTION
    };

    static const char* KWS_THRESHOLD = "-kws_threshold";
    static const char* ADD_DICT_FILE = "-dict";
    static const char* KEYPHRASE_SEARCH = "keyphrase_search";

    void SpeechRecognizerWrapper::eventRecognitionResult( const char *value )
    {
        if ( recognitionResult != nullptr )
            ( *recognitionResult )( value );
    }

    void SpeechRecognizerWrapper::eventCrashMessage( const char *value )
    {
        if ( crashMessage != nullptr )
            ( *crashMessage )( value );
    }

    void SpeechRecognizerWrapper::eventLogMessage( const char *value )
    {
        if ( logMessage != nullptr )
            ( *logMessage )( value );
    }

    void SpeechRecognizerWrapper::recognizeFromMicrophone()
    {
        if ( ( _ad = ad_open_dev( cmd_ln_str_r( _config, "-adcdev" ), ( int ) cmd_ln_float32_r( _config, "-samprate" ) ) ) == nullptr ) {

            eventCrashMessage( "Audio device:  " + QString( cmd_ln_str_r( _config, "-adcdev" ) ).toUtf8( ) + " not found!" );
            return;
        }
        if ( ad_start_rec( _ad ) < 0 ) {
            eventCrashMessage( "Failed to start recording" );
            return;
        }

        if ( ps_start_utt( _ps ) < 0 ) {
            eventCrashMessage( "Failed to start utt" );
            return;
        }

        _utt_started = FALSE;
        eventLogMessage( "Ready..." );
    }

    SpeechRecognizerWrapper::SpeechRecognizerWrapper( )
    {

    }

    bool SpeechRecognizerWrapper::runRecognizerSetup( const char *destination )
    {
        QString hmmDest = destination;
        hmmDest.append( "acousticModels/16000" );
        hmmDest = QDir::toNativeSeparators( hmmDest );

        QString dictDest = destination;
        dictDest.append( "dictionaries/actualDictionary.dict" );
        dictDest = QDir::toNativeSeparators( dictDest );

        _grammarPath = destination;
        _grammarPath.append( "grammarFiles/" );
        _grammarPath = QDir::toNativeSeparators( _grammarPath );
        _config = cmd_ln_init( nullptr, cont_args_def, TRUE,
                "-hmm", hmmDest.toUtf8( ).data( ),
                "-remove_noise", "yes",
                "-inmic", "yes",
                "-adcdev", _inputDeviceName.toUtf8( ).data( ),
                nullptr );
        if ( QFile( dictDest ).exists( ) )
            cmd_ln_set_str_r( _config, ADD_DICT_FILE, dictDest.toUtf8( ).data( ) );
        else {
            eventLogMessage( "dict file " + dictDest.toUtf8( ) + " not found. Use method 'addWordIntoDictionary' to add words manualy" );
        }
        cmd_ln_set_float_r( _config, KWS_THRESHOLD, _threshold );
        if ( _logIntoFile ) {
            QString logDest = destination;
            logDest.append( QDate::currentDate(  ).toString( "dd_MM_yy" ) +  ".log" );
            logDest = QDir::toNativeSeparators( logDest );
            cmd_ln_set_str_r( _config, "-logfn", logDest.toUtf8( ).data( ) );
        }

        char const *cfg;

        if ( _config && ( cfg = cmd_ln_str_r( _config, "-argfile" ) ) != nullptr )
            _config = cmd_ln_parse_file_r( _config, cont_args_def, cfg, FALSE );

        _ps = ps_init( _config );

        if (_ps == nullptr ) {
            cmd_ln_free_r( _config );
            eventCrashMessage( "error on init speechRecognizer!!!" );
            return false;
        }
        return true;
    }

    void SpeechRecognizerWrapper::setBaseGrammar( const char *grammarName )
    {
        _baseGrammarName = grammarName;
    }

    void SpeechRecognizerWrapper::setKeyword(const char *keyword )
    {
        _useKeyword = true;
        ps_set_keyphrase( _ps, KEYPHRASE_SEARCH, keyword );
    }

    void SpeechRecognizerWrapper::setThreshold(const double threshold )
    {
        _threshold = threshold;
    }

    void SpeechRecognizerWrapper::switchGrammar( const char *grammarName )
    {
        if ( _ps == nullptr ) return;
        int result = ps_set_search( _ps, grammarName );
        if ( result != 0 )
            eventCrashMessage( "error on switch search:" + QString( grammarName ).toUtf8( ) );
        else
            eventLogMessage( "switch grammar:" + QString( grammarName ).toUtf8( ) );
    }

    void SpeechRecognizerWrapper::setSearchKeyword( )
    {
        if ( ( _ps != nullptr ) && ( _useKeyword ) )
            ps_set_search( _ps, KEYPHRASE_SEARCH );
    }

    bool SpeechRecognizerWrapper::addGrammar( const char *grammarName , const char *grammarFileName )
    {
        if ( _ps == nullptr ) return false;
        int result = ps_set_jsgf_file( _ps, grammarName, grammarFileName );
        if ( result != 0 ) {
            eventCrashMessage( "error on add grammar file:" + QString( grammarFileName ).toUtf8( ) );
            return false;
        }
        else {   // инициализируем базовую грамматику по умолчанию первой успешно добавленной в декодер
            if ( _baseGrammarName == "" )
                _baseGrammarName = grammarName;
            return true;
        }
    }

    bool SpeechRecognizerWrapper::addGrammarString( const char *grammarName , const char *grammarString )
    {
        if ( _ps == nullptr ) return false;
        int result = ps_set_jsgf_string( _ps, grammarName, grammarString );

        if ( result != 0 ) {
            eventCrashMessage( "Error on add grammar string:" + QString( grammarString ).toUtf8( ) );
            return false;
        }
        else {   // инициализируем базовую грамматику по умолчанию первой успешно добавленной в декодер
            if ( _baseGrammarName == "" )
                _baseGrammarName = grammarName;
            return true;
        }
    }

    bool SpeechRecognizerWrapper::addWordIntoDictionary( const char *word, const char *phones )
    {
        if ( ps_lookup_word( _ps, word ) == NULL) {
            return ( ps_add_word( _ps, word, phones, 1 ) >= 0);
        }
        else {
            eventCrashMessage( "Error on add word into dictionary:" + QString( word ).toUtf8( ) + " with phones:" + QString( phones ).toUtf8( ) );
            return false;
        }
    }

    void SpeechRecognizerWrapper::startListening( )
    {
        eventLogMessage( "Start listening" );
        if ( _useKeyword ) {
            eventLogMessage( "Set search keyword" );
            ps_set_search( _ps, KEYPHRASE_SEARCH );
        }
        else {
            ps_set_search( _ps, _baseGrammarName.toUtf8( ).data( ) );
            eventLogMessage( QString( "Set search:" + _baseGrammarName ).toUtf8( ) );
        }

        recognizeFromMicrophone( );
    }

    void SpeechRecognizerWrapper::stopListening( )
    {
        eventLogMessage( "Stop listening" );
        ad_stop_rec( _ad );
    }

    void SpeechRecognizerWrapper::readMicrophoneBuffer( )
    {
        if ( _ad == nullptr ) return;
        int32 k;
        int16 buffer[ 2048 ];
        uint8 in_speech;

        if ( ( k = ad_read( _ad, buffer, 2048 ) ) < 0 ) {
            eventCrashMessage( "Failed to read audio" );
            return;
        }
        ps_process_raw( _ps, buffer, k, FALSE, FALSE );

        in_speech = ps_get_in_speech( _ps );
        if ( in_speech && !_utt_started ) {
            _utt_started = TRUE;
            //eventLogMessage("Listening...");
        }
        if ( !in_speech && _utt_started ) {
            ps_end_utt( _ps );
            char const *hyp = ps_get_hyp( _ps, nullptr );
            if ( hyp != nullptr ) {
                eventRecognitionResult( hyp );
            }

            if ( ps_start_utt( _ps ) < 0) {
                eventCrashMessage( "Failed to start utt" );
            }
            _utt_started = FALSE;
        }
    }

    void SpeechRecognizerWrapper::saveLogIntoFile( bool value )
    {
       //eventLogMessage( "save log into file" );
       _logIntoFile = value;
    }

    void SpeechRecognizerWrapper::setInputDeviceName( const char* name )
    {
        _inputDeviceName = name;
    }
}
