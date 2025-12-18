#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QMetaType>
#include <QDebug>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QFileInfo>
#include <QRegularExpression>
#include <QMap>

// Forward declaration
namespace Ui {
class EmployerAdmin;
}

/**
 * @class Activity
 * @brief Activity CRUD operations with UI integration
 * 
 * This class handles both database operations and UI interactions.
 * All SQL queries use prepared statements for security.
 */
class Activity : public QObject
{
    Q_OBJECT

public:
    // Constructors
    Activity();
    Activity(int idA, QString activityType, QDate eventDate,
             QTime eventTime, QString responsible, int ageRequirement,
             QString status, QString description, int capacity);
    
    // UI Constructor
    explicit Activity(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Activity();

    // Setup functions
    void setupActivityTable();
    void refreshActivityTable();
    
    // Getters
    int getIdA() const;
    QString getActivityType() const;
    QDate getEventDate() const;
    QTime getEventTime() const;
    QString getResponsible() const;
    int getAgeRequirement() const;
    QString getStatus() const;
    QString getDescription() const;
    int getCapacity() const;

    // Setters (for update operations)
    void setIdA(int idA);
    void setActivityType(const QString &activityType);
    void setEventDate(const QDate &eventDate);
    void setEventTime(const QTime &eventTime);
    void setResponsible(const QString &responsible);
    void setAgeRequirement(int ageRequirement);
    void setStatus(const QString &status);
    void setDescription(const QString &description);
    void setCapacity(int capacity);

    // CRUD Operations (Model Layer)
    bool ajouter();  // CREATE
    static QSqlQueryModel* afficher();  // READ ALL
    bool supprimer(int idA);  // DELETE by ID
    bool modifier();  // UPDATE
    
    // Additional queries
    static Activity* rechercherParId(int idA);  // Find by ID
    static QSqlQueryModel* rechercherParResponsible(const QString &responsible);  // Search by responsible person
    static QSqlQueryModel* filtrerParType(const QString &type);  // Filter by activity type
    static QSqlQueryModel* filtrerParStatut(const QString &statut);  // Filter by status
    
    // Validation
    bool valider() const;  // Validate activity data before insert/update
    static bool idExiste(int idA);  // Check if ID exists

    // UI Methods (View Layer)
    void onConfirmAdd();
    void onConfirmUpdate();
    void onConfirmDelete();
    void clearActivityForm();
    
    // ID-based edit/delete (stable across table changes - RECOMMENDED)
    void onEditActivityById(int idA);
    void onDeleteActivityById(int idA);
    
    // Row-based edit/delete (legacy - for backward compatibility)
    void onEditActivity(int row);
    void onDeleteActivity(int row);
    
    void onSortActivities();
    void onSortComboBoxChanged(int index);
    void onExportActivities();
    void onSearchActivities();
    void onFilterByType();
    void onFilterByStatus();
    void onToggleResponsibleInput();
    
    // ======================================================================
    // EQUIPMENT RESERVATION METHODS
    // ======================================================================
    void setupEquipmentReservation();
    void setupAvailableEquipmentTable();
    void setupReservedEquipmentTable();
    void refreshAvailableEquipment();
    void onReserveQuantityChanged(int value);
    QSqlQueryModel* getAvailableEquipment(const QDate& date);
    void addSelectedToReservation();
    void addToReservedTable(int equipmentId, const QString& name, int quantity);
    void updateReservedTotal();
    void confirmEquipmentReservation();
    bool reserveEquipment(int equipmentId, int quantity, int activityId);
    QString getReservedEquipmentSummary(int activityId) const;
    void clearReservation();

private:
    // Activity attributes matching ACTIVITIES table structure
    int idA;
    QString activityType;
    QDate eventDate;
    QTime eventTime;
    QString responsible;
    int ageRequirement;
    QString status;
    QString description;
    int capacity;
    
    // UI members
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    int editingId;
    bool useEmployeeComboBox; // Track which input mode is active
    bool sortAscending;  // Track sort order for arrow indicators
    int currentActivityId;  // Track current activity being edited for reservations
    QMap<int, int> reservedEquipment;  // Equipment ID -> Quantity mapping for current reservation
    
    // Helper validation methods
    bool validerResponsible(const QString &name) const;  // Validate responsible person name
    bool validerCapacity() const;  // Validate capacity is positive
    bool validerRequiredFields() const;  // Check all required fields are filled
    
    // Helper UI methods
    void loadEmployeesToComboBox();  // Populate employee combobox
    QString getResponsibleValue() const;  // Get value from active input (combobox or lineedit)
    
    // Helper UI methods
    void loadActivityToForm(Activity* activity);
    void populateActivityTableWidget(QTableWidget* table, QSqlQueryModel* model, Activity* activityManager);
    
    // Node.js script path helper (similar to OCR interface)
    QString getNodeScriptPath() const;
    bool ensureNodeJsScriptsExists() const;
    QString findActualProjectLocation() const;
    bool copyDirectoryRecursively(const QString &sourceDir, const QString &destDir) const;
    
    // PDF generation helper
    bool createPdfWithImage(const QString &imagePath, const QString &pdfPath) const;
    
    // Activity JSON file creation for QR code generation
    bool createActivityJsonFile(const QString &nodeScriptsPath) const;
    bool writeActivityToJsonFile(Activity* activity, const QString &filePath) const;
};

#endif // ACTIVITY_H