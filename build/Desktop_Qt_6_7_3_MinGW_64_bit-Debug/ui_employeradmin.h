/********************************************************************************
** Form generated from reading UI file 'employeradmin.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYERADMIN_H
#define UI_EMPLOYERADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmployerAdmin
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_main;
    QFrame *topBarFrame;
    QHBoxLayout *topBarLayout;
    QLabel *logoLabel;
    QSpacerItem *horizontalSpacer_top;
    QFrame *userInfoFrame;
    QHBoxLayout *userInfoLayout;
    QLabel *userAvatarLabel;
    QVBoxLayout *userDetailsLayout;
    QLabel *userNameLabel;
    QLabel *userRoleLabel;
    QFrame *mainFrame;
    QHBoxLayout *mainHorizontalLayout;
    QFrame *sidebarFrame;
    QVBoxLayout *sidebarLayout;
    QFrame *navigationFrame;
    QVBoxLayout *navigationLayout;
    QPushButton *employeesButton;
    QPushButton *membersButton;
    QPushButton *equipmentButton;
    QPushButton *activitiesButton;
    QPushButton *paymentsButton;
    QSpacerItem *verticalSpacer_sidebar;
    QFrame *mainContentFrame;
    QVBoxLayout *mainContentLayout;
    QStackedWidget *stackedWidget;
    QWidget *employeePage;
    QVBoxLayout *employeePageLayout;
    QLabel *pageTitle;
    QTabWidget *employeeTabWidget;
    QWidget *listTab;
    QVBoxLayout *listTabLayout;
    QFrame *searchFrame;
    QHBoxLayout *searchLayout;
    QLineEdit *searchLineEdit;
    QPushButton *employeeSearchButton;
    QTableWidget *employeeTable;
    QWidget *addTab;
    QVBoxLayout *addTabLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *formMainLayout;
    QFrame *formFrame;
    QGridLayout *gridLayout;
    QLabel *empIdLabel;
    QLineEdit *empIdLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEedit;
    QLabel *firstNameLabel;
    QLineEdit *firstNameLineEdit;
    QLabel *hireDateLabel;
    QDateEdit *hireDateEdit;
    QLabel *lastNameLabel;
    QLineEdit *lastNameLineEdit;
    QLabel *positionLabel;
    QLineEdit *positionLineEdit;
    QLabel *genderLabel;
    QComboBox *genderComboBox;
    QLabel *salaryLabel;
    QLineEdit *salaryLineEdit;
    QLabel *ageLabel;
    QSpinBox *ageSpinBox;
    QLabel *statusLabel;
    QComboBox *statusComboBox;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *departmentLabel;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QFrame *photoFrame;
    QVBoxLayout *photoLayout;
    QLabel *photoLabel;
    QPushButton *employeeUploadPhotoButton;
    QFrame *notesFrame;
    QVBoxLayout *notesLayout;
    QLabel *notesLabel;
    QTextEdit *notesTextEdit;
    QFrame *buttonFrame;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *confirmAddButton;
    QPushButton *confirmUpdateButton;
    QComboBox *departmentComboBox;
    QWidget *statisticsTab;
    QVBoxLayout *statisticsLayout;
    QFrame *statsFrame;
    QGridLayout *statsGridLayout;
    QFrame *totalEmployeesCard;
    QVBoxLayout *totalEmpLayout;
    QLabel *totalEmpTitle;
    QLabel *totalEmpNumber;
    QFrame *activeEmployeesCard;
    QVBoxLayout *activeEmpLayout;
    QLabel *activeEmpTitle;
    QLabel *activeEmpNumber;
    QFrame *newHiresCard;
    QVBoxLayout *newHiresLayout;
    QLabel *newHiresTitle;
    QLabel *newHiresNumber;
    QFrame *departmentStatsFrame;
    QVBoxLayout *deptStatsLayout;
    QLabel *deptStatsTitle;
    QTableWidget *departmentStatsTable;
    QWidget *membersPage;
    QVBoxLayout *verticalLayout;
    QLabel *memberPageTitle;
    QTabWidget *memberTabWidget;
    QWidget *memberListTab;
    QVBoxLayout *memberListTabLayout;
    QFrame *memberSearchFrame;
    QHBoxLayout *memberSearchLayout;
    QLineEdit *memberSearchLineEdit;
    QPushButton *memberSearchButton;
    QTableWidget *memberTable;
    QWidget *memberAddTab;
    QVBoxLayout *memberAddTabLayout;
    QScrollArea *memberScrollArea;
    QWidget *memberScrollAreaContents;
    QVBoxLayout *memberFormMainLayout;
    QFrame *memberFormFrame;
    QGridLayout *memberFormLayout;
    QLabel *memberIdLabel;
    QLineEdit *memberIdLineEdit;
    QLabel *membershipTypeLabel;
    QComboBox *membershipTypeComboBox;
    QLabel *memberFirstNameLabel;
    QLineEdit *memberFirstNameLineEdit;
    QLabel *memberJoinDateLabel;
    QDateEdit *memberJoinDateEdit;
    QLabel *memberLastNameLabel;
    QLineEdit *memberLastNameLineEdit;
    QLabel *membershipPlanLabel;
    QLineEdit *membershipPlanLineEdit;
    QLabel *memberGenderLabel;
    QComboBox *memberGenderComboBox;
    QLabel *memberMonthlyFeeLabel;
    QLineEdit *memberMonthlyFeeLineEdit;
    QLabel *memberAgeLabel;
    QSpinBox *memberAgeSpinBox;
    QLabel *memberStatusLabel;
    QComboBox *memberStatusComboBox;
    QLabel *memberEmailLabel;
    QLineEdit *memberEmailLineEdit;
    QLabel *memberPhoneLabel;
    QLineEdit *memberPhoneLineEdit;
    QFrame *memberPhotoFrame;
    QVBoxLayout *memberPhotoLayout;
    QLabel *memberPhotoLabel;
    QPushButton *memberUploadPhotoButton;
    QFrame *memberNotesFrame;
    QVBoxLayout *memberNotesLayout;
    QLabel *memberNotesLabel;
    QTextEdit *memberNotesTextEdit;
    QFrame *memberButtonFrame;
    QHBoxLayout *memberButtonLayout;
    QSpacerItem *buttonSpacer_2;
    QPushButton *memberConfirmAddButton;
    QPushButton *memberConfirmUpdateButton;
    QWidget *memberStatisticsTab;
    QVBoxLayout *memberStatisticsLayout;
    QFrame *memberStatsFrame;
    QGridLayout *memberStatsGridLayout;
    QFrame *totalMembersCard;
    QVBoxLayout *totalMembersLayout;
    QLabel *totalMembersTitle;
    QLabel *totalMembersNumber;
    QFrame *activeMembersCard;
    QVBoxLayout *activeMembersLayout;
    QLabel *activeMembersTitle;
    QLabel *activeMembersNumber;
    QFrame *newMembersCard;
    QVBoxLayout *newMembersLayout;
    QLabel *newMembersTitle;
    QLabel *newMembersNumber;
    QFrame *membershipStatsFrame;
    QVBoxLayout *membershipStatsLayout;
    QLabel *membershipStatsTitle;
    QTableWidget *membershipStatsTable;
    QWidget *equipmentPage;
    QVBoxLayout *equipmentPageLayout;
    QLabel *equipmentLabel;
    QWidget *activitiesPage;
    QVBoxLayout *activitiesPageLayout;
    QLabel *activityPageTitle;
    QTabWidget *activityTabWidget;
    QWidget *activityListTab;
    QVBoxLayout *activityListTabLayout;
    QFrame *activitySearchFrame;
    QHBoxLayout *activitySearchLayout;
    QLineEdit *activitySearchLineEdit;
    QPushButton *activitySearchButton;
    QTableWidget *activityTable;
    QWidget *activityAddTab;
    QVBoxLayout *activityAddTabLayout;
    QScrollArea *activityScrollArea;
    QWidget *activityScrollAreaContents;
    QVBoxLayout *activityFormMainLayout;
    QFrame *activityFormFrame;
    QGridLayout *activityFormLayout;
    QLineEdit *responsibleLineEdit;
    QComboBox *activityStatusComboBox;
    QLabel *responsibleLabel;
    QLabel *eventDateLabel;
    QDateEdit *eventDateEdit;
    QTimeEdit *eventTimeEdit;
    QLabel *eventTimeLabel;
    QLineEdit *activityIdLineEdit;
    QLabel *activityIdLabel;
    QLabel *activityTypeLabel;
    QFrame *activityButtonFrame;
    QHBoxLayout *activityButtonLayout;
    QSpacerItem *activityButtonSpacer;
    QPushButton *activityConfirmButton;
    QPushButton *activityUpdateButton;
    QComboBox *activityTypeComboBox;
    QFrame *activityDescriptionFrame;
    QVBoxLayout *activityDescriptionLayout;
    QTextEdit *activityDescriptionTextEdit;
    QLabel *activityStatusLabel;
    QLabel *activityDescriptionLabel;
    QWidget *activityStatisticsTab;
    QVBoxLayout *activityStatisticsLayout;
    QFrame *activityStatsFrame;
    QGridLayout *activityStatsGridLayout;
    QFrame *totalActivitiesCard;
    QVBoxLayout *totalActivitiesLayout;
    QLabel *totalActivitiesTitle;
    QLabel *totalActivitiesNumber;
    QFrame *upcomingActivitiesCard;
    QVBoxLayout *upcomingActivitiesLayout;
    QLabel *upcomingActivitiesTitle;
    QLabel *upcomingActivitiesNumber;
    QFrame *activeActivitiesCard;
    QVBoxLayout *activeActivitiesLayout;
    QLabel *activeActivitiesTitle;
    QLabel *activeActivitiesNumber;
    QFrame *activityTypeStatsFrame;
    QVBoxLayout *activityTypeStatsLayout;
    QLabel *activityTypeStatsTitle;
    QTableWidget *activityTypeStatsTable;
    QWidget *paymentsPage;
    QVBoxLayout *paymentsPageLayout;
    QLabel *paymentsLabel;

    void setupUi(QMainWindow *EmployerAdmin)
    {
        if (EmployerAdmin->objectName().isEmpty())
            EmployerAdmin->setObjectName("EmployerAdmin");
        EmployerAdmin->resize(1200, 800);
        EmployerAdmin->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #f5f7fa;\n"
"}\n"
"\n"
"/* Top Bar Styling */\n"
"#topBarFrame {\n"
"    background-color: white;\n"
"    border-bottom: 1px solid #e0e4e7;\n"
"}\n"
"\n"
"#logoLabel {\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"#userInfoFrame {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"#userNameLabel {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"#userRoleLabel {\n"
"    font-size: 12px;\n"
"    color: #7f8c8d;\n"
"}\n"
"\n"
"#userAvatarLabel {\n"
"    background-color: #3498db;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* Sidebar Styling */\n"
"#sidebarFrame {\n"
"    background-color: white;\n"
"    border-right: 1px solid #e0e4e7;\n"
"}\n"
"\n"
"#navigationFrame {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#employeesButton, QPushButton#membersButton, QPushButton#equipmentButton, QPushButton#activitiesButton, Q"
                        "PushButton#paymentsButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    padding: 15px 20px;\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    color: #2c3e50;\n"
"    border-radius: 8px;\n"
"    margin: 2px 10px;\n"
"}\n"
"\n"
"QPushButton#employeesButton:hover, QPushButton#membersButton:hover, QPushButton#equipmentButton:hover, QPushButton#activitiesButton:hover, QPushButton#paymentsButton:hover {\n"
"    background-color: #e8f4f5;\n"
"}\n"
"\n"
"QPushButton#employeesButton:checked, QPushButton#membersButton:checked, QPushButton#equipmentButton:checked, QPushButton#activitiesButton:checked, QPushButton#paymentsButton:checked {\n"
"    background-color: #16a5b3;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#employeesButton:checked:hover, QPushButton#membersButton:checked:hover, QPushButton#equipmentButton:checked:hover, QPushButton#activitiesButton:checked:hover, QPushButton#paymentsButton:checked:hover {\n"
"    background-color: #139aa6;\n"
"}\n"
"\n"
"/* Main Content Styl"
                        "ing */\n"
"#mainContentFrame {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"/* Tab Widget Styling */\n"
"QTabWidget::pane {\n"
"    border: 2px solid #16a5b3;\n"
"    background-color: white;\n"
"    border-radius: 12px;\n"
"    box-shadow: 0 4px 6px rgba(22, 165, 179, 0.1);\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #ecf0f1;\n"
"    color: #2c3e50;\n"
"    padding: 12px 24px;\n"
"    margin-right: 2px;\n"
"    border-top-left-radius: 8px;\n"
"    border-top-right-radius: 8px;\n"
"    border: 1px solid #e0e4e7;\n"
"    border-bottom: none;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #16a5b3;\n"
"    color: white;\n"
"    border-color: #16a5b3;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QTabBar::tab:hover:!selected {\n"
"    background-color: #d5dbdb;\n"
"    border-color: #16a5b3;\n"
"    transition: all 0.3s ease;\n"
"}\n"
"\n"
"/* Statistics Cards Styling */\n"
"QFrame[objectName*=\"Card\"] {\n"
"    background-color: white;\n"
"    border: 1px solid #e0e4e7;\n"
"    "
                        "border-radius: 16px;\n"
"    padding: 20px;\n"
"    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.05);\n"
"}\n"
"\n"
"QFrame[objectName*=\"Card\"]:hover {\n"
"    box-shadow: 0 4px 20px rgba(22, 165, 179, 0.15);\n"
"    border-color: #16a5b3;\n"
"    transition: all 0.3s ease;\n"
"}\n"
"\n"
"/* Form Styling */\n"
"QLineEdit {\n"
"    padding: 14px 16px;\n"
"    border: 2px solid #e0e4e7;\n"
"    border-radius: 10px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02);\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #16a5b3;\n"
"    box-shadow: 0 0 0 3px rgba(22, 165, 179, 0.1);\n"
"    outline: none;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border-color: #16a5b3;\n"
"    transition: border-color 0.2s ease;\n"
"}\n"
"\n"
"QComboBox {\n"
"    padding: 14px 16px;\n"
"    border: 2px solid #e0e4e7;\n"
"    border-radius: 10px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02);\n"
"}\n"
"\n"
"QComboBox:"
                        "focus {\n"
"    border-color: #16a5b3;\n"
"    box-shadow: 0 0 0 3px rgba(22, 165, 179, 0.1);\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border-color: #16a5b3;\n"
"    transition: border-color 0.2s ease;\n"
"}\n"
"\n"
"QDateEdit, QSpinBox {\n"
"    padding: 14px 16px;\n"
"    border: 2px solid #e0e4e7;\n"
"    border-radius: 10px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02);\n"
"}\n"
"\n"
"QDateEdit:focus, QSpinBox:focus {\n"
"    border-color: #16a5b3;\n"
"    box-shadow: 0 0 0 3px rgba(22, 165, 179, 0.1);\n"
"}\n"
"\n"
"QTextEdit {\n"
"    padding: 14px 16px;\n"
"    border: 2px solid #e0e4e7;\n"
"    border-radius: 10px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02);\n"
"}\n"
"\n"
"QTextEdit:focus {\n"
"    border-color: #16a5b3;\n"
"    box-shadow: 0 0 0 3px rgba(22, 165, 179, 0.1);\n"
"}\n"
"\n"
"QPushButton#actionButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
""
                        "                               stop:0 #16a5b3, stop:1 #139aa6);\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 14px 28px;\n"
"    border-radius: 10px;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    box-shadow: 0 4px 8px rgba(22, 165, 179, 0.2);\n"
"}\n"
"\n"
"QPushButton#actionButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 #139aa6, stop:1 #0f858f);\n"
"    box-shadow: 0 6px 12px rgba(22, 165, 179, 0.3);\n"
"    transform: translateY(-1px);\n"
"}\n"
"\n"
"QPushButton#actionButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 #0f858f, stop:1 #0c6b73);\n"
"    box-shadow: 0 2px 4px rgba(22, 165, 179, 0.2);\n"
"    transform: translateY(0px);\n"
"}\n"
"\n"
"/* Table Styling */\n"
"QTableWidget {\n"
"    background-color: white;\n"
"    gridline-color:  #e0e4e7;\n"
"    border: 1px solid #e0e4e7;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"QHeaderView::sect"
                        "ion {\n"
"    background-color: #f8f9fa;\n"
"    color: #2c3e50;\n"
"    padding: 5px;\n"
"    border: none;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* Frame Styling */\n"
"QFrame {\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"/* Label Styling */\n"
"QLabel {\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"/* Search Frame Styling */\n"
"QFrame[objectName*=\"SearchFrame\"], QFrame[objectName*=\"searchFrame\"] {\n"
"    background-color: rgba(22, 165, 179, 0.02);\n"
"    border: 1px solid rgba(22, 165, 179, 0.1);\n"
"    border-radius: 12px;\n"
"    padding: 8px;\n"
"}\n"
""));
        centralwidget = new QWidget(EmployerAdmin);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_main = new QVBoxLayout(centralwidget);
        verticalLayout_main->setSpacing(0);
        verticalLayout_main->setObjectName("verticalLayout_main");
        verticalLayout_main->setContentsMargins(0, 0, 0, 0);
        topBarFrame = new QFrame(centralwidget);
        topBarFrame->setObjectName("topBarFrame");
        topBarFrame->setMinimumSize(QSize(0, 70));
        topBarFrame->setMaximumSize(QSize(16777215, 70));
        topBarLayout = new QHBoxLayout(topBarFrame);
        topBarLayout->setObjectName("topBarLayout");
        topBarLayout->setContentsMargins(20, -1, 20, -1);
        logoLabel = new QLabel(topBarFrame);
        logoLabel->setObjectName("logoLabel");

        topBarLayout->addWidget(logoLabel);

        horizontalSpacer_top = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topBarLayout->addItem(horizontalSpacer_top);

        userInfoFrame = new QFrame(topBarFrame);
        userInfoFrame->setObjectName("userInfoFrame");
        userInfoLayout = new QHBoxLayout(userInfoFrame);
        userInfoLayout->setObjectName("userInfoLayout");
        userAvatarLabel = new QLabel(userInfoFrame);
        userAvatarLabel->setObjectName("userAvatarLabel");
        userAvatarLabel->setMinimumSize(QSize(40, 40));
        userAvatarLabel->setMaximumSize(QSize(40, 40));
        userAvatarLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        userInfoLayout->addWidget(userAvatarLabel);

        userDetailsLayout = new QVBoxLayout();
        userDetailsLayout->setSpacing(2);
        userDetailsLayout->setObjectName("userDetailsLayout");
        userNameLabel = new QLabel(userInfoFrame);
        userNameLabel->setObjectName("userNameLabel");

        userDetailsLayout->addWidget(userNameLabel);

        userRoleLabel = new QLabel(userInfoFrame);
        userRoleLabel->setObjectName("userRoleLabel");

        userDetailsLayout->addWidget(userRoleLabel);


        userInfoLayout->addLayout(userDetailsLayout);


        topBarLayout->addWidget(userInfoFrame);


        verticalLayout_main->addWidget(topBarFrame);

        mainFrame = new QFrame(centralwidget);
        mainFrame->setObjectName("mainFrame");
        mainHorizontalLayout = new QHBoxLayout(mainFrame);
        mainHorizontalLayout->setSpacing(0);
        mainHorizontalLayout->setObjectName("mainHorizontalLayout");
        mainHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        sidebarFrame = new QFrame(mainFrame);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarFrame->setMinimumSize(QSize(250, 0));
        sidebarFrame->setMaximumSize(QSize(250, 16777215));
        sidebarLayout = new QVBoxLayout(sidebarFrame);
        sidebarLayout->setSpacing(10);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(0, 20, 0, 20);
        navigationFrame = new QFrame(sidebarFrame);
        navigationFrame->setObjectName("navigationFrame");
        navigationLayout = new QVBoxLayout(navigationFrame);
        navigationLayout->setSpacing(5);
        navigationLayout->setObjectName("navigationLayout");
        employeesButton = new QPushButton(navigationFrame);
        employeesButton->setObjectName("employeesButton");
        employeesButton->setCheckable(true);
        employeesButton->setChecked(true);

        navigationLayout->addWidget(employeesButton);

        membersButton = new QPushButton(navigationFrame);
        membersButton->setObjectName("membersButton");
        membersButton->setCheckable(true);

        navigationLayout->addWidget(membersButton);

        equipmentButton = new QPushButton(navigationFrame);
        equipmentButton->setObjectName("equipmentButton");
        equipmentButton->setCheckable(true);

        navigationLayout->addWidget(equipmentButton);

        activitiesButton = new QPushButton(navigationFrame);
        activitiesButton->setObjectName("activitiesButton");
        activitiesButton->setCheckable(true);

        navigationLayout->addWidget(activitiesButton);

        paymentsButton = new QPushButton(navigationFrame);
        paymentsButton->setObjectName("paymentsButton");
        paymentsButton->setCheckable(true);

        navigationLayout->addWidget(paymentsButton);


        sidebarLayout->addWidget(navigationFrame);

        verticalSpacer_sidebar = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(verticalSpacer_sidebar);


        mainHorizontalLayout->addWidget(sidebarFrame);

        mainContentFrame = new QFrame(mainFrame);
        mainContentFrame->setObjectName("mainContentFrame");
        mainContentLayout = new QVBoxLayout(mainContentFrame);
        mainContentLayout->setObjectName("mainContentLayout");
        mainContentLayout->setContentsMargins(20, 20, 20, 20);
        stackedWidget = new QStackedWidget(mainContentFrame);
        stackedWidget->setObjectName("stackedWidget");
        employeePage = new QWidget();
        employeePage->setObjectName("employeePage");
        employeePageLayout = new QVBoxLayout(employeePage);
        employeePageLayout->setObjectName("employeePageLayout");
        pageTitle = new QLabel(employeePage);
        pageTitle->setObjectName("pageTitle");
        pageTitle->setStyleSheet(QString::fromUtf8("font-size: 28px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;"));

        employeePageLayout->addWidget(pageTitle);

        employeeTabWidget = new QTabWidget(employeePage);
        employeeTabWidget->setObjectName("employeeTabWidget");
        listTab = new QWidget();
        listTab->setObjectName("listTab");
        listTabLayout = new QVBoxLayout(listTab);
        listTabLayout->setObjectName("listTabLayout");
        searchFrame = new QFrame(listTab);
        searchFrame->setObjectName("searchFrame");
        searchLayout = new QHBoxLayout(searchFrame);
        searchLayout->setObjectName("searchLayout");
        searchLineEdit = new QLineEdit(searchFrame);
        searchLineEdit->setObjectName("searchLineEdit");

        searchLayout->addWidget(searchLineEdit);

        employeeSearchButton = new QPushButton(searchFrame);
        employeeSearchButton->setObjectName("employeeSearchButton");

        searchLayout->addWidget(employeeSearchButton);


        listTabLayout->addWidget(searchFrame);

        employeeTable = new QTableWidget(listTab);
        if (employeeTable->columnCount() < 7)
            employeeTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        employeeTable->setObjectName("employeeTable");
        employeeTable->setAlternatingRowColors(true);
        employeeTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        listTabLayout->addWidget(employeeTable);

        employeeTabWidget->addTab(listTab, QString());
        addTab = new QWidget();
        addTab->setObjectName("addTab");
        addTabLayout = new QVBoxLayout(addTab);
        addTabLayout->setObjectName("addTabLayout");
        scrollArea = new QScrollArea(addTab);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 542, 728));
        formMainLayout = new QVBoxLayout(scrollAreaWidgetContents);
        formMainLayout->setObjectName("formMainLayout");
        formFrame = new QFrame(scrollAreaWidgetContents);
        formFrame->setObjectName("formFrame");
        formFrame->setAutoFillBackground(false);
        formFrame->setStyleSheet(QString::fromUtf8("margin : 2px;"));
        gridLayout = new QGridLayout(formFrame);
        gridLayout->setObjectName("gridLayout");
        empIdLabel = new QLabel(formFrame);
        empIdLabel->setObjectName("empIdLabel");
        empIdLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(empIdLabel, 0, 0, 1, 1);

        empIdLineEdit = new QLineEdit(formFrame);
        empIdLineEdit->setObjectName("empIdLineEdit");

        gridLayout->addWidget(empIdLineEdit, 0, 1, 1, 1);

        passwordLabel = new QLabel(formFrame);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(passwordLabel, 0, 2, 1, 1);

        passwordLineEedit = new QLineEdit(formFrame);
        passwordLineEedit->setObjectName("passwordLineEedit");

        gridLayout->addWidget(passwordLineEedit, 0, 3, 1, 1);

        firstNameLabel = new QLabel(formFrame);
        firstNameLabel->setObjectName("firstNameLabel");
        firstNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(firstNameLabel, 1, 0, 1, 1);

        firstNameLineEdit = new QLineEdit(formFrame);
        firstNameLineEdit->setObjectName("firstNameLineEdit");

        gridLayout->addWidget(firstNameLineEdit, 1, 1, 1, 1);

        hireDateLabel = new QLabel(formFrame);
        hireDateLabel->setObjectName("hireDateLabel");
        hireDateLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(hireDateLabel, 1, 2, 1, 1);

        hireDateEdit = new QDateEdit(formFrame);
        hireDateEdit->setObjectName("hireDateEdit");
        hireDateEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        gridLayout->addWidget(hireDateEdit, 1, 3, 1, 1);

        lastNameLabel = new QLabel(formFrame);
        lastNameLabel->setObjectName("lastNameLabel");
        lastNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(lastNameLabel, 2, 0, 1, 1);

        lastNameLineEdit = new QLineEdit(formFrame);
        lastNameLineEdit->setObjectName("lastNameLineEdit");

        gridLayout->addWidget(lastNameLineEdit, 2, 1, 1, 1);

        positionLabel = new QLabel(formFrame);
        positionLabel->setObjectName("positionLabel");
        positionLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(positionLabel, 2, 2, 1, 1);

        positionLineEdit = new QLineEdit(formFrame);
        positionLineEdit->setObjectName("positionLineEdit");

        gridLayout->addWidget(positionLineEdit, 2, 3, 1, 1);

        genderLabel = new QLabel(formFrame);
        genderLabel->setObjectName("genderLabel");
        genderLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(genderLabel, 3, 0, 1, 1);

        genderComboBox = new QComboBox(formFrame);
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->setObjectName("genderComboBox");

        gridLayout->addWidget(genderComboBox, 3, 1, 1, 1);

        salaryLabel = new QLabel(formFrame);
        salaryLabel->setObjectName("salaryLabel");
        salaryLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(salaryLabel, 3, 2, 1, 1);

        salaryLineEdit = new QLineEdit(formFrame);
        salaryLineEdit->setObjectName("salaryLineEdit");

        gridLayout->addWidget(salaryLineEdit, 3, 3, 1, 1);

        ageLabel = new QLabel(formFrame);
        ageLabel->setObjectName("ageLabel");
        ageLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(ageLabel, 4, 0, 1, 1);

        ageSpinBox = new QSpinBox(formFrame);
        ageSpinBox->setObjectName("ageSpinBox");
        ageSpinBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        ageSpinBox->setMinimum(18);
        ageSpinBox->setMaximum(65);
        ageSpinBox->setValue(25);

        gridLayout->addWidget(ageSpinBox, 4, 1, 1, 1);

        statusLabel = new QLabel(formFrame);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(statusLabel, 4, 2, 1, 1);

        statusComboBox = new QComboBox(formFrame);
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->setObjectName("statusComboBox");

        gridLayout->addWidget(statusComboBox, 4, 3, 1, 1);

        emailLabel = new QLabel(formFrame);
        emailLabel->setObjectName("emailLabel");
        emailLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(emailLabel, 5, 0, 1, 1);

        emailLineEdit = new QLineEdit(formFrame);
        emailLineEdit->setObjectName("emailLineEdit");

        gridLayout->addWidget(emailLineEdit, 5, 1, 2, 1);

        departmentLabel = new QLabel(formFrame);
        departmentLabel->setObjectName("departmentLabel");
        departmentLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(departmentLabel, 6, 2, 1, 1);

        phoneLabel = new QLabel(formFrame);
        phoneLabel->setObjectName("phoneLabel");
        phoneLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(phoneLabel, 7, 0, 1, 1);

        phoneLineEdit = new QLineEdit(formFrame);
        phoneLineEdit->setObjectName("phoneLineEdit");

        gridLayout->addWidget(phoneLineEdit, 7, 1, 1, 1);

        photoFrame = new QFrame(formFrame);
        photoFrame->setObjectName("photoFrame");
        photoFrame->setStyleSheet(QString::fromUtf8("border: 2px dashed #16a5b3; border-radius: 8px; background-color: #f8f9fa;"));
        photoLayout = new QVBoxLayout(photoFrame);
        photoLayout->setObjectName("photoLayout");
        photoLabel = new QLabel(photoFrame);
        photoLabel->setObjectName("photoLabel");
        photoLabel->setStyleSheet(QString::fromUtf8("color: #16a5b3; font-weight: 600; padding: 20px;"));
        photoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        photoLayout->addWidget(photoLabel);

        employeeUploadPhotoButton = new QPushButton(photoFrame);
        employeeUploadPhotoButton->setObjectName("employeeUploadPhotoButton");

        photoLayout->addWidget(employeeUploadPhotoButton);


        gridLayout->addWidget(photoFrame, 8, 0, 1, 2);

        notesFrame = new QFrame(formFrame);
        notesFrame->setObjectName("notesFrame");
        notesLayout = new QVBoxLayout(notesFrame);
        notesLayout->setObjectName("notesLayout");
        notesLabel = new QLabel(notesFrame);
        notesLabel->setObjectName("notesLabel");
        notesLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        notesLayout->addWidget(notesLabel);

        notesTextEdit = new QTextEdit(notesFrame);
        notesTextEdit->setObjectName("notesTextEdit");
        notesTextEdit->setMaximumSize(QSize(16777215, 100));
        notesTextEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        notesLayout->addWidget(notesTextEdit);


        gridLayout->addWidget(notesFrame, 8, 2, 1, 2);

        buttonFrame = new QFrame(formFrame);
        buttonFrame->setObjectName("buttonFrame");
        buttonLayout = new QHBoxLayout(buttonFrame);
        buttonLayout->setObjectName("buttonLayout");
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        confirmAddButton = new QPushButton(buttonFrame);
        confirmAddButton->setObjectName("confirmAddButton");
        confirmAddButton->setMinimumSize(QSize(150, 45));

        buttonLayout->addWidget(confirmAddButton);

        confirmUpdateButton = new QPushButton(buttonFrame);
        confirmUpdateButton->setObjectName("confirmUpdateButton");
        confirmUpdateButton->setMinimumSize(QSize(150, 45));
        confirmUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));

        buttonLayout->addWidget(confirmUpdateButton);


        gridLayout->addWidget(buttonFrame, 9, 0, 1, 4);

        departmentComboBox = new QComboBox(formFrame);
        departmentComboBox->addItem(QString());
        departmentComboBox->addItem(QString());
        departmentComboBox->addItem(QString());
        departmentComboBox->addItem(QString());
        departmentComboBox->addItem(QString());
        departmentComboBox->setObjectName("departmentComboBox");

        gridLayout->addWidget(departmentComboBox, 6, 3, 1, 1);


        formMainLayout->addWidget(formFrame);

        scrollArea->setWidget(scrollAreaWidgetContents);

        addTabLayout->addWidget(scrollArea);

        employeeTabWidget->addTab(addTab, QString());
        statisticsTab = new QWidget();
        statisticsTab->setObjectName("statisticsTab");
        statisticsLayout = new QVBoxLayout(statisticsTab);
        statisticsLayout->setObjectName("statisticsLayout");
        statsFrame = new QFrame(statisticsTab);
        statsFrame->setObjectName("statsFrame");
        statsGridLayout = new QGridLayout(statsFrame);
        statsGridLayout->setObjectName("statsGridLayout");
        totalEmployeesCard = new QFrame(statsFrame);
        totalEmployeesCard->setObjectName("totalEmployeesCard");
        totalEmployeesCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        totalEmpLayout = new QVBoxLayout(totalEmployeesCard);
        totalEmpLayout->setObjectName("totalEmpLayout");
        totalEmpTitle = new QLabel(totalEmployeesCard);
        totalEmpTitle->setObjectName("totalEmpTitle");
        totalEmpTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        totalEmpLayout->addWidget(totalEmpTitle);

        totalEmpNumber = new QLabel(totalEmployeesCard);
        totalEmpNumber->setObjectName("totalEmpNumber");
        totalEmpNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #16a5b3;"));

        totalEmpLayout->addWidget(totalEmpNumber);


        statsGridLayout->addWidget(totalEmployeesCard, 0, 0, 1, 1);

        activeEmployeesCard = new QFrame(statsFrame);
        activeEmployeesCard->setObjectName("activeEmployeesCard");
        activeEmployeesCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        activeEmpLayout = new QVBoxLayout(activeEmployeesCard);
        activeEmpLayout->setObjectName("activeEmpLayout");
        activeEmpTitle = new QLabel(activeEmployeesCard);
        activeEmpTitle->setObjectName("activeEmpTitle");
        activeEmpTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        activeEmpLayout->addWidget(activeEmpTitle);

        activeEmpNumber = new QLabel(activeEmployeesCard);
        activeEmpNumber->setObjectName("activeEmpNumber");
        activeEmpNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #3498db;"));

        activeEmpLayout->addWidget(activeEmpNumber);


        statsGridLayout->addWidget(activeEmployeesCard, 0, 1, 1, 1);

        newHiresCard = new QFrame(statsFrame);
        newHiresCard->setObjectName("newHiresCard");
        newHiresCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        newHiresLayout = new QVBoxLayout(newHiresCard);
        newHiresLayout->setObjectName("newHiresLayout");
        newHiresTitle = new QLabel(newHiresCard);
        newHiresTitle->setObjectName("newHiresTitle");
        newHiresTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        newHiresLayout->addWidget(newHiresTitle);

        newHiresNumber = new QLabel(newHiresCard);
        newHiresNumber->setObjectName("newHiresNumber");
        newHiresNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #e67e22;"));

        newHiresLayout->addWidget(newHiresNumber);


        statsGridLayout->addWidget(newHiresCard, 0, 2, 1, 1);

        departmentStatsFrame = new QFrame(statsFrame);
        departmentStatsFrame->setObjectName("departmentStatsFrame");
        departmentStatsFrame->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px;"));
        deptStatsLayout = new QVBoxLayout(departmentStatsFrame);
        deptStatsLayout->setObjectName("deptStatsLayout");
        deptStatsTitle = new QLabel(departmentStatsFrame);
        deptStatsTitle->setObjectName("deptStatsTitle");
        deptStatsTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;"));

        deptStatsLayout->addWidget(deptStatsTitle);

        departmentStatsTable = new QTableWidget(departmentStatsFrame);
        if (departmentStatsTable->columnCount() < 3)
            departmentStatsTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        departmentStatsTable->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        departmentStatsTable->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        departmentStatsTable->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        departmentStatsTable->setObjectName("departmentStatsTable");
        departmentStatsTable->setAlternatingRowColors(true);

        deptStatsLayout->addWidget(departmentStatsTable);


        statsGridLayout->addWidget(departmentStatsFrame, 1, 0, 1, 3);


        statisticsLayout->addWidget(statsFrame);

        employeeTabWidget->addTab(statisticsTab, QString());

        employeePageLayout->addWidget(employeeTabWidget);

        stackedWidget->addWidget(employeePage);
        membersPage = new QWidget();
        membersPage->setObjectName("membersPage");
        verticalLayout = new QVBoxLayout(membersPage);
        verticalLayout->setObjectName("verticalLayout");
        memberPageTitle = new QLabel(membersPage);
        memberPageTitle->setObjectName("memberPageTitle");
        memberPageTitle->setStyleSheet(QString::fromUtf8("font-size: 28px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;"));

        verticalLayout->addWidget(memberPageTitle);

        memberTabWidget = new QTabWidget(membersPage);
        memberTabWidget->setObjectName("memberTabWidget");
        memberListTab = new QWidget();
        memberListTab->setObjectName("memberListTab");
        memberListTabLayout = new QVBoxLayout(memberListTab);
        memberListTabLayout->setObjectName("memberListTabLayout");
        memberSearchFrame = new QFrame(memberListTab);
        memberSearchFrame->setObjectName("memberSearchFrame");
        memberSearchLayout = new QHBoxLayout(memberSearchFrame);
        memberSearchLayout->setObjectName("memberSearchLayout");
        memberSearchLineEdit = new QLineEdit(memberSearchFrame);
        memberSearchLineEdit->setObjectName("memberSearchLineEdit");

        memberSearchLayout->addWidget(memberSearchLineEdit);

        memberSearchButton = new QPushButton(memberSearchFrame);
        memberSearchButton->setObjectName("memberSearchButton");

        memberSearchLayout->addWidget(memberSearchButton);


        memberListTabLayout->addWidget(memberSearchFrame);

        memberTable = new QTableWidget(memberListTab);
        if (memberTable->columnCount() < 7)
            memberTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(5, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(6, __qtablewidgetitem16);
        memberTable->setObjectName("memberTable");
        memberTable->setAlternatingRowColors(true);
        memberTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        memberListTabLayout->addWidget(memberTable);

        memberTabWidget->addTab(memberListTab, QString());
        memberAddTab = new QWidget();
        memberAddTab->setObjectName("memberAddTab");
        memberAddTabLayout = new QVBoxLayout(memberAddTab);
        memberAddTabLayout->setObjectName("memberAddTabLayout");
        memberScrollArea = new QScrollArea(memberAddTab);
        memberScrollArea->setObjectName("memberScrollArea");
        memberScrollArea->setWidgetResizable(true);
        memberScrollAreaContents = new QWidget();
        memberScrollAreaContents->setObjectName("memberScrollAreaContents");
        memberScrollAreaContents->setGeometry(QRect(0, 0, 853, 727));
        memberFormMainLayout = new QVBoxLayout(memberScrollAreaContents);
        memberFormMainLayout->setObjectName("memberFormMainLayout");
        memberFormFrame = new QFrame(memberScrollAreaContents);
        memberFormFrame->setObjectName("memberFormFrame");
        memberFormLayout = new QGridLayout(memberFormFrame);
        memberFormLayout->setObjectName("memberFormLayout");
        memberFormLayout->setHorizontalSpacing(20);
        memberFormLayout->setVerticalSpacing(15);
        memberIdLabel = new QLabel(memberFormFrame);
        memberIdLabel->setObjectName("memberIdLabel");
        memberIdLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberIdLabel, 0, 0, 1, 1);

        memberIdLineEdit = new QLineEdit(memberFormFrame);
        memberIdLineEdit->setObjectName("memberIdLineEdit");

        memberFormLayout->addWidget(memberIdLineEdit, 0, 1, 1, 1);

        membershipTypeLabel = new QLabel(memberFormFrame);
        membershipTypeLabel->setObjectName("membershipTypeLabel");
        membershipTypeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(membershipTypeLabel, 0, 2, 1, 1);

        membershipTypeComboBox = new QComboBox(memberFormFrame);
        membershipTypeComboBox->addItem(QString());
        membershipTypeComboBox->addItem(QString());
        membershipTypeComboBox->addItem(QString());
        membershipTypeComboBox->addItem(QString());
        membershipTypeComboBox->addItem(QString());
        membershipTypeComboBox->setObjectName("membershipTypeComboBox");

        memberFormLayout->addWidget(membershipTypeComboBox, 0, 3, 1, 1);

        memberFirstNameLabel = new QLabel(memberFormFrame);
        memberFirstNameLabel->setObjectName("memberFirstNameLabel");
        memberFirstNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberFirstNameLabel, 1, 0, 1, 1);

        memberFirstNameLineEdit = new QLineEdit(memberFormFrame);
        memberFirstNameLineEdit->setObjectName("memberFirstNameLineEdit");

        memberFormLayout->addWidget(memberFirstNameLineEdit, 1, 1, 1, 1);

        memberJoinDateLabel = new QLabel(memberFormFrame);
        memberJoinDateLabel->setObjectName("memberJoinDateLabel");
        memberJoinDateLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberJoinDateLabel, 1, 2, 1, 1);

        memberJoinDateEdit = new QDateEdit(memberFormFrame);
        memberJoinDateEdit->setObjectName("memberJoinDateEdit");
        memberJoinDateEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        memberFormLayout->addWidget(memberJoinDateEdit, 1, 3, 1, 1);

        memberLastNameLabel = new QLabel(memberFormFrame);
        memberLastNameLabel->setObjectName("memberLastNameLabel");
        memberLastNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberLastNameLabel, 2, 0, 1, 1);

        memberLastNameLineEdit = new QLineEdit(memberFormFrame);
        memberLastNameLineEdit->setObjectName("memberLastNameLineEdit");

        memberFormLayout->addWidget(memberLastNameLineEdit, 2, 1, 1, 1);

        membershipPlanLabel = new QLabel(memberFormFrame);
        membershipPlanLabel->setObjectName("membershipPlanLabel");
        membershipPlanLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(membershipPlanLabel, 2, 2, 1, 1);

        membershipPlanLineEdit = new QLineEdit(memberFormFrame);
        membershipPlanLineEdit->setObjectName("membershipPlanLineEdit");

        memberFormLayout->addWidget(membershipPlanLineEdit, 2, 3, 1, 1);

        memberGenderLabel = new QLabel(memberFormFrame);
        memberGenderLabel->setObjectName("memberGenderLabel");
        memberGenderLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberGenderLabel, 3, 0, 1, 1);

        memberGenderComboBox = new QComboBox(memberFormFrame);
        memberGenderComboBox->addItem(QString());
        memberGenderComboBox->addItem(QString());
        memberGenderComboBox->addItem(QString());
        memberGenderComboBox->setObjectName("memberGenderComboBox");

        memberFormLayout->addWidget(memberGenderComboBox, 3, 1, 1, 1);

        memberMonthlyFeeLabel = new QLabel(memberFormFrame);
        memberMonthlyFeeLabel->setObjectName("memberMonthlyFeeLabel");
        memberMonthlyFeeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberMonthlyFeeLabel, 3, 2, 1, 1);

        memberMonthlyFeeLineEdit = new QLineEdit(memberFormFrame);
        memberMonthlyFeeLineEdit->setObjectName("memberMonthlyFeeLineEdit");

        memberFormLayout->addWidget(memberMonthlyFeeLineEdit, 3, 3, 1, 1);

        memberAgeLabel = new QLabel(memberFormFrame);
        memberAgeLabel->setObjectName("memberAgeLabel");
        memberAgeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberAgeLabel, 4, 0, 1, 1);

        memberAgeSpinBox = new QSpinBox(memberFormFrame);
        memberAgeSpinBox->setObjectName("memberAgeSpinBox");
        memberAgeSpinBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        memberAgeSpinBox->setMinimum(18);
        memberAgeSpinBox->setMaximum(65);
        memberAgeSpinBox->setValue(25);

        memberFormLayout->addWidget(memberAgeSpinBox, 4, 1, 1, 1);

        memberStatusLabel = new QLabel(memberFormFrame);
        memberStatusLabel->setObjectName("memberStatusLabel");
        memberStatusLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberStatusLabel, 4, 2, 1, 1);

        memberStatusComboBox = new QComboBox(memberFormFrame);
        memberStatusComboBox->addItem(QString());
        memberStatusComboBox->addItem(QString());
        memberStatusComboBox->addItem(QString());
        memberStatusComboBox->addItem(QString());
        memberStatusComboBox->setObjectName("memberStatusComboBox");

        memberFormLayout->addWidget(memberStatusComboBox, 4, 3, 1, 1);

        memberEmailLabel = new QLabel(memberFormFrame);
        memberEmailLabel->setObjectName("memberEmailLabel");
        memberEmailLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberEmailLabel, 5, 0, 1, 1);

        memberEmailLineEdit = new QLineEdit(memberFormFrame);
        memberEmailLineEdit->setObjectName("memberEmailLineEdit");

        memberFormLayout->addWidget(memberEmailLineEdit, 5, 1, 1, 3);

        memberPhoneLabel = new QLabel(memberFormFrame);
        memberPhoneLabel->setObjectName("memberPhoneLabel");
        memberPhoneLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberPhoneLabel, 6, 0, 1, 1);

        memberPhoneLineEdit = new QLineEdit(memberFormFrame);
        memberPhoneLineEdit->setObjectName("memberPhoneLineEdit");

        memberFormLayout->addWidget(memberPhoneLineEdit, 6, 1, 1, 3);

        memberPhotoFrame = new QFrame(memberFormFrame);
        memberPhotoFrame->setObjectName("memberPhotoFrame");
        memberPhotoFrame->setStyleSheet(QString::fromUtf8("border: 2px dashed #16a5b3; border-radius: 8px; background-color: #f8f9fa;"));
        memberPhotoLayout = new QVBoxLayout(memberPhotoFrame);
        memberPhotoLayout->setObjectName("memberPhotoLayout");
        memberPhotoLabel = new QLabel(memberPhotoFrame);
        memberPhotoLabel->setObjectName("memberPhotoLabel");
        memberPhotoLabel->setStyleSheet(QString::fromUtf8("color: #16a5b3; font-weight: 600; padding: 20px;"));
        memberPhotoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        memberPhotoLayout->addWidget(memberPhotoLabel);

        memberUploadPhotoButton = new QPushButton(memberPhotoFrame);
        memberUploadPhotoButton->setObjectName("memberUploadPhotoButton");

        memberPhotoLayout->addWidget(memberUploadPhotoButton);


        memberFormLayout->addWidget(memberPhotoFrame, 7, 0, 1, 2);

        memberNotesFrame = new QFrame(memberFormFrame);
        memberNotesFrame->setObjectName("memberNotesFrame");
        memberNotesLayout = new QVBoxLayout(memberNotesFrame);
        memberNotesLayout->setObjectName("memberNotesLayout");
        memberNotesLabel = new QLabel(memberNotesFrame);
        memberNotesLabel->setObjectName("memberNotesLabel");
        memberNotesLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberNotesLayout->addWidget(memberNotesLabel);

        memberNotesTextEdit = new QTextEdit(memberNotesFrame);
        memberNotesTextEdit->setObjectName("memberNotesTextEdit");
        memberNotesTextEdit->setMaximumSize(QSize(16777215, 100));
        memberNotesTextEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        memberNotesLayout->addWidget(memberNotesTextEdit);


        memberFormLayout->addWidget(memberNotesFrame, 7, 2, 1, 2);

        memberButtonFrame = new QFrame(memberFormFrame);
        memberButtonFrame->setObjectName("memberButtonFrame");
        memberButtonLayout = new QHBoxLayout(memberButtonFrame);
        memberButtonLayout->setObjectName("memberButtonLayout");
        buttonSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        memberButtonLayout->addItem(buttonSpacer_2);

        memberConfirmAddButton = new QPushButton(memberButtonFrame);
        memberConfirmAddButton->setObjectName("memberConfirmAddButton");
        memberConfirmAddButton->setMinimumSize(QSize(150, 45));

        memberButtonLayout->addWidget(memberConfirmAddButton);

        memberConfirmUpdateButton = new QPushButton(memberButtonFrame);
        memberConfirmUpdateButton->setObjectName("memberConfirmUpdateButton");
        memberConfirmUpdateButton->setMinimumSize(QSize(150, 45));
        memberConfirmUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));

        memberButtonLayout->addWidget(memberConfirmUpdateButton);


        memberFormLayout->addWidget(memberButtonFrame, 8, 0, 1, 4);


        memberFormMainLayout->addWidget(memberFormFrame);

        memberScrollArea->setWidget(memberScrollAreaContents);

        memberAddTabLayout->addWidget(memberScrollArea);

        memberTabWidget->addTab(memberAddTab, QString());
        memberStatisticsTab = new QWidget();
        memberStatisticsTab->setObjectName("memberStatisticsTab");
        memberStatisticsLayout = new QVBoxLayout(memberStatisticsTab);
        memberStatisticsLayout->setObjectName("memberStatisticsLayout");
        memberStatsFrame = new QFrame(memberStatisticsTab);
        memberStatsFrame->setObjectName("memberStatsFrame");
        memberStatsGridLayout = new QGridLayout(memberStatsFrame);
        memberStatsGridLayout->setObjectName("memberStatsGridLayout");
        totalMembersCard = new QFrame(memberStatsFrame);
        totalMembersCard->setObjectName("totalMembersCard");
        totalMembersCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        totalMembersLayout = new QVBoxLayout(totalMembersCard);
        totalMembersLayout->setObjectName("totalMembersLayout");
        totalMembersTitle = new QLabel(totalMembersCard);
        totalMembersTitle->setObjectName("totalMembersTitle");
        totalMembersTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        totalMembersLayout->addWidget(totalMembersTitle);

        totalMembersNumber = new QLabel(totalMembersCard);
        totalMembersNumber->setObjectName("totalMembersNumber");
        totalMembersNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #16a5b3;"));

        totalMembersLayout->addWidget(totalMembersNumber);


        memberStatsGridLayout->addWidget(totalMembersCard, 0, 0, 1, 1);

        activeMembersCard = new QFrame(memberStatsFrame);
        activeMembersCard->setObjectName("activeMembersCard");
        activeMembersCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        activeMembersLayout = new QVBoxLayout(activeMembersCard);
        activeMembersLayout->setObjectName("activeMembersLayout");
        activeMembersTitle = new QLabel(activeMembersCard);
        activeMembersTitle->setObjectName("activeMembersTitle");
        activeMembersTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        activeMembersLayout->addWidget(activeMembersTitle);

        activeMembersNumber = new QLabel(activeMembersCard);
        activeMembersNumber->setObjectName("activeMembersNumber");
        activeMembersNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #3498db;"));

        activeMembersLayout->addWidget(activeMembersNumber);


        memberStatsGridLayout->addWidget(activeMembersCard, 0, 1, 1, 1);

        newMembersCard = new QFrame(memberStatsFrame);
        newMembersCard->setObjectName("newMembersCard");
        newMembersCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        newMembersLayout = new QVBoxLayout(newMembersCard);
        newMembersLayout->setObjectName("newMembersLayout");
        newMembersTitle = new QLabel(newMembersCard);
        newMembersTitle->setObjectName("newMembersTitle");
        newMembersTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        newMembersLayout->addWidget(newMembersTitle);

        newMembersNumber = new QLabel(newMembersCard);
        newMembersNumber->setObjectName("newMembersNumber");
        newMembersNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #e67e22;"));

        newMembersLayout->addWidget(newMembersNumber);


        memberStatsGridLayout->addWidget(newMembersCard, 0, 2, 1, 1);

        membershipStatsFrame = new QFrame(memberStatsFrame);
        membershipStatsFrame->setObjectName("membershipStatsFrame");
        membershipStatsFrame->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px;"));
        membershipStatsLayout = new QVBoxLayout(membershipStatsFrame);
        membershipStatsLayout->setObjectName("membershipStatsLayout");
        membershipStatsTitle = new QLabel(membershipStatsFrame);
        membershipStatsTitle->setObjectName("membershipStatsTitle");
        membershipStatsTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;"));

        membershipStatsLayout->addWidget(membershipStatsTitle);

        membershipStatsTable = new QTableWidget(membershipStatsFrame);
        if (membershipStatsTable->columnCount() < 3)
            membershipStatsTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        membershipStatsTable->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        membershipStatsTable->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        membershipStatsTable->setHorizontalHeaderItem(2, __qtablewidgetitem19);
        membershipStatsTable->setObjectName("membershipStatsTable");
        membershipStatsTable->setAlternatingRowColors(true);

        membershipStatsLayout->addWidget(membershipStatsTable);


        memberStatsGridLayout->addWidget(membershipStatsFrame, 1, 0, 1, 3);


        memberStatisticsLayout->addWidget(memberStatsFrame);

        memberTabWidget->addTab(memberStatisticsTab, QString());

        verticalLayout->addWidget(memberTabWidget);

        stackedWidget->addWidget(membersPage);
        equipmentPage = new QWidget();
        equipmentPage->setObjectName("equipmentPage");
        equipmentPageLayout = new QVBoxLayout(equipmentPage);
        equipmentPageLayout->setObjectName("equipmentPageLayout");
        equipmentLabel = new QLabel(equipmentPage);
        equipmentLabel->setObjectName("equipmentLabel");
        equipmentLabel->setStyleSheet(QString::fromUtf8("font-size: 24px; color: #7f8c8d;"));
        equipmentLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        equipmentPageLayout->addWidget(equipmentLabel);

        stackedWidget->addWidget(equipmentPage);
        activitiesPage = new QWidget();
        activitiesPage->setObjectName("activitiesPage");
        activitiesPageLayout = new QVBoxLayout(activitiesPage);
        activitiesPageLayout->setObjectName("activitiesPageLayout");
        activityPageTitle = new QLabel(activitiesPage);
        activityPageTitle->setObjectName("activityPageTitle");
        activityPageTitle->setStyleSheet(QString::fromUtf8("font-size: 28px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;"));

        activitiesPageLayout->addWidget(activityPageTitle);

        activityTabWidget = new QTabWidget(activitiesPage);
        activityTabWidget->setObjectName("activityTabWidget");
        activityListTab = new QWidget();
        activityListTab->setObjectName("activityListTab");
        activityListTabLayout = new QVBoxLayout(activityListTab);
        activityListTabLayout->setObjectName("activityListTabLayout");
        activitySearchFrame = new QFrame(activityListTab);
        activitySearchFrame->setObjectName("activitySearchFrame");
        activitySearchLayout = new QHBoxLayout(activitySearchFrame);
        activitySearchLayout->setObjectName("activitySearchLayout");
        activitySearchLineEdit = new QLineEdit(activitySearchFrame);
        activitySearchLineEdit->setObjectName("activitySearchLineEdit");

        activitySearchLayout->addWidget(activitySearchLineEdit);

        activitySearchButton = new QPushButton(activitySearchFrame);
        activitySearchButton->setObjectName("activitySearchButton");

        activitySearchLayout->addWidget(activitySearchButton);


        activityListTabLayout->addWidget(activitySearchFrame);

        activityTable = new QTableWidget(activityListTab);
        if (activityTable->columnCount() < 8)
            activityTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(3, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(4, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(5, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(6, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(7, __qtablewidgetitem27);
        activityTable->setObjectName("activityTable");
        activityTable->setAlternatingRowColors(true);
        activityTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        activityListTabLayout->addWidget(activityTable);

        activityTabWidget->addTab(activityListTab, QString());
        activityAddTab = new QWidget();
        activityAddTab->setObjectName("activityAddTab");
        activityAddTabLayout = new QVBoxLayout(activityAddTab);
        activityAddTabLayout->setObjectName("activityAddTabLayout");
        activityScrollArea = new QScrollArea(activityAddTab);
        activityScrollArea->setObjectName("activityScrollArea");
        activityScrollArea->setWidgetResizable(true);
        activityScrollAreaContents = new QWidget();
        activityScrollAreaContents->setObjectName("activityScrollAreaContents");
        activityScrollAreaContents->setGeometry(QRect(0, 0, 631, 429));
        activityFormMainLayout = new QVBoxLayout(activityScrollAreaContents);
        activityFormMainLayout->setObjectName("activityFormMainLayout");
        activityFormFrame = new QFrame(activityScrollAreaContents);
        activityFormFrame->setObjectName("activityFormFrame");
        activityFormLayout = new QGridLayout(activityFormFrame);
        activityFormLayout->setObjectName("activityFormLayout");
        activityFormLayout->setHorizontalSpacing(20);
        activityFormLayout->setVerticalSpacing(15);
        responsibleLineEdit = new QLineEdit(activityFormFrame);
        responsibleLineEdit->setObjectName("responsibleLineEdit");

        activityFormLayout->addWidget(responsibleLineEdit, 2, 1, 1, 2);

        activityStatusComboBox = new QComboBox(activityFormFrame);
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->setObjectName("activityStatusComboBox");

        activityFormLayout->addWidget(activityStatusComboBox, 2, 4, 1, 1);

        responsibleLabel = new QLabel(activityFormFrame);
        responsibleLabel->setObjectName("responsibleLabel");
        responsibleLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(responsibleLabel, 2, 0, 1, 1);

        eventDateLabel = new QLabel(activityFormFrame);
        eventDateLabel->setObjectName("eventDateLabel");
        eventDateLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(eventDateLabel, 1, 0, 1, 1);

        eventDateEdit = new QDateEdit(activityFormFrame);
        eventDateEdit->setObjectName("eventDateEdit");
        eventDateEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        eventDateEdit->setCalendarPopup(true);

        activityFormLayout->addWidget(eventDateEdit, 1, 1, 1, 1);

        eventTimeEdit = new QTimeEdit(activityFormFrame);
        eventTimeEdit->setObjectName("eventTimeEdit");
        eventTimeEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        activityFormLayout->addWidget(eventTimeEdit, 1, 4, 1, 1);

        eventTimeLabel = new QLabel(activityFormFrame);
        eventTimeLabel->setObjectName("eventTimeLabel");
        eventTimeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(eventTimeLabel, 1, 2, 1, 1);

        activityIdLineEdit = new QLineEdit(activityFormFrame);
        activityIdLineEdit->setObjectName("activityIdLineEdit");

        activityFormLayout->addWidget(activityIdLineEdit, 0, 1, 1, 1);

        activityIdLabel = new QLabel(activityFormFrame);
        activityIdLabel->setObjectName("activityIdLabel");
        activityIdLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityIdLabel, 0, 0, 1, 1);

        activityTypeLabel = new QLabel(activityFormFrame);
        activityTypeLabel->setObjectName("activityTypeLabel");
        activityTypeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityTypeLabel, 0, 2, 1, 1);

        activityButtonFrame = new QFrame(activityFormFrame);
        activityButtonFrame->setObjectName("activityButtonFrame");
        activityButtonLayout = new QHBoxLayout(activityButtonFrame);
        activityButtonLayout->setObjectName("activityButtonLayout");
        activityButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        activityButtonLayout->addItem(activityButtonSpacer);

        activityConfirmButton = new QPushButton(activityButtonFrame);
        activityConfirmButton->setObjectName("activityConfirmButton");
        activityConfirmButton->setMinimumSize(QSize(150, 45));

        activityButtonLayout->addWidget(activityConfirmButton);

        activityUpdateButton = new QPushButton(activityButtonFrame);
        activityUpdateButton->setObjectName("activityUpdateButton");
        activityUpdateButton->setMinimumSize(QSize(150, 45));
        activityUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));

        activityButtonLayout->addWidget(activityUpdateButton);


        activityFormLayout->addWidget(activityButtonFrame, 4, 0, 1, 5);

        activityTypeComboBox = new QComboBox(activityFormFrame);
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->setObjectName("activityTypeComboBox");

        activityFormLayout->addWidget(activityTypeComboBox, 0, 4, 1, 1);

        activityDescriptionFrame = new QFrame(activityFormFrame);
        activityDescriptionFrame->setObjectName("activityDescriptionFrame");
        activityDescriptionLayout = new QVBoxLayout(activityDescriptionFrame);
        activityDescriptionLayout->setObjectName("activityDescriptionLayout");
        activityDescriptionTextEdit = new QTextEdit(activityDescriptionFrame);
        activityDescriptionTextEdit->setObjectName("activityDescriptionTextEdit");
        activityDescriptionTextEdit->setMaximumSize(QSize(16777215, 100));
        activityDescriptionTextEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        activityDescriptionLayout->addWidget(activityDescriptionTextEdit);


        activityFormLayout->addWidget(activityDescriptionFrame, 3, 1, 1, 4);

        activityStatusLabel = new QLabel(activityFormFrame);
        activityStatusLabel->setObjectName("activityStatusLabel");
        activityStatusLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityStatusLabel, 2, 3, 1, 1);

        activityDescriptionLabel = new QLabel(activityFormFrame);
        activityDescriptionLabel->setObjectName("activityDescriptionLabel");
        activityDescriptionLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityDescriptionLabel, 3, 0, 1, 1);


        activityFormMainLayout->addWidget(activityFormFrame);

        activityScrollArea->setWidget(activityScrollAreaContents);

        activityAddTabLayout->addWidget(activityScrollArea);

        activityTabWidget->addTab(activityAddTab, QString());
        activityStatisticsTab = new QWidget();
        activityStatisticsTab->setObjectName("activityStatisticsTab");
        activityStatisticsLayout = new QVBoxLayout(activityStatisticsTab);
        activityStatisticsLayout->setObjectName("activityStatisticsLayout");
        activityStatsFrame = new QFrame(activityStatisticsTab);
        activityStatsFrame->setObjectName("activityStatsFrame");
        activityStatsGridLayout = new QGridLayout(activityStatsFrame);
        activityStatsGridLayout->setObjectName("activityStatsGridLayout");
        totalActivitiesCard = new QFrame(activityStatsFrame);
        totalActivitiesCard->setObjectName("totalActivitiesCard");
        totalActivitiesCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        totalActivitiesLayout = new QVBoxLayout(totalActivitiesCard);
        totalActivitiesLayout->setObjectName("totalActivitiesLayout");
        totalActivitiesTitle = new QLabel(totalActivitiesCard);
        totalActivitiesTitle->setObjectName("totalActivitiesTitle");
        totalActivitiesTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        totalActivitiesLayout->addWidget(totalActivitiesTitle);

        totalActivitiesNumber = new QLabel(totalActivitiesCard);
        totalActivitiesNumber->setObjectName("totalActivitiesNumber");
        totalActivitiesNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #16a5b3;"));

        totalActivitiesLayout->addWidget(totalActivitiesNumber);


        activityStatsGridLayout->addWidget(totalActivitiesCard, 0, 0, 1, 1);

        upcomingActivitiesCard = new QFrame(activityStatsFrame);
        upcomingActivitiesCard->setObjectName("upcomingActivitiesCard");
        upcomingActivitiesCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        upcomingActivitiesLayout = new QVBoxLayout(upcomingActivitiesCard);
        upcomingActivitiesLayout->setObjectName("upcomingActivitiesLayout");
        upcomingActivitiesTitle = new QLabel(upcomingActivitiesCard);
        upcomingActivitiesTitle->setObjectName("upcomingActivitiesTitle");
        upcomingActivitiesTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        upcomingActivitiesLayout->addWidget(upcomingActivitiesTitle);

        upcomingActivitiesNumber = new QLabel(upcomingActivitiesCard);
        upcomingActivitiesNumber->setObjectName("upcomingActivitiesNumber");
        upcomingActivitiesNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #e67e22;"));

        upcomingActivitiesLayout->addWidget(upcomingActivitiesNumber);


        activityStatsGridLayout->addWidget(upcomingActivitiesCard, 0, 1, 1, 1);

        activeActivitiesCard = new QFrame(activityStatsFrame);
        activeActivitiesCard->setObjectName("activeActivitiesCard");
        activeActivitiesCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        activeActivitiesLayout = new QVBoxLayout(activeActivitiesCard);
        activeActivitiesLayout->setObjectName("activeActivitiesLayout");
        activeActivitiesTitle = new QLabel(activeActivitiesCard);
        activeActivitiesTitle->setObjectName("activeActivitiesTitle");
        activeActivitiesTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        activeActivitiesLayout->addWidget(activeActivitiesTitle);

        activeActivitiesNumber = new QLabel(activeActivitiesCard);
        activeActivitiesNumber->setObjectName("activeActivitiesNumber");
        activeActivitiesNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #27ae60;"));

        activeActivitiesLayout->addWidget(activeActivitiesNumber);


        activityStatsGridLayout->addWidget(activeActivitiesCard, 0, 2, 1, 1);

        activityTypeStatsFrame = new QFrame(activityStatsFrame);
        activityTypeStatsFrame->setObjectName("activityTypeStatsFrame");
        activityTypeStatsFrame->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px;"));
        activityTypeStatsLayout = new QVBoxLayout(activityTypeStatsFrame);
        activityTypeStatsLayout->setObjectName("activityTypeStatsLayout");
        activityTypeStatsTitle = new QLabel(activityTypeStatsFrame);
        activityTypeStatsTitle->setObjectName("activityTypeStatsTitle");
        activityTypeStatsTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;"));

        activityTypeStatsLayout->addWidget(activityTypeStatsTitle);

        activityTypeStatsTable = new QTableWidget(activityTypeStatsFrame);
        if (activityTypeStatsTable->columnCount() < 4)
            activityTypeStatsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        activityTypeStatsTable->setHorizontalHeaderItem(0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        activityTypeStatsTable->setHorizontalHeaderItem(1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        activityTypeStatsTable->setHorizontalHeaderItem(2, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        activityTypeStatsTable->setHorizontalHeaderItem(3, __qtablewidgetitem31);
        activityTypeStatsTable->setObjectName("activityTypeStatsTable");
        activityTypeStatsTable->setAlternatingRowColors(true);

        activityTypeStatsLayout->addWidget(activityTypeStatsTable);


        activityStatsGridLayout->addWidget(activityTypeStatsFrame, 1, 0, 1, 3);


        activityStatisticsLayout->addWidget(activityStatsFrame);

        activityTabWidget->addTab(activityStatisticsTab, QString());

        activitiesPageLayout->addWidget(activityTabWidget);

        stackedWidget->addWidget(activitiesPage);
        paymentsPage = new QWidget();
        paymentsPage->setObjectName("paymentsPage");
        paymentsPageLayout = new QVBoxLayout(paymentsPage);
        paymentsPageLayout->setObjectName("paymentsPageLayout");
        paymentsLabel = new QLabel(paymentsPage);
        paymentsLabel->setObjectName("paymentsLabel");
        paymentsLabel->setStyleSheet(QString::fromUtf8("font-size: 24px; color: #7f8c8d;"));
        paymentsLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        paymentsPageLayout->addWidget(paymentsLabel);

        stackedWidget->addWidget(paymentsPage);

        mainContentLayout->addWidget(stackedWidget);


        mainHorizontalLayout->addWidget(mainContentFrame);


        verticalLayout_main->addWidget(mainFrame);

        EmployerAdmin->setCentralWidget(centralwidget);

        retranslateUi(EmployerAdmin);

        stackedWidget->setCurrentIndex(1);
        employeeTabWidget->setCurrentIndex(2);
        memberTabWidget->setCurrentIndex(0);
        activityTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(EmployerAdmin);
    } // setupUi

    void retranslateUi(QMainWindow *EmployerAdmin)
    {
        EmployerAdmin->setWindowTitle(QCoreApplication::translate("EmployerAdmin", "\360\237\220\273\342\200\215\342\235\204\357\270\217VIBRA CLUB- Application Management", nullptr));
        logoLabel->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\220\273\342\200\215\342\235\204\357\270\217VIBRA CLUB", nullptr));
        userAvatarLabel->setText(QCoreApplication::translate("EmployerAdmin", "KC", nullptr));
        userNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "Khalil Cherif", nullptr));
        userRoleLabel->setText(QCoreApplication::translate("EmployerAdmin", "Employee Manager", nullptr));
        employeesButton->setText(QCoreApplication::translate("EmployerAdmin", "  Employees", nullptr));
        membersButton->setText(QCoreApplication::translate("EmployerAdmin", "  Members", nullptr));
        equipmentButton->setText(QCoreApplication::translate("EmployerAdmin", "  Equipment", nullptr));
        activitiesButton->setText(QCoreApplication::translate("EmployerAdmin", "  Activities", nullptr));
        paymentsButton->setText(QCoreApplication::translate("EmployerAdmin", "  Payments", nullptr));
        pageTitle->setText(QCoreApplication::translate("EmployerAdmin", "Employee Management", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Search employees...", nullptr));
        employeeSearchButton->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\224\215 Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = employeeTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EmployerAdmin", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = employeeTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EmployerAdmin", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = employeeTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EmployerAdmin", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = employeeTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EmployerAdmin", "Department", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = employeeTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EmployerAdmin", "Hire Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = employeeTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("EmployerAdmin", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = employeeTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("EmployerAdmin", "Actions", nullptr));
        employeeTabWidget->setTabText(employeeTabWidget->indexOf(listTab), QCoreApplication::translate("EmployerAdmin", " List of Employees", nullptr));
        empIdLabel->setText(QCoreApplication::translate("EmployerAdmin", "Employee ID:", nullptr));
        empIdLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "e.g., EMP001", nullptr));
        passwordLabel->setText(QCoreApplication::translate("EmployerAdmin", "Password", nullptr));
        passwordLineEedit->setText(QCoreApplication::translate("EmployerAdmin", "Enter password  ", nullptr));
        passwordLineEedit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter salary amount", nullptr));
        firstNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "First Name:", nullptr));
        firstNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter first name", nullptr));
        hireDateLabel->setText(QCoreApplication::translate("EmployerAdmin", "Hire Date:", nullptr));
        lastNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "Last Name:", nullptr));
        lastNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter last name", nullptr));
        positionLabel->setText(QCoreApplication::translate("EmployerAdmin", "Position:", nullptr));
        positionLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "e.g., Manager, Instructor, etc.", nullptr));
        genderLabel->setText(QCoreApplication::translate("EmployerAdmin", "Gender:", nullptr));
        genderComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Male", nullptr));
        genderComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Female", nullptr));
        genderComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Other", nullptr));

        salaryLabel->setText(QCoreApplication::translate("EmployerAdmin", "Salary:", nullptr));
        salaryLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter salary amount", nullptr));
        ageLabel->setText(QCoreApplication::translate("EmployerAdmin", "Age:", nullptr));
        statusLabel->setText(QCoreApplication::translate("EmployerAdmin", "Status:", nullptr));
        statusComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Active", nullptr));
        statusComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Inactive", nullptr));
        statusComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "On Leave", nullptr));

        emailLabel->setText(QCoreApplication::translate("EmployerAdmin", "Email:", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "employee@esprit.tn", nullptr));
        departmentLabel->setText(QCoreApplication::translate("EmployerAdmin", "Department:", nullptr));
        phoneLabel->setText(QCoreApplication::translate("EmployerAdmin", "Phone Number:", nullptr));
        phoneLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "+216 55 123 456", nullptr));
        photoLabel->setText(QCoreApplication::translate("EmployerAdmin", " Upload Employee Photo", nullptr));
        employeeUploadPhotoButton->setText(QCoreApplication::translate("EmployerAdmin", "Choose File", nullptr));
        notesLabel->setText(QCoreApplication::translate("EmployerAdmin", " Progress Report / Notes:", nullptr));
        notesTextEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Add any notes or progress reports...", nullptr));
        confirmAddButton->setText(QCoreApplication::translate("EmployerAdmin", "\342\234\223 Confirm Add", nullptr));
        confirmUpdateButton->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\235 Confirm Update", nullptr));
        departmentComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Activity Management", nullptr));
        departmentComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Member Management", nullptr));
        departmentComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Equipment Management", nullptr));
        departmentComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Payment Management", nullptr));
        departmentComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "General Administration", nullptr));

        employeeTabWidget->setTabText(employeeTabWidget->indexOf(addTab), QCoreApplication::translate("EmployerAdmin", " Add Employee", nullptr));
        totalEmpTitle->setText(QCoreApplication::translate("EmployerAdmin", "Total Employees", nullptr));
        totalEmpNumber->setText(QCoreApplication::translate("EmployerAdmin", "47", nullptr));
        activeEmpTitle->setText(QCoreApplication::translate("EmployerAdmin", "Active Employees", nullptr));
        activeEmpNumber->setText(QCoreApplication::translate("EmployerAdmin", "42", nullptr));
        newHiresTitle->setText(QCoreApplication::translate("EmployerAdmin", "New Hires (This Month)", nullptr));
        newHiresNumber->setText(QCoreApplication::translate("EmployerAdmin", "8", nullptr));
        deptStatsTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\210 Department Distribution", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = departmentStatsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("EmployerAdmin", "Department", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = departmentStatsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("EmployerAdmin", "Employee Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = departmentStatsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("EmployerAdmin", "Percentage", nullptr));
        employeeTabWidget->setTabText(employeeTabWidget->indexOf(statisticsTab), QCoreApplication::translate("EmployerAdmin", " Statistics", nullptr));
        memberPageTitle->setText(QCoreApplication::translate("EmployerAdmin", "Member Management", nullptr));
        memberSearchLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Search members...", nullptr));
        memberSearchButton->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\224\215 Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = memberTable->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("EmployerAdmin", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = memberTable->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("EmployerAdmin", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = memberTable->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("EmployerAdmin", "Membership Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = memberTable->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("EmployerAdmin", "Plan", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = memberTable->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("EmployerAdmin", "Join Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = memberTable->horizontalHeaderItem(5);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("EmployerAdmin", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = memberTable->horizontalHeaderItem(6);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("EmployerAdmin", "Actions", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberListTab), QCoreApplication::translate("EmployerAdmin", " List of Members", nullptr));
        memberIdLabel->setText(QCoreApplication::translate("EmployerAdmin", "Member ID:", nullptr));
        memberIdLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "e.g., MEM001", nullptr));
        membershipTypeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Membership Type:", nullptr));
        membershipTypeComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Basic", nullptr));
        membershipTypeComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Premium", nullptr));
        membershipTypeComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "VIP", nullptr));
        membershipTypeComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Student", nullptr));
        membershipTypeComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Senior", nullptr));

        memberFirstNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "First Name:", nullptr));
        memberFirstNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter first name", nullptr));
        memberJoinDateLabel->setText(QCoreApplication::translate("EmployerAdmin", "Join Date:", nullptr));
        memberLastNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "Last Name:", nullptr));
        memberLastNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter last name", nullptr));
        membershipPlanLabel->setText(QCoreApplication::translate("EmployerAdmin", "Membership Plan:", nullptr));
        membershipPlanLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "e.g., Basic, Premium, VIP, etc.", nullptr));
        memberGenderLabel->setText(QCoreApplication::translate("EmployerAdmin", "Gender:", nullptr));
        memberGenderComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Male", nullptr));
        memberGenderComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Female", nullptr));
        memberGenderComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Other", nullptr));

        memberMonthlyFeeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Monthly Fee:", nullptr));
        memberMonthlyFeeLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter monthly fee amount", nullptr));
        memberAgeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Age:", nullptr));
        memberStatusLabel->setText(QCoreApplication::translate("EmployerAdmin", "Status:", nullptr));
        memberStatusComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Active", nullptr));
        memberStatusComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Inactive", nullptr));
        memberStatusComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Suspended", nullptr));
        memberStatusComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Expired", nullptr));

        memberEmailLabel->setText(QCoreApplication::translate("EmployerAdmin", "Email:", nullptr));
        memberEmailLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "member@example.com", nullptr));
        memberPhoneLabel->setText(QCoreApplication::translate("EmployerAdmin", "Phone Number:", nullptr));
        memberPhoneLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "+216 55 123 456", nullptr));
        memberPhotoLabel->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\267 Upload Member Photo", nullptr));
        memberUploadPhotoButton->setText(QCoreApplication::translate("EmployerAdmin", "Choose File", nullptr));
        memberNotesLabel->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\235 Member Notes / Comments:", nullptr));
        memberNotesTextEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Add any notes or comments about the member...", nullptr));
        memberConfirmAddButton->setText(QCoreApplication::translate("EmployerAdmin", "\342\234\223 Confirm Add", nullptr));
        memberConfirmUpdateButton->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\235 Confirm Update", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberAddTab), QCoreApplication::translate("EmployerAdmin", " Add Member", nullptr));
        totalMembersTitle->setText(QCoreApplication::translate("EmployerAdmin", "Total Members", nullptr));
        totalMembersNumber->setText(QCoreApplication::translate("EmployerAdmin", "47", nullptr));
        activeMembersTitle->setText(QCoreApplication::translate("EmployerAdmin", "Active Members", nullptr));
        activeMembersNumber->setText(QCoreApplication::translate("EmployerAdmin", "42", nullptr));
        newMembersTitle->setText(QCoreApplication::translate("EmployerAdmin", "New Members (This Month)", nullptr));
        newMembersNumber->setText(QCoreApplication::translate("EmployerAdmin", "8", nullptr));
        membershipStatsTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\210 Membership Distribution", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = membershipStatsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("EmployerAdmin", "Membership Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = membershipStatsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("EmployerAdmin", "Member Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = membershipStatsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("EmployerAdmin", "Percentage", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberStatisticsTab), QCoreApplication::translate("EmployerAdmin", " Statistics", nullptr));
        equipmentLabel->setText(QCoreApplication::translate("EmployerAdmin", "Equipment Management - Coming Soon", nullptr));
        activityPageTitle->setText(QCoreApplication::translate("EmployerAdmin", "Activity Management", nullptr));
        activitySearchLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Search activities...", nullptr));
        activitySearchButton->setText(QCoreApplication::translate("EmployerAdmin", " Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = activityTable->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("EmployerAdmin", "Activity ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = activityTable->horizontalHeaderItem(1);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("EmployerAdmin", "Activity Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = activityTable->horizontalHeaderItem(2);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("EmployerAdmin", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = activityTable->horizontalHeaderItem(3);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("EmployerAdmin", "Event Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = activityTable->horizontalHeaderItem(4);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("EmployerAdmin", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = activityTable->horizontalHeaderItem(5);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("EmployerAdmin", "Responsible", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = activityTable->horizontalHeaderItem(6);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("EmployerAdmin", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = activityTable->horizontalHeaderItem(7);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("EmployerAdmin", "Actions", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityListTab), QCoreApplication::translate("EmployerAdmin", " List of Activities", nullptr));
        responsibleLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter responsible person or instructor name", nullptr));
        activityStatusComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Scheduled", nullptr));
        activityStatusComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "In Progress", nullptr));
        activityStatusComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Completed", nullptr));
        activityStatusComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Cancelled", nullptr));
        activityStatusComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Postponed", nullptr));

        responsibleLabel->setText(QCoreApplication::translate("EmployerAdmin", "Responsible/Actor:", nullptr));
        eventDateLabel->setText(QCoreApplication::translate("EmployerAdmin", "Event Date:", nullptr));
        eventTimeEdit->setDisplayFormat(QCoreApplication::translate("EmployerAdmin", "HH:mm", nullptr));
        eventTimeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Event Time:", nullptr));
        activityIdLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "e.g., ACT001", nullptr));
        activityIdLabel->setText(QCoreApplication::translate("EmployerAdmin", "Activity ID:", nullptr));
        activityTypeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Activity Type:", nullptr));
        activityConfirmButton->setText(QCoreApplication::translate("EmployerAdmin", " Confirm Add Activity", nullptr));
        activityUpdateButton->setText(QCoreApplication::translate("EmployerAdmin", " Update Activity", nullptr));
        activityTypeComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Group Class", nullptr));
        activityTypeComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Personal Training", nullptr));
        activityTypeComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Workshop", nullptr));
        activityTypeComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Competition", nullptr));
        activityTypeComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Event", nullptr));
        activityTypeComboBox->setItemText(5, QCoreApplication::translate("EmployerAdmin", "Maintenance", nullptr));

        activityDescriptionTextEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter detailed activity description, requirements, or notes...", nullptr));
        activityStatusLabel->setText(QCoreApplication::translate("EmployerAdmin", "Status:", nullptr));
        activityDescriptionLabel->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\235 Activity Description:", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityAddTab), QCoreApplication::translate("EmployerAdmin", " Add Activity", nullptr));
        totalActivitiesTitle->setText(QCoreApplication::translate("EmployerAdmin", "Total Activities", nullptr));
        totalActivitiesNumber->setText(QCoreApplication::translate("EmployerAdmin", "127", nullptr));
        upcomingActivitiesTitle->setText(QCoreApplication::translate("EmployerAdmin", "Upcoming Activities", nullptr));
        upcomingActivitiesNumber->setText(QCoreApplication::translate("EmployerAdmin", "23", nullptr));
        activeActivitiesTitle->setText(QCoreApplication::translate("EmployerAdmin", "Active Today", nullptr));
        activeActivitiesNumber->setText(QCoreApplication::translate("EmployerAdmin", "8", nullptr));
        activityTypeStatsTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\210 Activity Type Distribution", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = activityTypeStatsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("EmployerAdmin", "Activity Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = activityTypeStatsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("EmployerAdmin", "Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = activityTypeStatsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("EmployerAdmin", "Percentage", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = activityTypeStatsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("EmployerAdmin", "This Month", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityStatisticsTab), QCoreApplication::translate("EmployerAdmin", " Statistics", nullptr));
        paymentsLabel->setText(QCoreApplication::translate("EmployerAdmin", "Payment Management - Coming Soon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmployerAdmin: public Ui_EmployerAdmin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYERADMIN_H
