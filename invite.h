#ifndef INVITE_H
#define INVITE_H
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class invite
{

    int cin;
    QString nom;
    QString prenom;
    int age;
    QDate date_naissance;
    QString mail;
    QString sexe;
public:
    invite();
    invite(int,QString,QString,int,QString,QString);
    int get_cin(){return cin;}
    QString get_nom(){return nom;}
    QString get_prenom(){return prenom;}
    int get_age(){return age;}
    QDate get_date_naissance(){return date_naissance;}
    QString get_email(){return mail;}
    QString get_sexe(){return sexe;}

    void set_cin(int c){cin=c;}
    void set_nom(QString n){nom=n;}
    void set_prenom(QString p){prenom=p;}
    void set_age(int a){age=a;}
    void set_date_naissance(QDate d){date_naissance=d;}
    void set_mail(QString m){mail=m;}
    void set_sexe(QString s){sexe=s;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);

};

#endif // INVITE_H
