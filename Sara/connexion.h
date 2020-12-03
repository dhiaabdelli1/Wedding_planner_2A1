#ifndef CONNEXION_H
#define CONNEXION_H


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connexion
{private:

public:
    QSqlDatabase GestionStock;
    Connexion();
    bool createconnect();
    void closeconnection();
};


#endif // CONNEXION_H
