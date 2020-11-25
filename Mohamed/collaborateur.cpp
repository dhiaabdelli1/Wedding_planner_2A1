#include "collaborateur.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
collaborateur::collaborateur()
{
    this->nom="";
    this->email="";
    this->reference="";
    this->telephone=0;
    this->rib=0;
    this->service="";
}
collaborateur::collaborateur (QString nom,int telephone,QString email,int rib,QString reference,QString service)
{
this->nom=nom;
this->telephone=telephone;
this->email=email;
this->rib=rib;
this->reference=reference;
this->service=service;
}


bool collaborateur::ajouter()
{
    QSqlQuery query ;

    query.prepare("INSERT INTO collaborateur (nom,telephone,email,rib,reference,service)"
                  "Values(:nom,:telephone,:email,:rib,:reference,:service)");
    query.bindValue(":service",service);
    query.bindValue(":nom",nom);
    query.bindValue(":telephone",telephone);
    query.bindValue(":email",email);
    query.bindValue(":rib",rib);
    query.bindValue(":reference",reference);
    query.bindValue(":service",service);

        return query.exec();
}

QSqlQueryModel * collaborateur::afficher()
{
   QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("select * from collaborateur");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("Nom"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Telephone"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("RIB"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Reference"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Service"));


   return model;

}
bool collaborateur::supprimer(QString reference)
{
    QSqlQuery query ;

    query.prepare("delete from collaborateur where reference=:reference");

    query.bindValue(":reference",reference);

        return query.exec();
}
bool collaborateur::modifier(QString nom,int telephone,QString email,int rib,QString reference,QString service)
{
    QSqlQuery query;
    query.prepare("UPDATE collaborateur SET nom= :nom,telephone= :telephone,email=:email,rib= :rib,reference=:reference,service=:service WHERE reference = :reference");
    query.bindValue(":nom", nom);
    query.bindValue(":telephone",telephone );
    query.bindValue(":email", email);
    query.bindValue(":rib", rib);
    query.bindValue(":reference", reference);
    query.bindValue(":service", service);
    return    query.exec();
}
QSqlQueryModel * collaborateur::rechercher_collaborateur(QString r)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from collaborateur where upper(email) like upper('%"+r+"%') or upper(rib) like upper('%"+r+"%') or upper(reference) like upper('%"+r+"%')");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("rib"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("reference"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("service"));

        return model;
}










