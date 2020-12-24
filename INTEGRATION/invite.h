#ifndef INVITE_H
#define INVITE_H
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
#include <QPrinter>
#include <QTextDocument>
#include <QDebug>
#include <QSqlTableModel>
#include "table.h"
#include <QMessageBox>

class invite
{

    //int cin;
    QString cin;
    QString nom;
    QString prenom;
    QDate date_naissance;
    QString mail;
    QString sexe;
    QString telephone;
    int num_table;

public:
    invite();
    invite(QString c,QString n, QString p, QDate d, QString m, QString s,QString t):cin(c),nom(n),prenom(p),date_naissance(d),mail(m),sexe(s),telephone(t){}
    //GETTERS
    QString get_cin(){return cin;}
    QString get_nom(){return nom;}
    QString get_prenom(){return prenom;}
    QDate get_date_naissance(){return date_naissance;}
    QString get_email(){return mail;}
    QString get_sexe(){return sexe;}
    int get_num_table(){return num_table;}


    //SETTERS
    void set_cin(QString c){cin=c;}
    void set_nom(QString n){nom=n;}
    void set_prenom(QString p){prenom=p;}
    void set_date_naissance(QDate d){date_naissance=d;}
    void set_mail(QString m){mail=m;}
    void set_sexe(QString s){sexe=s;}

    //CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);

    //FCTS Métiers
    QSqlQueryModel *rechercher_cin(QString);
    QSqlQueryModel *rechercher_nom(QString);
    QSqlQueryModel *rechercher_sexe(QString);
    QSqlQueryModel *rechercher_date(QDate);
    QSqlQueryModel *rechercher_email(QString);
    QSqlQueryModel *rechercher_combinaison_all(QString,QString,QDate);
    QSqlQueryModel *rechercher_combinaison_nom_date(QString,QDate);
    QSqlQueryModel *rechercher_combinaison_sexe_date(QString,QDate);
    QSqlQueryModel *rechercher_combinaison_nom_sexe(QString,QString);
    QSqlQueryModel *trier(QString,QString);
    int affecter_table(QString,int,int);
    QSqlQueryModel *update(QString,QString,QString);
    void exporter(QTableView *table);
    //FCTS Supp
    int count(QString);
    int count_date(QDate,QDate,QString);

};

#endif // INVITE_H
