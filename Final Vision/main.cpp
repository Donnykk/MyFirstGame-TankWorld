#include "tank.h"
#include "start.h"
#include "help.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>
#include <QPushButton>
#include <QMediaPlayer>
#include <QWidget>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    start s;
    help h;
    Tank w;
    QMediaPlayer *music=new QMediaPlayer;
    music->setMedia(QUrl::fromLocalFile("C:\\Users\\17898\\Desktop\\c++\\Final Vision\\Startmusic.mp3"));
    music->setVolume(20);
    music->play();
    QPixmap pixmap(":/image/start.jpg");
    QSplashScreen screen(pixmap);
    screen.show();
    a.processEvents();
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do
    {
        now=QDateTime::currentDateTime();
    }
    while(n.secsTo(now)<=1);
    s.show();
    s.raise();
    screen.finish(&s);
    QObject::connect(&s,SIGNAL(emitsignal_A()),&w,SLOT(acceptstart_A()));
    QObject::connect(&s,SIGNAL(emitsignal_B()),&h,SLOT(acceptstart_B()));
    QObject::connect(&h,SIGNAL(emitsignal_B1()),&s,SLOT(acceptstart_B1()));
    return a.exec();
}
