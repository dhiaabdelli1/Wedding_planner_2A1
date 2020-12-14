#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDateEdit>
#include <QSqlQueryModel>

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
