#include "connection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_projet2A");//inserer le nom de la source de données
    db.setUserName("sirin");//inserer nom de l'utilisateur
    db.setPassword("esprit25");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
}
