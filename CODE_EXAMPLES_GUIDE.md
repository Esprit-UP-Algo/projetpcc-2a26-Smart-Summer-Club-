# Employee Management System - Code Examples & Practical Guide

## Quick Reference for Professor Questions

This document provides specific code examples and explanations to help you answer detailed questions about your implementation.

---

## 1. Database Connection & Setup

### How the system connects to Oracle database:

```cpp
// In Connection.cpp (assumed)
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("DRIVER={Oracle ODBC Driver};SERVER=localhost:1521;DATABASE=SUMMERCLUB;");
db.setUserName("SUMMERCLUB");
db.setPassword("password");

if (!db.open()) {
    qDebug() << "Database connection failed:" << db.lastError().text();
}
```

**Professor might ask**: "Why QODBC instead of direct Oracle driver?"
**Answer**: QODBC is more portable and works with various databases. It's part of Qt's standard database modules and provides consistent API across different database systems.

---

## 2. Key Code Patterns Explained

### Pattern 1: Prepared Statements (SQL Injection Prevention)

```cpp
// WRONG WAY (vulnerable to injection):
QString sql = QString("INSERT INTO EMPLOYEES (CIN, FIRST_NAME) VALUES ('%1', '%2')")
              .arg(cin).arg(firstName);
QSqlQuery query(sql);

// RIGHT WAY (safe with parameter binding):
QSqlQuery query;
query.prepare("INSERT INTO EMPLOYEES (CIN, FIRST_NAME) VALUES (:cin, :firstName)");
query.bindValue(":cin", cin);
query.bindValue(":firstName", firstName);
query.exec();
```

**Why this matters**: If someone enters `'; DROP TABLE EMPLOYEES; --` as a name, the wrong way would execute it as SQL, destroying your database!

### Pattern 2: Qt's Signal-Slot System

```cpp
// In setupEmployeeTable() - connecting button clicks to functions
QPushButton* editBtn = new QPushButton("Edit");
QObject::connect(editBtn, &QPushButton::clicked, [emp, cin]() {
    emp->onEditEmployeeByCin(cin);  // Lambda captures CIN value
});
```

**Professor might ask**: "Explain lambda captures"
**Answer**: `[emp, cin]` captures the employee object pointer and CIN string by value. When the button is clicked later, these captured values are still available even if the original variables are out of scope.

### Pattern 3: RAII (Resource Acquisition Is Initialization)

```cpp
QByteArray Employee::loadPhotoAsBlob(const QString& path)
{
    QFile file(path);  // Constructor opens file
    if (!file.open(QIODevice::ReadOnly)) return QByteArray();
    
    QByteArray data = file.readAll();
    // No need to call file.close() - destructor handles it automatically
    return data;
}
```

**Why RAII**: Guarantees resource cleanup even if exceptions occur or early returns happen.

---

## 3. Validation System Deep Dive

### Comprehensive Email Validation

```cpp
bool Employee::validerEmail() const
{
    // Pattern: ^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$
    QRegularExpression emailPattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    return emailPattern.match(email).hasMatch();
}
```

**Pattern breakdown for professor**:
- `^` : Start of string
- `[A-Za-z0-9._%+-]+` : Username (letters, numbers, dots, underscores, percent, plus, minus)
- `@` : Required @ symbol  
- `[A-Za-z0-9.-]+` : Domain name (letters, numbers, dots, hyphens)
- `\\.` : Required dot (escaped because . is regex special character)
- `[A-Za-z]{2,}` : Top-level domain (minimum 2 letters)
- `$` : End of string

### CIN Validation (Business Logic)

```cpp
bool Employee::validerCin() const
{
    if (cin.length() != 8) return false;  // Tunisian CIN is exactly 8 digits
    
    for (QChar c : cin) {
        if (!c.isDigit()) return false;   // Must be numeric only
    }
    return true;
}
```

**Professor might ask**: "Why 8 digits specifically?"
**Answer**: This is based on Tunisian national ID format. Different countries have different formats - this shows understanding of business requirements and internationalization needs.

---

## 4. Memory Management Examples

### Qt Parent-Child System

```cpp
Employee::Employee(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent)  // Setting parent here is crucial!
{
    // When 'parent' is destroyed, this Employee object is automatically deleted
    // This prevents memory leaks in GUI applications
}
```

### Manual Memory Management for Database Models

```cpp
void populateTableWidget(QTableWidget* table, QSqlQueryModel* model, Employee* emp)
{
    // Use the model to populate table...
    for (int row = 0; row < model->rowCount(); ++row) {
        // ... extract data from model
    }
    
    delete model;  // CRITICAL: Manual cleanup to prevent memory leak
    // Model is temporary - created in afficher(), used here, then destroyed
}
```

**Professor might ask**: "Why not use smart pointers?"
**Answer**: Qt's parent-child system provides automatic memory management for UI objects. For temporary objects like database models, explicit deletion gives clear ownership semantics and immediate resource cleanup.

---

## 5. Database Schema Relationships

### Foreign Key Relationship

```sql
-- In your export.sql
ALTER TABLE "SUMMERCLUB"."EMPLOYEES" ADD CONSTRAINT "FK_EMPLOYEE_ACTIVITY" 
FOREIGN KEY ("ID_A") REFERENCES "SUMMERCLUB"."ACTIVITIES" ("ID_A") ON DELETE SET NULL;
```

**In your C++ code**:
```cpp
class Employee {
private:
    int idActivity;  // Foreign key to ACTIVITIES table
    
public:
    void setIdActivity(int idActivity) { this->idActivity = idActivity; }
    int getIdActivity() const { return idActivity; }
};
```

**Professor might ask**: "What does ON DELETE SET NULL mean?"
**Answer**: If an activity is deleted, the employee's ID_A field becomes NULL instead of causing a foreign key constraint violation. This preserves the employee record while removing the broken reference.

---

## 6. UI Design Patterns

### Action Button Creation Pattern

```cpp
void createActionButtons(QTableWidget* table, int row, int actionsCol, Employee* emp)
{
    // Create container widget for multiple buttons
    QWidget* buttonWidget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
    
    // Create styled buttons
    QPushButton* editBtn = new QPushButton("Edit");
    editBtn->setStyleSheet("QPushButton { "
        "background-color: #4CAF50; "
        "color: white; "
        "border: none; "
        "padding: 5px 10px; "
        "border-radius: 3px; "
    "}");
    
    // Get stable identifier (CIN) instead of using row number
    QString cin = table->item(row, 0)->text();
    
    // Connect with lambda that captures CIN
    QObject::connect(editBtn, &QPushButton::clicked, [emp, cin]() {
        emp->onEditEmployeeByCin(cin);
    });
    
    layout->addWidget(editBtn);
    // Set the widget in table cell
    table->setCellWidget(row, actionsCol, buttonWidget);
}
```

**Professor might ask**: "Why capture CIN instead of row number?"
**Answer**: Row numbers change when the table is sorted or filtered, but CIN is a stable primary key. This prevents editing/deleting the wrong employee after table operations.

---

## 7. Error Handling Strategies

### Multi-Level Error Handling

```cpp
bool Employee::ajouter()
{
    // Level 1: Input validation
    if (!valider()) {
        qDebug() << "Validation failed for employee:" << cin;
        return false;
    }
    
    // Level 2: Business rule validation
    if (cinExiste(cin)) {
        qDebug() << "CIN already exists:" << cin;
        return false;
    }
    
    // Level 3: Database operation
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEES ...");
    // ... bind values
    
    if (!query.exec()) {
        qDebug() << "Database error:" << query.lastError().text();
        return false;  // Database-level error
    }
    
    return true;  // Success
}
```

### UI Error Feedback

```cpp
void Employee::onConfirmAdd()
{
    Employee emp(/* ... form data ... */);
    
    if (Employee::cinExiste(cin)) {
        QMessageBox::warning(parentWidget, "Validation Error", 
            QString("Employee with CIN %1 already exists!\n"
                   "Please check the CIN and try again.").arg(cin));
        ui->empIdLineEdit->setFocus();  // Focus on problematic field
        return;
    }
    
    if (emp.ajouter()) {
        QMessageBox::information(parentWidget, "Success", 
            QString("Employee %1 %2 has been successfully added!")
            .arg(emp.getFirstName(), emp.getLastName()));
        clearEmployeeForm();
        refreshEmployeeTable();
    } else {
        QMessageBox::critical(parentWidget, "Database Error", 
            "Failed to add employee to database.\n"
            "Please check your data and try again.");
    }
}
```

---

## 8. Performance Optimizations

### Database Query Optimization

```cpp
QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    // Optimized query: select only needed columns, use index-friendly ORDER BY
    model->setQuery("SELECT CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                    "GENDER, AGE, SALARY, EMAIL, PHONE, HIRE_DATE, STATUS "
                    "FROM EMPLOYEES "
                    "ORDER BY HIRE_DATE DESC");  // Index on HIRE_DATE for fast sorting
    
    return model;
}
```

**Professor might ask**: "How could you optimize for large datasets?"
**Answer**: 
1. Add LIMIT clause for pagination
2. Use prepared statements for repeated queries
3. Create database indexes on frequently searched columns
4. Implement lazy loading for BLOB data (photos)

### UI Performance

```cpp
void populateTableWidget(QTableWidget* table, QSqlQueryModel* model, Employee* emp)
{
    // Store counts BEFORE operations to prevent race conditions
    const int dataColCount = model->columnCount();
    const int rowCount = model->rowCount();
    
    // Disable sorting during population for better performance
    table->setSortingEnabled(false);
    
    // Batch operations
    table->clearContents();
    table->setRowCount(rowCount);
    table->setColumnCount(dataColCount + 1);
    
    // Populate all data
    for (int row = 0; row < rowCount; ++row) {
        // ... populate row
    }
    
    // Re-enable sorting after population
    table->setSortingEnabled(true);
}
```

---

## 9. Security Considerations

### Input Sanitization

```cpp
QString Employee::sanitizeInput(const QString& input) const
{
    QString clean = input.trimmed();  // Remove whitespace
    
    // Remove potentially dangerous characters for names
    clean.remove(QRegularExpression("[<>\"'%;()&+]"));
    
    return clean;
}

bool Employee::validerName(const QString &name) const
{
    QString clean = sanitizeInput(name);
    
    if (clean.isEmpty()) return false;
    
    // Only allow letters, spaces, hyphens, apostrophes
    for (QChar c : clean) {
        if (!c.isLetter() && c != ' ' && c != '-' && c != '\'') {
            return false;
        }
    }
    return true;
}
```

### Password Handling (if implemented)

```cpp
// NOTE: In real applications, NEVER store plain text passwords!
// This is a simplified example - use proper hashing in production

QString Employee::hashPassword(const QString& plainPassword) const
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(plainPassword.toUtf8());
    hash.addData("your_salt_here");  // Add salt for security
    return hash.result().toHex();
}
```

---

## 10. Testing Scenarios

### Unit Test Examples

```cpp
#include <QtTest/QtTest>

class EmployeeTest : public QObject
{
    Q_OBJECT

private slots:
    void testCinValidation();
    void testEmailValidation();
    void testEmployeeCreation();
    void testEmployeeUpdate();
};

void EmployeeTest::testCinValidation()
{
    Employee emp;
    
    // Test valid CIN
    emp.setCin("12345678");
    QVERIFY(emp.validerCin() == true);
    
    // Test invalid CIN (too short)
    emp.setCin("1234567");
    QVERIFY(emp.validerCin() == false);
    
    // Test invalid CIN (contains letters)
    emp.setCin("1234567A");
    QVERIFY(emp.validerCin() == false);
    
    // Test invalid CIN (too long)
    emp.setCin("123456789");
    QVERIFY(emp.validerCin() == false);
}

void EmployeeTest::testEmailValidation()
{
    Employee emp;
    
    // Valid emails
    emp.setEmail("user@example.com");
    QVERIFY(emp.validerEmail() == true);
    
    emp.setEmail("user.name+tag@example.co.uk");
    QVERIFY(emp.validerEmail() == true);
    
    // Invalid emails
    emp.setEmail("invalid-email");
    QVERIFY(emp.validerEmail() == false);
    
    emp.setEmail("@example.com");
    QVERIFY(emp.validerEmail() == false);
    
    emp.setEmail("user@");
    QVERIFY(emp.validerEmail() == false);
}
```

---

## 11. Common Debugging Scenarios

### Database Connection Issues

```cpp
void debugDatabaseConnection()
{
    QSqlDatabase db = QSqlDatabase::database();
    
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        qDebug() << "Available drivers:" << QSqlDatabase::drivers();
        qDebug() << "Database error:" << db.lastError().text();
    }
    
    // Test with simple query
    QSqlQuery testQuery("SELECT COUNT(*) FROM EMPLOYEES");
    if (!testQuery.exec()) {
        qDebug() << "Test query failed:" << testQuery.lastError().text();
    } else {
        qDebug() << "Database connection is working";
    }
}
```

### UI Update Issues

```cpp
void Employee::debugTablePopulation()
{
    qDebug() << "Table widget pointer:" << ui->employeeTable;
    qDebug() << "Current row count:" << ui->employeeTable->rowCount();
    qDebug() << "Current column count:" << ui->employeeTable->columnCount();
    
    QSqlQueryModel* model = Employee::afficher();
    qDebug() << "Model row count:" << model->rowCount();
    qDebug() << "Model column count:" << model->columnCount();
    
    if (model->lastError().isValid()) {
        qDebug() << "Model error:" << model->lastError().text();
    }
    
    delete model;
}
```

---

## 12. Extension Possibilities

### How to add new features (for professor discussion):

#### 1. Photo Upload with Preview
```cpp
void Employee::onUploadPhoto()
{
    QString fileName = QFileDialog::getOpenFileName(
        parentWidget, 
        "Select Employee Photo", 
        "", 
        "Images (*.png *.jpg *.jpeg *.gif *.bmp)"
    );
    
    if (!fileName.isEmpty()) {
        // Load and display preview
        QPixmap pixmap(fileName);
        QPixmap scaled = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->photoLabel->setPixmap(scaled);
        
        selectedPhotoPath = fileName;
    }
}
```

#### 2. Advanced Search with Multiple Criteria
```cpp
QSqlQueryModel* Employee::advancedSearch(const QString& name, 
                                        const QString& department,
                                        int minAge, int maxAge,
                                        double minSalary, double maxSalary)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    QString sql = "SELECT * FROM EMPLOYEES WHERE 1=1";
    QSqlQuery query;
    
    if (!name.isEmpty()) {
        sql += " AND (UPPER(FIRST_NAME) LIKE :name OR UPPER(LAST_NAME) LIKE :name)";
    }
    if (!department.isEmpty()) {
        sql += " AND UPPER(DEPARTMENT) = UPPER(:dept)";
    }
    if (minAge > 0) {
        sql += " AND AGE >= :minAge";
    }
    if (maxAge > 0) {
        sql += " AND AGE <= :maxAge";
    }
    // ... more conditions
    
    query.prepare(sql);
    if (!name.isEmpty()) query.bindValue(":name", "%" + name.toUpper() + "%");
    if (!department.isEmpty()) query.bindValue(":dept", department);
    // ... bind other values
    
    model->setQuery(query);
    return model;
}
```

#### 3. Data Export to Excel
```cpp
bool Employee::exportToExcel(const QString& fileName)
{
    QAxObject* excel = new QAxObject("Excel.Application");
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Add");
    QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1);
    
    QSqlQueryModel* model = Employee::afficher();
    
    // Write headers
    for (int col = 0; col < model->columnCount(); ++col) {
        QAxObject* cell = worksheet->querySubObject("Cells(int,int)", 1, col + 1);
        cell->setProperty("Value", model->headerData(col, Qt::Horizontal).toString());
    }
    
    // Write data
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QAxObject* cell = worksheet->querySubObject("Cells(int,int)", row + 2, col + 1);
            cell->setProperty("Value", model->data(model->index(row, col)).toString());
        }
    }
    
    workbook->dynamicCall("SaveAs(const QString&)", fileName);
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    
    delete model;
    delete excel;
    
    return true;
}
```

---

## Key Points for Professor Discussion

1. **Separation of Concerns**: Database logic in Employee class, UI logic in separate methods
2. **Security**: Prepared statements prevent SQL injection, input validation prevents bad data
3. **Performance**: Efficient queries, memory management, UI optimizations
4. **Maintainability**: Clear function separation, consistent naming, comprehensive error handling
5. **Extensibility**: Easy to add new fields, search criteria, export formats
6. **User Experience**: Clear error messages, confirmation dialogs, intuitive interface

Remember: Your professor wants to see that you understand WHY you made these design choices, not just that you can write code that works!