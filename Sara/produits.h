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
#include <QComboBox>
#include <QApplication>
#include <QWidget>
#include <QSound>

class produits
{ int reference;
  int quantite;
  QString type;
  qreal prix;
  QDate datee;


public:
    produits();
    produits(int r,int q,QString t,qreal p,QDate d):reference(r),quantite (q),type (t),prix(p),datee(d){}

    int get_reference(){return reference;}
    int get_quantite(){return quantite;}
    qreal get_prix(){return prix;}
    QString get_type(){return type;}
    QDate get_datee(){return datee;}


    void set_reference(int r){reference=r;}
    void set_quantite(int q){quantite=q;}
    void set_prix(qreal p){prix=p;}
    void set_type(QString t){type=t;}
    void set_date(QDate d){datee=d;}

    bool ajouter();
    QSqlQueryModel * afficher();

    bool supprimer(int);
    QSqlQueryModel *rechercher_reference(int);
    QSqlQueryModel *rechercher_type(QString);
    QSqlQueryModel *rechercher_datee(QDate);
    QSqlQueryModel *rechercher_critere(int,QString,QDate);

};

#endif // PRODUITS_H


