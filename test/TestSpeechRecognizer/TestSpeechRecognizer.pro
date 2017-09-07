QT       += core gui multimedia
QT -= gui

CONFIG += c++11

TARGET = TestSpeechRecognizer
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    speakrecognition.cpp

HEADERS += \
    speakrecognition.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/dynamic/SpeechRecognizer/release/ -lSpeechRecognizer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/dynamic/SpeechRecognizer/debug/ -lSpeechRecognizer

INCLUDEPATH += $$PWD/../../lib/dynamic/SpeechRecognizer
DEPENDPATH += $$PWD/../../lib/dynamic/SpeechRecognizer
