#include "Connection.h"

Connection::Connection()
{
    // Use the ODBC driver
    db = QSqlDatabase::addDatabase("QODBC");

    // Configure connection parameters (change these or make configurable)
    db.setDatabaseName("Source_Projet2A");   // ODBC Data Source Name
    db.setUserName("SummerClub");            // DB username
    db.setPassword("esprit25");              // DB password
}

bool Connection::openConnection()
{
    if (db.open()) {
        qDebug() << "Successfully connected to Oracle via ODBC.";
        return true;
    } else {
        qDebug() << "Connection error:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Error", "Failed to connect to database!");
        return false;
    }
}

void Connection::closeConnection()
{
    db.close();
    qDebug() << "Database connection closed.";
}
