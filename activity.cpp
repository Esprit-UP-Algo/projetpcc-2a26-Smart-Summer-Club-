#include "activity.h"
#include "ui_employeradmin.h"
#include "employeelogspanel.h"
#include <QRegularExpression>
#include <QDateTime>
#include <QTextDocument>
#include <QPrinter>
#include <QPageLayout>
#include <QFile>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>

// ============================================================================
// CONSTRUCTORS & DESTRUCTOR
// ============================================================================

Activity::Activity()
    : QObject(nullptr), idA(0), activityType(""), eventDate(QDate::currentDate()),
      eventTime(QTime::currentTime()), responsible(""), ageRequirement(0),
      status("Scheduled"), description(""), capacity(0),
      ui(nullptr), parentWidget(nullptr), editingId(-1), useEmployeeComboBox(true)
{
}

Activity::Activity(int idA, QString activityType, QDate eventDate,
                   QTime eventTime, QString responsible, int ageRequirement,
                   QString status, QString description, int capacity)
    : QObject(nullptr), idA(idA), activityType(activityType),
      eventDate(eventDate), eventTime(eventTime), responsible(responsible),
      ageRequirement(ageRequirement), status(status), description(description),
      capacity(capacity), ui(nullptr), parentWidget(nullptr), editingId(-1), useEmployeeComboBox(true)
{
}

Activity::Activity(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), idA(0), activityType(""), eventDate(QDate::currentDate()),
      eventTime(QTime::currentTime()), responsible(""), ageRequirement(0),
      status("Scheduled"), description(""), capacity(0),
      ui(ui), parentWidget(parent), editingId(-1), useEmployeeComboBox(true)
{
    // Load employees into combobox and setup initial state
    loadEmployeesToComboBox();
    
    // Initially show combobox, hide lineedit
    if (ui) {
        ui->responsibleComboBox->setVisible(true);
        ui->responsibleLineEdit->setVisible(false);
        ui->responsibleToggleButton->setText("Use Manual");
    }
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
        
        // Log the CREATE action
        QJsonObject activityData;
        activityData["id"] = "auto-generated";
        activityData["activity_type"] = activityType;
        activityData["event_date"] = eventDate.toString("yyyy-MM-dd");
        activityData["event_time"] = eventTime.toString("hh:mm:ss");
        activityData["responsible"] = responsible;
        activityData["age_requirement"] = ageRequirement;
        activityData["status"] = status;
        activityData["description"] = description;
        activityData["capacity"] = capacity;
        
        QJsonDocument doc(activityData);
        EmployeeLogsPanel::logAction("CREATE", "Activity", "auto-generated", "", 
                                   doc.toJson(QJsonDocument::Compact), "New activity created");
        
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
    // Get activity data before deletion for logging
    QJsonObject beforeData;
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM ACTIVITIES WHERE ID_A = :idA");
    selectQuery.bindValue(":idA", idA);
    
    if (selectQuery.exec() && selectQuery.next()) {
        beforeData["id"] = selectQuery.value("ID_A").toString();
        beforeData["activity_type"] = selectQuery.value("ACTIVITY_TYPE").toString();
        beforeData["event_date"] = selectQuery.value("EVENT_DATE").toString();
        beforeData["event_time"] = selectQuery.value("EVENT_TIME").toString();
        beforeData["responsible"] = selectQuery.value("RESPONSIBLE").toString();
        beforeData["age_requirement"] = selectQuery.value("AGE_REQUIREMENT").toString();
        beforeData["status"] = selectQuery.value("STATUS").toString();
        beforeData["description"] = selectQuery.value("DESCRIPTION").toString();
        beforeData["capacity"] = selectQuery.value("CAPACITY").toString();
    }
    
    QSqlQuery query;
    query.prepare("DELETE FROM ACTIVITIES WHERE ID_A = :idA");
    query.bindValue(":idA", idA);
    
    if (query.exec()) {
        qDebug() << "Activity deleted successfully:" << idA;
        
        // Log the DELETE action
        QJsonDocument doc(beforeData);
        EmployeeLogsPanel::logAction("DELETE", "Activity", QString::number(idA), 
                                   doc.toJson(QJsonDocument::Compact), "", 
                                   QString("Activity deleted (ID: %1)").arg(idA));
        
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
        
        // Log the UPDATE action
        QJsonObject afterData;
        afterData["id"] = QString::number(idA);
        afterData["activity_type"] = activityType;
        afterData["event_date"] = eventDate.toString("yyyy-MM-dd");
        afterData["event_time"] = eventTime.toString("hh:mm:ss");
        afterData["responsible"] = responsible;
        afterData["age_requirement"] = ageRequirement;
        afterData["status"] = status;
        afterData["description"] = description;
        afterData["capacity"] = capacity;
        
        QJsonDocument doc(afterData);
        EmployeeLogsPanel::logAction("UPDATE", "Activity", QString::number(idA), "", 
                                   doc.toJson(QJsonDocument::Compact), 
                                   QString("Activity modified (ID: %1)").arg(idA));
        
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
    int actionColumnIndex = storedCols; // Actions column is after data columns
    
    table->setColumnCount(storedCols + 1); // +1 for Actions column
    
    // Set headers
    QStringList headers;
    for (int c = 0; c < storedCols; ++c) {
        headers << model->headerData(c, Qt::Horizontal).toString();
    }
    headers << "Actions";
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
        QMessageBox::information(parentWidget, "Success",
            QString("Activity '%1' added successfully!").arg(activityType));
        clearActivityForm();
        refreshActivityTable();
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
