#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include "dictionary.h"
#include "grammar.h"
#include "languages.h"
#include "speakrecognition.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Dictionary *dict = new Dictionary( this );
    connect( dict, SIGNAL( changeProgress( int ) ), ui->progressBar, SLOT( setValue( int ) ) );
    connect( dict, SIGNAL( changeProgress( int ) ), this, SLOT( onChangeProgress( int ) ) );

    dict->switchLanguage( Language::ru_RU );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onChangeProgress( int currentPercent )
{
    if ( currentPercent == 100 ) {
        Grammar gram;
        gram.addWord( "два" );
        gram.addWord( "три" );

        QString appDestination( QCoreApplication::applicationDirPath( ) );
        appDestination.append("/");
        appDestination.append("ru");
        appDestination.append("/");

        bool result = SpeakRecognition::instance( ).init( appDestination );
        if ( result ) {
            SpeakRecognition::instance( ).addWord( "два", "d v a1" );
            SpeakRecognition::instance( ).addWord( "три", "t rj i1" );
            SpeakRecognition::instance( ).addGrammarString( "menu", gram.toString( ) );
            SpeakRecognition::instance( ).startRecognition( );
        }
    }
}
