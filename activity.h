#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QFileInfo>
#include <QRegularExpression>
#include <QMap>

namespace Ui {
class EmployerAdmin;
}

class Activity : public QObject
{
    Q_OBJECT

public:
    Activity();
    Activity(int idA, QString activityType, QDate eventDate,
             QTime eventTime, QString responsible, int ageRequirement,
             QString status, QString description, int capacity);
    explicit Activity(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Activity();

    void setupActivityTable();
    void refreshActivityTable();

    int getIdA() const;
    QString getActivityType() const;
    QDate getEventDate() const;
    QTime getEventTime() const;
    QString getResponsible() const;
    int getAgeRequirement() const;
    QString getStatus() const;
    QString getDescription() const;
    int getCapacity() const;

    void setIdA(int idA);
    void setActivityType(const QString &activityType);
    void setEventDate(const QDate &eventDate);
    void setEventTime(const QTime &eventTime);
    void setResponsible(const QString &responsible);
    void setAgeRequirement(int ageRequirement);
    void setStatus(const QString &status);
    void setDescription(const QString &description);
    void setCapacity(int capacity);

    bool ajouter();
    static QSqlQueryModel* afficher();
    bool supprimer(int idA);
    bool modifier();

    static Activity* rechercherParId(int idA);
    static QSqlQueryModel* rechercherParResponsible(const QString &responsible);
    static QSqlQueryModel* filtrerParType(const QString &type);
    static QSqlQueryModel* filtrerParStatut(const QString &statut);

    bool valider() const;
    static bool idExiste(int idA);

    void onConfirmAdd();
    void onConfirmUpdate();
    void onConfirmDelete();
    void clearActivityForm();

    void onEditActivityById(int idA);
    void onDeleteActivityById(int idA);
    void onEditActivity(int row);
    void onDeleteActivity(int row);

    void onSortActivities();
    void onSortComboBoxChanged(int index);
    void onExportActivities();
    void onSearchActivities();
    void onFilterByType();
    void onFilterByStatus();
    void onToggleResponsibleInput();

private:
    int idA;
    QString activityType;
    QDate eventDate;
    QTime eventTime;
    QString responsible;
    int ageRequirement;
    QString status;
    QString description;
    int capacity;

    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    int editingId;
    bool useEmployeeComboBox;
    QMap<int, int> reservedEquipment;
    int currentActivityId;

    bool validerResponsible(const QString &name) const;
    bool validerCapacity() const;
    bool validerRequiredFields() const;

    void loadEmployeesToComboBox();
    QString getResponsibleValue() const;

    void populateActivityTableWidget(QTableWidget* table, QSqlQueryModel* model, Activity* activityManager);
    void loadActivityToForm(Activity* activity);
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);

    void setupEquipmentReservation();
    void setupAvailableEquipmentTable();
    void setupReservedEquipmentTable();
    void refreshAvailableEquipment();
    void onReserveQuantityChanged(int value);
    void addSelectedToReservation();
    void addToReservedTable(int equipmentId, const QString& name, int quantity);
    void confirmEquipmentReservation();
    void clearReservation();
    void updateReservedTotal();

    QSqlQueryModel* getAvailableEquipment(const QDate& date);
    bool reserveEquipment(int equipmentId, int quantity, int activityId);
    QString getReservedEquipmentSummary(int activityId) const;
};

#endif // ACTIVITY_H

