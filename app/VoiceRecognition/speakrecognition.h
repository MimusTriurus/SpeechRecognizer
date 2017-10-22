#ifndef SPEAKRECOGNITION_H
#define SPEAKRECOGNITION_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "dictionary.h"
#include "grammar.h"
#include "languages.h"
#include "speechrecognizer.h"

class SpeakRecognition : public QObject
{
    Q_OBJECT
    QTimer _tmrReadMicBuffer;
    bool _init { false };
    const int INTERVAL { 100 };
    const QString MIC_PARAM_ID { "-adcdev" };
    SpeakRecognition( );
    void tryGetInputDeviceFromArg( );
public:
    static SpeakRecognition &instance( );
    bool init( const QString acousticModelPath );
    void addWord( const QString word, const QString phones );
    void addGrammarString( const QString grammarId, const QString grammarString );
signals:
    void recognitionResult( QString );
    void logMessRecived( QString );
    void crashMessRecieved( QString );
public slots:
    void startRecognition( );
    void stopRecognition( );
private slots:
    void onTimeout( );
    static void onRecieveResult( const char *hypothesis );
    static void onRecieveLogMess( const char *logMess );
    static void onRecieveCrashMess( const char *crashMess );
};

#endif // SPEAKRECOGNITION_H
