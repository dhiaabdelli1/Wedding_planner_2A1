#include "connexion.h"
#include "QSqlDatabase"
connexion::connexion()
{

}

bool connexion::createConnection()
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
