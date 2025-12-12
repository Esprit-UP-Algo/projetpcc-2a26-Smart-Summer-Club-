/********************************************************************************
** Form generated from reading UI file 'employeradmin.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYERADMIN_H
#define UI_EMPLOYERADMIN_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
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
#include "emailpanel.h"
#include "ocrinterface.h"

QT_BEGIN_NAMESPACE

class Ui_EmployerAdmin
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
    QLabel *navigationTitle;
    QFrame *navigationFrame;
    QVBoxLayout *navigationLayout;
    QPushButton *employeesButton;
    QPushButton *membersButton;
    QPushButton *equipmentButton;
    QPushButton *activitiesButton;
    QPushButton *paymentsButton;
    QSpacerItem *verticalSpacer_sidebar;
    QFrame *bottomButtonsFrame;
    QVBoxLayout *bottomButtonsLayout;
    QPushButton *settingsButton;
    QPushButton *logoutButton;
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
    QSpacerItem *employeeSearchSpacer;
    QPushButton *employeeSortButton;
    QPushButton *employeeExportButton;
    QTableWidget *employeeTable;
    QWidget *addTab;
    QVBoxLayout *addTabLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *formMainLayout;
    QFrame *formFrame;
    QGridLayout *gridLayout;
    QFrame *photoFrame;
    QVBoxLayout *photoLayout;
    QLabel *photoLabel;
    QPushButton *employeeUploadPhotoButton;
    QLabel *firstNameLabel;
    QComboBox *departmentComboBox;
    QLineEdit *passwordLineEedit;
    QComboBox *genderComboBox;
    QLabel *phoneLabel;
    QFrame *buttonFrame;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *confirmAddButton;
    QPushButton *confirmUpdateButton;
    QLabel *genderLabel;
    QSpinBox *ageSpinBox;
    QLabel *lastNameLabel;
    QLineEdit *emailLineEdit;
    QLineEdit *salaryLineEdit;
    QDateEdit *hireDateEdit;
    QLabel *departmentLabel;
    QLabel *emailLabel;
    QLineEdit *empIdLineEdit;
    QComboBox *positionComboBox;
    QComboBox *statusComboBox;
    QLineEdit *lastNameLineEdit;
    QLabel *hireDateLabel;
    QLineEdit *firstNameLineEdit;
    QLabel *positionLabel;
    QLabel *ageLabel;
    QLabel *salaryLabel;
    QLabel *passwordLabel;
    QLabel *empIdLabel;
    QLabel *statusLabel;
    QLineEdit *phoneLineEdit;
    QWidget *statisticsTab;
    QVBoxLayout *statisticsLayout;
    QFrame *headerFrame;
    QVBoxLayout *headerLayout;
    QLabel *titleLabel;
    QFrame *cardsContainer;
    QGridLayout *cardsGrid;
    QFrame *totalEmployeesCard;
    QVBoxLayout *totalEmployeesLayout;
    QLabel *totalEmployeesTitle;
    QLabel *totalEmployeesNumber;
    QFrame *activeEmployeesCard;
    QVBoxLayout *activeEmployeesLayout;
    QLabel *activeEmployeesTitle;
    QLabel *activeEmployeesNumber;
    QFrame *newEmployeesCard;
    QVBoxLayout *newEmployeesLayout;
    QLabel *newEmployeesTitle;
    QLabel *newEmployeesNumber;
    QFrame *chartsContainer;
    QGridLayout *chartsGrid;
    QFrame *employeeDepartmentChartFrame;
    QVBoxLayout *employeeDepartmentChartLayout;
    QLabel *employeeDepartmentChartTitle;
    QLabel *employeeDepartmentChartPlaceholder;
    QFrame *employeeStatusChartFrame;
    QVBoxLayout *employeeStatusChartLayout;
    QLabel *employeeStatusChartTitle;
    QLabel *employeeStatusChartPlaceholder;
    QFrame *employeeSalaryChartFrame;
    QVBoxLayout *employeeSalaryChartLayout;
    QLabel *employeeSalaryChartTitle;
    QLabel *employeeSalaryChartPlaceholder;
    QWidget *employeeLogsTab;
    QVBoxLayout *employeeLogsLayout;
    QLabel *employeeLogsPlaceholder;
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
    QSpacerItem *memberSearchSpacer;
    QPushButton *memberSortButton;
    QPushButton *memberExportButton;
    QTableWidget *memberTable;
    QWidget *memberAddTab;
    QVBoxLayout *memberAddTabLayout;
    QScrollArea *memberScrollArea;
    QWidget *memberScrollAreaContents;
    QVBoxLayout *memberFormMainLayout;
    QFrame *memberFormFrame;
    QGridLayout *memberFormLayout;
    QLabel *memberGenderLabel;
    QLineEdit *memberLastNameLineEdit;
    QLineEdit *memberFirstNameLineEdit;
    QDateEdit *memberJoinDateEdit;
    QLabel *memberJoinDateLabel;
    QLabel *memberFirstNameLabel;
    QLineEdit *memberIdLineEdit;
    QLabel *memberPhoneLabel;
    QComboBox *memberGenderComboBox;
    QLabel *memberEmailLabel;
    QLineEdit *memberPhoneLineEdit;
    QLabel *memberAgeLabel;
    QSpinBox *memberAgeSpinBox;
    QFrame *memberButtonFrame;
    QHBoxLayout *memberButtonLayout;
    QSpacerItem *buttonSpacer_2;
    QPushButton *memberConfirmAddButton;
    QPushButton *memberConfirmUpdateButton;
    QLabel *memberLastNameLabel;
    QLabel *memberIdLabel;
    QLineEdit *memberEmailLineEdit;
    QComboBox *memberSubscriptionComboBox;
    QLabel *memberSubscriptionLabel;
    QFrame *memberPhotoFrame;
    QVBoxLayout *memberPhotoLayout;
    QLabel *memberPhotoLabel;
    QPushButton *memberUploadPhotoButton;
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
    QFrame *memberChartsContainer;
    QGridLayout *memberChartsGrid;
    QFrame *memberGenderChartFrame;
    QVBoxLayout *memberGenderChartLayout;
    QLabel *memberGenderChartTitle;
    QLabel *memberGenderChartPlaceholder;
    QFrame *memberAgeChartFrame;
    QVBoxLayout *memberAgeChartLayout;
    QLabel *memberAgeChartTitle;
    QLabel *memberAgeChartPlaceholder;
    QFrame *memberSubscriptionChartFrame;
    QVBoxLayout *memberSubscriptionChartLayout;
    QLabel *memberSubscriptionChartTitle;
    QLabel *memberSubscriptionChartPlaceholder;
    QWidget *memberSMSTab;
    QVBoxLayout *memberSMSTabLayout;
    EmailPanel *emailPanel;
    QWidget *memberOCRTab;
    QVBoxLayout *memberOCRTabLayout;
    OCRInterface *ocrInterface;
    QWidget *equipmentPage;
    QVBoxLayout *equipmentPageLayout;
    QLabel *equipmentPageTitle;
    QTabWidget *equipmentTabWidget;
    QWidget *equipmentListTab;
    QVBoxLayout *equipmentListTabLayout;
    QFrame *equipmentSearchFrame;
    QHBoxLayout *equipmentSearchLayout;
    QLineEdit *equipmentSearchLineEdit;
    QPushButton *equipmentSearchButton;
    QSpacerItem *equipmentSearchSpacer;
    QPushButton *equipmentSortButton;
    QPushButton *equipmentExportButton;
    QTableWidget *equipmentTable;
    QWidget *equipmentAddTab;
    QVBoxLayout *equipmentAddTabLayout;
    QScrollArea *equipmentScrollArea;
    QWidget *equipmentScrollAreaContents;
    QVBoxLayout *equipmentFormMainLayout;
    QFrame *equipmentFormFrame;
    QGridLayout *equipmentFormLayout;
    QLabel *equipmentQuantityLabel;
    QLineEdit *equipmentModelLineEdit;
    QLabel *equipmentNameLabel;
    QComboBox *equipmentCategoryComboBox;
    QLabel *equipmentCategoryLabel;
    QLabel *equipmentBrandLabel;
    QFrame *equipmentButtonFrame;
    QHBoxLayout *equipmentButtonLayout;
    QSpacerItem *equipmentButtonSpacer;
    QPushButton *equipmentConfirmButton;
    QPushButton *equipmentUpdateButton;
    QLabel *equipmentPurchaseDateLabel;
    QSpinBox *equipmentQuantitySpinBox;
    QLabel *equipmentStatusLabel;
    QComboBox *equipmentStatusComboBox;
    QLabel *equipmentModelLabel;
    QDateEdit *equipmentPurchaseDateEdit;
    QLineEdit *equipmentNameLineEdit;
    QLineEdit *equipmentBrandLineEdit;
    QLineEdit *equipmentPriceLineEdit;
    QLabel *equipmentPriceLabel;
    QWidget *equipmentStatisticsTab;
    QVBoxLayout *equipmentStatisticsLayout;
    QFrame *equipmentStatsFrame;
    QGridLayout *equipmentStatsGridLayout;
    QFrame *totalEquipmentCard;
    QVBoxLayout *totalEquipmentLayout;
    QLabel *totalEquipmentTitle;
    QLabel *totalEquipmentNumber;
    QFrame *availableEquipmentCard;
    QVBoxLayout *availableEquipmentLayout;
    QLabel *availableEquipmentTitle;
    QLabel *availableEquipmentNumber;
    QFrame *maintenanceEquipmentCard;
    QVBoxLayout *maintenanceEquipmentLayout;
    QLabel *maintenanceEquipmentTitle;
    QLabel *maintenanceEquipmentNumber;
    QFrame *equipmentCategoryStatsFrame;
    QVBoxLayout *equipmentCategoryStatsLayout;
    QLabel *equipmentCategoryStatsTitle;
    QTableWidget *equipmentCategoryStatsTable;
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
    QSpacerItem *activitySearchSpacer;
    QComboBox *activitySortComboBox;
    QPushButton *activityExportButton;
    QTableWidget *activityTable;
    QWidget *activityAddTab;
    QVBoxLayout *activityAddTabLayout;
    QScrollArea *activityScrollArea;
    QWidget *activityScrollAreaContents;
    QVBoxLayout *activityFormMainLayout;
    QFrame *activityFormFrame;
    QGridLayout *activityFormLayout;
    QSpinBox *activityAgeSpinBox;
    QFrame *activityButtonFrame;
    QHBoxLayout *activityButtonLayout;
    QSpacerItem *activityButtonSpacer;
    QPushButton *activityConfirmButton;
    QPushButton *activityUpdateButton;
    QTimeEdit *eventTimeEdit;
    QLabel *activityDescriptionLabel;
    QLabel *activityAgeLabel;
    QLabel *activityCapacityLabel;
    QFrame *activityDescriptionFrame;
    QVBoxLayout *activityDescriptionLayout;
    QTextEdit *activityDescriptionTextEdit;
    QWidget *responsibleWidget;
    QHBoxLayout *responsibleLayout;
    QComboBox *responsibleComboBox;
    QLineEdit *responsibleLineEdit;
    QPushButton *responsibleToggleButton;
    QSpinBox *activityCapacitySpinBox;
    QLabel *eventTimeLabel;
    QLabel *responsibleLabel;
    QDateEdit *eventDateEdit;
    QLabel *eventDateLabel;
    QLabel *activityStatusLabel;
    QComboBox *activityStatusComboBox;
    QLabel *activityTypeLabel;
    QComboBox *activityTypeComboBox;
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
    QFrame *activityChartsContainer;
    QGridLayout *activityChartsGrid;
    QFrame *activityTypeChartFrame;
    QVBoxLayout *activityTypeChartLayout;
    QLabel *activityTypeChartTitle;
    QLabel *activityTypeChartPlaceholder;
    QFrame *activityAgeChartFrame;
    QVBoxLayout *activityAgeChartLayout;
    QLabel *activityAgeChartTitle;
    QLabel *activityAgeChartPlaceholder;
    QWidget *activityCalendarTab;
    QVBoxLayout *activityCalendarLayout;
    QLabel *activityCalendarPlaceholder;
    QWidget *paymentsPage;
    QVBoxLayout *paymentsPageLayout;
    QTabWidget *paymentTabWidget;
    QWidget *listTab_4;
    QVBoxLayout *paymentListLayout;
    QFrame *paymentSearchFrame;
    QHBoxLayout *paymentSearchLayout;
    QLineEdit *paymentSearchLineEdit;
    QPushButton *paymentSearchButton;
    QSpacerItem *paymentSearchSpacer;
    QPushButton *paymentSortButton;
    QPushButton *paymentExportButton;
    QTableWidget *paymentTable;
    QWidget *addTab_4;
    QVBoxLayout *addPaymentLayout;
    QScrollArea *paymentScrollArea;
    QWidget *paymentScrollContent;
    QVBoxLayout *paymentFormMainLayout;
    QFrame *paymentFormFrame;
    QGridLayout *paymentGridLayout;
    QLineEdit *paymentDescriptionEdit;
    QLabel *paymentAmountLabel;
    QComboBox *paymentTypeCombo;
    QLabel *paymentTypeLabel;
    QLabel *paymentDescriptionLabel;
    QDoubleSpinBox *paymentAmountSpinBox;
    QDateEdit *paymentDateEdit;
    QLabel *paymentMethodLabel;
    QComboBox *paymentMethodCombo;
    QLabel *paymentCategoryLabel;
    QComboBox *paymentCategoryCombo;
    QLabel *paymentDateLabel;
    QLabel *paymentMemberLabel;
    QLineEdit *paymentMemberEdit;
    QLabel *paymentStatusLabel;
    QComboBox *paymentStatusCombo;
    QFrame *paymentButtonFrame;
    QHBoxLayout *paymentButtonLayout;
    QSpacerItem *paymentButtonSpacer;
    QPushButton *addPaymentButton;
    QPushButton *clearPaymentFormButton;
    QSpacerItem *paymentButtonSpacer2;
    QWidget *statisticsTab_4;
    QVBoxLayout *paymentStatsLayout;
    QScrollArea *paymentStatsScrollArea;
    QWidget *paymentStatsScrollContent;
    QVBoxLayout *paymentStatsContentLayout;
    QFrame *paymentSummaryFrame;
    QHBoxLayout *paymentSummaryLayout;
    QFrame *totalIncomeCard;
    QVBoxLayout *totalIncomeLayout;
    QLabel *totalIncomeLabel;
    QLabel *totalIncomeValue;
    QFrame *totalExpenseCard;
    QVBoxLayout *totalExpenseLayout;
    QLabel *totalExpenseLabel;
    QLabel *totalExpenseValue;
    QFrame *netBalanceCard;
    QVBoxLayout *netBalanceLayout;
    QLabel *netBalanceLabel;
    QLabel *netBalanceValue;
    QFrame *paymentChartsFrame;
    QVBoxLayout *paymentChartsLayout;
    QLabel *paymentChartsTitle;
    QTableWidget *paymentMethodStatsTable;
    QFrame *recentPaymentsFrame;
    QVBoxLayout *recentPaymentsLayout;
    QLabel *recentPaymentsTitle;
    QTableWidget *recentPaymentsTable;
    QWidget *settingsPage;
    QVBoxLayout *settingsPageLayout;
    QLabel *settingsPageTitle;
    QScrollArea *settingsScrollArea;
    QWidget *settingsScrollAreaContents;
    QVBoxLayout *settingsMainLayout;
    QFrame *userProfileFrame;
    QVBoxLayout *userProfileLayout;
    QLabel *userProfileTitle;
    QFrame *userProfileContentFrame;
    QGridLayout *userProfileContentLayout;
    QLabel *profilePictureLabel;
    QFrame *profileInfoFrame;
    QVBoxLayout *profileInfoLayout;
    QLabel *currentUserNameLabel;
    QLabel *currentUserRoleLabel;
    QPushButton *changeProfilePictureButton;
    QFrame *securityFrame;
    QVBoxLayout *securityLayout;
    QLabel *securityTitle;
    QFrame *twoFactorFrame;
    QHBoxLayout *twoFactorLayout;
    QFrame *twoFactorInfoFrame;
    QVBoxLayout *twoFactorInfoLayout;
    QLabel *twoFactorLabel;
    QLabel *twoFactorDescription;
    QSpacerItem *twoFactorSpacer;
    QFrame *twoFactorControlsFrame;
    QVBoxLayout *twoFactorControlsLayout;
    QLabel *twoFactorStatusLabel;
    QPushButton *setupTwoFactorButton;
    QPushButton *disableTwoFactorButton;
    QFrame *passwordChangeFrame;
    QVBoxLayout *passwordChangeLayout;
    QLabel *passwordChangeTitle;
    QFrame *passwordFieldsFrame;
    QGridLayout *passwordFieldsLayout;
    QLabel *currentPasswordLabel;
    QLineEdit *currentPasswordLineEdit;
    QLabel *newPasswordLabel;
    QLineEdit *newPasswordLineEdit;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordLineEdit;
    QPushButton *changePasswordButton;
    QFrame *appearanceFrame;
    QVBoxLayout *appearanceLayout;
    QLabel *appearanceTitle;
    QFrame *themeFrame;
    QHBoxLayout *themeLayout;
    QLabel *themeLabel;
    QComboBox *themeComboBox;
    QSpacerItem *themeSpacer;
    QPushButton *applyThemeButton;
    QFrame *preferencesFrame;
    QVBoxLayout *preferencesLayout;
    QLabel *preferencesTitle;
    QFrame *preferencesContentFrame;
    QVBoxLayout *preferencesContentLayout;
    QCheckBox *autoRefreshCheckBox;
    QCheckBox *notificationsCheckBox;
    QCheckBox *soundCheckBox;
    QSpacerItem *settingsVerticalSpacer;

    void setupUi(QMainWindow *EmployerAdmin)
    {
        if (EmployerAdmin->objectName().isEmpty())
            EmployerAdmin->setObjectName("EmployerAdmin");
        EmployerAdmin->resize(1390, 1112);
        EmployerAdmin->setStyleSheet(QString::fromUtf8("QMainWindow { background-color: #f5f7fa; } /* Top Bar Styling */ #topBarFrame { /* Match sidebar: smooth horizontal gradient from left to right */ background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 rgba(22, 165, 179, 0.28), stop:1 rgba(22, 165, 179, 0.12)); border-bottom: 1px solid #e0e4e7; } #logoLabel { font-size: 24px; font-weight: bold; color: #2c3e50; } #userInfoFrame { background-color: transparent; } #userNameLabel { font-size: 14px; font-weight: 600; color: #2c3e50; } #userRoleLabel { font-size: 12px; color: #7f8c8d; } #userAvatarLabel { background-color: #3498db; border-radius: 20px; color: white; font-weight: bold; } /* Sidebar Styling */ #sidebarFrame { /* Original gradient with teal colors */ background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 rgba(22, 165, 179, 0.28), stop:1 rgba(22, 165, 179, 0.12)); border-right: 1px solid #e0e4e7; } #navigationFrame { background-color: transparent; padding: 10px 0; } QPushButton#employeesButton, QPushButton#membersButton, QPushButton#"
                        "equipmentButton, QPushButton#activitiesButton, QPushButton#paymentsButton { background-color: transparent; border: none; padding: 18px 24px; text-align: left; font-size: 15px; font-weight: 500; color: #34495e; border-radius: 12px; margin: 4px 16px; transition: all 0.3s ease; min-height: 20px; } QPushButton#employeesButton:hover, QPushButton#membersButton:hover, QPushButton#equipmentButton:hover, QPushButton#activitiesButton:hover, QPushButton#paymentsButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 rgba(22, 165, 179, 0.12), stop:1 rgba(22, 165, 179, 0.08)); color: #16a5b3; transform: translateX(4px); box-shadow: 0 2px 8px rgba(22, 165, 179, 0.15); } QPushButton#employeesButton:checked, QPushButton#membersButton:checked, QPushButton#equipmentButton:checked, QPushButton#activitiesButton:checked, QPushButton#paymentsButton:checked { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #16a5b3, stop:1 #139aa6); color: white; font-weight: 600; box-shadow: 0 4px 12px rgba(22, 165, 179,"
                        " 0.25); transform: translateX(6px); } QPushButton#employeesButton:checked:hover, QPushButton#membersButton:checked:hover, QPushButton#equipmentButton:checked:hover, QPushButton#activitiesButton:checked:hover, QPushButton#paymentsButton:checked:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #139aa6, stop:1 #0f858f); box-shadow: 0 6px 16px rgba(22, 165, 179, 0.35); } /* Settings and Logout Button Styling */ QPushButton#settingsButton, QPushButton#logoutButton { background-color: transparent; border: none; padding: 18px 24px; text-align: left; font-size: 15px; font-weight: 500; color: #34495e; border-radius: 12px; margin: 4px 16px; transition: all 0.3s ease; min-height: 20px; } QPushButton#settingsButton:hover, QPushButton#logoutButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 rgba(22, 165, 179, 0.12), stop:1 rgba(22, 165, 179, 0.08)); color: #16a5b3; transform: translateX(4px); box-shadow: 0 2px 8px rgba(22, 165, 179, 0.15); } /* Main Content Styling */ #mainContentFr"
                        "ame { background-color: transparent; } /* Tab Widget Styling */ QTabWidget::pane { border: 2px solid #16a5b3; background-color: white; border-radius: 12px; box-shadow: 0 4px 6px rgba(22, 165, 179, 0.1); } QTabBar::tab { /* Unselected tabs mimic our button style: transparent teal with teal border */ background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; padding: 12px 24px; margin-right: 2px; border-top-left-radius: 8px; border-top-right-radius: 8px; border: 1.5px solid rgba(22, 165, 179, 0.65); border-bottom: none; } QTabBar::tab:selected { background-color: #16a5b3; color: white; border-color: #16a5b3; font-weight: 600; } QTabBar::tab:hover:!selected { background-color: rgba(22, 165, 179, 0.18); border-color: #16a5b3; transition: all 0.3s ease; } /* Statistics Cards Styling */ QFrame[objectName*=\"Card\"] { background-color: white; border: 1px solid #e0e4e7; border-radius: 16px; padding: 20px; box-shadow: 0 2px 10px rgba(0, 0, 0, 0.05); } QFrame[objectName*=\"Card\"]:hover { box-shadow: 0 4px 20px rgba(22"
                        ", 165, 179, 0.15); border-color: #16a5b3; transition: all 0.3s ease; } /* Form Styling */ QLineEdit { padding: 14px 16px; border: 2px solid #e0e4e7; border-radius: 10px; font-size: 14px; background-color: white; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02); } QLineEdit:focus { border-color: #16a5b3; box-shadow: 0 0 0 3px rgba(22, 165, 179, 0.1); outline: none; } QLineEdit:hover { border-color: #16a5b3; transition: border-color 0.2s ease; } QComboBox { padding: 14px 16px; border: 2px solid #e0e4e7; border-radius: 10px; font-size: 14px; background-color: white; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02); } QComboBox:focus { border-color: #16a5b3; box-shadow: 0 0 0 3px rgba(22, 165, 179, 0.1); } QComboBox:hover { border-color: #16a5b3; transition: border-color 0.2s ease; } QDateEdit, QSpinBox { padding: 14px 16px; border: 2px solid #e0e4e7; border-radius: 10px; font-size: 14px; background-color: white; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02); } QDateEdit:focus, QSpinBox:focus { border-color: #16a5b3; box-shadow: 0 "
                        "0 0 3px rgba(22, 165, 179, 0.1); } QTextEdit { padding: 14px 16px; border: 2px solid #e0e4e7; border-radius: 10px; font-size: 14px; background-color: white; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.02); } QTextEdit:focus { border-color: #16a5b3; box-shadow: 0 0 0 3px rgba(22, 165, 179, 0.1); } QPushButton#actionButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #16a5b3, stop:1 #139aa6); color: white; border: none; padding: 14px 28px; border-radius: 10px; font-size: 14px; font-weight: 600; box-shadow: 0 4px 8px rgba(22, 165, 179, 0.2); } QPushButton#actionButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #139aa6, stop:1 #0f858f); box-shadow: 0 6px 12px rgba(22, 165, 179, 0.3); transform: translateY(-1px); } QPushButton#actionButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0f858f, stop:1 #0c6b73); box-shadow: 0 2px 4px rgba(22, 165, 179, 0.2); transform: translateY(0px); } /* Table Styling */ QTableWidget { background-color: white; gridline-color"
                        ": #e6eef0; border: 2px solid #16a5b3; /* teal border like the mock */ border-radius: 12px; selection-background-color: rgba(22, 165, 179, 0.14); selection-color: #2c3e50; } /* Header styled to main brand color */ QHeaderView::section { background-color: #16a5b3; color: white; padding: 8px 10px; border: none; font-weight: 600; border-right: 1px solid rgba(255,255,255,0.25); } /* Corner button (top-left of table) to match header */ QTableCornerButton::section { background-color: #16a5b3; border: none; } /* Alternate rows for subtle striping */ QTableView::item:alternate { background: rgba(22, 165, 179, 0.03); } /* Selected row styling */ QTableView::item:selected { background: rgba(22, 165, 179, 0.14); color: #2c3e50; } /* Frame Styling */ QFrame { border-radius: 8px; } /* Label Styling */ QLabel { color: #2c3e50; } /* Search Frame Styling */ QFrame[objectName*=\"SearchFrame\"], QFrame[objectName*=\"searchFrame\"] { background-color: rgba(22, 165, 179, 0.02); border: 1px solid rgba(22, 165, 179, 0.1); border-rad"
                        "ius: 12px; padding: 8px; } /* Default buttons: avoid gray; use brand color with high transparency */ QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 10px 16px; border-radius: 10px; } QPushButton:hover { background-color: rgba(22, 165, 179, 0.18); } QPushButton:pressed { background-color: rgba(22, 165, 179, 0.26); } QPushButton:disabled { background-color: rgba(22, 165, 179, 0.06); color: #98a6ad; border-color: rgba(22, 165, 179, 0.25); }\n"
"/* ===== FIX: Invisible text in login and search fields ===== */\n"
"\n"
"/* Make sure typed text is visible in all line edits */\n"
"QLineEdit {\n"
"    color: #2c3e50;              /* dark readable text color like statistiques page */\n"
"}\n"
"\n"
"/* Placeholder text readable but subtle */\n"
"QLineEdit::placeholder {\n"
"    color: #7f8c8d;\n"
"}\n"
"\n"
"/* Specifically ensure login page inputs inherit readable color */\n"
"QLineEdit#emailLineEdit, \n"
"QLineEdit#passwordLineEdit {\n"
" "
                        "   color: #2c3e50;\n"
"    background-color: white;\n"
"}\n"
"\n"
"QLineEdit#emailLineEdit::placeholder, \n"
"QLineEdit#passwordLineEdit::placeholder {\n"
"    color: #7f8c8d;\n"
"}\n"
"\n"
"/* Ensure search bar input uses visible text */\n"
"QFrame#equipmentSearchFrame QLineEdit,\n"
"QFrame[objectName*=\"searchFrame\"] QLineEdit {\n"
"    color: #2c3e50;\n"
"    background-color: white;\n"
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
        logo = new QLabel(topBarFrame);
        logo->setObjectName("logo");
        logo->setMinimumSize(QSize(50, 50));
        logo->setMaximumSize(QSize(50, 50));
        logo->setPixmap(QPixmap(QString::fromUtf8(":/icons/assests/VibraClubLogo.png")));
        logo->setScaledContents(true);
        logo->setWordWrap(false);

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
        sidebarFrame->setMinimumSize(QSize(280, 0));
        sidebarFrame->setMaximumSize(QSize(280, 16777215));
        sidebarLayout = new QVBoxLayout(sidebarFrame);
        sidebarLayout->setSpacing(8);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(0, 30, 0, 30);
        navigationTitle = new QLabel(sidebarFrame);
        navigationTitle->setObjectName("navigationTitle");
        navigationTitle->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: 600; color: #7f8c8d; padding: 0 24px 8px 24px; text-transform: uppercase; letter-spacing: 1px;"));

        sidebarLayout->addWidget(navigationTitle);

        navigationFrame = new QFrame(sidebarFrame);
        navigationFrame->setObjectName("navigationFrame");
        navigationLayout = new QVBoxLayout(navigationFrame);
        navigationLayout->setSpacing(8);
        navigationLayout->setObjectName("navigationLayout");
        employeesButton = new QPushButton(navigationFrame);
        employeesButton->setObjectName("employeesButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/employee.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        employeesButton->setIcon(icon);
        employeesButton->setCheckable(true);
        employeesButton->setChecked(true);

        navigationLayout->addWidget(employeesButton);

        membersButton = new QPushButton(navigationFrame);
        membersButton->setObjectName("membersButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/members.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        membersButton->setIcon(icon1);
        membersButton->setCheckable(true);

        navigationLayout->addWidget(membersButton);

        equipmentButton = new QPushButton(navigationFrame);
        equipmentButton->setObjectName("equipmentButton");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/equipement.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        equipmentButton->setIcon(icon2);
        equipmentButton->setCheckable(true);

        navigationLayout->addWidget(equipmentButton);

        activitiesButton = new QPushButton(navigationFrame);
        activitiesButton->setObjectName("activitiesButton");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/activity.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        activitiesButton->setIcon(icon3);
        activitiesButton->setCheckable(true);

        navigationLayout->addWidget(activitiesButton);

        paymentsButton = new QPushButton(navigationFrame);
        paymentsButton->setObjectName("paymentsButton");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/payment.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        paymentsButton->setIcon(icon4);
        paymentsButton->setCheckable(true);

        navigationLayout->addWidget(paymentsButton);


        sidebarLayout->addWidget(navigationFrame);

        verticalSpacer_sidebar = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(verticalSpacer_sidebar);

        bottomButtonsFrame = new QFrame(sidebarFrame);
        bottomButtonsFrame->setObjectName("bottomButtonsFrame");
        bottomButtonsLayout = new QVBoxLayout(bottomButtonsFrame);
        bottomButtonsLayout->setSpacing(8);
        bottomButtonsLayout->setObjectName("bottomButtonsLayout");
        settingsButton = new QPushButton(bottomButtonsFrame);
        settingsButton->setObjectName("settingsButton");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/list.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingsButton->setIcon(icon5);

        bottomButtonsLayout->addWidget(settingsButton);

        logoutButton = new QPushButton(bottomButtonsFrame);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setIcon(icon5);

        bottomButtonsLayout->addWidget(logoutButton);


        sidebarLayout->addWidget(bottomButtonsFrame);


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
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        employeeSearchButton->setIcon(icon6);

        searchLayout->addWidget(employeeSearchButton);

        employeeSearchSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        searchLayout->addItem(employeeSearchSpacer);

        employeeSortButton = new QPushButton(searchFrame);
        employeeSortButton->setObjectName("employeeSortButton");

        searchLayout->addWidget(employeeSortButton);

        employeeExportButton = new QPushButton(searchFrame);
        employeeExportButton->setObjectName("employeeExportButton");

        searchLayout->addWidget(employeeExportButton);


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

        employeeTabWidget->addTab(listTab, icon5, QString());
        addTab = new QWidget();
        addTab->setObjectName("addTab");
        addTabLayout = new QVBoxLayout(addTab);
        addTabLayout->setObjectName("addTabLayout");
        scrollArea = new QScrollArea(addTab);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 536, 631));
        formMainLayout = new QVBoxLayout(scrollAreaWidgetContents);
        formMainLayout->setObjectName("formMainLayout");
        formFrame = new QFrame(scrollAreaWidgetContents);
        formFrame->setObjectName("formFrame");
        formFrame->setAutoFillBackground(false);
        formFrame->setStyleSheet(QString::fromUtf8("margin : 2px;"));
        gridLayout = new QGridLayout(formFrame);
        gridLayout->setObjectName("gridLayout");
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
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        employeeUploadPhotoButton->setIcon(icon7);

        photoLayout->addWidget(employeeUploadPhotoButton);


        gridLayout->addWidget(photoFrame, 8, 3, 1, 1);

        firstNameLabel = new QLabel(formFrame);
        firstNameLabel->setObjectName("firstNameLabel");
        firstNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(firstNameLabel, 1, 0, 1, 1);

        departmentComboBox = new QComboBox(formFrame);
        departmentComboBox->addItem(QString());
        departmentComboBox->addItem(QString());
        departmentComboBox->addItem(QString());
        departmentComboBox->addItem(QString());
        departmentComboBox->addItem(QString());
        departmentComboBox->setObjectName("departmentComboBox");

        gridLayout->addWidget(departmentComboBox, 7, 3, 1, 1);

        passwordLineEedit = new QLineEdit(formFrame);
        passwordLineEedit->setObjectName("passwordLineEedit");

        gridLayout->addWidget(passwordLineEedit, 0, 3, 1, 1);

        genderComboBox = new QComboBox(formFrame);
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->setObjectName("genderComboBox");

        gridLayout->addWidget(genderComboBox, 3, 1, 1, 1);

        phoneLabel = new QLabel(formFrame);
        phoneLabel->setObjectName("phoneLabel");
        phoneLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(phoneLabel, 8, 0, 1, 1);

        buttonFrame = new QFrame(formFrame);
        buttonFrame->setObjectName("buttonFrame");
        buttonLayout = new QHBoxLayout(buttonFrame);
        buttonLayout->setObjectName("buttonLayout");
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        confirmAddButton = new QPushButton(buttonFrame);
        confirmAddButton->setObjectName("confirmAddButton");
        confirmAddButton->setMinimumSize(QSize(150, 45));
        confirmAddButton->setIcon(icon7);

        buttonLayout->addWidget(confirmAddButton);

        confirmUpdateButton = new QPushButton(buttonFrame);
        confirmUpdateButton->setObjectName("confirmUpdateButton");
        confirmUpdateButton->setMinimumSize(QSize(150, 45));
        confirmUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        confirmUpdateButton->setIcon(icon8);

        buttonLayout->addWidget(confirmUpdateButton);


        gridLayout->addWidget(buttonFrame, 11, 0, 1, 4);

        genderLabel = new QLabel(formFrame);
        genderLabel->setObjectName("genderLabel");
        genderLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(genderLabel, 3, 0, 1, 1);

        ageSpinBox = new QSpinBox(formFrame);
        ageSpinBox->setObjectName("ageSpinBox");
        ageSpinBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        ageSpinBox->setMinimum(18);
        ageSpinBox->setMaximum(65);
        ageSpinBox->setValue(25);

        gridLayout->addWidget(ageSpinBox, 4, 1, 1, 1);

        lastNameLabel = new QLabel(formFrame);
        lastNameLabel->setObjectName("lastNameLabel");
        lastNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(lastNameLabel, 2, 0, 1, 1);

        emailLineEdit = new QLineEdit(formFrame);
        emailLineEdit->setObjectName("emailLineEdit");

        gridLayout->addWidget(emailLineEdit, 7, 1, 1, 1);

        salaryLineEdit = new QLineEdit(formFrame);
        salaryLineEdit->setObjectName("salaryLineEdit");

        gridLayout->addWidget(salaryLineEdit, 3, 3, 1, 1);

        hireDateEdit = new QDateEdit(formFrame);
        hireDateEdit->setObjectName("hireDateEdit");
        hireDateEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        gridLayout->addWidget(hireDateEdit, 1, 3, 1, 1);

        departmentLabel = new QLabel(formFrame);
        departmentLabel->setObjectName("departmentLabel");
        departmentLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(departmentLabel, 7, 2, 1, 1);

        emailLabel = new QLabel(formFrame);
        emailLabel->setObjectName("emailLabel");
        emailLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(emailLabel, 7, 0, 1, 1);

        empIdLineEdit = new QLineEdit(formFrame);
        empIdLineEdit->setObjectName("empIdLineEdit");

        gridLayout->addWidget(empIdLineEdit, 0, 1, 1, 1);

        positionComboBox = new QComboBox(formFrame);
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->addItem(QString());
        positionComboBox->setObjectName("positionComboBox");
        positionComboBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        gridLayout->addWidget(positionComboBox, 2, 3, 1, 1);

        statusComboBox = new QComboBox(formFrame);
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->setObjectName("statusComboBox");

        gridLayout->addWidget(statusComboBox, 4, 3, 1, 1);

        lastNameLineEdit = new QLineEdit(formFrame);
        lastNameLineEdit->setObjectName("lastNameLineEdit");

        gridLayout->addWidget(lastNameLineEdit, 2, 1, 1, 1);

        hireDateLabel = new QLabel(formFrame);
        hireDateLabel->setObjectName("hireDateLabel");
        hireDateLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(hireDateLabel, 1, 2, 1, 1);

        firstNameLineEdit = new QLineEdit(formFrame);
        firstNameLineEdit->setObjectName("firstNameLineEdit");

        gridLayout->addWidget(firstNameLineEdit, 1, 1, 1, 1);

        positionLabel = new QLabel(formFrame);
        positionLabel->setObjectName("positionLabel");
        positionLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(positionLabel, 2, 2, 1, 1);

        ageLabel = new QLabel(formFrame);
        ageLabel->setObjectName("ageLabel");
        ageLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(ageLabel, 4, 0, 1, 1);

        salaryLabel = new QLabel(formFrame);
        salaryLabel->setObjectName("salaryLabel");
        salaryLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(salaryLabel, 3, 2, 1, 1);

        passwordLabel = new QLabel(formFrame);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(passwordLabel, 0, 2, 1, 1);

        empIdLabel = new QLabel(formFrame);
        empIdLabel->setObjectName("empIdLabel");
        empIdLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(empIdLabel, 0, 0, 1, 1);

        statusLabel = new QLabel(formFrame);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        gridLayout->addWidget(statusLabel, 4, 2, 1, 1);

        phoneLineEdit = new QLineEdit(formFrame);
        phoneLineEdit->setObjectName("phoneLineEdit");

        gridLayout->addWidget(phoneLineEdit, 8, 1, 1, 1);


        formMainLayout->addWidget(formFrame);

        scrollArea->setWidget(scrollAreaWidgetContents);

        addTabLayout->addWidget(scrollArea);

        employeeTabWidget->addTab(addTab, icon7, QString());
        statisticsTab = new QWidget();
        statisticsTab->setObjectName("statisticsTab");
        statisticsLayout = new QVBoxLayout(statisticsTab);
        statisticsLayout->setObjectName("statisticsLayout");
        headerFrame = new QFrame(statisticsTab);
        headerFrame->setObjectName("headerFrame");
        headerFrame->setStyleSheet(QString::fromUtf8("background: #ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:18px;"));
        headerLayout = new QVBoxLayout(headerFrame);
        headerLayout->setObjectName("headerLayout");
        titleLabel = new QLabel(headerFrame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("font-size:24px; font-weight:600; color:#2c3e50;"));

        headerLayout->addWidget(titleLabel);


        statisticsLayout->addWidget(headerFrame);

        cardsContainer = new QFrame(statisticsTab);
        cardsContainer->setObjectName("cardsContainer");
        cardsContainer->setStyleSheet(QString::fromUtf8("background:transparent;"));
        cardsGrid = new QGridLayout(cardsContainer);
        cardsGrid->setObjectName("cardsGrid");
        totalEmployeesCard = new QFrame(cardsContainer);
        totalEmployeesCard->setObjectName("totalEmployeesCard");
        totalEmployeesCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        totalEmployeesLayout = new QVBoxLayout(totalEmployeesCard);
        totalEmployeesLayout->setObjectName("totalEmployeesLayout");
        totalEmployeesTitle = new QLabel(totalEmployeesCard);
        totalEmployeesTitle->setObjectName("totalEmployeesTitle");
        totalEmployeesTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        totalEmployeesLayout->addWidget(totalEmployeesTitle);

        totalEmployeesNumber = new QLabel(totalEmployeesCard);
        totalEmployeesNumber->setObjectName("totalEmployeesNumber");
        totalEmployeesNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #16a5b3;"));

        totalEmployeesLayout->addWidget(totalEmployeesNumber);


        cardsGrid->addWidget(totalEmployeesCard, 0, 0, 1, 1);

        activeEmployeesCard = new QFrame(cardsContainer);
        activeEmployeesCard->setObjectName("activeEmployeesCard");
        activeEmployeesCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        activeEmployeesLayout = new QVBoxLayout(activeEmployeesCard);
        activeEmployeesLayout->setObjectName("activeEmployeesLayout");
        activeEmployeesTitle = new QLabel(activeEmployeesCard);
        activeEmployeesTitle->setObjectName("activeEmployeesTitle");
        activeEmployeesTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        activeEmployeesLayout->addWidget(activeEmployeesTitle);

        activeEmployeesNumber = new QLabel(activeEmployeesCard);
        activeEmployeesNumber->setObjectName("activeEmployeesNumber");
        activeEmployeesNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #27ae60;"));

        activeEmployeesLayout->addWidget(activeEmployeesNumber);


        cardsGrid->addWidget(activeEmployeesCard, 0, 1, 1, 1);

        newEmployeesCard = new QFrame(cardsContainer);
        newEmployeesCard->setObjectName("newEmployeesCard");
        newEmployeesCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        newEmployeesLayout = new QVBoxLayout(newEmployeesCard);
        newEmployeesLayout->setObjectName("newEmployeesLayout");
        newEmployeesTitle = new QLabel(newEmployeesCard);
        newEmployeesTitle->setObjectName("newEmployeesTitle");
        newEmployeesTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        newEmployeesLayout->addWidget(newEmployeesTitle);

        newEmployeesNumber = new QLabel(newEmployeesCard);
        newEmployeesNumber->setObjectName("newEmployeesNumber");
        newEmployeesNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #e67e22;"));

        newEmployeesLayout->addWidget(newEmployeesNumber);


        cardsGrid->addWidget(newEmployeesCard, 0, 2, 1, 1);


        statisticsLayout->addWidget(cardsContainer);

        chartsContainer = new QFrame(statisticsTab);
        chartsContainer->setObjectName("chartsContainer");
        chartsContainer->setStyleSheet(QString::fromUtf8("background:transparent;"));
        chartsGrid = new QGridLayout(chartsContainer);
        chartsGrid->setObjectName("chartsGrid");
        employeeDepartmentChartFrame = new QFrame(chartsContainer);
        employeeDepartmentChartFrame->setObjectName("employeeDepartmentChartFrame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(employeeDepartmentChartFrame->sizePolicy().hasHeightForWidth());
        employeeDepartmentChartFrame->setSizePolicy(sizePolicy);
        employeeDepartmentChartFrame->setStyleSheet(QString::fromUtf8("background:#ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:12px;"));
        employeeDepartmentChartLayout = new QVBoxLayout(employeeDepartmentChartFrame);
        employeeDepartmentChartLayout->setObjectName("employeeDepartmentChartLayout");
        employeeDepartmentChartTitle = new QLabel(employeeDepartmentChartFrame);
        employeeDepartmentChartTitle->setObjectName("employeeDepartmentChartTitle");
        employeeDepartmentChartTitle->setStyleSheet(QString::fromUtf8("font-size:16px; font-weight:600; color:#2c3e50;"));

        employeeDepartmentChartLayout->addWidget(employeeDepartmentChartTitle);

        employeeDepartmentChartPlaceholder = new QLabel(employeeDepartmentChartFrame);
        employeeDepartmentChartPlaceholder->setObjectName("employeeDepartmentChartPlaceholder");
        employeeDepartmentChartPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:14px; padding:30px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));

        employeeDepartmentChartLayout->addWidget(employeeDepartmentChartPlaceholder);


        chartsGrid->addWidget(employeeDepartmentChartFrame, 0, 0, 1, 1);

        employeeStatusChartFrame = new QFrame(chartsContainer);
        employeeStatusChartFrame->setObjectName("employeeStatusChartFrame");
        sizePolicy.setHeightForWidth(employeeStatusChartFrame->sizePolicy().hasHeightForWidth());
        employeeStatusChartFrame->setSizePolicy(sizePolicy);
        employeeStatusChartFrame->setStyleSheet(QString::fromUtf8("background:#ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:12px;"));
        employeeStatusChartLayout = new QVBoxLayout(employeeStatusChartFrame);
        employeeStatusChartLayout->setObjectName("employeeStatusChartLayout");
        employeeStatusChartTitle = new QLabel(employeeStatusChartFrame);
        employeeStatusChartTitle->setObjectName("employeeStatusChartTitle");
        employeeStatusChartTitle->setStyleSheet(QString::fromUtf8("font-size:16px; font-weight:600; color:#2c3e50;"));

        employeeStatusChartLayout->addWidget(employeeStatusChartTitle);

        employeeStatusChartPlaceholder = new QLabel(employeeStatusChartFrame);
        employeeStatusChartPlaceholder->setObjectName("employeeStatusChartPlaceholder");
        employeeStatusChartPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:14px; padding:30px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));

        employeeStatusChartLayout->addWidget(employeeStatusChartPlaceholder);


        chartsGrid->addWidget(employeeStatusChartFrame, 0, 1, 1, 1);

        employeeSalaryChartFrame = new QFrame(chartsContainer);
        employeeSalaryChartFrame->setObjectName("employeeSalaryChartFrame");
        sizePolicy.setHeightForWidth(employeeSalaryChartFrame->sizePolicy().hasHeightForWidth());
        employeeSalaryChartFrame->setSizePolicy(sizePolicy);
        employeeSalaryChartFrame->setStyleSheet(QString::fromUtf8("background:#ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:12px;"));
        employeeSalaryChartLayout = new QVBoxLayout(employeeSalaryChartFrame);
        employeeSalaryChartLayout->setObjectName("employeeSalaryChartLayout");
        employeeSalaryChartTitle = new QLabel(employeeSalaryChartFrame);
        employeeSalaryChartTitle->setObjectName("employeeSalaryChartTitle");
        employeeSalaryChartTitle->setStyleSheet(QString::fromUtf8("font-size:16px; font-weight:600; color:#2c3e50;"));

        employeeSalaryChartLayout->addWidget(employeeSalaryChartTitle);

        employeeSalaryChartPlaceholder = new QLabel(employeeSalaryChartFrame);
        employeeSalaryChartPlaceholder->setObjectName("employeeSalaryChartPlaceholder");
        employeeSalaryChartPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:14px; padding:30px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));

        employeeSalaryChartLayout->addWidget(employeeSalaryChartPlaceholder);


        chartsGrid->addWidget(employeeSalaryChartFrame, 0, 2, 1, 1);


        statisticsLayout->addWidget(chartsContainer);

        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icons/statistic.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        employeeTabWidget->addTab(statisticsTab, icon9, QString());
        employeeLogsTab = new QWidget();
        employeeLogsTab->setObjectName("employeeLogsTab");
        employeeLogsLayout = new QVBoxLayout(employeeLogsTab);
        employeeLogsLayout->setObjectName("employeeLogsLayout");
        employeeLogsPlaceholder = new QLabel(employeeLogsTab);
        employeeLogsPlaceholder->setObjectName("employeeLogsPlaceholder");
        employeeLogsPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:16px; padding:50px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));
        employeeLogsPlaceholder->setAlignment(Qt::AlignmentFlag::AlignCenter);

        employeeLogsLayout->addWidget(employeeLogsPlaceholder);

        employeeTabWidget->addTab(employeeLogsTab, icon5, QString());

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
        memberSearchButton->setIcon(icon6);

        memberSearchLayout->addWidget(memberSearchButton);

        memberSearchSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        memberSearchLayout->addItem(memberSearchSpacer);

        memberSortButton = new QPushButton(memberSearchFrame);
        memberSortButton->setObjectName("memberSortButton");

        memberSearchLayout->addWidget(memberSortButton);

        memberExportButton = new QPushButton(memberSearchFrame);
        memberExportButton->setObjectName("memberExportButton");

        memberSearchLayout->addWidget(memberExportButton);


        memberListTabLayout->addWidget(memberSearchFrame);

        memberTable = new QTableWidget(memberListTab);
        if (memberTable->columnCount() < 10)
            memberTable->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(7, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(8, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        memberTable->setHorizontalHeaderItem(9, __qtablewidgetitem16);
        memberTable->setObjectName("memberTable");
        memberTable->setAlternatingRowColors(true);
        memberTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        memberListTabLayout->addWidget(memberTable);

        memberTabWidget->addTab(memberListTab, icon5, QString());
        memberAddTab = new QWidget();
        memberAddTab->setObjectName("memberAddTab");
        memberAddTabLayout = new QVBoxLayout(memberAddTab);
        memberAddTabLayout->setObjectName("memberAddTabLayout");
        memberScrollArea = new QScrollArea(memberAddTab);
        memberScrollArea->setObjectName("memberScrollArea");
        memberScrollArea->setWidgetResizable(true);
        memberScrollAreaContents = new QWidget();
        memberScrollAreaContents->setObjectName("memberScrollAreaContents");
        memberScrollAreaContents->setGeometry(QRect(0, 0, 1030, 857));
        memberFormMainLayout = new QVBoxLayout(memberScrollAreaContents);
        memberFormMainLayout->setObjectName("memberFormMainLayout");
        memberFormFrame = new QFrame(memberScrollAreaContents);
        memberFormFrame->setObjectName("memberFormFrame");
        memberFormLayout = new QGridLayout(memberFormFrame);
        memberFormLayout->setObjectName("memberFormLayout");
        memberFormLayout->setHorizontalSpacing(20);
        memberFormLayout->setVerticalSpacing(15);
        memberGenderLabel = new QLabel(memberFormFrame);
        memberGenderLabel->setObjectName("memberGenderLabel");
        memberGenderLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberGenderLabel, 4, 0, 1, 1);

        memberLastNameLineEdit = new QLineEdit(memberFormFrame);
        memberLastNameLineEdit->setObjectName("memberLastNameLineEdit");

        memberFormLayout->addWidget(memberLastNameLineEdit, 3, 1, 1, 1);

        memberFirstNameLineEdit = new QLineEdit(memberFormFrame);
        memberFirstNameLineEdit->setObjectName("memberFirstNameLineEdit");

        memberFormLayout->addWidget(memberFirstNameLineEdit, 2, 1, 1, 1);

        memberJoinDateEdit = new QDateEdit(memberFormFrame);
        memberJoinDateEdit->setObjectName("memberJoinDateEdit");
        memberJoinDateEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        memberFormLayout->addWidget(memberJoinDateEdit, 1, 3, 1, 1);

        memberJoinDateLabel = new QLabel(memberFormFrame);
        memberJoinDateLabel->setObjectName("memberJoinDateLabel");
        memberJoinDateLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberJoinDateLabel, 1, 2, 1, 1);

        memberFirstNameLabel = new QLabel(memberFormFrame);
        memberFirstNameLabel->setObjectName("memberFirstNameLabel");
        memberFirstNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberFirstNameLabel, 2, 0, 1, 1);

        memberIdLineEdit = new QLineEdit(memberFormFrame);
        memberIdLineEdit->setObjectName("memberIdLineEdit");

        memberFormLayout->addWidget(memberIdLineEdit, 1, 1, 1, 1);

        memberPhoneLabel = new QLabel(memberFormFrame);
        memberPhoneLabel->setObjectName("memberPhoneLabel");
        memberPhoneLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberPhoneLabel, 8, 0, 1, 1);

        memberGenderComboBox = new QComboBox(memberFormFrame);
        memberGenderComboBox->addItem(QString());
        memberGenderComboBox->addItem(QString());
        memberGenderComboBox->setObjectName("memberGenderComboBox");

        memberFormLayout->addWidget(memberGenderComboBox, 4, 1, 1, 1);

        memberEmailLabel = new QLabel(memberFormFrame);
        memberEmailLabel->setObjectName("memberEmailLabel");
        memberEmailLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberEmailLabel, 7, 0, 1, 1);

        memberPhoneLineEdit = new QLineEdit(memberFormFrame);
        memberPhoneLineEdit->setObjectName("memberPhoneLineEdit");

        memberFormLayout->addWidget(memberPhoneLineEdit, 8, 1, 1, 1);

        memberAgeLabel = new QLabel(memberFormFrame);
        memberAgeLabel->setObjectName("memberAgeLabel");
        memberAgeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberAgeLabel, 5, 0, 1, 1);

        memberAgeSpinBox = new QSpinBox(memberFormFrame);
        memberAgeSpinBox->setObjectName("memberAgeSpinBox");
        memberAgeSpinBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        memberAgeSpinBox->setMinimum(18);
        memberAgeSpinBox->setMaximum(65);
        memberAgeSpinBox->setValue(25);

        memberFormLayout->addWidget(memberAgeSpinBox, 5, 1, 1, 1);

        memberButtonFrame = new QFrame(memberFormFrame);
        memberButtonFrame->setObjectName("memberButtonFrame");
        memberButtonLayout = new QHBoxLayout(memberButtonFrame);
        memberButtonLayout->setObjectName("memberButtonLayout");
        buttonSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        memberButtonLayout->addItem(buttonSpacer_2);

        memberConfirmAddButton = new QPushButton(memberButtonFrame);
        memberConfirmAddButton->setObjectName("memberConfirmAddButton");
        memberConfirmAddButton->setMinimumSize(QSize(150, 45));
        memberConfirmAddButton->setIcon(icon7);

        memberButtonLayout->addWidget(memberConfirmAddButton);

        memberConfirmUpdateButton = new QPushButton(memberButtonFrame);
        memberConfirmUpdateButton->setObjectName("memberConfirmUpdateButton");
        memberConfirmUpdateButton->setMinimumSize(QSize(150, 45));
        memberConfirmUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));
        memberConfirmUpdateButton->setIcon(icon8);

        memberButtonLayout->addWidget(memberConfirmUpdateButton);


        memberFormLayout->addWidget(memberButtonFrame, 9, 0, 1, 4);

        memberLastNameLabel = new QLabel(memberFormFrame);
        memberLastNameLabel->setObjectName("memberLastNameLabel");
        memberLastNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberLastNameLabel, 3, 0, 1, 1);

        memberIdLabel = new QLabel(memberFormFrame);
        memberIdLabel->setObjectName("memberIdLabel");
        memberIdLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberIdLabel, 1, 0, 1, 1);

        memberEmailLineEdit = new QLineEdit(memberFormFrame);
        memberEmailLineEdit->setObjectName("memberEmailLineEdit");

        memberFormLayout->addWidget(memberEmailLineEdit, 7, 1, 1, 1);

        memberSubscriptionComboBox = new QComboBox(memberFormFrame);
        memberSubscriptionComboBox->addItem(QString());
        memberSubscriptionComboBox->addItem(QString());
        memberSubscriptionComboBox->addItem(QString());
        memberSubscriptionComboBox->setObjectName("memberSubscriptionComboBox");
        memberSubscriptionComboBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        memberFormLayout->addWidget(memberSubscriptionComboBox, 2, 3, 1, 1);

        memberSubscriptionLabel = new QLabel(memberFormFrame);
        memberSubscriptionLabel->setObjectName("memberSubscriptionLabel");
        memberSubscriptionLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        memberFormLayout->addWidget(memberSubscriptionLabel, 2, 2, 1, 1);

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
        memberUploadPhotoButton->setIcon(icon7);

        memberPhotoLayout->addWidget(memberUploadPhotoButton);


        memberFormLayout->addWidget(memberPhotoFrame, 4, 2, 4, 2);


        memberFormMainLayout->addWidget(memberFormFrame);

        memberScrollArea->setWidget(memberScrollAreaContents);

        memberAddTabLayout->addWidget(memberScrollArea);

        memberTabWidget->addTab(memberAddTab, icon7, QString());
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

        memberChartsContainer = new QFrame(memberStatsFrame);
        memberChartsContainer->setObjectName("memberChartsContainer");
        memberChartsContainer->setStyleSheet(QString::fromUtf8("background:transparent;"));
        memberChartsGrid = new QGridLayout(memberChartsContainer);
        memberChartsGrid->setObjectName("memberChartsGrid");
        memberGenderChartFrame = new QFrame(memberChartsContainer);
        memberGenderChartFrame->setObjectName("memberGenderChartFrame");
        memberGenderChartFrame->setStyleSheet(QString::fromUtf8("background:#ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:12px;"));
        memberGenderChartLayout = new QVBoxLayout(memberGenderChartFrame);
        memberGenderChartLayout->setObjectName("memberGenderChartLayout");
        memberGenderChartTitle = new QLabel(memberGenderChartFrame);
        memberGenderChartTitle->setObjectName("memberGenderChartTitle");
        memberGenderChartTitle->setStyleSheet(QString::fromUtf8("font-size:16px; font-weight:600; color:#2c3e50;"));

        memberGenderChartLayout->addWidget(memberGenderChartTitle);

        memberGenderChartPlaceholder = new QLabel(memberGenderChartFrame);
        memberGenderChartPlaceholder->setObjectName("memberGenderChartPlaceholder");
        memberGenderChartPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:14px; padding:28px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));

        memberGenderChartLayout->addWidget(memberGenderChartPlaceholder);


        memberChartsGrid->addWidget(memberGenderChartFrame, 0, 0, 1, 1);

        memberAgeChartFrame = new QFrame(memberChartsContainer);
        memberAgeChartFrame->setObjectName("memberAgeChartFrame");
        memberAgeChartFrame->setStyleSheet(QString::fromUtf8("background:#ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:12px;"));
        memberAgeChartLayout = new QVBoxLayout(memberAgeChartFrame);
        memberAgeChartLayout->setObjectName("memberAgeChartLayout");
        memberAgeChartTitle = new QLabel(memberAgeChartFrame);
        memberAgeChartTitle->setObjectName("memberAgeChartTitle");
        memberAgeChartTitle->setStyleSheet(QString::fromUtf8("font-size:16px; font-weight:600; color:#2c3e50;"));

        memberAgeChartLayout->addWidget(memberAgeChartTitle);

        memberAgeChartPlaceholder = new QLabel(memberAgeChartFrame);
        memberAgeChartPlaceholder->setObjectName("memberAgeChartPlaceholder");
        memberAgeChartPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:14px; padding:28px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));

        memberAgeChartLayout->addWidget(memberAgeChartPlaceholder);


        memberChartsGrid->addWidget(memberAgeChartFrame, 0, 1, 1, 1);

        memberSubscriptionChartFrame = new QFrame(memberChartsContainer);
        memberSubscriptionChartFrame->setObjectName("memberSubscriptionChartFrame");
        memberSubscriptionChartFrame->setStyleSheet(QString::fromUtf8("background:#ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:12px;"));
        memberSubscriptionChartLayout = new QVBoxLayout(memberSubscriptionChartFrame);
        memberSubscriptionChartLayout->setObjectName("memberSubscriptionChartLayout");
        memberSubscriptionChartTitle = new QLabel(memberSubscriptionChartFrame);
        memberSubscriptionChartTitle->setObjectName("memberSubscriptionChartTitle");
        memberSubscriptionChartTitle->setStyleSheet(QString::fromUtf8("font-size:16px; font-weight:600; color:#2c3e50;"));

        memberSubscriptionChartLayout->addWidget(memberSubscriptionChartTitle);

        memberSubscriptionChartPlaceholder = new QLabel(memberSubscriptionChartFrame);
        memberSubscriptionChartPlaceholder->setObjectName("memberSubscriptionChartPlaceholder");
        memberSubscriptionChartPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:14px; padding:28px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));

        memberSubscriptionChartLayout->addWidget(memberSubscriptionChartPlaceholder);


        memberChartsGrid->addWidget(memberSubscriptionChartFrame, 0, 2, 1, 1);


        memberStatsGridLayout->addWidget(memberChartsContainer, 1, 0, 1, 3);


        memberStatisticsLayout->addWidget(memberStatsFrame);

        memberTabWidget->addTab(memberStatisticsTab, icon9, QString());
        memberSMSTab = new QWidget();
        memberSMSTab->setObjectName("memberSMSTab");
        memberSMSTabLayout = new QVBoxLayout(memberSMSTab);
        memberSMSTabLayout->setObjectName("memberSMSTabLayout");
        emailPanel = new EmailPanel(memberSMSTab);
        emailPanel->setObjectName("emailPanel");

        memberSMSTabLayout->addWidget(emailPanel);

        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/icons/email.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        memberTabWidget->addTab(memberSMSTab, icon10, QString());
        memberOCRTab = new QWidget();
        memberOCRTab->setObjectName("memberOCRTab");
        memberOCRTabLayout = new QVBoxLayout(memberOCRTab);
        memberOCRTabLayout->setObjectName("memberOCRTabLayout");
        ocrInterface = new OCRInterface(memberOCRTab);
        ocrInterface->setObjectName("ocrInterface");

        memberOCRTabLayout->addWidget(ocrInterface);

        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/icons/ai-technology.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        memberTabWidget->addTab(memberOCRTab, icon11, QString());

        verticalLayout->addWidget(memberTabWidget);

        stackedWidget->addWidget(membersPage);
        equipmentPage = new QWidget();
        equipmentPage->setObjectName("equipmentPage");
        equipmentPageLayout = new QVBoxLayout(equipmentPage);
        equipmentPageLayout->setObjectName("equipmentPageLayout");
        equipmentPageTitle = new QLabel(equipmentPage);
        equipmentPageTitle->setObjectName("equipmentPageTitle");
        equipmentPageTitle->setStyleSheet(QString::fromUtf8("font-size: 28px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;"));

        equipmentPageLayout->addWidget(equipmentPageTitle);

        equipmentTabWidget = new QTabWidget(equipmentPage);
        equipmentTabWidget->setObjectName("equipmentTabWidget");
        equipmentListTab = new QWidget();
        equipmentListTab->setObjectName("equipmentListTab");
        equipmentListTabLayout = new QVBoxLayout(equipmentListTab);
        equipmentListTabLayout->setObjectName("equipmentListTabLayout");
        equipmentSearchFrame = new QFrame(equipmentListTab);
        equipmentSearchFrame->setObjectName("equipmentSearchFrame");
        equipmentSearchLayout = new QHBoxLayout(equipmentSearchFrame);
        equipmentSearchLayout->setObjectName("equipmentSearchLayout");
        equipmentSearchLineEdit = new QLineEdit(equipmentSearchFrame);
        equipmentSearchLineEdit->setObjectName("equipmentSearchLineEdit");

        equipmentSearchLayout->addWidget(equipmentSearchLineEdit);

        equipmentSearchButton = new QPushButton(equipmentSearchFrame);
        equipmentSearchButton->setObjectName("equipmentSearchButton");
        equipmentSearchButton->setIcon(icon6);

        equipmentSearchLayout->addWidget(equipmentSearchButton);

        equipmentSearchSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        equipmentSearchLayout->addItem(equipmentSearchSpacer);

        equipmentSortButton = new QPushButton(equipmentSearchFrame);
        equipmentSortButton->setObjectName("equipmentSortButton");
        equipmentSortButton->setIcon(icon5);

        equipmentSearchLayout->addWidget(equipmentSortButton);

        equipmentExportButton = new QPushButton(equipmentSearchFrame);
        equipmentExportButton->setObjectName("equipmentExportButton");
        equipmentExportButton->setIcon(icon4);

        equipmentSearchLayout->addWidget(equipmentExportButton);


        equipmentListTabLayout->addWidget(equipmentSearchFrame);

        equipmentTable = new QTableWidget(equipmentListTab);
        if (equipmentTable->columnCount() < 9)
            equipmentTable->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(3, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(4, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(5, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(6, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(7, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        equipmentTable->setHorizontalHeaderItem(8, __qtablewidgetitem25);
        equipmentTable->setObjectName("equipmentTable");
        equipmentTable->setAlternatingRowColors(true);
        equipmentTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        equipmentListTabLayout->addWidget(equipmentTable);

        equipmentTabWidget->addTab(equipmentListTab, icon5, QString());
        equipmentAddTab = new QWidget();
        equipmentAddTab->setObjectName("equipmentAddTab");
        equipmentAddTabLayout = new QVBoxLayout(equipmentAddTab);
        equipmentAddTabLayout->setObjectName("equipmentAddTabLayout");
        equipmentScrollArea = new QScrollArea(equipmentAddTab);
        equipmentScrollArea->setObjectName("equipmentScrollArea");
        equipmentScrollArea->setWidgetResizable(true);
        equipmentScrollAreaContents = new QWidget();
        equipmentScrollAreaContents->setObjectName("equipmentScrollAreaContents");
        equipmentScrollAreaContents->setGeometry(QRect(0, 0, 612, 371));
        equipmentFormMainLayout = new QVBoxLayout(equipmentScrollAreaContents);
        equipmentFormMainLayout->setObjectName("equipmentFormMainLayout");
        equipmentFormFrame = new QFrame(equipmentScrollAreaContents);
        equipmentFormFrame->setObjectName("equipmentFormFrame");
        equipmentFormLayout = new QGridLayout(equipmentFormFrame);
        equipmentFormLayout->setObjectName("equipmentFormLayout");
        equipmentFormLayout->setHorizontalSpacing(20);
        equipmentFormLayout->setVerticalSpacing(15);
        equipmentQuantityLabel = new QLabel(equipmentFormFrame);
        equipmentQuantityLabel->setObjectName("equipmentQuantityLabel");
        equipmentQuantityLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        equipmentFormLayout->addWidget(equipmentQuantityLabel, 3, 0, 1, 1);

        equipmentModelLineEdit = new QLineEdit(equipmentFormFrame);
        equipmentModelLineEdit->setObjectName("equipmentModelLineEdit");

        equipmentFormLayout->addWidget(equipmentModelLineEdit, 2, 1, 1, 1);

        equipmentNameLabel = new QLabel(equipmentFormFrame);
        equipmentNameLabel->setObjectName("equipmentNameLabel");
        equipmentNameLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        equipmentFormLayout->addWidget(equipmentNameLabel, 0, 0, 1, 1);

        equipmentCategoryComboBox = new QComboBox(equipmentFormFrame);
        equipmentCategoryComboBox->addItem(QString());
        equipmentCategoryComboBox->addItem(QString());
        equipmentCategoryComboBox->addItem(QString());
        equipmentCategoryComboBox->addItem(QString());
        equipmentCategoryComboBox->addItem(QString());
        equipmentCategoryComboBox->addItem(QString());
        equipmentCategoryComboBox->setObjectName("equipmentCategoryComboBox");

        equipmentFormLayout->addWidget(equipmentCategoryComboBox, 1, 1, 1, 1);

        equipmentCategoryLabel = new QLabel(equipmentFormFrame);
        equipmentCategoryLabel->setObjectName("equipmentCategoryLabel");
        equipmentCategoryLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        equipmentFormLayout->addWidget(equipmentCategoryLabel, 1, 0, 1, 1);

        equipmentBrandLabel = new QLabel(equipmentFormFrame);
        equipmentBrandLabel->setObjectName("equipmentBrandLabel");
        equipmentBrandLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        equipmentFormLayout->addWidget(equipmentBrandLabel, 0, 2, 1, 1);

        equipmentButtonFrame = new QFrame(equipmentFormFrame);
        equipmentButtonFrame->setObjectName("equipmentButtonFrame");
        equipmentButtonLayout = new QHBoxLayout(equipmentButtonFrame);
        equipmentButtonLayout->setObjectName("equipmentButtonLayout");
        equipmentButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        equipmentButtonLayout->addItem(equipmentButtonSpacer);

        equipmentConfirmButton = new QPushButton(equipmentButtonFrame);
        equipmentConfirmButton->setObjectName("equipmentConfirmButton");
        equipmentConfirmButton->setMinimumSize(QSize(150, 45));
        equipmentConfirmButton->setIcon(icon7);

        equipmentButtonLayout->addWidget(equipmentConfirmButton);

        equipmentUpdateButton = new QPushButton(equipmentButtonFrame);
        equipmentUpdateButton->setObjectName("equipmentUpdateButton");
        equipmentUpdateButton->setMinimumSize(QSize(150, 45));
        equipmentUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));
        equipmentUpdateButton->setIcon(icon8);

        equipmentButtonLayout->addWidget(equipmentUpdateButton);


        equipmentFormLayout->addWidget(equipmentButtonFrame, 5, 0, 1, 4);

        equipmentPurchaseDateLabel = new QLabel(equipmentFormFrame);
        equipmentPurchaseDateLabel->setObjectName("equipmentPurchaseDateLabel");
        equipmentPurchaseDateLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        equipmentFormLayout->addWidget(equipmentPurchaseDateLabel, 1, 2, 1, 1);

        equipmentQuantitySpinBox = new QSpinBox(equipmentFormFrame);
        equipmentQuantitySpinBox->setObjectName("equipmentQuantitySpinBox");
        equipmentQuantitySpinBox->setMinimum(1);
        equipmentQuantitySpinBox->setMaximum(999);
        equipmentQuantitySpinBox->setValue(1);

        equipmentFormLayout->addWidget(equipmentQuantitySpinBox, 3, 1, 1, 1);

        equipmentStatusLabel = new QLabel(equipmentFormFrame);
        equipmentStatusLabel->setObjectName("equipmentStatusLabel");
        equipmentStatusLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        equipmentFormLayout->addWidget(equipmentStatusLabel, 2, 2, 1, 1);

        equipmentStatusComboBox = new QComboBox(equipmentFormFrame);
        equipmentStatusComboBox->addItem(QString());
        equipmentStatusComboBox->addItem(QString());
        equipmentStatusComboBox->addItem(QString());
        equipmentStatusComboBox->addItem(QString());
        equipmentStatusComboBox->addItem(QString());
        equipmentStatusComboBox->setObjectName("equipmentStatusComboBox");

        equipmentFormLayout->addWidget(equipmentStatusComboBox, 2, 3, 1, 1);

        equipmentModelLabel = new QLabel(equipmentFormFrame);
        equipmentModelLabel->setObjectName("equipmentModelLabel");
        equipmentModelLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        equipmentFormLayout->addWidget(equipmentModelLabel, 2, 0, 1, 1);

        equipmentPurchaseDateEdit = new QDateEdit(equipmentFormFrame);
        equipmentPurchaseDateEdit->setObjectName("equipmentPurchaseDateEdit");
        equipmentPurchaseDateEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        equipmentPurchaseDateEdit->setCalendarPopup(true);

        equipmentFormLayout->addWidget(equipmentPurchaseDateEdit, 1, 3, 1, 1);

        equipmentNameLineEdit = new QLineEdit(equipmentFormFrame);
        equipmentNameLineEdit->setObjectName("equipmentNameLineEdit");

        equipmentFormLayout->addWidget(equipmentNameLineEdit, 0, 1, 1, 1);

        equipmentBrandLineEdit = new QLineEdit(equipmentFormFrame);
        equipmentBrandLineEdit->setObjectName("equipmentBrandLineEdit");

        equipmentFormLayout->addWidget(equipmentBrandLineEdit, 0, 3, 1, 1);

        equipmentPriceLineEdit = new QLineEdit(equipmentFormFrame);
        equipmentPriceLineEdit->setObjectName("equipmentPriceLineEdit");

        equipmentFormLayout->addWidget(equipmentPriceLineEdit, 3, 3, 1, 1);

        equipmentPriceLabel = new QLabel(equipmentFormFrame);
        equipmentPriceLabel->setObjectName("equipmentPriceLabel");
        equipmentPriceLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        equipmentFormLayout->addWidget(equipmentPriceLabel, 3, 2, 1, 1);


        equipmentFormMainLayout->addWidget(equipmentFormFrame);

        equipmentScrollArea->setWidget(equipmentScrollAreaContents);

        equipmentAddTabLayout->addWidget(equipmentScrollArea);

        equipmentTabWidget->addTab(equipmentAddTab, icon7, QString());
        equipmentStatisticsTab = new QWidget();
        equipmentStatisticsTab->setObjectName("equipmentStatisticsTab");
        equipmentStatisticsLayout = new QVBoxLayout(equipmentStatisticsTab);
        equipmentStatisticsLayout->setObjectName("equipmentStatisticsLayout");
        equipmentStatsFrame = new QFrame(equipmentStatisticsTab);
        equipmentStatsFrame->setObjectName("equipmentStatsFrame");
        equipmentStatsGridLayout = new QGridLayout(equipmentStatsFrame);
        equipmentStatsGridLayout->setObjectName("equipmentStatsGridLayout");
        totalEquipmentCard = new QFrame(equipmentStatsFrame);
        totalEquipmentCard->setObjectName("totalEquipmentCard");
        totalEquipmentCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        totalEquipmentLayout = new QVBoxLayout(totalEquipmentCard);
        totalEquipmentLayout->setObjectName("totalEquipmentLayout");
        totalEquipmentTitle = new QLabel(totalEquipmentCard);
        totalEquipmentTitle->setObjectName("totalEquipmentTitle");
        totalEquipmentTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        totalEquipmentLayout->addWidget(totalEquipmentTitle);

        totalEquipmentNumber = new QLabel(totalEquipmentCard);
        totalEquipmentNumber->setObjectName("totalEquipmentNumber");
        totalEquipmentNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #16a5b3;"));

        totalEquipmentLayout->addWidget(totalEquipmentNumber);


        equipmentStatsGridLayout->addWidget(totalEquipmentCard, 0, 0, 1, 1);

        availableEquipmentCard = new QFrame(equipmentStatsFrame);
        availableEquipmentCard->setObjectName("availableEquipmentCard");
        availableEquipmentCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        availableEquipmentLayout = new QVBoxLayout(availableEquipmentCard);
        availableEquipmentLayout->setObjectName("availableEquipmentLayout");
        availableEquipmentTitle = new QLabel(availableEquipmentCard);
        availableEquipmentTitle->setObjectName("availableEquipmentTitle");
        availableEquipmentTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        availableEquipmentLayout->addWidget(availableEquipmentTitle);

        availableEquipmentNumber = new QLabel(availableEquipmentCard);
        availableEquipmentNumber->setObjectName("availableEquipmentNumber");
        availableEquipmentNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #27ae60;"));

        availableEquipmentLayout->addWidget(availableEquipmentNumber);


        equipmentStatsGridLayout->addWidget(availableEquipmentCard, 0, 1, 1, 1);

        maintenanceEquipmentCard = new QFrame(equipmentStatsFrame);
        maintenanceEquipmentCard->setObjectName("maintenanceEquipmentCard");
        maintenanceEquipmentCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px; padding: 20px;"));
        maintenanceEquipmentLayout = new QVBoxLayout(maintenanceEquipmentCard);
        maintenanceEquipmentLayout->setObjectName("maintenanceEquipmentLayout");
        maintenanceEquipmentTitle = new QLabel(maintenanceEquipmentCard);
        maintenanceEquipmentTitle->setObjectName("maintenanceEquipmentTitle");
        maintenanceEquipmentTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; color: #7f8c8d; font-weight: 600;"));

        maintenanceEquipmentLayout->addWidget(maintenanceEquipmentTitle);

        maintenanceEquipmentNumber = new QLabel(maintenanceEquipmentCard);
        maintenanceEquipmentNumber->setObjectName("maintenanceEquipmentNumber");
        maintenanceEquipmentNumber->setStyleSheet(QString::fromUtf8("font-size: 36px; font-weight: bold; color: #e67e22;"));

        maintenanceEquipmentLayout->addWidget(maintenanceEquipmentNumber);


        equipmentStatsGridLayout->addWidget(maintenanceEquipmentCard, 0, 2, 1, 1);

        equipmentCategoryStatsFrame = new QFrame(equipmentStatsFrame);
        equipmentCategoryStatsFrame->setObjectName("equipmentCategoryStatsFrame");
        equipmentCategoryStatsFrame->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 12px;"));
        equipmentCategoryStatsLayout = new QVBoxLayout(equipmentCategoryStatsFrame);
        equipmentCategoryStatsLayout->setObjectName("equipmentCategoryStatsLayout");
        equipmentCategoryStatsTitle = new QLabel(equipmentCategoryStatsFrame);
        equipmentCategoryStatsTitle->setObjectName("equipmentCategoryStatsTitle");
        equipmentCategoryStatsTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;"));

        equipmentCategoryStatsLayout->addWidget(equipmentCategoryStatsTitle);

        equipmentCategoryStatsTable = new QTableWidget(equipmentCategoryStatsFrame);
        if (equipmentCategoryStatsTable->columnCount() < 5)
            equipmentCategoryStatsTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        equipmentCategoryStatsTable->setHorizontalHeaderItem(0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        equipmentCategoryStatsTable->setHorizontalHeaderItem(1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        equipmentCategoryStatsTable->setHorizontalHeaderItem(2, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        equipmentCategoryStatsTable->setHorizontalHeaderItem(3, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        equipmentCategoryStatsTable->setHorizontalHeaderItem(4, __qtablewidgetitem30);
        equipmentCategoryStatsTable->setObjectName("equipmentCategoryStatsTable");
        equipmentCategoryStatsTable->setAlternatingRowColors(true);

        equipmentCategoryStatsLayout->addWidget(equipmentCategoryStatsTable);


        equipmentStatsGridLayout->addWidget(equipmentCategoryStatsFrame, 1, 0, 1, 3);


        equipmentStatisticsLayout->addWidget(equipmentStatsFrame);

        equipmentTabWidget->addTab(equipmentStatisticsTab, icon9, QString());

        equipmentPageLayout->addWidget(equipmentTabWidget);

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
        activitySearchButton->setIcon(icon6);

        activitySearchLayout->addWidget(activitySearchButton);

        activitySearchSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        activitySearchLayout->addItem(activitySearchSpacer);

        activitySortComboBox = new QComboBox(activitySearchFrame);
        activitySortComboBox->addItem(QString());
        activitySortComboBox->addItem(QString());
        activitySortComboBox->addItem(QString());
        activitySortComboBox->setObjectName("activitySortComboBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(activitySortComboBox->sizePolicy().hasHeightForWidth());
        activitySortComboBox->setSizePolicy(sizePolicy1);
        activitySortComboBox->setStyleSheet(QString::fromUtf8("\n"
"QComboBox {\n"
"    background-color: rgba(22, 165, 179, 0.10);\n"
"    color: #2c3e50;\n"
"    border: 1.5px solid rgba(22, 165, 179, 0.65);\n"
"    padding: 8px 12px;\n"
"    border-radius: 6px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"    min-height: 24px;\n"
"}\n"
"QComboBox:hover {\n"
"    background-color: rgba(22, 165, 179, 0.15);\n"
"    border-color: #16a5b3;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 20px;\n"
"}\n"
"QComboBox::down-arrow {\n"
"    image: none;\n"
"    border-left: 4px solid transparent;\n"
"    border-right: 4px solid transparent;\n"
"    border-top: 6px solid #2c3e50;\n"
"    margin-right: 8px;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    background-color: white;\n"
"    border: 1px solid #e0e4e7;\n"
"    border-radius: 6px;\n"
"    padding: 4px;\n"
"    selection-background-color: rgba(22, 165, 179, 0.15);\n"
"}\n"
"                        "));

        activitySearchLayout->addWidget(activitySortComboBox);

        activityExportButton = new QPushButton(activitySearchFrame);
        activityExportButton->setObjectName("activityExportButton");

        activitySearchLayout->addWidget(activityExportButton);


        activityListTabLayout->addWidget(activitySearchFrame);

        activityTable = new QTableWidget(activityListTab);
        if (activityTable->columnCount() < 8)
            activityTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(1, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(2, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(3, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(4, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(5, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(6, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        activityTable->setHorizontalHeaderItem(7, __qtablewidgetitem38);
        activityTable->setObjectName("activityTable");
        activityTable->setAlternatingRowColors(true);
        activityTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        activityListTabLayout->addWidget(activityTable);

        activityTabWidget->addTab(activityListTab, icon5, QString());
        activityAddTab = new QWidget();
        activityAddTab->setObjectName("activityAddTab");
        activityAddTabLayout = new QVBoxLayout(activityAddTab);
        activityAddTabLayout->setObjectName("activityAddTabLayout");
        activityScrollArea = new QScrollArea(activityAddTab);
        activityScrollArea->setObjectName("activityScrollArea");
        activityScrollArea->setWidgetResizable(true);
        activityScrollAreaContents = new QWidget();
        activityScrollAreaContents->setObjectName("activityScrollAreaContents");
        activityScrollAreaContents->setGeometry(QRect(0, 0, 739, 493));
        activityFormMainLayout = new QVBoxLayout(activityScrollAreaContents);
        activityFormMainLayout->setObjectName("activityFormMainLayout");
        activityFormFrame = new QFrame(activityScrollAreaContents);
        activityFormFrame->setObjectName("activityFormFrame");
        activityFormLayout = new QGridLayout(activityFormFrame);
        activityFormLayout->setObjectName("activityFormLayout");
        activityFormLayout->setHorizontalSpacing(20);
        activityFormLayout->setVerticalSpacing(15);
        activityAgeSpinBox = new QSpinBox(activityFormFrame);
        activityAgeSpinBox->setObjectName("activityAgeSpinBox");
        activityAgeSpinBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        activityAgeSpinBox->setMinimum(0);
        activityAgeSpinBox->setMaximum(120);
        activityAgeSpinBox->setValue(18);

        activityFormLayout->addWidget(activityAgeSpinBox, 0, 1, 1, 1);

        activityButtonFrame = new QFrame(activityFormFrame);
        activityButtonFrame->setObjectName("activityButtonFrame");
        activityButtonLayout = new QHBoxLayout(activityButtonFrame);
        activityButtonLayout->setObjectName("activityButtonLayout");
        activityButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        activityButtonLayout->addItem(activityButtonSpacer);

        activityConfirmButton = new QPushButton(activityButtonFrame);
        activityConfirmButton->setObjectName("activityConfirmButton");
        activityConfirmButton->setMinimumSize(QSize(150, 45));
        activityConfirmButton->setIcon(icon7);

        activityButtonLayout->addWidget(activityConfirmButton);

        activityUpdateButton = new QPushButton(activityButtonFrame);
        activityUpdateButton->setObjectName("activityUpdateButton");
        activityUpdateButton->setMinimumSize(QSize(150, 45));
        activityUpdateButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));
        activityUpdateButton->setIcon(icon8);

        activityButtonLayout->addWidget(activityUpdateButton);


        activityFormLayout->addWidget(activityButtonFrame, 7, 0, 1, 7);

        eventTimeEdit = new QTimeEdit(activityFormFrame);
        eventTimeEdit->setObjectName("eventTimeEdit");
        eventTimeEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        activityFormLayout->addWidget(eventTimeEdit, 3, 3, 1, 3);

        activityDescriptionLabel = new QLabel(activityFormFrame);
        activityDescriptionLabel->setObjectName("activityDescriptionLabel");
        activityDescriptionLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityDescriptionLabel, 6, 0, 1, 1);

        activityAgeLabel = new QLabel(activityFormFrame);
        activityAgeLabel->setObjectName("activityAgeLabel");
        activityAgeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityAgeLabel, 0, 0, 1, 1);

        activityCapacityLabel = new QLabel(activityFormFrame);
        activityCapacityLabel->setObjectName("activityCapacityLabel");
        activityCapacityLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityCapacityLabel, 2, 0, 1, 1);

        activityDescriptionFrame = new QFrame(activityFormFrame);
        activityDescriptionFrame->setObjectName("activityDescriptionFrame");
        activityDescriptionLayout = new QVBoxLayout(activityDescriptionFrame);
        activityDescriptionLayout->setObjectName("activityDescriptionLayout");
        activityDescriptionTextEdit = new QTextEdit(activityDescriptionFrame);
        activityDescriptionTextEdit->setObjectName("activityDescriptionTextEdit");
        activityDescriptionTextEdit->setMaximumSize(QSize(16777215, 100));
        activityDescriptionTextEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        activityDescriptionLayout->addWidget(activityDescriptionTextEdit);


        activityFormLayout->addWidget(activityDescriptionFrame, 6, 1, 1, 6);

        responsibleWidget = new QWidget(activityFormFrame);
        responsibleWidget->setObjectName("responsibleWidget");
        responsibleLayout = new QHBoxLayout(responsibleWidget);
        responsibleLayout->setSpacing(8);
        responsibleLayout->setObjectName("responsibleLayout");
        responsibleLayout->setContentsMargins(0, 0, 0, 0);
        responsibleComboBox = new QComboBox(responsibleWidget);
        responsibleComboBox->addItem(QString());
        responsibleComboBox->setObjectName("responsibleComboBox");
        responsibleComboBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        responsibleComboBox->setEditable(false);

        responsibleLayout->addWidget(responsibleComboBox);

        responsibleLineEdit = new QLineEdit(responsibleWidget);
        responsibleLineEdit->setObjectName("responsibleLineEdit");
        responsibleLineEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        responsibleLayout->addWidget(responsibleLineEdit);

        responsibleToggleButton = new QPushButton(responsibleWidget);
        responsibleToggleButton->setObjectName("responsibleToggleButton");
        responsibleToggleButton->setMinimumSize(QSize(100, 40));
        responsibleToggleButton->setStyleSheet(QString::fromUtf8("background-color: #3498db; color: white; padding: 8px 12px; border-radius: 6px;"));

        responsibleLayout->addWidget(responsibleToggleButton);


        activityFormLayout->addWidget(responsibleWidget, 4, 1, 1, 2);

        activityCapacitySpinBox = new QSpinBox(activityFormFrame);
        activityCapacitySpinBox->setObjectName("activityCapacitySpinBox");
        activityCapacitySpinBox->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        activityCapacitySpinBox->setMinimum(1);
        activityCapacitySpinBox->setMaximum(500);
        activityCapacitySpinBox->setValue(30);

        activityFormLayout->addWidget(activityCapacitySpinBox, 2, 1, 1, 1);

        eventTimeLabel = new QLabel(activityFormFrame);
        eventTimeLabel->setObjectName("eventTimeLabel");
        eventTimeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(eventTimeLabel, 3, 2, 1, 1);

        responsibleLabel = new QLabel(activityFormFrame);
        responsibleLabel->setObjectName("responsibleLabel");
        responsibleLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(responsibleLabel, 4, 0, 1, 1);

        eventDateEdit = new QDateEdit(activityFormFrame);
        eventDateEdit->setObjectName("eventDateEdit");
        eventDateEdit->setStyleSheet(QString::fromUtf8("padding: 12px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));
        eventDateEdit->setCalendarPopup(true);

        activityFormLayout->addWidget(eventDateEdit, 3, 1, 1, 1);

        eventDateLabel = new QLabel(activityFormFrame);
        eventDateLabel->setObjectName("eventDateLabel");
        eventDateLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(eventDateLabel, 3, 0, 1, 1);

        activityStatusLabel = new QLabel(activityFormFrame);
        activityStatusLabel->setObjectName("activityStatusLabel");
        activityStatusLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityStatusLabel, 4, 3, 1, 1);

        activityStatusComboBox = new QComboBox(activityFormFrame);
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->addItem(QString());
        activityStatusComboBox->setObjectName("activityStatusComboBox");

        activityFormLayout->addWidget(activityStatusComboBox, 4, 4, 1, 2);

        activityTypeLabel = new QLabel(activityFormFrame);
        activityTypeLabel->setObjectName("activityTypeLabel");
        activityTypeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        activityFormLayout->addWidget(activityTypeLabel, 2, 2, 1, 1);

        activityTypeComboBox = new QComboBox(activityFormFrame);
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->addItem(QString());
        activityTypeComboBox->setObjectName("activityTypeComboBox");

        activityFormLayout->addWidget(activityTypeComboBox, 2, 3, 1, 3);


        activityFormMainLayout->addWidget(activityFormFrame);

        activityScrollArea->setWidget(activityScrollAreaContents);

        activityAddTabLayout->addWidget(activityScrollArea);

        activityTabWidget->addTab(activityAddTab, icon7, QString());
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

        activityChartsContainer = new QFrame(activityStatsFrame);
        activityChartsContainer->setObjectName("activityChartsContainer");
        activityChartsContainer->setStyleSheet(QString::fromUtf8("background:transparent;"));
        activityChartsGrid = new QGridLayout(activityChartsContainer);
        activityChartsGrid->setObjectName("activityChartsGrid");
        activityTypeChartFrame = new QFrame(activityChartsContainer);
        activityTypeChartFrame->setObjectName("activityTypeChartFrame");
        activityTypeChartFrame->setStyleSheet(QString::fromUtf8("background:#ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:12px;"));
        activityTypeChartLayout = new QVBoxLayout(activityTypeChartFrame);
        activityTypeChartLayout->setObjectName("activityTypeChartLayout");
        activityTypeChartTitle = new QLabel(activityTypeChartFrame);
        activityTypeChartTitle->setObjectName("activityTypeChartTitle");
        activityTypeChartTitle->setStyleSheet(QString::fromUtf8("font-size:16px; font-weight:600; color:#2c3e50;"));

        activityTypeChartLayout->addWidget(activityTypeChartTitle);

        activityTypeChartPlaceholder = new QLabel(activityTypeChartFrame);
        activityTypeChartPlaceholder->setObjectName("activityTypeChartPlaceholder");
        activityTypeChartPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:14px; padding:28px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));

        activityTypeChartLayout->addWidget(activityTypeChartPlaceholder);


        activityChartsGrid->addWidget(activityTypeChartFrame, 0, 0, 1, 1);

        activityAgeChartFrame = new QFrame(activityChartsContainer);
        activityAgeChartFrame->setObjectName("activityAgeChartFrame");
        activityAgeChartFrame->setStyleSheet(QString::fromUtf8("background:#ffffff; border:1px solid #e0e4e7; border-radius:16px; padding:12px;"));
        activityAgeChartLayout = new QVBoxLayout(activityAgeChartFrame);
        activityAgeChartLayout->setObjectName("activityAgeChartLayout");
        activityAgeChartTitle = new QLabel(activityAgeChartFrame);
        activityAgeChartTitle->setObjectName("activityAgeChartTitle");
        activityAgeChartTitle->setStyleSheet(QString::fromUtf8("font-size:16px; font-weight:600; color:#2c3e50;"));

        activityAgeChartLayout->addWidget(activityAgeChartTitle);

        activityAgeChartPlaceholder = new QLabel(activityAgeChartFrame);
        activityAgeChartPlaceholder->setObjectName("activityAgeChartPlaceholder");
        activityAgeChartPlaceholder->setStyleSheet(QString::fromUtf8("color:#95a5a6; font-size:14px; padding:28px; border:2px dashed #bdc3c7; border-radius:12px; text-align:center;"));

        activityAgeChartLayout->addWidget(activityAgeChartPlaceholder);


        activityChartsGrid->addWidget(activityAgeChartFrame, 0, 1, 1, 1);


        activityStatsGridLayout->addWidget(activityChartsContainer, 1, 0, 1, 3);


        activityStatisticsLayout->addWidget(activityStatsFrame);

        activityTabWidget->addTab(activityStatisticsTab, icon9, QString());
        activityCalendarTab = new QWidget();
        activityCalendarTab->setObjectName("activityCalendarTab");
        activityCalendarLayout = new QVBoxLayout(activityCalendarTab);
        activityCalendarLayout->setObjectName("activityCalendarLayout");
        activityCalendarPlaceholder = new QLabel(activityCalendarTab);
        activityCalendarPlaceholder->setObjectName("activityCalendarPlaceholder");
        activityCalendarPlaceholder->setAlignment(Qt::AlignmentFlag::AlignCenter);

        activityCalendarLayout->addWidget(activityCalendarPlaceholder);

        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/icons/calendar.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        activityTabWidget->addTab(activityCalendarTab, icon12, QString());

        activitiesPageLayout->addWidget(activityTabWidget);

        stackedWidget->addWidget(activitiesPage);
        paymentsPage = new QWidget();
        paymentsPage->setObjectName("paymentsPage");
        paymentsPageLayout = new QVBoxLayout(paymentsPage);
        paymentsPageLayout->setObjectName("paymentsPageLayout");
        paymentTabWidget = new QTabWidget(paymentsPage);
        paymentTabWidget->setObjectName("paymentTabWidget");
        listTab_4 = new QWidget();
        listTab_4->setObjectName("listTab_4");
        paymentListLayout = new QVBoxLayout(listTab_4);
        paymentListLayout->setObjectName("paymentListLayout");
        paymentSearchFrame = new QFrame(listTab_4);
        paymentSearchFrame->setObjectName("paymentSearchFrame");
        paymentSearchLayout = new QHBoxLayout(paymentSearchFrame);
        paymentSearchLayout->setObjectName("paymentSearchLayout");
        paymentSearchLineEdit = new QLineEdit(paymentSearchFrame);
        paymentSearchLineEdit->setObjectName("paymentSearchLineEdit");

        paymentSearchLayout->addWidget(paymentSearchLineEdit);

        paymentSearchButton = new QPushButton(paymentSearchFrame);
        paymentSearchButton->setObjectName("paymentSearchButton");
        paymentSearchButton->setIcon(icon6);

        paymentSearchLayout->addWidget(paymentSearchButton);

        paymentSearchSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        paymentSearchLayout->addItem(paymentSearchSpacer);

        paymentSortButton = new QPushButton(paymentSearchFrame);
        paymentSortButton->setObjectName("paymentSortButton");

        paymentSearchLayout->addWidget(paymentSortButton);

        paymentExportButton = new QPushButton(paymentSearchFrame);
        paymentExportButton->setObjectName("paymentExportButton");

        paymentSearchLayout->addWidget(paymentExportButton);


        paymentListLayout->addWidget(paymentSearchFrame);

        paymentTable = new QTableWidget(listTab_4);
        if (paymentTable->columnCount() < 9)
            paymentTable->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(1, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(2, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(3, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(4, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(5, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(6, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(7, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        paymentTable->setHorizontalHeaderItem(8, __qtablewidgetitem47);
        paymentTable->setObjectName("paymentTable");
        paymentTable->setAlternatingRowColors(true);
        paymentTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        paymentListLayout->addWidget(paymentTable);

        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icons/icons/employees.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        paymentTabWidget->addTab(listTab_4, icon13, QString());
        addTab_4 = new QWidget();
        addTab_4->setObjectName("addTab_4");
        addPaymentLayout = new QVBoxLayout(addTab_4);
        addPaymentLayout->setObjectName("addPaymentLayout");
        paymentScrollArea = new QScrollArea(addTab_4);
        paymentScrollArea->setObjectName("paymentScrollArea");
        paymentScrollArea->setWidgetResizable(true);
        paymentScrollContent = new QWidget();
        paymentScrollContent->setObjectName("paymentScrollContent");
        paymentScrollContent->setGeometry(QRect(0, 0, 573, 422));
        paymentFormMainLayout = new QVBoxLayout(paymentScrollContent);
        paymentFormMainLayout->setObjectName("paymentFormMainLayout");
        paymentFormFrame = new QFrame(paymentScrollContent);
        paymentFormFrame->setObjectName("paymentFormFrame");
        paymentFormFrame->setAutoFillBackground(false);
        paymentFormFrame->setStyleSheet(QString::fromUtf8("margin : 2px;"));
        paymentGridLayout = new QGridLayout(paymentFormFrame);
        paymentGridLayout->setObjectName("paymentGridLayout");
        paymentDescriptionEdit = new QLineEdit(paymentFormFrame);
        paymentDescriptionEdit->setObjectName("paymentDescriptionEdit");

        paymentGridLayout->addWidget(paymentDescriptionEdit, 1, 1, 1, 1);

        paymentAmountLabel = new QLabel(paymentFormFrame);
        paymentAmountLabel->setObjectName("paymentAmountLabel");
        paymentAmountLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        paymentGridLayout->addWidget(paymentAmountLabel, 2, 2, 1, 1);

        paymentTypeCombo = new QComboBox(paymentFormFrame);
        paymentTypeCombo->addItem(QString());
        paymentTypeCombo->addItem(QString());
        paymentTypeCombo->setObjectName("paymentTypeCombo");

        paymentGridLayout->addWidget(paymentTypeCombo, 0, 1, 1, 1);

        paymentTypeLabel = new QLabel(paymentFormFrame);
        paymentTypeLabel->setObjectName("paymentTypeLabel");
        paymentTypeLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        paymentGridLayout->addWidget(paymentTypeLabel, 0, 0, 1, 1);

        paymentDescriptionLabel = new QLabel(paymentFormFrame);
        paymentDescriptionLabel->setObjectName("paymentDescriptionLabel");
        paymentDescriptionLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        paymentGridLayout->addWidget(paymentDescriptionLabel, 1, 0, 1, 1);

        paymentAmountSpinBox = new QDoubleSpinBox(paymentFormFrame);
        paymentAmountSpinBox->setObjectName("paymentAmountSpinBox");
        paymentAmountSpinBox->setMaximum(999999.989999999990687);
        paymentAmountSpinBox->setSingleStep(0.010000000000000);

        paymentGridLayout->addWidget(paymentAmountSpinBox, 2, 1, 1, 1);

        paymentDateEdit = new QDateEdit(paymentFormFrame);
        paymentDateEdit->setObjectName("paymentDateEdit");
        paymentDateEdit->setCalendarPopup(true);
        paymentDateEdit->setDate(QDate(2025, 10, 8));

        paymentGridLayout->addWidget(paymentDateEdit, 2, 3, 1, 1);

        paymentMethodLabel = new QLabel(paymentFormFrame);
        paymentMethodLabel->setObjectName("paymentMethodLabel");
        paymentMethodLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        paymentGridLayout->addWidget(paymentMethodLabel, 3, 0, 1, 1);

        paymentMethodCombo = new QComboBox(paymentFormFrame);
        paymentMethodCombo->addItem(QString());
        paymentMethodCombo->addItem(QString());
        paymentMethodCombo->addItem(QString());
        paymentMethodCombo->addItem(QString());
        paymentMethodCombo->addItem(QString());
        paymentMethodCombo->addItem(QString());
        paymentMethodCombo->setObjectName("paymentMethodCombo");

        paymentGridLayout->addWidget(paymentMethodCombo, 3, 1, 1, 1);

        paymentCategoryLabel = new QLabel(paymentFormFrame);
        paymentCategoryLabel->setObjectName("paymentCategoryLabel");
        paymentCategoryLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        paymentGridLayout->addWidget(paymentCategoryLabel, 3, 2, 1, 1);

        paymentCategoryCombo = new QComboBox(paymentFormFrame);
        paymentCategoryCombo->addItem(QString());
        paymentCategoryCombo->addItem(QString());
        paymentCategoryCombo->addItem(QString());
        paymentCategoryCombo->addItem(QString());
        paymentCategoryCombo->addItem(QString());
        paymentCategoryCombo->addItem(QString());
        paymentCategoryCombo->addItem(QString());
        paymentCategoryCombo->setObjectName("paymentCategoryCombo");

        paymentGridLayout->addWidget(paymentCategoryCombo, 3, 3, 1, 1);

        paymentDateLabel = new QLabel(paymentFormFrame);
        paymentDateLabel->setObjectName("paymentDateLabel");
        paymentDateLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        paymentGridLayout->addWidget(paymentDateLabel, 2, 0, 1, 1);

        paymentMemberLabel = new QLabel(paymentFormFrame);
        paymentMemberLabel->setObjectName("paymentMemberLabel");
        paymentMemberLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        paymentGridLayout->addWidget(paymentMemberLabel, 4, 0, 1, 1);

        paymentMemberEdit = new QLineEdit(paymentFormFrame);
        paymentMemberEdit->setObjectName("paymentMemberEdit");

        paymentGridLayout->addWidget(paymentMemberEdit, 4, 1, 1, 1);

        paymentStatusLabel = new QLabel(paymentFormFrame);
        paymentStatusLabel->setObjectName("paymentStatusLabel");
        paymentStatusLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        paymentGridLayout->addWidget(paymentStatusLabel, 4, 2, 1, 1);

        paymentStatusCombo = new QComboBox(paymentFormFrame);
        paymentStatusCombo->addItem(QString());
        paymentStatusCombo->addItem(QString());
        paymentStatusCombo->addItem(QString());
        paymentStatusCombo->setObjectName("paymentStatusCombo");

        paymentGridLayout->addWidget(paymentStatusCombo, 4, 3, 1, 1);

        paymentButtonFrame = new QFrame(paymentFormFrame);
        paymentButtonFrame->setObjectName("paymentButtonFrame");
        paymentButtonLayout = new QHBoxLayout(paymentButtonFrame);
        paymentButtonLayout->setObjectName("paymentButtonLayout");
        paymentButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        paymentButtonLayout->addItem(paymentButtonSpacer);

        addPaymentButton = new QPushButton(paymentButtonFrame);
        addPaymentButton->setObjectName("addPaymentButton");
        addPaymentButton->setMinimumSize(QSize(150, 45));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icons/icons/plus.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addPaymentButton->setIcon(icon14);

        paymentButtonLayout->addWidget(addPaymentButton);

        clearPaymentFormButton = new QPushButton(paymentButtonFrame);
        clearPaymentFormButton->setObjectName("clearPaymentFormButton");
        clearPaymentFormButton->setMinimumSize(QSize(150, 45));
        clearPaymentFormButton->setStyleSheet(QString::fromUtf8("background-color: #f39c12;"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icons/icons/delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clearPaymentFormButton->setIcon(icon15);

        paymentButtonLayout->addWidget(clearPaymentFormButton);

        paymentButtonSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        paymentButtonLayout->addItem(paymentButtonSpacer2);


        paymentGridLayout->addWidget(paymentButtonFrame, 6, 0, 1, 4);


        paymentFormMainLayout->addWidget(paymentFormFrame);

        paymentScrollArea->setWidget(paymentScrollContent);

        addPaymentLayout->addWidget(paymentScrollArea);

        paymentTabWidget->addTab(addTab_4, icon14, QString());
        statisticsTab_4 = new QWidget();
        statisticsTab_4->setObjectName("statisticsTab_4");
        paymentStatsLayout = new QVBoxLayout(statisticsTab_4);
        paymentStatsLayout->setObjectName("paymentStatsLayout");
        paymentStatsScrollArea = new QScrollArea(statisticsTab_4);
        paymentStatsScrollArea->setObjectName("paymentStatsScrollArea");
        paymentStatsScrollArea->setWidgetResizable(true);
        paymentStatsScrollContent = new QWidget();
        paymentStatsScrollContent->setObjectName("paymentStatsScrollContent");
        paymentStatsScrollContent->setGeometry(QRect(0, 0, 629, 536));
        paymentStatsContentLayout = new QVBoxLayout(paymentStatsScrollContent);
        paymentStatsContentLayout->setObjectName("paymentStatsContentLayout");
        paymentSummaryFrame = new QFrame(paymentStatsScrollContent);
        paymentSummaryFrame->setObjectName("paymentSummaryFrame");
        paymentSummaryFrame->setStyleSheet(QString::fromUtf8("background: #ecf0f1; border: 1px solid #bdc3c7; border-radius: 5px; padding: 5px;"));
        paymentSummaryFrame->setFrameShape(QFrame::Shape::StyledPanel);
        paymentSummaryLayout = new QHBoxLayout(paymentSummaryFrame);
        paymentSummaryLayout->setSpacing(10);
        paymentSummaryLayout->setObjectName("paymentSummaryLayout");
        paymentSummaryLayout->setContentsMargins(5, 5, 5, 5);
        totalIncomeCard = new QFrame(paymentSummaryFrame);
        totalIncomeCard->setObjectName("totalIncomeCard");
        totalIncomeCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 16px; padding: 20px;"));
        totalIncomeLayout = new QVBoxLayout(totalIncomeCard);
        totalIncomeLayout->setObjectName("totalIncomeLayout");
        totalIncomeLabel = new QLabel(totalIncomeCard);
        totalIncomeLabel->setObjectName("totalIncomeLabel");
        totalIncomeLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 14px; color: #2c3e50;"));
        totalIncomeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        totalIncomeLayout->addWidget(totalIncomeLabel);

        totalIncomeValue = new QLabel(totalIncomeCard);
        totalIncomeValue->setObjectName("totalIncomeValue");
        totalIncomeValue->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #16a5b3;"));
        totalIncomeValue->setAlignment(Qt::AlignmentFlag::AlignCenter);

        totalIncomeLayout->addWidget(totalIncomeValue);


        paymentSummaryLayout->addWidget(totalIncomeCard);

        totalExpenseCard = new QFrame(paymentSummaryFrame);
        totalExpenseCard->setObjectName("totalExpenseCard");
        totalExpenseCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 16px; padding: 20px;"));
        totalExpenseLayout = new QVBoxLayout(totalExpenseCard);
        totalExpenseLayout->setObjectName("totalExpenseLayout");
        totalExpenseLabel = new QLabel(totalExpenseCard);
        totalExpenseLabel->setObjectName("totalExpenseLabel");
        totalExpenseLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 14px; color: #2c3e50;"));
        totalExpenseLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        totalExpenseLayout->addWidget(totalExpenseLabel);

        totalExpenseValue = new QLabel(totalExpenseCard);
        totalExpenseValue->setObjectName("totalExpenseValue");
        totalExpenseValue->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #16a5b3;"));
        totalExpenseValue->setAlignment(Qt::AlignmentFlag::AlignCenter);

        totalExpenseLayout->addWidget(totalExpenseValue);


        paymentSummaryLayout->addWidget(totalExpenseCard);

        netBalanceCard = new QFrame(paymentSummaryFrame);
        netBalanceCard->setObjectName("netBalanceCard");
        netBalanceCard->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 16px; padding: 20px;"));
        netBalanceLayout = new QVBoxLayout(netBalanceCard);
        netBalanceLayout->setObjectName("netBalanceLayout");
        netBalanceLabel = new QLabel(netBalanceCard);
        netBalanceLabel->setObjectName("netBalanceLabel");
        netBalanceLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 14px; color: #2c3e50;"));
        netBalanceLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        netBalanceLayout->addWidget(netBalanceLabel);

        netBalanceValue = new QLabel(netBalanceCard);
        netBalanceValue->setObjectName("netBalanceValue");
        netBalanceValue->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #16a5b3;"));
        netBalanceValue->setAlignment(Qt::AlignmentFlag::AlignCenter);

        netBalanceLayout->addWidget(netBalanceValue);


        paymentSummaryLayout->addWidget(netBalanceCard);


        paymentStatsContentLayout->addWidget(paymentSummaryFrame);

        paymentChartsFrame = new QFrame(paymentStatsScrollContent);
        paymentChartsFrame->setObjectName("paymentChartsFrame");
        paymentChartsFrame->setStyleSheet(QString::fromUtf8("background: #ecf0f1; border: 1px solid #bdc3c7; border-radius: 5px; padding: 5px;"));
        paymentChartsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        paymentChartsLayout = new QVBoxLayout(paymentChartsFrame);
        paymentChartsLayout->setSpacing(5);
        paymentChartsLayout->setObjectName("paymentChartsLayout");
        paymentChartsLayout->setContentsMargins(5, 5, 5, 5);
        paymentChartsTitle = new QLabel(paymentChartsFrame);
        paymentChartsTitle->setObjectName("paymentChartsTitle");
        paymentChartsTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #2c3e50;"));
        paymentChartsTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        paymentChartsLayout->addWidget(paymentChartsTitle);

        paymentMethodStatsTable = new QTableWidget(paymentChartsFrame);
        if (paymentMethodStatsTable->columnCount() < 4)
            paymentMethodStatsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        paymentMethodStatsTable->setHorizontalHeaderItem(0, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        paymentMethodStatsTable->setHorizontalHeaderItem(1, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        paymentMethodStatsTable->setHorizontalHeaderItem(2, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        paymentMethodStatsTable->setHorizontalHeaderItem(3, __qtablewidgetitem51);
        paymentMethodStatsTable->setObjectName("paymentMethodStatsTable");
        paymentMethodStatsTable->setMaximumSize(QSize(16777215, 200));
        paymentMethodStatsTable->setAlternatingRowColors(true);
        paymentMethodStatsTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        paymentChartsLayout->addWidget(paymentMethodStatsTable);


        paymentStatsContentLayout->addWidget(paymentChartsFrame);

        recentPaymentsFrame = new QFrame(paymentStatsScrollContent);
        recentPaymentsFrame->setObjectName("recentPaymentsFrame");
        recentPaymentsFrame->setStyleSheet(QString::fromUtf8("background: #ecf0f1; border: 1px solid #bdc3c7; border-radius: 5px; padding: 5px;"));
        recentPaymentsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        recentPaymentsLayout = new QVBoxLayout(recentPaymentsFrame);
        recentPaymentsLayout->setSpacing(5);
        recentPaymentsLayout->setObjectName("recentPaymentsLayout");
        recentPaymentsLayout->setContentsMargins(5, 5, 5, 5);
        recentPaymentsTitle = new QLabel(recentPaymentsFrame);
        recentPaymentsTitle->setObjectName("recentPaymentsTitle");
        recentPaymentsTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #2c3e50;"));
        recentPaymentsTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        recentPaymentsLayout->addWidget(recentPaymentsTitle);

        recentPaymentsTable = new QTableWidget(recentPaymentsFrame);
        if (recentPaymentsTable->columnCount() < 5)
            recentPaymentsTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        recentPaymentsTable->setHorizontalHeaderItem(0, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        recentPaymentsTable->setHorizontalHeaderItem(1, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        recentPaymentsTable->setHorizontalHeaderItem(2, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        recentPaymentsTable->setHorizontalHeaderItem(3, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        recentPaymentsTable->setHorizontalHeaderItem(4, __qtablewidgetitem56);
        recentPaymentsTable->setObjectName("recentPaymentsTable");
        recentPaymentsTable->setMaximumSize(QSize(16777215, 300));
        recentPaymentsTable->setAlternatingRowColors(true);
        recentPaymentsTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        recentPaymentsLayout->addWidget(recentPaymentsTable);


        paymentStatsContentLayout->addWidget(recentPaymentsFrame);

        paymentStatsScrollArea->setWidget(paymentStatsScrollContent);

        paymentStatsLayout->addWidget(paymentStatsScrollArea);

        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icons/icons/business-plan.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        paymentTabWidget->addTab(statisticsTab_4, icon16, QString());

        paymentsPageLayout->addWidget(paymentTabWidget);

        stackedWidget->addWidget(paymentsPage);
        settingsPage = new QWidget();
        settingsPage->setObjectName("settingsPage");
        settingsPageLayout = new QVBoxLayout(settingsPage);
        settingsPageLayout->setObjectName("settingsPageLayout");
        settingsPageTitle = new QLabel(settingsPage);
        settingsPageTitle->setObjectName("settingsPageTitle");
        settingsPageTitle->setStyleSheet(QString::fromUtf8("font-size: 28px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;"));

        settingsPageLayout->addWidget(settingsPageTitle);

        settingsScrollArea = new QScrollArea(settingsPage);
        settingsScrollArea->setObjectName("settingsScrollArea");
        settingsScrollArea->setWidgetResizable(true);
        settingsScrollAreaContents = new QWidget();
        settingsScrollAreaContents->setObjectName("settingsScrollAreaContents");
        settingsScrollAreaContents->setGeometry(QRect(0, 0, 642, 2011));
        settingsMainLayout = new QVBoxLayout(settingsScrollAreaContents);
        settingsMainLayout->setSpacing(20);
        settingsMainLayout->setObjectName("settingsMainLayout");
        userProfileFrame = new QFrame(settingsScrollAreaContents);
        userProfileFrame->setObjectName("userProfileFrame");
        userProfileFrame->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 16px; padding: 20px;"));
        userProfileLayout = new QVBoxLayout(userProfileFrame);
        userProfileLayout->setObjectName("userProfileLayout");
        userProfileTitle = new QLabel(userProfileFrame);
        userProfileTitle->setObjectName("userProfileTitle");
        userProfileTitle->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;"));

        userProfileLayout->addWidget(userProfileTitle);

        userProfileContentFrame = new QFrame(userProfileFrame);
        userProfileContentFrame->setObjectName("userProfileContentFrame");
        userProfileContentLayout = new QGridLayout(userProfileContentFrame);
        userProfileContentLayout->setObjectName("userProfileContentLayout");
        userProfileContentLayout->setHorizontalSpacing(20);
        userProfileContentLayout->setVerticalSpacing(15);
        profilePictureLabel = new QLabel(userProfileContentFrame);
        profilePictureLabel->setObjectName("profilePictureLabel");
        profilePictureLabel->setMinimumSize(QSize(100, 100));
        profilePictureLabel->setMaximumSize(QSize(100, 100));
        profilePictureLabel->setStyleSheet(QString::fromUtf8("border: 2px solid #16a5b3; border-radius: 50px; background-color: #f8f9fa;"));
        profilePictureLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        userProfileContentLayout->addWidget(profilePictureLabel, 0, 0, 1, 1);

        profileInfoFrame = new QFrame(userProfileContentFrame);
        profileInfoFrame->setObjectName("profileInfoFrame");
        profileInfoLayout = new QVBoxLayout(profileInfoFrame);
        profileInfoLayout->setObjectName("profileInfoLayout");
        currentUserNameLabel = new QLabel(profileInfoFrame);
        currentUserNameLabel->setObjectName("currentUserNameLabel");
        currentUserNameLabel->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: 600; color: #2c3e50;"));

        profileInfoLayout->addWidget(currentUserNameLabel);

        currentUserRoleLabel = new QLabel(profileInfoFrame);
        currentUserRoleLabel->setObjectName("currentUserRoleLabel");
        currentUserRoleLabel->setStyleSheet(QString::fromUtf8("font-size: 14px; color: #7f8c8d;"));

        profileInfoLayout->addWidget(currentUserRoleLabel);

        changeProfilePictureButton = new QPushButton(profileInfoFrame);
        changeProfilePictureButton->setObjectName("changeProfilePictureButton");
        changeProfilePictureButton->setMinimumSize(QSize(150, 32));
        changeProfilePictureButton->setMaximumSize(QSize(150, 32));
        changeProfilePictureButton->setIcon(icon7);

        profileInfoLayout->addWidget(changeProfilePictureButton);


        userProfileContentLayout->addWidget(profileInfoFrame, 0, 1, 1, 2);


        userProfileLayout->addWidget(userProfileContentFrame);


        settingsMainLayout->addWidget(userProfileFrame);

        securityFrame = new QFrame(settingsScrollAreaContents);
        securityFrame->setObjectName("securityFrame");
        securityFrame->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 16px; padding: 20px;"));
        securityLayout = new QVBoxLayout(securityFrame);
        securityLayout->setObjectName("securityLayout");
        securityTitle = new QLabel(securityFrame);
        securityTitle->setObjectName("securityTitle");
        securityTitle->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;"));

        securityLayout->addWidget(securityTitle);

        twoFactorFrame = new QFrame(securityFrame);
        twoFactorFrame->setObjectName("twoFactorFrame");
        twoFactorFrame->setStyleSheet(QString::fromUtf8("background-color: #f8f9fa; border: 1px solid #e9ecef; border-radius: 12px; padding: 16px;"));
        twoFactorLayout = new QHBoxLayout(twoFactorFrame);
        twoFactorLayout->setObjectName("twoFactorLayout");
        twoFactorInfoFrame = new QFrame(twoFactorFrame);
        twoFactorInfoFrame->setObjectName("twoFactorInfoFrame");
        twoFactorInfoLayout = new QVBoxLayout(twoFactorInfoFrame);
        twoFactorInfoLayout->setObjectName("twoFactorInfoLayout");
        twoFactorLabel = new QLabel(twoFactorInfoFrame);
        twoFactorLabel->setObjectName("twoFactorLabel");
        twoFactorLabel->setStyleSheet(QString::fromUtf8("font-size: 16px; font-weight: 600; color: #2c3e50;"));

        twoFactorInfoLayout->addWidget(twoFactorLabel);

        twoFactorDescription = new QLabel(twoFactorInfoFrame);
        twoFactorDescription->setObjectName("twoFactorDescription");
        twoFactorDescription->setStyleSheet(QString::fromUtf8("font-size: 14px; color: #6c757d; margin-top: 4px;"));
        twoFactorDescription->setWordWrap(true);

        twoFactorInfoLayout->addWidget(twoFactorDescription);


        twoFactorLayout->addWidget(twoFactorInfoFrame);

        twoFactorSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        twoFactorLayout->addItem(twoFactorSpacer);

        twoFactorControlsFrame = new QFrame(twoFactorFrame);
        twoFactorControlsFrame->setObjectName("twoFactorControlsFrame");
        twoFactorControlsLayout = new QVBoxLayout(twoFactorControlsFrame);
        twoFactorControlsLayout->setObjectName("twoFactorControlsLayout");
        twoFactorStatusLabel = new QLabel(twoFactorControlsFrame);
        twoFactorStatusLabel->setObjectName("twoFactorStatusLabel");
        twoFactorStatusLabel->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: 600; color: #dc3545;"));
        twoFactorStatusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        twoFactorControlsLayout->addWidget(twoFactorStatusLabel);

        setupTwoFactorButton = new QPushButton(twoFactorControlsFrame);
        setupTwoFactorButton->setObjectName("setupTwoFactorButton");
        setupTwoFactorButton->setMinimumSize(QSize(120, 40));
        setupTwoFactorButton->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #16a5b3, stop:1 #139aa6); color: white; border: none; padding: 10px 20px; border-radius: 8px; font-size: 14px; font-weight: 600;"));
        setupTwoFactorButton->setIcon(icon7);

        twoFactorControlsLayout->addWidget(setupTwoFactorButton);

        disableTwoFactorButton = new QPushButton(twoFactorControlsFrame);
        disableTwoFactorButton->setObjectName("disableTwoFactorButton");
        disableTwoFactorButton->setMinimumSize(QSize(120, 40));
        disableTwoFactorButton->setVisible(false);
        disableTwoFactorButton->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #dc3545, stop:1 #c82333); color: white; border: none; padding: 10px 20px; border-radius: 8px; font-size: 14px; font-weight: 600;"));

        twoFactorControlsLayout->addWidget(disableTwoFactorButton);


        twoFactorLayout->addWidget(twoFactorControlsFrame);


        securityLayout->addWidget(twoFactorFrame);

        passwordChangeFrame = new QFrame(securityFrame);
        passwordChangeFrame->setObjectName("passwordChangeFrame");
        passwordChangeFrame->setStyleSheet(QString::fromUtf8("background-color: #f8f9fa; border: 1px solid #e9ecef; border-radius: 12px; padding: 16px;"));
        passwordChangeLayout = new QVBoxLayout(passwordChangeFrame);
        passwordChangeLayout->setObjectName("passwordChangeLayout");
        passwordChangeTitle = new QLabel(passwordChangeFrame);
        passwordChangeTitle->setObjectName("passwordChangeTitle");
        passwordChangeTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; font-weight: 600; color: #2c3e50; margin-bottom: 10px;"));

        passwordChangeLayout->addWidget(passwordChangeTitle);

        passwordFieldsFrame = new QFrame(passwordChangeFrame);
        passwordFieldsFrame->setObjectName("passwordFieldsFrame");
        passwordFieldsLayout = new QGridLayout(passwordFieldsFrame);
        passwordFieldsLayout->setObjectName("passwordFieldsLayout");
        passwordFieldsLayout->setHorizontalSpacing(15);
        passwordFieldsLayout->setVerticalSpacing(10);
        currentPasswordLabel = new QLabel(passwordFieldsFrame);
        currentPasswordLabel->setObjectName("currentPasswordLabel");
        currentPasswordLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        passwordFieldsLayout->addWidget(currentPasswordLabel, 0, 0, 1, 1);

        currentPasswordLineEdit = new QLineEdit(passwordFieldsFrame);
        currentPasswordLineEdit->setObjectName("currentPasswordLineEdit");
        currentPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        passwordFieldsLayout->addWidget(currentPasswordLineEdit, 0, 1, 1, 1);

        newPasswordLabel = new QLabel(passwordFieldsFrame);
        newPasswordLabel->setObjectName("newPasswordLabel");
        newPasswordLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        passwordFieldsLayout->addWidget(newPasswordLabel, 1, 0, 1, 1);

        newPasswordLineEdit = new QLineEdit(passwordFieldsFrame);
        newPasswordLineEdit->setObjectName("newPasswordLineEdit");
        newPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        passwordFieldsLayout->addWidget(newPasswordLineEdit, 1, 1, 1, 1);

        confirmPasswordLabel = new QLabel(passwordFieldsFrame);
        confirmPasswordLabel->setObjectName("confirmPasswordLabel");
        confirmPasswordLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; color: #2c3e50;"));

        passwordFieldsLayout->addWidget(confirmPasswordLabel, 2, 0, 1, 1);

        confirmPasswordLineEdit = new QLineEdit(passwordFieldsFrame);
        confirmPasswordLineEdit->setObjectName("confirmPasswordLineEdit");
        confirmPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        passwordFieldsLayout->addWidget(confirmPasswordLineEdit, 2, 1, 1, 1);

        changePasswordButton = new QPushButton(passwordFieldsFrame);
        changePasswordButton->setObjectName("changePasswordButton");
        changePasswordButton->setMinimumSize(QSize(120, 36));
        changePasswordButton->setMaximumSize(QSize(120, 36));

        passwordFieldsLayout->addWidget(changePasswordButton, 3, 1, 1, 1);


        passwordChangeLayout->addWidget(passwordFieldsFrame);


        securityLayout->addWidget(passwordChangeFrame);


        settingsMainLayout->addWidget(securityFrame);

        appearanceFrame = new QFrame(settingsScrollAreaContents);
        appearanceFrame->setObjectName("appearanceFrame");
        appearanceFrame->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 16px; padding: 20px;"));
        appearanceLayout = new QVBoxLayout(appearanceFrame);
        appearanceLayout->setObjectName("appearanceLayout");
        appearanceTitle = new QLabel(appearanceFrame);
        appearanceTitle->setObjectName("appearanceTitle");
        appearanceTitle->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;"));

        appearanceLayout->addWidget(appearanceTitle);

        themeFrame = new QFrame(appearanceFrame);
        themeFrame->setObjectName("themeFrame");
        themeFrame->setStyleSheet(QString::fromUtf8("background-color: #f8f9fa; border: 1px solid #e9ecef; border-radius: 12px; padding: 16px;"));
        themeLayout = new QHBoxLayout(themeFrame);
        themeLayout->setObjectName("themeLayout");
        themeLabel = new QLabel(themeFrame);
        themeLabel->setObjectName("themeLabel");
        themeLabel->setStyleSheet(QString::fromUtf8("font-size: 16px; font-weight: 600; color: #2c3e50;"));

        themeLayout->addWidget(themeLabel);

        themeComboBox = new QComboBox(themeFrame);
        themeComboBox->addItem(QString());
        themeComboBox->addItem(QString());
        themeComboBox->addItem(QString());
        themeComboBox->setObjectName("themeComboBox");
        themeComboBox->setMinimumSize(QSize(150, 40));
        themeComboBox->setStyleSheet(QString::fromUtf8("padding: 10px; border: 2px solid #e0e4e7; border-radius: 8px; background-color: white;"));

        themeLayout->addWidget(themeComboBox);

        themeSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        themeLayout->addItem(themeSpacer);

        applyThemeButton = new QPushButton(themeFrame);
        applyThemeButton->setObjectName("applyThemeButton");
        applyThemeButton->setMinimumSize(QSize(100, 40));

        themeLayout->addWidget(applyThemeButton);


        appearanceLayout->addWidget(themeFrame);


        settingsMainLayout->addWidget(appearanceFrame);

        preferencesFrame = new QFrame(settingsScrollAreaContents);
        preferencesFrame->setObjectName("preferencesFrame");
        preferencesFrame->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid #e0e4e7; border-radius: 16px; padding: 20px;"));
        preferencesLayout = new QVBoxLayout(preferencesFrame);
        preferencesLayout->setObjectName("preferencesLayout");
        preferencesTitle = new QLabel(preferencesFrame);
        preferencesTitle->setObjectName("preferencesTitle");
        preferencesTitle->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;"));

        preferencesLayout->addWidget(preferencesTitle);

        preferencesContentFrame = new QFrame(preferencesFrame);
        preferencesContentFrame->setObjectName("preferencesContentFrame");
        preferencesContentFrame->setStyleSheet(QString::fromUtf8("background-color: #f8f9fa; border: 1px solid #e9ecef; border-radius: 12px; padding: 16px;"));
        preferencesContentLayout = new QVBoxLayout(preferencesContentFrame);
        preferencesContentLayout->setObjectName("preferencesContentLayout");
        autoRefreshCheckBox = new QCheckBox(preferencesContentFrame);
        autoRefreshCheckBox->setObjectName("autoRefreshCheckBox");
        autoRefreshCheckBox->setStyleSheet(QString::fromUtf8("font-size: 14px; color: #2c3e50;"));
        autoRefreshCheckBox->setChecked(true);

        preferencesContentLayout->addWidget(autoRefreshCheckBox);

        notificationsCheckBox = new QCheckBox(preferencesContentFrame);
        notificationsCheckBox->setObjectName("notificationsCheckBox");
        notificationsCheckBox->setStyleSheet(QString::fromUtf8("font-size: 14px; color: #2c3e50;"));
        notificationsCheckBox->setChecked(true);

        preferencesContentLayout->addWidget(notificationsCheckBox);

        soundCheckBox = new QCheckBox(preferencesContentFrame);
        soundCheckBox->setObjectName("soundCheckBox");
        soundCheckBox->setStyleSheet(QString::fromUtf8("font-size: 14px; color: #2c3e50;"));

        preferencesContentLayout->addWidget(soundCheckBox);


        preferencesLayout->addWidget(preferencesContentFrame);


        settingsMainLayout->addWidget(preferencesFrame);

        settingsVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        settingsMainLayout->addItem(settingsVerticalSpacer);

        settingsScrollArea->setWidget(settingsScrollAreaContents);

        settingsPageLayout->addWidget(settingsScrollArea);

        stackedWidget->addWidget(settingsPage);

        mainContentLayout->addWidget(stackedWidget);


        mainHorizontalLayout->addWidget(mainContentFrame);


        verticalLayout_main->addWidget(mainFrame);

        EmployerAdmin->setCentralWidget(centralwidget);

        retranslateUi(EmployerAdmin);

        stackedWidget->setCurrentIndex(1);
        employeeTabWidget->setCurrentIndex(2);
        memberTabWidget->setCurrentIndex(4);
        equipmentTabWidget->setCurrentIndex(1);
        activityTabWidget->setCurrentIndex(0);
        paymentTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EmployerAdmin);
    } // setupUi

    void retranslateUi(QMainWindow *EmployerAdmin)
    {
        EmployerAdmin->setWindowTitle(QCoreApplication::translate("EmployerAdmin", "VIBRA CLUB - Application Management", nullptr));
        logo->setText(QString());
        logoLabel->setText(QCoreApplication::translate("EmployerAdmin", "VIBRA CLUB", nullptr));
        userAvatarLabel->setText(QCoreApplication::translate("EmployerAdmin", "KC", nullptr));
        userNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "Khalil Cherif", nullptr));
        userRoleLabel->setText(QCoreApplication::translate("EmployerAdmin", "Employee Manager", nullptr));
        navigationTitle->setText(QCoreApplication::translate("EmployerAdmin", "Navigation", nullptr));
        employeesButton->setText(QCoreApplication::translate("EmployerAdmin", "  Employees", nullptr));
        membersButton->setText(QCoreApplication::translate("EmployerAdmin", "  Members", nullptr));
        equipmentButton->setText(QCoreApplication::translate("EmployerAdmin", "  Equipment", nullptr));
        activitiesButton->setText(QCoreApplication::translate("EmployerAdmin", "  Activities", nullptr));
        paymentsButton->setText(QCoreApplication::translate("EmployerAdmin", "Transaction", nullptr));
        settingsButton->setText(QCoreApplication::translate("EmployerAdmin", "  Settings", nullptr));
        logoutButton->setText(QCoreApplication::translate("EmployerAdmin", "  Logout", nullptr));
        pageTitle->setText(QCoreApplication::translate("EmployerAdmin", "Employee Management", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Search employees...", nullptr));
        employeeSearchButton->setText(QCoreApplication::translate("EmployerAdmin", "Search", nullptr));
        employeeSortButton->setText(QCoreApplication::translate("EmployerAdmin", "Sort by Hire Date", nullptr));
        employeeExportButton->setText(QCoreApplication::translate("EmployerAdmin", "Export PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem = employeeTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EmployerAdmin", "CIN", nullptr));
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
        photoLabel->setText(QCoreApplication::translate("EmployerAdmin", " Upload Employee Photo", nullptr));
        employeeUploadPhotoButton->setText(QCoreApplication::translate("EmployerAdmin", "Choose File", nullptr));
        firstNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "First Name:", nullptr));
        departmentComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Activity Management", nullptr));
        departmentComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Member Management", nullptr));
        departmentComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Equipment Management", nullptr));
        departmentComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Payment Management", nullptr));
        departmentComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "General Administration", nullptr));

        passwordLineEedit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter password", nullptr));
        genderComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Male", nullptr));
        genderComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Female", nullptr));

        phoneLabel->setText(QCoreApplication::translate("EmployerAdmin", "Phone Number:", nullptr));
        confirmAddButton->setText(QCoreApplication::translate("EmployerAdmin", "Confirm Add", nullptr));
        confirmUpdateButton->setText(QCoreApplication::translate("EmployerAdmin", "Confirm Update", nullptr));
        genderLabel->setText(QCoreApplication::translate("EmployerAdmin", "Gender:", nullptr));
        lastNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "Last Name:", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "employee@esprit.tn", nullptr));
        salaryLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter salary amount", nullptr));
        departmentLabel->setText(QCoreApplication::translate("EmployerAdmin", "Department:", nullptr));
        emailLabel->setText(QCoreApplication::translate("EmployerAdmin", "Email:", nullptr));
        empIdLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "e.g., 14471254", nullptr));
        positionComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Manager", nullptr));
        positionComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Assistant Manager", nullptr));
        positionComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Instructor", nullptr));
        positionComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Personal Trainer", nullptr));
        positionComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Receptionist", nullptr));
        positionComboBox->setItemText(5, QCoreApplication::translate("EmployerAdmin", "Maintenance Staff", nullptr));
        positionComboBox->setItemText(6, QCoreApplication::translate("EmployerAdmin", "Security Guard", nullptr));
        positionComboBox->setItemText(7, QCoreApplication::translate("EmployerAdmin", "Cleaning Staff", nullptr));
        positionComboBox->setItemText(8, QCoreApplication::translate("EmployerAdmin", "IT Support", nullptr));
        positionComboBox->setItemText(9, QCoreApplication::translate("EmployerAdmin", "Accountant", nullptr));
        positionComboBox->setItemText(10, QCoreApplication::translate("EmployerAdmin", "Other", nullptr));

        statusComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Active", nullptr));
        statusComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Inactive", nullptr));
        statusComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "On Leave", nullptr));

        lastNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter last name", nullptr));
        hireDateLabel->setText(QCoreApplication::translate("EmployerAdmin", "Hire Date:", nullptr));
        firstNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter first name", nullptr));
        positionLabel->setText(QCoreApplication::translate("EmployerAdmin", "Position:", nullptr));
        ageLabel->setText(QCoreApplication::translate("EmployerAdmin", "Age:", nullptr));
        salaryLabel->setText(QCoreApplication::translate("EmployerAdmin", "Salary:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("EmployerAdmin", "Password", nullptr));
        empIdLabel->setText(QCoreApplication::translate("EmployerAdmin", "CIN :", nullptr));
        statusLabel->setText(QCoreApplication::translate("EmployerAdmin", "Status:", nullptr));
        phoneLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "+216 55 123 456", nullptr));
        employeeTabWidget->setTabText(employeeTabWidget->indexOf(addTab), QCoreApplication::translate("EmployerAdmin", " Add Employee", nullptr));
        titleLabel->setText(QCoreApplication::translate("EmployerAdmin", "Employee Statistics Dashboard", nullptr));
        totalEmployeesTitle->setText(QCoreApplication::translate("EmployerAdmin", "Total Employees", nullptr));
        totalEmployeesNumber->setText(QCoreApplication::translate("EmployerAdmin", "\342\200\224", nullptr));
        activeEmployeesTitle->setText(QCoreApplication::translate("EmployerAdmin", "Active Employees", nullptr));
        activeEmployeesNumber->setText(QCoreApplication::translate("EmployerAdmin", "\342\200\224", nullptr));
        newEmployeesTitle->setText(QCoreApplication::translate("EmployerAdmin", "New This Month", nullptr));
        newEmployeesNumber->setText(QCoreApplication::translate("EmployerAdmin", "\342\200\224", nullptr));
        employeeDepartmentChartTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\217\242 Department Distribution", nullptr));
        employeeDepartmentChartPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "Pie Chart Placeholder", nullptr));
        employeeStatusChartTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\212 Status Distribution", nullptr));
        employeeStatusChartPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "Histogram Placeholder", nullptr));
        employeeSalaryChartTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\222\260 Salary Distribution (Cumulative Curve)", nullptr));
        employeeSalaryChartPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "ECC Curve Placeholder", nullptr));
        employeeTabWidget->setTabText(employeeTabWidget->indexOf(statisticsTab), QCoreApplication::translate("EmployerAdmin", " Statistics", nullptr));
        employeeLogsPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\213 Employee Logs Panel\n"
"                     \n"
"This panel will be implemented programmatically in C++\n"
"Advanced audit logging system with dashboard, filters, and analytics", nullptr));
        employeeTabWidget->setTabText(employeeTabWidget->indexOf(employeeLogsTab), QCoreApplication::translate("EmployerAdmin", " Employee Logs", nullptr));
        memberPageTitle->setText(QCoreApplication::translate("EmployerAdmin", "Member Management", nullptr));
        memberSearchLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Search members...", nullptr));
        memberSearchButton->setText(QCoreApplication::translate("EmployerAdmin", "Search", nullptr));
        memberSortButton->setText(QCoreApplication::translate("EmployerAdmin", "Sort by Join Date", nullptr));
        memberExportButton->setText(QCoreApplication::translate("EmployerAdmin", "Export PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = memberTable->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("EmployerAdmin", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = memberTable->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("EmployerAdmin", "First Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = memberTable->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("EmployerAdmin", "Last Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = memberTable->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("EmployerAdmin", "Gender", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = memberTable->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("EmployerAdmin", "Age", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = memberTable->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("EmployerAdmin", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = memberTable->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("EmployerAdmin", "Phone Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = memberTable->horizontalHeaderItem(7);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("EmployerAdmin", "Subscription Plan", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = memberTable->horizontalHeaderItem(8);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("EmployerAdmin", "Join Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = memberTable->horizontalHeaderItem(9);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("EmployerAdmin", "Actions", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberListTab), QCoreApplication::translate("EmployerAdmin", " List of Members", nullptr));
        memberGenderLabel->setText(QCoreApplication::translate("EmployerAdmin", "Gender:", nullptr));
        memberLastNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter last name", nullptr));
        memberFirstNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter first name", nullptr));
        memberJoinDateLabel->setText(QCoreApplication::translate("EmployerAdmin", "Join Date:", nullptr));
        memberFirstNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "First Name:", nullptr));
        memberIdLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "e.g., MEM001", nullptr));
        memberPhoneLabel->setText(QCoreApplication::translate("EmployerAdmin", "Phone Number:", nullptr));
        memberGenderComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Male", nullptr));
        memberGenderComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Female", nullptr));

        memberEmailLabel->setText(QCoreApplication::translate("EmployerAdmin", "Email:", nullptr));
        memberPhoneLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "+216 55 123 456", nullptr));
        memberAgeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Age:", nullptr));
        memberConfirmAddButton->setText(QCoreApplication::translate("EmployerAdmin", "Confirm Add", nullptr));
        memberConfirmUpdateButton->setText(QCoreApplication::translate("EmployerAdmin", "Confirm Update", nullptr));
        memberLastNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "Last Name:", nullptr));
        memberIdLabel->setText(QCoreApplication::translate("EmployerAdmin", "CIN :", nullptr));
        memberEmailLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "member@example.com", nullptr));
        memberSubscriptionComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Monthly", nullptr));
        memberSubscriptionComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Weekly", nullptr));
        memberSubscriptionComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Daily", nullptr));

        memberSubscriptionLabel->setText(QCoreApplication::translate("EmployerAdmin", "Subscription Plan:", nullptr));
        memberPhotoLabel->setText(QCoreApplication::translate("EmployerAdmin", "Upload Member Photo", nullptr));
        memberUploadPhotoButton->setText(QCoreApplication::translate("EmployerAdmin", "Choose File", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberAddTab), QCoreApplication::translate("EmployerAdmin", " Add Member", nullptr));
        totalMembersTitle->setText(QCoreApplication::translate("EmployerAdmin", "Total Members", nullptr));
        totalMembersNumber->setText(QCoreApplication::translate("EmployerAdmin", "\342\200\224", nullptr));
        activeMembersTitle->setText(QCoreApplication::translate("EmployerAdmin", "Active Members", nullptr));
        activeMembersNumber->setText(QCoreApplication::translate("EmployerAdmin", "\342\200\224", nullptr));
        newMembersTitle->setText(QCoreApplication::translate("EmployerAdmin", "New Members (This Month)", nullptr));
        newMembersNumber->setText(QCoreApplication::translate("EmployerAdmin", "\342\200\224", nullptr));
        memberGenderChartTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\247\254 Gender Distribution", nullptr));
        memberGenderChartPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "Pie Chart Placeholder", nullptr));
        memberAgeChartTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\212 Age Distribution (Groups)", nullptr));
        memberAgeChartPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "Bar Chart Placeholder", nullptr));
        memberSubscriptionChartTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\246 Subscription Plan Histogram", nullptr));
        memberSubscriptionChartPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "Histogram Placeholder", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberStatisticsTab), QCoreApplication::translate("EmployerAdmin", " Statistics", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberSMSTab), QCoreApplication::translate("EmployerAdmin", " Email Communications", nullptr));
        memberTabWidget->setTabText(memberTabWidget->indexOf(memberOCRTab), QCoreApplication::translate("EmployerAdmin", " ID Card OCR", nullptr));
        equipmentPageTitle->setText(QCoreApplication::translate("EmployerAdmin", "Equipment Management", nullptr));
        equipmentSearchLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Search equipment...", nullptr));
        equipmentSearchButton->setText(QCoreApplication::translate("EmployerAdmin", " Search", nullptr));
        equipmentSortButton->setText(QCoreApplication::translate("EmployerAdmin", "Sort by Name", nullptr));
        equipmentExportButton->setText(QCoreApplication::translate("EmployerAdmin", "Export PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = equipmentTable->horizontalHeaderItem(0);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("EmployerAdmin", "Equipment ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = equipmentTable->horizontalHeaderItem(1);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("EmployerAdmin", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = equipmentTable->horizontalHeaderItem(2);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("EmployerAdmin", "Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = equipmentTable->horizontalHeaderItem(3);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("EmployerAdmin", "Total Stock", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = equipmentTable->horizontalHeaderItem(4);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("EmployerAdmin", "Available", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = equipmentTable->horizontalHeaderItem(5);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("EmployerAdmin", "In Use", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = equipmentTable->horizontalHeaderItem(6);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("EmployerAdmin", "Under Maintenance", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = equipmentTable->horizontalHeaderItem(7);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("EmployerAdmin", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = equipmentTable->horizontalHeaderItem(8);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("EmployerAdmin", "Actions", nullptr));
        equipmentTabWidget->setTabText(equipmentTabWidget->indexOf(equipmentListTab), QCoreApplication::translate("EmployerAdmin", " List of Equipment", nullptr));
        equipmentQuantityLabel->setText(QCoreApplication::translate("EmployerAdmin", "Total Quantity:", nullptr));
        equipmentModelLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter model number", nullptr));
        equipmentNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "Equipment Name:", nullptr));
        equipmentCategoryComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Cardio", nullptr));
        equipmentCategoryComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Strength Training", nullptr));
        equipmentCategoryComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Free Weights", nullptr));
        equipmentCategoryComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Functional Training", nullptr));
        equipmentCategoryComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Accessories", nullptr));
        equipmentCategoryComboBox->setItemText(5, QCoreApplication::translate("EmployerAdmin", "Safety Equipment", nullptr));

        equipmentCategoryLabel->setText(QCoreApplication::translate("EmployerAdmin", "Category:", nullptr));
        equipmentBrandLabel->setText(QCoreApplication::translate("EmployerAdmin", "Brand:", nullptr));
        equipmentConfirmButton->setText(QCoreApplication::translate("EmployerAdmin", " Confirm Add Equipment", nullptr));
        equipmentUpdateButton->setText(QCoreApplication::translate("EmployerAdmin", " Update Equipment", nullptr));
        equipmentPurchaseDateLabel->setText(QCoreApplication::translate("EmployerAdmin", "Purchase Date:", nullptr));
        equipmentStatusLabel->setText(QCoreApplication::translate("EmployerAdmin", "Status:", nullptr));
        equipmentStatusComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Available", nullptr));
        equipmentStatusComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "In Use", nullptr));
        equipmentStatusComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Under Maintenance", nullptr));
        equipmentStatusComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Out of Order", nullptr));
        equipmentStatusComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Retired", nullptr));

        equipmentModelLabel->setText(QCoreApplication::translate("EmployerAdmin", "Model:", nullptr));
        equipmentNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter equipment name", nullptr));
        equipmentBrandLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter brand name", nullptr));
        equipmentPriceLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "$0.00", nullptr));
        equipmentPriceLabel->setText(QCoreApplication::translate("EmployerAdmin", "Purchase Price:", nullptr));
        equipmentTabWidget->setTabText(equipmentTabWidget->indexOf(equipmentAddTab), QCoreApplication::translate("EmployerAdmin", " Add Equipment", nullptr));
        totalEquipmentTitle->setText(QCoreApplication::translate("EmployerAdmin", "Total Equipment", nullptr));
        totalEquipmentNumber->setText(QCoreApplication::translate("EmployerAdmin", "245", nullptr));
        availableEquipmentTitle->setText(QCoreApplication::translate("EmployerAdmin", "Available", nullptr));
        availableEquipmentNumber->setText(QCoreApplication::translate("EmployerAdmin", "198", nullptr));
        maintenanceEquipmentTitle->setText(QCoreApplication::translate("EmployerAdmin", "Under Maintenance", nullptr));
        maintenanceEquipmentNumber->setText(QCoreApplication::translate("EmployerAdmin", "12", nullptr));
        equipmentCategoryStatsTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\212 Equipment by Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = equipmentCategoryStatsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("EmployerAdmin", "Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = equipmentCategoryStatsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("EmployerAdmin", "Total Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = equipmentCategoryStatsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("EmployerAdmin", "Available", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = equipmentCategoryStatsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("EmployerAdmin", "In Use", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = equipmentCategoryStatsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("EmployerAdmin", "Under Maintenance", nullptr));
        equipmentTabWidget->setTabText(equipmentTabWidget->indexOf(equipmentStatisticsTab), QCoreApplication::translate("EmployerAdmin", " Statistics", nullptr));
        activityPageTitle->setText(QCoreApplication::translate("EmployerAdmin", "Activity Management", nullptr));
        activitySearchLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Search activities...", nullptr));
        activitySearchButton->setText(QCoreApplication::translate("EmployerAdmin", " Search", nullptr));
        activitySortComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Sort by Date", nullptr));
        activitySortComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Sort by Age", nullptr));
        activitySortComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Sort by Activity", nullptr));

        activityExportButton->setText(QCoreApplication::translate("EmployerAdmin", "Export PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = activityTable->horizontalHeaderItem(0);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("EmployerAdmin", "Activity ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = activityTable->horizontalHeaderItem(1);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("EmployerAdmin", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = activityTable->horizontalHeaderItem(2);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("EmployerAdmin", "Event Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = activityTable->horizontalHeaderItem(3);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("EmployerAdmin", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = activityTable->horizontalHeaderItem(4);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("EmployerAdmin", "Responsible", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = activityTable->horizontalHeaderItem(5);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("EmployerAdmin", "Age", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = activityTable->horizontalHeaderItem(6);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("EmployerAdmin", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = activityTable->horizontalHeaderItem(7);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("EmployerAdmin", "Actions", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityListTab), QCoreApplication::translate("EmployerAdmin", " List of Activities", nullptr));
        activityAgeSpinBox->setSuffix(QCoreApplication::translate("EmployerAdmin", " years", nullptr));
        activityConfirmButton->setText(QCoreApplication::translate("EmployerAdmin", " Confirm Add Activity", nullptr));
        activityUpdateButton->setText(QCoreApplication::translate("EmployerAdmin", " Update Activity", nullptr));
        eventTimeEdit->setDisplayFormat(QCoreApplication::translate("EmployerAdmin", "HH:mm", nullptr));
        activityDescriptionLabel->setText(QCoreApplication::translate("EmployerAdmin", "Activity Description:", nullptr));
        activityAgeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Age Requirement:", nullptr));
        activityCapacityLabel->setText(QCoreApplication::translate("EmployerAdmin", "Capacity:", nullptr));
        activityDescriptionTextEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter detailed activity description, requirements, or notes...", nullptr));
        responsibleComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Select Employee...", nullptr));

        responsibleLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter responsible person or instructor name", nullptr));
        responsibleToggleButton->setText(QCoreApplication::translate("EmployerAdmin", "Use Manual", nullptr));
        activityCapacitySpinBox->setSuffix(QCoreApplication::translate("EmployerAdmin", " people", nullptr));
        eventTimeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Event Time:", nullptr));
        responsibleLabel->setText(QCoreApplication::translate("EmployerAdmin", "Responsible/Actor:", nullptr));
        eventDateLabel->setText(QCoreApplication::translate("EmployerAdmin", "Event Date:", nullptr));
        activityStatusLabel->setText(QCoreApplication::translate("EmployerAdmin", "Status:", nullptr));
        activityStatusComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Scheduled", nullptr));
        activityStatusComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "In Progress", nullptr));
        activityStatusComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Completed", nullptr));
        activityStatusComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Cancelled", nullptr));
        activityStatusComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Postponed", nullptr));

        activityTypeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Activity Type:", nullptr));
        activityTypeComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Mini Hackathon Kids", nullptr));
        activityTypeComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Aeronautics Workshop", nullptr));
        activityTypeComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Cin\303\251ma & Acting Lab", nullptr));
        activityTypeComboBox->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Musique", nullptr));
        activityTypeComboBox->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Sports & Fitness Program", nullptr));
        activityTypeComboBox->setItemText(5, QCoreApplication::translate("EmployerAdmin", "Art", nullptr));
        activityTypeComboBox->setItemText(6, QCoreApplication::translate("EmployerAdmin", "Special Events", nullptr));

        activityTabWidget->setTabText(activityTabWidget->indexOf(activityAddTab), QCoreApplication::translate("EmployerAdmin", " Add Activity", nullptr));
        totalActivitiesTitle->setText(QCoreApplication::translate("EmployerAdmin", "Total Activities", nullptr));
        totalActivitiesNumber->setText(QCoreApplication::translate("EmployerAdmin", "127", nullptr));
        upcomingActivitiesTitle->setText(QCoreApplication::translate("EmployerAdmin", "Upcoming Activities", nullptr));
        upcomingActivitiesNumber->setText(QCoreApplication::translate("EmployerAdmin", "23", nullptr));
        activeActivitiesTitle->setText(QCoreApplication::translate("EmployerAdmin", "Active Today", nullptr));
        activeActivitiesNumber->setText(QCoreApplication::translate("EmployerAdmin", "8", nullptr));
        activityTypeChartTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\217\267 Activity Type Distribution", nullptr));
        activityTypeChartPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "Pie Chart Placeholder", nullptr));
        activityAgeChartTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\212 Age Requirement Distribution", nullptr));
        activityAgeChartPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "Bar Chart Placeholder", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityStatisticsTab), QCoreApplication::translate("EmployerAdmin", " Statistics", nullptr));
        activityCalendarPlaceholder->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\223\205 Activity Calendar\n"
"\n"
"This interactive calendar will be implemented programmatically in C++\n"
"Shows activities by date with visual indicators, filters, and detailed views", nullptr));
        activityTabWidget->setTabText(activityTabWidget->indexOf(activityCalendarTab), QCoreApplication::translate("EmployerAdmin", " Calendar", nullptr));
        paymentSearchLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Search transactions...", nullptr));
        paymentSearchButton->setText(QCoreApplication::translate("EmployerAdmin", "Search", nullptr));
        paymentSortButton->setText(QCoreApplication::translate("EmployerAdmin", "Sort by Date", nullptr));
        paymentExportButton->setText(QCoreApplication::translate("EmployerAdmin", "Export PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = paymentTable->horizontalHeaderItem(0);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("EmployerAdmin", "Transaction ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = paymentTable->horizontalHeaderItem(1);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("EmployerAdmin", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = paymentTable->horizontalHeaderItem(2);
        ___qtablewidgetitem41->setText(QCoreApplication::translate("EmployerAdmin", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = paymentTable->horizontalHeaderItem(3);
        ___qtablewidgetitem42->setText(QCoreApplication::translate("EmployerAdmin", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = paymentTable->horizontalHeaderItem(4);
        ___qtablewidgetitem43->setText(QCoreApplication::translate("EmployerAdmin", "Amount", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = paymentTable->horizontalHeaderItem(5);
        ___qtablewidgetitem44->setText(QCoreApplication::translate("EmployerAdmin", "Method", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = paymentTable->horizontalHeaderItem(6);
        ___qtablewidgetitem45->setText(QCoreApplication::translate("EmployerAdmin", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = paymentTable->horizontalHeaderItem(7);
        ___qtablewidgetitem46->setText(QCoreApplication::translate("EmployerAdmin", "Member ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = paymentTable->horizontalHeaderItem(8);
        ___qtablewidgetitem47->setText(QCoreApplication::translate("EmployerAdmin", "Actions", nullptr));
        paymentTabWidget->setTabText(paymentTabWidget->indexOf(listTab_4), QCoreApplication::translate("EmployerAdmin", " List of Payments", nullptr));
        paymentDescriptionEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter transaction description", nullptr));
        paymentAmountLabel->setText(QCoreApplication::translate("EmployerAdmin", "Date:", nullptr));
        paymentTypeCombo->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Income", nullptr));
        paymentTypeCombo->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Expense", nullptr));

        paymentTypeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Transaction Type:", nullptr));
        paymentDescriptionLabel->setText(QCoreApplication::translate("EmployerAdmin", "Description:", nullptr));
        paymentAmountSpinBox->setPrefix(QCoreApplication::translate("EmployerAdmin", "$", nullptr));
        paymentMethodLabel->setText(QCoreApplication::translate("EmployerAdmin", "Transaction Method:", nullptr));
        paymentMethodCombo->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Cash", nullptr));
        paymentMethodCombo->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Credit Card", nullptr));
        paymentMethodCombo->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Debit Card", nullptr));
        paymentMethodCombo->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Bank Transfer", nullptr));
        paymentMethodCombo->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Check", nullptr));
        paymentMethodCombo->setItemText(5, QCoreApplication::translate("EmployerAdmin", "Online Payment", nullptr));

        paymentCategoryLabel->setText(QCoreApplication::translate("EmployerAdmin", "Category:", nullptr));
        paymentCategoryCombo->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Membership Fees", nullptr));
        paymentCategoryCombo->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Equipment Purchase", nullptr));
        paymentCategoryCombo->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Utilities", nullptr));
        paymentCategoryCombo->setItemText(3, QCoreApplication::translate("EmployerAdmin", "Salaries", nullptr));
        paymentCategoryCombo->setItemText(4, QCoreApplication::translate("EmployerAdmin", "Maintenance", nullptr));
        paymentCategoryCombo->setItemText(5, QCoreApplication::translate("EmployerAdmin", "Services", nullptr));
        paymentCategoryCombo->setItemText(6, QCoreApplication::translate("EmployerAdmin", "Other", nullptr));

        paymentDateLabel->setText(QCoreApplication::translate("EmployerAdmin", "Amount:", nullptr));
        paymentMemberLabel->setText(QCoreApplication::translate("EmployerAdmin", "Member ID:", nullptr));
        paymentMemberEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter member ID if applicable", nullptr));
        paymentStatusLabel->setText(QCoreApplication::translate("EmployerAdmin", "Status:", nullptr));
        paymentStatusCombo->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Completed", nullptr));
        paymentStatusCombo->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Pending", nullptr));
        paymentStatusCombo->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Failed", nullptr));

        addPaymentButton->setText(QCoreApplication::translate("EmployerAdmin", "Add Transaction", nullptr));
        clearPaymentFormButton->setText(QCoreApplication::translate("EmployerAdmin", "Clear Form", nullptr));
        paymentTabWidget->setTabText(paymentTabWidget->indexOf(addTab_4), QCoreApplication::translate("EmployerAdmin", " Add Payment", nullptr));
        totalIncomeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Total Income", nullptr));
        totalIncomeValue->setText(QCoreApplication::translate("EmployerAdmin", "$0.00", nullptr));
        totalExpenseLabel->setText(QCoreApplication::translate("EmployerAdmin", "Total Expenses", nullptr));
        totalExpenseValue->setText(QCoreApplication::translate("EmployerAdmin", "$0.00", nullptr));
        netBalanceLabel->setText(QCoreApplication::translate("EmployerAdmin", "Net Balance", nullptr));
        netBalanceValue->setText(QCoreApplication::translate("EmployerAdmin", "$0.00", nullptr));
        paymentChartsTitle->setText(QCoreApplication::translate("EmployerAdmin", "Payment Method Distribution", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = paymentMethodStatsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem48->setText(QCoreApplication::translate("EmployerAdmin", "Payment Method", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = paymentMethodStatsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem49->setText(QCoreApplication::translate("EmployerAdmin", "Total Transactions", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = paymentMethodStatsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem50->setText(QCoreApplication::translate("EmployerAdmin", "Total Amount", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = paymentMethodStatsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem51->setText(QCoreApplication::translate("EmployerAdmin", "Percentage", nullptr));
        recentPaymentsTitle->setText(QCoreApplication::translate("EmployerAdmin", "Recent Transactions (Last 10)", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = recentPaymentsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem52->setText(QCoreApplication::translate("EmployerAdmin", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = recentPaymentsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem53->setText(QCoreApplication::translate("EmployerAdmin", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = recentPaymentsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem54->setText(QCoreApplication::translate("EmployerAdmin", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = recentPaymentsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem55->setText(QCoreApplication::translate("EmployerAdmin", "Amount", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = recentPaymentsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem56->setText(QCoreApplication::translate("EmployerAdmin", "Status", nullptr));
        paymentTabWidget->setTabText(paymentTabWidget->indexOf(statisticsTab_4), QCoreApplication::translate("EmployerAdmin", " Statistics", nullptr));
        settingsPageTitle->setText(QCoreApplication::translate("EmployerAdmin", "Settings", nullptr));
        userProfileTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\221\244 User Profile", nullptr));
        profilePictureLabel->setText(QCoreApplication::translate("EmployerAdmin", "Photo", nullptr));
        currentUserNameLabel->setText(QCoreApplication::translate("EmployerAdmin", "User Name", nullptr));
        currentUserRoleLabel->setText(QCoreApplication::translate("EmployerAdmin", "User Role", nullptr));
        changeProfilePictureButton->setText(QCoreApplication::translate("EmployerAdmin", "Change Picture", nullptr));
        securityTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\224\220 Security Settings", nullptr));
        twoFactorLabel->setText(QCoreApplication::translate("EmployerAdmin", "Two-Factor Authentication (2FA)", nullptr));
        twoFactorDescription->setText(QCoreApplication::translate("EmployerAdmin", "Add an extra layer of security to your account by requiring a code from your authenticator app.", nullptr));
        twoFactorStatusLabel->setText(QCoreApplication::translate("EmployerAdmin", "\342\235\214 Disabled", nullptr));
        setupTwoFactorButton->setText(QCoreApplication::translate("EmployerAdmin", "Enable 2FA", nullptr));
        disableTwoFactorButton->setText(QCoreApplication::translate("EmployerAdmin", "Disable 2FA", nullptr));
        passwordChangeTitle->setText(QCoreApplication::translate("EmployerAdmin", "Change Password", nullptr));
        currentPasswordLabel->setText(QCoreApplication::translate("EmployerAdmin", "Current Password:", nullptr));
        currentPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter current password", nullptr));
        newPasswordLabel->setText(QCoreApplication::translate("EmployerAdmin", "New Password:", nullptr));
        newPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Enter new password", nullptr));
        confirmPasswordLabel->setText(QCoreApplication::translate("EmployerAdmin", "Confirm Password:", nullptr));
        confirmPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerAdmin", "Confirm new password", nullptr));
        changePasswordButton->setText(QCoreApplication::translate("EmployerAdmin", "Update Password", nullptr));
        appearanceTitle->setText(QCoreApplication::translate("EmployerAdmin", "\360\237\216\250 Appearance", nullptr));
        themeLabel->setText(QCoreApplication::translate("EmployerAdmin", "Theme:", nullptr));
        themeComboBox->setItemText(0, QCoreApplication::translate("EmployerAdmin", "Light Theme", nullptr));
        themeComboBox->setItemText(1, QCoreApplication::translate("EmployerAdmin", "Dark Theme", nullptr));
        themeComboBox->setItemText(2, QCoreApplication::translate("EmployerAdmin", "Auto (System)", nullptr));

        applyThemeButton->setText(QCoreApplication::translate("EmployerAdmin", "Apply Theme", nullptr));
        preferencesTitle->setText(QCoreApplication::translate("EmployerAdmin", "\342\232\231\357\270\217 Preferences", nullptr));
        autoRefreshCheckBox->setText(QCoreApplication::translate("EmployerAdmin", "Auto-refresh statistics every 15 seconds", nullptr));
        notificationsCheckBox->setText(QCoreApplication::translate("EmployerAdmin", "Enable desktop notifications", nullptr));
        soundCheckBox->setText(QCoreApplication::translate("EmployerAdmin", "Play sound notifications", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmployerAdmin: public Ui_EmployerAdmin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYERADMIN_H
