#include "client.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
client::client()
{

}
client::client(int CIN,QString nom,QString prenom)
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;

}
bool client::ajouter()
{
    QSqlQuery query;
    query.prepare("Insert into client(CIN,nom,prenom)"
                  "Values(:CIN,:nom,:prenom)");
    query.bindValue(":CIN",CIN);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    return query.exec();

}
QSqlQueryModel * client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from CLIENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));

    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    return model;

}

bool client::supprimer(int CIN)
{
    QSqlQuery query;
    query.prepare("delete from CLIENT where CIN=:CIN");
    query.bindValue(":CIN",CIN);
    return query.exec();
}
