#ifndef PRODUITS_H
#define PRODUITS_H
#include <QDate>
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

class produits
{ qreal prix;
  QString reference;
  QDate date;


public:
    produits();
    produits(qreal p,QString r,QDate d):prix(p),reference(r),date(d){}
    qreal get_prix(){return prix;}
    QString get_reference(){return reference;}
    QDate get_date(){return date;}
    void set_prix(qreal p){prix=p;}
    void set_reference(QString r){reference=r;}
    void set_date(QDate d){date=d;}

    bool ajouter();
    QSqlQueryModel * afficher();

    bool modifier();

    bool supprimer(int);
    QSqlQueryModel *rechercher_prix(qreal);
    QSqlQueryModel *rechercher_date(QDate);
    QSqlQueryModel *rechercher_reference(QString);
    QSqlQueryModel *rechercher_critere(qreal,QString,QDate);

};

#endif // PRODUITS_H


