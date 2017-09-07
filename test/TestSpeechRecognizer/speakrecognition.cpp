#include "speakrecognition.h"

SpeakRecognition::SpeakRecognition(QObject *parent) : QObject(parent)
{
    QObject::connect(&tmr, SIGNAL(timeout()), this, SLOT(OnTimeout()));
    tmr.setInterval(100);


    SpeechRecognizer::setLogMessReciever(LogResult);
    SpeechRecognizer::setResultReciever(SpeechResult);
    SpeechRecognizer::saveLogIntoFile(false);

    bool initResult = SpeechRecognizer::runRecognizerSetup("/home/ubuntu/Общедоступные/Projects/build-SpeechRecognizerControl-Desktop-Debug/TesterApp/");

    if (initResult) {
        qDebug() << "success";
        initResult = SpeechRecognizer::addGrammarString("base", "#JSGF V1.0; grammar calc; public <query> = [ выбрать | закрыть | назад | информация | увеличить | уменьшить | вниз | вверх | вправо | влево | задание | схема приказ | частот расписание | таблица позывных | схема построения трактов | показать расположение | оглавление | вернуться | интерактивная модель | стоп | зажать | отпустить | повернуть влево | повернуть вправо | повернуть вниз | повернуть вверх ];");
        if (initResult) {
            qDebug() << "success add grammar";
            SpeechRecognizer::startListeningMic();
            tmr.start(100);
        }

    }
    else {
        qDebug() << "not success";
    }
}

void SpeakRecognition::OnTimeout()
{
    SpeechRecognizer::readMicBuffer();
}

void SpeakRecognition::SpeechResult(const char value[])
{
    qDebug()  << "speechResult:" << value;
}

void SpeakRecognition::LogResult(const char value[])
{
    qDebug()  << "logResult:" << value;
}

void SpeakRecognition::InitResult(const char value[])
{
    qDebug()  << "initResult:" << value;
}

