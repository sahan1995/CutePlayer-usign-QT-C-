#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QFileDialog>
#include<QProgressBar>
#include<QSlider>
#include<QWidget>
#include<QFileInfo>
#include<QSize>
#include<QTime>
#include<QMap>
#include<QListWidgetItem>
#include<QMessageBox>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QTimer>
#include<QShortcut>
#include<QPixmap>
#include<QKeyEvent>
#include "controlplayer.h"
#include "controlplaylist.h"

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_btnFullScreen_clicked();

    void on_btnPlatyList_clicked();

    void on_lstPlayList_itemDoubleClicked(QListWidgetItem *item);

    void on_btnNext_clicked();

    void on_btnPrevious_clicked();

    void on_btnVolume_clicked();

    void on_cmbPlaySpeed_currentIndexChanged(int index);
    void status();
    void showVolume(int volume);


    void on_sliderVol_valueChanged(int value);

    void on_actionHide_PlayeList_triggered();

    void on_actionShow_PlayList_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QProgressBar* bar;
    QSlider* slider;
    QString filename;
    QWidget *widget;
    QFileInfo *fileInfo;
    QSize *qsize;
    QTime* totalTime;
    qint64 duration;
    controlPlayList cPlayList;
    QMap<QString,QString> playMap;

    bool muted=false;
    QGraphicsScene *graphS;
    QGraphicsView *graphV;
    QTimer *timer;
    QString fileFilter;

    QPixmap *pixMap;

    QMediaPlayer* player2;
    QVideoWidget* vw2;

    QShortcut *open;
    QShortcut *exit;

    QMessageBox *qm;

public:
     void durationChanged(qint64 duration);

     void positionChange(qint64 progress);

     void playMedia(QString filepath);

     void playFromLst(QString filepath);
     void openMedia();

     void loadPlaylist();

     void controllblStatus();

     void changeAlbumArt(QString path);



     QMap <QString,QString> listMap;
};

#endif // MAINWINDOW_H
