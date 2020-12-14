#include "client.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
client::client()
{

}
client::client(int CIN,QString nom,QString prenom,QDate date,QString telephone,QString mail,float budget)
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
    this->date=date;
    this->mail=mail;
    this->telephone=telephone;
    this->budget=budget;

}
bool client::ajouter()
{
    QSqlQuery query;
    QString budget_string=QString::number(budget);
    query.prepare("Insert into client(CIN,nom,prenom,DATEDENAISSANCE,telephone,mail,budget)"
                  "Values(:CIN,:nom,:prenom,:DATEDENAISSANCE,:telephone,:mail,:budget)");
    query.bindValue(":CIN",CIN);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":DATEDENAISSANCE",date);
    query.bindValue(":telephone",telephone);
    query.bindValue(":mail",mail);
    query.bindValue(":budget",budget_string);
    return query.exec();

}
QSqlQueryModel * client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from CLIENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));

    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEDENAISSANCE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("telephone"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("mail"));
    return model;

}

bool client::supprimer(int CIN)
{
    QSqlQuery query;
    query.prepare("delete from CLIENT where CIN=:CIN");
    query.bindValue(":CIN",CIN);
    return query.exec();
}

QSqlQueryModel * client::rechercheclient(const QString &id)
{

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from CLIENT where(CIN LIKE '"+id+"%') or (nom LIKE'"+id+"%') or (prenom LIKE '"+id+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));



    return model;
}
QString test_tri2(int c)
{
    if (c==0)
    {
        return "ress" ;
    }
    else if (c==1)
    {
        return "CIN";
    }
    else if (c==2)
    {
        return "nom";
    }
    else if (c==3)
    {
        return "prenom";
    }

    return "NULL";
}
QSqlQueryModel* client::triclient(int i)
{

    QString col = test_tri2(i);
    QSqlQueryModel *model = new QSqlQueryModel() ;

    QString header = "SELECT * FROM CLIENT ORDER BY "+col;
    model->setQuery(header);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));

    return model;
}

QSqlQueryModel *client::trier(QString crit,QString ordre)
{
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from client order by "+crit+" "+ordre);
    qry->exec();
    model->setQuery(*qry);
    return model;
}
