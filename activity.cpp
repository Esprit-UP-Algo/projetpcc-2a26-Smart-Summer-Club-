#include "activity.h"
#include "ui_employeradmin.h"
#include "employeelogspanel.h"
#include <QRegularExpression>
#include <QDateTime>
#include <QTextDocument>
#include <QPrinter>
#include <QPageLayout>
#include <QPageSize>
#include <QPainter>
#include <QImage>
#include <QFile>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QProcess>
#include <QDir>
#include <QStandardPaths>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QFileDialog>
#include <QApplication>
#include <QProcessEnvironment>

// ============================================================================
// CONSTRUCTORS & DESTRUCTOR
// ============================================================================
/// bla blalaalla lbababab  azdazdazdazd
Activity::Activity()
    : QObject(nullptr), idA(0), activityType(""), eventDate(QDate::currentDate()),
      eventTime(QTime::currentTime()), responsible(""), ageRequirement(0),
      status("Scheduled"), description(""), capacity(0),
      ui(nullptr), parentWidget(nullptr), editingId(-1), useEmployeeComboBox(true),
      sortAscending(true)
{
}

Activity::Activity(int idA, QString activityType, QDate eventDate,
                   QTime eventTime, QString responsible, int ageRequirement,
                   QString status, QString description, int capacity)
    : QObject(nullptr), idA(idA), activityType(activityType),
      eventDate(eventDate), eventTime(eventTime), responsible(responsible),
      ageRequirement(ageRequirement), status(status), description(description),
      capacity(capacity), ui(nullptr), parentWidget(nullptr), editingId(-1), useEmployeeComboBox(true),
      sortAscending(true)
{
}

Activity::Activity(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), idA(0), activityType(""), eventDate(QDate::currentDate()),
      eventTime(QTime::currentTime()), responsible(""), ageRequirement(0),
      status("Scheduled"), description(""), capacity(0),
      ui(ui), parentWidget(parent), editingId(-1), useEmployeeComboBox(true),
      sortAscending(true)
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
        layout->setContentsMargins(2, 2, 2, 2);
        layout->setSpacing(4);
        
        QPushButton* editBtn = new QPushButton("Edit", actionWidget);
        QPushButton* deleteBtn = new QPushButton("Delete", actionWidget);
        editBtn->setIcon(QIcon(":/icons/icons/edit.png"));
        deleteBtn->setIcon(QIcon(":/icons/icons/delete.png"));
        editBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        deleteBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
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
    
    // Make sort indicator arrows bigger and more visible
    ui->activityTable->setStyleSheet(
        ui->activityTable->styleSheet() + 
        "QHeaderView::down-arrow { "
        "    image: url(:/icons/icons/arrow-down.png); "
        "    width: 20px; "
        "    height: 20px; "
        "} "
        "QHeaderView::up-arrow { "
        "    image: url(:/icons/icons/arrow-up.png); "
        "    width: 20px; "
        "    height: 20px; "
        "}"
    );
    
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
    
    // Sort by event date (column 2)
    ui->activityTable->sortItems(2, sortAscending ? Qt::AscendingOrder : Qt::DescendingOrder);
    
    // Toggle sort order
    sortAscending = !sortAscending;
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
    
    // Create export configuration dialog
    QDialog dialog(parentWidget);
    dialog.setWindowTitle("Export Poster to PDF Configuration");
    dialog.setModal(true);
    dialog.resize(500, 300);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    // Background image selection
    QHBoxLayout* bgLayout = new QHBoxLayout();
    QLabel* bgLabel = new QLabel("Background Image:");
    QLineEdit* bgLineEdit = new QLineEdit();
    bgLineEdit->setPlaceholderText("Select background image...");
    QPushButton* bgBrowseBtn = new QPushButton("Browse");
    
    bgLayout->addWidget(bgLabel);
    bgLayout->addWidget(bgLineEdit);
    bgLayout->addWidget(bgBrowseBtn);
    layout->addLayout(bgLayout);
    
    // QR code position
    QHBoxLayout* posLayout = new QHBoxLayout();
    QLabel* posLabel = new QLabel("QR Code Position:");
    QLabel* xLabel = new QLabel("X:");
    QSpinBox* xSpinBox = new QSpinBox();
    xSpinBox->setRange(0, 9999);
    xSpinBox->setValue(417); // Default X
    QLabel* yLabel = new QLabel("Y:");
    QSpinBox* ySpinBox = new QSpinBox();
    ySpinBox->setRange(0, 9999);
    ySpinBox->setValue(216); // Default Y
    
    posLayout->addWidget(posLabel);
    posLayout->addWidget(xLabel);
    posLayout->addWidget(xSpinBox);
    posLayout->addWidget(yLabel);
    posLayout->addWidget(ySpinBox);
    posLayout->addStretch();
    layout->addLayout(posLayout);
    
    // Output path selection
    QHBoxLayout* outLayout = new QHBoxLayout();
    QLabel* outLabel = new QLabel("Save to:");
    QLineEdit* outLineEdit = new QLineEdit();
    outLineEdit->setPlaceholderText("Select output location...");
    QPushButton* outBrowseBtn = new QPushButton("Browse");
    
    outLayout->addWidget(outLabel);
    outLayout->addWidget(outLineEdit);
    outLayout->addWidget(outBrowseBtn);
    layout->addLayout(outLayout);
    
    // Buttons
    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* okBtn = new QPushButton("Generate Poster & PDF");
    QPushButton* cancelBtn = new QPushButton("Cancel");
    btnLayout->addStretch();
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);
    
    // Connect browse buttons
    QObject::connect(bgBrowseBtn, &QPushButton::clicked, [&]() {
        QString file = QFileDialog::getOpenFileName(&dialog, "Select Background Image", 
            "", "Image Files (*.png *.jpg *.jpeg *.bmp)");
        if (!file.isEmpty()) {
            bgLineEdit->setText(file);
        }
    });
    
    QObject::connect(outBrowseBtn, &QPushButton::clicked, [&]() {
        QString file = QFileDialog::getSaveFileName(&dialog, "Save Poster As", 
            "poster_with_qr.png", "PNG Files (*.png);;PDF Files (*.pdf)");
        if (!file.isEmpty()) {
            outLineEdit->setText(file);
        }
    });
    
    QObject::connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    QObject::connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        QString bgImage = bgLineEdit->text().trimmed();
        QString outputPath = outLineEdit->text().trimmed();
        int qrX = xSpinBox->value();
        int qrY = ySpinBox->value();
        
        if (bgImage.isEmpty()) {
            QMessageBox::warning(parentWidget, "Warning", "Please select a background image.");
            return;
        }
        
        if (outputPath.isEmpty()) {
            QMessageBox::warning(parentWidget, "Warning", "Please select an output location.");
            return;
        }
        
        // Validate background image exists
        if (!QFile::exists(bgImage)) {
            QMessageBox::warning(parentWidget, "Warning", "Background image file does not exist.");
            return;
        }
        
        // Ensure output directory exists
        QFileInfo outputInfo(outputPath);
        QDir outputDir = outputInfo.absoluteDir();
        if (!outputDir.exists()) {
            if (!outputDir.mkpath(outputDir.absolutePath())) {
                QMessageBox::warning(parentWidget, "Warning", "Cannot create output directory.");
                return;
            }
        }
        
        // Convert to absolute paths to avoid working directory issues
        QString absoluteBgImage = QFileInfo(bgImage).absoluteFilePath();
        QString absoluteOutputPath = QFileInfo(outputPath).absoluteFilePath();
        
        // Check if user wants PDF output directly
        bool pdfOutput = outputPath.toLower().endsWith(".pdf");
        QString tempImagePath = absoluteOutputPath;
        
        if (pdfOutput) {
            // If PDF is requested, create a temporary PNG file first
            tempImagePath = absoluteOutputPath;
            tempImagePath.replace(".pdf", "_temp.png");
        }
        
        // Get the node script path using the same approach as OCR interface
        QString scriptPath = getNodeScriptPath();
        if (scriptPath.isEmpty()) {
            QMessageBox::critical(parentWidget, "Error", "Cannot find qr_adder.js script!");
            return;
        }
        
        QFileInfo scriptInfo(scriptPath);
        QString nodeScriptsPath = scriptInfo.absolutePath();
        
        QProcess process;
        process.setWorkingDirectory(nodeScriptsPath);
        
        QStringList arguments;
        arguments << scriptInfo.fileName() << absoluteBgImage << QString::number(qrX) 
                 << QString::number(qrY) << tempImagePath;
        
        // Create activity JSON file with current selected activity data
        if (!createActivityJsonFile(nodeScriptsPath)) {
            QMessageBox::critical(parentWidget, "Error", "Failed to create activity data file!");
            return;
        }
        
        // Debug information
        qDebug() << "Working directory:" << nodeScriptsPath;
        qDebug() << "Background image:" << absoluteBgImage;
        qDebug() << "Temp image path:" << tempImagePath;
        qDebug() << "Final output path:" << absoluteOutputPath;
        qDebug() << "PDF output mode:" << pdfOutput;
        qDebug() << "Arguments:" << arguments;
        
        process.start("node", arguments);
        process.waitForFinished(15000); // Wait up to 15 seconds
        
        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();
        
        if (process.exitCode() == 0) {
            // Check if image file was created
            if (QFile::exists(tempImagePath)) {
                if (pdfOutput) {
                    // Create PDF with the generated image
                    if (createPdfWithImage(tempImagePath, absoluteOutputPath)) {
                        // Clean up temporary image file
                        QFile::remove(tempImagePath);
                        QMessageBox::information(parentWidget, "Success", 
                            QString("Poster with QR code generated and exported to PDF successfully!\n\nPDF saved to: %1").arg(absoluteOutputPath));
                    } else {
                        QMessageBox::warning(parentWidget, "Partial Success", 
                            QString("Poster image generated successfully but PDF creation failed.\n\nImage saved to: %1").arg(tempImagePath));
                    }
                } else {
                    // PNG output - also create PDF alongside
                    QString pdfPath = absoluteOutputPath;
                    pdfPath.replace(".png", ".pdf");
                    
                    if (createPdfWithImage(absoluteOutputPath, pdfPath)) {
                        QMessageBox::information(parentWidget, "Success", 
                            QString("Poster with QR code generated and exported to PDF successfully!\n\nImage saved to: %1\nPDF saved to: %2").arg(absoluteOutputPath, pdfPath));
                    } else {
                        QMessageBox::warning(parentWidget, "Partial Success", 
                            QString("Poster image generated successfully but PDF creation failed.\n\nImage saved to: %1").arg(absoluteOutputPath));
                    }
                }
            } else {
                QMessageBox::warning(parentWidget, "Warning", 
                    QString("Process completed but file not found at: %1\n\nWorking dir: %2\nOutput: %3").arg(tempImagePath, nodeScriptsPath, output));
            }
        } else {
            QMessageBox::critical(parentWidget, "Error", 
                QString("Failed to generate poster:\n\nWorking dir: %1\nError: %2\n\nOutput: %3").arg(nodeScriptsPath, error, output));
        }
    }
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

QString Activity::getNodeScriptPath() const
{
    // First ensure the nodeJsScripts folder exists in Qt workspace
    if (!ensureNodeJsScriptsExists()) {
        qDebug() << "❌ Failed to ensure nodeJsScripts exists in Qt workspace";
        return QString();
    }
    
    // Use Qt workspace location (where files are copied)
    QString buildDir = QApplication::applicationDirPath();
    QDir dir(buildDir);
    
    // Navigate to Qt workspace root
    dir.cdUp();  // Go up from Debug to build directory
    dir.cdUp();  // Go up from build to project root directory
    
    QString qtWorkspaceRoot = dir.absolutePath();
    
    // Try qr_adder.js in nodeJsScripts directory
    QString scriptPath = qtWorkspaceRoot + "/nodeJsScripts/qr_adder.js";
    
    qDebug() << "Looking for QR script at:" << scriptPath;
    
    if (QFileInfo::exists(scriptPath)) {
        return scriptPath;
    }
    
    qDebug() << "QR script not found in Qt workspace, script does not exist at:" << scriptPath;
    return QString(); // Return empty string if not found
}

bool Activity::ensureNodeJsScriptsExists() const
{
    // Get Qt workspace location
    QString buildDir = QApplication::applicationDirPath();
    QDir dir(buildDir);
    dir.cdUp(); dir.cdUp(); // Navigate to Qt workspace root
    QString qtWorkspaceRoot = dir.absolutePath();
    QString destNodeScriptsDir = qtWorkspaceRoot + "/nodeJsScripts";
    
    // Find the actual project location
    QString actualProjectPath = findActualProjectLocation();
    if (actualProjectPath.isEmpty()) {
        qDebug() << "❌ Could not find actual project location";
        return false;
    }
    
    QString sourceNodeScriptsDir = actualProjectPath + "/nodeJsScripts";
    QDir sourceDir(sourceNodeScriptsDir);
    
    if (!sourceDir.exists()) {
        qDebug() << "❌ Source nodeJsScripts folder does not exist:" << sourceNodeScriptsDir;
        return false;
    }
    
    // Always refresh: remove old destination folder if it exists
    QDir destDir(destNodeScriptsDir);
    if (destDir.exists()) {
        qDebug() << "🔄 Refreshing nodeJsScripts folder (removing old version)...";
        destDir.removeRecursively();
    }
    
    qDebug() << "📋 Copying nodeJsScripts from:" << sourceNodeScriptsDir;
    qDebug() << "📋 Copying nodeJsScripts to:" << destNodeScriptsDir;
    
    // Copy the entire nodeJsScripts directory
    if (copyDirectoryRecursively(sourceNodeScriptsDir, destNodeScriptsDir)) {
        // Verify the copy was successful
        QDir destDirVerify(destNodeScriptsDir);
        QStringList copiedFiles = destDirVerify.entryList(QDir::Files);
        qDebug() << "✅ Successfully copied nodeJsScripts to Qt workspace";
        qDebug() << "📄 Copied files:" << copiedFiles;
        return true;
    } else {
        qDebug() << "❌ Failed to copy nodeJsScripts to Qt workspace";
        return false;
    }
}

QString Activity::findActualProjectLocation() const
{
    // Start from the application directory (build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug)
    QString buildDir = QApplication::applicationDirPath();
    QDir dir(buildDir);
    
    qDebug() << "Starting search from application directory:" << buildDir;
    
    // Navigate up from build directory to project root
    // Typical structure: project_root/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug
    dir.cdUp();  // Go to Desktop_Qt_6_7_3_MinGW_64_bit-Debug/
    dir.cdUp();  // Go to build/
    dir.cdUp();  // Go to project root
    
    QString projectRoot = dir.absolutePath();
    qDebug() << "Checking project root:" << projectRoot;
    
    // Check if this is actually the project root by looking for source files
    // (not just nodeJsScripts which might be a cached copy in build/)
    QString activityCppPath = projectRoot + "/activity.cpp";
    QString mainCppPath = projectRoot + "/main.cpp";
    QString nodeScriptsPath = projectRoot + "/nodeJsScripts";
    
    // Verify this is the actual project root by checking for source files
    if ((QFileInfo::exists(activityCppPath) || QFileInfo::exists(mainCppPath)) && 
        QDir(nodeScriptsPath).exists()) {
        qDebug() << "✅ Found actual project root with source files:" << projectRoot;
        return projectRoot;
    }
    
    qDebug() << "⚠️ Directory doesn't contain source files, not the real project root";
    
    // If not found, return empty
    qDebug() << "❌ Could not locate actual project root";
    return QString();
}

bool Activity::copyDirectoryRecursively(const QString &sourceDir, const QString &destDir) const
{
    QDir sourceDirectory(sourceDir);
    if (!sourceDirectory.exists()) {
        return false;
    }
    
    QDir destDirectory(destDir);
    if (!destDirectory.exists()) {
        destDirectory.mkpath(".");
    }
    
    // Copy all files
    QStringList files = sourceDirectory.entryList(QDir::Files);
    for (const QString &fileName : files) {
        QString sourceFilePath = sourceDir + "/" + fileName;
        QString destFilePath = destDir + "/" + fileName;
        
        // Remove existing file if it exists
        if (QFileInfo::exists(destFilePath)) {
            QFile::remove(destFilePath);
        }
        
        if (!QFile::copy(sourceFilePath, destFilePath)) {
            qDebug() << "❌ Failed to copy file:" << sourceFilePath << "to" << destFilePath;
            return false;
        } else {
            qDebug() << "✅ Copied:" << fileName;
        }
    }
    
    // Copy subdirectories recursively
    QStringList subdirs = sourceDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &subdirName : subdirs) {
        QString sourceSubdir = sourceDir + "/" + subdirName;
        QString destSubdir = destDir + "/" + subdirName;
        
        if (!copyDirectoryRecursively(sourceSubdir, destSubdir)) {
            return false;
        }
    }
    
    return true;
}

bool Activity::createActivityJsonFile(const QString &nodeScriptsPath) const
{
    if (!ui) return false;
    
    // Get currently selected activity from table
    QModelIndexList selected = ui->activityTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::information(parentWidget, "Info", "Please select an activity to export, or the first activity will be used.");
        // Use first activity if none selected
        if (ui->activityTable->rowCount() == 0) {
            return false;
        }
        
        // Get data from first row
        int idA = ui->activityTable->item(0, 0)->text().toInt();
        Activity* activity = Activity::rechercherParId(idA);
        if (!activity) return false;
        
        QString jsonFilePath = nodeScriptsPath + "/sample_activity.json";
        return writeActivityToJsonFile(activity, jsonFilePath);
    } else {
        // Get data from selected row
        int row = selected.first().row();
        int idA = ui->activityTable->item(row, 0)->text().toInt();
        Activity* activity = Activity::rechercherParId(idA);
        if (!activity) return false;
        
        QString jsonFilePath = nodeScriptsPath + "/sample_activity.json";
        bool result = writeActivityToJsonFile(activity, jsonFilePath);
        delete activity;
        return result;
    }
}

bool Activity::writeActivityToJsonFile(Activity* activity, const QString &filePath) const
{
    if (!activity) return false;
    
    QJsonObject activityJson;
    activityJson["activityId"] = activity->getIdA();
    activityJson["title"] = activity->getActivityType();
    activityJson["type"] = activity->getActivityType();
    activityJson["date"] = activity->getEventDate().toString("yyyy-MM-dd");
    activityJson["startTime"] = activity->getEventTime().toString("HH:mm");
    activityJson["endTime"] = activity->getEventTime().addSecs(3600).toString("HH:mm"); // Add 1 hour as default
    activityJson["location"] = "Summer Club"; // Default location
    activityJson["instructor"] = activity->getResponsible();
    activityJson["responsible"] = activity->getResponsible();
    activityJson["currentParticipants"] = 0; // Default
    activityJson["maxCapacity"] = activity->getCapacity();
    activityJson["priority"] = "Medium"; // Default priority
    activityJson["status"] = activity->getStatus();
    activityJson["description"] = activity->getDescription();
    // Create a dynamic registration URL based on the activity
    QString dynamicUrl = QString("https://docs.google.com/forms/d/e/1FAIpQLSekepqj1qV4n0eMj9_52NBH8EOJpO4ys6IsIcHjYutrSUFlgg/viewform?usp=sharing&entry.123456=%1&entry.789012=%2")
                          .arg(activity->getIdA())
                          .arg(QString(activity->getActivityType()).replace(" ", "+"));
    activityJson["registrationUrl"] = dynamicUrl;
    
    QJsonDocument doc(activityJson);
    
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        qDebug() << "✅ Activity JSON file created:" << filePath;
        qDebug() << "🔗 Registration URL:" << activityJson["registrationUrl"].toString();
        qDebug() << "📄 Activity data:" << doc.toJson(QJsonDocument::Compact);
        return true;
    } else {
        qDebug() << "❌ Failed to create activity JSON file:" << filePath;
        return false;
    }
}

bool Activity::createPdfWithImage(const QString &imagePath, const QString &pdfPath) const
{
    // 1) Vérifier que le fichier existe
    if (!QFileInfo::exists(imagePath)) {
        qDebug() << "❌ Image file does not exist:" << imagePath;
        return false;
    }

    // 2) Charger l'image
    QImage image(imagePath);
    if (image.isNull()) {
        qDebug() << "❌ Failed to load image:" << imagePath;
        return false;
    }

    // 3) Configurer l'imprimante PDF (Qt 6 API)
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfPath);
    printer.setFullPage(true);

    // Set page layout to A4 Landscape
    QPageLayout pageLayout(QPageSize(QPageSize::A4), QPageLayout::Landscape, QMarginsF(0, 0, 0, 0));
    printer.setPageLayout(pageLayout);

    // 4) Dessiner l'image sur la page
    QPainter painter(&printer);
    if (!painter.isActive()) {
        qDebug() << "❌ Painter is not active";
        return false;
    }

    // Rectangle de la page imprimable (device pixels in Qt 6)
    QRectF pageRectF = printer.pageRect(QPrinter::DevicePixel);
    QRect pageRect = pageRectF.toRect();

    // Taille de l'image redimensionnée en gardant le ratio
    QSize targetSize = image.size();
    targetSize.scale(pageRect.size(), Qt::KeepAspectRatio);

    // Centrer l'image
    QPoint topLeft(
        (pageRect.width()  - targetSize.width())  / 2,
        (pageRect.height() - targetSize.height()) / 2
    );
    QRect targetRect(topLeft, targetSize);

    // Dessin
    painter.drawImage(targetRect, image);
    painter.end();

    // 5) Vérifier que le PDF a bien été créé
    if (QFileInfo::exists(pdfPath)) {
        qDebug() << "✅ PDF created successfully:" << pdfPath;
        return true;
    } else {
        qDebug() << "❌ Failed to create PDF:" << pdfPath;
        return false;
    }
}