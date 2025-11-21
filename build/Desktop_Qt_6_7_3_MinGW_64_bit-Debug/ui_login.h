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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *mainLayout;
    QFrame *mainFrame;
    QHBoxLayout *horizontalLayout;
    QFrame *leftFrame;
    QVBoxLayout *leftLayout;
    QSpacerItem *leftTopSpacer;
    QLabel *beachLabel;
    QSpacerItem *leftBottomSpacer;
    QFrame *rightFrame;
    QVBoxLayout *rightLayout;
    QFrame *logoFrame;
    QHBoxLayout *logoLayout;
    QSpacerItem *logoLeftSpacer;
    QLabel *logoCircle;
    QLabel *logoLabel;
    QSpacerItem *logoRightSpacer;
    QStackedWidget *loginStackedWidget;
    QWidget *emailPage;
    QVBoxLayout *emailPageLayout;
    QLabel *loginTitleLabel;
    QLabel *emailInstructionLabel;
    QSpacerItem *emailTopSpacer;
    QLineEdit *emailLineEdit;
    QLabel *emailErrorLabel;
    QSpacerItem *emailMiddleSpacer;
    QPushButton *nextButton;
    QSpacerItem *emailBottomSpacer;
    QWidget *passwordPage;
    QVBoxLayout *passwordPageLayout;
    QLabel *welcomeLabel;
    QLabel *emailLabel;
    QLabel *subtitleLabel;
    QSpacerItem *passwordTopSpacer;
    QLineEdit *passwordLineEdit;
    QLabel *passwordErrorLabel;
    QSpacerItem *passwordMiddleSpacer;
    QFrame *passwordButtonFrame;
    QHBoxLayout *passwordButtonLayout;
    QPushButton *backButton;
    QPushButton *loginButton;
    QSpacerItem *passwordBottomSpacer;
    QSpacerItem *bottomSpacer;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(1101, 663);
        Login->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background-color: #4DB6C3;\n"
"    border-radius: 20px;\n"
"}\n"
"\n"
"#mainFrame {\n"
"    background-color: white;\n"
"    border-radius: 20px;\n"
"    border: none;\n"
"}\n"
"\n"
"#leftFrame {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                               stop:0 #4DB6C3, stop:1 #2E9CAA);\n"
"    border-radius: 20px 0px 0px 20px;\n"
"}\n"
"\n"
"#rightFrame {\n"
"    background-color: white;\n"
"    border-radius: 0px 20px 20px 0px;\n"
"    padding: 40px;\n"
"}\n"
"\n"
"#beachLabel {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"#logoCircle {\n"
"    background-color: transparent;\n"
"    border-radius: 30px;\n"
"    border: none;\n"
"}\n"
"\n"
"#welcomeLabel {\n"
"    font-size: 28px;\n"
"    font-weight: bold;\n"
"    color: #2c3e50;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"#emailLabel {\n"
"    font-size: 16px;\n"
"    color: #7f8c8d;\n"
"    background-color: transparent;\n"
"    border: none"
                        ";\n"
"    margin-bottom: 20px;\n"
"}\n"
"\n"
"#subtitleLabel {\n"
"    font-size: 14px;\n"
"    color: #4DB6C3;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    margin-bottom: 30px;\n"
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
"    border-color: #4DB6C3;\n"
"    outline: none;\n"
"}\n"
"\n"
"#loginButton, #nextButton {\n"
"    background-color: #4DB6C3;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 15px 30px;\n"
"    border-radius: 25px;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    margin-right: 10px;\n"
"}\n"
"\n"
"#loginButton:hover, #nextButton:hover {\n"
"    background-color: #2E9CAA;\n"
"}\n"
"\n"
"#loginButton:pressed, #nextButton:pressed {\n"
"    background-color: #1E7A85;\n"
"}\n"
"\n"
"#backButton {\n"
"    background-color: transparent;\n"
"    color: #4DB6C3;\n"
""
                        "    border: 2px solid #4DB6C3;\n"
"    padding: 15px 30px;\n"
"    border-radius: 25px;\n"
"    font-size: 16px;\n"
"    font-weight: 600;\n"
"    margin-right: 10px;\n"
"}\n"
"\n"
"#backButton:hover {\n"
"    background-color: #4DB6C3;\n"
"    color: white;\n"
"}\n"
"\n"
"#backButton:pressed {\n"
"    background-color: #2E9CAA;\n"
"}\n"
"\n"
"#errorLabel {\n"
"    color: #e74c3c;\n"
"    font-size: 13px;\n"
"    font-weight: normal;\n"
"    margin-top: 10px;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}"));
        mainLayout = new QVBoxLayout(Login);
        mainLayout->setSpacing(20);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainFrame = new QFrame(Login);
        mainFrame->setObjectName("mainFrame");
        horizontalLayout = new QHBoxLayout(mainFrame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftFrame = new QFrame(mainFrame);
        leftFrame->setObjectName("leftFrame");
        leftFrame->setMinimumSize(QSize(450, 0));
        leftLayout = new QVBoxLayout(leftFrame);
        leftLayout->setObjectName("leftLayout");
        leftLayout->setContentsMargins(40, 40, 40, 40);
        leftTopSpacer = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(leftTopSpacer);

        beachLabel = new QLabel(leftFrame);
        beachLabel->setObjectName("beachLabel");
        beachLabel->setMinimumSize(QSize(300, 300));
        beachLabel->setPixmap(QPixmap(QString::fromUtf8(":/icons/assests/VibraClubBanner.png")));
        beachLabel->setScaledContents(true);
        beachLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        leftLayout->addWidget(beachLabel);

        leftBottomSpacer = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(leftBottomSpacer);


        horizontalLayout->addWidget(leftFrame);

        rightFrame = new QFrame(mainFrame);
        rightFrame->setObjectName("rightFrame");
        rightFrame->setMinimumSize(QSize(450, 0));
        rightLayout = new QVBoxLayout(rightFrame);
        rightLayout->setObjectName("rightLayout");
        rightLayout->setContentsMargins(40, 40, 40, 40);
        logoFrame = new QFrame(rightFrame);
        logoFrame->setObjectName("logoFrame");
        logoFrame->setMinimumSize(QSize(0, 80));
        logoLayout = new QHBoxLayout(logoFrame);
        logoLayout->setObjectName("logoLayout");
        logoLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoLayout->addItem(logoLeftSpacer);

        logoCircle = new QLabel(logoFrame);
        logoCircle->setObjectName("logoCircle");
        logoCircle->setMinimumSize(QSize(60, 60));
        logoCircle->setMaximumSize(QSize(60, 60));
        logoCircle->setPixmap(QPixmap(QString::fromUtf8(":/icons/assests/VibraClubLogo.png")));
        logoCircle->setScaledContents(true);
        logoCircle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        logoLayout->addWidget(logoCircle);

        logoLabel = new QLabel(logoFrame);
        logoLabel->setObjectName("logoLabel");

        logoLayout->addWidget(logoLabel);

        logoRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoLayout->addItem(logoRightSpacer);


        rightLayout->addWidget(logoFrame);

        loginStackedWidget = new QStackedWidget(rightFrame);
        loginStackedWidget->setObjectName("loginStackedWidget");
        emailPage = new QWidget();
        emailPage->setObjectName("emailPage");
        emailPageLayout = new QVBoxLayout(emailPage);
        emailPageLayout->setObjectName("emailPageLayout");
        loginTitleLabel = new QLabel(emailPage);
        loginTitleLabel->setObjectName("loginTitleLabel");
        loginTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        emailPageLayout->addWidget(loginTitleLabel);

        emailInstructionLabel = new QLabel(emailPage);
        emailInstructionLabel->setObjectName("emailInstructionLabel");
        emailInstructionLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        emailPageLayout->addWidget(emailInstructionLabel);

        emailTopSpacer = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        emailPageLayout->addItem(emailTopSpacer);

        emailLineEdit = new QLineEdit(emailPage);
        emailLineEdit->setObjectName("emailLineEdit");

        emailPageLayout->addWidget(emailLineEdit);

        emailErrorLabel = new QLabel(emailPage);
        emailErrorLabel->setObjectName("emailErrorLabel");
        emailErrorLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        emailPageLayout->addWidget(emailErrorLabel);

        emailMiddleSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        emailPageLayout->addItem(emailMiddleSpacer);

        nextButton = new QPushButton(emailPage);
        nextButton->setObjectName("nextButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/next.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        nextButton->setIcon(icon);

        emailPageLayout->addWidget(nextButton);

        emailBottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        emailPageLayout->addItem(emailBottomSpacer);

        loginStackedWidget->addWidget(emailPage);
        passwordPage = new QWidget();
        passwordPage->setObjectName("passwordPage");
        passwordPageLayout = new QVBoxLayout(passwordPage);
        passwordPageLayout->setObjectName("passwordPageLayout");
        welcomeLabel = new QLabel(passwordPage);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        passwordPageLayout->addWidget(welcomeLabel);

        emailLabel = new QLabel(passwordPage);
        emailLabel->setObjectName("emailLabel");
        emailLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        passwordPageLayout->addWidget(emailLabel);

        subtitleLabel = new QLabel(passwordPage);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        passwordPageLayout->addWidget(subtitleLabel);

        passwordTopSpacer = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        passwordPageLayout->addItem(passwordTopSpacer);

        passwordLineEdit = new QLineEdit(passwordPage);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        passwordPageLayout->addWidget(passwordLineEdit);

        passwordErrorLabel = new QLabel(passwordPage);
        passwordErrorLabel->setObjectName("passwordErrorLabel");
        passwordErrorLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        passwordPageLayout->addWidget(passwordErrorLabel);

        passwordMiddleSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        passwordPageLayout->addItem(passwordMiddleSpacer);

        passwordButtonFrame = new QFrame(passwordPage);
        passwordButtonFrame->setObjectName("passwordButtonFrame");
        passwordButtonLayout = new QHBoxLayout(passwordButtonFrame);
        passwordButtonLayout->setObjectName("passwordButtonLayout");
        backButton = new QPushButton(passwordButtonFrame);
        backButton->setObjectName("backButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/back.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        backButton->setIcon(icon1);

        passwordButtonLayout->addWidget(backButton);

        loginButton = new QPushButton(passwordButtonFrame);
        loginButton->setObjectName("loginButton");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/login.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        loginButton->setIcon(icon2);

        passwordButtonLayout->addWidget(loginButton);


        passwordPageLayout->addWidget(passwordButtonFrame);

        passwordBottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        passwordPageLayout->addItem(passwordBottomSpacer);

        loginStackedWidget->addWidget(passwordPage);

        rightLayout->addWidget(loginStackedWidget);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(bottomSpacer);


        horizontalLayout->addWidget(rightFrame);


        mainLayout->addWidget(mainFrame);


        retranslateUi(Login);

        loginStackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "VIBRA CLUB - Login", nullptr));
        beachLabel->setText(QString());
        logoCircle->setText(QString());
        logoLabel->setStyleSheet(QCoreApplication::translate("Login", "font-size: 24px; font-weight: bold; color: #4DB6C3; margin-left: 10px;", nullptr));
        logoLabel->setText(QCoreApplication::translate("Login", "VIBRA CLUB", nullptr));
        loginTitleLabel->setText(QCoreApplication::translate("Login", "Sign In", nullptr));
        loginTitleLabel->setStyleSheet(QCoreApplication::translate("Login", "font-size: 28px; font-weight: bold; color: #2c3e50;", nullptr));
        emailInstructionLabel->setText(QCoreApplication::translate("Login", "Enter your email to continue", nullptr));
        emailInstructionLabel->setStyleSheet(QCoreApplication::translate("Login", "font-size: 16px; color: #7f8c8d; margin-bottom: 20px;", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "\360\237\223\247 Enter your email address", nullptr));
        emailErrorLabel->setText(QString());
        emailErrorLabel->setStyleSheet(QCoreApplication::translate("Login", "color: #e74c3c; font-size: 13px;", nullptr));
        nextButton->setText(QCoreApplication::translate("Login", "Next", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("Login", "Welcome Back", nullptr));
        emailLabel->setText(QCoreApplication::translate("Login", "user@example.com", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("Login", "Application for club management", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "\360\237\224\222 Enter your password", nullptr));
        passwordErrorLabel->setText(QString());
        passwordErrorLabel->setStyleSheet(QCoreApplication::translate("Login", "color: #e74c3c; font-size: 13px;", nullptr));
        backButton->setText(QCoreApplication::translate("Login", "Back", nullptr));
        loginButton->setText(QCoreApplication::translate("Login", "Log In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
