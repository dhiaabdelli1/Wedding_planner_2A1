#include "produits.h"

produits::produits()
{

}

bool produits::ajouter()
{
    QString res= QString::number(reference);

    QSqlQuery query;
    query.prepare("insert into produits (reference,quantite,type,prix,datee)"
                  "values (:reference,:quantite,:type,:prix,:datee)");
    query.bindValue(":reference",reference);
    query.bindValue(":quantite",quantite);
    query.bindValue(":type",type);
    query.bindValue(":prix",prix);
    query.bindValue(":datee",datee);

    return query.exec();
}

QSqlQueryModel * produits::afficher()
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

bool produits::supprimer(int reference)
{
    QSqlQuery query;
    QString res = QString::number(reference);
    query.prepare("Delete from produits where reference = :reference");
    query.bindValue(":reference",res);
    return query.exec();

}


QSqlQueryModel * produits::rechercher_reference(int reference)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM produits WHERE reference = :reference");
    qry.bindValue(":reference",reference);
    qry.exec();
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);
    QSqlRecord rec=model->record(0);
    int r=rec.value("reference").toInt();
    if (r==reference)
        return model;
    return nullptr;

}

QSqlQueryModel * produits::rechercher_type(QString type)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM produits WHERE type = :type");
    qry.bindValue(":type",type);
    qry.exec();
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);
    return model;
    }


QSqlQueryModel * produits::rechercher_datee(QDate datee)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM produits WHERE datee =:datee");
    qry.bindValue(":datee",datee);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);

    return model;
}

QSqlQueryModel * produits::rechercher_critere(int reference,QString type,QDate datee)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM produits WHERE reference =:reference AND type =:type AND datee =:datee ");
    qry->bindValue(":reference",reference);
    qry->bindValue(":type",type);
    qry->bindValue(":datee",datee);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}



