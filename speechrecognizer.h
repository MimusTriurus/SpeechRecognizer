#ifndef SPEECHRECOGNIZER_H
#define SPEECHRECOGNIZER_H

#if defined( _WIN32 )
#define FUNCTION_EXPORT __declspec( dllexport )
#else
#define FUNCTION_EXPORT
#endif

namespace SpeechRecognizer {

    extern "C" {

    FUNCTION_EXPORT void *makeSR ( );

    FUNCTION_EXPORT void disposeSR ( void *ptr );

    FUNCTION_EXPORT void saveLogIntoFile ( void *ptr, bool value = false );

    FUNCTION_EXPORT void printLog ( void *ptr, bool value = false );

    FUNCTION_EXPORT bool runRecognizerSetup ( void *ptr, const char *destination );

    FUNCTION_EXPORT void setBaseGrammar ( void *ptr, const char *grammarName );

    FUNCTION_EXPORT void setKeyword ( void *ptr, const char *keyword );

    FUNCTION_EXPORT void setThreshold ( void *ptr, double threshold );

    FUNCTION_EXPORT void setVadThreshold ( void *ptr, double threshold );

    FUNCTION_EXPORT bool changeGrammar ( void *ptr, const char *grammarName );

    FUNCTION_EXPORT bool setSearchKeyword ( void *ptr );

    FUNCTION_EXPORT bool addGrammarFile ( void *ptr, const char *grammarName, const char *grammarFile );

    FUNCTION_EXPORT bool addGrammarString ( void *ptr, const char *grammarName, const char *grammarString );

    FUNCTION_EXPORT bool addWordIntoDictionary ( void *ptr, const char *word, const char *phones );

    FUNCTION_EXPORT bool startListeningMic ( void *ptr );

    FUNCTION_EXPORT bool stopListeningMic ( void *ptr );

    FUNCTION_EXPORT bool readMicBuffer ( void *ptr, unsigned char *data, int length);

    FUNCTION_EXPORT void *getRecognitionResult ( void *ptr );

    }

}

#endif // SPEECHRECOGNIZER_H
