#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collaborateur.h"
#include "service.h"
#include "dialog.h"
#include <QMessageBox>
#include <QDate>
#include <QSqlTableModel>
#include <QTableView>
#include <QTableWidgetItem>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(202,202,202);");



    MRE=QRegExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    ui->lineEdit_Nom->setPlaceholderText("Nom ...");
    ui->lineEdit_Telephone->setPlaceholderText("Téléphone ...");
    ui->lineEdit_Email->setPlaceholderText("E-mail ...");
    ui->lineEdit_Rib->setPlaceholderText("RIB ...");
    ui->lineEdit_Reference->setPlaceholderText("Référence ...");
    ui->lineEdit_type->setPlaceholderText("Type ...");
    ui->lineEdit_prix->setPlaceholderText("Prix ...");
    ui->tableView_colab->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_colab->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_service->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_service->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_service->setModel(tmpservice.afficher_service());
    ui->tableView_colab->setModel(tmpCollaborateur.afficher());




}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ajouter_clicked()
{

    QString nom= ui->lineEdit_Nom->text();
    int telephone= ui->lineEdit_Telephone->text().toInt();
    QString email= ui->lineEdit_Email->text();
    int rib= ui->lineEdit_Rib->text().toInt();
    QString reference= ui->lineEdit_Reference->text();
    QString service=ui->comboBox_2->currentText();

    collaborateur e(nom,telephone,email,rib,reference,service);

    bool verifier = MRE.exactMatch(ui->lineEdit_Email->text());


    if ( ui->lineEdit_Nom->text()!= "" &&
         ui->lineEdit_Telephone->text()!="" &&
         ui->lineEdit_Email->text()!= "" &&
         ui->lineEdit_Rib->text()!= "" &&
         ui->lineEdit_Reference->text() != "" )
    {
        if (!verifier)

        {
            QMessageBox::warning(nullptr, QObject::tr("Ajouter collaborateur"),
                        QObject::tr("Vérifier E-mail ! .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {

    QString nom= ui->lineEdit_Nom->text();
    int telephone= ui->lineEdit_Telephone->text().toInt();
    QString email= ui->lineEdit_Email->text();
    int rib= ui->lineEdit_Rib->text().toInt();
    QString reference= ui->lineEdit_Reference->text();
    QString service=ui->comboBox_2->currentText();

    collaborateur e(nom,telephone,email,rib,reference,service);

            bool test=e.ajouter();
            if(test)

            {
                ui->tableView_colab->setModel(tmpCollaborateur.afficher());

                ui->lineEdit_Nom->setText("");
                ui->lineEdit_Telephone->setText("");
                ui->lineEdit_Email->setText("");
                ui->lineEdit_Rib->setText("");
                ui->lineEdit_Reference->setText("");

                QMessageBox::information(nullptr, QObject::tr("Ajouter collaborateur"),
                            QObject::tr("Collaborateur ajouté.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("Ajouter collaborateur"),
                            QObject::tr("Ajout echoué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
         }


    }
    else
    {
        QMessageBox::warning(nullptr, QObject::tr("Ajouter collaborateur"),
                    QObject::tr("Ajout echoué ! Cases vides ! .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_supprimer_clicked()
{
    /*QItemSelectionModel *select = ui->tableView_colab->selectionModel();

      int rib=select->selectedRows(0).value(0).data().toInt();

       if(tmpCollaborateur.supprimer(rib))
       {
           ui->tableView_colab->setModel(tmpCollaborateur.afficher());
           ui->statusbar->showMessage("Collaborateur supprimé");
        }*/

    QString reference= ui->lineEdit_Reference->text();
    bool test=tmpCollaborateur.supprimer(reference);
    if(test)
    {
        ui->tableView_colab->setModel(tmpCollaborateur.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer collaborateur"),
                    QObject::tr("Collaborateur supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Supprimer collaborateur"),
                    QObject::tr("Suppression echoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}




void MainWindow::on_pushButton_ajouterS_clicked()
{
    QString type= ui->lineEdit_type->text();
    QDate date_service= ui->dateEdit->date();
    int prix= ui->lineEdit_prix->text().toInt();
    QString proprietaire;
    bool b=ui->radioButton_e->isChecked();
   if (b)
   { proprietaire="Entreprise";}
   else
     { proprietaire="Free-lance"; }


    service e(type,date_service,prix,proprietaire);

            bool test=e.ajouter_service();
            if(test)
            {
                ui->tableView_service->setModel(tmpservice.afficher_service());
                QMessageBox::information(nullptr, QObject::tr("Ajouter service"),
                            QObject::tr("service ajouté.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("Ajouter service"),
                            QObject::tr("Ajout echoué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void MainWindow::on_pushButton_supprimerS_clicked()
{
    /*QItemSelectionModel *select = ui->tableView_service->selectionModel();

       QString type =select->selectedRows(0).value(0).data().toString();

       if(tmpservice.supprimer_service(type))
       {
           ui->tableView_service->setModel(tmpservice.afficher_service());
           ui->statusbar->showMessage("service supprimé");
       }*/

   QString type= ui->lineEdit_type->text();
    bool test=tmpservice.supprimer_service(type);
    if(test)
    {
        ui->tableView_service->setModel(tmpservice.afficher_service());
        QMessageBox::information(nullptr, QObject::tr("Supprimer service"),
                    QObject::tr("service supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Supprimer service"),
                    QObject::tr("Suppression echoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_clicked()
{


    /*if (ui->modifier->isChecked())
       {
           ui->modifier->setDisabled(true);
           ui->modifier->setText("Modifiable");
           QSqlTableModel *tableModel= new QSqlTableModel();
           tableModel->setTable("collaborateur");
           tableModel->select();
           ui->tableView_colab->setModel(tableModel);
       }
       else
       {
           ui->modifier->setText("Modifier");
           ui->tableView_colab->setModel(tmpCollaborateur.afficher());

       }*/

        QString nom= ui->lineEdit_Nom->text();
        int telephone=ui->lineEdit_Telephone->text().toInt();
        QString email=ui->lineEdit_Email->text();
        int rib= ui->lineEdit_Rib->text().toInt();
        QString reference=ui->lineEdit_Reference->text();
         QString service=ui->comboBox_2->currentText();

          bool test = tmpCollaborateur.modifier(nom,telephone,email,rib,reference,service);
          if(test)

          {
               ui->tableView_colab->setModel(tmpCollaborateur.afficher());
              QMessageBox::information(nullptr, QObject::tr("Modifier collaborateur"),
                          QObject::tr("Collaborateur modifié\n"
          "Click Cancel to exit."), QMessageBox::Cancel);}
          else
          {
              QMessageBox::information(nullptr, QObject::tr("Modifier collaborateur"),
                          QObject::tr("Modification echoué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
          }


}


void MainWindow::on_pushButton_modifierS_clicked()
{

    QString type= ui->lineEdit_type->text();

    QDate date_service=ui->dateEdit->date();
    int prix= ui->lineEdit_prix->text().toInt();
    QString proprietaire;
    bool b=ui->radioButton_e->isChecked();
   if (b)
   { proprietaire="Entreprise";}
   else
     { proprietaire="Free-lance"; }


      bool test = tmpservice.modifier_service(type,date_service,prix,proprietaire);
      if(test)

      {
           ui->tableView_service->setModel(tmpservice.afficher_service());
          QMessageBox::information(nullptr, QObject::tr("Modifier service"),
                      QObject::tr("Service modifié\n"
      "Click Cancel to exit."), QMessageBox::Cancel);}
      else
      {
          QMessageBox::information(nullptr, QObject::tr("Modifier service"),
                      QObject::tr("Modification echoué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }

}

void MainWindow::on_reset_clicked()
{
     ui->lineEdit_Nom->setText("");
     ui->lineEdit_Telephone->setText("");
     ui->lineEdit_Email->setText("");
     ui->lineEdit_Rib->setText("");
     ui->lineEdit_Reference->setText("");
}

void MainWindow::on_resetS_clicked()
{
    ui->lineEdit_type->setText("");
    ui->lineEdit_prix->setText("");

}





void MainWindow::on_checkBox_7_clicked()
{

        {QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();


               model->setQuery("select * from service order by prix asc");

               model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("dat"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("proprietaire"));

                        ui->tableView_service->setModel(model);
                        ui->tableView_service->show();
                        msgBox.setText("Tri affecté sur le prix.");
                        msgBox.exec();

        }
    }



void MainWindow::on_checkBox_6_clicked()
{
    {QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


           model->setQuery("select * from service order by type");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_service"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("proprietaire"));

                    ui->tableView_service->setModel(model);
                    ui->tableView_service->show();
                    msgBox.setText("Tri affecté sur le type.");
                    msgBox.exec();

    }
}



void MainWindow::on_checkBox_5_clicked()
{
    {QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


           model->setQuery("select * from service order by date_service");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_service"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("proprietaire"));

                    ui->tableView_service->setModel(model);
                    ui->tableView_service->show();

                    msgBox.exec();

    }
}


void MainWindow::on_rechercher_colab_clicked()
{
   if (ui->checkBox_rib->isChecked())
   { int rib=ui->rech_rib->text().toInt();
       QSqlQueryModel *verif=tmpCollaborateur.rechercher_rib(rib);
       if (verif!=nullptr)
       {
           ui->tableView_colab->setModel(verif);
           QMessageBox::information(nullptr, QObject::tr("Recherche collaborateur"),
                       QObject::tr("Recherche affecté sur le RIB.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }
    }

   if (ui->checkBox_ref->isChecked())
   { QString reference=ui->rech_ref->text();
       QSqlQueryModel *verif=tmpCollaborateur.rechercher_ref(reference);
       if (verif!=nullptr)
       {
           QMessageBox msgBox ;
           ui->tableView_colab->setModel(verif);
           msgBox.setText("recherche bien affecté sur Référence");
       }
    }
   if (ui->checkBox_service->isChecked())
   { QString service=ui->rech_service->currentText();
       QSqlQueryModel *verif=tmpCollaborateur.rechercher_service(service);
       if (verif!=nullptr)
       {
           QMessageBox msgBox ;
           ui->tableView_colab->setModel(verif);
           msgBox.setText("recherche bien affecté sur Service");
       }
    }
   if ((ui->checkBox_rib->isChecked())&&(ui->checkBox_ref->isChecked()))
   {
       int rib=ui->rech_rib->text().toInt();
       QString reference=ui->rech_ref->text();

                   if (rib!=0)
                     {
                       if (reference!="")
                          {
                   QSqlQueryModel *verif=tmpCollaborateur.rechercher_RibRef(rib,reference);
                   if (verif!=nullptr)
                   {   QMessageBox msgBox ;
                       ui->tableView_colab->setModel(verif);
                       msgBox.setText("recherche bien affecté sur Rib et référence");
                   }
                       } else
                           QMessageBox::warning(this,"erreur","Champ reference est vide");
                   } else
                       QMessageBox::warning(this,"erreur","Champ rib est vide");
   }
   if ((ui->checkBox_rib->isChecked())&&(ui->checkBox_service->isChecked()))
   {
       int rib=ui->rech_rib->text().toInt();
      QString service=ui->rech_service->currentText();

                   if (rib!=0)
                     {
                   QSqlQueryModel *verif=tmpCollaborateur.rechercher_RibSer(rib,service);
                   if (verif!=nullptr)
                   {   QMessageBox msgBox ;
                       ui->tableView_colab->setModel(verif);
                       msgBox.setText("recherche bien affecté sur Rib et Service");
                   }

                   } else
                       QMessageBox::warning(this,"erreur","Champ rib est vide");
   }
   if ((ui->checkBox_ref->isChecked())&&(ui->checkBox_service->isChecked()))
   {
      QString reference=ui->rech_ref->text();
      QString service=ui->rech_service->currentText();

                   if (reference!="")
                     {
                   QSqlQueryModel *verif=tmpCollaborateur.rechercher_RefSer(reference,service);
                   if (verif!=nullptr)
                   {   QMessageBox msgBox ;
                       ui->tableView_colab->setModel(verif);
                       msgBox.setText("recherche bien affecté sur Référence et Service");
                   }

                   } else
                       QMessageBox::warning(this,"erreur","Champ Référence est vide");
   }


if ((ui->checkBox_rib->isChecked())&&(ui->checkBox_service->isChecked())&&(ui->checkBox_ref->isChecked()))
{

    QString service=ui->rech_service->currentText();
    int rib=ui->rech_rib->text().toInt();
    QString reference=ui->rech_ref->text();

                if (rib!=0)
                  {
                    if (reference!="")
                       {
                QSqlQueryModel *verif=tmpCollaborateur.rechercher_tous(rib,reference,service);
                if (verif!=nullptr)
                {
                    QMessageBox msgBox ;
                    ui->tableView_colab->setModel(verif);
                    msgBox.setText("recherche bien affecté sur les 3 critéres");
                }
                    } else
                        QMessageBox::warning(this,"erreur","Champ reference est vide");
                } else
                    QMessageBox::warning(this,"erreur","Champ rib est vide");

} // else QMessageBox::warning(this,"erreur","Aucun critére n'est coché");
}



void MainWindow::on_reafficher_colab_clicked()
{
    ui->rech_rib->setText("");
    ui->rech_ref->setText("");
  ui->tableView_colab->setModel(tmpCollaborateur.afficher());
}




/*void MainWindow::on_envoyer_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
        QString email_recipient =select->selectedRows(4).value(0).data().toString();
        QString nom_recipient =select->selectedRows(1).value(0).data().toString();
        QString sexe_recipient =select->selectedRows(5).value(0).data().toString();


        QDialog *d=new Dialog(email_recipient,nom_recipient,sexe_recipient,this);
        d->show();
        d->exec();
}*/

void MainWindow::on_exporter_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
       if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("liste_collaborateurs.pdf"); }

       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setPaperSize(QPrinter::A4);
       printer.setOutputFileName(fileName);

       QTextDocument doc;
       QSqlQuery q;
       q.prepare("SELECT * FROM collaborateur ");
       q.exec();
       QString pdf="<br> <img src='D:/Documents/ftf/CC.png' height='50' width='150'/> <h1  style='color:red'>       LISTE DES COLLABORATEURS  <br></h1>\n <br> <table>  <tr>  <th> NOM </th> <th> TELEPHONE </th> <th> EMAIL </th> <th> RIB  </th> <th>SERVICE </th>  </tr>" ;


       while ( q.next()) {

           pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"</td>  <td>" +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"--------"+"</td>       <td>"+q.value(4).toString()+"       </td>" ;

       }
       doc.setHtml(pdf);
       doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
       doc.print(&printer);

}

void MainWindow::on_envoyer_clicked()
{

    QItemSelectionModel *select = ui->tableView_colab->selectionModel();

    QString email =select->selectedRows(3).value(0).data().toString();
    QString nom=select->selectedRows(1).value(0).data().toString();
    QString reference =select->selectedRows(5).value(0).data().toString();


    QDialog *d=new Dialog(email,nom,reference,this);
    d->show();
    d->exec();
}



void MainWindow::on_radioButton_triType_clicked()
{
    {QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


           model->setQuery("select * from service order by type");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_service"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("proprietaire"));

                    ui->tableView_service->setModel(model);
                    ui->tableView_service->show();
                    msgBox.setText("Tri affecté sur le type.");
                    msgBox.exec();

    }
}

void MainWindow::on_radioButton_triPrix_clicked()
{

    {QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


           model->setQuery("select * from service order by prix asc");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("dat"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("proprietaire"));

                    ui->tableView_service->setModel(model);
                    ui->tableView_service->show();
                    msgBox.setText("Tri affecté sur le prix.");
                    msgBox.exec();

    }
}

void MainWindow::on_radioButton_triDate_clicked()
{
    {QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


           model->setQuery("select * from service order by date_service");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_service"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("proprietaire"));

                    ui->tableView_service->setModel(model);
                    ui->tableView_service->show();

                    msgBox.exec();

    }
}
