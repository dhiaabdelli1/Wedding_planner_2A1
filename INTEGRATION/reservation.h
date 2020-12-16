#ifndef RESERVATION_H
#define RESERVATION_H
#include <QString>
#include <QDateEdit>
#include <QSqlQueryModel>

class reservation
{
public:
    reservation();
    reservation(QString,QDate,float,int,QString,QString);
    QString getREFERENCE(){return reference;}
    float getPRIX(){return prix;}
    int getNBINV(){return nb_invites;}
    QString getLOCALISATION(){return localisation;}
    QDate getDATE(){return date_reservation;}
    QSqlQueryModel * recherchereservation(const QString &id);
    QSqlQueryModel* trireservation(int);
    QSqlQueryModel *trier(QString crit,QString ordre);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool supprimer_cin(QString);
private:
    float prix;
    int nb_invites;
    QString localisation,reference;
    QDate date_reservation;
    QString cin_client;
};

#endif // RESERVATION_H
