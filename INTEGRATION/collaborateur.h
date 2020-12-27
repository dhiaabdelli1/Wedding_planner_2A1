#ifndef COLLABORATEUR_H
#define COLLABORATEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QApplication>
#include <QPrinter>
#include <QTextDocument>

class collaborateur
{
public:
    collaborateur();
    collaborateur (QString,QString,QString,QString,QString,QString);
    QString getNom(){return nom;}
    QString getTelephone(){return telephone;}
    QString getEmail(){return email;}
    QString getRib(){return rib;}
    QString getReference(){return reference;}
    QString getService(){return service;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString,QString);
     QSqlQueryModel * rechercher_rib(QString);
     QSqlQueryModel * rechercher_nom(QString);
     QSqlQueryModel * rechercher_service(QString);
     QSqlQueryModel * rechercher_RibNom(QString,QString);
     QSqlQueryModel * rechercher_RibSer(QString,QString);
     QSqlQueryModel * rechercher_NomSer(QString,QString);
     QSqlQueryModel * rechercher_tous(QString,QString,QString);
     void exporter(QTableView *table);




private :
    QString nom,email,reference,service;
    QString telephone,rib;



};

#endif // COLLABORATEUR_H
