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

private:
    Ui::EmployerAdmin *ui;
    QButtonGroup *navigationButtonGroup;
    
    void setupConnections();
    void setupEmployeeTable();
    void setupStatisticsTable();
    void setupIcons();  // Optional icon setup
    void setupButtonStyling();  // Apply consistent button styling
    void clearEmployeeForm();
    void updateNavigationStyle();
};

#endif // EMPLOYERADMIN_H
