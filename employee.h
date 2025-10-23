#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QFileInfo>
#include <QIcon>
#include <QDebug>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDateEdit>

// Forward declaration
namespace Ui {
class EmployerAdmin;
}

class Employee : public QObject
{
    Q_OBJECT

public:
    explicit Employee(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Employee();

    // Setup functions
    void setupEmployeeTable();
    
    // Employee management functions
    void onSearchEmployees();
    void onUploadPhoto();
    void onConfirmAdd();
    void onConfirmUpdate();
    void clearEmployeeForm();
    
    // Table operations
    void onEditEmployee(int row);
    void onDeleteEmployee(int row);
    void onSortEmployees();
    void onExportEmployees();

private:
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    
    // Helper functions
    void sortTableByName(QTableWidget* table, int nameColumnIndex = 1);
    bool exportTableToCsv(QTableWidget* table, const QString& defaultName);
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);
};

#endif // EMPLOYEE_H