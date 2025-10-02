#include "employeradmin.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Show login dialog first
    Login loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // Login successful, show main application
        EmployerAdmin w;
        w.show();
        return a.exec();
    } else {
        // Login cancelled or failed, exit application
        return 0;
    }
}
