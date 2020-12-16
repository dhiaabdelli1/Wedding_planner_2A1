#ifndef TABLE_H
#define TABLE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "invite.h"

class table
{
    int nb_places;
    QString nom_serveur;
    QString reference;
public:
    table();
    table(int nb,QString no,QString ref):nb_places(nb),nom_serveur(no),reference(ref){};
    //CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    //FCTS métiers
    QSqlQueryModel *recherche(QString);
    QSqlQueryModel *recherche_ref(QString ref);
    QSqlQueryModel *trier(QString,QString);
    //FCTS supp
    bool invite_existe(int);
    void update_comboBox();
};

#endif // TABLE_H
