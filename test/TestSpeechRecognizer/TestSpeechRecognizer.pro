QT       += core gui multimedia
QT -= gui

CONFIG += c++11

TARGET = TestSpeechRecognizer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/dynamic/SpeechRecognizerWrapper/release/ -lSpeechRecognizerWrapper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/dynamic/SpeechRecognizerWrapper/debug/ -lSpeechRecognizerWrapper

INCLUDEPATH += $$PWD/../../lib/dynamic/SpeechRecognizerWrapper
DEPENDPATH += $$PWD/../../lib/dynamic/SpeechRecognizerWrapper
