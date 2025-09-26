/********************************************************************************
** Form generated from reading UI file 'adminmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINMAINWINDOW_H
#define UI_ADMINMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adminmainwindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
    QFrame *sidebar;
    QVBoxLayout *sidebarLayout;
    QLabel *adminLogoLabel;
    QPushButton *btnAccueil;
    QPushButton *btnGestionPersonnel;
    QPushButton *btnDeconnecter;
    QFrame *mainContent;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topBarLayout;
    QLineEdit *searchMember;
    QComboBox *sortCombo;
    QPushButton *adminBtnShowStats;
    QStackedWidget *stackedWidgetMainContentView;
    QWidget *mainPanel;
    QFrame *frame_2;
    QGroupBox *employeeListBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *employeeListLabel;
    QTableWidget *adminEmployeeTable;
    QFrame *frame_3;
    QGridLayout *gridLayout;
    QPushButton *adminBtnEditEmployee;
    QPushButton *adminBtnAddEmployee;
    QPushButton *adminBtnDeleteEmployee;
    QStackedWidget *stackedWidgetEditAndAdd;
    QWidget *addEmployeePage;
    QFormLayout *formLayout;
    QGroupBox *addEmployeeBox;
    QFormLayout *adminAddEmployeeForm;
    QLabel *labelID;
    QLineEdit *adminEditEmployeeID;
    QLabel *labelNom;
    QLineEdit *adminEditEmployeeName;
    QLabel *labelAge;
    QLineEdit *adminEditEmployeeAge;
    QLabel *labelContactParent;
    QLineEdit *adminEditEmployeeContact;
    QLabel *adminLabelEmployeePosition;
    QLineEdit *adminEditEmployeePosition;
    QLabel *adminLabelEmployeePhone;
    QLineEdit *adminEditEmployeePhone;
    QPushButton *adminBtnCancel;
    QPushButton *adminBtnConfirm;
    QWidget *editEmplyerPage;
    QFormLayout *formLayout_2;
    QGroupBox *addEmployeeBox_2;
    QFormLayout *adminAddEmployeeForm_2;
    QLabel *labelID_3;
    QLineEdit *adminEditEmployeeID_2;
    QLabel *labelNom_2;
    QLineEdit *adminEditEmployeeName_2;
    QLabel *labelAge_2;
    QLineEdit *adminEditEmployeeAge_2;
    QLabel *labelContactParent_2;
    QLineEdit *adminEditEmployeeContact_2;
    QLabel *adminLabelEmployeePosition_2;
    QLineEdit *adminEditEmployeePosition_2;
    QLabel *adminLabelEmployeePhone_2;
    QLineEdit *adminEditEmployeePhone_2;
    QPushButton *adminBtnCancel_2;
    QPushButton *adminBtnConfirm_4;
    QWidget *stats;
    QFrame *frame_5;
    QGroupBox *employeeListBox_2;
    QVBoxLayout *verticalLayout_4;
    QStackedWidget *stackedWidgetEditAndAdd_2;
    QWidget *addEmployeePage_3;
    QFormLayout *formLayout_5;
    QGroupBox *addEmployeeBox_5;
    QFormLayout *adminAddEmployeeForm_5;
    QWidget *editEmplyerPage_3;
    QFormLayout *formLayout_6;
    QGroupBox *addEmployeeBox_6;
    QFormLayout *adminAddEmployeeForm_6;
    QLabel *labelID_6;
    QLineEdit *adminEditEmployeeID_6;
    QLabel *labelNom_6;
    QLineEdit *adminEditEmployeeName_6;
    QLabel *labelAge_6;
    QLineEdit *adminEditEmployeeAge_6;
    QLabel *labelContactParent_6;
    QLineEdit *adminEditEmployeeContact_6;
    QLabel *adminLabelEmployeePosition_6;
    QLineEdit *adminEditEmployeePosition_6;
    QLabel *adminLabelEmployeePhone_6;
    QLineEdit *adminEditEmployeePhone_6;
    QPushButton *adminBtnCancel_6;
    QPushButton *adminBtnConfirm_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *adminmainwindow)
    {
        if (adminmainwindow->objectName().isEmpty())
            adminmainwindow->setObjectName("adminmainwindow");
        adminmainwindow->resize(1386, 939);
        centralwidget = new QWidget(adminmainwindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        sidebar = new QFrame(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setFrameShape(QFrame::Shape::StyledPanel);
        sidebar->setFrameShadow(QFrame::Shadow::Raised);
        sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setObjectName("sidebarLayout");
        adminLogoLabel = new QLabel(sidebar);
        adminLogoLabel->setObjectName("adminLogoLabel");
        adminLogoLabel->setPixmap(QPixmap(QString::fromUtf8("assests/VibraClubLogo.png")));
        adminLogoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(adminLogoLabel);

        btnAccueil = new QPushButton(sidebar);
        btnAccueil->setObjectName("btnAccueil");

        sidebarLayout->addWidget(btnAccueil);

        btnGestionPersonnel = new QPushButton(sidebar);
        btnGestionPersonnel->setObjectName("btnGestionPersonnel");

        sidebarLayout->addWidget(btnGestionPersonnel);

        btnDeconnecter = new QPushButton(sidebar);
        btnDeconnecter->setObjectName("btnDeconnecter");

        sidebarLayout->addWidget(btnDeconnecter);


        mainLayout->addWidget(sidebar);

        mainContent = new QFrame(centralwidget);
        mainContent->setObjectName("mainContent");
        mainContent->setFrameShape(QFrame::Shape::StyledPanel);
        mainContent->setFrameShadow(QFrame::Shadow::Raised);
        frame = new QFrame(mainContent);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(70, 20, 851, 111));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        topBarLayout = new QHBoxLayout();
        topBarLayout->setObjectName("topBarLayout");
        searchMember = new QLineEdit(frame);
        searchMember->setObjectName("searchMember");

        topBarLayout->addWidget(searchMember);

        sortCombo = new QComboBox(frame);
        sortCombo->setObjectName("sortCombo");

        topBarLayout->addWidget(sortCombo);

        adminBtnShowStats = new QPushButton(frame);
        adminBtnShowStats->setObjectName("adminBtnShowStats");

        topBarLayout->addWidget(adminBtnShowStats);


        verticalLayout->addLayout(topBarLayout);

        stackedWidgetMainContentView = new QStackedWidget(mainContent);
        stackedWidgetMainContentView->setObjectName("stackedWidgetMainContentView");
        stackedWidgetMainContentView->setGeometry(QRect(0, 100, 1061, 591));
        mainPanel = new QWidget();
        mainPanel->setObjectName("mainPanel");
        frame_2 = new QFrame(mainPanel);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(-30, 10, 1031, 571));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #eadbc8;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        employeeListBox = new QGroupBox(frame_2);
        employeeListBox->setObjectName("employeeListBox");
        employeeListBox->setGeometry(QRect(440, 40, 581, 471));
        employeeListBox->setStyleSheet(QString::fromUtf8("background: #946d65; color: white; border-radius: 18px; font-weight: bold; font-size: 16px; padding: 0px;"));
        verticalLayout_2 = new QVBoxLayout(employeeListBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        employeeListLabel = new QLabel(employeeListBox);
        employeeListLabel->setObjectName("employeeListLabel");

        verticalLayout_2->addWidget(employeeListLabel);

        adminEmployeeTable = new QTableWidget(employeeListBox);
        if (adminEmployeeTable->columnCount() < 6)
            adminEmployeeTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        adminEmployeeTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        adminEmployeeTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        adminEmployeeTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        adminEmployeeTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        adminEmployeeTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        adminEmployeeTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (adminEmployeeTable->rowCount() < 5)
            adminEmployeeTable->setRowCount(5);
        adminEmployeeTable->setObjectName("adminEmployeeTable");

        verticalLayout_2->addWidget(adminEmployeeTable);

        frame_3 = new QFrame(employeeListBox);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(0, 70));
        frame_3->setMaximumSize(QSize(16777215, 300));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(frame_3);
        gridLayout->setObjectName("gridLayout");
        adminBtnEditEmployee = new QPushButton(frame_3);
        adminBtnEditEmployee->setObjectName("adminBtnEditEmployee");

        gridLayout->addWidget(adminBtnEditEmployee, 0, 0, 1, 1);

        adminBtnAddEmployee = new QPushButton(frame_3);
        adminBtnAddEmployee->setObjectName("adminBtnAddEmployee");

        gridLayout->addWidget(adminBtnAddEmployee, 0, 1, 1, 1);

        adminBtnDeleteEmployee = new QPushButton(frame_3);
        adminBtnDeleteEmployee->setObjectName("adminBtnDeleteEmployee");

        gridLayout->addWidget(adminBtnDeleteEmployee, 0, 2, 1, 1);


        verticalLayout_2->addWidget(frame_3);

        stackedWidgetEditAndAdd = new QStackedWidget(frame_2);
        stackedWidgetEditAndAdd->setObjectName("stackedWidgetEditAndAdd");
        stackedWidgetEditAndAdd->setGeometry(QRect(0, 10, 438, 537));
        addEmployeePage = new QWidget();
        addEmployeePage->setObjectName("addEmployeePage");
        formLayout = new QFormLayout(addEmployeePage);
        formLayout->setObjectName("formLayout");
        addEmployeeBox = new QGroupBox(addEmployeePage);
        addEmployeeBox->setObjectName("addEmployeeBox");
        adminAddEmployeeForm = new QFormLayout(addEmployeeBox);
        adminAddEmployeeForm->setObjectName("adminAddEmployeeForm");
        labelID = new QLabel(addEmployeeBox);
        labelID->setObjectName("labelID");

        adminAddEmployeeForm->setWidget(0, QFormLayout::LabelRole, labelID);

        adminEditEmployeeID = new QLineEdit(addEmployeeBox);
        adminEditEmployeeID->setObjectName("adminEditEmployeeID");

        adminAddEmployeeForm->setWidget(0, QFormLayout::FieldRole, adminEditEmployeeID);

        labelNom = new QLabel(addEmployeeBox);
        labelNom->setObjectName("labelNom");

        adminAddEmployeeForm->setWidget(1, QFormLayout::LabelRole, labelNom);

        adminEditEmployeeName = new QLineEdit(addEmployeeBox);
        adminEditEmployeeName->setObjectName("adminEditEmployeeName");

        adminAddEmployeeForm->setWidget(1, QFormLayout::FieldRole, adminEditEmployeeName);

        labelAge = new QLabel(addEmployeeBox);
        labelAge->setObjectName("labelAge");

        adminAddEmployeeForm->setWidget(2, QFormLayout::LabelRole, labelAge);

        adminEditEmployeeAge = new QLineEdit(addEmployeeBox);
        adminEditEmployeeAge->setObjectName("adminEditEmployeeAge");

        adminAddEmployeeForm->setWidget(2, QFormLayout::FieldRole, adminEditEmployeeAge);

        labelContactParent = new QLabel(addEmployeeBox);
        labelContactParent->setObjectName("labelContactParent");

        adminAddEmployeeForm->setWidget(3, QFormLayout::LabelRole, labelContactParent);

        adminEditEmployeeContact = new QLineEdit(addEmployeeBox);
        adminEditEmployeeContact->setObjectName("adminEditEmployeeContact");

        adminAddEmployeeForm->setWidget(3, QFormLayout::FieldRole, adminEditEmployeeContact);

        adminLabelEmployeePosition = new QLabel(addEmployeeBox);
        adminLabelEmployeePosition->setObjectName("adminLabelEmployeePosition");

        adminAddEmployeeForm->setWidget(4, QFormLayout::LabelRole, adminLabelEmployeePosition);

        adminEditEmployeePosition = new QLineEdit(addEmployeeBox);
        adminEditEmployeePosition->setObjectName("adminEditEmployeePosition");

        adminAddEmployeeForm->setWidget(4, QFormLayout::FieldRole, adminEditEmployeePosition);

        adminLabelEmployeePhone = new QLabel(addEmployeeBox);
        adminLabelEmployeePhone->setObjectName("adminLabelEmployeePhone");

        adminAddEmployeeForm->setWidget(5, QFormLayout::LabelRole, adminLabelEmployeePhone);

        adminEditEmployeePhone = new QLineEdit(addEmployeeBox);
        adminEditEmployeePhone->setObjectName("adminEditEmployeePhone");

        adminAddEmployeeForm->setWidget(5, QFormLayout::FieldRole, adminEditEmployeePhone);

        adminBtnCancel = new QPushButton(addEmployeeBox);
        adminBtnCancel->setObjectName("adminBtnCancel");
        adminBtnCancel->setCheckable(true);
        adminBtnCancel->setChecked(true);

        adminAddEmployeeForm->setWidget(6, QFormLayout::FieldRole, adminBtnCancel);

        adminBtnConfirm = new QPushButton(addEmployeeBox);
        adminBtnConfirm->setObjectName("adminBtnConfirm");

        adminAddEmployeeForm->setWidget(6, QFormLayout::LabelRole, adminBtnConfirm);


        formLayout->setWidget(0, QFormLayout::LabelRole, addEmployeeBox);

        stackedWidgetEditAndAdd->addWidget(addEmployeePage);
        editEmplyerPage = new QWidget();
        editEmplyerPage->setObjectName("editEmplyerPage");
        formLayout_2 = new QFormLayout(editEmplyerPage);
        formLayout_2->setObjectName("formLayout_2");
        addEmployeeBox_2 = new QGroupBox(editEmplyerPage);
        addEmployeeBox_2->setObjectName("addEmployeeBox_2");
        adminAddEmployeeForm_2 = new QFormLayout(addEmployeeBox_2);
        adminAddEmployeeForm_2->setObjectName("adminAddEmployeeForm_2");
        labelID_3 = new QLabel(addEmployeeBox_2);
        labelID_3->setObjectName("labelID_3");

        adminAddEmployeeForm_2->setWidget(0, QFormLayout::LabelRole, labelID_3);

        adminEditEmployeeID_2 = new QLineEdit(addEmployeeBox_2);
        adminEditEmployeeID_2->setObjectName("adminEditEmployeeID_2");

        adminAddEmployeeForm_2->setWidget(0, QFormLayout::FieldRole, adminEditEmployeeID_2);

        labelNom_2 = new QLabel(addEmployeeBox_2);
        labelNom_2->setObjectName("labelNom_2");

        adminAddEmployeeForm_2->setWidget(1, QFormLayout::LabelRole, labelNom_2);

        adminEditEmployeeName_2 = new QLineEdit(addEmployeeBox_2);
        adminEditEmployeeName_2->setObjectName("adminEditEmployeeName_2");

        adminAddEmployeeForm_2->setWidget(1, QFormLayout::FieldRole, adminEditEmployeeName_2);

        labelAge_2 = new QLabel(addEmployeeBox_2);
        labelAge_2->setObjectName("labelAge_2");

        adminAddEmployeeForm_2->setWidget(2, QFormLayout::LabelRole, labelAge_2);

        adminEditEmployeeAge_2 = new QLineEdit(addEmployeeBox_2);
        adminEditEmployeeAge_2->setObjectName("adminEditEmployeeAge_2");

        adminAddEmployeeForm_2->setWidget(2, QFormLayout::FieldRole, adminEditEmployeeAge_2);

        labelContactParent_2 = new QLabel(addEmployeeBox_2);
        labelContactParent_2->setObjectName("labelContactParent_2");

        adminAddEmployeeForm_2->setWidget(3, QFormLayout::LabelRole, labelContactParent_2);

        adminEditEmployeeContact_2 = new QLineEdit(addEmployeeBox_2);
        adminEditEmployeeContact_2->setObjectName("adminEditEmployeeContact_2");

        adminAddEmployeeForm_2->setWidget(3, QFormLayout::FieldRole, adminEditEmployeeContact_2);

        adminLabelEmployeePosition_2 = new QLabel(addEmployeeBox_2);
        adminLabelEmployeePosition_2->setObjectName("adminLabelEmployeePosition_2");

        adminAddEmployeeForm_2->setWidget(4, QFormLayout::LabelRole, adminLabelEmployeePosition_2);

        adminEditEmployeePosition_2 = new QLineEdit(addEmployeeBox_2);
        adminEditEmployeePosition_2->setObjectName("adminEditEmployeePosition_2");

        adminAddEmployeeForm_2->setWidget(4, QFormLayout::FieldRole, adminEditEmployeePosition_2);

        adminLabelEmployeePhone_2 = new QLabel(addEmployeeBox_2);
        adminLabelEmployeePhone_2->setObjectName("adminLabelEmployeePhone_2");

        adminAddEmployeeForm_2->setWidget(5, QFormLayout::LabelRole, adminLabelEmployeePhone_2);

        adminEditEmployeePhone_2 = new QLineEdit(addEmployeeBox_2);
        adminEditEmployeePhone_2->setObjectName("adminEditEmployeePhone_2");

        adminAddEmployeeForm_2->setWidget(5, QFormLayout::FieldRole, adminEditEmployeePhone_2);

        adminBtnCancel_2 = new QPushButton(addEmployeeBox_2);
        adminBtnCancel_2->setObjectName("adminBtnCancel_2");
        adminBtnCancel_2->setCheckable(true);
        adminBtnCancel_2->setChecked(true);

        adminAddEmployeeForm_2->setWidget(6, QFormLayout::FieldRole, adminBtnCancel_2);

        adminBtnConfirm_4 = new QPushButton(addEmployeeBox_2);
        adminBtnConfirm_4->setObjectName("adminBtnConfirm_4");

        adminAddEmployeeForm_2->setWidget(6, QFormLayout::LabelRole, adminBtnConfirm_4);


        formLayout_2->setWidget(0, QFormLayout::LabelRole, addEmployeeBox_2);

        stackedWidgetEditAndAdd->addWidget(editEmplyerPage);
        stackedWidgetMainContentView->addWidget(mainPanel);
        stats = new QWidget();
        stats->setObjectName("stats");
        frame_5 = new QFrame(stats);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(-20, 0, 1031, 571));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: #eadbc8;"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        employeeListBox_2 = new QGroupBox(frame_5);
        employeeListBox_2->setObjectName("employeeListBox_2");
        employeeListBox_2->setGeometry(QRect(440, 40, 581, 471));
        employeeListBox_2->setStyleSheet(QString::fromUtf8("background: #946d65; color: white; border-radius: 18px; font-weight: bold; font-size: 16px; padding: 0px;"));
        verticalLayout_4 = new QVBoxLayout(employeeListBox_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        stackedWidgetEditAndAdd_2 = new QStackedWidget(frame_5);
        stackedWidgetEditAndAdd_2->setObjectName("stackedWidgetEditAndAdd_2");
        stackedWidgetEditAndAdd_2->setGeometry(QRect(0, 10, 438, 537));
        addEmployeePage_3 = new QWidget();
        addEmployeePage_3->setObjectName("addEmployeePage_3");
        formLayout_5 = new QFormLayout(addEmployeePage_3);
        formLayout_5->setObjectName("formLayout_5");
        addEmployeeBox_5 = new QGroupBox(addEmployeePage_3);
        addEmployeeBox_5->setObjectName("addEmployeeBox_5");
        adminAddEmployeeForm_5 = new QFormLayout(addEmployeeBox_5);
        adminAddEmployeeForm_5->setObjectName("adminAddEmployeeForm_5");

        formLayout_5->setWidget(0, QFormLayout::SpanningRole, addEmployeeBox_5);

        stackedWidgetEditAndAdd_2->addWidget(addEmployeePage_3);
        editEmplyerPage_3 = new QWidget();
        editEmplyerPage_3->setObjectName("editEmplyerPage_3");
        formLayout_6 = new QFormLayout(editEmplyerPage_3);
        formLayout_6->setObjectName("formLayout_6");
        addEmployeeBox_6 = new QGroupBox(editEmplyerPage_3);
        addEmployeeBox_6->setObjectName("addEmployeeBox_6");
        adminAddEmployeeForm_6 = new QFormLayout(addEmployeeBox_6);
        adminAddEmployeeForm_6->setObjectName("adminAddEmployeeForm_6");
        labelID_6 = new QLabel(addEmployeeBox_6);
        labelID_6->setObjectName("labelID_6");

        adminAddEmployeeForm_6->setWidget(0, QFormLayout::LabelRole, labelID_6);

        adminEditEmployeeID_6 = new QLineEdit(addEmployeeBox_6);
        adminEditEmployeeID_6->setObjectName("adminEditEmployeeID_6");

        adminAddEmployeeForm_6->setWidget(0, QFormLayout::FieldRole, adminEditEmployeeID_6);

        labelNom_6 = new QLabel(addEmployeeBox_6);
        labelNom_6->setObjectName("labelNom_6");

        adminAddEmployeeForm_6->setWidget(1, QFormLayout::LabelRole, labelNom_6);

        adminEditEmployeeName_6 = new QLineEdit(addEmployeeBox_6);
        adminEditEmployeeName_6->setObjectName("adminEditEmployeeName_6");

        adminAddEmployeeForm_6->setWidget(1, QFormLayout::FieldRole, adminEditEmployeeName_6);

        labelAge_6 = new QLabel(addEmployeeBox_6);
        labelAge_6->setObjectName("labelAge_6");

        adminAddEmployeeForm_6->setWidget(2, QFormLayout::LabelRole, labelAge_6);

        adminEditEmployeeAge_6 = new QLineEdit(addEmployeeBox_6);
        adminEditEmployeeAge_6->setObjectName("adminEditEmployeeAge_6");

        adminAddEmployeeForm_6->setWidget(2, QFormLayout::FieldRole, adminEditEmployeeAge_6);

        labelContactParent_6 = new QLabel(addEmployeeBox_6);
        labelContactParent_6->setObjectName("labelContactParent_6");

        adminAddEmployeeForm_6->setWidget(3, QFormLayout::LabelRole, labelContactParent_6);

        adminEditEmployeeContact_6 = new QLineEdit(addEmployeeBox_6);
        adminEditEmployeeContact_6->setObjectName("adminEditEmployeeContact_6");

        adminAddEmployeeForm_6->setWidget(3, QFormLayout::FieldRole, adminEditEmployeeContact_6);

        adminLabelEmployeePosition_6 = new QLabel(addEmployeeBox_6);
        adminLabelEmployeePosition_6->setObjectName("adminLabelEmployeePosition_6");

        adminAddEmployeeForm_6->setWidget(4, QFormLayout::LabelRole, adminLabelEmployeePosition_6);

        adminEditEmployeePosition_6 = new QLineEdit(addEmployeeBox_6);
        adminEditEmployeePosition_6->setObjectName("adminEditEmployeePosition_6");

        adminAddEmployeeForm_6->setWidget(4, QFormLayout::FieldRole, adminEditEmployeePosition_6);

        adminLabelEmployeePhone_6 = new QLabel(addEmployeeBox_6);
        adminLabelEmployeePhone_6->setObjectName("adminLabelEmployeePhone_6");

        adminAddEmployeeForm_6->setWidget(5, QFormLayout::LabelRole, adminLabelEmployeePhone_6);

        adminEditEmployeePhone_6 = new QLineEdit(addEmployeeBox_6);
        adminEditEmployeePhone_6->setObjectName("adminEditEmployeePhone_6");

        adminAddEmployeeForm_6->setWidget(5, QFormLayout::FieldRole, adminEditEmployeePhone_6);

        adminBtnCancel_6 = new QPushButton(addEmployeeBox_6);
        adminBtnCancel_6->setObjectName("adminBtnCancel_6");
        adminBtnCancel_6->setCheckable(true);
        adminBtnCancel_6->setChecked(true);

        adminAddEmployeeForm_6->setWidget(6, QFormLayout::FieldRole, adminBtnCancel_6);

        adminBtnConfirm_6 = new QPushButton(addEmployeeBox_6);
        adminBtnConfirm_6->setObjectName("adminBtnConfirm_6");

        adminAddEmployeeForm_6->setWidget(6, QFormLayout::LabelRole, adminBtnConfirm_6);


        formLayout_6->setWidget(0, QFormLayout::LabelRole, addEmployeeBox_6);

        stackedWidgetEditAndAdd_2->addWidget(editEmplyerPage_3);
        stackedWidgetMainContentView->addWidget(stats);

        mainLayout->addWidget(mainContent);

        adminmainwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(adminmainwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1386, 21));
        adminmainwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(adminmainwindow);
        statusbar->setObjectName("statusbar");
        adminmainwindow->setStatusBar(statusbar);

        retranslateUi(adminmainwindow);

        QMetaObject::connectSlotsByName(adminmainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *adminmainwindow)
    {
        adminmainwindow->setWindowTitle(QCoreApplication::translate("adminmainwindow", "adminmainwindow", nullptr));
        sidebar->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #fff8e6, stop:1 #fff8e6); color: white; border-top-left-radius: 18px; border-bottom-left-radius: 18px; min-width: 260px; max-width: 300px;", nullptr));
        adminLogoLabel->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: transparent; margin-bottom: 18px; margin-top: 18px;", nullptr));
        btnAccueil->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; padding: 12px; font-weight: bold; margin-bottom: 8px; font-size: 16px; transition: background 0.2s; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        btnAccueil->setText(QCoreApplication::translate("adminmainwindow", "Home", nullptr));
        btnGestionPersonnel->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; padding: 12px; font-weight: bold; margin-bottom: 8px; font-size: 16px; transition: background 0.2s; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        btnGestionPersonnel->setText(QCoreApplication::translate("adminmainwindow", "Employee Admin Panel", nullptr));
        btnDeconnecter->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: #e74c3c; background: transparent; font-weight: bold; margin-top: 24px; font-size: 16px; }\n"
"QPushButton:hover { background: #e74c3c; color: #fff; }", nullptr));
        btnDeconnecter->setText(QCoreApplication::translate("adminmainwindow", "Logout", nullptr));
        mainContent->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #fff8e6; color: white; border-top-right-radius: 18px; border-bottom-right-radius: 18px; padding: 24px;", nullptr));
        searchMember->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; padding: 12px; font-size: 16px;", nullptr));
        searchMember->setPlaceholderText(QCoreApplication::translate("adminmainwindow", "Search for an emplyer :", nullptr));
        sortCombo->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; padding: 12px; font-size: 16px;", nullptr));
        sortCombo->setPlaceholderText(QCoreApplication::translate("adminmainwindow", "Sort by", nullptr));
        adminBtnShowStats->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        adminBtnShowStats->setText(QCoreApplication::translate("adminmainwindow", "Show Statistics", nullptr));
        employeeListBox->setTitle(QString());
        employeeListLabel->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        employeeListLabel->setText(QCoreApplication::translate("adminmainwindow", "Employee List", nullptr));
        QTableWidgetItem *___qtablewidgetitem = adminEmployeeTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("adminmainwindow", "Employee ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = adminEmployeeTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("adminmainwindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = adminEmployeeTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("adminmainwindow", "Age", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = adminEmployeeTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("adminmainwindow", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = adminEmployeeTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("adminmainwindow", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = adminEmployeeTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("adminmainwindow", "Phone Num", nullptr));
        adminEmployeeTable->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 12px; font-size: 15px;", nullptr));
        adminBtnEditEmployee->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        adminBtnEditEmployee->setText(QCoreApplication::translate("adminmainwindow", "Edit", nullptr));
        adminBtnAddEmployee->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        adminBtnAddEmployee->setText(QCoreApplication::translate("adminmainwindow", "Add", nullptr));
        adminBtnDeleteEmployee->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        adminBtnDeleteEmployee->setText(QCoreApplication::translate("adminmainwindow", "Delete", nullptr));
        addEmployeeBox->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #946d65; color: white; border-radius: 18px; font-weight: bold; font-size: 16px; padding: 18px;", nullptr));
        addEmployeeBox->setTitle(QCoreApplication::translate("adminmainwindow", "Add Employee", nullptr));
        labelID->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelID->setText(QCoreApplication::translate("adminmainwindow", "Employee ID", nullptr));
        adminEditEmployeeID->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelNom->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelNom->setText(QCoreApplication::translate("adminmainwindow", "Name", nullptr));
        adminEditEmployeeName->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelAge->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelAge->setText(QCoreApplication::translate("adminmainwindow", "Age", nullptr));
        adminEditEmployeeAge->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelContactParent->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelContactParent->setText(QCoreApplication::translate("adminmainwindow", "Contact", nullptr));
        adminEditEmployeeContact->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminLabelEmployeePosition->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        adminLabelEmployeePosition->setText(QCoreApplication::translate("adminmainwindow", "Position", nullptr));
        adminEditEmployeePosition->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminLabelEmployeePhone->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        adminLabelEmployeePhone->setText(QCoreApplication::translate("adminmainwindow", "Phone Number", nullptr));
        adminEditEmployeePhone->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminBtnCancel->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: #FFFF; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        adminBtnCancel->setText(QCoreApplication::translate("adminmainwindow", "Cancel", nullptr));
        adminBtnConfirm->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        adminBtnConfirm->setText(QCoreApplication::translate("adminmainwindow", "Confirm", nullptr));
        addEmployeeBox_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #946d65; color: white; border-radius: 18px; font-weight: bold; font-size: 16px; padding: 18px;", nullptr));
        addEmployeeBox_2->setTitle(QCoreApplication::translate("adminmainwindow", "Edit Employee", nullptr));
        labelID_3->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelID_3->setText(QCoreApplication::translate("adminmainwindow", "Employee ID", nullptr));
        adminEditEmployeeID_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelNom_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelNom_2->setText(QCoreApplication::translate("adminmainwindow", "Name", nullptr));
        adminEditEmployeeName_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelAge_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelAge_2->setText(QCoreApplication::translate("adminmainwindow", "Age", nullptr));
        adminEditEmployeeAge_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelContactParent_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelContactParent_2->setText(QCoreApplication::translate("adminmainwindow", "Contact", nullptr));
        adminEditEmployeeContact_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminLabelEmployeePosition_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        adminLabelEmployeePosition_2->setText(QCoreApplication::translate("adminmainwindow", "Position", nullptr));
        adminEditEmployeePosition_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminLabelEmployeePhone_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        adminLabelEmployeePhone_2->setText(QCoreApplication::translate("adminmainwindow", "Phone Number", nullptr));
        adminEditEmployeePhone_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminBtnCancel_2->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #f9bab7; color: #FFFF; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #cfb9aa; color: #fff; }", nullptr));
        adminBtnCancel_2->setText(QCoreApplication::translate("adminmainwindow", "Cancel", nullptr));
        adminBtnConfirm_4->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        adminBtnConfirm_4->setText(QCoreApplication::translate("adminmainwindow", "Confirm", nullptr));
        employeeListBox_2->setTitle(QString());
        addEmployeeBox_5->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #946d65; color: white; border-radius: 18px; font-weight: bold; font-size: 16px; padding: 18px;", nullptr));
        addEmployeeBox_5->setTitle(QCoreApplication::translate("adminmainwindow", "Add Employee", nullptr));
        addEmployeeBox_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #946d65; color: white; border-radius: 18px; font-weight: bold; font-size: 16px; padding: 18px;", nullptr));
        addEmployeeBox_6->setTitle(QCoreApplication::translate("adminmainwindow", "Edit Employee", nullptr));
        labelID_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelID_6->setText(QCoreApplication::translate("adminmainwindow", "Employee ID", nullptr));
        adminEditEmployeeID_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelNom_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelNom_6->setText(QCoreApplication::translate("adminmainwindow", "Name", nullptr));
        adminEditEmployeeName_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelAge_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelAge_6->setText(QCoreApplication::translate("adminmainwindow", "Age", nullptr));
        adminEditEmployeeAge_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        labelContactParent_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        labelContactParent_6->setText(QCoreApplication::translate("adminmainwindow", "Contact", nullptr));
        adminEditEmployeeContact_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminLabelEmployeePosition_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        adminLabelEmployeePosition_6->setText(QCoreApplication::translate("adminmainwindow", "Position", nullptr));
        adminEditEmployeePosition_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminLabelEmployeePhone_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "color: white; font-size: 15px;", nullptr));
        adminLabelEmployeePhone_6->setText(QCoreApplication::translate("adminmainwindow", "Phone Number", nullptr));
        adminEditEmployeePhone_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #e3eafc; color: #1a237e; border-radius: 8px; padding: 8px; font-size: 15px;", nullptr));
        adminBtnCancel_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #f9bab7; color: #FFFF; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #cfb9aa; color: #fff; }", nullptr));
        adminBtnCancel_6->setText(QCoreApplication::translate("adminmainwindow", "Cancel", nullptr));
        adminBtnConfirm_6->setStyleSheet(QCoreApplication::translate("adminmainwindow", "background: #cfb9aa; color: white; border-radius: 12px; font-weight: bold; padding: 12px; font-size: 16px; }\n"
"QPushButton:hover { background: #f9bab7; color: #fff; }", nullptr));
        adminBtnConfirm_6->setText(QCoreApplication::translate("adminmainwindow", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adminmainwindow: public Ui_adminmainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINMAINWINDOW_H
