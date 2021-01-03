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
    QString code_rfid;
    QString entree;
    QString num_entree;

public:
    personnel();

    personnel(QString,QString,QString,QString,QString,QDate,QString,QString,QString);
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
    bool update(QString,QString,QString,QString,QString,QDate,QString,QString,QString);
    void creerpdf();
    bool ajouter_image(QString);
    bool update_rfid(QString,QString);

    bool verify_rfid(QString);

    QSqlQueryModel * search_rfid(QString);

    bool update_num_entree(QString cin,int i);

    QSqlQueryModel  * afficher_notifications();



  QSqlQueryModel * chercher(QString r);



};

#endif // PERSONNEL_H
