/********************************************************************************
** Form generated from reading UI file 'activitymanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIVITYMANAGEMENT_H
#define UI_ACTIVITYMANAGEMENT_H

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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ActivityManagement
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
    QFrame *mainContentFrame;
    QVBoxLayout *mainContentLayout;
    QStackedWidget *stackedWidget;
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

    void setupUi(QMainWindow *ActivityManagement)
    {
        if (ActivityManagement->objectName().isEmpty())
            ActivityManagement->setObjectName("ActivityManagement");
        ActivityManagement->resize(1200, 800);
        ActivityManagement->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
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
""
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
"/* Form Stylin"
                        "g */\n"
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
"QDateEdit, QSpinBox, QTimeEdit {\n"
"    padding: 14px 16px;\n"
"    border: 2px so"
                        "lid #e0e4e7;\n"
"    border-radius: 10px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02);\n"
"}\n"
"\n"
"QDateEdit:focus, QSpinBox:focus, QTimeEdit:focus {\n"
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
"QPushButton {\n"
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
""
                        "QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                               stop:0 #139aa6, stop:1 #0f858f);\n"
"    box-shadow: 0 6px 12px rgba(22, 165, 179, 0.3);\n"
"    transform: translateY(-1px);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
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
"/* Search Fram"
                        "e Styling */\n"
"QFrame[objectName*=\"SearchFrame\"], QFrame[objectName*=\"searchFrame\"] {\n"
"    background-color: rgba(22, 165, 179, 0.02);\n"
"    border: 1px solid rgba(22, 165, 179, 0.1);\n"
"    border-radius: 12px;\n"
"    padding: 8px;\n"
"}\n"
""));
        centralwidget = new QWidget(ActivityManagement);
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
        mainContentFrame = new QFrame(mainFrame);
        mainContentFrame->setObjectName("mainContentFrame");
        mainContentLayout = new QVBoxLayout(mainContentFrame);
        mainContentLayout->setObjectName("mainContentLayout");
        mainContentLayout->setContentsMargins(20, 20, 20, 20);
        stackedWidget = new QStackedWidget(mainContentFrame);
        stackedWidget->setObjectName("stackedWidget");
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
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        activitySearchButton->setIcon(icon);

        activitySearchLayout->addWidget(activitySearchButton);


        activityListTabLayout->addWidget(activitySearchFrame);

        activityTable = new QTableWidget(activityListTab);
        if (activityTable->columnCount() < 8)
            activityTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        activityTable->setObjectName("activityTable");
        activityTable->setAlternatingRowColors(true);
        activityTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        activityListTabLayout->addWidget(activityTable);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/list.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        activityTabWidget->addTab(activityListTab, icon1, QString());
        activityAddTab = new QWidget();
        activityAddTab->setObjectName("activityAddTab");
        activityAddTabLayout = new QVBoxLayout(activityAddTab);
        activityAddTabLayout->setObjectName("activityAddTabLayout");
        activityScrollArea = new QScrollArea(activityAddTab);
        activityScrollArea->setObjectName("activityScrollArea");
        activityScrollArea->setWidgetResizable(true);
        activityScrollAreaContents = new QWidget();
        activityScrollAreaContents->setObjectName("activityScrollAreaContents");
        activityScrollAreaContents->setGeometry(QRect(0, 0, 870, 546));
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        activityConfirmButton->setIcon(icon2);

        activityButtonLayout->addWidget(activityConfirmButton);

        activityUpdateButton = new QPushButton(activityButtonFrame);
        activityUpdateButton->setObjectName("activityUpdateButton");
        activityUpdateButton->setMinimumSize(QSize(150, 45));
        activityUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        activityUpdateButton->setIcon(icon3);

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

        activityTabWidget->addTab(activityAddTab, icon2, QString());
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
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        activityTypeStatsTable->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        activityTypeStatsTable->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        activityTypeStatsTable->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        activityTypeStatsTable->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        activityTypeStatsTable->setObjectName("activityTypeStatsTable");
        activityTypeStatsTable->setAlternatingRowColors(true);

        activityTypeStatsLayout->addWidget(activityTypeStatsTable);


        activityStatsGridLayout->addWidget(activityTypeStatsFrame, 1, 0, 1, 3);


        activityStatisticsLayout->addWidget(activityStatsFrame);

        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/statistic.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        activityTabWidget->addTab(activityStatisticsTab, icon4, QString());

        activitiesPageLayout->addWidget(activityTabWidget);

        stackedWidget->addWidget(activitiesPage);

        mainContentLayout->addWidget(stackedWidget);


        mainHorizontalLayout->addWidget(mainContentFrame);


        verticalLayout_main->addWidget(mainFrame);

        ActivityManagement->setCentralWidget(centralwidget);

        retranslateUi(ActivityManagement);

        stackedWidget->setCurrentIndex(0);
        activityTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ActivityManagement);
    } // setupUi

    void retranslateUi(QMainWindow *ActivityManagement)
    {
        ActivityManagement->setWindowTitle(QCoreApplication::translate("ActivityManagement", "VIBRA CLUB - Activity Management", nullptr));
        logo->setText(QCoreApplication::translate("ActivityManagement", "TextLabel", nullptr));
        logoLabel->setText(QCoreApplication::translate("ActivityManagement", "VIBRA CLUB", nullptr));
        userAvatarLabel->setText(QCoreApplication::translate("ActivityManagement", "KC", nullptr));
        userNameLabel->setText(QCoreApplication::translate("ActivityManagement", "Khalil Cherif", nullptr));
        userRoleLabel->setText(QCoreApplication::translate("ActivityManagement", "Activity Manager", nullptr));
        activityPageTitle->setText(QCoreApplication::translate("ActivityManagement", "Activity Management", nullptr));
        activitySearchLineEdit->setPlaceholderText(QCoreApplication::translate("ActivityManagement", "Search activities...", nullptr));
        activitySearchButton->setText(QCoreApplication::translate("ActivityManagement", " Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = activityTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ActivityManagement", "Activity ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = activityTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ActivityManagement", "Activity Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = activityTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ActivityManagement", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = activityTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ActivityManagement", "Event Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = activityTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ActivityManagement", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = activityTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ActivityManagement", "Responsible", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = activityTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ActivityManagement", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = activityTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ActivityManagement", "Actions", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityListTab), QCoreApplication::translate("ActivityManagement", " List of Activities", nullptr));
        responsibleLineEdit->setPlaceholderText(QCoreApplication::translate("ActivityManagement", "Enter responsible person or instructor name", nullptr));
        activityStatusComboBox->setItemText(0, QCoreApplication::translate("ActivityManagement", "Scheduled", nullptr));
        activityStatusComboBox->setItemText(1, QCoreApplication::translate("ActivityManagement", "In Progress", nullptr));
        activityStatusComboBox->setItemText(2, QCoreApplication::translate("ActivityManagement", "Completed", nullptr));
        activityStatusComboBox->setItemText(3, QCoreApplication::translate("ActivityManagement", "Cancelled", nullptr));
        activityStatusComboBox->setItemText(4, QCoreApplication::translate("ActivityManagement", "Postponed", nullptr));

        responsibleLabel->setText(QCoreApplication::translate("ActivityManagement", "Responsible/Actor:", nullptr));
        eventDateLabel->setText(QCoreApplication::translate("ActivityManagement", "Event Date:", nullptr));
        eventTimeEdit->setDisplayFormat(QCoreApplication::translate("ActivityManagement", "HH:mm", nullptr));
        eventTimeLabel->setText(QCoreApplication::translate("ActivityManagement", "Event Time:", nullptr));
        activityIdLineEdit->setPlaceholderText(QCoreApplication::translate("ActivityManagement", "e.g., ACT001", nullptr));
        activityIdLabel->setText(QCoreApplication::translate("ActivityManagement", "Activity ID:", nullptr));
        activityTypeLabel->setText(QCoreApplication::translate("ActivityManagement", "Activity Type:", nullptr));
        activityConfirmButton->setText(QCoreApplication::translate("ActivityManagement", " Confirm Add Activity", nullptr));
        activityUpdateButton->setText(QCoreApplication::translate("ActivityManagement", " Update Activity", nullptr));
        activityTypeComboBox->setItemText(0, QCoreApplication::translate("ActivityManagement", "Group Class", nullptr));
        activityTypeComboBox->setItemText(1, QCoreApplication::translate("ActivityManagement", "Personal Training", nullptr));
        activityTypeComboBox->setItemText(2, QCoreApplication::translate("ActivityManagement", "Workshop", nullptr));
        activityTypeComboBox->setItemText(3, QCoreApplication::translate("ActivityManagement", "Competition", nullptr));
        activityTypeComboBox->setItemText(4, QCoreApplication::translate("ActivityManagement", "Event", nullptr));
        activityTypeComboBox->setItemText(5, QCoreApplication::translate("ActivityManagement", "Maintenance", nullptr));

        activityDescriptionTextEdit->setPlaceholderText(QCoreApplication::translate("ActivityManagement", "Enter detailed activity description, requirements, or notes...", nullptr));
        activityStatusLabel->setText(QCoreApplication::translate("ActivityManagement", "Status:", nullptr));
        activityDescriptionLabel->setText(QCoreApplication::translate("ActivityManagement", "Activity Description:", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityAddTab), QCoreApplication::translate("ActivityManagement", " Add Activity", nullptr));
        totalActivitiesTitle->setText(QCoreApplication::translate("ActivityManagement", "Total Activities", nullptr));
        totalActivitiesNumber->setText(QCoreApplication::translate("ActivityManagement", "127", nullptr));
        upcomingActivitiesTitle->setText(QCoreApplication::translate("ActivityManagement", "Upcoming Activities", nullptr));
        upcomingActivitiesNumber->setText(QCoreApplication::translate("ActivityManagement", "23", nullptr));
        activeActivitiesTitle->setText(QCoreApplication::translate("ActivityManagement", "Active Today", nullptr));
        activeActivitiesNumber->setText(QCoreApplication::translate("ActivityManagement", "8", nullptr));
        activityTypeStatsTitle->setText(QCoreApplication::translate("ActivityManagement", "\360\237\223\210 Activity Type Distribution", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = activityTypeStatsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ActivityManagement", "Activity Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = activityTypeStatsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ActivityManagement", "Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = activityTypeStatsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ActivityManagement", "Percentage", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = activityTypeStatsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ActivityManagement", "This Month", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityStatisticsTab), QCoreApplication::translate("ActivityManagement", " Statistics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ActivityManagement: public Ui_ActivityManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIVITYMANAGEMENT_H
