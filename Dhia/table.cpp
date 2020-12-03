#include "table.h"

table::table()
{

}

bool table::ajouter()
{
    QSqlQuery query;



    query.prepare("INSERT INTO tables (nb_places,nom_serveur)"
                  "VALUES (:nb_places,:nom_serveur)");


    query.bindValue(":nb_places",nb_places);
    query.bindValue(":nom_serveur",nom_serveur);

    return query.exec();
}

QSqlQueryModel * table::afficher()
{

    QSqlQueryModel *model_2= new QSqlQueryModel();

    model_2->setQuery("select * from TABLES");

    model_2->setHeaderData(0, Qt::Horizontal, QObject::tr("Numéro"));
    model_2->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre places"));
    model_2->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom serveur"));

    return model_2;
}


bool table::supprimer(int num)
{
    QSqlQuery qry;

    qry.prepare("Delete from tables where numero = :numero");
    qry.bindValue(":numero",num);
    return qry.exec();
}

QSqlQueryModel *table::recherche(QString num)
{

    QSqlQueryModel *model= new QSqlQueryModel;

    model->setQuery("select * from tables where numero like'"+num+"%'");

    return model;
}

QSqlQueryModel *table::trier(QString crit,QString ordre)
{
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from tables order by "+crit+" "+ordre);
    qry->exec();
    model->setQuery(*qry);
    return model;
}

bool table::invite_existe(int num)
{
    QSqlQuery query;
    query.prepare("select * from invites where num_table=:num");
    query.bindValue(":num",num);

    query.exec();

    int total=0;
    while(query.next()){
        total++;
    }
    if (total)
    {
        return true;
    }
    return false;
}




