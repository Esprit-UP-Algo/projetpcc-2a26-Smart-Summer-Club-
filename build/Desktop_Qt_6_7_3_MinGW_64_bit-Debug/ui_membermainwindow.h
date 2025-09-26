/********************************************************************************
** Form generated from reading UI file 'membermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBERMAINWINDOW_H
#define UI_MEMBERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_membermainwindow
{
public:
    QWidget *centralwidget;
    QFrame *sidebar;
    QPushButton *btnAccueil;
    QPushButton *btnGestion;
    QPushButton *btnStats;
    QPushButton *btnLogout;
    QLabel *label_7;
    QFrame *topbar;
    QLineEdit *searchMember;
    QComboBox *comboSort;
    QPushButton *btnExportPDF;
    QFrame *mainContent;
    QLineEdit *deleteIDEdit;
    QTableWidget *tableWidget;
    QGroupBox *addMemberBox;
    QLineEdit *editID;
    QLineEdit *editLastName;
    QLineEdit *editFirstName;
    QLineEdit *editContact;
    QComboBox *comboType;
    QDateEdit *dateEdit;
    QPushButton *btnAnnuler;
    QPushButton *btnValider;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *editID_2;
    QPushButton *btnDeleteID_3;
    QPushButton *btnDeleteID_2;
    QLabel *label_9;
    QLabel *label_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *membermainwindow)
    {
        if (membermainwindow->objectName().isEmpty())
            membermainwindow->setObjectName("membermainwindow");
        membermainwindow->resize(1920, 1080);
        centralwidget = new QWidget(membermainwindow);
        centralwidget->setObjectName("centralwidget");
        sidebar = new QFrame(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setGeometry(QRect(0, 0, 230, 910));
        sidebar->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(216, 195, 165);"));
        btnAccueil = new QPushButton(sidebar);
        btnAccueil->setObjectName("btnAccueil");
        btnAccueil->setGeometry(QRect(30, 310, 180, 40));
        btnAccueil->setStyleSheet(QString::fromUtf8(" color: black; text-align: middle; \n"
"background-color:  rgb(255, 248, 231);\n"
"font: 14pt \"Segoe UI\";\n"
""));
        btnGestion = new QPushButton(sidebar);
        btnGestion->setObjectName("btnGestion");
        btnGestion->setGeometry(QRect(30, 370, 180, 40));
        btnGestion->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 248, 231);\n"
" color: black; text-align: middle; \n"
"font: 11pt \"Segoe UI\";"));
        btnStats = new QPushButton(sidebar);
        btnStats->setObjectName("btnStats");
        btnStats->setGeometry(QRect(30, 430, 180, 40));
        btnStats->setStyleSheet(QString::fromUtf8(" color: black; text-align: middle; \n"
"background-color: rgb(255, 248, 231);\n"
"font: 13pt \"Segoe UI\";"));
        btnLogout = new QPushButton(sidebar);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setGeometry(QRect(20, 820, 180, 40));
        btnLogout->setStyleSheet(QString::fromUtf8(" color: black; text-align: middle; \n"
"background-color: rgb(255, 248, 231);\n"
"font: 12pt \"Segoe UI\";  \n"
"border-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        label_7 = new QLabel(sidebar);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 50, 161, 141));
        label_7->setPixmap(QPixmap(QString::fromUtf8("../../AppData/Local/Packages/5319275A.WhatsAppDesktop_cv1g1gvanyjgm/TempState/814A9C18F5ABFF398787C9CFCBF3D80C/WhatsApp Image 2025-09-18 \303\240 22.16.26_547ae55f.jpg")));
        label_7->setScaledContents(true);
        topbar = new QFrame(centralwidget);
        topbar->setObjectName("topbar");
        topbar->setGeometry(QRect(240, 0, 1331, 911));
        topbar->setStyleSheet(QString::fromUtf8("background-color: rgb(216, 195, 165);"));
        searchMember = new QLineEdit(topbar);
        searchMember->setObjectName("searchMember");
        searchMember->setGeometry(QRect(30, 20, 501, 31));
        searchMember->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 248, 231); color: black; border-radius: 8px; padding-left: 30px;"));
        comboSort = new QComboBox(topbar);
        comboSort->addItem(QString());
        comboSort->addItem(QString());
        comboSort->setObjectName("comboSort");
        comboSort->setGeometry(QRect(660, 30, 121, 31));
        comboSort->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 248, 231); color: black; border-radius: 8px;"));
        btnExportPDF = new QPushButton(topbar);
        btnExportPDF->setObjectName("btnExportPDF");
        btnExportPDF->setGeometry(QRect(840, 20, 141, 30));
        btnExportPDF->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 248, 231); color: black; border-radius: 8px;"));
        mainContent = new QFrame(topbar);
        mainContent->setObjectName("mainContent");
        mainContent->setGeometry(QRect(10, 80, 1291, 801));
        mainContent->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 248, 231);"));
        deleteIDEdit = new QLineEdit(mainContent);
        deleteIDEdit->setObjectName("deleteIDEdit");
        deleteIDEdit->setGeometry(QRect(680, 460, 200, 40));
        deleteIDEdit->setMinimumSize(QSize(200, 40));
        deleteIDEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 218, 200);\n"
"font: 300 9pt \"Segoe UI\";\n"
"color: white;  font-size: 16px; font-weight: bold; color: white;  font-size: 16px;\n"
"\n"
""));
        tableWidget = new QTableWidget(mainContent);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        __qtablewidgetitem->setBackground(QColor(149, 109, 101));
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        __qtablewidgetitem1->setBackground(QColor(149, 109, 101));
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        __qtablewidgetitem2->setBackground(QColor(149, 109, 101));
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        __qtablewidgetitem3->setBackground(QColor(149, 109, 101));
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        __qtablewidgetitem4->setBackground(QColor(149, 109, 101));
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        __qtablewidgetitem5->setBackground(QColor(149, 109, 101));
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font1);
        __qtablewidgetitem6->setBackground(QColor(149, 109, 101));
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font1);
        __qtablewidgetitem7->setBackground(QColor(149, 109, 101));
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font1);
        __qtablewidgetitem8->setBackground(QColor(149, 109, 101));
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font1);
        __qtablewidgetitem9->setBackground(QColor(149, 109, 101));
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font1);
        __qtablewidgetitem10->setBackground(QColor(149, 109, 101));
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font);
        __qtablewidgetitem11->setBackground(QColor(149, 109, 101));
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font);
        __qtablewidgetitem12->setBackground(QColor(149, 109, 101));
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem12);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font);
        __qtablewidgetitem13->setBackground(QColor(149, 109, 101));
        __qtablewidgetitem13->setForeground(brush);
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem13);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font);
        __qtablewidgetitem14->setBackground(QColor(149, 109, 101));
        __qtablewidgetitem14->setForeground(brush1);
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem14);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(390, 50, 841, 381));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 218, 200);\n"
""));
        addMemberBox = new QGroupBox(mainContent);
        addMemberBox->setObjectName("addMemberBox");
        addMemberBox->setGeometry(QRect(10, 50, 351, 711));
        addMemberBox->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 218, 200);"));
        editID = new QLineEdit(addMemberBox);
        editID->setObjectName("editID");
        editID->setGeometry(QRect(90, 60, 201, 51));
        editID->setStyleSheet(QString::fromUtf8("background: #cb958a; color: white; border-radius: 8px;"));
        editLastName = new QLineEdit(addMemberBox);
        editLastName->setObjectName("editLastName");
        editLastName->setGeometry(QRect(90, 160, 201, 51));
        editLastName->setStyleSheet(QString::fromUtf8("background: #cb958a; color: white; border-radius: 8px;\n"
"font: 300 9pt \"Segoe UI\";"));
        editFirstName = new QLineEdit(addMemberBox);
        editFirstName->setObjectName("editFirstName");
        editFirstName->setGeometry(QRect(90, 270, 201, 51));
        editFirstName->setStyleSheet(QString::fromUtf8("background: #cb958a; color: white; border-radius: 8px;font: 300 9pt \"Segoe UI\";"));
        editContact = new QLineEdit(addMemberBox);
        editContact->setObjectName("editContact");
        editContact->setGeometry(QRect(90, 470, 201, 51));
        editContact->setStyleSheet(QString::fromUtf8("background: #cb958a; color: white; border-radius: 8px;\n"
"font: 350  9pt \"Segoe UI\";"));
        comboType = new QComboBox(addMemberBox);
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->setObjectName("comboType");
        comboType->setGeometry(QRect(90, 560, 201, 51));
        comboType->setStyleSheet(QString::fromUtf8("background: #cb958a; color: white; border-radius: 8px;"));
        dateEdit = new QDateEdit(addMemberBox);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(90, 360, 201, 51));
        dateEdit->setStyleSheet(QString::fromUtf8(" color: white; border-radius: 8px;\n"
"background-color: rgb(203, 149, 138);"));
        btnAnnuler = new QPushButton(addMemberBox);
        btnAnnuler->setObjectName("btnAnnuler");
        btnAnnuler->setGeometry(QRect(190, 640, 141, 51));
        btnAnnuler->setStyleSheet(QString::fromUtf8("background: #956d65; color: white; border-radius: 8px;"));
        btnValider = new QPushButton(addMemberBox);
        btnValider->setObjectName("btnValider");
        btnValider->setGeometry(QRect(30, 640, 131, 51));
        btnValider->setStyleSheet(QString::fromUtf8("; color: white; border-radius: 8px;\n"
"background-color: rgb(149, 10, 12);"));
        label = new QLabel(addMemberBox);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 30, 63, 20));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 900 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"color: rgb(0, 0, 0);"));
        label_2 = new QLabel(addMemberBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 120, 63, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 900 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"color: rgb(0, 0, 0);"));
        label_3 = new QLabel(addMemberBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 230, 91, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 900 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"color: rgb(0, 0, 0);"));
        label_4 = new QLabel(addMemberBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(150, 320, 131, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 14pt \"Segoe UI\";\n"
"font: 900 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"color: rgb(0, 0, 0);"));
        label_5 = new QLabel(addMemberBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(160, 420, 81, 41));
        label_5->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Segoe UI\";\n"
"font: 900 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"color: rgb(0, 0, 0);"));
        label_6 = new QLabel(addMemberBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(150, 520, 101, 31));
        label_6->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe UI\";\n"
"font: 900 9pt \"Segoe UI\";\n"
"text-decoration: underline;\n"
"color: rgb(0, 0, 0);"));
        editID_2 = new QLineEdit(mainContent);
        editID_2->setObjectName("editID_2");
        editID_2->setGeometry(QRect(0, 20, 201, 51));
        editID_2->setStyleSheet(QString::fromUtf8("background: #956d65; color: black; border-radius: 16px;\n"
"font: 14pt \"Segoe UI\";   text-align: middle;"));
        btnDeleteID_3 = new QPushButton(mainContent);
        btnDeleteID_3->setObjectName("btnDeleteID_3");
        btnDeleteID_3->setGeometry(QRect(900, 460, 161, 41));
        btnDeleteID_3->setMinimumSize(QSize(150, 40));
        btnDeleteID_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(216, 195, 165); color: #232e7a; border-radius: 8px; font-size: 16px; font-weight: bold;"));
        btnDeleteID_2 = new QPushButton(mainContent);
        btnDeleteID_2->setObjectName("btnDeleteID_2");
        btnDeleteID_2->setGeometry(QRect(1080, 460, 161, 41));
        btnDeleteID_2->setMinimumSize(QSize(150, 40));
        btnDeleteID_2->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(216, 195, 165); color: #232e7a; border-radius: 8px; font-size: 16px; font-weight: bold;"));
        label_9 = new QLabel(mainContent);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(380, 509, 881, 271));
        label_9->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/statistique.jpg")));
        label_9->setScaledContents(true);
        label_8 = new QLabel(topbar);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(590, 30, 63, 20));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        membermainwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(membermainwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 25));
        membermainwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(membermainwindow);
        statusbar->setObjectName("statusbar");
        membermainwindow->setStatusBar(statusbar);

        retranslateUi(membermainwindow);

        QMetaObject::connectSlotsByName(membermainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *membermainwindow)
    {
        membermainwindow->setWindowTitle(QCoreApplication::translate("membermainwindow", "membermainwindow", nullptr));
        btnAccueil->setText(QCoreApplication::translate("membermainwindow", "Home", nullptr));
        btnGestion->setText(QCoreApplication::translate("membermainwindow", "Member management", nullptr));
        btnStats->setText(QCoreApplication::translate("membermainwindow", "Statistics", nullptr));
        btnLogout->setText(QCoreApplication::translate("membermainwindow", "Log out", nullptr));
        label_7->setText(QString());
        searchMember->setText(QCoreApplication::translate("membermainwindow", "Search for member:", nullptr));
        searchMember->setPlaceholderText(QCoreApplication::translate("membermainwindow", "Rechercher un membre :", nullptr));
        comboSort->setItemText(0, QCoreApplication::translate("membermainwindow", "Name", nullptr));
        comboSort->setItemText(1, QCoreApplication::translate("membermainwindow", "ID", nullptr));

        btnExportPDF->setText(QCoreApplication::translate("membermainwindow", "Export PDF", nullptr));
        deleteIDEdit->setText(QCoreApplication::translate("membermainwindow", "id:", nullptr));
        deleteIDEdit->setPlaceholderText(QCoreApplication::translate("membermainwindow", "Identifiant", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("membermainwindow", "id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("membermainwindow", "name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("membermainwindow", "surname", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("membermainwindow", "date of birth", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("membermainwindow", "contact", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("membermainwindow", "subscription", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("membermainwindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("membermainwindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("membermainwindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("membermainwindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("membermainwindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("membermainwindow", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("membermainwindow", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("membermainwindow", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("membermainwindow", "9", nullptr));
        addMemberBox->setTitle(QString());
        editID->setPlaceholderText(QCoreApplication::translate("membermainwindow", "ID", nullptr));
        editLastName->setText(QCoreApplication::translate("membermainwindow", "Name", nullptr));
        editLastName->setPlaceholderText(QCoreApplication::translate("membermainwindow", "Nom", nullptr));
        editFirstName->setText(QCoreApplication::translate("membermainwindow", "First name", nullptr));
        editFirstName->setPlaceholderText(QCoreApplication::translate("membermainwindow", "Pr\303\251nom", nullptr));
        editContact->setText(QCoreApplication::translate("membermainwindow", "contact", nullptr));
        editContact->setPlaceholderText(QCoreApplication::translate("membermainwindow", "Contact parent", nullptr));
        comboType->setItemText(0, QCoreApplication::translate("membermainwindow", "Mensuel", nullptr));
        comboType->setItemText(1, QCoreApplication::translate("membermainwindow", "Annuel", nullptr));
        comboType->setItemText(2, QCoreApplication::translate("membermainwindow", "Trimestriel", nullptr));

        btnAnnuler->setText(QCoreApplication::translate("membermainwindow", "Cancel", nullptr));
        btnValider->setText(QCoreApplication::translate("membermainwindow", "Validate", nullptr));
        label->setText(QCoreApplication::translate("membermainwindow", "id", nullptr));
        label_2->setText(QCoreApplication::translate("membermainwindow", "name", nullptr));
        label_3->setText(QCoreApplication::translate("membermainwindow", "First name", nullptr));
        label_4->setText(QCoreApplication::translate("membermainwindow", "date of birth", nullptr));
        label_5->setText(QCoreApplication::translate("membermainwindow", "contact", nullptr));
        label_6->setText(QCoreApplication::translate("membermainwindow", "subsciption", nullptr));
        editID_2->setText(QCoreApplication::translate("membermainwindow", "    ADD MEMBER", nullptr));
        editID_2->setPlaceholderText(QCoreApplication::translate("membermainwindow", "ID", nullptr));
        btnDeleteID_3->setText(QCoreApplication::translate("membermainwindow", "Delete", nullptr));
        btnDeleteID_2->setText(QCoreApplication::translate("membermainwindow", "Modify", nullptr));
        label_9->setText(QString());
        label_8->setText(QCoreApplication::translate("membermainwindow", "Sort by:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class membermainwindow: public Ui_membermainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBERMAINWINDOW_H
