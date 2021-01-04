#include "chat.h"
#include "ui_chat.h"

chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    QHostAddress me("192.168.34.246");
    ui->setupUi(this);
    socketServerc=new QUdpSocket(this);
    socketServer=new QUdpSocket(this);
    socketServer->bind(QHostAddress::LocalHost, 8001);

    connect(socketServer,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));

//    clientSocket=new QUdpSocket(this);
//    clientSocketc=new QUdpSocket(this);
//    clientSocketc->bind(QHostAddress::LocalHost, 7000);
//    connect(clientSocketc,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}

chat::~chat()
{
    delete ui;
}

void chat::on_sendButton_clicked()
{



    QString word=ui->lineEdit->text();
    ui->textBrowser->append("me: "+word);

    QFuture<bool> future= QtConcurrent::run(this,&chat::send,word);

//    ui->textBrowser->append("me: "+word);
//    QByteArray buffer;
//    buffer=word.toUtf8();
//    QHostAddress sender;
//    quint16 senderPort;
//    //socketServerc->writeDatagram(buffer.data(), QHostAddress::LocalHost, 7000 );
//    socketServerc->writeDatagram(buffer.data(), QHostAddress::LocalHost, 7000 );

}

bool chat::send(QString word)
{

    QByteArray buffer;
    buffer=word.toUtf8();
    QHostAddress sender;
    quint16 senderPort;
    //socketServerc->writeDatagram(buffer.data(), QHostAddress::LocalHost, 7000 );
    socketServerc->writeDatagram(buffer.data(), QHostAddress::LocalHost, 7000 );
}

void chat::readPendingDatagrams()
{
    QString word;
    QFuture<QString> future= QtConcurrent::run(this,&chat::read,word);
    ui->textBrowser->append(future.result());
//    while (socketServer->hasPendingDatagrams()) {
//        QByteArray buffer;
//        buffer.resize(socketServer->pendingDatagramSize());
//        QHostAddress sender;
//        quint16 senderPort;
//        socketServer->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
//        //ui->textBrowser->append(buffer.data());

//        qDebug() << sender;
//        qDebug() << senderPort;

//    }

}

QString chat::read(QString)
{
    while (socketServer->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(socketServer->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socketServer->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
        //ui->textBrowser->append(buffer.data());

        qDebug() << sender;
        qDebug() << senderPort;

    }
}


//void chat::on_sendButton_clicked()
//{
//    QString word=ui->lineEdit->text();
//    ui->textBrowser->append(word);
//    QByteArray buffer;
//    buffer.resize(clientSocket->pendingDatagramSize());
//    QHostAddress sender;
//    quint16 senderPort;
//    buffer=word.toUtf8();
//    clientSocket->writeDatagram(buffer.data(), QHostAddress::LocalHost, 8001 );
//}
//void chat::readPendingDatagrams()
//{
//    while (clientSocketc->hasPendingDatagrams()) {
//        QByteArray buffer;
//        buffer.resize(clientSocketc->pendingDatagramSize());
//        QHostAddress sender;
//        quint16 senderPort;
//        clientSocketc->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
//        ui->textBrowser->append(buffer.data());

//    }

//}
