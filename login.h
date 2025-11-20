#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
class QLineEdit;
namespace Ui {
class Login;
}
QT_END_NAMESPACE

struct LoggedInUser {
    QString cin;
    QString firstName;
    QString lastName;
    QString department;
    QByteArray photo;
    bool isAdmin;
};

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

    static LoggedInUser currentUser;

private slots:
    void onNextClicked();
    void onLoginClicked();
    void onBackClicked();

private:
    Ui::Login *ui;
    // Simple hardcoded credentials
    const QString ADMIN_USERNAME = "adembg91@gmail.com";
    const QString ADMIN_PASSWORD = "admin";
    bool validateCredentials(const QString &username, const QString &password);
    bool checkTwoFactorEnabled(const QString &cin);
    bool validateTOTPCode(const QString &cin, const QString &code);
    void showError(const QString &message);
    void clearError();
    void shakePasswordField();
    void successAnimationEmail();
    void successAnimationLogin();
};

#endif // LOGIN_H