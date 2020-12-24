#include "reservation.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
reservation::reservation()
{

}
reservation::reservation(QString reference,QDate date_reservation,float prix,int nb_invites,QString localisation)
{
    this->reference=reference;
    this->date_reservation=date_reservation;
    this->prix=prix;
    this->nb_invites=nb_invites;
    this->localisation=localisation;

}
bool reservation::ajouter()
{
    QSqlQuery query;
    QString prix_string=QString::number(prix);

    query.prepare("Insert into reservation(reference,date_reservation,prix,nb_invites,localisation)"
                  "Values(:reference,:date_reservation,:prix,:nb_invites,:localisation)");
    query.bindValue(":reference",reference);
    query.bindValue(":date_reservation",date_reservation);
    query.bindValue(":prix",prix_string);

    query.bindValue(":nb_invites",nb_invites);
    query.bindValue(":localisation",localisation);
    return query.exec();

}
QSqlQueryModel * reservation::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from reservation");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("reference"));

    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_reservation"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nb_invites"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("localisation"));
    return model;

}

bool reservation::supprimer(int reference)
{
    QSqlQuery query;
    query.prepare("delete from reservation where reference=:reference");
    query.bindValue(":reference",reference);
    return query.exec();
}

QSqlQueryModel * reservation::recherchereservation(const QString &id)
{

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from reservation where(reference LIKE '"+id+"%') or (prix LIKE'"+id+"%') or (localisation LIKE '"+id+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("localisation"));



    return model;
}
QString test_tri(int c)
{
    if (c==0)
    {
        return "ress" ;
    }
    else if (c==1)
    {
        return "reference";
    }
    else if (c==2)
    {
        return "prix";
    }
    else if (c==3)
    {
        return "localisation";
    }

    return "NULL";
}
QSqlQueryModel* reservation::trireservation(int i)
{

    QString col = test_tri(i);
    QSqlQueryModel *model = new QSqlQueryModel() ;

    QString header = "SELECT * FROM reservation ORDER BY "+col;
    model->setQuery(header);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nb_invites"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("localisation"));

    return model;
}

QSqlQueryModel *reservation::trier(QString crit,QString ordre)
{
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from reservation order by "+crit+" "+ordre);
    qry->exec();
    model->setQuery(*qry);
    return model;
}
