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

    //current_user=uname;

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

bool login::modifier_mdp(QString user,QString old_mdp,QString new_mdp)
{
    QSqlQuery qry;
    qry.prepare("UPDATE USERS SET password=:new_password WHERE (username=:user AND password=:old_password)");
    qry.bindValue(":user",user);
    qry.bindValue(":old_password",this->hash(old_mdp));
    qry.bindValue(":new_password",this->hash(new_mdp));

    return qry.exec();
}

int login::hash(QString pwd)
{
    std::hash<std::string> hash;
    return hash(pwd.toStdString());
}


