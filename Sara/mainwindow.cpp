#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include "fournisseurs.h"
#include "produits.h"
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sound=new QSound(":/sound/music.wav");
    ui->tableView_Produits->setModel(tmpprod.afficher());
    ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());
    ui->lineEdit_Ref->setPlaceholderText("Reference ...");
    ui->lineEdit_quantite->setPlaceholderText("Quantite ...");
    ui->lineEdit_Prix->setPlaceholderText("Prix ...");
    ui->lineEdit_CIN->setPlaceholderText("CIN...");
    ui->lineEdit_RIB->setPlaceholderText("RIB");
    ui->lineEdit_tel->setPlaceholderText("Numero de telephone");

    ui->tableView_Produits->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_Produits->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView_Fournisseurs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_Fournisseurs->setSelectionMode(QAbstractItemView::SingleSelection);
this->setStyleSheet("background-color: rgb(137, 198, 240);");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_val_clicked()
{
            int reference = ui->lineEdit_Ref->text().toInt();
            int quantite = ui->lineEdit_quantite->text().toInt();
            QString type= ui->comboBox_Type->currentText();
            qreal prix= ui->lineEdit_Prix->text().toFloat();
            QDate datee = ui->dateEdit->date();
            produits p (reference,quantite,type,prix,datee);
            bool test=p.ajouter();

            if (test)
            {
                ui->tableView_Produits->setModel(tmpprod.afficher());
                ui->lineEdit_Ref->setText("");
                ui->lineEdit_quantite->setText("");
                ui->lineEdit_Prix->setText("");
                QMessageBox::information(nullptr,QObject::tr("OK"),
                                      QObject::tr("Ajout effectué .\n"),QMessageBox::Cancel);
            }
            else
{QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                       QObject::tr("Ajout non effectué .\n"),QMessageBox::Cancel);}
}
void MainWindow::on_pushButton_Supp_clicked()
{
    QItemSelectionModel *select = ui->tableView_Produits->selectionModel();

    int reference =select->selectedRows(0).value(0).data().toInt();

    if(tmpprod.supprimer(reference))
    {
        ui->tableView_Produits->setModel(tmpprod.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                              QObject::tr("suppression effectué .\n"),QMessageBox::Cancel);
     }

}
void MainWindow::on_pushButton_Modifier_clicked()
{
    if (ui->pushButton_Modifier->isChecked())
    {
        //ui->pushButton_Modifier->setDisabled(true);
        ui->pushButton_Modifier->setText("Modifier...");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("produits");
        tableModel->select();
        ui->tableView_Produits->setModel(tableModel);
    }
    else
    {
        ui->pushButton_Modifier->setText("Modifier");
        ui->tableView_Produits->setModel(tmpprod.afficher());

    }
}
void MainWindow::on_pushButton_Recherche_clicked()
{
    if (ui->comboBox->currentIndex()==0)
    {
        int reference=ui->lineEdit_Recherche->text().toInt();
        QSqlQueryModel *verif_reference=tmpprod.rechercher_reference(reference);
        if (verif_reference!=nullptr)
        {
            ui->tableView_Produits->setModel(verif_reference);

        }
    }
    else if (ui->comboBox->currentIndex()==1)
    {
        QString type;
        if (ui->radioButton_perissables->isChecked())
        type=ui->radioButton_perissables->text();
        else if (ui->radioButton_durables->isChecked())
        type=ui->radioButton_durables->text();

        QSqlQueryModel *verif_type=tmpprod.rechercher_type(type);
        if (verif_type!=nullptr)
        {
            ui->tableView_Produits->setModel(verif_type);
        }
    }

    else if (ui->comboBox->currentIndex()==2)
    {
        QDate datee=ui->dateEdit_recherche->date();
        QSqlQueryModel *verif_datee=tmpprod.rechercher_datee(datee);
        if (verif_datee!=nullptr)
        {
            ui->tableView_Produits->setModel(verif_datee);
        }

    }
    else if (ui->comboBox->currentIndex()==3)
    {
        int reference=ui->lineEdit_Recherche->text().toInt();
        QSqlQueryModel *verif_reference=tmpprod.rechercher_reference(reference);
        QDate datee=ui->dateEdit_recherche->date();
        QString type;
        if (verif_reference!=nullptr)
        {
            if (ui->radioButton_perissables->isChecked())
               type=ui->radioButton_perissables->text();
            else if (ui->radioButton_durables->isChecked())
                type=ui->radioButton_durables->text();
            QSqlQueryModel *verif_critere=tmpprod.rechercher_critere(reference,type,datee);
            if (verif_critere!=nullptr)
            {
                ui->tableView_Produits->setModel(verif_critere);
            }
        }
        else
            QMessageBox::warning(this,"Erreur","réessayer");

    }

}
void MainWindow::on_pushButton_afficher_clicked()
{
    ui->tableView_Produits->setModel(tmpprod.afficher());
}
void MainWindow::on_actionSound_clicked()

   {
     sound->play();
   }
void MainWindow::on_muteSound_clicked()

   {
     sound->stop();
   }
void MainWindow::on_pushButton_val_2_clicked()
{
            int CIN = ui->lineEdit_CIN->text().toInt();
            int telephone = ui->lineEdit_tel->text().toInt();
            QString type = ui->comboBox_type_f->currentText();
            int RIB = ui->lineEdit_RIB->text().toInt();

            fournisseurs f (CIN,telephone,type,RIB);
            bool test=f.ajouter_f();

            if (test)
            {
                ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());
                ui->lineEdit_CIN->setText("");
                ui->lineEdit_tel->setText("");
                ui->lineEdit_RIB->setText("");
                QMessageBox::information(nullptr,QObject::tr("OK"),
                                      QObject::tr("Ajout effectué .\n"),QMessageBox::Cancel);
            }
            else
{       QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                       QObject::tr("Ajout non effectué .\n"),QMessageBox::Cancel);}
}
void MainWindow::on_pushButton_supp_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_Fournisseurs->selectionModel();

    int CIN =select->selectedRows(0).value(0).data().toInt();

    if(tmpf.supprimer_f(CIN))
    {
        ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                              QObject::tr("suppression effectué .\n"),QMessageBox::Cancel);
     }
}


void MainWindow::on_pushButton_modifier_2_clicked()
{

    if (ui->pushButton_modifier_2->isChecked())
               {
                  // ui->pushButton_modifier->setDisabled(true);
                   ui->pushButton_modifier_2->setText("Modifiable");
                   QSqlTableModel *tableModel= new QSqlTableModel();
                   tableModel->setTable("fournisseurs");
                   tableModel->select();
                   ui->tableView_Fournisseurs->setModel(tableModel);
               }
               else
               {
                   ui->pushButton_modifier_2->setText("Modifier");
                   ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());

               }
}


    void MainWindow::on_pushButton_afficher_2_clicked()
    {
        ui->tableView_Fournisseurs->setModel(tmpf.afficher_f());
    }

void MainWindow::on_pushButton_rechercher_2_clicked()
{
    ui->tableView_Fournisseurs->setModel(tmpf.afficher_f(  ));
     QString CIN= ui->lineEdit_rechercher_2->text();
     ui->tableView_Fournisseurs->setModel(tmpf.rechercher_fournisseurs(CIN));
}



void MainWindow::on_pushButton_Exporter_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("liste_produits.pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        QSqlQuery q;

        q.prepare("SELECT * FROM produits ");
        q.exec();
        QString pdf="<br> <img src='C:/Users/lenovo/Documents/Gestion_stock/wedding bells.png' height='20' width='50'/> <h1  style='color:blue'>       LISTE DES PRODUITS  <br></h1>\n <br> <table>  <tr>  <th> REFERENCE </th>  <th> QUANTITE </th>  <th>TYPE </th>  <th> DATE  " ;


        while ( q.next()) {

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"    </td>  <td>    " +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"</td>             </td>" ;

        }
        doc.setHtml(pdf);
        doc.setPageSize(printer.pageRect().size());
        doc.print(&printer);
}
