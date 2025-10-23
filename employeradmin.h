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

// Include the management classes
#include "employee.h"
#include "member.h"
#include "activity.h"
#include "equipment.h"
#include "payment.h"

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

private slots:
    void onNavigationButtonClicked();

private:
    Ui::EmployerAdmin *ui;
    QButtonGroup *navigationButtonGroup;
    
    // Management class instances
    Employee *employeeManager;
    Member *memberManager;
    Activity *activityManager;
    Equipment *equipmentManager;
    Payment *paymentManager;
    
    void setupCostAnalysisChart(); // New function for setting up the chart
    void setupConnections();
    void setupIcons();  // Optional icon setup
    void setupTabIcons(); // Set icons for tab widgets
    void setupButtonStyling();  // Apply consistent button styling
    void updateNavigationStyle();
};

#endif // EMPLOYERADMIN_H
