/********************************************************************************
** Form generated from reading UI file 'membersmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBERSMAINWINDOW_H
#define UI_MEMBERSMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_membersMainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QFrame *sidebar;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLineEdit *lineEdit_search;
    QComboBox *comboBox_sort;
    QComboBox *comboBox_filter;
    QPushButton *pushButton_exportPdf;
    QPushButton *pushButton_exportExcel;
    QTableWidget *tableWidget_members;
    QWidget *tab_3;
    QLabel *label_cin;
    QLineEdit *lineEdit_cin;
    QLabel *label_firstName;
    QLineEdit *lineEdit_firstName;
    QLabel *label_lastName;
    QLineEdit *lineEdit_lastName;
    QLabel *label_age;
    QSpinBox *spinBox_age;
    QLabel *label_email;
    QLineEdit *lineEdit_email;
    QLabel *label_phone;
    QLineEdit *lineEdit_phone;
    QLabel *label_subscription;
    QComboBox *comboBox_subscription;
    QLabel *label_image;
    QLabel *label_age_2;
    QComboBox *comboBox_gender;
    QWidget *widget_image;
    QVBoxLayout *verticalLayout;
    QLabel *label_imagePreview;
    QPushButton *pushButton_upload;
    QWidget *widget_buttons;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_add;
    QPushButton *pushButton_update;
    QWidget *tab_2;
    QLabel *label_2;
    QMenuBar *menubar;
    QMenu *menumember_management;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *membersMainWindow)
    {
        if (membersMainWindow->objectName().isEmpty())
            membersMainWindow->setObjectName("membersMainWindow");
        membersMainWindow->resize(1280, 720);
        centralwidget = new QWidget(membersMainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-1, -1, 1280, 720));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        frame->setMidLineWidth(1);
        sidebar = new QFrame(frame);
        sidebar->setObjectName("sidebar");
        sidebar->setGeometry(QRect(-20, 20, 341, 661));
        sidebar->setAcceptDrops(false);
        sidebar->setStyleSheet(QString::fromUtf8("border-radius: 26px;\n"
"background-color: rgb(22, 166, 179);"));
        sidebar->setFrameShape(QFrame::Shape::StyledPanel);
        sidebar->setFrameShadow(QFrame::Shadow::Raised);
        pushButton = new QPushButton(sidebar);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(60, 220, 211, 51));
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 140, 140);\n"
"color: rgb(0, 0, 0);;border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"	background-color: rgb(177, 206, 194);\n"
"}"));
        pushButton_2 = new QPushButton(sidebar);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(60, 300, 211, 51));
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 140, 140);\n"
"color: rgb(0, 0, 0);;border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"	background-color: rgb(177, 206, 194);\n"
"}"));
        pushButton_3 = new QPushButton(sidebar);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(60, 380, 211, 51));
        pushButton_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 140, 140);\n"
"color: rgb(0, 0, 0);;border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"	background-color: rgb(177, 206, 194);\n"
"}"));
        pushButton_4 = new QPushButton(sidebar);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(60, 460, 211, 51));
        pushButton_4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(17, 140, 140);\n"
"color: rgb(0, 0, 0);;border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"	background-color: rgb(177, 206, 194);\n"
"}"));
        pushButton_5 = new QPushButton(sidebar);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(60, 550, 211, 51));
        pushButton_5->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_5->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QPushButton{\n"
"background-color: rgb(17, 133, 143);\n"
"color: rgb(0, 0, 0);;border-radius: 25px;\n"
"font: 700 11pt \"Segoe UI\";\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"	background-color: rgb(177, 206, 194);\n"
"}"));
        label = new QLabel(sidebar);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 10, 231, 211));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/logo1.png")));
        label->setScaledContents(true);
        tabWidget = new QTabWidget(frame);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(370, 20, 901, 631));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        tabWidget->setFont(font);
        tabWidget->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setIconSize(QSize(20, 20));
        tab = new QWidget();
        tab->setObjectName("tab");
        lineEdit_search = new QLineEdit(tab);
        lineEdit_search->setObjectName("lineEdit_search");
        lineEdit_search->setGeometry(QRect(20, 20, 221, 30));
        lineEdit_search->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #16A6B3;\n"
"    border-radius: 15px;\n"
"    padding: 5px 15px;\n"
"    font-size: 12px;\n"
"}"));
        comboBox_sort = new QComboBox(tab);
        comboBox_sort->addItem(QString());
        comboBox_sort->addItem(QString());
        comboBox_sort->addItem(QString());
        comboBox_sort->setObjectName("comboBox_sort");
        comboBox_sort->setGeometry(QRect(270, 20, 181, 30));
        comboBox_sort->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 2px solid #16A6B3;\n"
"    border-radius: 15px;\n"
"    padding: 5px 15px;\n"
"    font-size: 12px;\n"
"}"));
        comboBox_filter = new QComboBox(tab);
        comboBox_filter->addItem(QString());
        comboBox_filter->addItem(QString());
        comboBox_filter->addItem(QString());
        comboBox_filter->addItem(QString());
        comboBox_filter->setObjectName("comboBox_filter");
        comboBox_filter->setGeometry(QRect(480, 20, 181, 30));
        comboBox_filter->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 2px solid #16A6B3;\n"
"    border-radius: 15px;\n"
"    padding: 5px 15px;\n"
"    font-size: 12px;\n"
"}"));
        pushButton_exportPdf = new QPushButton(tab);
        pushButton_exportPdf->setObjectName("pushButton_exportPdf");
        pushButton_exportPdf->setGeometry(QRect(70, 440, 191, 51));
        pushButton_exportPdf->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
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
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/pdf.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_exportPdf->setIcon(icon);
        pushButton_exportPdf->setIconSize(QSize(22, 22));
        pushButton_exportExcel = new QPushButton(tab);
        pushButton_exportExcel->setObjectName("pushButton_exportExcel");
        pushButton_exportExcel->setGeometry(QRect(340, 440, 191, 51));
        pushButton_exportExcel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_exportExcel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/excel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_exportExcel->setIcon(icon1);
        pushButton_exportExcel->setIconSize(QSize(22, 22));
        tableWidget_members = new QTableWidget(tab);
        if (tableWidget_members->columnCount() < 9)
            tableWidget_members->setColumnCount(9);
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
        tableWidget_members->setObjectName("tableWidget_members");
        tableWidget_members->setGeometry(QRect(10, 70, 871, 331));
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
        tableWidget_members->horizontalHeader()->setVisible(true);
        tableWidget_members->horizontalHeader()->setHighlightSections(true);
        tableWidget_members->verticalHeader()->setVisible(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/list.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tabWidget->addTab(tab, icon2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_cin = new QLabel(tab_3);
        label_cin->setObjectName("label_cin");
        label_cin->setGeometry(QRect(11, 60, 44, 30));
        lineEdit_cin = new QLineEdit(tab_3);
        lineEdit_cin->setObjectName("lineEdit_cin");
        lineEdit_cin->setGeometry(QRect(210, 60, 210, 38));
        label_firstName = new QLabel(tab_3);
        label_firstName->setObjectName("label_firstName");
        label_firstName->setGeometry(QRect(11, 130, 118, 30));
        lineEdit_firstName = new QLineEdit(tab_3);
        lineEdit_firstName->setObjectName("lineEdit_firstName");
        lineEdit_firstName->setGeometry(QRect(210, 130, 210, 38));
        label_lastName = new QLabel(tab_3);
        label_lastName->setObjectName("label_lastName");
        label_lastName->setGeometry(QRect(11, 200, 115, 30));
        lineEdit_lastName = new QLineEdit(tab_3);
        lineEdit_lastName->setObjectName("lineEdit_lastName");
        lineEdit_lastName->setGeometry(QRect(210, 200, 210, 38));
        label_age = new QLabel(tab_3);
        label_age->setObjectName("label_age");
        label_age->setGeometry(QRect(11, 340, 48, 30));
        spinBox_age = new QSpinBox(tab_3);
        spinBox_age->setObjectName("spinBox_age");
        spinBox_age->setGeometry(QRect(210, 340, 70, 39));
        spinBox_age->setMinimum(18);
        spinBox_age->setMaximum(100);
        label_email = new QLabel(tab_3);
        label_email->setObjectName("label_email");
        label_email->setGeometry(QRect(11, 410, 62, 30));
        lineEdit_email = new QLineEdit(tab_3);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(210, 410, 210, 38));
        label_phone = new QLabel(tab_3);
        label_phone->setObjectName("label_phone");
        label_phone->setGeometry(QRect(11, 480, 163, 30));
        lineEdit_phone = new QLineEdit(tab_3);
        lineEdit_phone->setObjectName("lineEdit_phone");
        lineEdit_phone->setGeometry(QRect(210, 480, 210, 38));
        label_subscription = new QLabel(tab_3);
        label_subscription->setObjectName("label_subscription");
        label_subscription->setGeometry(QRect(470, 140, 192, 30));
        comboBox_subscription = new QComboBox(tab_3);
        comboBox_subscription->addItem(QString());
        comboBox_subscription->addItem(QString());
        comboBox_subscription->addItem(QString());
        comboBox_subscription->setObjectName("comboBox_subscription");
        comboBox_subscription->setGeometry(QRect(690, 140, 141, 38));
        label_image = new QLabel(tab_3);
        label_image->setObjectName("label_image");
        label_image->setGeometry(QRect(460, 290, 145, 30));
        label_age_2 = new QLabel(tab_3);
        label_age_2->setObjectName("label_age_2");
        label_age_2->setGeometry(QRect(10, 270, 101, 41));
        comboBox_gender = new QComboBox(tab_3);
        comboBox_gender->addItem(QString());
        comboBox_gender->addItem(QString());
        comboBox_gender->setObjectName("comboBox_gender");
        comboBox_gender->setGeometry(QRect(210, 270, 141, 38));
        widget_image = new QWidget(tab_3);
        widget_image->setObjectName("widget_image");
        widget_image->setGeometry(QRect(650, 250, 164, 155));
        verticalLayout = new QVBoxLayout(widget_image);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_imagePreview = new QLabel(widget_image);
        label_imagePreview->setObjectName("label_imagePreview");
        label_imagePreview->setMinimumSize(QSize(100, 100));
        label_imagePreview->setStyleSheet(QString::fromUtf8("border: 1px solid gray; background-color: white;"));
        label_imagePreview->setFrameShape(QFrame::Shape::Box);
        label_imagePreview->setFrameShadow(QFrame::Shadow::Sunken);
        label_imagePreview->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_imagePreview);

        pushButton_upload = new QPushButton(widget_image);
        pushButton_upload->setObjectName("pushButton_upload");
        pushButton_upload->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_upload->setStyleSheet(QString::fromUtf8("background-color: #16A6B3; color: white; padding: 8px; border-radius: 5px;"));

        verticalLayout->addWidget(pushButton_upload);

        widget_buttons = new QWidget(tab_3);
        widget_buttons->setObjectName("widget_buttons");
        widget_buttons->setGeometry(QRect(490, 460, 353, 52));
        horizontalLayout = new QHBoxLayout(widget_buttons);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_add = new QPushButton(widget_buttons);
        pushButton_add->setObjectName("pushButton_add");
        pushButton_add->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_add->setStyleSheet(QString::fromUtf8("background-color: #118C8C; color: white; padding: 10px; border-radius: 8px; font-weight: bold;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/addd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_add->setIcon(icon3);

        horizontalLayout->addWidget(pushButton_add);

        pushButton_update = new QPushButton(widget_buttons);
        pushButton_update->setObjectName("pushButton_update");
        pushButton_update->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_update->setStyleSheet(QString::fromUtf8("background-color: #16A6B3; color: white; padding: 10px; border-radius: 8px; font-weight: bold;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_update->setIcon(icon4);

        horizontalLayout->addWidget(pushButton_update);

        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tabWidget->addTab(tab_3, icon5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_2 = new QLabel(tab_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, -1, 851, 621));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/statistique.png")));
        label_2->setScaledContents(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/statis.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tabWidget->addTab(tab_2, icon6, QString());
        membersMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(membersMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 26));
        menumember_management = new QMenu(menubar);
        menumember_management->setObjectName("menumember_management");
        membersMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(membersMainWindow);
        statusbar->setObjectName("statusbar");
        membersMainWindow->setStatusBar(statusbar);

        menubar->addAction(menumember_management->menuAction());

        retranslateUi(membersMainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(membersMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *membersMainWindow)
    {
        membersMainWindow->setWindowTitle(QCoreApplication::translate("membersMainWindow", "Gestion des Membres", nullptr));
        pushButton->setText(QCoreApplication::translate("membersMainWindow", "Members", nullptr));
        pushButton_2->setText(QCoreApplication::translate("membersMainWindow", "Employee", nullptr));
        pushButton_3->setText(QCoreApplication::translate("membersMainWindow", "Equipement", nullptr));
        pushButton_4->setText(QCoreApplication::translate("membersMainWindow", "Activities", nullptr));
        pushButton_5->setText(QCoreApplication::translate("membersMainWindow", "Log out", nullptr));
        label->setText(QString());
        lineEdit_search->setPlaceholderText(QCoreApplication::translate("membersMainWindow", "Search members...", nullptr));
        comboBox_sort->setItemText(0, QCoreApplication::translate("membersMainWindow", "Sort by CIN", nullptr));
        comboBox_sort->setItemText(1, QCoreApplication::translate("membersMainWindow", "Sort by Age", nullptr));
        comboBox_sort->setItemText(2, QCoreApplication::translate("membersMainWindow", "Sort by Name", nullptr));

        comboBox_filter->setItemText(0, QCoreApplication::translate("membersMainWindow", "All Members", nullptr));
        comboBox_filter->setItemText(1, QCoreApplication::translate("membersMainWindow", "Mensuel", nullptr));
        comboBox_filter->setItemText(2, QCoreApplication::translate("membersMainWindow", "Trimestriel", nullptr));
        comboBox_filter->setItemText(3, QCoreApplication::translate("membersMainWindow", "Annuel", nullptr));

        pushButton_exportPdf->setText(QCoreApplication::translate("membersMainWindow", "Export PDF", nullptr));
        pushButton_exportExcel->setText(QCoreApplication::translate("membersMainWindow", "Export Excel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_members->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("membersMainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_members->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("membersMainWindow", "First Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_members->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("membersMainWindow", "Last Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_members->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("membersMainWindow", "Age", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_members->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("membersMainWindow", "Gender", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_members->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("membersMainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_members->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("membersMainWindow", "Phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_members->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("membersMainWindow", "Subscription", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_members->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("membersMainWindow", "Actions", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("membersMainWindow", "List of Members", nullptr));
        label_cin->setText(QCoreApplication::translate("membersMainWindow", "CIN:", nullptr));
        label_firstName->setText(QCoreApplication::translate("membersMainWindow", "First Name:", nullptr));
        label_lastName->setText(QCoreApplication::translate("membersMainWindow", "Last Name:", nullptr));
        label_age->setText(QCoreApplication::translate("membersMainWindow", "Age:", nullptr));
        label_email->setText(QCoreApplication::translate("membersMainWindow", "Email:", nullptr));
        label_phone->setText(QCoreApplication::translate("membersMainWindow", "Phone Number:", nullptr));
        label_subscription->setText(QCoreApplication::translate("membersMainWindow", "Subscription Type:", nullptr));
        comboBox_subscription->setItemText(0, QCoreApplication::translate("membersMainWindow", "Annuel", nullptr));
        comboBox_subscription->setItemText(1, QCoreApplication::translate("membersMainWindow", "Trimestriel", nullptr));
        comboBox_subscription->setItemText(2, QCoreApplication::translate("membersMainWindow", "Mensuel", nullptr));

        label_image->setText(QCoreApplication::translate("membersMainWindow", "Profile Image:", nullptr));
        label_age_2->setText(QCoreApplication::translate("membersMainWindow", "Gender:", nullptr));
        comboBox_gender->setItemText(0, QCoreApplication::translate("membersMainWindow", "Male", nullptr));
        comboBox_gender->setItemText(1, QCoreApplication::translate("membersMainWindow", "Female", nullptr));

        label_imagePreview->setText(QCoreApplication::translate("membersMainWindow", "No Image", nullptr));
        pushButton_upload->setText(QCoreApplication::translate("membersMainWindow", "Upload Image", nullptr));
        pushButton_add->setText(QCoreApplication::translate("membersMainWindow", "Add Member", nullptr));
        pushButton_update->setText(QCoreApplication::translate("membersMainWindow", "Confirm Update", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("membersMainWindow", "Add Members", nullptr));
        label_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("membersMainWindow", "Statistics", nullptr));
        menumember_management->setTitle(QCoreApplication::translate("membersMainWindow", "member_management", nullptr));
    } // retranslateUi

};

namespace Ui {
    class membersMainWindow: public Ui_membersMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBERSMAINWINDOW_H
