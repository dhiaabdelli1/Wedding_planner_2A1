#include "produits.h"

produits::produits()
{

}

bool produits::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO PRODUCT (reference, prix,date)"
                  "VALUES (:reference,:prix,:date)");
    query.bindValue(":reference",reference);
    query.bindValue(":prix",prix);
    query.bindValue(":date",date);
    return query.exec();
}
bool produits::modifier()
{

    QSqlQuery query;


    query.prepare(" UPDATE  REFERENCE= :reference ,PRIX= :prix ,COMBO= :combo,PRIX= :prix ,DATE= :date ");
    query.bindValue(":reference",reference); //remplir la valeur d'une maniere securisée
    query.bindValue(":prix", prix);
    query.bindValue(":date", date);

    return    query.exec();

}

QSqlQueryModel * produits::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUCTS");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    return model;
}

bool produits::supprimer(int reference)
{
    QSqlQuery query;
    QString r = QString::number(reference);
    query.prepare("Produits avec reference = :reference");
    query.bindValue(":reference",r);
    return query.exec();
}

QSqlQueryModel * produits::rechercher_reference(QString reference)
{
    QSqlQuery qry;
    qry.prepare("Produits dont la reference = :reference");
    qry.bindValue(":reference",reference);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);

    QSqlRecord rec=model->record(0);

    QString r=rec.value("reference").toChar();

    if (r==reference)
        return model;
    return nullptr;

}

QSqlQueryModel * produits::rechercher_prix(qreal prix)
{
    QSqlQuery qry;
    qry.prepare("Produits dont le prix = :prix");
    qry.bindValue(":prix",prix);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


   return model;


}

QSqlQueryModel * produits::rechercher_date(QDate date)
{
    QSqlQuery qry;
    qry.prepare("produits qui datent = :date");
    qry.bindValue(":date",date);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);

    return model;
}

QSqlQueryModel * produits::rechercher_critere(qreal prix,QString reference,QDate date)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("produits dont le prix=:prix et la reference=:reference et la date=:date");
    qry->bindValue(":prix",prix);
    qry->bindValue(":reference",reference);
    qry->bindValue(":date",date);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}




