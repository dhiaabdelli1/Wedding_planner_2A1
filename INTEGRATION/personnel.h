#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QString>

class personnel
{
    QString cin;
    QString nom;
    QString prenom;
    QString mobile;
    QString departement;
    QDate date_naissance;
    QString salaire;
    QString ref_dep;

public:
    personnel();

    personnel(QString,QString,QString,QString,QString,QDate,QString,QString);
    //int getCin(){return cin;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getMobile(){return mobile;}
    QString getDepartement(){return departement;}
    QDate getDate_naissance(){return date_naissance;}
    //QString getSalaire(){return salaire;}



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool update(QString,QString,QString,QString,QString,QDate,QString,QString);
    void creerpdf();
    bool ajouter_image(QString);



  QSqlQueryModel * chercher(QString r);



};

#endif // PERSONNEL_H
