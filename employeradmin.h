#ifndef EMPLOYERADMIN_H
#define EMPLOYERADMIN_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QFileInfo>
#include <QIcon>
#include <QResource>
#include <QDebug>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

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
     void onSearchEmployees();
    void onUploadPhoto();
    void onConfirmAdd();
    void onConfirmUpdate();
    void populateEmployeeTable();
    void populateStatistics();
    void onEditEmployee(int row);
    void onDeleteEmployee(int row);
    void onEditMember(int row);
    void onDeleteMember(int row);
    void onEditActivity(int row);
    void onDeleteActivity(int row);
    void onEquipmentDetails(const QStringList &equipmentData);
    void onEquipmentManage(const QStringList &equipmentData);
    void onEquipmentDelete(const QStringList &equipmentData, int row);
    
    // Payment Management
    void onAddPayment();
    void onClearPaymentForm();
    void onPaymentSearchTextChanged();
    void onEditPayment(const QStringList &paymentData);
    void onDeletePayment(const QStringList &paymentData, int row);
    
    // Sorting and Exporting
    void onSortEmployees();
    void onExportEmployees();
    void onSortMembers();
    void onExportMembers();
    void onSortActivities(int index);
    void onExportActivities();
    void onSortEquipment();
    void onExportEquipment();

private:
    Ui::EmployerAdmin *ui;
    QButtonGroup *navigationButtonGroup;
    
    // Dynamic equipment details table
    QTableWidget *equipmentDetailsTable;
    QWidget *equipmentDetailsWidget;
    bool isDetailsTableVisible;
    
    void setupCostAnalysisChart(); // New function for setting up the chart
    
    void setupConnections();
    void setupEmployeeTable();
    void setupMemberTable();
    void setupActivityTable();
    void setupEquipmentTable();
    void setupPaymentTable();
    void setupStatisticsTable();
    void populateMemberTable();
    void populateActivityTable();
    void populateEquipmentTable();
    void populatePaymentTable();
    void populatePaymentStatistics();
    void setupIcons();  // Optional icon setup
    void setupTabIcons(); // Set icons for tab widgets
    void setupButtonStyling();  // Apply consistent button styling
    void clearEmployeeForm();
    void updateNavigationStyle();
    
    // Equipment details table functions
    void setupEquipmentDetailsTable();
    void showEquipmentDetailsTable(const QStringList &equipmentData);
    void hideEquipmentDetailsTable();
    // helpers
    void sortTableByName(QTableWidget* table, int nameColumnIndex = 1);
    bool exportTableToCsv(QTableWidget* table, const QString& defaultName); // legacy
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);
};

#endif // EMPLOYERADMIN_H
