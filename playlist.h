#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include<QFileInfo>
#include<QFileDialog>
#include<QMap>
#include<QMapIterator>
#include<QListWidgetItem>
#include<QMessageBox>
#include "mainwindow.h"
namespace Ui {
class playlist;
}

class playlist : public QWidget
{
    Q_OBJECT

public:
    explicit playlist(QWidget *parent = nullptr);
    ~playlist();

private slots:
    void on_btnAdd_clicked();



    void on_lstPlayList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::playlist *ui;
    QFileInfo *fileInfo;
    QString filename;


 static QMap<QString,QString> playMap;



public:
    void loadPlayList();



};

#endif // PLAYLIST_H
