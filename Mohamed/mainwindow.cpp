#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collaborateur.h"
#include "service.h"
#include <QMessageBox>
#include <QDate>
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
    ui->tableView_service->setModel(tmpservice.afficher_service());
    ui->tableView_colab->setModel(tmpCollaborateur.afficher());
    //ui->tabView_rech->setModel(tmpCollaborateur.afficher());
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
    QDate dat= ui->dateEdit->date();
    float prix= ui->lineEdit_prix->text().toInt();
    QString proprietaire;
    bool b=ui->radioButton_e->isChecked();
   if (b)
   { proprietaire="entreprise";}
   else
     { proprietaire="free-lance"; }


    service e(type,dat,prix,proprietaire);

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

    QDate dat=ui->dateEdit->date();
    float prix= ui->lineEdit_prix->text().toInt();
    QString proprietaire;
    bool b=ui->radioButton_e->isChecked();
   if (b)
   { proprietaire="entreprise";}
   else
     { proprietaire="free-lance"; }


      bool test = tmpservice.modifier_service(type,dat,prix,proprietaire);
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

void MainWindow::on_lineEdit_rechC_textChanged(const QString &)
{
    collaborateur c;
    ui->tabView_rech->setModel(c.rechercher_collaborateur(ui->lineEdit_rechC->text()));

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

                        ui->tableView->setModel(model);
                        ui->tableView->show();
                        msgBox.setText("Tri avec succés.");
                        msgBox.exec();

        }
    }



void MainWindow::on_checkBox_6_clicked()
{
    {QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


           model->setQuery("select * from service order by type");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("dat"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("proprietaire"));

                    ui->tableView->setModel(model);
                    ui->tableView->show();
                    msgBox.setText("Tri avec succés.");
                    msgBox.exec();

    }
}

void MainWindow::on_checkBox_5_clicked()
{
    {QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();


           model->setQuery("select * from service order by dat");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("dat"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("proprietaire"));

                    ui->tableView->setModel(model);
                    ui->tableView->show();
                    msgBox.setText("Tri avec succés.");
                    msgBox.exec();

    }
}
