#include "fournisseurs.h"

fournisseurs::fournisseurs()
{
    this->CIN=0;
    this->telephone=0;
    this->type="";
    this->RIB=0;
}
fournisseurs::fournisseurs(int CIN,int telephone,QString type,int RIB)
{
    this->CIN=CIN;
    this->telephone=telephone;
    this->type=type;
    this->RIB=RIB;

}


bool fournisseurs::ajouter_f()
{
    QString res= QString::number(CIN);
    QSqlQuery query;
    query.prepare("insert into fournisseurs (CIN,telephone,type,RIB)"
                  "values (:CIN,:telephone,:type,:RIB)");
    query.bindValue(":CIN",CIN);
    query.bindValue(":telephone",telephone);
    query.bindValue(":type",type);
    query.bindValue(":RIB",RIB);


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

bool fournisseurs::supprimer_f(int CIN)
{
    QSqlQuery query ;

    query.prepare("delete from fournisseurs where CIN=:CIN");

    query.bindValue(":CIN",CIN);

        return query.exec();

}


QSqlQueryModel * fournisseurs::rechercher_fournisseurs(QString CIN)
{
    QString query1="SELECT * FROM fournisseurs WHERE CIN=";
    QString queryfull=query1 + CIN;
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery(queryfull);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RIB"));

        return model;
}

/*QSqlQueryModel * fournisseurs::rechercher_type_2(QString type)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM fournisseurs WHERE type = :type");
    qry.bindValue(":type",type);
    qry.exec();
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);
    return model;
}


QSqlQueryModel * fournisseurs::rechercher_RIB(int RIB)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM fournisseurs WHERE RIB =:RIB");
    qry.bindValue(":RIB",RIB);
    qry.exec();
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);
    QSqlRecord recb=model->record(0);
    int r_2=recb.value("RIB").toInt();
    if (r_2==RIB)
    return model;
    return nullptr;



QSqlQueryModel * fournisseurs::rechercher_telephone(int telephone)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM fournisseurs WHERE telephone =:telephone");
    qry->bindValue(":telephone",telephone);
    qry->exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
    QSqlRecord rect=model->record(0);
    int t_2=rect.value("telephone").toInt();
    if (t_2==telephone)
    return model;
    return nullptr;
}
*/

