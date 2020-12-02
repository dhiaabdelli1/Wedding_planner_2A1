#include "connexion.h"
#include "QSqlDatabase"
connexion::connexion()
{

}

bool connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("testbd");
db.setUserName("ELA");//inserer nom de l'utilisateur
db.setPassword("elaa123");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
