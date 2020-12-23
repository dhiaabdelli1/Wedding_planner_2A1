#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <functional>

class login
{
    QString current_user;
    QString current_pwd;
public:
    login();
    login(QString user, QString pwd):current_user(user),current_pwd(pwd){}
    bool sign_in(QString,QString);
    bool sign_up(QString,QString);
    bool modifier_mdp(QString,QString,QString);
    int hash(QString);
    QString get_current_user(){return current_user;}
    QString get_current_pwd(){return current_pwd;}
    void set_current_user(QString u){current_user=u;}
    void set_current_pwd(QString m){current_pwd=m;}
};

#endif // LOGIN_H
