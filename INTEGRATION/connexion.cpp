#include "connexion.h"
#include "QSqlDatabase"
connexion::connexion()
{

}

bool connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("testqt");
db.setUserName("ELLA");//inserer nom de l'utilisateur
db.setPassword("ella");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}





