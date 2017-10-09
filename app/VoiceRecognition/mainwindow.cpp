#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "languages.h"

#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _dict = new Dictionary( this );
    connect( _dict, SIGNAL( changeProgress( int ) ), this, SLOT( onLoadDict( int ) ) );

    connect( &SpeakRecognition::instance( ), SIGNAL( logMessRecived( QString ) ), this, SLOT( onLogMessRecieve( QString ) ) );
    connect( &SpeakRecognition::instance( ), SIGNAL( crashMessRecieved( QString ) ), this, SLOT(onCrashRecieve( QString ) ) );
    connect( &SpeakRecognition::instance( ), SIGNAL( recognitionResult( QString ) ), this, SLOT( onResultRecieve( QString ) ) );

    initInterface( );
}

MainWindow::~MainWindow( ) {
    delete ui;
}

bool MainWindow::eventFilter( QObject *sender, QEvent *event ) {
    if ( event->type( ) == QEvent::MouseButtonDblClick ) {
        if ( _resultsArea.viewport( ) == sender ) _resultsArea.clear( );
        if ( _wordsArea.viewport( ) == sender ) _wordsArea.clear( );
    }
    return QWidget::eventFilter( sender, event );
}

void MainWindow::initInterface( ) {
    auto *mainLayout =  new QVBoxLayout( );
    mainLayout->setAlignment( Qt::AlignTop );
    this->centralWidget( )->setLayout( mainLayout );

    auto *languageLbl = new QLabel( "1. Select language", this );
    mainLayout->addWidget( languageLbl );

    auto *languageComboBox = new QComboBox( this );
    languageComboBox->addItem( "en_US" );
    languageComboBox->addItem( "ru_RU" );
    languageComboBox->addItem( "fr_FR" );
    languageComboBox->addItem( "de_DE" );
    languageComboBox->addItem( "es_ES" );
    languageComboBox->addItem( "it_IT" );
    languageComboBox->setCurrentIndex( -1 );
    connect( languageComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onLanguageChange( int ) ) );
    mainLayout->addWidget( languageComboBox );

    auto *progressBar = new QProgressBar( this );
    connect( _dict, SIGNAL( changeProgress( int ) ), progressBar, SLOT( setValue( int ) ) );
    mainLayout->addWidget( progressBar );

    auto *wordsLbl = new QLabel( "2. Enter words. Double click to clear area", this );
    mainLayout->addWidget( wordsLbl );

    _wordsArea.viewport( )->installEventFilter( this );
    mainLayout->addWidget( &_wordsArea );

    auto *btnLbl = new QLabel( "3. Start recognition", this );
    mainLayout->addWidget( btnLbl );

    _btnStart.setText( "Start" );
    connect( &_btnStart, SIGNAL( clicked( ) ), this, SLOT( onBtnStartChangeStatus( ) ) );
    _btnStart.setEnabled( false );
    mainLayout->addWidget( &_btnStart );

    auto *resultsLbl = new QLabel( "4. Check results. Double click to clear area", this );
    mainLayout->addWidget( resultsLbl );

    _resultsArea.viewport( )->installEventFilter( this );
    mainLayout->addWidget( &_resultsArea );

    auto *btnClose = new QPushButton( "Close app", this );
    connect( btnClose, &QPushButton::clicked, []( ){ QApplication::quit( ); } );
    mainLayout->addWidget( btnClose );
}

bool MainWindow::initSpeechRecognizer( ) {
    auto list = _wordsArea.toPlainText( ).split( " " );
    Grammar grammar;
    bool initResult = false;
    initResult = SpeakRecognition::instance( ).init( _acousticModelPath );
    if ( !initResult ) return false;
    for ( auto word : list ) {
        if ( _dict->containsWord( word ) ) {
            SpeakRecognition::instance( ).addWord( word, _dict->getWordPhones( word ) );
            grammar.addWord( word );
        }
        else {
            onCrashRecieve( "Dictionary does not contain word:" + word );
        }
    }
    QString grammarString( grammar.toString( ) );
    if ( grammarString != QString( ) ) {
        SpeakRecognition::instance( ).addGrammarString( "base", grammarString );
        return true;
    }
    else {
        onCrashRecieve( "Word list is empty. Enter some words" );
        return false;
    }
}

void MainWindow::onLanguageChange( int index ) {
    if ( index == -1) return;
    QString path( QCoreApplication::applicationDirPath( ) );
    auto lang = ( Language )index;
    switch ( lang ) {
    case Language::en_US:
        path.append( "/acousticModels/eng/" );
        break;
    case Language::de_DE:
        path.append( "/acousticModels/ger/" );
        break;
    case Language::es_ES:
        path.append( "/acousticModels/esp/" );
        break;
    case Language::fr_FR:
        path.append( "/acousticModels/fr/" );
        break;
    case Language::it_IT:
        path.append( "/acousticModels/it/" );
        break;
    case Language::ru_RU:
        path.append( "/acousticModels/ru/" );
        break;
    }
    _dict->switchLanguage( lang );
    _acousticModelPath = QDir::toNativeSeparators( path );
    _start = false;
    _btnStart.setDisabled( true );
    SpeakRecognition::instance( ).stopRecognition( );
    _wordsArea.clear( );
    _resultsArea.clear( );
}

void MainWindow::onLoadDict( int value ) {
    if ( value == 100 ) {
        _btnStart.setEnabled( true );
        _btnStart.setText( "Start" );
    }
}

void MainWindow::onBtnStartChangeStatus( ) {
    _start = !_start;
    if ( _start ) {
        _btnStart.setText( "Stop" );
        auto initResult = initSpeechRecognizer( );
        if ( initResult )
            SpeakRecognition::instance( ).startRecognition( );
    }
    else {
        _btnStart.setText( "Start" );
        SpeakRecognition::instance( ).stopRecognition( );
    }
}

void MainWindow::onLogMessRecieve( QString mess ) {
    _resultsArea.append("<font color = black>Log:" + mess + "<\\font>");
}

void MainWindow::onResultRecieve( QString result ) {
    _resultsArea.append("<font color = green>Result:" + result + "<\\font>");
}

void MainWindow::onCrashRecieve( QString crash ) {
    _resultsArea.append("<font color = red>CRASH:" + crash + "<\\font>");
}
