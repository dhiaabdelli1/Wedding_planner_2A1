#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include "smtp.h"
#include "stat_combo.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QVariant>
#include <QFileDialog>
#include <QTextBrowser>
#include <QPixmap>
#include <QLabel>
#include <QDesktopServices>
#include<QDebug>

#include<QSqlTableModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLineSeries>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
mail_regex=QRegExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
   setWindowTitle("Wedding");
    setWindowIcon(QIcon("C:\\Users\\houba\\Downloads\\logo.jpg"));
this->setStyleSheet("background-color: rgb(255,192,203);");
    ui->setupUi(this);
    ui->tableView->setModel(tempclient.afficher());

    ui->tableView_2->setModel(tempreservation.afficher());
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    //for email tab
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
   /* player= new QMediaPlayer;
    vw=new QVideoWidget;
QString chemin="C:\\Users\\houba\\Downloads\\";
QDir chedir(chemin);
    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",chemin,"Excel Files(*.mp4)");


    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,300,400);
    vw->show();
player->play();*/
   /* player = new QMediaPlayer;
    // ...
    player->setMedia(QUrl::fromLocalFile("C:\\Users\\houba\\Downloads\\kda.mp3"));
    player->setVolume(100);
    player->play();*/
    player=new QMediaPlayer(this);
    anim = new QPropertyAnimation(ui->groupBox,"maximumWidth");
    anim->setDuration(3000);
    anim->setStartValue(10); //find how to get get default value
    anim->setEndValue(1026);
QEasingCurve curve;
curve.setType(QEasingCurve::OutBounce);
    anim->setEasingCurve(curve);

anim->start();
anim2 = new QPropertyAnimation(ui->groupBox_6,"maximumWidth");
anim2->setDuration(3000);
anim2->setStartValue(10); //find how to get get default value
anim2->setEndValue(554);
QEasingCurve curve1;
curve1.setType(QEasingCurve::OutBounce);
anim2->setEasingCurve(curve1);

anim2->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{ MainWindow w;

bool mail_verif = mail_regex.exactMatch(ui->mailPartenaire1LineEdit->text());
    int CIN= ui->LineEditp1->text().toInt();
    QString nom= ui->prNomPartenaire1LineEdit->text();
    QString prenom= ui->nomPartenaire1LineEdit->text();
    QDate date_naissance = ui->dateEdit_2->date();
    QString mail=ui->mailPartenaire1LineEdit->text();
    QString telephone=ui->tLPhonePartenaire1LineEdit->text();

    if (!mail_verif)
    {
        QMessageBox::warning(this,"Erreur lors de l'ajout","E-mail invalid");

    }
    else
    {
        QString mail=ui->mailPartenaire1LineEdit->text();

    }
    client c(CIN,nom,prenom,date_naissance,telephone,mail);
    bool test=c.ajouter();
    if(test)
    {
       // w.show();
       /* QMessageBox::information(nullptr, QObject::tr("ajout client"),
                    QObject::tr("ajout réussi\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/
        player->setMedia(QUrl::fromLocalFile("C:\\Users\\houba\\Downloads\\clic.mp3"));


        player->play();
ui->LineEditp1->clear();
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

void MainWindow::on_pushButton_4_clicked()
{


        if (ui->pushButton_4->isChecked())
        {
            //ui->pushButton_4->setDisabled(true);
            ui->pushButton_4->setText("Modifiable");
            QSqlTableModel *tableModel= new QSqlTableModel();
            tableModel->setTable("CLIENT");

            tableModel->select();
            ui->tableView->setModel(tableModel);


        }
        else
        {
            ui->pushButton_4->setText("modifier client");
            ui->tableView->setModel(tempclient.afficher());

        }



}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

    if (arg1=="")
    {
     ui->tableView->setModel(tempclient.afficher());
    }
    else
    {
    ui->tableView->setModel(tempclient.rechercheclient(arg1));
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index==0)
        {
              ui->tableView->setModel(tempclient.afficher());
        }
        else
        {
              ui->tableView->setModel(tempclient.triclient(index));
        }
}

//void MainWindow::on_pushButton_5_clicked()
//{
//    {
//        {
//            /*  QPrinter printer;
//              QString doc;

//              printer.setPrinterName("printer1");
//              QPrintDialog print_dialog(&printer,this);
//             if(print_dialog.exec()== QDialog::Rejected) return ;

//               ui->text_id-> */


//              QString strStream;
//              QTextStream out(&strStream);

//              const int rowCount = ui->tableView->model()->rowCount();
//              const int columnCount = ui->tableView->model()->columnCount();

//              out <<  "<html>\n"
//                  "<head>\n"
//                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
//                  <<  QString("<title>%1</title>\n").arg("col1")
//                  <<  "</head>\n"
//                  "<body bgcolor=#ffffff link=#5000A0>\n"
//                  "<table border=1 cellspacing=0 cellpadding=2>\n";

//              // headers
//              out << "<thead><tr bgcolor=#f0f0f0>";
//              for (int column = 0; column < columnCount; column++)
//                  if (!ui->tableView->isColumnHidden(column))
//                      out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
//              out << "</tr></thead>\n";

//              // data table
//              for (int row = 0; row < rowCount; row++) {
//                  out << "<tr>";
//                  for (int column = 0; column < columnCount; column++) {
//                      if (!ui->tableView->isColumnHidden(column)) {
//                          QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
//                          out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
//                      }
//                  }
//                  out << "</tr>\n";
//              }
//              out <<  "</table>\n"
//                  "</body>\n"
//                  "</html>\n";

//              QTextDocument *document = new QTextDocument();
//              document->setHtml(strStream);

//             QPrinter printer;

//              QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
//              if (dialog->exec() == QDialog::Accepted) {
//                  document->print(&printer);
//              }


//    }
//   }


void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mohamediheb.berraies@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("mohamediheb.berraies@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("mohamediheb.berraies@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
void MainWindow::on_actionplay_video_triggered()
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;

    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");


    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{



    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        //document->print(&printer);
        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
            if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(fileName);

            QPainter painter;
            painter.begin (&printer);

         //   QImage img (1, 6, QImage::Format_ARGB32);
          /* img.setPixelColor (0,0,QColor (Qt::red));
            img.setPixelColor (0,1,QColor (Qt::red));*/
            QPixmap pm("C:/Users/houba/Pictures/téléchargement.jpg");
            painter.drawPixmap(0, 0, pm);
           /* img.setPixelColor (0,2,QColor (Qt::green));
            img.setPixelColor (0,3,QColor (Qt::green));
            img.setPixelColor (0,4,QColor (Qt::blue));
            img.setPixelColor (0,5,QColor (Qt::blue));*/


            // Increase the apparent size of the image

            //painter.drawPixmap (QRect (0,0,1, 6), pm);
            QString strStream;
            QTextStream out(&strStream);

            const int rowCount = ui->tableView->model()->rowCount();
            const int columnCount = ui->tableView->model()->columnCount();

            out <<  "<html>\n"
                "<head>\n"
                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%1</title>\n").arg("Title")
                <<  "</head>\n"
                "<body bgcolor=#ffffff link=#5000A0>\n"
                "<table border=1 cellspacing=0 cellpadding=2>\n";

            // headers
            out << "<thead><tr bgcolor=#f0f0f0>";
            for (int column = 0; column < columnCount; column++)
                if (!ui->tableView->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            // data table
            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->tableView->isColumnHidden(column)) {
                        QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                    }
                }
                out << "</tr>\n";
            }
            out <<  "</table>\n"
                "</body>\n"
                "</html>\n";

            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);

           // QPrinter printer;

            QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
            if (dialog->exec() == QDialog::Accepted) {
                document->print(&printer);
            }
            QTransform tform(58.68,0,0,-58.68,268.74,384.48);
            painter.setTransform (tform);

           // delete document;

            painter.end ();

    }

   // delete document;

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{QItemSelectionModel *select = ui->tableView->selectionModel();
    QString email_recipient =select->selectedRows(3).value(0).data().toString();
    ui->rcpt->setText(email_recipient);
}

void MainWindow::on_pushButton_5_clicked()
{

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("liste_clients.pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);
        QPainter painter;

        QTextDocument doc;
        QSqlQuery q;
        q.prepare("SELECT * FROM CLIENT ");
        q.exec();

        QString pdf="<br> <img src='C:/Users/houba/Downloads/logo.jpg' height='80' width='144'/> <h1  style='color:pink'>       LISTE DES INVITES  <br></h1>\n <br> <table>  <tr>  <th> CIN </th> <th> NOM </th> <th> PRENOM </th> <th> DATE DE NAISSANCE  </th> <th>E-MAIL </th>  </tr>" ;


        while ( q.next()) {

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"</td>  <td>" +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"--------"+"</td>       <td>"+q.value(4).toString()+"       </td>" ;

        }
        doc.setHtml(pdf);
       // doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);

}





void MainWindow::on_stat_clicked()
{
    stat_combo *s = new stat_combo();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();
}




void MainWindow::on_comboBox_activated(int index)
{

}

void MainWindow::on_pushButton_7_clicked()
{
    MainWindow w;

    int reference= ui->typeLineEdit->text().toInt();
    QDate date_reservation = ui->dateEdit->date();

    QString prix= ui->prixLineEdit->text();
    int nb_invites=ui->nombreInvitSLineEdit->text().toInt();

        QString localisation= ui->localisationLineEdit->text();

        qDebug()<<reference<<date_reservation<<prix<<nb_invites<<localisation;

        reservation r(reference,date_reservation,prix,nb_invites,localisation);
        bool test=r.ajouter();
        if(test)
        {
           // w.show();
           /* QMessageBox::information(nullptr, QObject::tr("ajout client"),
                        QObject::tr("ajout réussi\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);*/
            player->setMedia(QUrl::fromLocalFile("C:\\Users\\houba\\Downloads\\clic.mp3"));


            player->play();

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("ajout échoué"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_tabWidget_3_currentChanged(int index)
{
    ui->tableView_2->setModel(tempreservation.afficher());

}

void MainWindow::on_pushButton_8_clicked()
{
    QItemSelectionModel *select=ui->tableView_2->selectionModel();
    int ref =select->selectedRows(0).value(0).data().toInt();
    bool test=tempreservation.supprimer(ref);

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
    ui->tableView_2->setModel(tempreservation.afficher());


}



void MainWindow::on_lineEdit_2_textEdited(const QString &arg1)
{
    if (arg1=="")
    {
     ui->tableView_2->setModel(tempreservation.afficher());
    }
    else
    {
    ui->tableView_2->setModel(tempreservation.recherchereservation(arg1));
    }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if (index==0)
        {
              ui->tableView_2->setModel(tempreservation.afficher());
        }
        else
        {
              ui->tableView_2->setModel(tempreservation.trireservation(index));
        }
}

void MainWindow::on_pushButton_9_clicked()
{
    if (ui->pushButton_9->isChecked())
    {
        //ui->pushButton_4->setDisabled(true);
        ui->pushButton_9->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("RESERVATION");

        tableModel->select();
        ui->tableView_2->setModel(tableModel);


    }
    else
    {
        ui->pushButton_4->setText("modifier reservation");
        ui->tableView_2->setModel(tempreservation.afficher());

    }



}

