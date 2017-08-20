#include "speechrecognizerwrapper.h"

namespace SpeechRecognizerWrapperNamespace {

    void SpeechRecognizerWrapper::eventRecognitionResult(const char value[])
    {
        (*recognitionResult)(value);
    }

    void SpeechRecognizerWrapper::eventInitResult(const char value[])
    {
        (*initResult)(value);
    }

    void SpeechRecognizerWrapper::eventRecognitionPartialResult(const char value[])
    {
        (*recognitionPartialResult)(value);
    }

    void SpeechRecognizerWrapper::eventLogMessage(QString value)
    {
        (*logMessage)(value.toUtf8().data());
    }

    void SpeechRecognizerWrapper::recognize_from_microphone()
    {
        qDebug( ) << "input device name:" << cmd_ln_str_r( _config, "-adcdev" );
        if ( ( _ad = ad_open_dev( cmd_ln_str_r( _config, "-adcdev" ), ( int ) cmd_ln_float32_r( _config, "-samprate" ) ) ) == NULL )
        {
            eventLogMessage("audio device not found!");
        }
        if (ad_start_rec(_ad) < 0)
        {
            eventLogMessage("Failed to start recording");
        }

        if (ps_start_utt(_ps) < 0)
        {
            eventLogMessage("Failed to start utt");
        }

        _utt_started = FALSE;
        eventLogMessage("Ready...");
    }

    SpeechRecognizerWrapper::SpeechRecognizerWrapper(QObject *parent) : QObject(parent)
    {

    }

    bool SpeechRecognizerWrapper::runRecognizerSetup(const char *destination)
    {
        QString hmmDest = destination;
        hmmDest.append("acousticModels/16000");
        hmmDest = QDir::toNativeSeparators(hmmDest);

        QString dictDest = destination;
        dictDest.append("dictionaries/actualDictionary.dict");
        dictDest = QDir::toNativeSeparators(dictDest);

        _grammarPath = destination;
        _grammarPath.append("grammarFiles/");
        _grammarPath = QDir::toNativeSeparators(_grammarPath);

        char const *cfg;

        _config = cmd_ln_init(NULL, cont_args_def, TRUE,
                "-hmm", hmmDest.toUtf8().data(),
                "-remove_noise", "yes",
                "-inmic", "yes",
                "-adcdev", _inputDeviceName,
                NULL);
        if (QFile(dictDest).exists())
            cmd_ln_set_str_r(_config, ADD_DICT_FILE, dictDest.toUtf8().data());
        else
        {
            eventLogMessage("dict file not found");
        }
        cmd_ln_set_float_r(_config, KWS_THRESHOLD, _threshold);
        if (_logIntoFile)
        {
            QString logDest = destination;
            logDest.append("log.txt");
            logDest = QDir::toNativeSeparators(logDest);
            cmd_ln_set_str_r(_config, "-logfn", logDest.toUtf8().data());
        }

        if (_config && (cfg = cmd_ln_str_r(_config, "-argfile")) != NULL)
            _config = cmd_ln_parse_file_r(_config, cont_args_def, cfg, FALSE);

        _ps = ps_init(_config);

        if (_ps == NULL) {
            cmd_ln_free_r(_config);
            eventInitResult("error on init speechRecognizer");
            return false;
        }
        eventInitResult(INIT_COMPLETE);
        return true;
    }

    void SpeechRecognizerWrapper::setBaseGrammar(const char *grammarName)
    {
        _baseGrammarName = grammarName;
    }

    void SpeechRecognizerWrapper::setKeyword(const char *pKeyword)
    {
        _useKeyword = true;
        ps_set_keyphrase(_ps, KEYPHRASE_SEARCH, pKeyword);
    }

    void SpeechRecognizerWrapper::setThreshold(double pThreshold)
    {
        _threshold = pThreshold;
    }

    void SpeechRecognizerWrapper::switchGrammar(const char *grammarName)
    {
        if (_ps == NULL) return;
        int result = ps_set_search(_ps, grammarName);
        if (result != 0)
            eventLogMessage("error on switch search");
        else
            eventLogMessage("switch grammar");
    }

    void SpeechRecognizerWrapper::setSearchKeyword()
    {
        if ((_ps != NULL) && (_useKeyword))
            ps_set_search(_ps, KEYPHRASE_SEARCH);
    }

    bool SpeechRecognizerWrapper::addGrammar(const char *grammar[])
    {
        QString key(grammar[0]);
        QString value(_grammarPath + grammar[1]);
        if (_ps == NULL) return false;
        int result = ps_set_jsgf_file(_ps, key.toUtf8().data(), value.toUtf8().data());
        if (result != 0)
        {
            eventLogMessage("error on add grammar file:" + value);
            return false;
        }
        else
        {   // инициализируем базовую грамматику поумолчанию первой успешно добавленной в декодер
            if (_baseGrammarName == "")
                _baseGrammarName = grammar[0];
            return true;
        }
    }

    bool SpeechRecognizerWrapper::addGrammarString(const char *grammar[])
    {
        QString key(grammar[0]);
        QString value(grammar[1]);
        if (_ps == NULL) return false;
        int result = ps_set_jsgf_string(_ps, key.toUtf8().data(), value.toUtf8().data());

        if (result != 0)
        {
            eventLogMessage("error on add grammar string:" + value.toUtf8());
            return false;
        }
        else
        {   // инициализируем базовую грамматику поумолчанию первой успешно добавленной в декодер
            if (_baseGrammarName == "")
                _baseGrammarName = grammar[0];
            return true;
        }
    }

    bool SpeechRecognizerWrapper::addWordIntoDictionary(const char *pWord, const char *pPhones)
    {
        QString word(pWord);
        if (ps_lookup_word( _ps, word.toUtf8( ).data( ) ) == NULL)
        {
            return ( ps_add_word( _ps, word.toUtf8( ).data( ), pPhones, 1 ) >= 0);
        }
        else
        {
            eventLogMessage("error on word");
            return false;
        }
    }

    void SpeechRecognizerWrapper::startListening()
    {
        eventLogMessage("start listening");
        if (_useKeyword) {
            ps_set_search(_ps, KEYPHRASE_SEARCH);
        }
        else {
            ps_set_search(_ps, _baseGrammarName.toUtf8().data());
            eventLogMessage("setSearch:" + _baseGrammarName);
        }

        recognize_from_microphone();
    }

    void SpeechRecognizerWrapper::stopListening()
    {
        eventLogMessage("stop listening");
        ad_stop_rec(_ad);
    }

    void SpeechRecognizerWrapper::readMicrophoneBuffer()
    {
        if (_ad == NULL) return;
        setlocale(LC_ALL, "Russian");

        int32 k;
        int16 buffer[2048];
        uint8 in_speech;

        if ((k = ad_read(_ad, buffer, 2048)) < 0)
        {
            eventLogMessage("Failed to read audio");
            return;
        }
        ps_process_raw(_ps, buffer, k, FALSE, FALSE);

        in_speech = ps_get_in_speech(_ps);
        if (in_speech && !_utt_started) {
            _utt_started = TRUE;
            //eventLogMessage("Listening...");
        }
        if (!in_speech && _utt_started) {
            ps_end_utt(_ps);
            char const *hyp = ps_get_hyp(_ps, NULL );
            if (hyp != NULL)
            {
                char hypophesis[255];
                strcpy(hypophesis, hyp);
                eventRecognitionResult(hypophesis);
                fflush(stdout);
            }

            if (ps_start_utt(_ps) < 0)
            {
                eventLogMessage("Failed to start utt");
            }
            _utt_started = FALSE;
            //eventLogMessage("Ready...");
        }
    }

    void SpeechRecognizerWrapper::saveLogIntoFile(bool value)
    {
       eventLogMessage("save log into file");
       _logIntoFile = value;
    }

    void SpeechRecognizerWrapper::setInputDeviceName(QString name)
    {
        _inputDeviceName = name;
    }
}
