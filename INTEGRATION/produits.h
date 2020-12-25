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
{ int reference_p;
  int quantite_p;
  QString type_p;
  qreal prix_p;
  QDate date_p;


public:
    produits();
    produits(int r,int q,QString t,qreal p,QDate d):reference_p(r),quantite_p (q),type_p (t),prix_p(p),date_p(d){}

    int get_reference_p(){return reference_p;}
    int get_quantite_p(){return quantite_p;}
    qreal get_prix_p(){return prix_p;}
    QString get_type_p(){return type_p;}
    QDate get_date_p(){return date_p;}


    void set_reference_p(int r){reference_p=r;}
    void set_quantite_p(int q){quantite_p=q;}
    void set_prix_p(qreal p){prix_p=p;}
    void set_type_p(QString t){type_p=t;}
    void set_date_p(QDate d){date_p=d;}

    bool ajouter_p();
    QSqlQueryModel * afficher_p();

    bool supprimer_p(int);
    QSqlQueryModel *rechercher_reference_p(int);
    QSqlQueryModel *rechercher_quantite_p(int);
    QSqlQueryModel *rechercher_type_p(QString);
    QSqlQueryModel *rechercher_date_p(QDate);
    QSqlQueryModel *rechercher_critere_p(int,QString,QDate);

};

#endif // PRODUITS_H

