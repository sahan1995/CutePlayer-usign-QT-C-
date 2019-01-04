#include "controlplaylist.h"

QMap<QString,QString> controlPlayList::playMap;
controlPlayList::controlPlayList()
{



}
QMap<QString,QString> controlPlayList::addPlayList(QString key,QString value){
    playMap.insert(key,value);
    return playMap;
}

QString controlPlayList::playMedia(QString key){
    QString path;
    QMap<QString, QString>::iterator i;
    for (i = playMap.begin(); i != playMap.end(); ++i){

        if(i.key()==key){
             path = i.value();
             return path;
        }

    }
}
QString controlPlayList::findMedia(int row){


}
