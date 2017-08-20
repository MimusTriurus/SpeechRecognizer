#include <QCoreApplication>

#include "speechrecognizer.h"
#include "iostream"
#include <Windows.h>
#include <QIODevice>
#include <QAudioDeviceInfo>

void onRecieveResult(const char hypothesis[])
{
    qDebug() << "result:" << hypothesis;
    QString hyp(hypothesis);
    if (hyp == "один")
        SpeechRecognizer::changeGrammar("menu");
    if (hyp == "два")
        SpeechRecognizer::setSearchKeyword();
}

void onRecievePartialResult(const char hypothesis[])
{
    qDebug() << "partial result:" << hypothesis;
}

void onInitResult(const char hypothesis[])
{
    qDebug() << "init:" << hypothesis;
}

void onRecieveLogMessage(const char hypothesis[])
{
    QString mess(hypothesis);
    qDebug() << "log:" << mess;
}

void addResultRecieverMethod(void)
{
    typedef void (*function_address)(const char[]);
    function_address var_function;
    var_function = onRecieveResult;
    SpeechRecognizer::setResultRecieverMethod(var_function);
}

void addPartialResultRecieverMethod(void)
{
    typedef void (*function_address)(const char[]);
    function_address var_function;
    var_function = onRecievePartialResult;
    SpeechRecognizer::setPartialResultRecieverMethod(var_function);
}

void addInitResultRecieverMethod(void)
{
    typedef void (*function_address)(const char[]);
    function_address var_function;
    var_function = onInitResult;
    SpeechRecognizer::setInitResultMethod(var_function);
}

void addLogRecieverMethod(void)
{
    typedef void (*function_address)(const char[]);
    function_address var_function;
    var_function = onRecieveLogMessage;
    SpeechRecognizer::setMessagesFromLogRecieverMethod(var_function);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    addLogRecieverMethod();
    addResultRecieverMethod();
    addPartialResultRecieverMethod();
    addInitResultRecieverMethod();

    QString appDestination(QCoreApplication::applicationDirPath());
    appDestination.append("/");
    appDestination.append("ru");
    //appDestination.append("ru");
    appDestination.append("/");

    const char *str[2];
    str[0] = "menu";
    //str[1] = "menu.gram";
    str[1] = "#JSGF V1.0; grammar commands; <commands> = два | три; public <command> = <commands>+;";
    //qDebug() << str[1];
    //str[1] = "#JSGF V1.0; grammar calc; public <query> = [exit | new | settings | new game | network];";

    SpeechRecognizer::saveLogIntoFile( true );
    QString name = "";
    name = "Микрофон (2- Устройство с поддержкой High Definition Audio)";
    //name =  "Микрофон (Аудио устройства USB)";
    SpeechRecognizer::setInputDeviceName( name.toUtf8() );
    //SpeechRecognizer::setThreshold(1e-7f);
    bool result = SpeechRecognizer::runRecognizerSetup( appDestination.toUtf8( ).data( ) );
    if (!result)
        qDebug() << "error on init";

    result = SpeechRecognizer::addWordIntoDictionary("два", "d v a1");
    result = SpeechRecognizer::addWordIntoDictionary("три", "t rj i1");

    //result = SpeechRecognizer::addWordIntoDictionary("exit", "EH G Z IH T");
    //result = SpeechRecognizer::addWordIntoDictionary("new", "N UW");
    //result = SpeechRecognizer::addWordIntoDictionary("settings", "S EH T IH NG Z");
    //result = SpeechRecognizer::addWordIntoDictionary("game", "G EY M");
    //result = SpeechRecognizer::addWordIntoDictionary("network", "N EH T W ER K");

    if (!result)
        qDebug() << "error on add word";

    if (result)
    {
           //result = SpeechRecognizer::addGrammar(str[0], str[1]);
           result = SpeechRecognizer::addGrammarString(str[0], str[1]);
    }
    else
        qDebug() << "error on init speech recognizer";

    //SpeechRecognizer::setKeyword("один");
    //SpeechRecognizer::setBaseGrammar("menu");
    if (!result)
    {
        qDebug() << "error on add grammar" << str[1];
        return -1;
    }

    SpeechRecognizer::startListeningMic();

    while (true) {
        SpeechRecognizer::readMicBuffer();
        Sleep(100);
    }
    return a.exec();
}
