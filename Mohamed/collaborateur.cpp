#include "collaborateur.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
collaborateur::collaborateur()
{
    this->nom="";
    this->email="";
    this->reference="";
    this->telephone=0;
    this->rib=0;
    this->service="";
}
collaborateur::collaborateur (QString nom,int telephone,QString email,int rib,QString reference,QString service)
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

    query.prepare("INSERT INTO collaborateur (nom,telephone,email,rib,reference,service)"
                  "Values(:nom,:telephone,:email,:rib,:reference,:service)");
    query.bindValue(":service",service);
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
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("Nom"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Telephone"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("RIB"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Reference"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Service"));


   return model;

}
 bool collaborateur::supprimer(QString reference)
{
    QSqlQuery qry;

    qry.prepare("delete from collaborateur where reference=:reference");

    qry.bindValue(":reference",reference);

        return qry.exec();
}
 bool collaborateur::modifier(QString nom,int telephone,QString email,int rib,QString reference,QString service)
{
    QSqlQuery query;
    query.prepare("UPDATE collaborateur SET nom= :nom,telephone= :telephone,email=:email,rib= :rib,reference=:reference,service=:service WHERE reference = :reference");
    query.bindValue(":nom", nom);
    query.bindValue(":telephone",telephone );
    query.bindValue(":email", email);
    query.bindValue(":rib", rib);
    query.bindValue(":reference", reference);
    query.bindValue(":service", service);
    return    query.exec();
}
 QSqlQueryModel * collaborateur::rechercher_rib(int rib)
 {
     QSqlQuery qry;
     qry.prepare("select * from collaborateur where rib=:rib");
     qry.bindValue(":rib",rib);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * collaborateur::rechercher_ref(QString reference)
 {
     QSqlQuery qry;
     qry.prepare("select * from collaborateur where reference=:reference");
     qry.bindValue(":reference",reference);
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
 QSqlQueryModel * collaborateur::rechercher_RibRef(int rib, QString reference)
 {
     QSqlQuery *qry= new QSqlQuery();
     qry->prepare("select * from collaborateur where rib=:rib and reference=:reference");
     qry->bindValue(":rib",rib);
     qry->bindValue(":reference",reference);
     qry->exec();


        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(*qry);
         return model;


 }
 QSqlQueryModel * collaborateur::rechercher_RibSer(int rib, QString service)
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
 QSqlQueryModel * collaborateur::rechercher_RefSer(QString reference, QString service)
 {
     QSqlQuery *qry= new QSqlQuery();
     qry->prepare("select * from collaborateur where reference=:reference and service=:service");
     qry->bindValue(":reference",reference);
     qry->bindValue(":service",service);
     qry->exec();

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(*qry);
         return model;


 }



QSqlQueryModel * collaborateur::rechercher_tous(int rib,QString reference,QString service)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("select * from collaborateur where rib=:rib and reference=:reference and service=:service");
    qry->bindValue(":rib",rib);
    qry->bindValue(":reference",reference);
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











