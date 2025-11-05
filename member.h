#ifndef MEMBER_H
#define MEMBER_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QVariant>
#include <QMetaType>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QDebug>

// Forward declaration
// ============================================================================

namespace Ui {
class EmployerAdmin;
}

class Member : public QObject
{
    Q_OBJECT

public:
    // Constructors
    Member();
    Member(QString cin, QString firstName, QString lastName, QString gender, 
           int age, QString email, QString phone, QString subscriptionPlan, 
           QDate joinDate);
    Member(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Member();

    // Getters
    QString getCin() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getGender() const;
    int getAge() const;
    QString getEmail() const;
    QString getPhone() const;
    QString getSubscriptionPlan() const;
    QDate getJoinDate() const;

    // Setters (for update operations)
    void setCin(const QString &cin);
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setGender(const QString &gender);
    void setAge(int age);
    void setEmail(const QString &email);
    void setPhone(const QString &phone);
    void setSubscriptionPlan(const QString &subscriptionPlan);
    void setJoinDate(const QDate &joinDate);

    // CRUD Operations (Model Layer)
    bool ajouter();  // CREATE
    static QSqlQueryModel* afficher();  // READ ALL
    bool supprimer(const QString &cin);  // DELETE by CIN
    bool modifier();  // UPDATE
    
    // Additional queries
    static Member* rechercherParCin(const QString &cin);  // Find by CIN
    static QSqlQueryModel* rechercherParNom(const QString &nom);  // Search by name
    static QSqlQueryModel* filtrerParPlan(const QString &plan);  // Filter by subscription plan
    static QSqlQueryModel* filtrerParGenre(const QString &genre);  // Filter by gender
    
    // Validation
    bool valider() const;  // Validate member data before insert/update
    static bool cinExiste(const QString &cin);  // Check if CIN exists
    static bool emailExiste(const QString &email, const QString &excludeCin = "");  // Check if email exists

    // UI Methods (View Layer)
    void setupMemberTable();
    void refreshMemberTable();
    void onConfirmAdd();
    void onConfirmUpdate();
    void onConfirmDelete();
    void clearMemberForm();
    
    // CIN-based edit/delete (stable across table changes - RECOMMENDED)
    void onEditMemberByCin(const QString &cin);
    void onDeleteMemberByCin(const QString &cin);
    
    // Row-based edit/delete (legacy - for backward compatibility)
    void onEditMember(int row);
    void onDeleteMember(int row);
    
    void onSortMembers();
    void onExportMembers();
    void onSearchMembers();
    void onFilterByPlan();
    void onFilterByGender();

private:
    // Member attributes matching MEMBERS table structure
    QString cin;
    QString firstName;
    QString lastName;
    QString gender;
    int age;
    QString email;
    QString phone;
    QString subscriptionPlan;
    QDate joinDate;
    
    // UI members
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    QString editingCin;
    
    // Helper validation methods
    bool validerEmail() const;
    bool validerCin() const;
    bool validerAge() const;
    bool validerName(const QString &name) const;  // Validate names (no numbers/special chars)
    bool validerPhone() const;  // Validate phone format
    bool validerRequiredFields() const;  // Check all required fields are filled
    
    // Helper UI methods
    void loadMemberToForm(Member* member);
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);
};

#endif // MEMBER_H