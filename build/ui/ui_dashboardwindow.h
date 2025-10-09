/********************************************************************************
** Form generated from reading UI file 'dashboardwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARDWINDOW_H
#define UI_DASHBOARDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DashboardWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_main;
    QFrame *sidebarFrame;
    QVBoxLayout *verticalLayout_sidebar;
    QLabel *logoLabel;
    QSpacerItem *spacer_top;
    QPushButton *membersButton;
    QPushButton *activitiesButton;
    QSpacerItem *spacer_bottom;
    QPushButton *exitButton;
    QFrame *mainFrame;
    QVBoxLayout *verticalLayout_mainFrame;
    QStackedWidget *stackedWidget;
    QWidget *dashboardPage;
    QVBoxLayout *verticalLayout_dashboardPage;

    void setupUi(QMainWindow *DashboardWindow)
    {
        if (DashboardWindow->objectName().isEmpty())
            DashboardWindow->setObjectName("DashboardWindow");
        DashboardWindow->resize(1300, 850);
        DashboardWindow->setStyleSheet(QString::fromUtf8("\n"
"QMainWindow {\n"
"    background-color: #f5f7fa;\n"
"}\n"
"\n"
"/* Sidebar */\n"
"#sidebarFrame {\n"
"    background-color: white;\n"
"    border-right: 1px solid #e0e4e7;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: transparent;\n"
"    color: #2c3e50;\n"
"    border: none;\n"
"    text-align: left;\n"
"    padding: 14px 28px;\n"
"    font-size: 15px;\n"
"    border-radius: 10px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(22,165,179,0.1);\n"
"    color: #16a5b3;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #16a5b3;\n"
"    color: white;\n"
"}\n"
"\n"
"/* Header */\n"
"#headerFrame {\n"
"    background-color: white;\n"
"    border-bottom: 1px solid #e0e4e7;\n"
"}\n"
"\n"
"#logoLabel {\n"
"    font-size: 22px;\n"
"    font-weight: bold;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"/* Main content */\n"
"#mainFrame {\n"
"    background-color: transparent;\n"
"}\n"
"   "));
        centralwidget = new QWidget(DashboardWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_main = new QHBoxLayout(centralwidget);
        horizontalLayout_main->setSpacing(0);
        horizontalLayout_main->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_main->setObjectName("horizontalLayout_main");
        sidebarFrame = new QFrame(centralwidget);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarFrame->setMinimumSize(QSize(240, 0));
        verticalLayout_sidebar = new QVBoxLayout(sidebarFrame);
        verticalLayout_sidebar->setObjectName("verticalLayout_sidebar");
        verticalLayout_sidebar->setContentsMargins(20, 20, 20, 20);
        logoLabel = new QLabel(sidebarFrame);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignHCenter);

        verticalLayout_sidebar->addWidget(logoLabel);

        spacer_top = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_sidebar->addItem(spacer_top);

        membersButton = new QPushButton(sidebarFrame);
        membersButton->setObjectName("membersButton");
        membersButton->setCheckable(true);

        verticalLayout_sidebar->addWidget(membersButton);

        activitiesButton = new QPushButton(sidebarFrame);
        activitiesButton->setObjectName("activitiesButton");
        activitiesButton->setCheckable(true);

        verticalLayout_sidebar->addWidget(activitiesButton);

        spacer_bottom = new QSpacerItem(20, 400, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_sidebar->addItem(spacer_bottom);

        exitButton = new QPushButton(sidebarFrame);
        exitButton->setObjectName("exitButton");

        verticalLayout_sidebar->addWidget(exitButton);


        horizontalLayout_main->addWidget(sidebarFrame);

        mainFrame = new QFrame(centralwidget);
        mainFrame->setObjectName("mainFrame");
        verticalLayout_mainFrame = new QVBoxLayout(mainFrame);
        verticalLayout_mainFrame->setObjectName("verticalLayout_mainFrame");
        verticalLayout_mainFrame->setContentsMargins(20, 20, 20, 20);
        stackedWidget = new QStackedWidget(mainFrame);
        stackedWidget->setObjectName("stackedWidget");
        dashboardPage = new QWidget();
        dashboardPage->setObjectName("dashboardPage");
        verticalLayout_dashboardPage = new QVBoxLayout(dashboardPage);
        verticalLayout_dashboardPage->setObjectName("verticalLayout_dashboardPage");
        stackedWidget->addWidget(dashboardPage);

        verticalLayout_mainFrame->addWidget(stackedWidget);


        horizontalLayout_main->addWidget(mainFrame);

        DashboardWindow->setCentralWidget(centralwidget);

        retranslateUi(DashboardWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DashboardWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DashboardWindow)
    {
        DashboardWindow->setWindowTitle(QCoreApplication::translate("DashboardWindow", "VIBRA CLUB - Dashboard", nullptr));
        logoLabel->setText(QCoreApplication::translate("DashboardWindow", "\360\237\217\231\357\270\217 VIBRA CLUB", nullptr));
        membersButton->setText(QCoreApplication::translate("DashboardWindow", "\360\237\221\245  Members", nullptr));
        activitiesButton->setText(QCoreApplication::translate("DashboardWindow", "\360\237\217\213\357\270\217\342\200\215\342\231\200\357\270\217  Activities", nullptr));
        exitButton->setText(QCoreApplication::translate("DashboardWindow", "\360\237\232\252  Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardWindow: public Ui_DashboardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARDWINDOW_H
