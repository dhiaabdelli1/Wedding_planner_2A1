#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QUdpSocket>

namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();

private slots:
    void on_sendButton_clicked();
    void readPendingDatagrams();

private:
    Ui::chat *ui;
//    QUdpSocket *socketServer;
//    QUdpSocket *socketServerc;
    QUdpSocket *clientSocket;
    QUdpSocket *clientSocketc;

};

#endif // CHAT_H
