#ifndef SERVICE_H
#define SERVICE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class service
{
public:
    service();
    service (QString,QDate,int,QString);
    QString gettype(){return type;}
    QDate getdat(){return date_service;}
    double getprix(){return prix;}
    QString getproprietaire(){return proprietaire;}

    bool ajouter_service();
    QSqlQueryModel * afficher_service();
    bool supprimer_service(QString);
    bool modifier_service(QString,QDate,int,QString);

private:
    QString type;
    QDate date_service ;
    int prix;
    QString proprietaire;

};

#endif // SERVICE_H
