#ifndef DICTREADER_H
#define DICTREADER_H

#include <QObject>
#include <QThread>
#include <QMap>

#include "languages.h"

class DictReader : public QThread
{
    Q_OBJECT
    Language _currentLang = Language::en_US;
    QString getDictFilePath( Language value );
    int checkPercent( int current, int count );
protected:
    void run( ) override;
public:
    /**
     * @brief конструктор класса
     * @param value язык целевого словаря
     */
    explicit DictReader( Language value = Language::en_US );
    ~DictReader( );
signals:
    /**
     * @brief изменение прогресса чтение файла словаря
     * @param текущий процент выполнения чтения файла словаря
     */
    void progressChanged( int );
    /**
     * @brief уведомление о нахождении в файле словаря
     * слова и фонемы
     * @param word слово
     * @param phones фонема
     */
    void wordAndPhonesExtracted( QString word, QString phones );
public slots:
};

#endif // DICTREADER_H
