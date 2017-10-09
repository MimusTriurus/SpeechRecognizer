#include "speakrecognition.h"

#include <QDebug>

SpeakRecognition::SpeakRecognition( ) {
    connect( &_tmrReadMicBuffer, SIGNAL( timeout( ) ), this, SLOT( onTimeout( ) ) );
    _tmrReadMicBuffer.setInterval( INTERVAL );

    SpeechRecognizer::setLogMessReciever( onRecieveLogMess );
    SpeechRecognizer::setCrashReciever( onRecieveCrashMess );
    SpeechRecognizer::setResultReciever( onRecieveResult );
    //SpeechRecognizer::setInputDeviceName( "hw:1,0" );
    SpeechRecognizer::saveLogIntoFile( true );
}

SpeakRecognition &SpeakRecognition::instance( ) {
    static SpeakRecognition instance;
    return instance;
}

bool SpeakRecognition::init( const QString acousticModelPath ) {
    _init = SpeechRecognizer::runRecognizerSetup( acousticModelPath.toUtf8( ) );
    return _init;
}

void SpeakRecognition::addWord( const QString word, const QString phones ) {
    if ( _init ) {
        _init = SpeechRecognizer::addWordIntoDictionary( word.toUtf8( ), phones.toUtf8( ) );
    }
}

void SpeakRecognition::addGrammarString( const QString grammarId, const QString grammarString ) {
    if ( _init ) {
        _init = SpeechRecognizer::addGrammarString( grammarId.toUtf8( ), grammarString.toUtf8( ) );
    }
}

void SpeakRecognition::startRecognition( ) {
    if ( _init ) {
        SpeechRecognizer::startListeningMic( );
        _tmrReadMicBuffer.start( );
    }
}

void SpeakRecognition::stopRecognition( ) {
    if ( _init ) {
        _tmrReadMicBuffer.stop( );
        SpeechRecognizer::stopListeningMic( );
    }
}

void SpeakRecognition::onTimeout( ) {
    if ( _init )
        SpeechRecognizer::readMicBuffer( );
}

void SpeakRecognition::onRecieveResult( const char *hypothesis ) {
    emit SpeakRecognition::instance( ).recognitionResult( hypothesis );
}

void SpeakRecognition::onRecieveLogMess( const char *logMess ) {
    emit SpeakRecognition::instance( ).logMessRecived( logMess );
}

void SpeakRecognition::onRecieveCrashMess( const char *crashMess ) {
    emit SpeakRecognition::instance( ).crashMessRecieved( crashMess );
}
