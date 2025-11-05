#include "Connection.h"

// Private constructor
Connection::Connection()
{
    // Use the ODBC driver (created once for the singleton)
    db = QSqlDatabase::addDatabase("QODBC");

    // Default connection parameters (can be changed later or made configurable)
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("SummerClub");
    db.setPassword("esprit25");
}

Connection::~Connection()
{
    if (db.isOpen()) db.close();
}

// Return the singleton instance
Connection* Connection::getInstance()
{
    static Connection instance;
    return &instance;
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
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}
