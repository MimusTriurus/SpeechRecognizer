#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T15:42:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VoiceRecognition
TEMPLATE = app

CONFIG += c++11

DESTDIR = ../../bin

MOC_DIR = moc

OBJECTS_DIR = obj

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
        mainwindow.cpp \
        speakrecognition.cpp

HEADERS  += mainwindow.h \
        speakrecognition.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/Dictionary/release/ -lDictionary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/Dictionary/debug/ -lDictionary
else:unix:!macx: LIBS += -L$$OUT_PWD/../../lib/static/Dictionary/ -lDictionary

INCLUDEPATH += $$PWD/../../lib/static/Dictionary
DEPENDPATH += $$PWD/../../lib/static/Dictionary

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Dictionary/release/libDictionary.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Dictionary/debug/libDictionary.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Dictionary/release/Dictionary.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Dictionary/debug/Dictionary.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Dictionary/libDictionary.a

LIBS += -L$$OUT_PWD/../../bin/ -lSpeechRecognizer

INCLUDEPATH += $$PWD/../../lib/dynamic/SpeechRecognizer
DEPENDPATH += $$PWD/../../lib/dynamic/SpeechRecognizer
