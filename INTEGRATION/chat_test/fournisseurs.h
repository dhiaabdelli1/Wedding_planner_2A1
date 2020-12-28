#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class fournisseurs
{

public:
    fournisseurs();
    fournisseurs (QString,QString,QString,QString);
    QString getCIN_f(){return CIN_f;}
    QString getTelephone_f(){return telephone_f;}
    QString gettype_f(){return type_f;}
    QString getRIB_f(){return RIB_f;}

    bool ajouter_f();
    QSqlQueryModel * afficher_f();
    bool supprimer_f(int);
    bool modifier_f();
    QSqlQueryModel * rechercher_fournisseurs(QString);

private:
    QString CIN_f;
    QString telephone_f;
    QString type_f;
    QString RIB_f;
};

#endif // FOURNISSEURS_H
