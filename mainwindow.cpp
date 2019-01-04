#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playlist.h"
#include<QKeyEvent>
#include<QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setFixedSize(QSize(1300,630));

    //Setting up the Media Player and VideoWidget
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    ui->horizontalLayout->addWidget(vw);




    player2 = new QMediaPlayer(this);
    vw2= new QVideoWidget(this);



    pixMap = new QPixmap();
    widget = new QWidget(vw);



    player2->setVideoOutput(vw2);
    timer = new QTimer(this);
    ui->btnPlay->setFixedHeight(30);
    ui->btnPlay->setFixedWidth(30);

    ui->btnPause->setFixedSize(QSize(30,30));
    ui->btnPause->setIconSize(QSize(20,20));


    ui->btnPlay->setIconSize(QSize(20,20));

    ui->sliderVol->setFixedWidth(100);
    ui->horizontalLayout->addWidget(vw2);

    //Add lable to horizontal layout and set Welcome Image
    ui->horizontalLayout->addWidget(ui->lblWimg);
    pixMap->load(":/images/images/cool-background1.jpg");
    ui->lblWimg->setPixmap(*pixMap);


    vw->hide();
    vw2->hide();

    ui->horizontalLayout->addWidget(ui->lstPlayList);
    ui->lstPlayList->setFixedSize(QSize(250,500));


    ui->statusBar->addWidget(ui->btnPlay);
    ui->statusBar->addWidget(ui->btnPause);
    ui->statusBar->addWidget(ui->btnPrevious);
    ui->statusBar->addWidget(ui->btnStop);
    ui->statusBar->addWidget(ui->btnNext);
    ui->statusBar->addWidget(ui->btnFullScreen);
    ui->statusBar->addWidget(ui->btnPlatyList);
    ui->statusBar->addWidget(ui->btnVolume);
    ui->statusBar->addWidget(ui->sliderVol);
    ui->statusBar->addWidget(ui->cmbPlaySpeed);



    ui->statusBar->addPermanentWidget(ui->lblStatus);


    connect(player,&QMediaPlayer::durationChanged,ui->slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,ui->slider,&QSlider::setValue);
    connect(ui->slider,&QSlider::sliderMoved ,player,&QMediaPlayer::setPosition);

    connect(player2,&QMediaPlayer::stateChanged,player2,&QMediaPlayer::play);


    ui->sliderVol->setRange(0, 100);
    ui->sliderVol->setFixedWidth(100);


    connect( ui->sliderVol, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));
    connect( ui->sliderVol, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));

    ui->cmbPlaySpeed->addItem("0.5x",QVariant(0.5));
    ui->cmbPlaySpeed->addItem("1.0x",QVariant(1.0));
    ui->cmbPlaySpeed->addItem("2.0x",QVariant(2.0));
    ui->cmbPlaySpeed->setCurrentIndex(1);


    fileFilter = "All Media Files(*.mp3 *.mp4 *.avi *.wav *.3gp *.flv *.m4v *.mpeg *.wmv *.vob *.mpa);; Audio Files(*.mp3 *.wav *.mpa) ;; Video Files (*.mp4 *.avi.3gp *.flv *.m4v *.mpeg *.wmv *.vob)";


    open = new QShortcut(this);
    open->setKey(Qt::Key_F1);
    connect(open,SIGNAL(activated()),this,SLOT(on_actionOpen_triggered()));

    exit = new QShortcut(this);
    exit->setKey(Qt::Key_F4);
    connect(exit,SIGNAL(activated()),this,SLOT(on_actionQuit_triggered()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    openMedia();
}

void MainWindow::on_actionPlay_triggered()
{
}

void MainWindow::on_actionPause_triggered()
{
    QMessageBox::information(this,"Sa","sasasas");
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
}

void MainWindow::on_btnPlay_clicked()
{


    playMedia(NULL);

    ui->lblStatus->setText("Play");
    controllblStatus();
}

void MainWindow::on_btnPause_clicked()
{
    player->pause();
    timer->stop();
    ui->lblStatus->setText("Pause");
}

void MainWindow::on_btnStop_clicked()
{
    vw->hide();
    vw2->hide();
    ui->lblWimg->show();
    player->stop();
    ui->lblStatus->setText("Stop");
    QWidget::setWindowTitle("CutePlayer");

}

void MainWindow::on_btnFullScreen_clicked()
{
   vw->setFullScreen(true);
}

void MainWindow::on_btnPlatyList_clicked()
{
    filename = QFileDialog::getOpenFileName(this,"Open a File","","All Media File(*.*)");

    fileInfo = new QFileInfo(filename);
    QString key =fileInfo->fileName();
    QString value = fileInfo->filePath();

    playMap = cPlayList.addPlayList(key,value);

  loadPlaylist();

}
void MainWindow::playMedia(QString filepath){

    if(player->isAudioAvailable()||player->isVideoAvailable()){
        player->play();
        return;
    }
    filename = QFileDialog::getOpenFileName(this,"Open a File","",fileFilter);
    fileInfo = new QFileInfo(filename);

   changeAlbumArt(filename);

    QWidget::setWindowTitle(fileInfo->fileName());

    player->stop();
    player->setMedia(QUrl::fromLocalFile(filename));
    player->play();

}

void ::MainWindow::openMedia(){
    filename = QFileDialog::getOpenFileName(this,"Open a File","",fileFilter);
    fileInfo = new QFileInfo(filename);
    changeAlbumArt(filename);
    QWidget::setWindowTitle(fileInfo->fileName());

   player->stop();
   player->setMedia(QUrl::fromLocalFile(filename));
   player->play();

}
void MainWindow::playFromLst(QString path){

   changeAlbumArt(path);
//    vw->show();
    player->stop();
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}
void MainWindow::on_lstPlayList_itemDoubleClicked(QListWidgetItem *item)
{
    QString key = ui->lstPlayList->currentItem()->text();
    QWidget::setWindowTitle(key);
    QString path = cPlayList.playMedia(key);
    playFromLst(path);
}

void MainWindow::on_btnNext_clicked()
{

    int rowcount = ui->lstPlayList->count();
    int currentRow =ui->lstPlayList->currentRow();
    int nextrow = currentRow+1;
    if(nextrow<rowcount){

        QString nextMedia = ui->lstPlayList->item(nextrow)->text();
        QWidget::setWindowTitle(nextMedia);
        ui->lstPlayList->setCurrentRow(nextrow);
        ui->lstPlayList->item(nextrow)->setSelected(true);
        QString path = cPlayList.playMedia(nextMedia);
        playFromLst(path);

    }


}
void MainWindow::loadPlaylist(){
    ui->lstPlayList->clear();
    QMap<QString, QString>::iterator i;
    for (i = playMap.begin(); i != playMap.end(); ++i){

        ui->lstPlayList->addItem(i.key());
    }
}

void MainWindow::on_btnPrevious_clicked()
{
    int rowcount = ui->lstPlayList->count();
    int currentRow =ui->lstPlayList->currentRow();
    int prevousRow = currentRow-1;
    if(prevousRow>=0){

        QString nextMedia = ui->lstPlayList->item(prevousRow)->text();
        QWidget::setWindowTitle(nextMedia);
        ui->lstPlayList->setCurrentRow(prevousRow);
        ui->lstPlayList->item(prevousRow)->setSelected(true);
        QString path = cPlayList.playMedia(nextMedia);
        playFromLst(path);

    }
}

void MainWindow::on_btnVolume_clicked()
{
    if(muted==true){
        player->setMuted(false);
        status();
        muted=false;
    }else{
        player->setMuted(true);
        ui->lblStatus->setText("Mute");
        muted=true;
    }
}



void MainWindow::on_cmbPlaySpeed_currentIndexChanged(int index)
{
    float speed=  ui->cmbPlaySpeed->itemData(index).toFloat();
    player->setPlaybackRate(speed);

    if(speed==0.5){
        ui->lblStatus->setText(QString::number(float(speed))+"x");

    }else{
        if(speed==1.0){
          ui->lblStatus->setText("");
          controllblStatus();
        }else{
            ui->lblStatus->setText(QString::number(float(speed))+".0x");
        }
    }
}

void MainWindow::status()
{
   int state= player->state();
   if(state==2){
       ui->lblStatus->setText("Pause");
       return;
   }
    ui->lblStatus->setText("");
}

void MainWindow::showVolume(int volume)
{
    ui->lblStatus->setText("Volume "+QString::number(volume)+"%");
    controllblStatus();
}

void MainWindow::controllblStatus()
{
    timer->start(10000);
    connect(timer,SIGNAL(timeout()),this,SLOT(status()));

}

void MainWindow::changeAlbumArt(QString path)
{

    fileInfo->setFile(path);
    QString extention = fileInfo->suffix();
    ui->lblWimg->hide();
    if(extention=="mp3"){

          qDebug()<<extention;
        vw->hide();
        vw2->show();
        player2->stop();
        player2->setMedia(QUrl("qrc:/video/video/Ring Equalizer -- After Effects.mp4"));
        player2->play();
        player2->setMuted(true);
        ui->btnFullScreen->setEnabled(false);

    }else{
        vw2->hide();
        player2->stop();
        vw->show();
        ui->btnFullScreen->setEnabled(true);
    }
}

void MainWindow::on_sliderVol_valueChanged(int value)
{
    showVolume(value);
}

void MainWindow::on_actionHide_PlayeList_triggered()
{
    ui->lstPlayList->setHidden(true);

}

void MainWindow::on_actionShow_PlayList_triggered()
{
    ui->lstPlayList->setHidden(false);
}

void MainWindow::on_actionQuit_triggered()
{

    QMessageBox::StandardButton reply = qm->question(this,"CutePlayer","Do you want to Exit",QMessageBox::Yes|QMessageBox::No);
    if(reply==qm->Yes){
         QCoreApplication::quit();
    }

}
