#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDateEdit>
#include <QSqlQueryModel>

#include "reservation.h"

class client
{
public:
    client();
    client(int,QString,QString,QDate,QString,QString,float);
    int getCIN(){return CIN;}
    QString getNOM(){return nom;}
    QString getPRENOM(){return prenom;}
    QDate getDATE(){return date;}
    QSqlQueryModel * rechercheclient(const QString &id);
    QSqlQueryModel* triclient(int);
    QSqlQueryModel *trier(QString crit,QString ordre);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
private:
    int CIN;
    QString nom,prenom,mail,telephone;
    QDate date;
    float budget;

};

#endif // CLIENT_H
