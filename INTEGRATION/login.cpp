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

bool login::sign_in_code(QString uname,QString code)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM USERS WHERE username=:username AND pwd_reset=:pwd_reset");
    qry.bindValue(":username",uname);
    qry.bindValue(":pwd_reset",this->hash(code));

    //current_user=uname;

    return qry.exec() && qry.next();

}

bool login::sign_up(QString uname,QString pwd,QString email)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO USERS (username,password,email)"
                "VALUES (:username,:password,:email)");
    qry.bindValue(":username",uname);
    qry.bindValue(":password",this->hash(pwd));
    qry.bindValue(":email",email);

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


QString login::code_generator()
{
    static const char alphanum[] =
    "0123456789"
    "!@#$%^&*"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

    int stringLength = sizeof(alphanum) - 1;

    srand(time(0));
        QString Str;
        for(unsigned int i = 0; i < 7; ++i)
        {
        Str += alphanum[rand() % stringLength];

        }
        return Str;
}


bool login::update_mpd_reset(QString uname,QString code)
{
    QSqlQuery qry;
    qry.prepare("UPDATE USERS SET pwd_reset=:pwd_reset WHERE (username=:user)");
    qry.bindValue(":user",uname);
    qry.bindValue(":pwd_reset",this->hash(code));

    return qry.exec();
}
bool login::delete_account(QString uname)
{
    QSqlQuery qry;
    qry.prepare("Delete from USERS where username = :username");
    qry.bindValue(":username",uname);
    return qry.exec();
}
