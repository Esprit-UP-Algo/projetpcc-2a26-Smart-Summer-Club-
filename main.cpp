#include "employeradmin.h"
#include "login.h"
#include "Connection.h"
#include "connexion_ard.h"

#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Print available SQL drivers (useful to verify QODBC is available)
    qDebug() << "Available Qt SQL drivers:" << QSqlDatabase::drivers();

    // Initialize Arduino connection
    Arduino* arduino = new Arduino(&a);
    qDebug() << "\n=== Initializing Arduino Connection ===";
    int connectionResult = arduino->connect_arduino();
    
    if (connectionResult == 0) {
        qDebug() << "Arduino connected successfully on port:" << arduino->getarduino_port_name();
    } else if (connectionResult == -1) {
        qDebug() << "ERROR: Arduino device not found. Application will continue without Arduino support.";
        qDebug() << "Error:" << arduino->getLastError();
    } else {
        qDebug() << "ERROR: Failed to open Arduino port. Application will continue without Arduino support.";
        qDebug() << "Error:" << arduino->getLastError();
    }

    // Try to open database connection once via the Connection singleton and log the result
    Connection* connexion = Connection::getInstance();
    bool dbOk = connexion->openConnection();
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
        w.setArduino(arduino);  // Pass Arduino instance to main window
        w.show();
        int ret = a.exec();

        // Close connections on exit
        if (arduino->isConnected()) {
            arduino->close_arduino();
        }
        if (dbOk) connexion->closeConnection();
        return ret;
    } else {
        // Login cancelled or failed, close connections and exit application
        if (arduino->isConnected()) {
            arduino->close_arduino();
        }
        if (dbOk) connexion->closeConnection();
        return 0;
    }
}
