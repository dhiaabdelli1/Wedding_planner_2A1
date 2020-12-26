#include "connexion.h"


connexion::connexion()
{

}

bool connexion::createConnection()
{
    bool test=false;
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("madness");
    db.setUserName("mad");
    db.setPassword("mad");

    if (db.open())
        test=true;

    return test;
}

bool connexion::createConnexion()
{
    bool test=false;
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("madness");
    db.setUserName("mad");
    db.setPassword("mad");

    if (db.open())
        test=true;

    return test;
}




