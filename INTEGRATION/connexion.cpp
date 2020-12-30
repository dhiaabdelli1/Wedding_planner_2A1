#include "connexion.h"


connexion::connexion()
{

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




