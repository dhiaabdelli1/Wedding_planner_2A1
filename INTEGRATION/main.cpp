#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QDebug>
#include <QTranslator>
#include <QSplashScreen>
#include <QTimer>
#include <qmovie.h>
#include <QWidget>
#include <QLayout>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");
    connexion c;
    bool test=c.createConnexion();
    MainWindow w;

//    QMovie *movie = new QMovie("D:/Users/dhiaa/Desktop/Wedding_planner_2A1/INTEGRATION/splash.gif");
//    QLabel *processLabel = new QLabel(NULL);
//    processLabel->setMovie(movie);
//    processLabel->setWindowFlag(Qt::FramelessWindowHint );

//    processLabel->setAlignment(Qt::AlignCenter);
//    movie->start();
//    processLabel->show();


//    QTimer::singleShot(5000,processLabel,SLOT(close()));
//    QTimer::singleShot(5000,&w,SLOT(show()));


    if (test)
        qDebug() << "connexion successful";
    else
        qDebug() << "connexion failed";



    w.show();

    return app.exec();
}
