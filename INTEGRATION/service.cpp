#include "service.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
service::service()
{

}
service::service (QString type,QDate date_service,int prix,QString proprietaire)
{
this->type=type;
this->date_service=date_service;
this->prix=prix;
this->proprietaire=proprietaire;

}


bool service::ajouter_service()
{
    QSqlQuery query ;

    query.prepare("INSERT INTO service (type,date_service,prix,proprietaire)"
                  "Values(:type,:date_service,:prix,:proprietaire)");
    query.bindValue(":type",type);
    query.bindValue(":date_service",date_service);
    query.bindValue(":prix",prix);
    query.bindValue(":proprietaire",proprietaire);


        return query.exec();
}

QSqlQueryModel * service::afficher_service()
{
   QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("select * from service");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("type"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_service"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("proprietaire"));


   return model;

}
bool service::supprimer_service(QString type)
{
    QSqlQuery query ;

    query.prepare("delete from service where type=:type");

    query.bindValue(":type",type);

        return query.exec();
}
bool service::modifier_service(QString type,QDate date_service,int prix,QString proprietaire)
{
    QSqlQuery query;
    query.prepare("UPDATE service SET type= :type,date_service= :date_service,prix=:prix,proprietaire=:proprietaire WHERE type = :type");
    query.bindValue(":type", type);
    query.bindValue(":date_service", date_service);
    query.bindValue(":prix", prix);
    query.bindValue(":proprietaire", proprietaire);

    return    query.exec();
}

