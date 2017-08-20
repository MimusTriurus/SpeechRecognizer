#ifndef SPEECHRECOGNIZERWRAPPER_H
#define SPEECHRECOGNIZERWRAPPER_H

using namespace std;

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include <err.h>
#include <ad.h>
#include <pocketsphinx.h>

#include <QDir>
#include <QDebug>

using namespace std;

namespace SpeechRecognizerWrapperNamespace {

    static const arg_t cont_args_def[] = {
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
    static const char* INIT_COMPLETE = "initComplete";

    class SpeechRecognizerWrapper : public QObject
    {
        Q_OBJECT
    private:
        ps_decoder_t *_ps;
        cmd_ln_t *_config;
        ad_rec_t *_ad;
        uint8 _utt_started;

        bool _logIntoFile = true;
        bool _useKeyword = false;

        double _threshold = 1e+10f;

        QString _baseGrammarName = "";
        QString _grammarPath = "";
        QString _inputDeviceName = "";

        void eventRecognitionResult(const char value[]);

        void eventInitResult(const char value[]);

        void eventRecognitionPartialResult(const char value[]);      

        void recognize_from_microphone();
    public:
        /**
         * @brief не используется
         * @param parent
         */
        explicit SpeechRecognizerWrapper(QObject *parent = 0);
        /**
         * @brief настройка распознавания голоса
         * @param destination путь к папке где содержится акустическая модель, словарь и грамматика
         */
        bool runRecognizerSetup(const char *destination);
        /**
         * @brief устанавливаем имя файла грамматики поумолчанию
         * @param grammarName имя файла грамматики
         * @return результат инициализации - удачно\нет
         */
        void setBaseGrammar(const char *grammarName);
        /**
         * @brief устанавливаем ключевое слово(OK GOOGLE)
         * @param pKeyword
         */
        void setKeyword(const char *pKeyword);
        /**
         * @brief устанавливаем порог сабатывания для ключевого слова
         * @param pThreshold чем больше значение тем меньше ложных срабатываний
         */
        void setThreshold(double pThreshold);
        /**
         * @brief меняем файл грамматики (слова для распознавания)
         * @param grammarName имя файла грамматики
         */
        void switchGrammar(const char *grammarName);
        /**
         * @brief инициируем поиск ключевого слова
         */
        void setSearchKeyword();
        /**
         * @brief добавляем файл грамматики
         * @param grammar массив из двух элементов [0] - имя грамматики [1] - имя файла грамматики (menu.gram)
         * @return результат добавления - удачно\нет
         */
        bool addGrammar(const char *grammar[]);
        /**
         * @brief добавляем грамматику в виде текста (а не файла)
         * @param grammar формализованная строка с грамматикой
         * @return результат добавления - удачно\нет
         */
        bool addGrammarString(const char *grammar[]);
        /**
         * @brief добавляем слово в словарь
         * @param pWord слово
         * @param pPhones транскрипция слова
         * @return результат добавления - удачно\нет
         */
        bool addWordIntoDictionary(const char *pWord, const char *pPhones);
        /**
         * @brief слушаем микрофон
         */
        void startListening();
        /**
         * @brief окончание прослушки микрофона
         */
        void stopListening();
        /**
         * @brief читаем буффер микрофона (с перерывом в 100 мс)
         */
        void readMicrophoneBuffer();
        /**
         * @brief сохраняем лог в файл или выводим в консоль
         * @param value в файл\в консоль
         */
        void saveLogIntoFile(bool value = false);
        /**
         * @brief устанавливаем имя устройства ввода(микрофона)
         * @param name имя устройства ввода(микрофона)
         */
        void setInputDeviceName( QString name );

        void (*recognitionResult)(const char value[]);
        void (*recognitionPartialResult)(const char value[]);
        void (*logMessage)(const char value[]);
        void (*initResult)(const char value[]);
        // переместить в private
        void eventLogMessage(QString value);
    };
}

#endif // SPEECHRECOGNIZERWRAPPER_H
