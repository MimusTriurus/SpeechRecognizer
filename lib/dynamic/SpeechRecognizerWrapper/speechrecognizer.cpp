#include "speechrecognizer.h"

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

#include <QMap>
#include <QTimer>

#include "speechrecognizerwrapper.h"

using namespace SpeechRecognizerWrapperNamespace;

namespace SpeechRecognizer
{
    SpeechRecognizerWrapper *speechRecognizer = new SpeechRecognizerWrapper();

    void SpeechRecognizer::setResultRecieverMethod(void *func)
    {
        if (speechRecognizer != NULL)
        {
            speechRecognizer->recognitionResult = (void (*)(const char[]))func;
            speechRecognizer->eventLogMessage("setResultRecieverMethod");
        }
    }

    void SpeechRecognizer::setPartialResultRecieverMethod(void *func)
    {
        if (speechRecognizer != NULL)
        {
            speechRecognizer->recognitionPartialResult = (void (*)(const char[]))func;
            speechRecognizer->eventLogMessage("setPartialResultRecieverMethod");
        }
    }

    void SpeechRecognizer::setMessagesFromLogRecieverMethod(void *func)
    {
        if (speechRecognizer != NULL)
        {
            speechRecognizer->logMessage = (void (*)(const char[]))func;
            speechRecognizer->eventLogMessage("setMessagesFromLogRecieverMethod");
        }
    }

    void SpeechRecognizer::setInitResultMethod(void *func)
    {
        if (speechRecognizer != NULL)
        {
            speechRecognizer->initResult = (void (*)(const char[]))func;
            speechRecognizer->eventLogMessage("setInitResultMethod");
        }
    }
    void SpeechRecognizer::setBaseGrammar(const char *grammarName)
    {
        if (speechRecognizer != NULL)
            speechRecognizer->setBaseGrammar(grammarName);
    }

    void SpeechRecognizer::changeGrammar(const char *grammarName)
    {
        if (speechRecognizer != NULL)
            speechRecognizer->switchGrammar(grammarName);
    }

    bool SpeechRecognizer::runRecognizerSetup(const char *destination)
    {
        if (speechRecognizer != NULL)
            return speechRecognizer->runRecognizerSetup(destination);
        else
            return false;
    }

    void SpeechRecognizer::startListeningMic()
    {
        if (speechRecognizer != NULL)
            speechRecognizer->startListening();
    }

    void SpeechRecognizer::stopListeningMic()
    {
        if (speechRecognizer != NULL)
            speechRecognizer->stopListening();
    }

    void SpeechRecognizer::saveLogIntoFile(bool value)
    {
        if (speechRecognizer != NULL)
            speechRecognizer->saveLogIntoFile(value);
    }

    bool SpeechRecognizer::addGrammar(const char *grammar, const char *grammarFile)
    {
        const char *str[2];
        str[0] = grammar;
        str[1] = grammarFile;
        if (speechRecognizer != NULL)
            return speechRecognizer->addGrammar(str);
        else
            return false;
    }

    void SpeechRecognizer::readMicBuffer()
    {
        if (speechRecognizer != NULL)
            speechRecognizer->readMicrophoneBuffer();
    }

    void SpeechRecognizer::setKeyword(const char *keyword)
    {
        if (speechRecognizer != NULL)
            speechRecognizer->setKeyword(keyword);
    }

    void SpeechRecognizer::setThreshold(double threshold)
    {
        if (speechRecognizer != NULL)
        {
            speechRecognizer->setThreshold(threshold);
        }
    }

    void SpeechRecognizer::setSearchKeyword()
    {
        if (speechRecognizer != NULL)
        {
            speechRecognizer->setSearchKeyword();
        }
    }

    bool SpeechRecognizer::addGrammarString(const char *grammar, const char *grammarString)
    {
        const char *str[2];
        str[0] = grammar;
        str[1] = grammarString;
        qDebug() << "grammar string:" << str;
        if (speechRecognizer != NULL)
            return speechRecognizer->addGrammarString(str);
        else
            return false;
    }

    bool SpeechRecognizer::addWordIntoDictionary(const char *word, const char *phones)
    {
        if (speechRecognizer != NULL)
        {
            qDebug() << "try add word:" << word << " phones:" <<  phones;
            return speechRecognizer->addWordIntoDictionary(word, phones);
        }
        else
            return false;
    }

    void setInputDeviceName(const char *inputDeviceName)
    {

    }

}
