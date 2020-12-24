#include "login.h"

login::login()
{

}

bool login::sign_in(QString uname,QString pwd)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM USERS WHERE username=:username AND password=:password");
    qry.bindValue(":username",uname);
    qry.bindValue(":password",this->hash(pwd));

    return qry.exec() && qry.next();

}

bool login::sign_up(QString uname,QString pwd)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO USERS (username,password)"
                "VALUES (:username,:password)");
    qry.bindValue(":username",uname);
    qry.bindValue(":password",this->hash(pwd));

    return qry.exec();
}

int login::hash(QString pwd)
{
    std::hash<std::string> hash;
    return hash(pwd.toStdString());
}
