#include "employee.h"
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

// ============================================================================
// CONSTRUCTORS
// ============================================================================

Employee::Employee()
    : QObject(nullptr), cin(""), firstName(""), lastName(""), position(""), 
      department(""), hireDate(QDate::currentDate()), status("Active"), 
      age(0), gender(""), email(""), phone(""), salary(0.0), 
      password(""), photo(QByteArray()), idActivity(0),
      ui(nullptr), parentWidget(nullptr), selectedPhotoPath(""), editingCin("")
{
}

Employee::Employee(QString cin, QString firstName, QString lastName, QString position, 
                   QString department, QDate hireDate, QString status, int age, 
                   QString gender, QString email, QString phone, double salary, 
                   QString password, QByteArray photo, int idActivity)
    : QObject(nullptr), cin(cin), firstName(firstName), lastName(lastName), position(position),
      department(department), hireDate(hireDate), status(status), age(age),
      gender(gender), email(email), phone(phone), salary(salary),
      password(password), photo(photo), idActivity(idActivity),
      ui(nullptr), parentWidget(nullptr), selectedPhotoPath(""), editingCin("")
{
}

Employee::Employee(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), cin(""), firstName(""), lastName(""), position(""), 
      department(""), hireDate(QDate::currentDate()), status("Active"), 
      age(0), gender(""), email(""), phone(""), salary(0.0), 
      password(""), photo(QByteArray()), idActivity(0),
      ui(ui), parentWidget(parent), selectedPhotoPath(""), editingCin("")
{
}

Employee::~Employee()
{
}

// ============================================================================
// GETTERS
// ============================================================================

QString Employee::getCin() const { return cin; }
QString Employee::getFirstName() const { return firstName; }
QString Employee::getLastName() const { return lastName; }
QString Employee::getPosition() const { return position; }
QString Employee::getDepartment() const { return department; }
QDate Employee::getHireDate() const { return hireDate; }
QString Employee::getStatus() const { return status; }
int Employee::getAge() const { return age; }
QString Employee::getGender() const { return gender; }
QString Employee::getEmail() const { return email; }
QString Employee::getPhone() const { return phone; }
double Employee::getSalary() const { return salary; }
QString Employee::getPassword() const { return password; }
QByteArray Employee::getPhoto() const { return photo; }
int Employee::getIdActivity() const { return idActivity; }

// ============================================================================
// SETTERS
// ============================================================================

void Employee::setCin(const QString &cin) { this->cin = cin; }
void Employee::setFirstName(const QString &firstName) { this->firstName = firstName; }
void Employee::setLastName(const QString &lastName) { this->lastName = lastName; }
void Employee::setPosition(const QString &position) { this->position = position; }
void Employee::setDepartment(const QString &department) { this->department = department; }
void Employee::setHireDate(const QDate &hireDate) { this->hireDate = hireDate; }
void Employee::setStatus(const QString &status) { this->status = status; }
void Employee::setAge(int age) { this->age = age; }
void Employee::setGender(const QString &gender) { this->gender = gender; }
void Employee::setEmail(const QString &email) { this->email = email; }
void Employee::setPhone(const QString &phone) { this->phone = phone; }
void Employee::setSalary(double salary) { this->salary = salary; }
void Employee::setPassword(const QString &password) { this->password = password; }
void Employee::setPhoto(const QByteArray &photo) { this->photo = photo; }
void Employee::setIdActivity(int idActivity) { this->idActivity = idActivity; }

// ============================================================================
// VALIDATION METHODS
// ============================================================================

bool Employee::validerEmail() const
{
    // Email regex pattern: name@domain.ext
    QRegularExpression emailPattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    return emailPattern.match(email).hasMatch();
}

bool Employee::validerCin() const
{
    // CIN must be exactly 8 numeric digits (Tunisian CIN format)
    if (cin.length() != 8) {
        return false;
    }
    
    // Check that all characters are digits
    for (QChar c : cin) {
        if (!c.isDigit()) {
            return false;
        }
    }
    
    return true;
}

bool Employee::validerAge() const
{
    // Age should be between 18 and 70
    return (age >= 18 && age <= 70);
}

bool Employee::validerName(const QString &name) const
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

bool Employee::validerPhone() const
{
    // Phone is optional, but if provided must be valid
    if (phone.trimmed().isEmpty()) {
        return true;  // Optional field
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

bool Employee::validerSalary() const
{
    // Salary must be positive
    return (salary > 0);
}

bool Employee::validerRequiredFields() const
{
    // Check all required fields are filled (photo is optional)
    if (cin.trimmed().isEmpty()) {
        return false;
    }
    if (firstName.trimmed().isEmpty()) {
        return false;
    }
    if (lastName.trimmed().isEmpty()) {
        return false;
    }
    if (position.trimmed().isEmpty()) {
        return false;
    }
    if (department.trimmed().isEmpty()) {
        return false;
    }
    if (!hireDate.isValid()) {
        return false;
    }
    if (status.trimmed().isEmpty()) {
        return false;
    }
    if (age <= 0) {
        return false;
    }
    if (gender.trimmed().isEmpty()) {
        return false;
    }
    if (email.trimmed().isEmpty()) {
        return false;
    }
    if (phone.trimmed().isEmpty()) {
        return false;
    }
    if (salary <= 0) {
        return false;
    }
    if (password.trimmed().isEmpty()) {
        return false;
    }
    
    return true;
}

bool Employee::valider() const
{
    // 1. Check all required fields are filled (except photo which is optional)
    if (!validerRequiredFields()) {
        qDebug() << "Validation failed: All fields must be filled (photo is optional)";
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
        qDebug() << "Validation failed: Age must be between 18 and 70";
        return false;
    }
    
    // 7. Validate phone format (8 digits for Tunisian numbers)
    if (!validerPhone()) {
        qDebug() << "Validation failed: Phone must be exactly 8 numeric digits";
        return false;
    }
    
    // 8. Validate salary is positive
    if (!validerSalary()) {
        qDebug() << "Validation failed: Salary must be greater than 0";
        return false;
    }
    
    return true;
}

bool Employee::cinExiste(const QString &cin)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYEES WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    qDebug() << "Error checking CIN existence:" << query.lastError().text();
    return false;
}

bool Employee::emailExiste(const QString &email, const QString &excludeCin)
{
    QSqlQuery query;
    
    if (excludeCin.isEmpty()) {
        query.prepare("SELECT COUNT(*) FROM EMPLOYEES WHERE EMAIL = :email");
        query.bindValue(":email", email);
    } else {
        query.prepare("SELECT COUNT(*) FROM EMPLOYEES WHERE EMAIL = :email AND CIN != :cin");
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
 * @brief CREATE - Add new employee to database
 * @return true if successful, false otherwise
 */
bool Employee::ajouter()
{
    // Validate data before insertion
    if (!valider()) {
        qDebug() << "Employee::ajouter() - Validation failed";
        return false;
    }
    
    // Check if CIN already exists
    if (cinExiste(cin)) {
        qDebug() << "Employee::ajouter() - CIN already exists:" << cin;
        return false;
    }
    
    // Check if email already exists (if provided)
    if (!email.isEmpty() && emailExiste(email)) {
        qDebug() << "Employee::ajouter() - Email already exists:" << email;
        return false;
    }
    
    // Prepare INSERT query with prepared statements (SQL Injection Protection)
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEES "
                  "(CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                  "HIRE_DATE, STATUS, AGE, GENDER, EMAIL, PHONE, SALARY, "
                  "PASSWORD, PHOTO, ID_A) "
                  "VALUES "
                  "(:cin, :firstName, :lastName, :position, :department, "
                  ":hireDate, :status, :age, :gender, :email, :phone, :salary, "
                  ":password, :photo, :idActivity)");
    
    // Bind values
    query.bindValue(":cin", cin);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":position", position.isEmpty() ? QVariant(QString()) : position);
    query.bindValue(":department", department.isEmpty() ? QVariant(QString()) : department);
    query.bindValue(":hireDate", hireDate.isValid() ? hireDate : QDate::currentDate());
    query.bindValue(":status", status.isEmpty() ? "Active" : status);
    query.bindValue(":age", age > 0 ? QVariant(age) : QVariant(QMetaType(QMetaType::Int)));
    query.bindValue(":gender", gender.isEmpty() ? QVariant(QString()) : gender);
    query.bindValue(":email", email.isEmpty() ? QVariant(QString()) : email);
    query.bindValue(":phone", phone.isEmpty() ? QVariant(QString()) : phone);
    query.bindValue(":salary", salary > 0 ? QVariant(salary) : QVariant(QMetaType(QMetaType::Double)));
    query.bindValue(":password", password.isEmpty() ? QVariant(QString()) : password);
    query.bindValue(":photo", photo.isEmpty() ? QVariant(QByteArray()) : photo);
    query.bindValue(":idActivity", idActivity > 0 ? QVariant(idActivity) : QVariant(QMetaType(QMetaType::Int)));
    
    // Execute query
    if (!query.exec()) {
        qDebug() << "Employee::ajouter() - Insert failed:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Employee::ajouter() - Successfully added employee:" << cin;
    return true;
}

/**
 * @brief READ - Display all employees
 * @return QSqlQueryModel containing all employees
 */
QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                    "GENDER, AGE, SALARY, EMAIL, PHONE, HIRE_DATE, STATUS "
                    "FROM EMPLOYEES "
                    "ORDER BY HIRE_DATE DESC");
    
    if (model->lastError().isValid()) {
        qDebug() << "Employee::afficher() - Query failed:" << model->lastError().text();
        return model;
    }
    
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Position");
    model->setHeaderData(4, Qt::Horizontal, "Department");
    model->setHeaderData(5, Qt::Horizontal, "Gender");
    model->setHeaderData(6, Qt::Horizontal, "Age");
    model->setHeaderData(7, Qt::Horizontal, "Salary");
    model->setHeaderData(8, Qt::Horizontal, "Email");
    model->setHeaderData(9, Qt::Horizontal, "Phone");
    model->setHeaderData(10, Qt::Horizontal, "Hire Date");
    model->setHeaderData(11, Qt::Horizontal, "Status");
    
    qDebug() << "Employee::afficher() - Loaded" << model->rowCount() << "employees";
    return model;
}

/**
 * @brief DELETE - Remove employee by CIN
 * @param cin Employee CIN to delete
 * @return true if successful, false otherwise
 */
bool Employee::supprimer(const QString &cin)
{
    if (cin.isEmpty()) {
        qDebug() << "Employee::supprimer() - CIN is empty";
        return false;
    }
    
    // Check if employee exists
    if (!cinExiste(cin)) {
        qDebug() << "Employee::supprimer() - Employee not found:" << cin;
        return false;
    }
    
    // Prepare DELETE query with prepared statement
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEES WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    
    if (!query.exec()) {
        qDebug() << "Employee::supprimer() - Delete failed:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Employee::supprimer() - Successfully deleted employee:" << cin;
    return true;
}

/**
 * @brief UPDATE - Modify existing employee
 * @return true if successful, false otherwise
 */
bool Employee::modifier()
{
    // Validate data before update
    if (!valider()) {
        qDebug() << "Employee::modifier() - Validation failed";
        return false;
    }
    
    // Check if employee exists
    if (!cinExiste(cin)) {
        qDebug() << "Employee::modifier() - Employee not found:" << cin;
        return false;
    }
    
    // Check if email is being changed and if new email already exists
    if (!email.isEmpty() && emailExiste(email, cin)) {
        qDebug() << "Employee::modifier() - Email already exists:" << email;
        return false;
    }
    
    // Prepare UPDATE query with prepared statements
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEES SET "
                  "FIRST_NAME = :firstName, "
                  "LAST_NAME = :lastName, "
                  "POSITION = :position, "
                  "DEPARTMENT = :department, "
                  "HIRE_DATE = :hireDate, "
                  "STATUS = :status, "
                  "AGE = :age, "
                  "GENDER = :gender, "
                  "EMAIL = :email, "
                  "PHONE = :phone, "
                  "SALARY = :salary, "
                  "PASSWORD = :password, "
                  "PHOTO = :photo, "
                  "ID_A = :idActivity, "
                  "UPDATED_DATE = CURRENT_TIMESTAMP "
                  "WHERE CIN = :cin");
    
    // Bind values
    query.bindValue(":cin", cin);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":position", position.isEmpty() ? QVariant(QString()) : position);
    query.bindValue(":department", department.isEmpty() ? QVariant(QString()) : department);
    query.bindValue(":hireDate", hireDate.isValid() ? hireDate : QDate::currentDate());
    query.bindValue(":status", status.isEmpty() ? "Active" : status);
    query.bindValue(":age", age > 0 ? QVariant(age) : QVariant(QMetaType(QMetaType::Int)));
    query.bindValue(":gender", gender.isEmpty() ? QVariant(QString()) : gender);
    query.bindValue(":email", email.isEmpty() ? QVariant(QString()) : email);
    query.bindValue(":phone", phone.isEmpty() ? QVariant(QString()) : phone);
    query.bindValue(":salary", salary > 0 ? QVariant(salary) : QVariant(QMetaType(QMetaType::Double)));
    query.bindValue(":password", password.isEmpty() ? QVariant(QString()) : password);
    query.bindValue(":photo", photo.isEmpty() ? QVariant(QByteArray()) : photo);
    query.bindValue(":idActivity", idActivity > 0 ? QVariant(idActivity) : QVariant(QMetaType(QMetaType::Int)));
    
    // Execute query
    if (!query.exec()) {
        qDebug() << "Employee::modifier() - Update failed:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Employee::modifier() - Successfully updated employee:" << cin;
    return true;
}

// ============================================================================
// ADDITIONAL QUERY METHODS
// ============================================================================

/**
 * @brief Find employee by CIN
 * @param cin Employee CIN to search
 * @return Employee object if found, nullptr otherwise
 */
Employee* Employee::rechercherParCin(const QString &cin)
{
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                  "HIRE_DATE, STATUS, AGE, GENDER, EMAIL, PHONE, SALARY, "
                  "PASSWORD, PHOTO, ID_A "
                  "FROM EMPLOYEES WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    
    if (query.exec() && query.next()) {
        Employee* emp = new Employee();
        emp->setCin(query.value(0).toString());
        emp->setFirstName(query.value(1).toString());
        emp->setLastName(query.value(2).toString());
        emp->setPosition(query.value(3).toString());
        emp->setDepartment(query.value(4).toString());
        emp->setHireDate(query.value(5).toDate());
        emp->setStatus(query.value(6).toString());
        emp->setAge(query.value(7).toInt());
        emp->setGender(query.value(8).toString());
        emp->setEmail(query.value(9).toString());
        emp->setPhone(query.value(10).toString());
        emp->setSalary(query.value(11).toDouble());
        emp->setPassword(query.value(12).toString());
        emp->setPhoto(query.value(13).toByteArray());
        emp->setIdActivity(query.value(14).toInt());
        
        return emp;
    }
    
    qDebug() << "Employee::rechercherParCin() - Employee not found:" << cin;
    return nullptr;
}

/**
 * @brief Search employees by name (first or last name)
 * @param nom Name to search (partial match supported)
 * @return QSqlQueryModel with matching employees
 */
QSqlQueryModel* Employee::rechercherParNom(const QString &nom)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                  "GENDER, AGE, SALARY, EMAIL, PHONE, HIRE_DATE, STATUS "
                  "FROM EMPLOYEES "
                  "WHERE UPPER(FIRST_NAME) LIKE UPPER(:nom) "
                  "OR UPPER(LAST_NAME) LIKE UPPER(:nom) "
                  "ORDER BY LAST_NAME, FIRST_NAME");
    query.bindValue(":nom", "%" + nom + "%");
    
    if (!query.exec()) {
        qDebug() << "Employee::rechercherParNom() - Query failed:" << query.lastError().text();
    }
    
    model->setQuery(std::move(query));
    
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Position");
    model->setHeaderData(4, Qt::Horizontal, "Department");
    model->setHeaderData(5, Qt::Horizontal, "Gender");
    model->setHeaderData(6, Qt::Horizontal, "Age");
    model->setHeaderData(7, Qt::Horizontal, "Salary");
    model->setHeaderData(8, Qt::Horizontal, "Email");
    model->setHeaderData(9, Qt::Horizontal, "Phone");
    model->setHeaderData(10, Qt::Horizontal, "Hire Date");
    model->setHeaderData(11, Qt::Horizontal, "Status");
    
    return model;
}

/**
 * @brief Filter employees by department
 * @param departement Department name
 * @return QSqlQueryModel with filtered employees
 */
QSqlQueryModel* Employee::filtrerParDepartement(const QString &departement)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                  "GENDER, AGE, SALARY, EMAIL, PHONE, HIRE_DATE, STATUS "
                  "FROM EMPLOYEES "
                  "WHERE UPPER(DEPARTMENT) = UPPER(:departement) "
                  "ORDER BY HIRE_DATE DESC");
    query.bindValue(":departement", departement);
    
    if (!query.exec()) {
        qDebug() << "Employee::filtrerParDepartement() - Query failed:" << query.lastError().text();
    }
    
    model->setQuery(std::move(query));
    
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Position");
    model->setHeaderData(4, Qt::Horizontal, "Department");
    model->setHeaderData(5, Qt::Horizontal, "Gender");
    model->setHeaderData(6, Qt::Horizontal, "Age");
    model->setHeaderData(7, Qt::Horizontal, "Salary");
    model->setHeaderData(8, Qt::Horizontal, "Email");
    model->setHeaderData(9, Qt::Horizontal, "Phone");
    model->setHeaderData(10, Qt::Horizontal, "Hire Date");
    model->setHeaderData(11, Qt::Horizontal, "Status");
    
    return model;
}

/**
 * @brief Filter employees by status
 * @param statut Status (Active/Inactive)
 * @return QSqlQueryModel with filtered employees
 */
QSqlQueryModel* Employee::filtrerParStatut(const QString &statut)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                  "GENDER, AGE, SALARY, EMAIL, PHONE, HIRE_DATE, STATUS "
                  "FROM EMPLOYEES "
                  "WHERE UPPER(STATUS) = UPPER(:statut) "
                  "ORDER BY HIRE_DATE DESC");
    query.bindValue(":statut", statut);
    
    if (!query.exec()) {
        qDebug() << "Employee::filtrerParStatut() - Query failed:" << query.lastError().text();
    }
    
    model->setQuery(std::move(query));
    
    // Set header labels
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Position");
    model->setHeaderData(4, Qt::Horizontal, "Department");
    model->setHeaderData(5, Qt::Horizontal, "Gender");
    model->setHeaderData(6, Qt::Horizontal, "Age");
    model->setHeaderData(7, Qt::Horizontal, "Salary");
    model->setHeaderData(8, Qt::Horizontal, "Email");
    model->setHeaderData(9, Qt::Horizontal, "Phone");
    model->setHeaderData(10, Qt::Horizontal, "Hire Date");
    model->setHeaderData(11, Qt::Horizontal, "Status");
    
    return model;
}
// ============================================================================
// UI METHODS (VIEW LAYER)
// ============================================================================

// Helper function to populate QTableWidget from QSqlQueryModel
void populateTableWidget(QTableWidget* table, QSqlQueryModel* model, Employee* emp = nullptr)
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
        // CRITICAL: Get CIN (primary key) from first column for stable reference
        QString cin = model->data(model->index(row, 0)).toString();
        
        // Validate CIN before proceeding (prevent empty action widgets)
        if (cin.isEmpty()) {
            qDebug() << "Warning: Empty CIN at row" << row << "- skipping action buttons";
        }
        
        // Add data columns
        for (int col = 0; col < dataColCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Make read-only
            table->setItem(row, col, item);
        }
        
        // Create Actions column with Edit and Delete buttons (only if CIN is valid)
        if (!cin.isEmpty()) {
            QWidget* actionWidget = new QWidget(table); // CRITICAL: Set parent to table for proper ownership
            QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
            actionLayout->setContentsMargins(4, 2, 4, 2);
            actionLayout->setSpacing(4);
            
            // Create Edit button
            QPushButton* editButton = new QPushButton("Edit", actionWidget);
            editButton->setIcon(QIcon(":/icons/icons/edit.png"));
            editButton->setIconSize(QSize(16, 16));
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
            // This ensures the correct employee is always edited/deleted regardless of sorting/filtering
            if (emp) {
                QObject::connect(editButton, &QPushButton::clicked, emp, [emp, cin]() {
                    emp->onEditEmployeeByCin(cin);
                });
                QObject::connect(deleteButton, &QPushButton::clicked, emp, [emp, cin]() {
                    emp->onDeleteEmployeeByCin(cin);
                });
            }
            
            actionLayout->addWidget(editButton);
            actionLayout->addWidget(deleteButton);
            actionLayout->addStretch();
            
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

void Employee::setupEmployeeTable()
{
    if (!ui) return;
    
    // Configure table appearance
    ui->employeeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->employeeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->employeeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->employeeTable->setAlternatingRowColors(true);
    ui->employeeTable->setSortingEnabled(true);
    ui->employeeTable->horizontalHeader()->setStretchLastSection(true);
    
    // Populate with data (pass 'this' for button connections)
    populateTableWidget(ui->employeeTable, Employee::afficher(), this);
}

void Employee::refreshEmployeeTable()
{
    if (!ui) return;
    populateTableWidget(ui->employeeTable, Employee::afficher(), this);
}

// ============================================================================
// UI METHODS - TO BE ADDED TO employee.cpp
// ============================================================================

void Employee::onConfirmAdd()
{
    if (!ui) return;
    QString cin = ui->empIdLineEdit->text().trimmed();
    QString firstName = ui->firstNameLineEdit->text().trimmed();
    QString lastName = ui->lastNameLineEdit->text().trimmed();
    QString position = ui->positionComboBox->currentText();
    QString department = ui->departmentComboBox->currentText();
    QDate hireDate = ui->hireDateEdit->date();
    QString status = ui->statusComboBox->currentText();
    int age = ui->ageSpinBox->value();
    QString gender = ui->genderComboBox->currentText();
    QString email = ui->emailLineEdit->text().trimmed();
    QString phone = ui->phoneLineEdit->text().trimmed();
    double salary = ui->salaryLineEdit->text().toDouble();
    QString password = ui->passwordLineEedit->text();
    
    QByteArray photoBlob;
    if (!selectedPhotoPath.isEmpty()) {
        photoBlob = loadPhotoAsBlob(selectedPhotoPath);
    }
    
    Employee emp(cin, firstName, lastName, position, department, 
                 hireDate, status, age, gender, email, phone, 
                 salary, password, photoBlob, 0);
    
    // Check if CIN already exists first
    if (Employee::cinExiste(cin)) {
        QMessageBox::warning(parentWidget, "Duplicate CIN", 
            "An employee with this CIN already exists!");
        return;
    }
    
    // Check if email already exists
    if (!email.isEmpty() && Employee::emailExiste(email)) {
        QMessageBox::warning(parentWidget, "Duplicate Email", 
            "This email is already registered!");
        return;
    }
    
    if (emp.ajouter()) {
        QMessageBox::information(parentWidget, "Success", 
            QString("Employee %1 %2 added successfully!").arg(firstName, lastName));
        clearEmployeeForm();
        refreshEmployeeTable();
    } else {
        // Show detailed validation error message
        QString errorMsg = "Please fix the following errors:\n\n";
        
        if (cin.trimmed().isEmpty() || firstName.trimmed().isEmpty() || lastName.trimmed().isEmpty() ||
            position.trimmed().isEmpty() || department.trimmed().isEmpty() || status.trimmed().isEmpty() ||
            gender.trimmed().isEmpty() || email.trimmed().isEmpty() || phone.trimmed().isEmpty() ||
            password.trimmed().isEmpty() || !hireDate.isValid() || age <= 0 || salary <= 0) {
            errorMsg += "• All fields must be filled (photo is optional)\n";
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
        if (age < 18 || age > 70) {
            errorMsg += "• Age must be between 18 and 70\n";
        }
        if (phone.length() != 8 || !phone.contains(QRegularExpression("^[0-9]{8}$"))) {
            errorMsg += "• Phone must be exactly 8 numeric digits\n";
        }
        if (salary <= 0) {
            errorMsg += "• Salary must be greater than 0\n";
        }
        
        QMessageBox::critical(parentWidget, "Validation Error", errorMsg);
    }
}

void Employee::onConfirmUpdate()
{
    if (!ui || editingCin.isEmpty()) return;
    
    Employee emp(editingCin,
                ui->firstNameLineEdit->text().trimmed(),
                ui->lastNameLineEdit->text().trimmed(),
                ui->positionComboBox->currentText(),
                ui->departmentComboBox->currentText(),
                ui->hireDateEdit->date(),
                ui->statusComboBox->currentText(),
                ui->ageSpinBox->value(),
                ui->genderComboBox->currentText(),
                ui->emailLineEdit->text().trimmed(),
                ui->phoneLineEdit->text().trimmed(),
                ui->salaryLineEdit->text().toDouble(),
                ui->passwordLineEedit->text(),
                selectedPhotoPath.isEmpty() ? QByteArray() : loadPhotoAsBlob(selectedPhotoPath),
                0);
    
    if (emp.modifier()) {
        QMessageBox::information(parentWidget, "Success", "Employee updated!");
        clearEmployeeForm();
        refreshEmployeeTable();
        editingCin = "";
    } else {
        QMessageBox::critical(parentWidget, "Error", "Failed to update employee.");
    }
}

void Employee::onConfirmDelete()
{
    if (!ui) return;
    QModelIndexList selected = ui->employeeTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(parentWidget, "No Selection", "Select an employee to delete.");
        return;
    }
    
    QString cin = ui->employeeTable->model()->data(ui->employeeTable->model()->index(selected.first().row(), 0)).toString();
    QString name = ui->employeeTable->model()->data(ui->employeeTable->model()->index(selected.first().row(), 1)).toString() + " " +
                   ui->employeeTable->model()->data(ui->employeeTable->model()->index(selected.first().row(), 2)).toString();
    
    if (QMessageBox::question(parentWidget, "Confirm", QString("Delete %1?").arg(name)) == QMessageBox::Yes) {
        Employee emp;
        if (emp.supprimer(cin)) {
            QMessageBox::information(parentWidget, "Success", "Employee deleted!");
            refreshEmployeeTable();
        } else {
            QMessageBox::critical(parentWidget, "Error", "Failed to delete.");
        }
    }
}

// CRITICAL FIX: CIN-based edit/delete methods (stable across table changes)
void Employee::onEditEmployeeByCin(const QString &cin)
{
    if (!ui || cin.isEmpty()) return;
    
    // Fetch employee data directly from database using CIN
    Employee* emp = Employee::rechercherParCin(cin);
    if (emp) {
        loadEmployeeToForm(emp);
        delete emp;
        ui->employeeTabWidget->setCurrentIndex(1); // Switch to Add/Edit tab
    } else {
        QMessageBox::warning(parentWidget, "Not Found", 
            QString("Employee with CIN %1 not found.").arg(cin));
    }
}

void Employee::onDeleteEmployeeByCin(const QString &cin)
{
    if (!ui || cin.isEmpty()) return;
    
    // Fetch employee data to display confirmation with name
    Employee* emp = Employee::rechercherParCin(cin);
    if (!emp) {
        QMessageBox::warning(parentWidget, "Not Found", 
            QString("Employee with CIN %1 not found.").arg(cin));
        return;
    }
    
    QString name = emp->getFirstName() + " " + emp->getLastName();
    delete emp;
    
    // Confirm deletion
    if (QMessageBox::question(parentWidget, "Confirm Delete", 
        QString("Are you sure you want to delete employee:\n%1 (CIN: %2)?").arg(name, cin),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        
        Employee tempEmp;
        if (tempEmp.supprimer(cin)) {
            QMessageBox::information(parentWidget, "Success", "Employee deleted successfully!");
            refreshEmployeeTable();
        } else {
            QMessageBox::critical(parentWidget, "Error", "Failed to delete employee.");
        }
    }
}

// Legacy row-based methods (kept for backward compatibility with selection-based delete)
void Employee::onEditEmployee(int row)
{
    if (!ui || row < 0 || row >= ui->employeeTable->rowCount()) return;
    
    QTableWidgetItem* cinItem = ui->employeeTable->item(row, 0);
    if (!cinItem) return;
    
    onEditEmployeeByCin(cinItem->text());
}

void Employee::onDeleteEmployee(int row)
{
    if (!ui || row < 0 || row >= ui->employeeTable->rowCount()) return;
    
    QTableWidgetItem* cinItem = ui->employeeTable->item(row, 0);
    if (!cinItem) return;
    
    onDeleteEmployeeByCin(cinItem->text());
}

void Employee::clearEmployeeForm()
{
    if (!ui) return;
    ui->empIdLineEdit->clear();
    ui->empIdLineEdit->setEnabled(true);
    ui->firstNameLineEdit->clear();
    ui->lastNameLineEdit->clear();
    ui->positionComboBox->setCurrentIndex(0);
    ui->emailLineEdit->clear();
    ui->phoneLineEdit->clear();
    ui->salaryLineEdit->clear();
    ui->passwordLineEedit->clear();
    ui->departmentComboBox->setCurrentIndex(0);
    ui->genderComboBox->setCurrentIndex(0);
    ui->statusComboBox->setCurrentIndex(0);
    ui->ageSpinBox->setValue(25);
    ui->hireDateEdit->setDate(QDate::currentDate());
    ui->photoLabel->clear();
    selectedPhotoPath = "";
    editingCin = "";
    
    // Reset to add mode UI
    ui->confirmAddButton->setVisible(true);  // Show the Add button
    ui->confirmUpdateButton->setVisible(false);  // Hide the Update button
}

void Employee::onSearchEmployees()
{
    if (!ui) return;
    QString search = ui->searchLineEdit->text().trimmed();
    if (search.isEmpty()) {
        refreshEmployeeTable();
    } else {
        populateTableWidget(ui->employeeTable, Employee::rechercherParNom(search), this);
    }
}

void Employee::onFilterByDepartment()
{
    if (!ui) return;
    QString dept = ui->departmentComboBox->currentText();
    if (dept == "All" || dept.isEmpty()) {
        refreshEmployeeTable();
    } else {
        populateTableWidget(ui->employeeTable, Employee::filtrerParDepartement(dept), this);
    }
}

void Employee::onFilterByStatus()
{
    if (!ui) return;
    QString stat = ui->statusComboBox->currentText();
    if (stat == "All" || stat.isEmpty()) {
        refreshEmployeeTable();
    } else {
        populateTableWidget(ui->employeeTable, Employee::filtrerParStatut(stat), this);
    }
}

void Employee::onUploadPhoto()
{
    if (!ui) return;
    QString file = QFileDialog::getOpenFileName(parentWidget, "Select Photo", "", "Images (*.png *.jpg *.jpeg)");
    if (!file.isEmpty()) {
        selectedPhotoPath = file;
        ui->photoLabel->setPixmap(QPixmap(file).scaled(150, 150, Qt::KeepAspectRatio));
    }
}

void Employee::onSortEmployees()
{
    if (!ui) return;
    static bool asc = true;
    ui->employeeTable->sortByColumn(10, asc ? Qt::AscendingOrder : Qt::DescendingOrder);
    asc = !asc;
}


void Employee::onExportEmployees()
{
    if (!ui) return;
    exportTableToPdf(ui->employeeTable, "employees.pdf", "Employee List");
}

void Employee::loadEmployeeToForm(Employee* emp)
{
    if (!emp || !ui) return;
    editingCin = emp->getCin();
    ui->empIdLineEdit->setText(emp->getCin());
    ui->empIdLineEdit->setEnabled(false);
    ui->firstNameLineEdit->setText(emp->getFirstName());
    ui->lastNameLineEdit->setText(emp->getLastName());
    ui->positionComboBox->setCurrentText(emp->getPosition());
    ui->departmentComboBox->setCurrentText(emp->getDepartment());
    ui->hireDateEdit->setDate(emp->getHireDate());
    ui->statusComboBox->setCurrentText(emp->getStatus());
    ui->ageSpinBox->setValue(emp->getAge());
    ui->genderComboBox->setCurrentText(emp->getGender());
    ui->emailLineEdit->setText(emp->getEmail());
    ui->phoneLineEdit->setText(emp->getPhone());
    ui->salaryLineEdit->setText(QString::number(emp->getSalary(), 'f', 2));
    ui->passwordLineEedit->setText(emp->getPassword());
    if (!emp->getPhoto().isEmpty()) {
        QPixmap photo;
        photo.loadFromData(emp->getPhoto());
        ui->photoLabel->setPixmap(photo.scaled(150, 150, Qt::KeepAspectRatio));
    }
    
    // Switch to edit mode UI
    ui->confirmAddButton->setVisible(false);  // Hide the Add button
    ui->confirmUpdateButton->setVisible(true);  // Show the Update button
    ui->employeeTabWidget->setCurrentIndex(1);  // Switch to Add/Edit tab
}

QByteArray Employee::loadPhotoAsBlob(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return QByteArray();
    QByteArray data = file.readAll();
    file.close();
    return data;
}

bool Employee::exportTableToPdf(QTableView* table, const QString& name, const QString& title)
{
    if (!table || !table->model()) return false;
    QString file = QFileDialog::getSaveFileName(parentWidget, "Export PDF", name, "PDF (*.pdf)");
    if (file.isEmpty()) return false;
    
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    
    QTextDocument doc;
    QString html = "<h1>" + title + "</h1><table border='1' cellpadding='5'><tr>";
    for (int c = 0; c < table->model()->columnCount(); ++c)
        html += "<th>" + table->model()->headerData(c, Qt::Horizontal).toString() + "</th>";
    html += "</tr>";
    for (int r = 0; r < table->model()->rowCount(); ++r) {
        html += "<tr>";
        for (int c = 0; c < table->model()->columnCount(); ++c)
            html += "<td>" + table->model()->data(table->model()->index(r, c)).toString() + "</td>";
        html += "</tr>";
    }
    html += "</table>";
    doc.setHtml(html);
    doc.print(&printer);
    
    QMessageBox::information(parentWidget, "Success", "PDF exported!");
    return true;
}
