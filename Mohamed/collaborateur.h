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
    collaborateur (QString,int,QString,int,QString,QString);
    QString getNom(){return nom;}
    int getTelephone(){return telephone;}
    QString getEmail(){return email;}
    int getRib(){return rib;}
    QString getReference(){return reference;}
    QString getService(){return service;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString,int,QString,int,QString,QString);
     QSqlQueryModel * rechercher_rib(int);
     QSqlQueryModel * rechercher_ref(QString);
     QSqlQueryModel * rechercher_service(QString);
     QSqlQueryModel * rechercher_RibRef(int,QString);
     QSqlQueryModel * rechercher_RibSer(int,QString);
     QSqlQueryModel * rechercher_RefSer(QString,QString);
     QSqlQueryModel * rechercher_tous(int,QString,QString);
     void exporter(QTableView *table);




private :
    QString nom,email,reference,service;
    int telephone,rib;



};

#endif // COLLABORATEUR_H
