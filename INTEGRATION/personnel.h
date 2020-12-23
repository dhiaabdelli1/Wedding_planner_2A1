#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QString>

class personnel
{
    int cin,c;
    QString nom;
    QString prenom;
    QString mobile;
    QString departement;
    QDate date_naissance;
    QString salaire;
    QString ref_dep;
public:
    personnel();

    personnel(int,QString,QString,QString,QString,QDate,QString,QString);
    int getCin(){return cin;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getMobile(){return mobile;}
    QString getDepartement(){return departement;}
    QDate getDate_naissance(){return date_naissance;}
    QString getSalaire(){return salaire;}
    QString getRef_dep(){return ref_dep;}


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool update(int,QString,QString,QString,QString,QDate,QString,QString);
    void creerpdf();



  QSqlQueryModel * chercher(QString r);



};

#endif // PERSONNEL_H
