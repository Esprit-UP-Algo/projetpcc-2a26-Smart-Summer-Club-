# QSqlQuery Complete Guide - Methods & Functions Explained

## Table of Contents
1. [QSqlQuery Overview](#qsqlquery-overview)
2. [Query Preparation Methods](#query-preparation-methods)
3. [Parameter Binding Methods](#parameter-binding-methods)
4. [Query Execution Methods](#query-execution-methods)
5. [Data Retrieval Methods](#data-retrieval-methods)
6. [Error Handling Methods](#error-handling-methods)
7. [Navigation Methods](#navigation-methods)
8. [Complete Function Analysis](#complete-function-analysis)
9. [Best Practices & Common Patterns](#best-practices--common-patterns)

---

## QSqlQuery Overview

### What is QSqlQuery?
**QSqlQuery** is Qt's class for executing SQL statements and retrieving results from databases. It provides a safe, efficient way to interact with SQL databases while preventing common security issues like SQL injection.

### Basic QSqlQuery Lifecycle
```cpp
QSqlQuery query;                    // 1. Create query object
query.prepare("SELECT * FROM ...");  // 2. Prepare SQL statement
query.bindValue(":param", value);   // 3. Bind parameters safely
query.exec();                       // 4. Execute the query
while (query.next()) {              // 5. Navigate through results
    QString data = query.value(0).toString();  // 6. Retrieve data
}
```

---

## Query Preparation Methods

### 1. `prepare()` Method
**Purpose**: Prepares an SQL statement for execution with parameter placeholders

```cpp
// From your ajouter() function
QSqlQuery query;
query.prepare("INSERT INTO EMPLOYEES "
              "(CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
              "HIRE_DATE, STATUS, AGE, GENDER, EMAIL, PHONE, SALARY, "
              "PASSWORD, PHOTO, ID_A) "
              "VALUES "
              "(:cin, :firstName, :lastName, :position, :department, "
              ":hireDate, :status, :age, :gender, :email, :phone, :salary, "
              ":password, :photo, :idActivity)");
```

**Parameter Placeholders**:
- **Named placeholders**: `:paramName` (recommended)
- **Positional placeholders**: `?` (less readable)

**Why use prepare()?**
1. **Security**: Prevents SQL injection attacks
2. **Performance**: Query is compiled once, can be executed multiple times
3. **Type Safety**: Automatic parameter type conversion
4. **Readability**: Clear separation of SQL structure and data

### 2. Direct Query Construction (Alternative)
```cpp
// Less secure approach - NOT recommended
QSqlQuery query("SELECT * FROM EMPLOYEES");
```

---

## Parameter Binding Methods

### 1. `bindValue()` Method
**Purpose**: Safely binds a value to a named or positional parameter

#### Basic Syntax:
```cpp
query.bindValue(":parameterName", value);
query.bindValue(0, value);  // Positional binding (0-based index)
```

#### Examples from Your Code:

##### Simple Value Binding
```cpp
// From ajouter() function
query.bindValue(":cin", cin);           // QString binding
query.bindValue(":firstName", firstName); // QString binding
query.bindValue(":age", age);           // int binding
query.bindValue(":salary", salary);     // double binding
```

##### Conditional/Null Value Binding
```cpp
// Handle optional fields with QVariant
query.bindValue(":position", position.isEmpty() ? QVariant(QString()) : position);
query.bindValue(":department", department.isEmpty() ? QVariant(QString()) : department);
query.bindValue(":age", age > 0 ? QVariant(age) : QVariant(QMetaType(QMetaType::Int)));
```

**Why conditional binding?**
- **NULL handling**: Empty strings become NULL in database
- **Data integrity**: Prevents invalid default values
- **Flexibility**: Handles optional vs required fields differently

##### BLOB Data Binding
```cpp
// For binary data (photos)
query.bindValue(":photo", photo.isEmpty() ? QVariant(QByteArray()) : photo);
```

##### Date/Time Binding
```cpp
// QDate binding with fallback
query.bindValue(":hireDate", hireDate.isValid() ? hireDate : QDate::currentDate());
```

### 2. `addBindValue()` Method
**Purpose**: Binds values to positional placeholders in order

```cpp
// Alternative approach (not used in your code)
query.prepare("INSERT INTO EMPLOYEES (CIN, FIRST_NAME) VALUES (?, ?)");
query.addBindValue(cin);
query.addBindValue(firstName);
```

### 3. `bindValue()` vs `addBindValue()`
| Method | Placeholder Type | Advantages | Usage |
|--------|------------------|------------|-------|
| `bindValue()` | Named (`:name`) | More readable, order-independent | Recommended for complex queries |
| `addBindValue()` | Positional (`?`) | Slightly faster, less typing | Good for simple queries |

---

## Query Execution Methods

### 1. `exec()` Method
**Purpose**: Executes the prepared query

```cpp
// From your ajouter() function
if (!query.exec()) {
    qDebug() << "Employee::ajouter() - Database error:" << query.lastError().text();
    return false;
}
```

**Return Value**: 
- `true`: Query executed successfully
- `false`: Query failed (check `lastError()` for details)

### 2. `exec(QString sql)` Method - Direct Execution
```cpp
// Execute SQL directly (less secure)
QSqlQuery query;
query.exec("SELECT COUNT(*) FROM EMPLOYEES");
```

**When to use direct exec()**:
- Simple queries without parameters
- Administrative queries
- One-time operations

---

## Data Retrieval Methods

### 1. `value()` Method - Core Data Access
**Purpose**: Retrieves data from the current row by column index or name

#### By Column Index (0-based)
```cpp
// From your rechercherParCin() function
Employee* emp = new Employee(
    query.value(0).toString(),    // CIN (column 0)
    query.value(1).toString(),    // FIRST_NAME (column 1)
    query.value(2).toString(),    // LAST_NAME (column 2)
    query.value(3).toString(),    // POSITION (column 3)
    query.value(4).toString(),    // DEPARTMENT (column 4)
    query.value(5).toDate(),      // HIRE_DATE (column 5)
    query.value(6).toString(),    // STATUS (column 6)
    query.value(7).toInt(),       // AGE (column 7)
    query.value(8).toString(),    // GENDER (column 8)
    query.value(9).toString(),    // EMAIL (column 9)
    query.value(10).toString(),   // PHONE (column 10)
    query.value(11).toDouble(),   // SALARY (column 11)
    query.value(12).toString(),   // PASSWORD (column 12)
    query.value(13).toByteArray(),// PHOTO (column 13)
    query.value(14).toInt()       // ID_A (column 14)
);
```

#### By Column Name (More Readable)
```cpp
// Alternative approach - more maintainable
Employee* emp = new Employee(
    query.value("CIN").toString(),
    query.value("FIRST_NAME").toString(),
    query.value("LAST_NAME").toString(),
    query.value("POSITION").toString(),
    query.value("DEPARTMENT").toString(),
    query.value("HIRE_DATE").toDate(),
    query.value("STATUS").toString(),
    query.value("AGE").toInt(),
    query.value("GENDER").toString(),
    query.value("EMAIL").toString(),
    query.value("PHONE").toString(),
    query.value("SALARY").toDouble(),
    query.value("PASSWORD").toString(),
    query.value("PHOTO").toByteArray(),
    query.value("ID_A").toInt()
);
```

### 2. QVariant Type Conversion Methods
**QVariant** is Qt's generic data container that can hold any type

#### String Conversion
```cpp
QString cin = query.value(0).toString();
QString name = query.value("FIRST_NAME").toString();
```

#### Numeric Conversions
```cpp
int age = query.value("AGE").toInt();
double salary = query.value("SALARY").toDouble();
bool isValid = query.value("AGE").toInt() > 0;
```

#### Date/Time Conversions
```cpp
QDate hireDate = query.value("HIRE_DATE").toDate();
QDateTime timestamp = query.value("CREATED_DATE").toDateTime();
```

#### Binary Data Conversion
```cpp
QByteArray photoData = query.value("PHOTO").toByteArray();
```

#### Null Value Handling
```cpp
QVariant value = query.value("OPTIONAL_FIELD");
if (value.isNull()) {
    qDebug() << "Field is NULL in database";
} else {
    QString data = value.toString();
}
```

### 3. `isNull()` Method
**Purpose**: Check if a field contains NULL value

```cpp
if (query.value("PHOTO").isNull()) {
    qDebug() << "Employee has no photo";
} else {
    QByteArray photo = query.value("PHOTO").toByteArray();
}
```

---

## Error Handling Methods

### 1. `lastError()` Method
**Purpose**: Returns detailed information about the last error

```cpp
// From your ajouter() function
if (!query.exec()) {
    qDebug() << "Employee::ajouter() - Database error:" << query.lastError().text();
    qDebug() << "Query:" << query.lastQuery();
    return false;
}
```

#### QSqlError Properties:
```cpp
QSqlError error = query.lastError();
qDebug() << "Error text:" << error.text();           // Human-readable error
qDebug() << "Error type:" << error.type();           // Error category
qDebug() << "Database text:" << error.databaseText(); // Database-specific error
qDebug() << "Driver text:" << error.driverText();    // Driver-specific error
```

### 2. `lastQuery()` Method
**Purpose**: Returns the last executed SQL statement

```cpp
if (!query.exec()) {
    qDebug() << "Failed query:" << query.lastQuery();
    qDebug() << "Bound values:" << query.boundValues();
}
```

### 3. `boundValues()` Method
**Purpose**: Returns map of all bound parameter values

```cpp
QMap<QString, QVariant> values = query.boundValues();
for (auto it = values.begin(); it != values.end(); ++it) {
    qDebug() << "Parameter:" << it.key() << "Value:" << it.value().toString();
}
```

---

## Navigation Methods

### 1. `next()` Method
**Purpose**: Moves to the next record in the result set

```cpp
// From your rechercherParCin() function
if (query.exec() && query.next()) {
    // Process first (and only) record
    Employee* emp = new Employee(
        query.value("CIN").toString(),
        // ... other fields
    );
    return emp;
}
```

#### Loop Through All Results:
```cpp
// Example: Print all employee names
QSqlQuery query("SELECT FIRST_NAME, LAST_NAME FROM EMPLOYEES");
while (query.next()) {
    QString firstName = query.value(0).toString();
    QString lastName = query.value(1).toString();
    qDebug() << firstName << lastName;
}
```

### 2. Other Navigation Methods
```cpp
query.first();      // Move to first record
query.last();       // Move to last record  
query.previous();   // Move to previous record
query.seek(5);      // Move to specific position (0-based)
```

### 3. Position Query Methods
```cpp
int position = query.at();          // Current position (-1 if invalid)
bool isValid = query.isValid();     // True if pointing to valid record
bool isActive = query.isActive();   // True if query was executed successfully
int count = query.size();           // Number of records (if supported)
```

---

## Complete Function Analysis

### 1. `ajouter()` Function - Complete QSqlQuery Usage

```cpp
bool Employee::ajouter()
{
    // STEP 1: Create QSqlQuery object
    QSqlQuery query;
    
    // STEP 2: Prepare SQL with named placeholders
    query.prepare("INSERT INTO EMPLOYEES "
                  "(CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                  "HIRE_DATE, STATUS, AGE, GENDER, EMAIL, PHONE, SALARY, "
                  "PASSWORD, PHOTO, ID_A) "
                  "VALUES "
                  "(:cin, :firstName, :lastName, :position, :department, "
                  ":hireDate, :status, :age, :gender, :email, :phone, :salary, "
                  ":password, :photo, :idActivity)");
    
    // STEP 3: Bind all parameters safely
    query.bindValue(":cin", cin);                    // Required field - direct binding
    query.bindValue(":firstName", firstName);        // Required field - direct binding
    query.bindValue(":lastName", lastName);          // Required field - direct binding
    
    // Optional fields with null handling
    query.bindValue(":position", position.isEmpty() ? QVariant(QString()) : position);
    query.bindValue(":department", department.isEmpty() ? QVariant(QString()) : department);
    
    // Date with validation
    query.bindValue(":hireDate", hireDate.isValid() ? hireDate : QDate::currentDate());
    
    // String with default value
    query.bindValue(":status", status.isEmpty() ? "Active" : status);
    
    // Numeric fields with validation
    query.bindValue(":age", age > 0 ? QVariant(age) : QVariant(QMetaType(QMetaType::Int)));
    query.bindValue(":salary", salary > 0 ? QVariant(salary) : QVariant(QMetaType(QMetaType::Double)));
    
    // Optional string fields
    query.bindValue(":gender", gender.isEmpty() ? QVariant(QString()) : gender);
    query.bindValue(":email", email.isEmpty() ? QVariant(QString()) : email);
    query.bindValue(":phone", phone.isEmpty() ? QVariant(QString()) : phone);
    query.bindValue(":password", password.isEmpty() ? QVariant(QString()) : password);
    
    // Binary data (BLOB)
    query.bindValue(":photo", photo.isEmpty() ? QVariant(QByteArray()) : photo);
    
    // Foreign key
    query.bindValue(":idActivity", idActivity > 0 ? QVariant(idActivity) : QVariant(QMetaType(QMetaType::Int)));
    
    // STEP 4: Execute query with error handling
    if (!query.exec()) {
        qDebug() << "Employee::ajouter() - Database error:" << query.lastError().text();
        return false;
    }
    
    return true;
}
```

### 2. `rechercherParCin()` Function - Query with Results

```cpp
Employee* Employee::rechercherParCin(const QString &cin)
{
    // STEP 1: Create and prepare query
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                  "HIRE_DATE, STATUS, AGE, GENDER, EMAIL, PHONE, SALARY, "
                  "PASSWORD, PHOTO, ID_A "
                  "FROM EMPLOYEES WHERE CIN = :cin");
    
    // STEP 2: Bind parameter
    query.bindValue(":cin", cin);
    
    // STEP 3: Execute and check if record found
    if (query.exec() && query.next()) {
        
        // STEP 4: Create Employee object using query.value()
        Employee* emp = new Employee(
            query.value("CIN").toString(),           // Column by name
            query.value("FIRST_NAME").toString(),    // String conversion
            query.value("LAST_NAME").toString(),
            query.value("POSITION").toString(),
            query.value("DEPARTMENT").toString(),
            query.value("HIRE_DATE").toDate(),       // Date conversion
            query.value("STATUS").toString(),
            query.value("AGE").toInt(),              // Integer conversion
            query.value("GENDER").toString(),
            query.value("EMAIL").toString(),
            query.value("PHONE").toString(),
            query.value("SALARY").toDouble(),        // Double conversion
            query.value("PASSWORD").toString(),
            query.value("PHOTO").toByteArray(),      // Binary data conversion
            query.value("ID_A").toInt()              // Foreign key
        );
        
        return emp;
    }
    
    // STEP 5: Return nullptr if not found
    return nullptr;
}
```

### 3. `cinExiste()` Function - COUNT Query Pattern

```cpp
bool Employee::cinExiste(const QString &cin)
{
    QSqlQuery query;
    
    // Prepare COUNT query
    query.prepare("SELECT COUNT(*) FROM EMPLOYEES WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    
    // Execute and get count
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();  // First column (COUNT result)
        return count > 0;                    // True if any records found
    }
    
    qDebug() << "Error checking CIN existence:" << query.lastError().text();
    return false;  // Assume doesn't exist if query fails
}
```

### 4. `afficher()` Function - QSqlQueryModel Pattern

```cpp
QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    // Set query directly on model (no manual parameter binding needed)
    model->setQuery("SELECT CIN, FIRST_NAME, LAST_NAME, POSITION, DEPARTMENT, "
                    "GENDER, AGE, SALARY, EMAIL, PHONE, HIRE_DATE, STATUS "
                    "FROM EMPLOYEES "
                    "ORDER BY HIRE_DATE DESC");
    
    // Check for errors using model's lastError()
    if (model->lastError().isValid()) {
        qDebug() << "Employee::afficher() - Query error:" << model->lastError().text();
    }
    
    // Set column headers for UI display
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    // ... more headers
    
    return model;
}
```

---

## Best Practices & Common Patterns

### 1. Parameter Binding Best Practices

#### Always Use Named Parameters
```cpp
// GOOD - Clear and maintainable
query.prepare("SELECT * FROM EMPLOYEES WHERE CIN = :cin AND AGE > :minAge");
query.bindValue(":cin", cin);
query.bindValue(":minAge", 18);

// AVOID - Hard to maintain
query.prepare("SELECT * FROM EMPLOYEES WHERE CIN = ? AND AGE > ?");
query.addBindValue(cin);
query.addBindValue(18);
```

#### Handle NULL Values Properly
```cpp
// GOOD - Explicit null handling
query.bindValue(":optionalField", 
    value.isEmpty() ? QVariant(QString()) : value);

// AVOID - May cause unexpected behavior
query.bindValue(":optionalField", value);  // Empty string != NULL
```

### 2. Error Handling Patterns

#### Always Check exec() Return Value
```cpp
// GOOD - Proper error handling
if (!query.exec()) {
    qDebug() << "Query failed:" << query.lastError().text();
    qDebug() << "Query was:" << query.lastQuery();
    return false;
}

// AVOID - Ignoring errors
query.exec();  // What if it fails?
```

#### Log Detailed Error Information
```cpp
if (!query.exec()) {
    QSqlError error = query.lastError();
    qDebug() << "Database Error:";
    qDebug() << "  Text:" << error.text();
    qDebug() << "  Type:" << error.type();
    qDebug() << "  Query:" << query.lastQuery();
    qDebug() << "  Bound values:" << query.boundValues();
}
```

### 3. Data Retrieval Patterns

#### Use Column Names Instead of Indexes
```cpp
// GOOD - Robust against schema changes
QString name = query.value("FIRST_NAME").toString();
int age = query.value("AGE").toInt();

// AVOID - Fragile if columns are reordered
QString name = query.value(1).toString();  // What if columns change?
int age = query.value(7).toInt();
```

#### Check for NULL Values When Needed
```cpp
// Handle potentially NULL fields
QVariant photoVariant = query.value("PHOTO");
QByteArray photo;
if (!photoVariant.isNull()) {
    photo = photoVariant.toByteArray();
}
```

### 4. Performance Optimization Patterns

#### Reuse Prepared Queries
```cpp
class EmployeeDao {
private:
    QSqlQuery insertQuery;
    
public:
    EmployeeDao() {
        // Prepare once, use many times
        insertQuery.prepare("INSERT INTO EMPLOYEES (CIN, FIRST_NAME) VALUES (:cin, :name)");
    }
    
    bool addEmployee(const QString& cin, const QString& name) {
        insertQuery.bindValue(":cin", cin);
        insertQuery.bindValue(":name", name);
        return insertQuery.exec();
    }
};
```

#### Use Transactions for Multiple Operations
```cpp
QSqlDatabase::database().transaction();

bool success = true;
success &= addEmployee(emp1);
success &= addEmployee(emp2);
success &= addEmployee(emp3);

if (success) {
    QSqlDatabase::database().commit();
} else {
    QSqlDatabase::database().rollback();
}
```

### 5. Common QSqlQuery Mistakes to Avoid

#### 1. String Concatenation (SQL Injection Risk)
```cpp
// NEVER DO THIS - Vulnerable to SQL injection
QString sql = QString("SELECT * FROM EMPLOYEES WHERE CIN = '%1'").arg(cin);
QSqlQuery query(sql);

// ALWAYS DO THIS - Safe parameter binding
QSqlQuery query;
query.prepare("SELECT * FROM EMPLOYEES WHERE CIN = :cin");
query.bindValue(":cin", cin);
```

#### 2. Forgetting to Call next()
```cpp
// WRONG - Missing next() call
QSqlQuery query("SELECT * FROM EMPLOYEES");
if (query.exec()) {
    QString name = query.value("FIRST_NAME").toString();  // No data!
}

// CORRECT - Call next() first
QSqlQuery query("SELECT * FROM EMPLOYEES");
if (query.exec() && query.next()) {
    QString name = query.value("FIRST_NAME").toString();  // Has data
}
```

#### 3. Ignoring Return Values
```cpp
// WRONG - Not checking if exec() succeeded
query.exec();
while (query.next()) { /* Process data */ }

// CORRECT - Always check exec() return value
if (query.exec()) {
    while (query.next()) { /* Process data */ }
} else {
    qDebug() << "Query failed:" << query.lastError().text();
}
```

## Summary

**QSqlQuery** is your main tool for database operations in Qt. Key points:

1. **Always use `prepare()` and `bindValue()`** for security
2. **Check `exec()` return value** for error handling
3. **Use `next()`** to navigate through results
4. **Use `value()`** with proper type conversion to retrieve data
5. **Handle NULL values** appropriately with QVariant
6. **Log errors** using `lastError()` for debugging

This comprehensive understanding of QSqlQuery methods will help you confidently explain your database operations to your professor!