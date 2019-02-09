#include "dictionary.h"

#include <QDebug>
#include <QFile>
#include <QResource>

Dictionary::Dictionary( QObject *parent ) :
    QObject{ parent }
{

}

Dictionary::~Dictionary( ) {

}

void Dictionary::switchLanguage( Language value ) {
    DictReader *dictReader = new DictReader( value );
    connect( dictReader, SIGNAL( finished( ) ), dictReader, SLOT( deleteLater( ) ) );
    connect( dictReader, SIGNAL( progressChanged( int ) ), this, SLOT( onChangeProgress( int ) ) );
    connect( dictReader, SIGNAL( wordAndPhonesExtracted( QString, QString ) ), this, SLOT( onGetWordAndPhones( QString, QString ) ) );
    dictReader->start( );
}

QString Dictionary::getWordPhones( const QString &word ) const {
    if ( _dict.contains( word ) ) {
        return _dict[ word ];
    }
    else {
        return QString( );
    }
}

bool Dictionary::containsWord( const QString &word ) const {
    return _dict.contains( word );
}

void Dictionary::onGetWordAndPhones( const QString &word, const QString &phones ) {
    if ( !_dict.contains( word ) ) {
        _dict.insert( word, phones );
    }
}

void Dictionary::onChangeProgress( int currentPercent ) {
    emit changeProgress( currentPercent );
}
