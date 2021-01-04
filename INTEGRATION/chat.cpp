#include "chat.h"
#include "ui_chat.h"

chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    QHostAddress me("192.168.1.27");

    ui->setupUi(this);
    clientSocket=new QUdpSocket(this);
    clientSocketc=new QUdpSocket(this);
    clientSocketc->bind(me, 7000);
    connect(clientSocketc,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}

chat::~chat()
{
    delete ui;
}

void chat::on_sendButton_clicked()
{
    QString word=ui->lineEdit->text();
    ui->textBrowser->append(word);
    QByteArray buffer;
    buffer.resize(clientSocket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    buffer=word.toUtf8();
    clientSocketc->writeDatagram(buffer.data(), QHostAddress::Broadcast, 8001 );
}
void chat::readPendingDatagrams()
{
    while (clientSocketc->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(clientSocketc->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        clientSocketc->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
        ui->textBrowser->append(buffer.data());

    }

}


//Client side
/*#include "chat.h"
#include "ui_chat.h"

chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    QHostAddress me("192.168.1.18");
    ui->setupUi(this);
       socketServerc=new QUdpSocket(this);
       socketServer=new QUdpSocket(this);
       socketServer->bind(me, 8001);
       connect(socketServer,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}

chat::~chat()
{
    delete ui;
}

void chat::on_sendButton_clicked()
{


    QString word=ui->lineEdit->text();
    ui->textBrowser->append(word);
    QByteArray buffer;
    buffer=word.toUtf8();
    QHostAddress sender;
    quint16 senderPort;
    socketServer->writeDatagram(buffer.data(), QHostAddress::Broadcast, 7000 );

}

void chat::readPendingDatagrams()
{
    while (socketServer->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(socketServer->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socketServer->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
        ui->textBrowser->append(buffer.data());

    }

}*/

