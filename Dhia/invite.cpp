#include "invite.h"

invite::invite()
{

}


bool invite::ajouter()
{
    QSqlQuery query;

    QString res= QString::number(cin);

    query.prepare("INSERT INTO Invites (cin, nom, prenom,age,date_naissance,mail,sexe)"
                  "VALUES (:cin,:nom,:prenom,:age,:date_naissance,:mail,:sexe)");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":age",age);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":mail",mail);
    query.bindValue(":sexe",sexe);

    return query.exec();
}


QSqlQueryModel * invite::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("select * from Invites");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nmo"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Sexe"));

    return model;
}


bool invite::supprimer(int cin)
{
    QSqlQuery qry;
    QString mat = QString::number(cin);
    qry.prepare("Delete from INVITES where CIN = :CIN");
    qry.bindValue(":CIN",mat);
    return qry.exec();
}












