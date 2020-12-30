#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QDebug>
#include <QTranslator>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash= new QSplashScreen;
    splash->setPixmap(QPixmap("D:\\Users\\dhiaa\\Desktop\\Wedding_planner_2A1\\INTEGRATION\\bikou.png"));
    //splash->setGeometry(0,0,500,500);
    //splash->resize(1024,576);
    //splash->show();

    connexion c;
    bool test=c.createConnexion();
    MainWindow w;

//    QTimer::singleShot(1500,splash,SLOT(close()));
//    QTimer::singleShot(1500,&w,SLOT(show()));
    w.show();
    if (test)
        qDebug() << "connexion successful";
    else
        qDebug() << "connexion failed";
    //w.show();

    return a.exec();
}
