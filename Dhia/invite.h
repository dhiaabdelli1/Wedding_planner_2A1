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
class invite
{

    int cin;
    QString nom;
    QString prenom;
    QDate date_naissance;
    QString mail;
    QString sexe;

public:
    invite();
    invite(int c,QString n, QString p, QDate d, QString m, QString s):cin(c),nom(n),prenom(p),date_naissance(d),mail(m),sexe(s){}
    int get_cin(){return cin;}
    QString get_nom(){return nom;}
    QString get_prenom(){return prenom;}
    QDate get_date_naissance(){return date_naissance;}
    QString get_email(){return mail;}
    QString get_sexe(){return sexe;}

    void set_cin(int c){cin=c;}
    void set_nom(QString n){nom=n;}
    void set_prenom(QString p){prenom=p;}
    void set_date_naissance(QDate d){date_naissance=d;}
    void set_mail(QString m){mail=m;}
    void set_sexe(QString s){sexe=s;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);

    QSqlQueryModel *rechercher_cin(int);
    QSqlQueryModel *rechercher_sexe(QString);
    QSqlQueryModel *rechercher_date(QDate);
    QSqlQueryModel *rechercher_combinaison(QString,QString,QDate);

    void exporter(QTableView *table);

    QSqlQueryModel *trier(QString,QString);

};

#endif // INVITE_H
