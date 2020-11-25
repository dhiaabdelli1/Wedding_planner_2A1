#include "connection.h"
#include <QString>

connection::connection()
{

}
bool connection::createconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("alpha");
db.setUserName("mohamed");
db.setPassword("mohamed");

if (db.open())
test=true;

    return  test;
}
