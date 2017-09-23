#include "dictreader.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QTextStream>

void DictReader::run( ) {
    QString dictFilePath( getDictFilePath( _currentLang ) );
    QFile dictFile( dictFilePath );
    if ( dictFile.open( QFile::ReadOnly | QFile::Text ) ) {
        QTextStream textStream( &dictFile );
        textStream.setCodec("UTF-8");
        QStringList words = textStream.readAll( ).split( '\n' );
        int count( words.count( ) );
        int currentLineIndex( 0 );
        int prevCurrentPercent( currentLineIndex );
        foreach ( QString line, words ) {
            QStringList list = line.split( " " );
            QString word( list.at( 0 ).toLower( ) );
            list.removeAt( 0 );
            QString phones( list.join( " " ) );
            int currentPercent( checkPercent( ++currentLineIndex, count ) );
            if ( currentPercent != prevCurrentPercent ) {
                prevCurrentPercent = currentPercent;
                emit progressChanged( currentPercent );
            }
            if ( word != QString( ) )
                emit wordAndPhonesExtracted( word, phones );
        }
    }
    else
        qDebug( ) << "error on open file" << dictFilePath << "Use Q_INIT_RESOURCE( dictfiles ); in main.cpp to init resource file";
}

DictReader::DictReader( Language value ) : _currentLang( value ) {

}

DictReader::~DictReader( ) {

}

QString DictReader::getDictFilePath( Language value ) {
    switch ( value ) {
    case Language::en_US:
        return ":/assets/enDict.dict";
    case Language::de_DE:
        return ":/assets/geDict.dict";
    case Language::es_ES:
        return ":/assets/esDict.dict";
    case Language::fr_FR:
        return ":/assets/frDict.dict";
    case Language::it_IT:
        return ":/assets/itDict.dict";
    case Language::ru_RU:
        return ":/assets/ruDict.dict";
    }
    return QString( );
}

int DictReader::checkPercent( int current, int count ) {
    double currentPercent( current * 100 );
    currentPercent /= count;
    return currentPercent;
}
