#include "employeradmin.h"
#include "login.h"
#include "Connection.h"

#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Print available SQL drivers (useful to verify QODBC is available)
    qDebug() << "Available Qt SQL drivers:" << QSqlDatabase::drivers();

    // Try to open database connection and log the result
    Connection connexion;
    bool dbOk = connexion.openConnection();
    if (!dbOk) {
        qDebug() << "Database connection failed. You can still open the app but DB features may not work.";
    } else {
        qDebug() << "Database connection succeeded.";
    }

    // Show login dialog first
    Login loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // Login successful, show main application
        EmployerAdmin w;
        w.show();
        int ret = a.exec();

        // Close connection on exit
    if (dbOk) connexion.closeConnection();
        return ret;
    } else {
        // Login cancelled or failed, close DB if open and exit application
    if (dbOk) connexion.closeConnection();
        return 0;
    }
}
