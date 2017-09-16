#ifndef DICTREADER_H
#define DICTREADER_H

#include <QObject>

class DictReader : public QObject
{
    Q_OBJECT
public:
    explicit DictReader(QObject *parent = 0);

signals:

public slots:
};

#endif // DICTREADER_H