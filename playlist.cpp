#include "playlist.h"
#include "ui_playlist.h"
#include "mainwindow.h"

QMap<QString,QString> playlist::playMap;

playlist::playlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playlist)
{
    ui->setupUi(this);
    loadPlayList();



}

playlist::~playlist()
{
    delete ui;
}

void playlist::on_btnAdd_clicked()
{
    filename = QFileDialog::getOpenFileName(this,"Open a File","","All Media File(*.*)");
    fileInfo = new QFileInfo(filename);
    QString extention = fileInfo->suffix();


  playMap.insert(fileInfo->fileName(),filename);

loadPlayList();
}
void playlist::loadPlayList(){
ui->lstPlayList->clear();

QMap<QString, QString>::iterator i;
for (i = playMap.begin(); i != playMap.end(); ++i){

    ui->lstPlayList->addItem(i.key());
}

}

void playlist::on_lstPlayList_itemDoubleClicked(QListWidgetItem *item)
{

   QString key = ui->lstPlayList->currentItem()->text();
   QMap<QString, QString>::iterator i;
   for (i = playMap.begin(); i != playMap.end(); ++i){

       if(i.key()==key){
           QString path = i.value();

    QMessageBox::information(this,"titile",path);




           break;
       }

   }


}
