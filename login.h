#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void onLoginClicked();

private:
    Ui::Login *ui;
    
    // Simple hardcoded credentials
    const QString ADMIN_USERNAME = "admin";
    const QString ADMIN_PASSWORD = "admin";
    
    bool validateCredentials(const QString &username, const QString &password);
    void showError(const QString &message);
    void clearError();
};

#endif // LOGIN_H