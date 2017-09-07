#ifndef SPEECHRECOGNIZER_H
#define SPEECHRECOGNIZER_H

#include <QtGlobal>

#if defined( Q_CC_MSVC )
#define FUNCTION_EXPORT __declspec( dllexport )
#else
#define FUNCTION_EXPORT
#endif
/**
 * @brief обертка - набор методов для работы с классом SpeechRecognizerWrapper
 * реализовано в виде набора методов для упрощения работы с библиотекой из под Unity 5 при помощи InteropServices
 */
namespace SpeechRecognizer {

    extern "C" {
        /**
        * @brief сохраняем лог с подробной информацией
        * о работе библиотеки распознвания
        * в файл или выводим в консоль
        * @param value в файл - true \ в консоль - false
        */
        FUNCTION_EXPORT void saveLogIntoFile( bool value = false );
        /**
         * @brief устанавливаем имя устройства ввода(микрофона)
         * @param name имя устройства ввода(микрофона)
         */
        FUNCTION_EXPORT void setInputDeviceName( const char *inputDeviceName );
        /**
         * @brief настройка распознавания голоса
         * @param destination путь к папке где содержится акустическая модель, словарь и грамматика
         */
        FUNCTION_EXPORT bool runRecognizerSetup( const char *destination );
        /**
         * @brief устанавливаем имя грамматики поумолчанию
         * @param grammarName имя грамматики
         */
        FUNCTION_EXPORT void setBaseGrammar( const char *grammarName );
        /**
         * @brief устанавливаем ключевое слово(OK GOOGLE!)
         * @param keyword ключевое слово
         */
        FUNCTION_EXPORT void setKeyword( const char *keyword );
        /**
         * @brief устанавливаем порог сабатывания для ключевого слова
         * @param threshold чем больше значение тем меньше ложных срабатываний
         */
        FUNCTION_EXPORT void setThreshold( double threshold );
        /**
         * @brief меняем грамматику (слова для распознавания)
         * @param grammarName имя грамматики
         */
        FUNCTION_EXPORT void changeGrammar( const char *grammarName );
        /**
         * @brief инициируем поиск ключевого слова (OK GOOGLE!)
         */
        FUNCTION_EXPORT void setSearchKeyword( );
        /**
         * @brief добавляем файл грамматики
         * @param grammarName идентификатор грамматики
         * @param grammarFileName имя файла грамматики
         * файл должен лежать в <destination>/grammarFiles/
         * где <destination> - параметр метода 'runRecognizerSetup'
         * @return результат добавления файла грамматики (удачно\нет)
         */
        FUNCTION_EXPORT bool addGrammarFile( const char *grammarName, const char *grammarFile );
        /**
         * @brief addGrammarString
         * @param grammarName идентификатор грамматики
         * @param grammarString формализованная строка с грамматикой
         * @return результат добавления строки с грамматикой (удачно\нет)
         */
        FUNCTION_EXPORT bool addGrammarString( const char *grammarName, const char *grammarString );
        /**
         * @brief добавляем слово в словарь
         * @param word слово
         * @param phones транскрипция слова
         * @return результат добавления - удачно\нет
         */
        FUNCTION_EXPORT bool addWordIntoDictionary( const char *word, const char *phones );
        /**
         * @brief слушаем микрофон
         */
        FUNCTION_EXPORT void startListeningMic( );
        /**
         * @brief окончание прослушки микрофона
         */
        FUNCTION_EXPORT void stopListeningMic( );
        /**
         * @brief читаем буффер микрофона (с перерывом в 100 мс)
         * ... из потока Unity 5
         */
        FUNCTION_EXPORT void readMicBuffer( );
        /**
         * @brief передаем указатель на функцию-приемник результатов распознавания
         */
        FUNCTION_EXPORT void setResultReciever( void ( *func )( const char *value ) );
        /**
         * @brief передаем указатель на функцию-приемник сообщений об ошибках
         */
        FUNCTION_EXPORT void setCrashReciever( void ( *func )( const char *value ) );
        /**
         * @brief передаем указатель на функцию-приемник отладочных сообщений
         */
        FUNCTION_EXPORT void setLogMessReciever( void ( *func )( const char *value ) );
    }
}

#endif // SPEECHRECOGNIZER_H
