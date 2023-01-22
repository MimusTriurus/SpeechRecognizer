#include "speechrecognizer.h"

#include "speechrecognizerwrapper.h"

namespace SpeechRecognizer {

    void setBaseGrammar ( void *ptr, const char *grammarName ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        sr->setBaseGrammar ( grammarName );
    }

    bool changeGrammar ( void *ptr, const char *grammarName ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->switchGrammar ( grammarName );
    }

    bool runRecognizerSetup ( void *ptr, const char *destination ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->runRecognizerSetup ( destination );
    }

    bool startListeningMic ( void *ptr ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->startListening ( );
    }

    bool stopListeningMic ( void *ptr ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->stopListening ( );
    }

    void saveLogIntoFile ( void *ptr, bool value ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        sr->saveLogIntoFile ( value );
    }

    bool addGrammarFile ( void *ptr, const char *grammarName, const char *grammarFile ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->addGrammar ( grammarName, grammarFile );
    }

    bool readMicBuffer ( void *ptr, unsigned char *data, int length ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->readMicrophoneBuffer ( data, length );
    }

    void setKeyword ( void *ptr, const char *keyword ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        sr->setKeyword ( keyword );
    }

    void setThreshold ( void *ptr, double threshold ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        sr->setThreshold ( threshold );
    }

    bool setSearchKeyword ( void *ptr ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->setSearchKeyword ( );
    }

    bool addGrammarString ( void *ptr, const char *grammarName, const char *grammarString ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->addGrammarString ( grammarName, grammarString );
    }

    bool addWordIntoDictionary ( void *ptr, const char *word, const char *phones ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->addWordIntoDictionary ( word, phones );
    }

    void setVadThreshold ( void *ptr, double threshold ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        sr->setVadThreshold ( threshold );
    }

    void *makeSR ( ) {
        return new SpeechRecognizerWrapper ( );
    }

    void disposeSR ( void *ptr ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        sr->stopListening ( );
        delete sr;
    }

    void *getRecognitionResult(void *ptr) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->getRecognitionResult ( );
    }

    void printLog( void *ptr, bool value ) {
        auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
        return sr->printLog ( value );
    }

}
