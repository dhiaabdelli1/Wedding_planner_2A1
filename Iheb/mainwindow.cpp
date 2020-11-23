#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QTimeEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tableView->setModel(tempclient.afficher());
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{ MainWindow w;
    int CIN= ui->LineEditp1->text().toInt();
    QString nom= ui->prNomPartenaire1LineEdit->text();
    QString prenom= ui->nomPartenaire1LineEdit->text();
    QDate date_naissance = ui->dateEdit_2->date();
    client c(CIN,nom,prenom);
    bool test=c.ajouter();
    if(test)
    {        ui->tableView->setModel(tempclient.afficher());

        w.show();
        QMessageBox::information(nullptr, QObject::tr("ajout client"),
                    QObject::tr("ajout réussi\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("ajout échoué"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_pushButton_3_clicked()
{
    QItemSelectionModel *select=ui->tableView->selectionModel();
    int CIN =select->selectedRows(0).value(0).data().toInt();
    bool test=tempclient.supprimer(CIN);

    if(test)
    {        ui->tableView->setModel(tempclient.afficher());

        //w.show();
        QMessageBox::information(nullptr, QObject::tr("ajout client"),
                    QObject::tr("suppression réussie\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("ajout échoué"),
                    QObject::tr("suppression échouée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_tabWidget_2_currentChanged(int index)
{
    ui->tableView->setModel(tempclient.afficher());
}
