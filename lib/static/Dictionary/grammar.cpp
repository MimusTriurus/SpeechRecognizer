#include "grammar.h"
#include <QDebug>

Grammar::Grammar( QObject *parent ) : QObject( parent ) {

}

void Grammar::addWord( QString word ) {
    _words.append( word.toLower( ) );
}

QString Grammar::toString( ) {
    if ( _words.empty( ) ) {
        return QString( );
    }
    QString grammarString( "#JSGF V1.0;" );
    grammarString.append( "grammar commands;" );
    grammarString.append( "<commands> = " );

    QStringListIterator it( _words );

    while ( it.hasNext( ) ) {
        grammarString.append( it.next( ) );
        if ( it.hasNext( ) )
            grammarString.append( "|" );
    }
    grammarString.append( ";" );
    grammarString.append( "public <command> = <commands>+;" );
    return grammarString;
}
