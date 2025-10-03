/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *sidebar;
    QLabel *label_logo;
    QPushButton *pushButton_members;
    QPushButton *pushButton_employee;
    QPushButton *pushButton_equipement;
    QPushButton *pushButton_activities;
    QPushButton *pushButton_logout;
    QTabWidget *tabWidget;
    QWidget *tab_list;
    QLineEdit *lineEdit_search;
    QComboBox *comboBox_sort;
    QTableWidget *tableWidget_members;
    QPushButton *pushButton_exportPdf;
    QPushButton *pushButton_Modify;
    QWidget *tab_add;
    QLabel *label_cin;
    QLineEdit *lineEdit_cin;
    QLabel *label_firstName;
    QLineEdit *lineEdit_firstName;
    QLabel *label_lastName;
    QSpinBox *spinBox_age;
    QLabel *label_email;
    QLineEdit *lineEdit_email;
    QLabel *label_phone;
    QLineEdit *lineEdit_phone;
    QPushButton *pushButton_add;
    QPushButton *pushButton_update;
    QCheckBox *checkBox;
    QPushButton *pushButton_calendar;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_time;
    QWidget *tab_stats;
    QLabel *label_stats;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #f5f5f5;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sidebar = new QFrame(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setGeometry(QRect(0, 0, 300, 720));
        sidebar->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"     stop:0 #ffffff, stop:1 #118C8C);\n"
"     border-radius: 0px;"));
        sidebar->setFrameShape(QFrame::Shape::StyledPanel);
        sidebar->setFrameShadow(QFrame::Shadow::Raised);
        label_logo = new QLabel(sidebar);
        label_logo->setObjectName("label_logo");
        label_logo->setGeometry(QRect(75, 20, 200, 150));
        label_logo->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        label_logo->setScaledContents(true);
        pushButton_members = new QPushButton(sidebar);
        pushButton_members->setObjectName("pushButton_members");
        pushButton_members->setGeometry(QRect(50, 200, 200, 50));
        pushButton_members->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 140, 140);\n"
"color: white;\n"
"border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:hover{\n"
"background-color: rgb(177, 206, 194);\n"
"}"));
        pushButton_employee = new QPushButton(sidebar);
        pushButton_employee->setObjectName("pushButton_employee");
        pushButton_employee->setGeometry(QRect(50, 270, 200, 50));
        pushButton_employee->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 140, 140);\n"
"color: white;\n"
"border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:hover{\n"
"background-color: rgb(177, 206, 194);\n"
"}"));
        pushButton_equipement = new QPushButton(sidebar);
        pushButton_equipement->setObjectName("pushButton_equipement");
        pushButton_equipement->setGeometry(QRect(50, 340, 200, 50));
        pushButton_equipement->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 140, 140);\n"
"color: white;\n"
"border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:hover{\n"
"background-color: rgb(177, 206, 194);\n"
"}"));
        pushButton_activities = new QPushButton(sidebar);
        pushButton_activities->setObjectName("pushButton_activities");
        pushButton_activities->setGeometry(QRect(50, 410, 200, 50));
        pushButton_activities->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 140, 140);\n"
"color: white;\n"
"border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:hover{\n"
"background-color: rgb(177, 206, 194);\n"
"}"));
        pushButton_logout = new QPushButton(sidebar);
        pushButton_logout->setObjectName("pushButton_logout");
        pushButton_logout->setGeometry(QRect(50, 550, 200, 50));
        pushButton_logout->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 133, 143);\n"
"color: white;\n"
"border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:hover{\n"
"background-color: rgb(177, 206, 194);\n"
"}"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(310, 10, 960, 700));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
"    border: 3px solid #16A6B3;\n"
"    border-radius: 15px;\n"
"    background-color: #FFFFFF;\n"
"    margin-top: 10px;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    alignment: center;\n"
"    left: 20px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #E8F4F8;\n"
"    border: 2px solid #16A6B3;\n"
"    border-bottom: 2px solid #16A6B3;\n"
"    border-top-left-radius: 12px;\n"
"    border-top-right-radius: 12px;\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"    width: 180px;\n"
"    padding: 12px 20px;\n"
"    margin-right: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 12px;\n"
"    color: #16A6B3;\n"
"    height: 45px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #16A6B3;\n"
"    color: white;\n"
"    border-color: #118C8C;\n"
"    border-bottom: 2px solid #16A6B3;\n"
"}\n"
"\n"
"QTabBar::tab:hover:!selected {\n"
"    background-color: #B1CEC2;\n"
"    color: #333333;\n"
"    border-color: #11"
                        "8C8C;\n"
"}\n"
"\n"
"QTabBar::tab:pressed {\n"
"    background-color: #0D6E6E;\n"
"    color: white;\n"
"}"));
        tab_list = new QWidget();
        tab_list->setObjectName("tab_list");
        lineEdit_search = new QLineEdit(tab_list);
        lineEdit_search->setObjectName("lineEdit_search");
        lineEdit_search->setGeometry(QRect(40, 20, 231, 30));
        lineEdit_search->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #16A6B3;\n"
"    border-radius: 15px;\n"
"    padding: 5px 15px;\n"
"    font-size: 12px;\n"
"}"));
        comboBox_sort = new QComboBox(tab_list);
        comboBox_sort->addItem(QString());
        comboBox_sort->addItem(QString());
        comboBox_sort->addItem(QString());
        comboBox_sort->setObjectName("comboBox_sort");
        comboBox_sort->setGeometry(QRect(310, 20, 171, 30));
        comboBox_sort->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 2px solid #16A6B3;\n"
"    border-radius: 15px;\n"
"    padding: 5px 15px;\n"
"    font-size: 12px;\n"
"}"));
        tableWidget_members = new QTableWidget(tab_list);
        if (tableWidget_members->columnCount() < 10)
            tableWidget_members->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_members->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tableWidget_members->setObjectName("tableWidget_members");
        tableWidget_members->setGeometry(QRect(20, 70, 781, 400));
        tableWidget_members->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    border: 2px solid #16A6B3;\n"
"    border-radius: 10px;\n"
"    gridline-color: #E0E0E0;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #E0E0E0;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #B1CEC2;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #16A6B3;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));
        tableWidget_members->setColumnCount(10);
        tableWidget_members->horizontalHeader()->setVisible(true);
        tableWidget_members->verticalHeader()->setVisible(false);
        pushButton_exportPdf = new QPushButton(tab_list);
        pushButton_exportPdf->setObjectName("pushButton_exportPdf");
        pushButton_exportPdf->setGeometry(QRect(200, 500, 191, 51));
        pushButton_exportPdf->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #118C8C;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0D6E6E;\n"
"}"));
        pushButton_Modify = new QPushButton(tab_list);
        pushButton_Modify->setObjectName("pushButton_Modify");
        pushButton_Modify->setGeometry(QRect(450, 500, 191, 51));
        pushButton_Modify->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #16A6B3;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #118C8C;\n"
"}"));
        tabWidget->addTab(tab_list, QString());
        tab_add = new QWidget();
        tab_add->setObjectName("tab_add");
        label_cin = new QLabel(tab_add);
        label_cin->setObjectName("label_cin");
        label_cin->setGeometry(QRect(50, 50, 44, 30));
        label_cin->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";"));
        lineEdit_cin = new QLineEdit(tab_add);
        lineEdit_cin->setObjectName("lineEdit_cin");
        lineEdit_cin->setGeometry(QRect(200, 50, 210, 38));
        lineEdit_cin->setStyleSheet(QString::fromUtf8("border: 2px solid #16A6B3; border-radius: 8px; padding: 5px;"));
        label_firstName = new QLabel(tab_add);
        label_firstName->setObjectName("label_firstName");
        label_firstName->setGeometry(QRect(50, 100, 118, 30));
        label_firstName->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";"));
        lineEdit_firstName = new QLineEdit(tab_add);
        lineEdit_firstName->setObjectName("lineEdit_firstName");
        lineEdit_firstName->setGeometry(QRect(200, 100, 210, 38));
        lineEdit_firstName->setStyleSheet(QString::fromUtf8("border: 2px solid #16A6B3; border-radius: 8px; padding: 5px;"));
        label_lastName = new QLabel(tab_add);
        label_lastName->setObjectName("label_lastName");
        label_lastName->setGeometry(QRect(50, 150, 115, 30));
        label_lastName->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";"));
        spinBox_age = new QSpinBox(tab_add);
        spinBox_age->setObjectName("spinBox_age");
        spinBox_age->setGeometry(QRect(200, 150, 70, 39));
        spinBox_age->setStyleSheet(QString::fromUtf8("border: 2px solid #16A6B3; border-radius: 8px; padding: 5px;"));
        spinBox_age->setMinimum(18);
        spinBox_age->setMaximum(100);
        label_email = new QLabel(tab_add);
        label_email->setObjectName("label_email");
        label_email->setGeometry(QRect(50, 220, 62, 30));
        label_email->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";"));
        lineEdit_email = new QLineEdit(tab_add);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(160, 220, 171, 31));
        lineEdit_email->setStyleSheet(QString::fromUtf8("border: 2px solid #16A6B3; border-radius: 8px; padding: 5px;"));
        label_phone = new QLabel(tab_add);
        label_phone->setObjectName("label_phone");
        label_phone->setGeometry(QRect(50, 320, 163, 30));
        label_phone->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";"));
        lineEdit_phone = new QLineEdit(tab_add);
        lineEdit_phone->setObjectName("lineEdit_phone");
        lineEdit_phone->setGeometry(QRect(190, 310, 210, 38));
        lineEdit_phone->setStyleSheet(QString::fromUtf8("border: 2px solid #16A6B3; border-radius: 8px; padding: 5px;"));
        pushButton_add = new QPushButton(tab_add);
        pushButton_add->setObjectName("pushButton_add");
        pushButton_add->setGeometry(QRect(150, 480, 191, 51));
        pushButton_add->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #118C8C;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    font-weight: bold;\n"
"    padding: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0D6E6E;\n"
"}"));
        pushButton_update = new QPushButton(tab_add);
        pushButton_update->setObjectName("pushButton_update");
        pushButton_update->setGeometry(QRect(350, 480, 191, 51));
        pushButton_update->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #16A6B3;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    font-weight: bold;\n"
"    padding: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #118C8C;\n"
"}"));
        checkBox = new QCheckBox(tab_add);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(140, 280, 231, 18));
        pushButton_calendar = new QPushButton(tab_add);
        pushButton_calendar->setObjectName("pushButton_calendar");
        pushButton_calendar->setGeometry(QRect(60, 220, 62, 31));
        pushButton_calendar->setStyleSheet(QString::fromUtf8("border: 2px solid #16A6B3; border-radius: 8px; padding: 5px;"));
        label_2 = new QLabel(tab_add);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 390, 91, 16));
        lineEdit = new QLineEdit(tab_add);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(190, 370, 211, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("border: 2px solid #16A6B3; border-radius: 8px; padding: 5px;"));
        pushButton_time = new QPushButton(tab_add);
        pushButton_time->setObjectName("pushButton_time");
        pushButton_time->setGeometry(QRect(370, 220, 81, 31));
        pushButton_time->setStyleSheet(QString::fromUtf8("border: 2px solid #16A6B3; border-radius: 8px; padding: 5px;"));
        tabWidget->addTab(tab_add, QString());
        tab_stats = new QWidget();
        tab_stats->setObjectName("tab_stats");
        label_stats = new QLabel(tab_stats);
        label_stats->setObjectName("label_stats");
        label_stats->setGeometry(QRect(50, 50, 300, 30));
        tabWidget->addTab(tab_stats, QString());
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Membres", nullptr));
        label_logo->setText(QString());
        pushButton_members->setText(QCoreApplication::translate("MainWindow", "Members", nullptr));
        pushButton_employee->setText(QCoreApplication::translate("MainWindow", "Employee", nullptr));
        pushButton_equipement->setText(QCoreApplication::translate("MainWindow", "Equipement", nullptr));
        pushButton_activities->setText(QCoreApplication::translate("MainWindow", "Activities", nullptr));
        pushButton_logout->setText(QCoreApplication::translate("MainWindow", "Log out", nullptr));
        lineEdit_search->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search for an Activity ...", nullptr));
        comboBox_sort->setItemText(0, QCoreApplication::translate("MainWindow", "Sort by CIN", nullptr));
        comboBox_sort->setItemText(1, QCoreApplication::translate("MainWindow", "Sort by Age", nullptr));
        comboBox_sort->setItemText(2, QCoreApplication::translate("MainWindow", "Sort by The Name Of The Activity", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget_members->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_members->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "cin", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_members->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", " the activity", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_members->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Age", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_members->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_members->horizontalHeaderItem(6);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "heure", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_members->horizontalHeaderItem(7);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Disponibility ", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_members->horizontalHeaderItem(8);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "price", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_members->horizontalHeaderItem(9);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Lead facilitator :", nullptr));
        pushButton_exportPdf->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
        pushButton_Modify->setText(QCoreApplication::translate("MainWindow", "Modify  ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_list), QCoreApplication::translate("MainWindow", "List of Activities", nullptr));
        label_cin->setText(QCoreApplication::translate("MainWindow", "CIN:", nullptr));
        label_firstName->setText(QCoreApplication::translate("MainWindow", "Name of the activity", nullptr));
        label_lastName->setText(QCoreApplication::translate("MainWindow", "Age ", nullptr));
        label_email->setText(QString());
        label_phone->setText(QCoreApplication::translate("MainWindow", "Price :", nullptr));
        pushButton_add->setText(QCoreApplication::translate("MainWindow", "Add Activity", nullptr));
        pushButton_update->setText(QCoreApplication::translate("MainWindow", "Confirm Update", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Check Disponibility", nullptr));
        pushButton_calendar->setText(QCoreApplication::translate("MainWindow", "Date \360\237\223\205", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Lead facilitator :", nullptr));
        pushButton_time->setText(QCoreApplication::translate("MainWindow", "\360\237\225\222 Heure :  ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_add), QCoreApplication::translate("MainWindow", "Add Activity", nullptr));
        label_stats->setText(QCoreApplication::translate("MainWindow", "Statistics will be displayed here", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_stats), QCoreApplication::translate("MainWindow", "Statistics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
