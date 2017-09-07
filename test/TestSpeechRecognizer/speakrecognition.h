#ifndef SPEAKRECOGNITION_H
#define SPEAKRECOGNITION_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "speechrecognizer.h"
using namespace SpeechRecognizer;

class SpeakRecognition : public QObject
{
    Q_OBJECT
private:
    QTimer tmr;
public:
    explicit SpeakRecognition(QObject *parent = 0);

signals:

public slots:
    void OnTimeout();

    static void SpeechResult(const char value[]);

    static void LogResult(const char value[]);

    static void InitResult(const char value[]);
};

#endif // SPEAKRECOGNITION_H
