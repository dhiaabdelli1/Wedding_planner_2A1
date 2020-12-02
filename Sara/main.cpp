#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
    bool test=c.createconnect();
    MainWindow w;

    if (test)
    {qDebug() << "connexion successful";
    w.show();}
    else
        qDebug() << "connexion failed";


    return a.exec();
}
