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
public:
    table();
    table(int nb,QString no):nb_places(nb),nom_serveur(no){};
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    QSqlQueryModel *recherche(QString);
    QSqlQueryModel *trier(QString,QString);
    bool invite_existe(int);
    bool get_nb_max(int);

};

#endif // TABLE_H
