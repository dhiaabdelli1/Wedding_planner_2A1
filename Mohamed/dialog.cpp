#include "dialog.h"
#include "ui_dialog.h"
#include "smtp.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

       ui->server->setText("smtp.gmail.com");
       ui->port->setText("465");
}
Dialog::Dialog(QString,QString,QString,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QString contenu="Contenu";
    ui->setupUi(this);
    ui->server->setText("smtp.gmail.com");
    ui->port->setText("465");

    ui->uname->setText("barkia.medit@gamil.com");
    ui->passwd->setText("Dpstream1");
    ui->passwd->setEchoMode(QLineEdit::Password);

}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->passwd->text(), ui->server->text(), ui->port->text().toInt());

    smtp->sendMail(ui->uname->text(), ui->recipient->text() , "subject" ,ui->message->toPlainText());

}
