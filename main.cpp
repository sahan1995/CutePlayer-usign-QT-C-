#include "mainwindow.h"
#include <QApplication>
#include<QSplashScreen>
#include<QTimer>
#include<QPixmap>
#include <QDesktopWidget>
int main(int argc, char *argv[])

{
    QApplication a(argc, argv);

    MainWindow w;

    QSplashScreen *splash = new QSplashScreen();
    QPixmap *pixMap = new QPixmap(":/images/images/splash.jpg");
    splash->setPixmap(*pixMap);
    splash->show();


    w.adjustSize();
    w.setGeometry( QStyle::alignedRect(
                       Qt::LeftToRight,
                       Qt::AlignCenter,
                       w.size(),
                       a.desktop()->availableGeometry()
                   ));

    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));

//    w.show();
    return a.exec();
}
