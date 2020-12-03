#ifndef RESERVATION_H
#define RESERVATION_H
#include <QString>
#include <QDateEdit>
#include <QSqlQueryModel>

class reservation
{
public:
    reservation();
 reservation(int,QDate,QString,int,QString);
 int getREFERENCE(){return reference;}
 QString getPRIX(){return prix;}
 int getNBINV(){return nb_invites;}
 QString getLOCALISATION(){return localisation;}
 QDate getDATE(){return date_reservation;}
QSqlQueryModel * recherchereservation(const QString &id);
QSqlQueryModel* trireservation(int);

 bool ajouter();
 QSqlQueryModel * afficher();
 bool supprimer(int);
private:
 QString prix;
 int nb_invites,reference;
 QString localisation;
 QDate date_reservation;
};

#endif // RESERVATION_H
