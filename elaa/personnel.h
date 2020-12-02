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
    int salaire;
public:
    personnel();

    personnel(int,QString,QString,QString,QString,QDate,int);
    int getCin(){return cin;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getMobile(){return mobile;}
    QString getDepartement(){return departement;}
    QDate getDate_naissance(){return date_naissance;}
    int getSalaire(){return salaire;}


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool update(int,QString,QString,QString,QString,QDate,int);
    void creerpdf();



  QSqlQueryModel * cherchernom(QString rech);
        QSqlQueryModel * chercherprenom(QString rech);
        QSqlQueryModel * cherchermobile(QString rech);
        QSqlQueryModel * chercher(QString ,QString,QString);

};

#endif // PERSONNEL_H
