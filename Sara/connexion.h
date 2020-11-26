#ifndef CONNEXION_H
#define CONNEXION_H


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connexion
{private:

public:
    QSqlDatabase db;
    Connexion();
    bool createconnect();
    void closeconnection();
};


#endif // CONNEXION_H
