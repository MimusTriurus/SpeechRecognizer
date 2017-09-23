#include "speechrecognizer.h"

#include "speechrecognizerwrapper.h"

namespace SpeechRecognizer
{
    static SpeechRecognizerWrapper speechRecognizer;

    void SpeechRecognizer::setBaseGrammar( const char *grammarName ) {
        speechRecognizer.setBaseGrammar( grammarName );
    }

    void SpeechRecognizer::changeGrammar( const char *grammarName ) {
        speechRecognizer.switchGrammar( grammarName );
    }

    bool SpeechRecognizer::runRecognizerSetup( const char *destination ) {
        return speechRecognizer.runRecognizerSetup( destination );
    }

    void SpeechRecognizer::startListeningMic( ) {
        speechRecognizer.startListening( );
    }

    void SpeechRecognizer::stopListeningMic( ) {
        speechRecognizer.stopListening( );
    }

    void SpeechRecognizer::saveLogIntoFile( bool value ) {
        speechRecognizer.saveLogIntoFile( value );
    }

    bool SpeechRecognizer::addGrammarFile( const char *grammarName, const char *grammarFile ) {
        return speechRecognizer.addGrammar( grammarName, grammarFile );
    }

    void SpeechRecognizer::readMicBuffer( ) {
        speechRecognizer.readMicrophoneBuffer( );
    }

    void SpeechRecognizer::setKeyword( const char *keyword ) {
        speechRecognizer.setKeyword( keyword );
    }

    void SpeechRecognizer::setThreshold( double threshold ) {
        speechRecognizer.setThreshold( threshold );
    }

    void SpeechRecognizer::setSearchKeyword( ) {
        speechRecognizer.setSearchKeyword( );
    }

    bool SpeechRecognizer::addGrammarString( const char *grammarName, const char *grammarString ) {
        return speechRecognizer.addGrammarString( grammarName, grammarString );
    }

    bool SpeechRecognizer::addWordIntoDictionary( const char *word, const char *phones ) {
        return speechRecognizer.addWordIntoDictionary( word, phones );
    }

    void setInputDeviceName( const char *inputDeviceName ) {
        speechRecognizer.setInputDeviceName( inputDeviceName );
    }

    void setResultReciever( void ( *func )( const char * ) ) {
        speechRecognizer.recognitionResult = func;
    }

    void setCrashReciever( void ( *func )( const char * ) ) {
        speechRecognizer.crashMessage = func;
    }

    void setLogMessReciever( void ( *func )( const char * ) ) {
        speechRecognizer.logMessage = func;
    }

}
