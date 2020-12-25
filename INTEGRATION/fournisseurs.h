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
    int getCIN_f(){return CIN_f;}
    int getTelephone_f(){return telephone_f;}
    QString gettype_f(){return type_f;}
    int getRIB_f(){return RIB_f;}

    bool ajouter_f();
    QSqlQueryModel * afficher_f();
    bool supprimer_f(int);
    bool modifier_f();
    QSqlQueryModel * rechercher_fournisseurs(QString);

private:
    int CIN_f,telephone_f;
    QString type_f;
    int RIB_f;
};

#endif // FOURNISSEURS_H
