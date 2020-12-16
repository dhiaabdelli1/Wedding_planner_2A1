#include "invite.h"
#include "mainwindow.h"

invite::invite()
{

}


bool invite::ajouter()
{
    QSqlQuery query;



    query.prepare("INSERT INTO Invites (cin, nom, prenom,date_naissance,mail,sexe,telephone,permission)"
                  "VALUES (:cin,:nom,:prenom,:date_naissance,:mail,:sexe,:telephone,:permission)");

    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":mail",mail);
    query.bindValue(":sexe",sexe);
    query.bindValue(":telephone",telephone);
    query.bindValue(":permission","-");

    return query.exec();
}


QSqlQueryModel * invite::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("select * from Invites");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Numéro table"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Permission"));

    return model;
}


bool invite::supprimer(QString cin)
{
    QSqlQuery qry;
    qry.prepare("Delete from INVITES where CIN = :CIN");
    qry.bindValue(":CIN",cin);
    return qry.exec();
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

bool invite::update(QString cin,QString att,QString val)
{
    QSqlQuery query;
    query.prepare("update invites set permission=:permission where cin=:cin");
    query.bindValue(":permission",val);
    query.bindValue(":cin",cin);


    return query.exec();
}

QSqlQueryModel *invite::rechercher_nom(QString nom)
{

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery("select * from invites where nom like'"+nom+"%'");

    return model;
}

QSqlQueryModel * invite::rechercher_cin(QString cin)
{
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery("select * from invites where cin like'"+cin+"%'");

    return model;
}

QSqlQueryModel * invite::rechercher_email(QString email)
{
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery("select * from invites where mail like'"+email+"%'");

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

QSqlQueryModel * invite::rechercher_combinaison_all(QString nom,QString sexe,QDate date)
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

QSqlQueryModel * invite::rechercher_combinaison_nom_date(QString nom, QDate date)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("select * from invites where nom=:nom and date_naissance=:date_naissance");
    qry->bindValue(":nom",nom);
    qry->bindValue(":date_naissance",date);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}

QSqlQueryModel * invite::rechercher_combinaison_sexe_date(QString sexe, QDate date)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("select * from invites where sexe=:sexe and date_naissance=:date_naissance");
    qry->bindValue(":sexe",sexe);
    qry->bindValue(":date_naissance",date);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}

QSqlQueryModel * invite::rechercher_combinaison_nom_sexe(QString nom, QString sexe)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("select * from invites where nom=:nom and sexe=:sexe");
    qry->bindValue(":nom",nom);
    qry->bindValue(":sexe",sexe);
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


int invite::count(QString etat)
{
    QSqlQuery query;
    query.prepare("select * from invites where sexe=:etat");
    query.bindValue(":etat",etat);

    query.exec();
    int total=0;
    while(query.next()){
        total++;
    }

    return total;

}

int invite::count_date(QDate date_1,QDate date_2,QString sexe)
{
    QSqlQuery query;
    query.prepare("select * from invites where date_naissance between :date_1 AND :date_2  AND sexe=:sexe");
    query.bindValue(":date_1",date_1);
    query.bindValue(":date_2",date_2);
    query.bindValue(":sexe",sexe);

    query.exec();
    int total=0;
    while(query.next()){
        total++;
    }

    return total;
}


int invite::affecter_table(QString cin, int num,int nb_max)
{
    QSqlQuery query;

    query.prepare("select * from tables where numero=:num");
    query.bindValue(":num",num);

    query.exec();

    int total=0;
    while(query.next()){
        total++;
    }

    if (!total)
    {
        return 1;
    }

    query.prepare("select * from invites where num_table=:num");
    query.bindValue(":num",num);

    query.exec();

    total=0;
    while(query.next()){
        total++;
    }
    if (total>=nb_max)
    {
        return 2;
    }

    qDebug() << total;

    query.prepare("update invites set num_table=:num where cin=:cin");
    query.bindValue(":num",num);
    query.bindValue(":cin",cin);


    return !query.exec();
}


QSqlQueryModel *invite::afficher_notifications()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *qry= new QSqlQuery;
    qry->prepare("select * from invites where permission='pending' or permission='accepte' or permission='refuse' order by ordre_entree DESC");
    qry->exec();
    model->setQuery(*qry);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Numéro table"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Permission"));

    return model;
}

bool invite::update_num_entree(QString cin,int i)
{
    QSqlQuery query;
    query.prepare("update invites set ordre_entree=:ordre_entree where cin=:cin");
    query.bindValue(":ordre_entree",i);
    query.bindValue(":cin",cin);


    return query.exec();
}
