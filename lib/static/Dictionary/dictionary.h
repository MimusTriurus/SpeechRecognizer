#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QObject>
#include <QMap>

#include "languages.h"
#include "dictreader.h"

class Dictionary : public QObject
{
    Q_OBJECT
    QMap<QString, QString> _dict;
public:
    /**
     * @brief конструктор класса
     * @param value язык словаря
     */
    Dictionary( Language value = Language::en_US, QObject *parent = nullptr ) : QObject( parent ) { switchLanguage( value ); }
    /**
     * @brief конструктор класса по умолчанию
     */
    explicit Dictionary( QObject *parent = nullptr ) : QObject( parent ) { }

    ~Dictionary( ) { }
    /**
     * @brief смена словаря
     * @param value язык словаря
     */
    void switchLanguage( Language value = Language::en_US );
    /**
     * @brief метод получения транскрипции слова
     * @param word слово
     * @return транскрипция
     */
    QString getWordPhones( QString word ) const ;
    /**
     * @brief проверка наличия слова в словаре
     * @param word искомое слово
     * @return результат поиска
     */
    bool containsWord( QString word ) const;
signals:
    /**
     * @brief прогресс чтение файла словаря
     * @param текущий процент выполнения чтения файла словаря
     * currentPercent == 100 - окончание чтение словаря
     */
    void changeProgress( int );
    /**
     * @brief уведомление об отсутствии
     * слова в словаре
     * @param mess сообщение с ошибкой
     */
    void notContainWord( QString );
private slots:
    /**
     * @brief уведомление о нахождении в файле словаря
     * слова и фонемы
     * @param word слово
     * @param phones фонема
     */
    void onGetWordAndPhones( QString word, QString phones );
    /**
     * @brief прогресс чтение файла словаря
     * @param currentPercent текущий процент выполнения чтения файла словаря
     * currentPercent == 100 - окончание чтение словаря
     */
    void onChangeProgress( int currentPercent );
};

#endif // DICTIONARY_H
