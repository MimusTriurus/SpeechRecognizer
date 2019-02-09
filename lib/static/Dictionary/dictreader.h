#ifndef DICTREADER_H
#define DICTREADER_H

#include <QObject>
#include <QThread>
#include <QMap>

#include "languages.h"

class DictReader : public QThread {
    Q_OBJECT
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
protected:
    void run( ) override;
private:
    Language _currentLang;
    QString getDictFilePath( Language value );
    int checkPercent( int current, int count );
};

#endif // DICTREADER_H
