#include "dialog.h"
#include "ui_dialog.h"
#include "smtp.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


    QPixmap bkgnd("D:/Users/dhiaa/Desktop/gestion_invités/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

}
Dialog::Dialog(QString e,QString n,QString s,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QString contenu="Contenu";
    ui->setupUi(this);

    ui->recipient->setText(e);
    ui->uname->setText("dhia.abdelli1@esprit.tn");
    ui->passwd->setText("Dpstream1");
    ui->passwd->setEchoMode(QLineEdit::Password);

    if (s=="Homme")
    {
        ui->message->setText("Cher Monsieur "+n+",\n\n"+contenu+"\n\n"+"Cordialement,\n");
    }
    else if (s=="Femme")
    {
        ui->message->setText("Chère Madame "+n+",\n\n"+contenu+"\n\n"+"Cordialement,\n");
    }

}
Dialog::~Dialog()
{
    delete ui;

}

void Dialog::on_pushButton_2_clicked()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->passwd->text(), "smtp.gmail.com", 465);

    smtp->sendMail(ui->uname->text(), ui->recipient->text() , ui->subjectLineEdit->text() ,ui->message->toPlainText());

    /*if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );*/

}
