#include "departement.h"
#include "QDebug"
#include <QFileDialog>
#include <QString>


departement::departement()
{

}

departement::departement(QString reference, QString nom,int nb_employes)
{

this->reference=reference;
this->nom=nom;
this->nb_employes=nb_employes;


}




bool departement::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO departements (reference, nom, nb_employes)"
                  "VALUES (:reference, :nom, :nb_employes)");
    query.bindValue(":reference",reference);
    query.bindValue(":nom",nom);
    query.bindValue(":nb_employes",nb_employes);




    return query.exec();


}



QSqlQueryModel * departement::afficher()
{
QSqlQueryModel * model = new QSqlQueryModel();

model->setQuery("select *from departements");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nb_employes"));


    return model;
}





bool departement::supprimer(QString reference)
{

    QSqlQuery qry;

        qry.prepare("Delete from departements where reference = :reference");
        qry.bindValue(":reference",reference);
        return qry.exec();
}




bool departement::update( QString reference, QString nom, int nb_employes)
{
    QSqlQuery query;
    query.prepare("UPDATE departements SET reference= :reference , nom= :nom , nb_employes= :nb_employes WHERE nom = :nom");

    query.bindValue(":reference", reference);
    query.bindValue(":nom",nom );
    query.bindValue(":nb_employes", nb_employes);



    return    query.exec();
}

QSqlQueryModel *departement::refdep()
{
    QSqlQuery query;
        query.prepare("SELECT reference FROM departements"); //remplir le combo Box
        QSqlQueryModel *modal=new QSqlQueryModel();
        query.exec();
        modal->setQuery(query);
        return modal;
}
