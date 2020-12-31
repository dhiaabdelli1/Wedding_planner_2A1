#ifndef DEPARTEMENT_H
#define DEPARTEMENT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
class departement
{


    QString reference;
    QString nom;
    QString nb_employes;

public:
    departement();

    departement(QString,QString,QString);
      QString getReference(){return reference;}
    QString getNom(){return nom;}
    //int getnb_employes(){return nb_employes;}



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool update(QString,QString,QString);
    QSqlQueryModel * refdep();
    QSqlQueryModel *nomdep();

};

#endif // DEPARTEMENT_H
