#include "speechrecognizer.h"

#include "speechrecognizerwrapper.h"

namespace SpeechRecognizer
{
    static SpeechRecognizerWrapper speechRecognizer;

    void setBaseGrammar( const char *grammarName ) {
        speechRecognizer.setBaseGrammar( grammarName );
    }

    void changeGrammar( const char *grammarName ) {
        speechRecognizer.switchGrammar( grammarName );
    }

    bool runRecognizerSetup( const char *destination ) {
        return speechRecognizer.runRecognizerSetup( destination );
    }

    void startListeningMic( ) {
        speechRecognizer.startListening( );
    }

    void stopListeningMic( ) {
        speechRecognizer.stopListening( );
    }

    void saveLogIntoFile( bool value ) {
        speechRecognizer.saveLogIntoFile( value );
    }

    bool addGrammarFile( const char *grammarName, const char *grammarFile ) {
        return speechRecognizer.addGrammar( grammarName, grammarFile );
    }

    void readMicBuffer( ) {
        speechRecognizer.readMicrophoneBuffer( );
    }

    void setKeyword( const char *keyword ) {
        speechRecognizer.setKeyword( keyword );
    }

    void setThreshold( double threshold ) {
        speechRecognizer.setThreshold( threshold );
    }

    void setSearchKeyword( ) {
        speechRecognizer.setSearchKeyword( );
    }

    bool addGrammarString( const char *grammarName, const char *grammarString ) {
        return speechRecognizer.addGrammarString( grammarName, grammarString );
    }

    bool addWordIntoDictionary( const char *word, const char *phones ) {
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
