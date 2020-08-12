#include "speechrecognizer.h"

#include "speechrecognizerwrapper.h"

namespace SpeechRecognizer {

void setBaseGrammar ( void *ptr, const char *grammarName ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->setBaseGrammar ( grammarName );
}

void changeGrammar ( void *ptr, const char *grammarName ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->switchGrammar ( grammarName );
}

bool runRecognizerSetup ( void *ptr, const char *destination ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    return sr->runRecognizerSetup ( destination );
}

void startListeningMic ( void *ptr ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->startListening ( );
}

void stopListeningMic ( void *ptr ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->stopListening ( );
}

void saveLogIntoFile ( void *ptr, bool value ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->saveLogIntoFile ( value );
}

bool addGrammarFile ( void *ptr, const char *grammarName, const char *grammarFile ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    return sr->addGrammar ( grammarName, grammarFile );
}

void readMicBuffer ( void *ptr ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->readMicrophoneBuffer ( );
}

void setKeyword ( void *ptr, const char *keyword ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->setKeyword ( keyword );
}

void setThreshold ( void *ptr, double threshold ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->setThreshold ( threshold );
}

void setSearchKeyword ( void *ptr ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->setSearchKeyword ( );
}

bool addGrammarString ( void *ptr, const char *grammarName, const char *grammarString ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    return sr->addGrammarString ( grammarName, grammarString );
}

bool addWordIntoDictionary ( void *ptr, const char *word, const char *phones ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    return sr->addWordIntoDictionary ( word, phones );
}

void setInputDeviceName ( void *ptr, const char *inputDeviceName ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->setInputDeviceName ( inputDeviceName );
}

void setResultReciever ( void *ptr, void ( *func ) ( const char * ) ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->recognitionResult = func;
}

void setCrashReciever ( void *ptr, void ( *func ) ( const char * ) ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->crashMessage = func;
}

void setLogMessReciever ( void *ptr, void ( *func ) ( const char * ) ) {
    auto sr = reinterpret_cast<SpeechRecognizerWrapper *> ( ptr );
    sr->logMessage = func;
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

}
