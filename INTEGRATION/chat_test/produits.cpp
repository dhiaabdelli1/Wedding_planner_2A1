#include "produits.h"

produits::produits()
{

}

bool produits::ajouter_p()
{
    QString res= QString::number(reference_p);

    QSqlQuery query;
    query.prepare("insert into produits (reference,quantite,type,prix,datee)"
                  "values (:reference,:quantite,:type,:prix,:datee)");
    query.bindValue(":reference",reference_p);
    query.bindValue(":quantite",quantite_p);
    query.bindValue(":type",type_p);
    query.bindValue(":prix",prix_p);
    query.bindValue(":datee",date_p);

    return query.exec();
}

QSqlQueryModel * produits::afficher_p()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM produits");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    return model;
}

bool produits::supprimer_p(int reference_p)
{
    QSqlQuery query;
    QString res = QString::number(reference_p);
    query.prepare("Delete from produits where reference = :reference");
    query.bindValue(":reference",res);
    return query.exec();

}


QSqlQueryModel * produits::rechercher_reference_p(int reference_p)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM produits WHERE reference = :reference");
    qry.bindValue(":reference",reference_p);
    qry.exec();
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);
    QSqlRecord rec=model->record(0);
    int r=rec.value("reference").toInt();
    if (r==reference_p)
        return model;
    return nullptr;

}
QSqlQueryModel * produits::rechercher_quantite_p(int quantite_p)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM produits WHERE quantite = :quantite");
    qry.bindValue(":quantite",quantite_p);
    qry.exec();
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);
    QSqlRecord rec=model->record(0);
    int q=rec.value("quantite").toInt();
    if (q==quantite_p)
        return model;
    return nullptr;

}

QSqlQueryModel * produits::rechercher_type_p(QString type_p)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM produits WHERE type = :type");
    qry.bindValue(":type",type_p);
    qry.exec();
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);
    return model;
    }


QSqlQueryModel * produits::rechercher_date_p(QDate date_p)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM produits WHERE datee =:datee");
    qry.bindValue(":datee",date_p);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);

    return model;
}

QSqlQueryModel * produits::rechercher_critere_p(int quantite_p,QString type_p,QDate date_p)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM produits WHERE quantite =:quantite AND type =:type AND datee =:datee ");
    qry->bindValue(":quantite",quantite_p);
    qry->bindValue(":type",type_p);
    qry->bindValue(":datee",date_p);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}

