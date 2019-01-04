#ifndef CONTROLPLAYLIST_H
#define CONTROLPLAYLIST_H

#include<QMap>
#include<QMapIterator>

class controlPlayList
{
public:
    controlPlayList();
    QMap<QString,QString> addPlayList(QString key,QString value);

    QString playMedia(QString key);
    QString findMedia(int row);

private:
    QString filename;
    static QMap<QString,QString> playMap;
};

#endif // CONTROLPLAYLIST_H
