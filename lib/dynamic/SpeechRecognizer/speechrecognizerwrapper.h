#ifndef SPEECHRECOGNIZERWRAPPER_H
#define SPEECHRECOGNIZERWRAPPER_H

#include <err.h>
#include <ad.h>
#include <pocketsphinx.h>

#include <QDir>
#include <QDebug>

namespace SpeechRecognizer {
/**
 * @brief Обертка вокруг статических методов pocketsphinx.
 * Помимо базовых функций библиотеки pocketsphinx
 * обеспечивает формирование конфигурации для pocketsphinx, захват потока с микрофона и передачу его для распознавания,
 * уведомление объекта-пользователя о результатах инициализации и распознавания
 * посредством вызова его методов(через указатели)
 * @author mimus.triurus@yandex.ru
 * @version 1.0
 */
class SpeechRecognizerWrapper
    {
        ps_decoder_t *_ps;
        cmd_ln_t *_config;
        ad_rec_t *_ad;
        uint8 _utt_started;

        bool _logIntoFile = true;
        bool _useKeyword = false;

        double _threshold = 1e+10f;

        QString _baseGrammarName = "";
        QString _inputDeviceName = "";

        const QString ASSEST_FILE_NAME = "assets.lst";

        void eventRecognitionResult( const char* value );

        void eventCrashMessage( const char* value );

        void eventLogMessage( const char* value );

        void recognizeFromMicrophone( );

        bool checkAcousticModelFiles( const char* assetsFilePath );
    public:
        /**
         * @brief конструктор
         */
         SpeechRecognizerWrapper( );
        /**
         * @brief настройка распознавания голоса
         * @param destination путь к папке где содержится акустическая модель, словарь и грамматика
         */
        bool runRecognizerSetup( const char *destination );
        /**
         * @brief устанавливаем имя грамматики поумолчанию
         * @param grammarName имя грамматики
         */
        void setBaseGrammar( const char *grammarName );
        /**
         * @brief устанавливаем ключевое слово(OK GOOGLE!)
         * @param keyword ключевое слово
         */
        void setKeyword( const char *keyword );
        /**
         * @brief устанавливаем порог сабатывания для ключевого слова
         * @param threshold чем больше значение тем меньше ложных срабатываний
         */
        void setThreshold( const double threshold );
        /**
         * @brief меняем грамматику (слова для распознавания)
         * @param grammarName имя грамматики
         */
        void switchGrammar( const char *grammarName );
        /**
         * @brief инициируем поиск ключевого слова (OK GOOGLE!)
         */
        void setSearchKeyword( );
        /**
         * @brief добавляем файл грамматики
         * @param grammarName идентификатор грамматики
         * @param grammarFileName имя файла грамматики
         * файл должен лежать в <destination>/grammarFiles/
         * где <destination> - параметр метода 'runRecognizerSetup'
         * @return результат добавления файла грамматики (удачно\нет)
         */
        bool addGrammar( const char* grammarName, const char *grammarFileName );
        /**
         * @brief addGrammarString
         * @param grammarName идентификатор грамматики
         * @param grammarString формализованная строка с грамматикой
         * @return результат добавления строки с грамматикой (удачно\нет)
         */
        bool addGrammarString( const char *grammarName, const char *grammarString );
        /**
         * @brief добавляем слово в словарь
         * @param word слово
         * @param phones транскрипция слова
         * @return результат добавления - удачно\нет
         */
        bool addWordIntoDictionary(const char *word, const char *phones );
        /**
         * @brief слушаем микрофон
         */
        void startListening( );
        /**
         * @brief окончание прослушки микрофона
         */
        void stopListening( );
        /**
         * @brief читаем буффер микрофона (с перерывом в 100 мс)
         */
        void readMicrophoneBuffer( );
        /**
         * @brief сохраняем лог с подробной информацией
         * о работе библиотеки распознвания
         * в файл или выводим в консоль
         * @param value в файл - true \ в консоль - false
         */
        void saveLogIntoFile( bool value = false );
        /**
         * @brief устанавливаем имя устройства ввода(микрофона)
         * @param name имя устройства ввода(микрофона)
         */
        void setInputDeviceName( const char *name );
        /**
         * указатель на функцию-приемник результатов распознавания
         */
        void ( *recognitionResult )( const char *value );
        /**
         * указатель на функцию-приемник сообщений об ошибках
         */
        void ( *crashMessage )( const char *value );
        /**
         * указатель на функцию-приемник отладочных сообщений
         */
        void ( *logMessage )( const char *value );
    };
}

#endif // SPEECHRECOGNIZERWRAPPER_H
