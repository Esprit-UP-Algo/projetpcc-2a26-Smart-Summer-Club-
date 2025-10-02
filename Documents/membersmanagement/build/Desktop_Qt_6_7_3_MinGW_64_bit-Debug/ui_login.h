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

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QFrame *frame;
    QLabel *label;
    QLineEdit *username;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *password;
    QPushButton *log_in;
    QPushButton *singup;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(1280, 720);
        login->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(login);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(519, -1, 791, 721));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 206, 194);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(180, 160, 191, 71));
        label->setMinimumSize(QSize(151, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(13);
        font.setBold(true);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 140, 140); border-radius: 16px;\n"
"font: 700 13pt \"Segoe UI\";background-color: rgb(17, 140, 140);"));
        username = new QLineEdit(frame);
        username->setObjectName("username");
        username->setGeometry(QRect(150, 350, 391, 28));
        username->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"Segoe UI\";"));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 290, 101, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 430, 91, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        password = new QLineEdit(frame);
        password->setObjectName("password");
        password->setGeometry(QRect(150, 480, 391, 28));
        password->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"Segoe UI\";"));
        password->setEchoMode(QLineEdit::EchoMode::Password);
        log_in = new QPushButton(frame);
        log_in->setObjectName("log_in");
        log_in->setGeometry(QRect(90, 580, 211, 81));
        log_in->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        log_in->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 140, 140); border-radius: 16px;\n"
"font: 700 11pt \"Segoe UI\";\n"
""));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::UserAvailable));
        log_in->setIcon(icon);
        singup = new QPushButton(frame);
        singup->setObjectName("singup");
        singup->setGeometry(QRect(419, 578, 211, 81));
        singup->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        singup->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 140, 140); border-radius: 16px;\n"
"font: 700 11pt \"Segoe UI\";"));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ContactNew));
        singup->setIcon(icon1);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("login", "<html><head/><body><p align=\"center\">Welcome Back</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("login", "username", nullptr));
        label_3->setText(QCoreApplication::translate("login", "password", nullptr));
        log_in->setText(QCoreApplication::translate("login", "Log In", nullptr));
        singup->setText(QCoreApplication::translate("login", "Sing up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
