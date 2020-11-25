#ifndef COLLABORATEUR_H
#define COLLABORATEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class collaborateur
{
public:
    collaborateur();
    collaborateur (QString,int,QString,int,QString,QString);
    QString getNom(){return nom;}
    int getTelephone(){return telephone;}
    QString getEmail(){return email;}
    int getRib(){return rib;}
    QString getReference(){return reference;}
    QString getService(){return service;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString,int,QString,int,QString,QString);
    QSqlQueryModel * rechercher_collaborateur(QString);


private :
    QString nom,email,reference,service;
    int telephone,rib;



};

#endif // COLLABORATEUR_H
