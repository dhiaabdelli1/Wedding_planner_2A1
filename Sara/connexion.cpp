#include "connexion.h"
#include "QSqlDatabase"
Connexion::Connexion()
{

}

bool Connexion::createconnect()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("GestionStock");
db.setUserName("sara4");
db.setPassword("sara4");

if (db.open())
test=true;

    return  test;
}
