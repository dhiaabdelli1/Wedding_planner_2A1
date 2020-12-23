#ifndef DEPARTEMENT_H
#define DEPARTEMENT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
class departement
{


    QString reference;
    QString nom;
    int nb_employes;

public:
    departement();

    departement(QString,QString,int);
      QString getReference(){return reference;}
    QString getNom(){return nom;}
    int getnb_employes(){return nb_employes;}



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool update(QString,QString,int);
    QSqlQueryModel * refdep();

};

#endif // DEPARTEMENT_H
