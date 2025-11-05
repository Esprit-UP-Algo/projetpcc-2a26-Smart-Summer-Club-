#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QVariant>
#include <QMetaType>
#include <QByteArray>
#include <QDebug>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QFileInfo>
#include <QPixmap>

// Forward declaration
namespace Ui {
class EmployerAdmin;
}

/**
 * @class Employee
 * @brief Employee CRUD operations with UI integration
 * 
 * This class handles both database operations and UI interactions.
 * All SQL queries use prepared statements for security.
 */
class Employee : public QObject
{
    Q_OBJECT

public:
    // Constructors
    Employee();
    Employee(QString cin, QString firstName, QString lastName, QString position, 
             QString department, QDate hireDate, QString status, int age, 
             QString gender, QString email, QString phone, double salary, 
             QString password = "", QByteArray photo = QByteArray(), int idActivity = 0);
    
    // UI Constructor
    explicit Employee(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Employee();

    // Setup functions
    void setupEmployeeTable();
    void refreshEmployeeTable();

public slots:
    // Employee management functions (UI handlers)
    void onSearchEmployees();
    void onUploadPhoto();
    void onConfirmAdd();
    void onConfirmUpdate();
    void onConfirmDelete();
    void clearEmployeeForm();
    
    // CIN-based edit/delete (stable across table changes - RECOMMENDED)
    void onEditEmployeeByCin(const QString &cin);
    void onDeleteEmployeeByCin(const QString &cin);
    
    // Row-based edit/delete (legacy - for backward compatibility)
    void onEditEmployee(int row);
    void onDeleteEmployee(int row);
    
    void onSortEmployees();
    void onExportEmployees();
    void onFilterByDepartment();
    void onFilterByStatus();

public:

    // Getters
    QString getCin() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getPosition() const;
    QString getDepartment() const;
    QDate getHireDate() const;
    QString getStatus() const;
    int getAge() const;
    QString getGender() const;
    QString getEmail() const;
    QString getPhone() const;
    double getSalary() const;
    QString getPassword() const;
    QByteArray getPhoto() const;
    int getIdActivity() const;

    // Setters (for update operations)
    void setCin(const QString &cin);
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setPosition(const QString &position);
    void setDepartment(const QString &department);
    void setHireDate(const QDate &hireDate);
    void setStatus(const QString &status);
    void setAge(int age);
    void setGender(const QString &gender);
    void setEmail(const QString &email);
    void setPhone(const QString &phone);
    void setSalary(double salary);
    void setPassword(const QString &password);
    void setPhoto(const QByteArray &photo);
    void setIdActivity(int idActivity);

    // CRUD Operations (Model Layer)
    bool ajouter();  // CREATE
    static QSqlQueryModel* afficher();  // READ ALL
    bool supprimer(const QString &cin);  // DELETE by CIN
    bool modifier();  // UPDATE
    
    // Additional queries
    static Employee* rechercherParCin(const QString &cin);  // Find by CIN
    static QSqlQueryModel* rechercherParNom(const QString &nom);  // Search by name
    static QSqlQueryModel* filtrerParDepartement(const QString &departement);  // Filter by department
    static QSqlQueryModel* filtrerParStatut(const QString &statut);  // Filter by status
    
    // Validation
    bool valider() const;  // Validate employee data before insert/update
    static bool cinExiste(const QString &cin);  // Check if CIN exists
    static bool emailExiste(const QString &email, const QString &excludeCin = "");  // Check if email exists

private:
    // Employee attributes matching EMPLOYEES table structure
    QString cin;
    QString firstName;
    QString lastName;
    QString position;
    QString department;
    QDate hireDate;
    QString status;
    int age;
    QString gender;
    QString email;
    QString phone;
    double salary;
    QString password;
    QByteArray photo;  // BLOB storage
    int idActivity;    // Foreign key to ACTIVITIES table
    
    // UI members
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    QString selectedPhotoPath;
    QString editingCin;
    
    // Helper validation methods
    bool validerEmail() const;
    bool validerCin() const;
    bool validerAge() const;
    
    // Helper UI methods
    void loadEmployeeToForm(Employee* emp);
    bool exportTableToPdf(QTableView* table, const QString& defaultName, const QString& title);
    QByteArray loadPhotoAsBlob(const QString& filePath);
};

#endif // EMPLOYEE_H