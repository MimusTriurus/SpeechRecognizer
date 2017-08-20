#ifndef SPEECHRECOGNIZER_H
#define SPEECHRECOGNIZER_H

#include <QCoreApplication>
#include <QDir>
#include <QDebug>

#if defined(Q_CC_MSVC)
#define FUNCTION_EXPORT __declspec(dllexport)
#else
#define FUNCTION_EXPORT
#endif

#define _CRT_SECURE_NO_WARNINGS

namespace SpeechRecognizer {

    extern "C" {
        FUNCTION_EXPORT void saveLogIntoFile(bool value = false);

        FUNCTION_EXPORT void setInputDeviceName(const char *inputDeviceName);

        FUNCTION_EXPORT bool runRecognizerSetup(const char *destination);

        FUNCTION_EXPORT void setBaseGrammar(const char *grammarName);

        FUNCTION_EXPORT void setKeyword(const char *keyword);

        FUNCTION_EXPORT void setThreshold(double threshold);

        FUNCTION_EXPORT void changeGrammar(const char *grammarName);

        FUNCTION_EXPORT void setSearchKeyword();

        FUNCTION_EXPORT bool addGrammar(const char *grammar, const char *grammarFile);

        FUNCTION_EXPORT bool addGrammarString(const char *grammar, const char *grammarString);

        FUNCTION_EXPORT bool addWordIntoDictionary(const char *word, const char *phones);

        FUNCTION_EXPORT void startListeningMic();

        FUNCTION_EXPORT void stopListeningMic();

        FUNCTION_EXPORT void readMicBuffer();

        FUNCTION_EXPORT void setResultRecieverMethod(void *func);
        FUNCTION_EXPORT void setPartialResultRecieverMethod(void *func);
        FUNCTION_EXPORT void setMessagesFromLogRecieverMethod(void *func);
        FUNCTION_EXPORT void setInitResultMethod(void *func);

        typedef void (__stdcall * emitSignal)(const char value[]);
    }
}

#endif // SPEECHRECOGNIZER_H
