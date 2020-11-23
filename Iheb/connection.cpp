#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
 QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test4");//inserer le nom de la source de données ODBC
db.setUserName("iheb");//inserer nom de l'utilisateur
db.setPassword("iheb");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::fermerconnexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

   db.close();
}
