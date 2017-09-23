#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QProgressBar>
#include <QFile>
#include <QIODevice>
#include <QLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QEvent>

#include "speakrecognition.h"
#include "grammar.h"
#include "dictionary.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Dictionary *_dict;
    Ui::MainWindow *ui;
    bool _start = false;
    QPushButton _btnStart;
    QTextEdit _wordsArea;
    QTextEdit _resultsArea;
    QString _acousticModelPath = QString( );
    void initInterface( );
    bool initSpeechRecognizer( );
public:
    explicit MainWindow( QWidget *parent = nullptr );
    ~MainWindow( );
protected:
    bool eventFilter( QObject *sender, QEvent *event );
private slots:
    void onLanguageChange( int index );
    void onLoadDict( int value );
    void onBtnStartChangeStatus( );

    void onLogMessRecieve( QString mess );
    void onResultRecieve( QString result );
    void onCrashRecieve( QString crash );
};

#endif // MAINWINDOW_H
