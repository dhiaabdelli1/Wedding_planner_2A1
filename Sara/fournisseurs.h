#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class fournisseurs
{

public:
    fournisseurs();
    fournisseurs (int,int,QString,int);
    int getCIN(){return CIN;}
    int getTelephone(){return telephone;}
    QString gettype(){return type;}
    int getRIB(){return RIB;}

    bool ajouter_f();
    QSqlQueryModel * afficher_f();
    bool supprimer_f(int);
    bool modifier_f();
    QSqlQueryModel * rechercher_fournisseurs(QString);

private:
    int CIN,telephone;
    QString type;
    int RIB;
};

#endif // FOURNISSEURS_H

