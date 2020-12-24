#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connexion c;
    bool test=c.createConnexion();
    MainWindow w;

    if (test)
        qDebug() << "connexion successful";
    else
        qDebug() << "connexion failed";
    w.show();

    return a.exec();
}
