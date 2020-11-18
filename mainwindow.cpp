#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->cINLineEdit->setMaxLength(8);

    ui->cINLineEdit->setPlaceholderText("CIN ...");
    ui->nomLineEdit->setPlaceholderText("Nom ...");
    ui->prNomLineEdit->setPlaceholderText("Prénom ...");
    ui->eMailLineEdit->setPlaceholderText("E-mail ...");


    ui->tableView->setModel(tmpinvite.afficher());


    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_ajouter_clicked()
{


    if ( ui->cINLineEdit->text()!= "" &&
         ui->nomLineEdit->text()!="" &&
         ui->prNomLineEdit->text() != "" &&
         ui->eMailLineEdit->text()!= "")
    {

            int cin = ui->cINLineEdit->text().toInt();
            QString nom= ui->nomLineEdit->text();
            QString prenom= ui->prNomLineEdit->text();
            int age = ui->ageLineEdit->text().toInt();
            QString mail= ui->eMailLineEdit->text();
            QString sexe = ui->sexeComboBox->currentText();



            invite inv(cin,nom,prenom,age,mail,sexe);

            bool test=inv.ajouter();

            if (test)
                ui->tableView->setModel(tmpinvite.afficher());



            /*ui->cINLineEdit->setText("");
            ui->nomLineEdit->setText("");
            ui->prNomLineEdit->setText("");
            ui->eMailLineEdit->setText("");*/


    }
    else
    {
        QMessageBox::warning(this,"Erreur lors de l'ajout","Veuillez compléter tous les champs");
    }


}

void MainWindow::on_pushButton_reset_clicked()
{
    ui->cINLineEdit->setText("");
    ui->nomLineEdit->setText("");
    ui->prNomLineEdit->setText("");
    ui->eMailLineEdit->setText("");
}

void MainWindow::on_pushButton_details_clicked()
{

}

void MainWindow::on_pushButton_modifier_clicked()
{
    if (ui->pushButton_modifier->isChecked())
    {
        ui->pushButton_modifier->setDisabled(true);
        ui->pushButton_modifier->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("INVITES");
        tableModel->select();
        ui->tableView->setModel(tableModel);
    }
    else
    {
        ui->pushButton_modifier->setText("Modifier");
        ui->tableView->setModel(tmpinvite.afficher());

    }

}

void MainWindow::on_pushButton_supprimer_clicked()
{


    QItemSelectionModel *select = ui->tableView->selectionModel();

    int cin =select->selectedRows(0).value(0).data().toInt();

    if(tmpinvite.supprimer(cin))
    {
        ui->tableView->setModel(tmpinvite.afficher());
        ui->statusbar->showMessage("Invité supprimé");
     }


}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{

}
