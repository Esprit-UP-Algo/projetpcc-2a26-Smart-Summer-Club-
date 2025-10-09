/********************************************************************************
** Form generated from reading UI file 'membermanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBERMANAGEMENT_H
#define UI_MEMBERMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MemberManagement
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_main;
    QFrame *topBarFrame;
    QHBoxLayout *topBarLayout;
    QLabel *logo;
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
    QPushButton *membersButton;
    QSpacerItem *verticalSpacer_sidebar;
    QFrame *mainContentFrame;
    QVBoxLayout *mainContentLayout;
    QStackedWidget *stackedWidget;
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

    void setupUi(QMainWindow *MemberManagement)
    {
        if (MemberManagement->objectName().isEmpty())
            MemberManagement->setObjectName("MemberManagement");
        MemberManagement->resize(1200, 800);
        MemberManagement->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
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
"QPushButton#membersButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    padding: 15px 20px;"
                        "\n"
"    text-align: left;\n"
"    font-size: 14px;\n"
"    color: #2c3e50;\n"
"    border-radius: 8px;\n"
"    margin: 2px 10px;\n"
"}\n"
"\n"
"QPushButton#membersButton:hover {\n"
"    background-color: #e8f4f5;\n"
"}\n"
"\n"
"QPushButton#membersButton:checked {\n"
"    background-color: #16a5b3;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#membersButton:checked:hover {\n"
"    background-color: #139aa6;\n"
"}\n"
"\n"
"/* Main Content Styling */\n"
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
""
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
"    border-radius: 16px;\n"
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
"    border-color: #"
                        "16a5b3;\n"
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
"QComboBox:focus {\n"
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
""
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
"QPushButton#actionBut"
                        "ton:pressed {\n"
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
"QHeaderView::section {\n"
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
        centralwidget = new QWidget(MemberManagement);
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
        logo = new QLabel(topBarFrame);
        logo->setObjectName("logo");

        topBarLayout->addWidget(logo);

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
        membersButton = new QPushButton(navigationFrame);
        membersButton->setObjectName("membersButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/members.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        membersButton->setIcon(icon);
        membersButton->setCheckable(true);
        membersButton->setChecked(true);

        navigationLayout->addWidget(membersButton);


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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        memberSearchButton->setIcon(icon1);

        memberSearchLayout->addWidget(memberSearchButton);


        memberListTabLayout->addWidget(memberSearchFrame);

        memberTable = new QTableWidget(memberListTab);
        if (memberTable->columnCount() < 7)
            memberTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        memberTable->setObjectName("memberTable");
        memberTable->setAlternatingRowColors(true);
        memberTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        memberListTabLayout->addWidget(memberTable);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/list.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        memberTabWidget->addTab(memberListTab, icon2, QString());
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        memberUploadPhotoButton->setIcon(icon3);

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
        memberConfirmAddButton->setIcon(icon3);

        memberButtonLayout->addWidget(memberConfirmAddButton);

        memberConfirmUpdateButton = new QPushButton(memberButtonFrame);
        memberConfirmUpdateButton->setObjectName("memberConfirmUpdateButton");
        memberConfirmUpdateButton->setMinimumSize(QSize(150, 45));
        memberConfirmUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        memberConfirmUpdateButton->setIcon(icon4);

        memberButtonLayout->addWidget(memberConfirmUpdateButton);


        memberFormLayout->addWidget(memberButtonFrame, 8, 0, 1, 4);


        memberFormMainLayout->addWidget(memberFormFrame);

        memberScrollArea->setWidget(memberScrollAreaContents);

        memberAddTabLayout->addWidget(memberScrollArea);

        memberTabWidget->addTab(memberAddTab, icon3, QString());
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
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        membershipStatsTable->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        membershipStatsTable->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        membershipStatsTable->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        membershipStatsTable->setObjectName("membershipStatsTable");
        membershipStatsTable->setAlternatingRowColors(true);

        membershipStatsLayout->addWidget(membershipStatsTable);


        memberStatsGridLayout->addWidget(membershipStatsFrame, 1, 0, 1, 3);


        memberStatisticsLayout->addWidget(memberStatsFrame);

        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/statistic.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        memberTabWidget->addTab(memberStatisticsTab, icon5, QString());

        verticalLayout->addWidget(memberTabWidget);

        stackedWidget->addWidget(membersPage);

        mainContentLayout->addWidget(stackedWidget);


        mainHorizontalLayout->addWidget(mainContentFrame);


        verticalLayout_main->addWidget(mainFrame);

        MemberManagement->setCentralWidget(centralwidget);

        retranslateUi(MemberManagement);

        stackedWidget->setCurrentIndex(0);
        memberTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MemberManagement);
    } // setupUi

    void retranslateUi(QMainWindow *MemberManagement)
    {
        MemberManagement->setWindowTitle(QCoreApplication::translate("MemberManagement", "VIBRA CLUB - Application Management", nullptr));
        logo->setText(QCoreApplication::translate("MemberManagement", "TextLabel", nullptr));
        logoLabel->setText(QCoreApplication::translate("MemberManagement", "VIBRA CLUB", nullptr));
        userAvatarLabel->setText(QCoreApplication::translate("MemberManagement", "YH", nullptr));
        userNameLabel->setText(QCoreApplication::translate("MemberManagement", "Yasmine Hidri", nullptr));
        userRoleLabel->setText(QCoreApplication::translate("MemberManagement", "Member Manager", nullptr));
        membersButton->setText(QCoreApplication::translate("MemberManagement", "  Members", nullptr));
        memberPageTitle->setText(QCoreApplication::translate("MemberManagement", "Member Management", nullptr));
        memberSearchLineEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "Search members...", nullptr));
        memberSearchButton->setText(QCoreApplication::translate("MemberManagement", "Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = memberTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MemberManagement", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = memberTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MemberManagement", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = memberTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MemberManagement", "Membership Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = memberTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MemberManagement", "Plan", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = memberTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MemberManagement", "Join Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = memberTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MemberManagement", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = memberTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MemberManagement", "Actions", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberListTab), QCoreApplication::translate("MemberManagement", " List of Members", nullptr));
        memberIdLabel->setText(QCoreApplication::translate("MemberManagement", "Member ID:", nullptr));
        memberIdLineEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "e.g., MEM001", nullptr));
        membershipTypeLabel->setText(QCoreApplication::translate("MemberManagement", "Membership Type:", nullptr));
        membershipTypeComboBox->setItemText(0, QCoreApplication::translate("MemberManagement", "Basic", nullptr));
        membershipTypeComboBox->setItemText(1, QCoreApplication::translate("MemberManagement", "Premium", nullptr));
        membershipTypeComboBox->setItemText(2, QCoreApplication::translate("MemberManagement", "VIP", nullptr));
        membershipTypeComboBox->setItemText(3, QCoreApplication::translate("MemberManagement", "Student", nullptr));
        membershipTypeComboBox->setItemText(4, QCoreApplication::translate("MemberManagement", "Senior", nullptr));

        memberFirstNameLabel->setText(QCoreApplication::translate("MemberManagement", "First Name:", nullptr));
        memberFirstNameLineEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "Enter first name", nullptr));
        memberJoinDateLabel->setText(QCoreApplication::translate("MemberManagement", "Join Date:", nullptr));
        memberLastNameLabel->setText(QCoreApplication::translate("MemberManagement", "Last Name:", nullptr));
        memberLastNameLineEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "Enter last name", nullptr));
        membershipPlanLabel->setText(QCoreApplication::translate("MemberManagement", "Membership Plan:", nullptr));
        membershipPlanLineEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "e.g., Basic, Premium, VIP, etc.", nullptr));
        memberGenderLabel->setText(QCoreApplication::translate("MemberManagement", "Gender:", nullptr));
        memberGenderComboBox->setItemText(0, QCoreApplication::translate("MemberManagement", "Male", nullptr));
        memberGenderComboBox->setItemText(1, QCoreApplication::translate("MemberManagement", "Female", nullptr));
        memberGenderComboBox->setItemText(2, QCoreApplication::translate("MemberManagement", "Other", nullptr));

        memberMonthlyFeeLabel->setText(QCoreApplication::translate("MemberManagement", "Monthly Fee:", nullptr));
        memberMonthlyFeeLineEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "Enter monthly fee amount", nullptr));
        memberAgeLabel->setText(QCoreApplication::translate("MemberManagement", "Age:", nullptr));
        memberStatusLabel->setText(QCoreApplication::translate("MemberManagement", "Status:", nullptr));
        memberStatusComboBox->setItemText(0, QCoreApplication::translate("MemberManagement", "Active", nullptr));
        memberStatusComboBox->setItemText(1, QCoreApplication::translate("MemberManagement", "Inactive", nullptr));
        memberStatusComboBox->setItemText(2, QCoreApplication::translate("MemberManagement", "Suspended", nullptr));
        memberStatusComboBox->setItemText(3, QCoreApplication::translate("MemberManagement", "Expired", nullptr));

        memberEmailLabel->setText(QCoreApplication::translate("MemberManagement", "Email:", nullptr));
        memberEmailLineEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "member@example.com", nullptr));
        memberPhoneLabel->setText(QCoreApplication::translate("MemberManagement", "Phone Number:", nullptr));
        memberPhoneLineEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "+216 55 123 456", nullptr));
        memberPhotoLabel->setText(QCoreApplication::translate("MemberManagement", "Upload Member Photo", nullptr));
        memberUploadPhotoButton->setText(QCoreApplication::translate("MemberManagement", "Choose File", nullptr));
        memberNotesLabel->setText(QCoreApplication::translate("MemberManagement", "Member Notes / Comments:", nullptr));
        memberNotesTextEdit->setPlaceholderText(QCoreApplication::translate("MemberManagement", "Add any notes or comments about the member...", nullptr));
        memberConfirmAddButton->setText(QCoreApplication::translate("MemberManagement", "Confirm Add", nullptr));
        memberConfirmUpdateButton->setText(QCoreApplication::translate("MemberManagement", "Confirm Update", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberAddTab), QCoreApplication::translate("MemberManagement", " Add Member", nullptr));
        totalMembersTitle->setText(QCoreApplication::translate("MemberManagement", "Total Members", nullptr));
        totalMembersNumber->setText(QCoreApplication::translate("MemberManagement", "47", nullptr));
        activeMembersTitle->setText(QCoreApplication::translate("MemberManagement", "Active Members", nullptr));
        activeMembersNumber->setText(QCoreApplication::translate("MemberManagement", "42", nullptr));
        newMembersTitle->setText(QCoreApplication::translate("MemberManagement", "New Members (This Month)", nullptr));
        newMembersNumber->setText(QCoreApplication::translate("MemberManagement", "8", nullptr));
        membershipStatsTitle->setText(QCoreApplication::translate("MemberManagement", "\360\237\223\210 Membership Distribution", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = membershipStatsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MemberManagement", "Membership Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = membershipStatsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MemberManagement", "Member Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = membershipStatsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MemberManagement", "Percentage", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberStatisticsTab), QCoreApplication::translate("MemberManagement", " Statistics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MemberManagement: public Ui_MemberManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBERMANAGEMENT_H
