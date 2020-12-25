#include "fournisseurs.h"

fournisseurs::fournisseurs()
{
//    this->CIN_f=0;
//    this->telephone_f=0;
//    this->type_f="";
//    this->RIB_f=0;
}
fournisseurs::fournisseurs(QString CIN_f,QString telephone_f,QString type_f,QString RIB_f)
{
    this->CIN_f=CIN_f;
    this->telephone_f=telephone_f;
    this->type_f=type_f;
    this->RIB_f=RIB_f;

}


bool fournisseurs::ajouter_f()
{
    //QString res= QString::number(CIN_f);
    QSqlQuery query;
    query.prepare("insert into fournisseurs (CIN,type,telephone,RIB)"
                  "values (:CIN,:type,:telephone,:RIB)");
    query.bindValue(":CIN",CIN_f);
    query.bindValue(":telephone",telephone_f);
    query.bindValue(":type",type_f);
    query.bindValue(":RIB",RIB_f);


    return query.exec();
}

QSqlQueryModel * fournisseurs::afficher_f()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("select * from fournisseurs");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RIB"));

    return model;
}

bool fournisseurs::supprimer_f(int CIN_f)
{
    QSqlQuery query ;

    query.prepare("delete from fournisseurs where CIN=:CIN");

    query.bindValue(":CIN",CIN_f);

        return query.exec();

}


QSqlQueryModel * fournisseurs::rechercher_fournisseurs(QString CIN_f)
{
    QString query1="SELECT * FROM fournisseurs WHERE CIN=";
    QString queryfull=query1 + CIN_f;
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery(queryfull);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RIB"));

        return model;
}


