#include "member.h"
#include "ui_employeradmin.h"
#include "employeelogspanel.h"
#include <QRegularExpression>
#include <QDateTime>
#include <QTextDocument>
#include <QPrinter>
#include <QPageLayout>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QIODevice>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>

// ============================================================================
// CONSTRUCTORS
// ============================================================================

Member::Member()
    : QObject(nullptr), cin(""), firstName(""), lastName(""), gender(""), 
      age(0), email(""), phone(""), subscriptionPlan(""), 
      joinDate(QDate::currentDate()), photo(QByteArray()),
      ui(nullptr), parentWidget(nullptr), editingCin(""), selectedPhotoPath(""),
      sortAscending(true)
{
}

Member::Member(QString cin, QString firstName, QString lastName, QString gender,
               int age, QString email, QString phone, QString subscriptionPlan,
               QDate joinDate, QByteArray photo)
    : QObject(nullptr), cin(cin), firstName(firstName), lastName(lastName),
      gender(gender), age(age), email(email), phone(phone),
      subscriptionPlan(subscriptionPlan), joinDate(joinDate), photo(photo),
      ui(nullptr), parentWidget(nullptr), editingCin(""), selectedPhotoPath(""),
      sortAscending(true)
{
}

Member::Member(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), cin(""), firstName(""), lastName(""), gender(""),
      age(0), email(""), phone(""), subscriptionPlan(""),
      joinDate(QDate::currentDate()), photo(QByteArray()),
      ui(ui), parentWidget(parent), editingCin(""), selectedPhotoPath(""),
      sortAscending(true)
{
}

Member::~Member()
{
}

// ============================================================================
// GETTERS
// ============================================================================

QString Member::getCin() const { return cin; }
QString Member::getFirstName() const { return firstName; }
QString Member::getLastName() const { return lastName; }
QString Member::getGender() const { return gender; }
int Member::getAge() const { return age; }
QString Member::getEmail() const { return email; }
QString Member::getPhone() const { return phone; }
QString Member::getSubscriptionPlan() const { return subscriptionPlan; }
QDate Member::getJoinDate() const { return joinDate; }
QByteArray Member::getPhoto() const { return photo; }

// ============================================================================
// SETTERS

// ============================================================================


void Member::setCin(const QString &cin) { this->cin = cin; }
void Member::setFirstName(const QString &firstName) { this->firstName = firstName; }
void Member::setLastName(const QString &lastName) { this->lastName = lastName; }
void Member::setGender(const QString &gender) { this->gender = gender; }
void Member::setAge(int age) { this->age = age; }
void Member::setEmail(const QString &email) { this->email = email; }
void Member::setPhone(const QString &phone) { this->phone = phone; }
void Member::setSubscriptionPlan(const QString &subscriptionPlan) { this->subscriptionPlan = subscriptionPlan; }
void Member::setJoinDate(const QDate &joinDate) { this->joinDate = joinDate; }
void Member::setPhoto(const QByteArray &photo) { this->photo = photo; }

// ============================================================================
// VALIDATION METHODS
// ============================================================================

bool Member::validerEmail() const
{
    // Email regex pattern: name@domain.ext
    QRegularExpression emailPattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    return emailPattern.match(email).hasMatch();
}

bool Member::validerCin() const
{
    // CIN should be exactly 8 numeric digits (e.g., 22542687)
    if (cin.isEmpty() || cin.length() != 8) {
        return false;
    }
    
    // Check that all characters are digits (0-9) only
    QRegularExpression numericPattern("^[0-9]{8}$");
    if (!numericPattern.match(cin).hasMatch()) {
        return false;
    }
    
    return true;
}

bool Member::validerAge() const
{
    // Age should be between 5 and 100 for members
    return (age >= 5 && age <= 100);
}

bool Member::validerName(const QString &name) const
{
    // Name must not be empty
    if (name.trimmed().isEmpty()) {
        return false;
    }
    
    // Name should only contain letters, spaces, hyphens, and apostrophes
    // No numbers or special characters allowed
    for (QChar c : name) {
        if (!c.isLetter() && c != ' ' && c != '-' && c != '\'') {
            return false;
        }
    }
    
    return true;
}

bool Member::validerPhone() const
{
    // Phone is required and must be valid
    if (phone.trimmed().isEmpty()) {
        return false;  // Required field
    }
    
    // Phone should be 8 digits for Tunisian numbers
    QString cleanPhone = phone.trimmed();
    if (cleanPhone.length() != 8) {
        return false;
    }
    
    // All characters must be digits
    for (QChar c : cleanPhone) {
        if (!c.isDigit()) {
            return false;
        }
    }
    
    return true;
}

bool Member::validerRequiredFields() const
{
    // Check all required fields are filled
    if (cin.trimmed().isEmpty()) {
        return false;
    }
    if (firstName.trimmed().isEmpty()) {
        return false;
    }
    if (lastName.trimmed().isEmpty()) {
        return false;
    }
    if (gender.trimmed().isEmpty()) {
        return false;
    }
    if (age <= 0) {
        return false;
    }
    if (email.trimmed().isEmpty()) {
        return false;
    }
    if (phone.trimmed().isEmpty()) {
        return false;
    }
    if (subscriptionPlan.trimmed().isEmpty()) {
        return false;
    }
    if (!joinDate.isValid()) {
        return false;
    }
    
    return true;
}

bool Member::valider() const
{
    // 1. Check all required fields are filled
    if (!validerRequiredFields()) {
        qDebug() << "Validation failed: All fields must be filled";
        return false;
    }
    
    // 2. Validate CIN format (8 numeric digits)
    if (!validerCin()) {
        qDebug() << "Validation failed: CIN must be exactly 8 numeric digits";
        return false;
    }
    
    // 3. Validate first name (no numbers/special characters)
    if (!validerName(firstName)) {
        qDebug() << "Validation failed: First name can only contain letters, spaces, hyphens, and apostrophes";
        return false;
    }
    
    // 4. Validate last name (no numbers/special characters)
    if (!validerName(lastName)) {
        qDebug() << "Validation failed: Last name can only contain letters, spaces, hyphens, and apostrophes";
        return false;
    }
    
    // 5. Validate email format
    if (!validerEmail()) {
        qDebug() << "Validation failed: Invalid email format";
        return false;
    }
    
    // 6. Validate age range
    if (!validerAge()) {
        qDebug() << "Validation failed: Age must be between 5 and 100";
        return false;
    }
    
    // 7. Validate phone format (8 digits for Tunisian numbers)
    if (!validerPhone()) {
        qDebug() << "Validation failed: Phone must be exactly 8 numeric digits";
        return false;
    }
    
    return true;
}

bool Member::cinExiste(const QString &cin)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM MEMBERS WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    qDebug() << "Error checking CIN existence:" << query.lastError().text();
    return false;
}

bool Member::emailExiste(const QString &email, const QString &excludeCin)
{
    QSqlQuery query;
    
    if (excludeCin.isEmpty()) {
        query.prepare("SELECT COUNT(*) FROM MEMBERS WHERE EMAIL = :email");
        query.bindValue(":email", email);
    } else {
        query.prepare("SELECT COUNT(*) FROM MEMBERS WHERE EMAIL = :email AND CIN != :cin");
        query.bindValue(":email", email);
        query.bindValue(":cin", excludeCin);
    }
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    qDebug() << "Error checking email existence:" << query.lastError().text();
    return false;
}

// ============================================================================
// CRUD OPERATIONS
// ============================================================================

/**
 * @brief CREATE - Add new member to database
 * @return true if successful, false otherwise
 */
bool Member::ajouter()
{
    // Validate data before insertion
    if (!valider()) {
        qDebug() << "Member::ajouter() - Validation failed";
        return false;
    }
    
    // Check if CIN already exists
    if (cinExiste(cin)) {
        qDebug() << "Member::ajouter() - CIN already exists:" << cin;
        return false;
    }
    
    // Check if email already exists (if provided)
    if (!email.isEmpty() && emailExiste(email)) {
        qDebug() << "Member::ajouter() - Email already exists:" << email;
        return false;
    }
    
    // Prepare INSERT query with prepared statements (SQL Injection Protection)
    QSqlQuery query;
    query.prepare("INSERT INTO MEMBERS "
                  "(CIN, FIRST_NAME, LAST_NAME, GENDER, AGE, EMAIL, PHONE, "
                  "SUBSCRIPTION_PLAN, JOIN_DATE, PHOTO) "
                  "VALUES "
                  "(:cin, :firstName, :lastName, :gender, :age, :email, :phone, "
                  ":subscriptionPlan, :joinDate, :photo)");
    
    // Bind values
    query.bindValue(":cin", cin);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":gender", gender.isEmpty() ? QVariant(QString()) : gender);
    query.bindValue(":age", age > 0 ? QVariant(age) : QVariant(QMetaType(QMetaType::Int)));
    query.bindValue(":email", email.isEmpty() ? QVariant(QString()) : email);
    query.bindValue(":phone", phone.isEmpty() ? QVariant(QString()) : phone);
    query.bindValue(":subscriptionPlan", subscriptionPlan.isEmpty() ? QVariant(QString()) : subscriptionPlan);
    query.bindValue(":joinDate", joinDate.isValid() ? joinDate : QDate::currentDate());
    query.bindValue(":photo", photo.isEmpty() ? QVariant(QByteArray()) : photo);
    
    // Execute query
    if (!query.exec()) {
        qDebug() << "Member::ajouter() - Insert failed:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Member::ajouter() - Successfully added member:" << cin;
    
    // Log the CREATE action
    QJsonObject memberData;
    memberData["cin"] = cin;
    memberData["first_name"] = firstName;
    memberData["last_name"] = lastName;
    memberData["gender"] = gender;
    memberData["age"] = age;
    memberData["email"] = email;
    memberData["phone"] = phone;
    memberData["subscription_plan"] = subscriptionPlan;
    memberData["join_date"] = joinDate.toString("yyyy-MM-dd");
    memberData["has_photo"] = !photo.isEmpty();
    
    QJsonDocument doc(memberData);
    EmployeeLogsPanel::logAction("CREATE", "Member", cin, "", 
                               doc.toJson(QJsonDocument::Compact), 
                               QString("New member created: %1 %2 (%3)")
                               .arg(firstName, lastName, cin));
    
    return true;
}

/**
 * @brief READ - Display all members
 * @return QSqlQueryModel containing all members
 */
QSqlQueryModel* Member::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT PHOTO, CIN, FIRST_NAME, LAST_NAME, GENDER, AGE, "
                    "EMAIL, PHONE, SUBSCRIPTION_PLAN, JOIN_DATE "
                    "FROM MEMBERS "
                    "ORDER BY JOIN_DATE DESC");

    if (model->lastError().isValid()) {
        qDebug() << "Member::afficher() - Query failed:" << model->lastError().text();
        return model;
    }
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, "Photo");
    model->setHeaderData(1, Qt::Horizontal, "CIN");
    model->setHeaderData(2, Qt::Horizontal, "First Name");
    model->setHeaderData(3, Qt::Horizontal, "Last Name");
    model->setHeaderData(4, Qt::Horizontal, "Gender");
    model->setHeaderData(5, Qt::Horizontal, "Age");
    model->setHeaderData(6, Qt::Horizontal, "Email");
    model->setHeaderData(7, Qt::Horizontal, "Phone");
    model->setHeaderData(8, Qt::Horizontal, "Subscription Plan");
    model->setHeaderData(9, Qt::Horizontal, "Join Date");
    
    qDebug() << "Member::afficher() - Loaded" << model->rowCount() << "members";
    return model;
}

/**
 * @brief DELETE - Remove member by CIN
 * @param cin Member CIN to delete
 * @return true if successful, false otherwise
 */
bool Member::supprimer(const QString &cin)
{
    if (cin.isEmpty()) {
        qDebug() << "Member::supprimer() - CIN is empty";
        return false;
    }
    
    // Check if member exists
    if (!cinExiste(cin)) {
        qDebug() << "Member::supprimer() - Member not found:" << cin;
        return false;
    }
    
    // Get member data before deletion for logging
    QJsonObject beforeData;
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM MEMBERS WHERE CIN = :cin");
    selectQuery.bindValue(":cin", cin);
    
    if (selectQuery.exec() && selectQuery.next()) {
        beforeData["cin"] = selectQuery.value("CIN").toString();
        beforeData["first_name"] = selectQuery.value("FIRST_NAME").toString();
        beforeData["last_name"] = selectQuery.value("LAST_NAME").toString();
        beforeData["gender"] = selectQuery.value("GENDER").toString();
        beforeData["age"] = selectQuery.value("AGE").toString();
        beforeData["email"] = selectQuery.value("EMAIL").toString();
        beforeData["phone"] = selectQuery.value("PHONE").toString();
        beforeData["subscription_plan"] = selectQuery.value("SUBSCRIPTION_PLAN").toString();
        beforeData["join_date"] = selectQuery.value("JOIN_DATE").toString();
    }
    
    // Prepare DELETE query with prepared statement
    QSqlQuery query;
    query.prepare("DELETE FROM MEMBERS WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    
    if (!query.exec()) {
        qDebug() << "Member::supprimer() - Delete failed:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Member::supprimer() - Successfully deleted member:" << cin;
    
    // Log the DELETE action
    QJsonDocument doc(beforeData);
    EmployeeLogsPanel::logAction("DELETE", "Member", cin, 
                               doc.toJson(QJsonDocument::Compact), "", 
                               QString("Member deleted: %1 %2 (%3)")
                               .arg(beforeData["first_name"].toString(),
                                    beforeData["last_name"].toString(),
                                    cin));
    
    return true;
}

/**
 * @brief UPDATE - Modify existing member
 * @return true if successful, false otherwise
 */
bool Member::modifier()
{
    // Validate data before update
    if (!valider()) {
        qDebug() << "Member::modifier() - Validation failed";
        return false;
    }
    
    // Check if member exists
    if (!cinExiste(cin)) {
        qDebug() << "Member::modifier() - Member not found:" << cin;
        return false;
    }
    
    // Check if email is being changed and if new email already exists
    if (!email.isEmpty() && emailExiste(email, cin)) {
        qDebug() << "Member::modifier() - Email already exists:" << email;
        return false;
    }
    
    // Prepare UPDATE query with prepared statements
    QSqlQuery query;
    query.prepare("UPDATE MEMBERS SET "
                  "FIRST_NAME = :firstName, "
                  "LAST_NAME = :lastName, "
                  "GENDER = :gender, "
                  "AGE = :age, "
                  "EMAIL = :email, "
                  "PHONE = :phone, "
                  "SUBSCRIPTION_PLAN = :subscriptionPlan, "
                  "JOIN_DATE = :joinDate, "
                  "PHOTO = :photo, "
                  "UPDATED_DATE = SYSDATE "
                  "WHERE CIN = :cin");
    
    // Bind values
    query.bindValue(":cin", cin);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":gender", gender.isEmpty() ? QVariant(QString()) : gender);
    query.bindValue(":age", age > 0 ? QVariant(age) : QVariant(QMetaType(QMetaType::Int)));
    query.bindValue(":email", email.isEmpty() ? QVariant(QString()) : email);
    query.bindValue(":phone", phone.isEmpty() ? QVariant(QString()) : phone);
    query.bindValue(":subscriptionPlan", subscriptionPlan.isEmpty() ? QVariant(QString()) : subscriptionPlan);
    query.bindValue(":joinDate", joinDate.isValid() ? joinDate : QDate::currentDate());
    query.bindValue(":photo", photo.isEmpty() ? QVariant(QByteArray()) : photo);
    
    // Execute query
    if (!query.exec()) {
        qDebug() << "Member::modifier() - Update failed:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Member::modifier() - Successfully updated member:" << cin;
    
    // Log the UPDATE action
    QJsonObject afterData;
    afterData["cin"] = cin;
    afterData["first_name"] = firstName;
    afterData["last_name"] = lastName;
    afterData["gender"] = gender;
    afterData["age"] = age;
    afterData["email"] = email;
    afterData["phone"] = phone;
    afterData["subscription_plan"] = subscriptionPlan;
    afterData["join_date"] = joinDate.toString("yyyy-MM-dd");
    afterData["has_photo"] = !photo.isEmpty();
    
    QJsonDocument doc(afterData);
    EmployeeLogsPanel::logAction("UPDATE", "Member", cin, "", 
                               doc.toJson(QJsonDocument::Compact), 
                               QString("Member modified: %1 %2 (%3)")
                               .arg(firstName, lastName, cin));
    
    return true;
}

// ============================================================================
// ADDITIONAL QUERY METHODS
// ============================================================================

/**
 * @brief Find member by CIN
 * @param cin Member CIN to search
 * @return Member object if found, nullptr otherwise
 */
Member* Member::rechercherParCin(const QString &cin)
{
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, GENDER, AGE, "
                  "EMAIL, PHONE, SUBSCRIPTION_PLAN, JOIN_DATE "
                  "FROM MEMBERS WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    
    if (query.exec() && query.next()) {
        Member* member = new Member();
        member->setCin(query.value(0).toString());
        member->setFirstName(query.value(1).toString());
        member->setLastName(query.value(2).toString());
        member->setGender(query.value(3).toString());
        member->setAge(query.value(4).toInt());
        member->setEmail(query.value(5).toString());
        member->setPhone(query.value(6).toString());
        member->setSubscriptionPlan(query.value(7).toString());
        member->setJoinDate(query.value(8).toDate());
        
        return member;
    }
    
    qDebug() << "Member::rechercherParCin() - Member not found:" << cin;
    return nullptr;
}

/**
 * @brief Search members by name (first or last name)
 * @param nom Name to search (partial match supported)
 * @return QSqlQueryModel with matching members
 */
QSqlQueryModel* Member::rechercherParNom(const QString &nom)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, GENDER, AGE, "
                  "EMAIL, PHONE, SUBSCRIPTION_PLAN, JOIN_DATE "
                  "FROM MEMBERS "
                  "WHERE UPPER(FIRST_NAME) LIKE UPPER(:nom) "
                  "OR UPPER(LAST_NAME) LIKE UPPER(:nom) "
                  "ORDER BY LAST_NAME, FIRST_NAME");
    query.bindValue(":nom", "%" + nom + "%");
    
    if (!query.exec()) {
        qDebug() << "Member::rechercherParNom() - Query failed:" << query.lastError().text();
    }
    
    model->setQuery(std::move(query));
    
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Gender");
    model->setHeaderData(4, Qt::Horizontal, "Age");
    model->setHeaderData(5, Qt::Horizontal, "Email");
    model->setHeaderData(6, Qt::Horizontal, "Phone");
    model->setHeaderData(7, Qt::Horizontal, "Subscription Plan");
    model->setHeaderData(8, Qt::Horizontal, "Join Date");
    
    return model;
}

/**
 * @brief Filter members by subscription plan
 * @param plan Subscription plan name
 * @return QSqlQueryModel with filtered members
 */
QSqlQueryModel* Member::filtrerParPlan(const QString &plan)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, GENDER, AGE, "
                  "EMAIL, PHONE, SUBSCRIPTION_PLAN, JOIN_DATE "
                  "FROM MEMBERS "
                  "WHERE UPPER(SUBSCRIPTION_PLAN) = UPPER(:plan) "
                  "ORDER BY JOIN_DATE DESC");
    query.bindValue(":plan", plan);
    
    if (!query.exec()) {
        qDebug() << "Member::filtrerParPlan() - Query failed:" << query.lastError().text();
    }
    
    model->setQuery(std::move(query));
    
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Gender");
    model->setHeaderData(4, Qt::Horizontal, "Age");
    model->setHeaderData(5, Qt::Horizontal, "Email");
    model->setHeaderData(6, Qt::Horizontal, "Phone");
    model->setHeaderData(7, Qt::Horizontal, "Subscription Plan");
    model->setHeaderData(8, Qt::Horizontal, "Join Date");
    
    return model;
}

/**
 * @brief Filter members by gender
 * @param genre Gender (Male/Female)
 * @return QSqlQueryModel with filtered members
 */
QSqlQueryModel* Member::filtrerParGenre(const QString &genre)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, GENDER, AGE, "
                  "EMAIL, PHONE, SUBSCRIPTION_PLAN, JOIN_DATE "
                  "FROM MEMBERS "
                  "WHERE UPPER(GENDER) = UPPER(:genre) "
                  "ORDER BY JOIN_DATE DESC");
    query.bindValue(":genre", genre);
    
    if (!query.exec()) {
        qDebug() << "Member::filtrerParGenre() - Query failed:" << query.lastError().text();
    }
    
    model->setQuery(std::move(query));
    
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Gender");
    model->setHeaderData(4, Qt::Horizontal, "Age");
    model->setHeaderData(5, Qt::Horizontal, "Email");
    model->setHeaderData(6, Qt::Horizontal, "Phone");
    model->setHeaderData(7, Qt::Horizontal, "Subscription Plan");
    model->setHeaderData(8, Qt::Horizontal, "Join Date");
    
    return model;
}

// ============================================================================
// UI METHODS (VIEW LAYER)
// ============================================================================

// Helper function to populate QTableWidget from QSqlQueryModel
void populateMemberTableWidget(QTableWidget* table, QSqlQueryModel* model, Member* member = nullptr)
{
    if (!table || !model) return;
    
    // CRITICAL: Store counts before any operations to prevent race conditions
    const int dataColCount = model->columnCount();
    const int totalColCount = dataColCount + 1; // +1 for Actions column
    const int rowCount = model->rowCount();
    const int actionsColIndex = dataColCount; // Actions column is the last one
    
    // CRITICAL: Clear all existing widgets to prevent memory leaks and conflicts
    table->clearContents();
    table->setRowCount(0);
    
    // Set column count (add 1 for Actions column)
    table->setColumnCount(totalColCount);
    
    // Set headers for data columns
    for (int col = 0; col < dataColCount; ++col) {
        table->setHorizontalHeaderItem(col, new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString()));
    }
    
    // Set header for Actions column
    table->setHorizontalHeaderItem(actionsColIndex, new QTableWidgetItem("Actions"));
    
    // Set row count
    table->setRowCount(rowCount);
    
    // Populate data
    for (int row = 0; row < rowCount; ++row) {
        // CRITICAL: Get CIN (primary key) from column 1 (since 0 is now Photo)
        QString cin = model->data(model->index(row, 1)).toString();
        // Add photo thumbnail in column 0
        QByteArray photoData = model->data(model->index(row, 0)).toByteArray();
        QLabel* photoLabel = new QLabel(table);
        photoLabel->setAlignment(Qt::AlignCenter);
        QPixmap pixmap;
        if (!photoData.isEmpty() && pixmap.loadFromData(photoData)) {
            photoLabel->setPixmap(pixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            pixmap = QPixmap(":/icons/icons/default_user.png");
            photoLabel->setPixmap(pixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        table->setCellWidget(row, 0, photoLabel);
        // Install hover event filter for larger preview
        photoLabel->installEventFilter(new MemberPhotoHoverFilter(pixmap, photoLabel));

        // Add data columns (shifted by +1)
        for (int col = 1; col < dataColCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Make read-only
            table->setItem(row, col, item);
        }
        
        // Create Actions column with Edit and Delete buttons (only if CIN is valid)
        if (!cin.isEmpty()) {
            QWidget* actionWidget = new QWidget(table); // CRITICAL: Set parent to table for proper ownership
            QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
            actionLayout->setContentsMargins(2, 2, 2, 2);
            actionLayout->setSpacing(4);
            
            // Create Edit button
            QPushButton* editButton = new QPushButton("Edit", actionWidget);
            editButton->setIcon(QIcon(":/icons/icons/edit.png"));
            editButton->setIconSize(QSize(16, 16));
            editButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            editButton->setStyleSheet(
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
            
            // Create Delete button
            QPushButton* deleteButton = new QPushButton("Delete", actionWidget);
            deleteButton->setIcon(QIcon(":/icons/icons/delete.png"));
            deleteButton->setIconSize(QSize(16, 16));
            deleteButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            deleteButton->setStyleSheet(
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
            
            // CRITICAL FIX: Capture CIN (primary key) instead of row index
            // This ensures the correct member is always edited/deleted regardless of sorting/filtering
            if (member) {
                QObject::connect(editButton, &QPushButton::clicked, member, [member, cin]() {
                    member->onEditMemberByCin(cin);
                });
                QObject::connect(deleteButton, &QPushButton::clicked, member, [member, cin]() {
                    member->onDeleteMemberByCin(cin);
                });
            }
            
            actionLayout->addWidget(editButton);
            actionLayout->addWidget(deleteButton);
            
            // CRITICAL: Use stored column index instead of model->columnCount()
            table->setCellWidget(row, actionsColIndex, actionWidget);
        } else {
            // If CIN is empty, create empty widget to maintain table structure
            QWidget* emptyWidget = new QWidget(table);
            table->setCellWidget(row, actionsColIndex, emptyWidget);
        }
    }
    
    // Clean up model (safe now because we stored all needed values)
    delete model;
}

void Member::setupMemberTable()
{
    if (!ui) return;
    
    // Configure table appearance
    ui->memberTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->memberTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->memberTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->memberTable->setAlternatingRowColors(true);
    ui->memberTable->setSortingEnabled(true);
    ui->memberTable->horizontalHeader()->setStretchLastSection(true);
    
    // Make sort indicator arrows bigger and more visible
    ui->memberTable->setStyleSheet(
        ui->memberTable->styleSheet() + 
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
    
    // Populate with data (pass 'this' for button connections)
    populateMemberTableWidget(ui->memberTable, Member::afficher(), this);
}

void Member::refreshMemberTable()
{
    if (!ui) return;
    populateMemberTableWidget(ui->memberTable, Member::afficher(), this);
}

// ============================================================================
// UI HANDLER METHODS
// ============================================================================

void Member::onConfirmAdd()
{
    if (!ui) return;
    
    qDebug() << "Member::onConfirmAdd() called"; // DEBUG
    
    // Check if we're in edit mode (editingCin is set)
    if (!editingCin.isEmpty()) {
        qDebug() << "Edit mode detected, calling onConfirmUpdate() instead"; // DEBUG
        onConfirmUpdate();
        return;
    }
    
    QString cin = ui->memberIdLineEdit->text().trimmed();
    QString firstName = ui->memberFirstNameLineEdit->text().trimmed();
    QString lastName = ui->memberLastNameLineEdit->text().trimmed();
    QString gender = ui->memberGenderComboBox->currentText();
    int age = ui->memberAgeSpinBox->value();
    QString email = ui->memberEmailLineEdit->text().trimmed();
    QString phone = ui->memberPhoneLineEdit->text().trimmed();
    QString subscriptionPlan = ui->memberSubscriptionComboBox->currentText();
    QDate joinDate = ui->memberJoinDateEdit->date();
    
    // Handle photo if selected
    QByteArray photoBlob;
    if (!selectedPhotoPath.isEmpty()) {
        photoBlob = loadPhotoAsBlob(selectedPhotoPath);
    }
    
    qDebug() << "Member data:" << cin << firstName << lastName << gender << age; // DEBUG
    
    Member member(cin, firstName, lastName, gender, age, email, phone, 
                  subscriptionPlan, joinDate, photoBlob);
    
    // Check if CIN already exists first
    if (Member::cinExiste(cin)) {
        QMessageBox::warning(parentWidget, "Duplicate CIN", 
            "A member with this CIN already exists!");
        return;
    }
    
    // Check if email already exists
    if (!email.isEmpty() && Member::emailExiste(email)) {
        QMessageBox::warning(parentWidget, "Duplicate Email", 
            "This email is already registered!");
        return;
    }
    
    if (member.ajouter()) {
        QMessageBox::information(parentWidget, "Success", 
            QString("Member %1 %2 added successfully!").arg(firstName, lastName));
        clearMemberForm();
        refreshMemberTable();
    } else {
        // Show detailed validation error message
        QString errorMsg = "Please fix the following errors:\n\n";
        
        if (cin.trimmed().isEmpty() || firstName.trimmed().isEmpty() || lastName.trimmed().isEmpty() ||
            gender.trimmed().isEmpty() || email.trimmed().isEmpty() || phone.trimmed().isEmpty() ||
            subscriptionPlan.trimmed().isEmpty() || !joinDate.isValid() || age <= 0) {
            errorMsg += "• All fields must be filled\n";
        }
        if (cin.length() != 8 || !cin.contains(QRegularExpression("^[0-9]{8}$"))) {
            errorMsg += "• CIN must be exactly 8 numeric digits\n";
        }
        if (!firstName.contains(QRegularExpression("^[A-Za-z\\s\\-']+$"))) {
            errorMsg += "• First name can only contain letters, spaces, hyphens, and apostrophes\n";
        }
        if (!lastName.contains(QRegularExpression("^[A-Za-z\\s\\-']+$"))) {
            errorMsg += "• Last name can only contain letters, spaces, hyphens, and apostrophes\n";
        }
        if (!email.contains(QRegularExpression("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"))) {
            errorMsg += "• Invalid email format\n";
        }
        if (age < 5 || age > 100) {
            errorMsg += "• Age must be between 5 and 100\n";
        }
        if (phone.length() != 8 || !phone.contains(QRegularExpression("^[0-9]{8}$"))) {
            errorMsg += "• Phone must be exactly 8 numeric digits\n";
        }
        
        QMessageBox::critical(parentWidget, "Validation Error", errorMsg);
    }
}

void Member::onConfirmUpdate()
{
    if (!ui || editingCin.isEmpty()) return;
    
    qDebug() << "Member::onConfirmUpdate() called - Editing CIN:" << editingCin; // DEBUG
    
    // Handle photo if selected  
    QByteArray photoBlob;
    if (!selectedPhotoPath.isEmpty()) {
        photoBlob = loadPhotoAsBlob(selectedPhotoPath);
    }
    
    Member member(editingCin,
                  ui->memberFirstNameLineEdit->text().trimmed(),
                  ui->memberLastNameLineEdit->text().trimmed(),
                  ui->memberGenderComboBox->currentText(),
                  ui->memberAgeSpinBox->value(),
                  ui->memberEmailLineEdit->text().trimmed(),
                  ui->memberPhoneLineEdit->text().trimmed(),
                  ui->memberSubscriptionComboBox->currentText(),
                  ui->memberJoinDateEdit->date(),
                  photoBlob);
    
    qDebug() << "Updating member:" << member.getFirstName() << member.getLastName(); // DEBUG
    
    if (member.modifier()) {
        QMessageBox::information(parentWidget, "Success", "Member updated!");
        clearMemberForm();
        refreshMemberTable();
        editingCin = "";
    } else {
        QMessageBox::critical(parentWidget, "Error", "Failed to update member.");
    }
}

void Member::onConfirmDelete()
{
    if (!ui) return;
    QModelIndexList selected = ui->memberTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(parentWidget, "No Selection", "Select a member to delete.");
        return;
    }
    
    QString cin = ui->memberTable->model()->data(ui->memberTable->model()->index(selected.first().row(), 0)).toString();
    QString name = ui->memberTable->model()->data(ui->memberTable->model()->index(selected.first().row(), 1)).toString() + " " +
                   ui->memberTable->model()->data(ui->memberTable->model()->index(selected.first().row(), 2)).toString();
    
    if (QMessageBox::question(parentWidget, "Confirm", QString("Delete %1?").arg(name)) == QMessageBox::Yes) {
        Member member;
        if (member.supprimer(cin)) {
            QMessageBox::information(parentWidget, "Success", "Member deleted!");
            refreshMemberTable();
        } else {
            QMessageBox::critical(parentWidget, "Error", "Failed to delete.");
        }
    }
}

// CRITICAL FIX: CIN-based edit/delete methods (stable across table changes)
void Member::onEditMemberByCin(const QString &cin)
{
    if (!ui || cin.isEmpty()) return;
    
    // Fetch member data directly from database using CIN
    Member* member = Member::rechercherParCin(cin);
    if (member) {
        loadMemberToForm(member);
        delete member;
        ui->memberTabWidget->setCurrentIndex(1); // Switch to Add/Edit tab
    } else {
        QMessageBox::warning(parentWidget, "Not Found", 
            QString("Member with CIN %1 not found.").arg(cin));
    }
}

void Member::onDeleteMemberByCin(const QString &cin)
{
    if (!ui || cin.isEmpty()) return;
    
    // Fetch member data to display confirmation with name
    Member* member = Member::rechercherParCin(cin);
    if (!member) {
        QMessageBox::warning(parentWidget, "Not Found", 
            QString("Member with CIN %1 not found.").arg(cin));
        return;
    }
    
    QString name = member->getFirstName() + " " + member->getLastName();
    delete member;
    
    // Confirm deletion
    if (QMessageBox::question(parentWidget, "Confirm Delete", 
        QString("Are you sure you want to delete member:\n%1 (CIN: %2)?").arg(name, cin),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        
        Member tempMember;
        if (tempMember.supprimer(cin)) {
            QMessageBox::information(parentWidget, "Success", "Member deleted successfully!");
            refreshMemberTable();
        } else {
            QMessageBox::critical(parentWidget, "Error", "Failed to delete member.");
        }
    }
}

// Legacy row-based methods (kept for backward compatibility with selection-based delete)
void Member::onEditMember(int row)
{
    if (!ui || row < 0 || row >= ui->memberTable->rowCount()) return;
    
    QTableWidgetItem* cinItem = ui->memberTable->item(row, 0);
    if (!cinItem) return;
    
    onEditMemberByCin(cinItem->text());
}

void Member::onDeleteMember(int row)
{
    if (!ui || row < 0 || row >= ui->memberTable->rowCount()) return;
    
    QTableWidgetItem* cinItem = ui->memberTable->item(row, 0);
    if (!cinItem) return;
    
    onDeleteMemberByCin(cinItem->text());
}

void Member::clearMemberForm()
{
    if (!ui) return;
    ui->memberIdLineEdit->clear();
    ui->memberIdLineEdit->setEnabled(true);
    ui->memberFirstNameLineEdit->clear();
    ui->memberLastNameLineEdit->clear();
    ui->memberEmailLineEdit->clear();
    ui->memberPhoneLineEdit->clear();
    ui->memberGenderComboBox->setCurrentIndex(0);
    ui->memberSubscriptionComboBox->setCurrentIndex(0);
    ui->memberAgeSpinBox->setValue(18);
    ui->memberJoinDateEdit->setDate(QDate::currentDate());
    editingCin = "";
    selectedPhotoPath = "";
    
    // Clear photo display
    ui->memberPhotoLabel->clear();
    ui->memberPhotoLabel->setText("Upload Member Photo");
    
    // Reset to add mode UI
    ui->memberConfirmAddButton->setVisible(true);  // Show the Add button
    ui->memberConfirmUpdateButton->setVisible(false);  // Hide the Update button
}

void Member::onSearchMembers()
{
    if (!ui) return;
    QString search = ui->memberSearchLineEdit->text().trimmed();
    if (search.isEmpty()) {
        refreshMemberTable();
    } else {
        populateMemberTableWidget(ui->memberTable, Member::rechercherParNom(search), this);
    }
}

void Member::onFilterByPlan()
{
    if (!ui) return;
    QString plan = ui->memberSubscriptionComboBox->currentText();
    if (plan == "All" || plan.isEmpty()) {
        refreshMemberTable();
    } else {
        populateMemberTableWidget(ui->memberTable, Member::filtrerParPlan(plan), this);
    }
}

void Member::onFilterByGender()
{
    if (!ui) return;
    QString gender = ui->memberGenderComboBox->currentText();
    if (gender == "All" || gender.isEmpty()) {
        refreshMemberTable();
    } else {
        populateMemberTableWidget(ui->memberTable, Member::filtrerParGenre(gender), this);
    }
}

void Member::onSortMembers()
{
    if (!ui) return;
    
    // Sort by Join Date column (index 9 - after Photo column)
    ui->memberTable->sortByColumn(9, sortAscending ? Qt::AscendingOrder : Qt::DescendingOrder);
    
    // Toggle sort order
    sortAscending = !sortAscending;
    
    // Update button icon based on sort order for better UX
    QIcon sortIcon = sortAscending ? QIcon(":/icons/icons/arrow-down.png") : QIcon(":/icons/icons/arrow-up.png");
    ui->memberSortButton->setIcon(sortIcon);
    ui->memberSortButton->setIconSize(QSize(20, 20));
}

void Member::onExportMembers()
{
    if (!ui || !ui->memberTable) return;
    
    // Get selected member from table
    int currentRow = ui->memberTable->currentRow();
    if (currentRow < 0 || currentRow >= ui->memberTable->rowCount()) {
        QMessageBox::warning(parentWidget, "Warning", "Please select a member to export registration certificate.");
        return;
    }
    
    // Safely get member data from selected row with null checks
    auto getItemText = [this](int row, int col) -> QString {
        if (col >= ui->memberTable->columnCount()) return "";
        QTableWidgetItem* item = ui->memberTable->item(row, col);
        return item ? item->text() : "";
    };
    
    // Adjusted column indices to match table structure (Photo is at column 0)
    QString memberCin = getItemText(currentRow, 1);          // CIN is at column 1 (after Photo)
    QString memberFirstName = getItemText(currentRow, 2);    // First Name is at column 2
    QString memberLastName = getItemText(currentRow, 3);     // Last Name is at column 3
    QString ageText = getItemText(currentRow, 4);           // Gender is at column 4, Age at 5
    QString memberEmail = getItemText(currentRow, 6);        // Email is at column 6
    QString memberPhone = getItemText(currentRow, 7);        // Phone is at column 7
    QString subscriptionPlan = getItemText(currentRow, 8);   // Subscription is at column 8
    QString joinDateStr = getItemText(currentRow, 9);       // Join Date is at column 9
    
    // Validate essential data
    if (memberCin.isEmpty() || memberFirstName.isEmpty() || memberLastName.isEmpty()) {
        QMessageBox::warning(parentWidget, "Warning", "Selected member has incomplete data. Cannot generate certificate.");
        return;
    }
    
    // Calculate birth date (approximation based on age if available)
    QString birthDate = "[Date of Birth]";
    QString ageFromGenderCol = getItemText(currentRow, 5);   // Age is at column 5
    if (!ageFromGenderCol.isEmpty()) {
        int age = ageFromGenderCol.toInt();
        if (age > 0 && age < 150) { // Reasonable age range
            int birthYear = QDate::currentDate().year() - age;
            birthDate = QString::number(birthYear);
        }
    }
    
    exportMemberCertificate(memberCin, memberFirstName, memberLastName, birthDate, subscriptionPlan, joinDateStr);
}

void Member::loadMemberToForm(Member* member)
{
    if (!member || !ui) return;
    editingCin = member->getCin();
    ui->memberIdLineEdit->setText(member->getCin());
    ui->memberIdLineEdit->setEnabled(false);
    ui->memberFirstNameLineEdit->setText(member->getFirstName());
    ui->memberLastNameLineEdit->setText(member->getLastName());
    ui->memberGenderComboBox->setCurrentText(member->getGender());
    ui->memberAgeSpinBox->setValue(member->getAge());
    ui->memberEmailLineEdit->setText(member->getEmail());
    ui->memberPhoneLineEdit->setText(member->getPhone());
    ui->memberSubscriptionComboBox->setCurrentText(member->getSubscriptionPlan());
    ui->memberJoinDateEdit->setDate(member->getJoinDate());
    
    // Switch to edit mode UI
    ui->memberConfirmAddButton->setVisible(false);  // Hide the Add button
    ui->memberConfirmUpdateButton->setVisible(true);  // Show the Update button
    ui->memberTabWidget->setCurrentIndex(1);  // Switch to Add/Edit tab
}

bool Member::exportMemberCertificate(const QString& memberCin, const QString& firstName, const QString& lastName, 
                                      const QString& birthDate, const QString& membershipType, const QString& joinDate)
{
    Q_UNUSED(joinDate)  // Parameter reserved for future use
    
    // Validate input parameters
    if (memberCin.isEmpty() || firstName.isEmpty() || lastName.isEmpty()) {
        QMessageBox::warning(parentWidget, "Error", "Essential member information is missing.");
        return false;
    }
    
    // Safely create filename with HTML encoding
    QString safeFirstName = firstName.simplified().remove(QRegularExpression("[^a-zA-Z0-9]"));
    QString safeLastName = lastName.simplified().remove(QRegularExpression("[^a-zA-Z0-9]"));
    QString defaultFileName = QString("Registration_Certificate_%1_%2.pdf").arg(safeFirstName).arg(safeLastName);
    
    QString file = QFileDialog::getSaveFileName(parentWidget, "Export Registration Certificate", defaultFileName, "PDF (*.pdf)");
    if (file.isEmpty()) return false;
    
    try {
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(file);
        printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);
        
        // Get current date and year
        QString currentDate = QDate::currentDate().toString("dd/MM/yyyy");
        QString currentYear = QString::number(QDate::currentDate().year());
        
        // Safely escape HTML content
        auto htmlEscape = [](const QString& text) -> QString {
            return text.toHtmlEscaped();
        };
        
        // Load logo safely
        QString logoPath = QDir::currentPath() + "/assests/VibraClubLogo.png";
        QFile logoFile(logoPath);
        QString logoBase64 = "";
        if (logoFile.exists() && logoFile.open(QIODevice::ReadOnly)) {
            QByteArray logoData = logoFile.readAll();
            if (!logoData.isEmpty()) {
                logoBase64 = QString("data:image/png;base64,%1").arg(QString::fromLatin1(logoData.toBase64().data()));
            }
            logoFile.close();
        }
        
        QTextDocument doc;
        QString html = "<html><body style='font-family: Arial, sans-serif; line-height: 1.6;'>";
        
        // Header with logo and title
        html += "<div style='text-align: center; border-bottom: 3px solid #16a5b3; padding-bottom: 20px; margin-bottom: 30px;'>";
        
        if (!logoBase64.isEmpty()) {
            html += "<img src='" + logoBase64 + "' style='height: 120px; margin-bottom: 15px;' /><br>";
        }
        
        html += "<h1 style='color: #16a5b3; font-size: 32px; margin: 10px 0; text-transform: uppercase; letter-spacing: 2px;'>VIBRACLUB - SMART SUMMER CLUB</h1>";
        html += "<h2 style='color: #666; font-size: 24px; margin: 5px 0; font-weight: normal;'>Registration Certificate No. " + htmlEscape(memberCin) + "</h2>";
        html += "</div>";
        
        // Certificate body
        html += "<div style='margin: 40px 0; padding: 20px; background-color: #f8f9fa; border-left: 5px solid #16a5b3;'>";
        html += "<p style='font-size: 16px; margin-bottom: 20px; text-align: justify;'>";
        html += "I, the undersigned, <strong>The Manager of member department</strong>,certify that:</p>";
        
        html += "<div style='margin: 30px 0; padding: 20px; background-color: white; border: 2px solid #16a5b3; border-radius: 10px;'>";
        html += "<table style='width: 100%; font-size: 16px; line-height: 2;'>";
        html += "<tr><td style='width: 30%; font-weight: bold; color: #16a5b3;'>Member:</td><td>" + htmlEscape(lastName) + " " + htmlEscape(firstName) + "</td></tr>";
        html += "<tr><td style='font-weight: bold; color: #16a5b3;'>Born on:</td><td>" + htmlEscape(birthDate) + "</td></tr>";
        html += "<tr><td style='font-weight: bold; color: #16a5b3;'>National Identity Card:</td><td>" + htmlEscape(memberCin) + "</td></tr>";
        html += "</table>";
        html += "</div>";
        
        html += "<p style='font-size: 16px; margin: 20px 0; text-align: center; font-weight: bold; color: #16a5b3;'>";
        html += "is officially registered with our club for the " + currentYear + " season.</p>";
        
        html += "<div style='margin: 20px 0; padding: 15px; background-color: white; border: 1px solid #ddd; border-radius: 5px;'>";
        html += "<p style='font-size: 16px; text-align: center;'><strong>Membership Type:</strong> <span style='color: #16a5b3; font-size: 18px;'>" + htmlEscape(membershipType.isEmpty() ? "Standard" : membershipType) + "</span></p>";
        html += "</div>";
        html += "</div>";
        
        // Footer with signature and stamp area
        html += "<div style='margin-top: 50px; display: table; width: 100%;'>";
        html += "<div style='display: table-cell; width: 50%; text-align: left;'>";
        html += "<p style='font-size: 16px; margin-bottom: 5px;'>Done on <strong>" + currentDate + "</strong></p>";
        html += "</div>";
        html += "<div style='display: table-cell; width: 50%; text-align: right;'>";
        html += "<div style='border: 2px solid #16a5b3; width: 200px; height: 100px; margin-left: auto; position: relative;'>";
        html += "<p style='text-align: center; margin-top: 35px; color: #666; font-style: italic;'>[Digital Signature]</p>";
        html += "</div>";
        html += "<p style='text-align: center; margin-top: 10px; font-size: 14px; color: #16a5b3; font-weight: bold;'>Official VibraClub Stamp</p>";
        html += "</div>";
        html += "</div>";
        
        // Validity and certificate number footer
        html += "<div style='margin-top: 40px; text-align: center; border-top: 2px solid #16a5b3; padding-top: 20px;'>";
        html += "<p style='font-size: 12px; color: #888; margin: 5px 0;'>This certificate is valid for the current season and serves as official proof of registration.</p>";
        html += "<p style='font-size: 12px; color: #888; margin: 5px 0;'>Certificate Generated: " + currentDate + " | Member ID: " + htmlEscape(memberCin) + "</p>";
        html += "</div>";
        
        html += "</body></html>";
        
        doc.setHtml(html);
        doc.print(&printer);
        
        QMessageBox::information(parentWidget, "Success", "Registration Certificate exported successfully!");
        return true;
        
    } catch (const std::exception& e) {
        QMessageBox::critical(parentWidget, "Error", QString("Failed to export certificate: %1").arg(e.what()));
        return false;
    } catch (...) {
        QMessageBox::critical(parentWidget, "Error", "An unexpected error occurred while exporting the certificate.");
        return false;
    }
}

bool Member::exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title)
{
    if (!table) return false;
    QString file = QFileDialog::getSaveFileName(parentWidget, "Export PDF", defaultName, "PDF (*.pdf)");
    if (file.isEmpty()) return false;
    
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    
    QTextDocument doc;
    QString html = "<h1>" + title + "</h1><table border='1' cellpadding='5'><tr>";
    
    // Add headers (exclude Actions column)
    int colCount = table->columnCount() - 1; // Exclude last column (Actions)
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
    html += "</table>";
    doc.setHtml(html);
    doc.print(&printer);
    
    QMessageBox::information(parentWidget, "Success", "PDF exported!");
    return true;
}

void Member::onUploadPhoto()
{
    if (!ui) return;
    QString file = QFileDialog::getOpenFileName(parentWidget, "Select Photo", "", "Images (*.png *.jpg *.jpeg)");
    if (!file.isEmpty()) {
        selectedPhotoPath = file;
        ui->memberPhotoLabel->setPixmap(QPixmap(file).scaled(150, 150, Qt::KeepAspectRatio));
    }
}

QByteArray Member::loadPhotoAsBlob(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return QByteArray();
    QByteArray data = file.readAll();
    file.close();
    return data;
}