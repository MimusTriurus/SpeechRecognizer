#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QObject>
#include <QStringList>

/**
 * @brief класс формирования формализованной
 * строки грамматики - читай перечня слов для
 * распознвания
 */
class Grammar : public QObject
{
    Q_OBJECT
    QStringList _words;
public:
    Grammar( QObject *parent = nullptr );
    /**
     * @brief добавление слова в строку с грамматикой
     * @param word слово
     */
    void addWord( const QString word );
    /**
     * @brief преобразование строк в формализованную строку
     * @return строка с грамматикой
     */
    QString toString( );
};

#endif // GRAMMAR_H
