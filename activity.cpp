#include "activity.h"
#include "ui_employeradmin.h"
#include <QRegularExpression>
#include <QDateTime>
#include <QTextDocument>
#include <QPrinter>
#include <QPageLayout>
#include <QFile>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QSpinBox>
#include <QtGlobal>

// ============================================================================
// CONSTRUCTORS & DESTRUCTOR
// ============================================================================

Activity::Activity()
    : QObject(nullptr), idA(0), activityType(""), eventDate(QDate::currentDate()),
      eventTime(QTime::currentTime()), responsible(""), ageRequirement(0),
      status("Scheduled"), description(""), capacity(0),
      ui(nullptr), parentWidget(nullptr), editingId(-1), useEmployeeComboBox(true),
      currentActivityId(-1)
{
}

Activity::Activity(int idA, QString activityType, QDate eventDate,
                   QTime eventTime, QString responsible, int ageRequirement,
                   QString status, QString description, int capacity)
    : QObject(nullptr), idA(idA), activityType(activityType),
      eventDate(eventDate), eventTime(eventTime), responsible(responsible),
      ageRequirement(ageRequirement), status(status), description(description),
      capacity(capacity), ui(nullptr), parentWidget(nullptr), editingId(-1), useEmployeeComboBox(true),
      currentActivityId(-1)
{
}

Activity::Activity(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), idA(0), activityType(""), eventDate(QDate::currentDate()),
      eventTime(QTime::currentTime()), responsible(""), ageRequirement(0),
      status("Scheduled"), description(""), capacity(0),
      ui(ui), parentWidget(parent), editingId(-1), useEmployeeComboBox(true),
      currentActivityId(-1)
{
    // Load employees into combobox and setup initial state
    loadEmployeesToComboBox();
    
    // Initially show combobox, hide lineedit
    if (ui) {
        ui->responsibleComboBox->setVisible(true);
        ui->responsibleLineEdit->setVisible(false);
        ui->responsibleToggleButton->setText("Use Manual");
    }
    
    setupEquipmentReservation();
}

Activity::~Activity()
{
}

// ============================================================================
// GETTERS
// ============================================================================

int Activity::getIdA() const { return idA; }
QString Activity::getActivityType() const { return activityType; }
QDate Activity::getEventDate() const { return eventDate; }
QTime Activity::getEventTime() const { return eventTime; }
QString Activity::getResponsible() const { return responsible; }
int Activity::getAgeRequirement() const { return ageRequirement; }
QString Activity::getStatus() const { return status; }
QString Activity::getDescription() const { return description; }
int Activity::getCapacity() const { return capacity; }

// ============================================================================
// SETTERS
// ============================================================================

void Activity::setIdA(int idA) { this->idA = idA; }
void Activity::setActivityType(const QString &activityType) { this->activityType = activityType; }
void Activity::setEventDate(const QDate &eventDate) { this->eventDate = eventDate; }
void Activity::setEventTime(const QTime &eventTime) { this->eventTime = eventTime; }
void Activity::setResponsible(const QString &responsible) { this->responsible = responsible; }
void Activity::setAgeRequirement(int ageRequirement) { this->ageRequirement = ageRequirement; }
void Activity::setStatus(const QString &status) { this->status = status; }
void Activity::setDescription(const QString &description) { this->description = description; }
void Activity::setCapacity(int capacity) { this->capacity = capacity; }

// ============================================================================
// VALIDATION METHODS
// ============================================================================

bool Activity::validerResponsible(const QString &name) const
{
    // Responsible person name must not be empty
    if (name.trimmed().isEmpty()) {
        return false;
    }
    
    // Name should only contain letters, spaces, hyphens, and apostrophes
    for (QChar c : name) {
        if (!c.isLetter() && c != ' ' && c != '-' && c != '\'') {
            return false;
        }
    }
    
    return true;
}

bool Activity::validerCapacity() const
{
    // Capacity must be positive
    return (capacity > 0);
}

bool Activity::validerRequiredFields() const
{
    // Check all required fields are filled
    if (activityType.trimmed().isEmpty()) {
        return false;
    }
    if (!eventDate.isValid()) {
        return false;
    }
    if (!eventTime.isValid()) {
        return false;
    }
    if (responsible.trimmed().isEmpty()) {
        return false;
    }
    if (ageRequirement < 0) {
        return false;
    }
    if (status.trimmed().isEmpty()) {
        return false;
    }
    if (capacity <= 0) {
        return false;
    }
    // Description is optional
    
    return true;
}

bool Activity::valider() const
{
    // 1. Check all required fields are filled
    if (!validerRequiredFields()) {
        qDebug() << "Validation failed: All fields must be filled (description is optional)";
        return false;
    }
    
    // 2. Validate responsible person name
    if (!validerResponsible(responsible)) {
        qDebug() << "Validation failed: Responsible person name can only contain letters, spaces, hyphens, and apostrophes";
        return false;
    }
    
    // 3. Validate capacity is positive
    if (!validerCapacity()) {
        qDebug() << "Validation failed: Capacity must be greater than 0";
        return false;
    }
    
    // 4. Validate age requirement is reasonable
    if (ageRequirement < 0 || ageRequirement > 100) {
        qDebug() << "Validation failed: Age requirement must be between 0 and 100";
        return false;
    }
    
    // 5. Validate event date is not in the past (optional check)
    if (eventDate < QDate::currentDate()) {
        qDebug() << "Warning: Event date is in the past";
        // This is just a warning, not a failure
    }
    
    return true;
}

bool Activity::idExiste(int idA)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM ACTIVITIES WHERE ID_A = :idA");
    query.bindValue(":idA", idA);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    qDebug() << "Error checking ID existence:" << query.lastError().text();
    return false;
}

// ============================================================================
// CRUD OPERATIONS
// ============================================================================

/**
 * @brief CREATE - Add new activity to database
 * @return true if successful, false otherwise
 */
bool Activity::ajouter()
{
    // Validate data before insertion
    if (!valider()) {
        qDebug() << "Activity::ajouter() - Validation failed";
        return false;
    }
    
    // Prepare INSERT query - ID_A will be auto-generated by database trigger
    QSqlQuery query;
    query.prepare("INSERT INTO ACTIVITIES "
                  "(ACTIVITY_TYPE, EVENT_DATE, EVENT_TIME, "
                  "RESPONSIBLE, AGE_REQUIREMENT, STATUS, DESCRIPTION, CAPACITY) "
                  "VALUES "
                  "(:activityType, :eventDate, :eventTime, "
                  ":responsible, :ageRequirement, :status, :description, :capacity)");
    
    // Bind values (no ID - let trigger handle it)
    query.bindValue(":activityType", activityType);
    query.bindValue(":eventDate", eventDate);
    
    // Convert QTime to Oracle TIMESTAMP format
    QDateTime dateTime(eventDate, eventTime);
    query.bindValue(":eventTime", dateTime);
    
    query.bindValue(":responsible", responsible);
    query.bindValue(":ageRequirement", ageRequirement);
    query.bindValue(":status", status);
    query.bindValue(":description", description.isEmpty() ? QVariant(QString()) : description);
    query.bindValue(":capacity", capacity);
    
    // Execute query
    if (query.exec()) {
        qDebug() << "Activity added successfully - ID auto-generated by database";
        // Note: ID is auto-generated by database trigger, not stored in this instance
        return true;
    }
    
    qDebug() << "Error adding activity:" << query.lastError().text();
    return false;
}

/**
 * @brief READ - Get all activities
 * @return QSqlQueryModel containing all activities
 */
QSqlQueryModel* Activity::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_A, ACTIVITY_TYPE, EVENT_DATE, EVENT_TIME, "
                    "RESPONSIBLE, AGE_REQUIREMENT, STATUS, DESCRIPTION, CAPACITY "
                    "FROM ACTIVITIES ORDER BY EVENT_DATE DESC");
    
    if (model->lastError().isValid()) {
        qDebug() << "Error fetching activities:" << model->lastError().text();
    }
    
    return model;
}

/**
 * @brief DELETE - Remove activity from database
 * @param idA Activity ID to delete
 * @return true if successful, false otherwise
 */
bool Activity::supprimer(int idA)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ACTIVITIES WHERE ID_A = :idA");
    query.bindValue(":idA", idA);
    
    if (query.exec()) {
        qDebug() << "Activity deleted successfully:" << idA;
        return true;
    }
    
    qDebug() << "Error deleting activity:" << query.lastError().text();
    return false;
}

/**
 * @brief UPDATE - Modify existing activity
 * @return true if successful, false otherwise
 */
bool Activity::modifier()
{
    // Validate data before update
    if (!valider()) {
        qDebug() << "Activity::modifier() - Validation failed";
        return false;
    }
    
    // Check if ID exists
    if (!idExiste(idA)) {
        qDebug() << "Activity::modifier() - ID does not exist:" << idA;
        return false;
    }
    
    // Prepare UPDATE query
    QSqlQuery query;
    query.prepare("UPDATE ACTIVITIES SET "
                  "ACTIVITY_TYPE = :activityType, "
                  "EVENT_DATE = :eventDate, "
                  "EVENT_TIME = :eventTime, "
                  "RESPONSIBLE = :responsible, "
                  "AGE_REQUIREMENT = :ageRequirement, "
                  "STATUS = :status, "
                  "DESCRIPTION = :description, "
                  "CAPACITY = :capacity "
                  "WHERE ID_A = :idA");
    
    // Bind values
    query.bindValue(":idA", idA);
    query.bindValue(":activityType", activityType);
    query.bindValue(":eventDate", eventDate);
    
    // Convert QTime to Oracle TIMESTAMP format
    QDateTime dateTime(eventDate, eventTime);
    query.bindValue(":eventTime", dateTime);
    
    query.bindValue(":responsible", responsible);
    query.bindValue(":ageRequirement", ageRequirement);
    query.bindValue(":status", status);
    query.bindValue(":description", description.isEmpty() ? QVariant(QString()) : description);
    query.bindValue(":capacity", capacity);
    
    // Execute query
    if (query.exec()) {
        qDebug() << "Activity updated successfully:" << idA;
        return true;
    }
    
    qDebug() << "Error updating activity:" << query.lastError().text();
    return false;
}

/**
 * @brief SEARCH - Find activity by ID
 * @param idA Activity ID to search for
 * @return Activity object if found, nullptr otherwise
 */
Activity* Activity::rechercherParId(int idA)
{
    QSqlQuery query;
    query.prepare("SELECT ID_A, ACTIVITY_TYPE, EVENT_DATE, EVENT_TIME, "
                  "RESPONSIBLE, AGE_REQUIREMENT, STATUS, DESCRIPTION, CAPACITY "
                  "FROM ACTIVITIES WHERE ID_A = :idA");
    query.bindValue(":idA", idA);
    
    if (query.exec() && query.next()) {
        // Extract time from TIMESTAMP
        QDateTime eventDateTime = query.value(3).toDateTime();
        
        return new Activity(
            query.value(0).toInt(),           // ID_A
            query.value(1).toString(),         // ACTIVITY_TYPE
            query.value(2).toDate(),          // EVENT_DATE
            eventDateTime.time(),             // EVENT_TIME
            query.value(4).toString(),         // RESPONSIBLE
            query.value(5).toInt(),           // AGE_REQUIREMENT
            query.value(6).toString(),         // STATUS
            query.value(7).toString(),         // DESCRIPTION
            query.value(8).toInt()            // CAPACITY
        );
    }
    
    qDebug() << "Activity not found:" << idA;
    return nullptr;
}

/**
 * @brief SEARCH - Find activities by responsible person (partial match)
 * @param responsible Responsible person name to search for
 * @return QSqlQueryModel containing matching activities
 */
QSqlQueryModel* Activity::rechercherParResponsible(const QString &responsible)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_A, ACTIVITY_TYPE, EVENT_DATE, EVENT_TIME, "
                  "RESPONSIBLE, AGE_REQUIREMENT, STATUS, DESCRIPTION, CAPACITY "
                  "FROM ACTIVITIES "
                  "WHERE UPPER(RESPONSIBLE) LIKE UPPER(:responsible) "
                  "ORDER BY EVENT_DATE DESC");
    query.bindValue(":responsible", "%" + responsible + "%");
    query.exec();
    
    model->setQuery(std::move(query));
    
    if (model->lastError().isValid()) {
        qDebug() << "Error searching activities:" << model->lastError().text();
    }
    
    return model;
}

/**
 * @brief FILTER - Filter activities by type
 * @param type Activity type to filter by
 * @return QSqlQueryModel containing filtered activities
 */
QSqlQueryModel* Activity::filtrerParType(const QString &type)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_A, ACTIVITY_TYPE, EVENT_DATE, EVENT_TIME, "
                  "RESPONSIBLE, AGE_REQUIREMENT, STATUS, DESCRIPTION, CAPACITY "
                  "FROM ACTIVITIES "
                  "WHERE UPPER(ACTIVITY_TYPE) = UPPER(:type) "
                  "ORDER BY EVENT_DATE DESC");
    query.bindValue(":type", type);
    query.exec();
    
    model->setQuery(std::move(query));
    
    if (model->lastError().isValid()) {
        qDebug() << "Error filtering activities by type:" << model->lastError().text();
    }
    
    return model;
}

/**
 * @brief FILTER - Filter activities by status
 * @param statut Status to filter by
 * @return QSqlQueryModel containing filtered activities
 */
QSqlQueryModel* Activity::filtrerParStatut(const QString &statut)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_A, ACTIVITY_TYPE, EVENT_DATE, EVENT_TIME, "
                  "RESPONSIBLE, AGE_REQUIREMENT, STATUS, DESCRIPTION, CAPACITY "
                  "FROM ACTIVITIES "
                  "WHERE UPPER(STATUS) = UPPER(:status) "
                  "ORDER BY EVENT_DATE DESC");
    query.bindValue(":status", statut);
    query.exec();
    
    model->setQuery(std::move(query));
    
    if (model->lastError().isValid()) {
        qDebug() << "Error filtering activities by status:" << model->lastError().text();
    }
    
    return model;
}

// ============================================================================
// UI METHODS - TABLE POPULATION
// ============================================================================

void Activity::populateActivityTableWidget(QTableWidget* table, QSqlQueryModel* model, Activity* activityManager)
{
    if (!table || !model) return;
    
    table->clearContents();
    table->setRowCount(0);
    
    int rows = model->rowCount();
    int cols = model->columnCount();
    
    // Store these before the loop to avoid race conditions
    int storedCols = cols;
    int reservedColumnIndex = storedCols;
    int actionColumnIndex = storedCols + 1; // Actions column is after reserved column
    
    table->setColumnCount(storedCols + 2); // + reserved + actions
    
    // Set headers
    QStringList headers;
    for (int c = 0; c < storedCols; ++c) {
        headers << model->headerData(c, Qt::Horizontal).toString();
    }
    headers << "Reserved Equipment" << "Actions";
    table->setHorizontalHeaderLabels(headers);
    
    for (int r = 0; r < rows; ++r) {
        table->insertRow(r);
        
        // Capture ID for lambda (column 0 contains ID_A)
        int activityId = model->record(r).value(0).toInt();
        
        // Add data cells
        for (int c = 0; c < storedCols; ++c) {
            QVariant data = model->record(r).value(c);
            QString displayText;
            
            // Format special columns (NAME column removed, so indices shifted)
            if (c == 2) { // EVENT_DATE (was column 3)
                displayText = data.toDate().toString("yyyy-MM-dd");
            } else if (c == 3) { // EVENT_TIME (was column 4)
                QDateTime dt = data.toDateTime();
                displayText = dt.time().toString("HH:mm");
            } else {
                displayText = data.toString();
            }
            
            QTableWidgetItem* item = new QTableWidgetItem(displayText);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(r, c, item);
        }
        
        // Reserved equipment summary
        QString reservedSummary;
        if (activityManager) {
            reservedSummary = activityManager->getReservedEquipmentSummary(activityId);
        }
        QTableWidgetItem* reservedItem = new QTableWidgetItem(reservedSummary.isEmpty() ? "None" : reservedSummary);
        reservedItem->setFlags(reservedItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(r, reservedColumnIndex, reservedItem);
        
        // Add action buttons
        QWidget* actionWidget = new QWidget(table);
        QHBoxLayout* layout = new QHBoxLayout(actionWidget);
        layout->setContentsMargins(4, 2, 4, 2);
        layout->setSpacing(4);
        
        QPushButton* editBtn = new QPushButton("Edit", actionWidget);
        QPushButton* deleteBtn = new QPushButton("Delete", actionWidget);
        editBtn->setIcon(QIcon(":/icons/icons/edit.png"));
        deleteBtn->setIcon(QIcon(":/icons/icons/delete.png"));
        editBtn->setStyleSheet(
                "QPushButton { "
                "background-color: rgba(22, 165, 179, 0.10); "
                "color: #2c3e50; "
                "border: 1.5px solid rgba(22, 165, 179, 0.65); "
                "padding: 5px 10px; "
                "border-radius: 4px; "
                "font-size: 12px; "
                "} "
                "QPushButton:hover { "
                "background-color: #e67e22; "
                "color: white; "
                "}"
            );
        deleteBtn->setStyleSheet(
                "QPushButton { "
                "background-color: rgba(22, 165, 179, 0.10); "
                "color: #2c3e50; "
                "border: 1.5px solid rgba(22, 165, 179, 0.65); "
                "padding: 5px 10px; "
                "border-radius: 4px; "
                "font-size: 12px; "
                "} "
                "QPushButton:hover { "
                "background-color: #c0392b; "
                "color: white; "
                "}"
            );
        
        layout->addWidget(editBtn);
        layout->addWidget(deleteBtn);
        layout->addStretch();
        
        actionWidget->setLayout(layout);
        table->setCellWidget(r, actionColumnIndex, actionWidget);
        
        // Connect using CAPTURED ID (not row index)
        if (activityManager) {
            QObject::connect(editBtn, &QPushButton::clicked, activityManager, [activityManager, activityId]() {
                activityManager->onEditActivityById(activityId);
            });
            QObject::connect(deleteBtn, &QPushButton::clicked, activityManager, [activityManager, activityId]() {
                activityManager->onDeleteActivityById(activityId);
            });
        }
    }
    
    // Adjust column widths
    table->setColumnWidth(0, 80);   // ID
    table->setColumnWidth(1, 150);  // Name
    table->setColumnWidth(2, 120);  // Type
    table->setColumnWidth(3, 100);  // Date
    table->setColumnWidth(4, 80);   // Time
    table->setColumnWidth(5, 120);  // Responsible
    table->setColumnWidth(6, 60);   // Age Req
    table->setColumnWidth(7, 90);   // Status
    table->setColumnWidth(8, 200);  // Description
    table->setColumnWidth(9, 80);   // Capacity
    table->setColumnWidth(reservedColumnIndex, 220); // Reserved equipment
    table->setColumnWidth(actionColumnIndex, 150); // Actions
}

void Activity::setupActivityTable()
{
    if (!ui) return;
    
    ui->activityTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->activityTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->activityTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->activityTable->setAlternatingRowColors(true);
    ui->activityTable->horizontalHeader()->setStretchLastSection(true);
    ui->activityTable->verticalHeader()->setVisible(false);
    
    refreshActivityTable();
}

void Activity::refreshActivityTable()
{
    if (!ui) return;
    populateActivityTableWidget(ui->activityTable, Activity::afficher(), this);
}

// ============================================================================
// UI METHODS - FORM MANAGEMENT
// ============================================================================

void Activity::onConfirmAdd()
{
    if (!ui) return;
    
    QString activityType = ui->activityTypeComboBox->currentText();
    QDate eventDate = ui->eventDateEdit->date();
    QTime eventTime = ui->eventTimeEdit->time();
    QString responsible = getResponsibleValue();
    int ageRequirement = ui->activityAgeSpinBox->value();
    QString status = ui->activityStatusComboBox->currentText();
    QString description = ui->activityDescriptionTextEdit->toPlainText().trimmed();
    int capacity = ui->activityCapacitySpinBox->value();
    
    Activity activity(0, activityType, eventDate, eventTime, responsible,
                     ageRequirement, status, description, capacity);
    
    if (activity.ajouter()) {
        QSqlQuery fetchIdQuery;
        fetchIdQuery.prepare("SELECT ID_A FROM ACTIVITIES "
                             "WHERE ACTIVITY_TYPE = :type "
                             "AND EVENT_DATE = :eventDate "
                             "AND EVENT_TIME = :eventTime "
                             "ORDER BY ID_A DESC");
        fetchIdQuery.bindValue(":type", activityType);
        fetchIdQuery.bindValue(":eventDate", eventDate);
        fetchIdQuery.bindValue(":eventTime", QDateTime(eventDate, eventTime));
        
        if (fetchIdQuery.exec() && fetchIdQuery.next()) {
            currentActivityId = fetchIdQuery.value(0).toInt();
        } else {
            currentActivityId = -1;
        }
        
        QMessageBox::information(parentWidget, "Success",
            QString("Activity '%1' added successfully!\nYou can now reserve equipment.")
                .arg(activityType));
        
        refreshActivityTable();
        refreshAvailableEquipment();
        
        if (ui && ui->activityTabWidget && ui->equipmentReservationTab) {
            int tabIndex = ui->activityTabWidget->indexOf(ui->equipmentReservationTab);
            if (tabIndex != -1) {
                ui->activityTabWidget->setCurrentIndex(tabIndex);
            }
        }
    } else {
        // Show detailed validation error message
        QString errorMsg = "Please fix the following errors:\n\n";
        
        if (activityType.trimmed().isEmpty() ||
            responsible.trimmed().isEmpty() || status.trimmed().isEmpty() ||
            !eventDate.isValid() || !eventTime.isValid()) {
            errorMsg += "• All fields must be filled (description is optional)\n";
        }
        if (!responsible.contains(QRegularExpression("^[A-Za-z\\s\\-']+$"))) {
            errorMsg += "• Responsible person name can only contain letters, spaces, hyphens, and apostrophes\n";
        }
        if (ageRequirement < 0 || ageRequirement > 100) {
            errorMsg += "• Age requirement must be between 0 and 100\n";
        }
        
        QMessageBox::critical(parentWidget, "Validation Error", errorMsg);
    }
}

void Activity::onConfirmUpdate()
{
    if (!ui || editingId <= 0) return;
    
    QString activityType = ui->activityTypeComboBox->currentText();
    
    Activity activity(
        editingId,
        activityType,
        ui->eventDateEdit->date(),
        ui->eventTimeEdit->time(),
        getResponsibleValue(),
        ui->activityAgeSpinBox->value(),
        ui->activityStatusComboBox->currentText(),
        ui->activityDescriptionTextEdit->toPlainText().trimmed(),
        ui->activityCapacitySpinBox->value()
    );
    
    if (activity.modifier()) {
        QMessageBox::information(parentWidget, "Success", "Activity updated successfully!");
        clearActivityForm();
        refreshActivityTable();
        editingId = -1;
    } else {
        QMessageBox::critical(parentWidget, "Error", "Failed to update activity. Please check validation.");
    }
}

void Activity::onConfirmDelete()
{
    if (!ui) return;
    QModelIndexList selected = ui->activityTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(parentWidget, "No Selection", "Please select an activity to delete.");
        return;
    }
    
    int row = selected.first().row();
    int idA = ui->activityTable->item(row, 0)->text().toInt();
    QString activityType = ui->activityTable->item(row, 1)->text();
    
    if (QMessageBox::question(parentWidget, "Confirm Delete",
                              QString("Delete activity '%1' (ID: %2)?").arg(activityType).arg(idA)) == QMessageBox::Yes) {
        Activity activity;
        if (activity.supprimer(idA)) {
            QMessageBox::information(parentWidget, "Success", "Activity deleted successfully!");
            refreshActivityTable();
        } else {
            QMessageBox::critical(parentWidget, "Error", "Failed to delete activity.");
        }
    }
}

void Activity::clearActivityForm()
{
    if (!ui) return;
    ui->responsibleComboBox->setCurrentIndex(0);
    ui->responsibleLineEdit->clear();
    ui->activityDescriptionTextEdit->clear();
    ui->activityTypeComboBox->setCurrentIndex(0);
    ui->activityStatusComboBox->setCurrentIndex(0);
    ui->activityAgeSpinBox->setValue(5);
    ui->activityCapacitySpinBox->setValue(30); // Default capacity
    ui->eventDateEdit->setDate(QDate::currentDate());
    ui->eventTimeEdit->setTime(QTime::currentTime());
    editingId = -1;
    
    // Reset to add mode UI
    ui->activityConfirmButton->setVisible(true);
    ui->activityUpdateButton->setVisible(false);
    
    currentActivityId = -1;
    clearReservation();
    refreshAvailableEquipment();
}

// ============================================================================
// UI METHODS - ACTIONS
// ============================================================================

void Activity::onEditActivityById(int idA)
{
    Activity* activity = Activity::rechercherParId(idA);
    if (activity) {
        loadActivityToForm(activity);
        delete activity;
    } else {
        QMessageBox::warning(parentWidget, "Not Found", "Activity not found!");
    }
}

void Activity::onDeleteActivityById(int idA)
{
    Activity* activity = Activity::rechercherParId(idA);
    if (!activity) {
        QMessageBox::warning(parentWidget, "Not Found", "Activity not found!");
        return;
    }
    
    QString activityType = activity->getActivityType();
    delete activity;
    
    if (QMessageBox::question(parentWidget, "Confirm Delete",
                              QString("Delete activity '%1' (ID: %2)?").arg(activityType).arg(idA)) == QMessageBox::Yes) {
        Activity temp;
        if (temp.supprimer(idA)) {
            QMessageBox::information(parentWidget, "Success", "Activity deleted successfully!");
            refreshActivityTable();
        } else {
            QMessageBox::critical(parentWidget, "Error", "Failed to delete activity.");
        }
    }
}

void Activity::onEditActivity(int row)
{
    if (!ui || row < 0 || row >= ui->activityTable->rowCount()) return;
    int idA = ui->activityTable->item(row, 0)->text().toInt();
    onEditActivityById(idA);
}

void Activity::onDeleteActivity(int row)
{
    if (!ui || row < 0 || row >= ui->activityTable->rowCount()) return;
    int idA = ui->activityTable->item(row, 0)->text().toInt();
    onDeleteActivityById(idA);
}

void Activity::onSortActivities()
{
    if (!ui || !ui->activityTable) return;
    
    // Enable sorting if not already enabled
    if (!ui->activityTable->isSortingEnabled()) {
        ui->activityTable->setSortingEnabled(true);
    }
    
    // Sort by event date (column 2 - now that NAME is removed)
    static Qt::SortOrder order = Qt::AscendingOrder;
    order = (order == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    ui->activityTable->sortItems(2, order);
}

void Activity::onSortComboBoxChanged(int index)
{
    if (!ui || !ui->activityTable) return;
    
    // Enable sorting if not already enabled
    if (!ui->activityTable->isSortingEnabled()) {
        ui->activityTable->setSortingEnabled(true);
    }
    
    // Column mapping (after NAME removal):
    // 0: ID_A
    // 1: ACTIVITY_TYPE
    // 2: EVENT_DATE
    // 3: EVENT_TIME
    // 4: RESPONSIBLE
    // 5: AGE_REQUIREMENT
    // 6: STATUS
    // 7: DESCRIPTION
    // 8: CAPACITY
    
    int sortColumn = 2; // Default to Event Date
    
    switch (index) {
        case 0: // Sort by Date
            sortColumn = 2; // EVENT_DATE
            break;
        case 1: // Sort by Age
            sortColumn = 5; // AGE_REQUIREMENT
            break;
        case 2: // Sort by Activity (Type)
            sortColumn = 1; // ACTIVITY_TYPE
            break;
        default:
            sortColumn = 2;
            break;
    }
    
    // Sort in ascending order
    ui->activityTable->sortItems(sortColumn, Qt::AscendingOrder);
}

void Activity::onExportActivities()
{
    if (!ui) return;
    exportTableToPdf(ui->activityTable, "activities_export.pdf", "List of Activities");
}

void Activity::onSearchActivities()
{
    if (!ui) return;
    QString search = ui->activitySearchLineEdit->text().trimmed();
    if (search.isEmpty()) {
        refreshActivityTable();
    } else {
        populateActivityTableWidget(ui->activityTable, Activity::rechercherParResponsible(search), this);
    }
}

void Activity::onFilterByType()
{
    if (!ui) return;
    QString type = ui->activityTypeComboBox->currentText();
    if (type == "All" || type.isEmpty()) {
        refreshActivityTable();
    } else {
        populateActivityTableWidget(ui->activityTable, Activity::filtrerParType(type), this);
    }
}

void Activity::onFilterByStatus()
{
    if (!ui) return;
    QString status = ui->activityStatusComboBox->currentText();
    if (status == "All" || status.isEmpty()) {
        refreshActivityTable();
    } else {
        populateActivityTableWidget(ui->activityTable, Activity::filtrerParStatut(status), this);
    }
}

// ============================================================================
// HELPER METHODS
// ============================================================================

void Activity::loadActivityToForm(Activity* activity)
{
    if (!activity || !ui) return;
    editingId = activity->getIdA();
    currentActivityId = activity->getIdA();
    clearReservation();
    refreshAvailableEquipment();
    // ID field removed from UI - it's auto-generated and shown in table only
    ui->activityTypeComboBox->setCurrentText(activity->getActivityType());
    ui->eventDateEdit->setDate(activity->getEventDate());
    ui->eventTimeEdit->setTime(activity->getEventTime());
    
    // Set responsible in both widgets
    ui->responsibleComboBox->setCurrentText(activity->getResponsible());
    ui->responsibleLineEdit->setText(activity->getResponsible());
    
    ui->activityAgeSpinBox->setValue(activity->getAgeRequirement());
    ui->activityCapacitySpinBox->setValue(activity->getCapacity()); // Load capacity
    ui->activityStatusComboBox->setCurrentText(activity->getStatus());
    ui->activityDescriptionTextEdit->setPlainText(activity->getDescription());
    
    // Switch to edit mode UI
    ui->activityConfirmButton->setVisible(false);
    ui->activityUpdateButton->setVisible(true);
    ui->activityTabWidget->setCurrentIndex(1); // Switch to Add/Edit tab
}

bool Activity::exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title)
{
    if (!table) return false;
    QString file = QFileDialog::getSaveFileName(parentWidget, "Export PDF", defaultName, "PDF (*.pdf)");
    if (file.isEmpty()) return false;
    
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    
    QTextDocument doc;
    QString html = "<html><head><style>";
    html += "table { border-collapse: collapse; width: 100%; font-family: Arial; }";
    html += "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }";
    html += "th { background-color: #16a5b3; color: white; font-weight: bold; }";
    html += "tr:nth-child(even) { background-color: #f9f9f9; }";
    html += ".title { font-size: 20px; font-weight: bold; text-align: center; margin-bottom: 10px; }";
    html += "</style></head><body>";
    
    html += QString("<div class='title'>%1</div>").arg(title);
    html += "<div style='text-align:center; margin-bottom:20px; color:#666;'>Generated: " + 
            QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm") + "</div>";
    
    html += "<table><tr>";
    
    // Add headers (exclude Actions column)
    int colCount = table->columnCount() - 1;
    for (int c = 0; c < colCount; ++c) {
        QTableWidgetItem* headerItem = table->horizontalHeaderItem(c);
        html += "<th>" + (headerItem ? headerItem->text() : "") + "</th>";
    }
    html += "</tr>";
    
    // Add data rows
    for (int r = 0; r < table->rowCount(); ++r) {
        html += "<tr>";
        for (int c = 0; c < colCount; ++c) {
            QTableWidgetItem* item = table->item(r, c);
            html += "<td>" + (item ? item->text() : "") + "</td>";
        }
        html += "</tr>";
    }
    
    html += "</table></body></html>";
    
    doc.setHtml(html);
    doc.print(&printer);
    
    QMessageBox::information(parentWidget, "Success", "Activities exported to PDF successfully!");
    return true;
}

// Load employee names from database into combobox
void Activity::loadEmployeesToComboBox()
{
    if (!ui) return;
    
    QSqlQuery query;
    query.prepare("SELECT FIRST_NAME || ' ' || LAST_NAME AS FULL_NAME "
                  "FROM EMPLOYEES "
                  "ORDER BY LAST_NAME, FIRST_NAME");
    
    ui->responsibleComboBox->clear();
    ui->responsibleComboBox->addItem("Select Employee...");
    
    if (query.exec()) {
        while (query.next()) {
            QString fullName = query.value(0).toString();
            if (!fullName.trimmed().isEmpty()) {
                ui->responsibleComboBox->addItem(fullName);
            }
        }
    } else {
        qDebug() << "Failed to load employees:" << query.lastError().text();
    }
}

// Get the responsible value from the active input mode
QString Activity::getResponsibleValue() const
{
    if (!ui) return "";
    
    if (useEmployeeComboBox) {
        QString selected = ui->responsibleComboBox->currentText();
        return (selected == "Select Employee...") ? "" : selected;
    } else {
        return ui->responsibleLineEdit->text().trimmed();
    }
}

// Toggle between employee combobox and manual text input
void Activity::onToggleResponsibleInput()
{
    if (!ui) return;
    
    useEmployeeComboBox = !useEmployeeComboBox;
    
    ui->responsibleComboBox->setVisible(useEmployeeComboBox);
    ui->responsibleLineEdit->setVisible(!useEmployeeComboBox);
    
    if (useEmployeeComboBox) {
        ui->responsibleToggleButton->setText("Use Manual");
    } else {
        ui->responsibleToggleButton->setText("Use Employee List");
    }
}

// ============================================================================
// EQUIPMENT RESERVATION METHODS
// ============================================================================

void Activity::setupEquipmentReservation()
{
    if (!ui) return;
    
    setupAvailableEquipmentTable();
    setupReservedEquipmentTable();
    
    if (ui->refreshEquipmentButton) {
        connect(ui->refreshEquipmentButton, &QPushButton::clicked,
                this, &Activity::refreshAvailableEquipment, Qt::UniqueConnection);
    }
    
    if (ui->addToReservationButton) {
        connect(ui->addToReservationButton, &QPushButton::clicked,
                this, &Activity::addSelectedToReservation, Qt::UniqueConnection);
    }
    
    if (ui->confirmReservationButton) {
        connect(ui->confirmReservationButton, &QPushButton::clicked,
                this, &Activity::confirmEquipmentReservation, Qt::UniqueConnection);
    }
    
    if (ui->clearReservationButton) {
        connect(ui->clearReservationButton, &QPushButton::clicked,
                this, &Activity::clearReservation, Qt::UniqueConnection);
    }
    
    if (ui->eventDateEdit) {
        connect(ui->eventDateEdit, &QDateEdit::dateChanged,
                this, &Activity::refreshAvailableEquipment, Qt::UniqueConnection);
    }
    
    if (ui->reserveQuantitySpinBox) {
        connect(ui->reserveQuantitySpinBox, qOverload<int>(&QSpinBox::valueChanged),
                this, &Activity::onReserveQuantityChanged, Qt::UniqueConnection);
    }
    
    reservedEquipment.clear();
    updateReservedTotal();
    refreshAvailableEquipment();
}

void Activity::setupAvailableEquipmentTable()
{
    if (!ui || !ui->availableEquipmentTable) return;
    
    QTableWidget *table = ui->availableEquipmentTable;
    table->clear();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList()
                                     << "Select"
                                     << "Equipment Name"
                                     << "Category"
                                     << "Available Qty"
                                     << "Reserve Qty");
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionsClickable(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setRowCount(0);
    table->setColumnWidth(0, 70);
    table->setColumnWidth(1, 220);
    table->setColumnWidth(2, 160);
    table->setColumnWidth(3, 120);
    table->setColumnWidth(4, 120);
}

void Activity::setupReservedEquipmentTable()
{
    if (!ui || !ui->reservedEquipmentTable) return;
    
    QTableWidget *table = ui->reservedEquipmentTable;
    table->clear();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList()
                                     << "Equipment Name"
                                     << "Reserved Qty"
                                     << "Actions");
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setRowCount(0);
    table->setColumnWidth(0, 250);
    table->setColumnWidth(1, 120);
    table->setColumnWidth(2, 120);
    
    updateReservedTotal();
}

void Activity::refreshAvailableEquipment()
{
    if (!ui || !ui->availableEquipmentTable) return;
    
    QTableWidget *table = ui->availableEquipmentTable;
    table->setRowCount(0);
    
    QDate selectedDate = ui->eventDateEdit ? ui->eventDateEdit->date() : QDate::currentDate();
    QSqlQueryModel *model = getAvailableEquipment(selectedDate);
    
    if (!model) {
        return;
    }
    
    int targetRow = 0;
    for (int row = 0; row < model->rowCount(); ++row) {
        QSqlRecord record = model->record(row);
        int equipmentId = record.value("ID_EQ").toInt();
        QString name = record.value("NAME").toString();
        QString category = record.value("CATEGORY").toString();
        int availableQty = record.value("QTY_AVAILABLE").toInt();
        
        if (availableQty <= 0) {
            continue;
        }
        
        table->insertRow(targetRow);
        
        QTableWidgetItem *selectItem = new QTableWidgetItem();
        selectItem->setFlags(selectItem->flags() & ~Qt::ItemIsEditable);
        selectItem->setCheckState(Qt::Unchecked);
        selectItem->setData(Qt::UserRole, equipmentId);
        table->setItem(targetRow, 0, selectItem);
        
        QTableWidgetItem *nameItem = new QTableWidgetItem(name);
        nameItem->setData(Qt::UserRole, equipmentId);
        table->setItem(targetRow, 1, nameItem);
        table->setItem(targetRow, 2, new QTableWidgetItem(category));
        table->setItem(targetRow, 3, new QTableWidgetItem(QString::number(availableQty)));
        
        QSpinBox *quantitySpinBox = new QSpinBox(table);
        quantitySpinBox->setMinimum(1);
        quantitySpinBox->setMaximum(availableQty);
        int defaultQty = (ui->reserveQuantitySpinBox ? ui->reserveQuantitySpinBox->value() : 1);
        quantitySpinBox->setValue(qBound(1, defaultQty, availableQty));
        table->setCellWidget(targetRow, 4, quantitySpinBox);
        
        ++targetRow;
    }
    
    delete model;
}

void Activity::onReserveQuantityChanged(int value)
{
    if (!ui || !ui->availableEquipmentTable) return;
    
    const int desiredValue = qMax(1, value);
    QTableWidget *table = ui->availableEquipmentTable;
    for (int row = 0; row < table->rowCount(); ++row) {
        if (QSpinBox *spin = qobject_cast<QSpinBox*>(table->cellWidget(row, 4))) {
            spin->setValue(qBound(1, desiredValue, spin->maximum()));
        }
    }
}

QSqlQueryModel* Activity::getAvailableEquipment(const QDate& date)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    
    QString sql =
        "SELECT e.ID_EQ, e.NAME, e.CATEGORY, "
        "GREATEST(NVL(e.QUANTITY_AVAILABLE, e.AVAILABLE) - "
        "NVL((SELECT SUM(r.QUANTITY_RESERVED) "
        "      FROM EQUIPMENT_RESERVATIONS r "
        "      WHERE r.RESERVATION_DATE = :selectedDate "
        "        AND r.ID_EQUIPMENT = e.ID_EQ "
        "        AND (:currentActivityId IS NULL OR r.ID_ACTIVITY <> :currentActivityId)"
        "     ), 0), 0) AS QTY_AVAILABLE "
        "FROM EQUIPEMENTS e "
        "ORDER BY e.NAME";
    
    query.prepare(sql);
    query.bindValue(":selectedDate", date);
    if (currentActivityId > 0) {
        query.bindValue(":currentActivityId", currentActivityId);
    } else {
        query.bindValue(":currentActivityId", QVariant(QVariant::Int));
    }
    
    if (!query.exec()) {
        qDebug() << "Error fetching available equipment:" << query.lastError().text();
        delete model;
        return nullptr;
    }
    
    model->setQuery(query);
    if (model->lastError().isValid()) {
        qDebug() << "Model error while fetching equipment:" << model->lastError().text();
    }
    
    return model;
}

void Activity::addSelectedToReservation()
{
    if (!ui || !ui->availableEquipmentTable) return;
    
    bool anySelected = false;
    QTableWidget *table = ui->availableEquipmentTable;
    
    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem *selectItem = table->item(row, 0);
        if (!selectItem || selectItem->checkState() != Qt::Checked) {
            continue;
        }
        
        int equipmentId = selectItem->data(Qt::UserRole).toInt();
        if (equipmentId <= 0) {
            continue;
        }
        
        QString equipmentName = table->item(row, 1) ? table->item(row, 1)->text() : QString();
        int availableQty = table->item(row, 3) ? table->item(row, 3)->text().toInt() : 0;
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(table->cellWidget(row, 4));
        int requestedQty = spinBox ? spinBox->value() : 0;
        
        if (requestedQty <= 0) {
            continue;
        }
        
        int newQuantity = reservedEquipment.value(equipmentId, 0) + requestedQty;
        newQuantity = qMin(newQuantity, availableQty);
        reservedEquipment[equipmentId] = newQuantity;
        
        addToReservedTable(equipmentId, equipmentName, newQuantity);
        
        selectItem->setCheckState(Qt::Unchecked);
        if (spinBox) {
            spinBox->setValue(1);
        }
        
        anySelected = true;
    }
    
    if (!anySelected) {
        QMessageBox::information(parentWidget, "No Selection",
                                 "Please select at least one equipment item to reserve.");
    }
    
    updateReservedTotal();
}

void Activity::addToReservedTable(int equipmentId, const QString& name, int quantity)
{
    if (!ui || !ui->reservedEquipmentTable) return;
    
    QTableWidget *table = ui->reservedEquipmentTable;
    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem *item = table->item(row, 0);
        if (item && item->data(Qt::UserRole).toInt() == equipmentId) {
            item->setText(name);
            if (table->item(row, 1)) {
                table->item(row, 1)->setText(QString::number(quantity));
            } else {
                table->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
            }
            return;
        }
    }
    
    int row = table->rowCount();
    table->insertRow(row);
    
    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    nameItem->setData(Qt::UserRole, equipmentId);
    table->setItem(row, 0, nameItem);
    table->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
    
    QPushButton *removeButton = new QPushButton("Remove");
    removeButton->setProperty("equipmentId", equipmentId);
    connect(removeButton, &QPushButton::clicked, this, [this, equipmentId]() {
        reservedEquipment.remove(equipmentId);
        if (ui && ui->reservedEquipmentTable) {
            for (int r = 0; r < ui->reservedEquipmentTable->rowCount(); ++r) {
                QTableWidgetItem *item = ui->reservedEquipmentTable->item(r, 0);
                if (item && item->data(Qt::UserRole).toInt() == equipmentId) {
                    ui->reservedEquipmentTable->removeRow(r);
                    break;
                }
            }
        }
        updateReservedTotal();
    });
    table->setCellWidget(row, 2, removeButton);
}

void Activity::updateReservedTotal()
{
    if (!ui) return;
    
    int totalItems = 0;
    for (auto it = reservedEquipment.cbegin(); it != reservedEquipment.cend(); ++it) {
        totalItems += it.value();
    }
    
    if (ui->reservedTotalLabel) {
        ui->reservedTotalLabel->setText(QString("Total Reserved Items: %1").arg(totalItems));
    }
    
    const bool hasItems = totalItems > 0;
    if (ui->confirmReservationButton) {
        ui->confirmReservationButton->setEnabled(hasItems);
    }
    if (ui->clearReservationButton) {
        ui->clearReservationButton->setEnabled(hasItems);
    }
}

void Activity::confirmEquipmentReservation()
{
    if (reservedEquipment.isEmpty()) {
        QMessageBox::information(parentWidget, "No Reservation",
                                 "Select equipment and quantities before confirming.");
        return;
    }
    
    if (currentActivityId <= 0) {
        QMessageBox::warning(parentWidget, "Activity Required",
                             "Please save the activity details before reserving equipment.");
        return;
    }
    
    bool success = true;
    for (auto it = reservedEquipment.cbegin(); it != reservedEquipment.cend(); ++it) {
        if (!reserveEquipment(it.key(), it.value(), currentActivityId)) {
            success = false;
        }
    }
    
    if (success) {
        QMessageBox::information(parentWidget, "Reservation Saved",
                                 "Equipment reserved successfully!");
        clearReservation();
        refreshAvailableEquipment();
        refreshActivityTable();
    } else {
        QMessageBox::warning(parentWidget, "Reservation Error",
                             "Some equipment could not be reserved. Please review availability.");
        refreshAvailableEquipment();
    }
}

bool Activity::reserveEquipment(int equipmentId, int quantity, int activityId)
{
    // Get the next reservation ID from sequence (fallback if trigger doesn't exist)
    QSqlQuery seqQuery;
    int reservationId = 0;
    if (seqQuery.exec("SELECT SUMMERCLUB.SEQ_RESERVATIONS.NEXTVAL FROM DUAL")) {
        if (seqQuery.next()) {
            reservationId = seqQuery.value(0).toInt();
        }
    } else {
        // Try without schema prefix
        if (seqQuery.exec("SELECT SEQ_RESERVATIONS.NEXTVAL FROM DUAL")) {
            if (seqQuery.next()) {
                reservationId = seqQuery.value(0).toInt();
            }
        }
    }
    
    if (reservationId <= 0) {
        qDebug() << "Failed to get reservation ID from sequence:" << seqQuery.lastError().text();
        return false;
    }
    
    QSqlQuery insertQuery;
    insertQuery.prepare(
        "INSERT INTO EQUIPMENT_RESERVATIONS "
        "(ID_RESERVATION, ID_ACTIVITY, ID_EQUIPMENT, QUANTITY_RESERVED, RESERVATION_DATE, RETURN_DATE, STATUS) "
        "VALUES (:reservationId, :activityId, :equipmentId, :quantity, :startDate, :endDate, 'Reserved')");
    
    QDate reservationDate = (ui && ui->eventDateEdit) ? ui->eventDateEdit->date() : QDate::currentDate();
    
    insertQuery.bindValue(":reservationId", reservationId);
    insertQuery.bindValue(":activityId", activityId);
    insertQuery.bindValue(":equipmentId", equipmentId);
    insertQuery.bindValue(":quantity", quantity);
    insertQuery.bindValue(":startDate", reservationDate);
    insertQuery.bindValue(":endDate", reservationDate);
    
    if (!insertQuery.exec()) {
        qDebug() << "Failed to insert reservation:" << insertQuery.lastError().text();
        return false;
    }
    
    QSqlQuery updateQuery;
    updateQuery.prepare(
        "UPDATE EQUIPEMENTS SET "
        "QUANTITY_AVAILABLE = NVL(QUANTITY_AVAILABLE, AVAILABLE) - :qty, "
        "QUANTITY_RESERVED = NVL(QUANTITY_RESERVED, IN_USE) + :qty "
        "WHERE ID_EQ = :id");
    updateQuery.bindValue(":qty", quantity);
    updateQuery.bindValue(":id", equipmentId);
    
    if (!updateQuery.exec()) {
        qDebug() << "Failed to update equipment quantities:" << updateQuery.lastError().text();
        return false;
    }
    
    return true;
}

QString Activity::getReservedEquipmentSummary(int activityId) const
{
    QStringList parts;
    QSqlQuery query;
    query.prepare(
        "SELECT e.NAME, r.QUANTITY_RESERVED "
        "FROM EQUIPMENT_RESERVATIONS r "
        "JOIN EQUIPEMENTS e ON e.ID_EQ = r.ID_EQUIPMENT "
        "WHERE r.ID_ACTIVITY = :activityId "
        "ORDER BY e.NAME");
    query.bindValue(":activityId", activityId);
    
    if (query.exec()) {
        while (query.next()) {
            const QString name = query.value(0).toString();
            const int qty = query.value(1).toInt();
            parts << QString("%1 (%2)").arg(name).arg(qty);
        }
    } else {
        qDebug() << "Failed to fetch reserved equipment summary:"
                 << query.lastError().text();
    }
    
    return parts.join(", ");
}

void Activity::clearReservation()
{
    if (!ui) return;
    
    reservedEquipment.clear();
    
    if (ui->reservedEquipmentTable) {
        ui->reservedEquipmentTable->setRowCount(0);
    }
    
    if (ui->availableEquipmentTable) {
        for (int row = 0; row < ui->availableEquipmentTable->rowCount(); ++row) {
            QTableWidgetItem *selectItem = ui->availableEquipmentTable->item(row, 0);
            if (selectItem) {
                selectItem->setCheckState(Qt::Unchecked);
            }
            if (QSpinBox *spin = qobject_cast<QSpinBox*>(ui->availableEquipmentTable->cellWidget(row, 4))) {
                spin->setValue(1);
            }
        }
    }
    
    if (ui->reserveQuantitySpinBox) {
        ui->reserveQuantitySpinBox->setValue(1);
    }
    
    updateReservedTotal();
}
