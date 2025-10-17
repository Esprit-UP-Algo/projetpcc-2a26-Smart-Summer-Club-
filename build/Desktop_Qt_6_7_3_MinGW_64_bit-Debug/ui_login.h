/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *mainLayout;
    QFrame *loginFrame;
    QVBoxLayout *loginLayout;
    QLabel *logo;
    QLabel *logoLabel;
    QLabel *subtitleLabel;
    QSpacerItem *topSpacer;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *errorLabel;
    QPushButton *loginButton;
    QSpacerItem *bottomSpacer;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(443, 707);
        Login->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                               stop:0 #16a5b3, stop:1 #139aa6);\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"    border: 1px solid rgba(0,0,0,0.1);\n"
"}\n"
"\n"
"#logoLabel {\n"
"    font-size: 32px;\n"
"    font-weight: bold;\n"
"    color: #16a5b3;\n"
"    margin-bottom: 10px;\n"
"}\n"
"\n"
"#subtitleLabel {\n"
"    font-size: 16px;\n"
"    color: #7f8c8d;\n"
"    margin-bottom: 30px;\n"
"}\n"
"\n"
"QLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #2c3e50;\n"
"    margin-bottom: 5px;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    padding: 15px;\n"
"    border: 2px solid #e0e4e7;\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"    margin-bottom: 15px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #16a5b3;\n"
"    outline: none;\n"
"}\n"
"\n"
"#loginButton {\n"
"    background-color: #16a5b3;\n"
"    color: white;\n"
"    b"
                        "order: none;\n"
"    padding: 15px;\n"
"    border-radius: 8px;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    margin-top: 10px;\n"
"}\n"
"\n"
"#loginButton:hover {\n"
"    background-color: #139aa6;\n"
"}\n"
"\n"
"#loginButton:pressed {\n"
"    background-color: #0f858f;\n"
"}\n"
"\n"
"#errorLabel {\n"
"    color: #e74c3c;\n"
"    font-size: 13px;\n"
"    font-weight: normal;\n"
"    margin-top: 10px;\n"
"}"));
        mainLayout = new QVBoxLayout(Login);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(40, 40, 40, 40);
        loginFrame = new QFrame(Login);
        loginFrame->setObjectName("loginFrame");
        loginLayout = new QVBoxLayout(loginFrame);
        loginLayout->setObjectName("loginLayout");
        loginLayout->setContentsMargins(40, 40, 40, 40);
        logo = new QLabel(loginFrame);
        logo->setObjectName("logo");
        logo->setMinimumSize(QSize(0, 100));
        logo->setStyleSheet(QString::fromUtf8("padding-left :90;"));
        logo->setMargin(0);

        loginLayout->addWidget(logo);

        logoLabel = new QLabel(loginFrame);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginLayout->addWidget(logoLabel);

        subtitleLabel = new QLabel(loginFrame);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginLayout->addWidget(subtitleLabel);

        topSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginLayout->addItem(topSpacer);

        usernameLabel = new QLabel(loginFrame);
        usernameLabel->setObjectName("usernameLabel");

        loginLayout->addWidget(usernameLabel);

        usernameLineEdit = new QLineEdit(loginFrame);
        usernameLineEdit->setObjectName("usernameLineEdit");

        loginLayout->addWidget(usernameLineEdit);

        passwordLabel = new QLabel(loginFrame);
        passwordLabel->setObjectName("passwordLabel");

        loginLayout->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(loginFrame);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        loginLayout->addWidget(passwordLineEdit);

        errorLabel = new QLabel(loginFrame);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginLayout->addWidget(errorLabel);

        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        loginButton->setIcon(icon);

        loginLayout->addWidget(loginButton);

        bottomSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginLayout->addItem(bottomSpacer);


        mainLayout->addWidget(loginFrame);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "VIBRA CLUB - Login", nullptr));
        logo->setText(QString());
        logoLabel->setText(QCoreApplication::translate("Login", "VIBRA CLUB", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("Login", "Application for  club managemnt", nullptr));
        usernameLabel->setText(QCoreApplication::translate("Login", "Username:", nullptr));
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter your username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("Login", "Password:", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter your password", nullptr));
        errorLabel->setText(QString());
        loginButton->setText(QCoreApplication::translate("Login", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
