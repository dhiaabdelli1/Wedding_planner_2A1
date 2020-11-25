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
    service (QString,QDate,float,QString);
    QString gettype(){return type;}
    QDate getdat(){return dat;}
    double getprix(){return prix;}
    QString getproprietaire(){return proprietaire;}

    bool ajouter_service();
    QSqlQueryModel * afficher_service();
    bool supprimer_service(QString);
    bool modifier_service(QString,QDate,float,QString);
private:
    QString type;
    QDate dat ;
    float prix;
    QString proprietaire;

};

#endif // SERVICE_H
