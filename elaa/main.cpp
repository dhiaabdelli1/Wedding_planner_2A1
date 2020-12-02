#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connexion c;
    bool test=c.createconnect();
     MainWindow w;
    if(test)
    {w.show();
        QMessageBox::critical(nullptr, QObject::tr("testbd is open"),
                    QObject::tr("connexion successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("testbd is not open"),
                    QObject::tr("connexion failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
