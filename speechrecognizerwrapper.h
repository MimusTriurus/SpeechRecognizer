#ifndef SPEECHRECOGNIZERWRAPPER_H
#define SPEECHRECOGNIZERWRAPPER_H

#include <cctype>
#include <err.h>
#include <ad.h>
#include <pocketsphinx.h>

#include <string>

namespace SpeechRecognizer {

class SpeechRecognizerWrapper {

public:
    SpeechRecognizerWrapper( );
    ~SpeechRecognizerWrapper( );

    bool runRecognizerSetup( const char *destination );

    void setBaseGrammar( const char *grammarName );

    void setKeyword( const char *keyword );

    void setThreshold ( double threshold );

    void setVadThreshold ( double threshold );

    bool switchGrammar( const char *grammarName );

    bool setSearchKeyword( );

    bool addGrammar( const char* grammarName, const char *grammarFileName );

    bool addGrammarString( const char *grammarName, const char *grammarString );

    bool addWordIntoDictionary(const char *word, const char *phones );

    bool startListening( );

    bool stopListening( );

    bool readMicrophoneBuffer( unsigned char *data, int length );

    void *getRecognitionResult( );

    void saveLogIntoFile( bool value = false );

    void printLog( bool value );

private:
    ps_decoder_t *_ps;
    cmd_ln_t *_config;
    uint8 _utt_started;

    bool _logIntoFile;
    bool _printLog;
    bool _useKeyword;

    double _threshold;
    double _vadThreshold;

    std::string _baseGrammarName;
    std::string _inputDeviceName;

    const std::string ASSETS_FILE_NAME;

    void eventRecognitionResult( const char* value ) const;

    void eventCrashMessage( const char* value ) const;

    void eventLogMessage( const char* value ) const;

    bool recognizeFromMicrophone( );

    bool checkAcousticModelFiles( const char* assetsFilePath );

    void freeAllResources( );

    std::string _recognitionResult;
};

}

#endif // SPEECHRECOGNIZERWRAPPER_H
