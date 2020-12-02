#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class connection
{
private:
    QSqlDatabase db;
public:
    connection();
    bool createconnection();
};

#endif // CONNEXION_H
