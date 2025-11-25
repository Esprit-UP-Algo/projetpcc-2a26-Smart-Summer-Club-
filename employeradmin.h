#ifndef EMPLOYERADMIN_H
#define EMPLOYERADMIN_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QPixmap>

#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLineSeries>

#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>

// Include the management classes
#include "employee.h"
#include "member.h"
#include "activity.h"
#include "equipment.h"
#include "payment.h"
#include "emailpanel.h"
#include "activitypanel.h"
#include "connexion_ard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EmployerAdmin;
}
QT_END_NAMESPACE

class EmployerAdmin : public QMainWindow
{
    Q_OBJECT

public:
    EmployerAdmin(QWidget *parent = nullptr);
    ~EmployerAdmin();
    void refreshUserInfoFromDatabase();
    void setArduino(Arduino *ard);

private slots:
    void onNavigationButtonClicked();
    void onSettingsButtonClicked();
    void onSetupTwoFactorClicked();
    void onDisableTwoFactorClicked();
    void onLogoutClicked();
    void onChangeProfilePictureClicked();
    void onChangePasswordClicked();
    void onApplyThemeClicked();
    void onArduinoDataReceived(QByteArray data);
    void onArduinoConnectionStatusChanged(bool connected);
    void onArduinoErrorOccurred(QString errorMessage);

private:
    Ui::EmployerAdmin *ui;
    QButtonGroup *navigationButtonGroup;
    Arduino *arduino;
    
    // Management class instances
    Employee *employeeManager;
    Member *memberManager;
    Activity *activityManager;
    Equipment *equipmentManager;
    Payment *paymentManager;
    EmailPanel *emailPanel;
    ActivityPanel *activityPanel;
    
    void setupEmployeeStatisticsCharts();
    void buildEmployeeDepartmentChart();
    void buildEmployeeStatusChart();
    void buildEmployeeSalaryChart();
    void setupMemberStatisticsCharts();
    void buildMemberGenderChart();
    void buildMemberAgeChart();
    void buildMemberSubscriptionChart();
    void updateMemberStatisticsCards();
    void updateEmployeeStatisticsCards();
    void updateActivityStatisticsCards();
    void refreshStatistics(); // combined refresh
    void setStatisticsAutoRefreshEnabled(bool enabled, int intervalMs = 15000);
    void setupActivityStatisticsCharts();
    void buildActivityTypeChart();
    void buildActivityAgeChart();
    void setupConnections();
    void setupInputValidators(); // Setup input field validators
    void setupIcons();  // Optional icon setup
    void setupTabIcons(); // Set icons for tab widgets
    void setupButtonStyling();  // Apply consistent button styling
    void setupActivityAnalyticsTab(); // Setup Activity Analytics tab
    void updateNavigationStyle();
    void showUserInfo();
    void updateTabVisibility();
    void setupSettingsPage();
    void updateTwoFactorStatus();
    void setupEmailPanel();
    void loadUserProfileInfo();
    void setupArduinoConnections();
    
    QChartView *employeeDepartmentChartView = nullptr;
    QChartView *employeeStatusChartView = nullptr;
    QChartView *employeeSalaryChartView = nullptr;
    QChartView *memberGenderChartView = nullptr;
    QChartView *memberAgeChartView = nullptr;
    QChartView *memberSubscriptionChartView = nullptr;
    QTimer *m_statsRefreshTimer = nullptr;
    QChartView *activityTypeChartView = nullptr;
    QChartView *activityAgeChartView = nullptr;
};

#endif // EMPLOYERADMIN_H
