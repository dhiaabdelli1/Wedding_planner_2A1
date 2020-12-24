#include "connexion.h"


connexion::connexion()
{

}

bool connexion::createConnection()
{
    bool test=false;
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("wedding planner");
    db.setUserName("iheb1");
    db.setPassword("iheb1");

    if (db.open())
        test=true;

    return test;
}

bool connexion::createConnexion()
{
    bool test=false;
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("gestion_invites");
    db.setUserName("dhia");
    db.setPassword("dhia");

    if (db.open())
        test=true;

    return test;
}




