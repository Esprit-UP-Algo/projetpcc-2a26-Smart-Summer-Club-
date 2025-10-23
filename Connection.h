#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

// Simple DB connection helper
class Connection
{
private:
    QSqlDatabase db;  // QSqlDatabase instance

public:
    Connection();                 // Constructor
    bool openConnection();        // Open the database connection
    void closeConnection();       // Close the database connection
};

#endif // CONNECTION_H
