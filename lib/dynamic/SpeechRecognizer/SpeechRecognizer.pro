#-------------------------------------------------
#
# Project created by QtCreator 2017-01-04T15:15:07
#
#-------------------------------------------------

QT       -= gui

TARGET = SpeechRecognizer
TEMPLATE = lib

CONFIG += c++11

DEFINES += SPEECHRECOGNIZER_LIBRARY

SOURCES += speechrecognizer.cpp \
    speechrecognizerwrapper.cpp

HEADERS += \
    speechrecognizer.h \
    speechrecognizerwrapper.h

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

INCLUDEPATH += $$PWD/include/pocketsphinx
DEPENDPATH += $$PWD/include/pocketsphinx

INCLUDEPATH += $$PWD/include/sphinxbase
DEPENDPATH += $$PWD/include/sphinxbase

INCLUDEPATH += $$PWD/include/win32
DEPENDPATH += $$PWD/include/win32

equals(QT_ARCH, i386) {
    #message("32-bit")
    win32: LIBS += -L$$PWD/lib/win/x32/ -lsphinxbase
    win32: LIBS += -L$$PWD/lib/win/x32/ -lpocketsphinx
    win32: LIBS += -L$$PWD/lib/win/x32/ -lWinMM
}

equals(QT_ARCH, "x86_64") {
    #message("64-bit")
    win32: LIBS += -L$$PWD/lib/win/x64/ -lsphinxbase
    win32: LIBS += -L$$PWD/lib/win/x64/ -lpocketsphinx
    win32: LIBS += -L$$PWD/lib/win/x64/ -lWinMM
}

equals(QT_ARCH, arm) {
    #message("raspbian")
    unix: LIBS += -L$$PWD/lib/raspbian/ -lpocketsphinx
    unix: LIBS += -L$$PWD/lib/raspbian/ -lsphinxad
    unix: LIBS += -L$$PWD/lib/raspbian/ -lsphinxbase
}

unix: LIBS += -lpulse
unix: LIBS += -lpulse-simple
