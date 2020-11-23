#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDateEdit>
#include <QSqlQueryModel>

class client
{
public:
    client();
 client(int,QString,QString);
 int getCIN(){return CIN;}
 QString getNOM(){return nom;}
 QString getPRENOM(){return prenom;}


 bool ajouter();
 QSqlQueryModel * afficher();
 bool supprimer(int);
private:
    int CIN;
    QString nom,prenom;

};

#endif // CLIENT_H
