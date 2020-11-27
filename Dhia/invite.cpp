#include "invite.h"

invite::invite()
{

}


bool invite::ajouter()
{
    QSqlQuery query;

    QString res= QString::number(cin);

    query.prepare("INSERT INTO Invites (cin, nom, prenom,date_naissance,mail,sexe)"
                  "VALUES (:cin,:nom,:prenom,:date_naissance,:mail,:sexe)");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
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
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));

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


QSqlQueryModel * invite::rechercher_cin(int cin)
{
    QSqlQuery qry;
    qry.prepare("select * from invites where cin = :cin");
    qry.bindValue(":cin",cin);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);

    QSqlRecord rec=model->record(0);

    int c=rec.value("cin").toInt();

    if (c==cin)
        return model;
    return nullptr;

}

QSqlQueryModel * invite::rechercher_sexe(QString sexe)
{
    QSqlQuery qry;
    qry.prepare("select * from invites where sexe = :sexe");
    qry.bindValue(":sexe",sexe);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


   return model;


}

QSqlQueryModel * invite::rechercher_date(QDate date)
{
    QSqlQuery qry;
    qry.prepare("select * from invites where date_naissance = :date_naissance");
    qry.bindValue(":date_naissance",date);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);

    return model;
}

QSqlQueryModel * invite::rechercher_combinaison(QString nom,QString sexe,QDate date)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("select * from invites where nom=:nom and sexe=:sexe and date_naissance=:date_naissance");
    qry->bindValue(":nom",nom);
    qry->bindValue(":sexe",sexe);
    qry->bindValue(":date_naissance",date);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}

void invite::exporter(QTableView *table)
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



QSqlQueryModel *invite::trier(QString crit,QString ordre)
{
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from invites order by "+crit+" "+ordre);
    qry->exec();
    model->setQuery(*qry);
    return model;
}






