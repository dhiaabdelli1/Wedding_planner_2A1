#include "collaborateur.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
collaborateur::collaborateur()
{
    this->nom="";
    this->email="";
    this->reference="";
    this->telephone="";
    this->rib="";
    this->service="";
}
collaborateur::collaborateur (QString reference,QString nom,QString email,QString telephone,QString service ,QString rib)
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

    query.prepare("INSERT INTO collaborateur (reference,nom,email,telephone,service,rib)"
                  "Values(:reference,:nom,:email,:telephone,:service,:rib)");

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
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("reference"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("email"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("telephone"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("service"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("rib"));


   return model;

}
 bool collaborateur::supprimer(QString reference)
{
    QSqlQuery qry;

    qry.prepare("delete from collaborateur where reference=:reference");

    qry.bindValue(":reference",reference);

        return qry.exec();
}
 bool collaborateur::modifier(QString reference,QString nom,QString email,QString telephone,QString service ,QString rib)
{
    QSqlQuery query;
    query.prepare("UPDATE collaborateur SET reference=:reference,nom=:nom,email=:email,telephone=:telephone,service=:service,rib=:rib WHERE reference = :reference");
    query.bindValue(":nom", nom);
    query.bindValue(":telephone",telephone );
    query.bindValue(":email", email);
    query.bindValue(":rib", rib);
    query.bindValue(":reference", reference);
    query.bindValue(":service", service);
    return    query.exec();
}
 QSqlQueryModel * collaborateur::rechercher_rib(QString rib)
 {
     QSqlQuery qry;
     qry.prepare("select * from collaborateur where rib=:rib");
     qry.bindValue(":rib",rib);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * collaborateur::rechercher_nom(QString nom)
 {
     QSqlQuery qry;
     qry.prepare("select * from collaborateur where nom=:nom");
     qry.bindValue(":nom",nom);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * collaborateur::rechercher_service(QString service)
 {
     QSqlQuery qry;
     qry.prepare("select * from collaborateur where service=:service");
     qry.bindValue(":service",service);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * collaborateur::rechercher_RibNom(QString rib, QString nom)
 {
     QSqlQuery *qry= new QSqlQuery();
     qry->prepare("select * from collaborateur where rib=:rib and nom=:nom");
     qry->bindValue(":rib",rib);
     qry->bindValue(":nom",nom);
     qry->exec();


        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(*qry);
         return model;


 }
 QSqlQueryModel * collaborateur::rechercher_RibSer(QString rib, QString service)
 {
     QSqlQuery *qry= new QSqlQuery();
     qry->prepare("select * from collaborateur where rib=:rib and service=:service");
     qry->bindValue(":rib",rib);
     qry->bindValue(":service",service);
     qry->exec();

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(*qry);
         return model;


 }
 QSqlQueryModel * collaborateur::rechercher_NomSer(QString nom, QString service)
 {
     QSqlQuery *qry= new QSqlQuery();
     qry->prepare("select * from collaborateur where nom=:nom and service=:service");
     qry->bindValue(":nom",nom);
     qry->bindValue(":service",service);
     qry->exec();

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(*qry);
         return model;


 }



QSqlQueryModel * collaborateur::rechercher_tous(QString rib,QString nom,QString service)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("select * from collaborateur where rib=:rib and nom=:nom and service=:service");
    qry->bindValue(":rib",rib);
    qry->bindValue(":nom",nom);
    qry->bindValue(":service",service);
    qry->exec();

       QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery(*qry);
        return model;

}

void collaborateur::exporter(QTableView *table)
{

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                                    filters, &defaultFilter);
    QFile file(fileName);
    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++)
        {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++)
        {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++)
            {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
    }
}











