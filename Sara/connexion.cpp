#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("");
db.setUserName("");
db.setPassword("");

if (db.open())
test=true;

    return  test;
}
