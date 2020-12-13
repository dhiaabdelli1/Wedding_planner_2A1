#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <functional>

class login
{
public:
    login();
    bool sign_in(QString,QString);
    bool sign_up(QString,QString);
    int hash(QString);
};

#endif // LOGIN_H
