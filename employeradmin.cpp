#include "employeradmin.h"
#include "ui_employeradmin.h"

EmployerAdmin::EmployerAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmployerAdmin)
{
    ui->setupUi(this);
    
    // Setup navigation button group
    navigationButtonGroup = new QButtonGroup(this);
    navigationButtonGroup->addButton(ui->employeesButton, 0);    // Employees
    navigationButtonGroup->addButton(ui->membersButton, 1);      // Members  
    navigationButtonGroup->addButton(ui->equipmentButton, 2);    // Equipment
    navigationButtonGroup->addButton(ui->activitiesButton, 3);   // Activities
    navigationButtonGroup->addButton(ui->paymentsButton, 4);     // Payments
    
    // Setup connections
    setupConnections();
    
    // Setup tables
     setupEmployeeTable();
    //  setupStatisticsTable();
    
    // Populate with sample data
    populateEmployeeTable();
    // populateStatistics();

    // Set initial state
    ui->stackedWidget->setCurrentIndex(0); // Show employee page first
    ui->employeeTabWidget->setCurrentIndex(0); // Show list tab first
    
    // Set current date for hire date
    ui->hireDateEdit->setDate(QDate::currentDate());
    
    // Setup icons (optional - won't break anything if icons don't exist)
    setupIcons();
    
    // CSS styling is now handled in the UI file
    // setupButtonStyling();
}





EmployerAdmin::~EmployerAdmin()
{
    delete ui;
}

void EmployerAdmin::setupConnections()
{
    // Navigation buttons
    connect(navigationButtonGroup, &QButtonGroup::idClicked,
            this, [this](int id) {
                ui->stackedWidget->setCurrentIndex(id);
                updateNavigationStyle();
            });
    
    // Employee management buttons
    connect(ui->employeeSearchButton, &QPushButton::clicked, this, &EmployerAdmin::onSearchEmployees);
    connect(ui->employeeUploadPhotoButton, &QPushButton::clicked, this, &EmployerAdmin::onUploadPhoto);
    connect(ui->confirmAddButton, &QPushButton::clicked, this, &EmployerAdmin::onConfirmAdd);
    connect(ui->confirmUpdateButton, &QPushButton::clicked, this, &EmployerAdmin::onConfirmUpdate);
}

void EmployerAdmin::setupEmployeeTable()
{
    ui->employeeTable->setColumnWidth(0, 80);   // ID
    ui->employeeTable->setColumnWidth(1, 150);  // Name
    ui->employeeTable->setColumnWidth(2, 120);  // Position
    ui->employeeTable->setColumnWidth(3, 150);  // Department
    ui->employeeTable->setColumnWidth(4, 100);  // Hire Date
    ui->employeeTable->setColumnWidth(5, 80);   // Status
    ui->employeeTable->setColumnWidth(6, 120);  // Actions
    
    // Make table read-only
    ui->employeeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void EmployerAdmin::setupStatisticsTable()
{
    ui->departmentStatsTable->setRowCount(5);
    ui->departmentStatsTable->setColumnWidth(0, 200);  // Department
    ui->departmentStatsTable->setColumnWidth(1, 150);  // Count
    ui->departmentStatsTable->setColumnWidth(2, 100);  // Percentage
    
    // Make table read-only
    ui->departmentStatsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void EmployerAdmin::populateEmployeeTable()
{
    // Sample employee data
    QStringList employees[] = {
        {"EMP001", "John Doe", "Manager", "Activity Management", "2023-01-15", "Active"},
        {"EMP002", "Jane Smith", "Instructor", "Activity Management", "2023-02-20", "Active"},
        {"EMP003", "Mike Johnson", "Coordinator", "Member Management", "2023-03-10", "Active"},
        {"EMP004", "Sarah Wilson", "Supervisor", "Equipment Management", "2023-01-25", "On Leave"},
        {"EMP005", "David Brown", "Assistant", "Payment Management", "2023-04-05", "Active"},
        {"EMP006", "Lisa Garcia", "Trainer", "Activity Management", "2023-02-15", "Active"},
        {"EMP007", "Tom Anderson", "Maintenance", "Equipment Management", "2023-03-20", "Active"},
        {"EMP008", "Emma Davis", "Receptionist", "General Administration", "2023-01-30", "Active"}
    };
    
    int numEmployees = sizeof(employees) / sizeof(employees[0]);
    ui->employeeTable->setRowCount(numEmployees);
    
    for (int i = 0; i < numEmployees; ++i) {
        for (int j = 0; j < 6; ++j) {
            ui->employeeTable->setItem(i, j, new QTableWidgetItem(employees[i][j]));
        }
        
        // Add action buttons
        QPushButton *editBtn = new QPushButton("✏️ Edit");
        QPushButton *deleteBtn = new QPushButton("🗑️ Delete");
        
        editBtn->setStyleSheet("QPushButton { background-color: #f39c12; color: white; border: none; padding: 5px 10px; border-radius: 4px; }");
        deleteBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; padding: 5px 10px; border-radius: 4px; }");
        
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->addWidget(editBtn);
        actionLayout->addWidget(deleteBtn);
        actionLayout->setContentsMargins(5, 0, 5, 0);
        actionLayout->setSpacing(5);
        
        ui->employeeTable->setCellWidget(i, 6, actionWidget);
    }
}

void EmployerAdmin::populateStatistics()
{
    // Sample department statistics
    QStringList departments[] = {
        {"Activity Management", "15", "31.9%"},
        {"Member Management", "12", "25.5%"},
        {"Equipment Management", "8", "17.0%"},
        {"Payment Management", "7", "14.9%"},
        {"General Administration", "5", "10.6%"}
    };
    
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            ui->departmentStatsTable->setItem(i, j, new QTableWidgetItem(departments[i][j]));
        }
    }
}

void EmployerAdmin::onNavigationButtonClicked()
{
    updateNavigationStyle();
}

void EmployerAdmin::onSearchEmployees()
{
    QString searchTerm = ui->searchLineEdit->text().toLower();
    
    for (int i = 0; i < ui->employeeTable->rowCount(); ++i) {
        bool showRow = false;
        
        // Search in all columns except actions
        for (int j = 0; j < 6; ++j) {
            QTableWidgetItem *item = ui->employeeTable->item(i, j);
            if (item && item->text().toLower().contains(searchTerm)) {
                showRow = true;
                break;
            }
        }
        
        ui->employeeTable->setRowHidden(i, !showRow);
    }
    
    if (searchTerm.isEmpty()) {
        // Show all rows if search is empty
        for (int i = 0; i < ui->employeeTable->rowCount(); ++i) {
            ui->employeeTable->setRowHidden(i, false);
        }
    }
}

void EmployerAdmin::onUploadPhoto()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Employee Photo"), "",
        tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));
    
    if (!fileName.isEmpty()) {
        ui->photoLabel->setText("📷 Photo Selected: " + QFileInfo(fileName).fileName());
        QMessageBox::information(this, "Photo Upload", "Photo selected successfully!\n\nFile: " + QFileInfo(fileName).fileName());
    }
}

void EmployerAdmin::onConfirmAdd()
{
    // Validate required fields
    if (ui->empIdLineEdit->text().isEmpty() || 
        ui->firstNameLineEdit->text().isEmpty() || 
        ui->lastNameLineEdit->text().isEmpty() ||
        ui->emailLineEdit->text().isEmpty()) {
        
        QMessageBox::warning(this, "Validation Error", "Please fill in all required fields:\n- Employee ID\n- First Name\n- Last Name\n- Email");
        return;
    }
    
    // Show confirmation message
    QMessageBox::information(this, "Employee Added", 
        QString("Employee %1 %2 has been successfully added to the system!")
        .arg(ui->firstNameLineEdit->text())
        .arg(ui->lastNameLineEdit->text()));
    
    // Clear form and refresh table
    clearEmployeeForm();
    populateEmployeeTable(); // In a real application, this would add the new employee to the table
}

void EmployerAdmin::onConfirmUpdate()
{
    // Validate required fields
    if (ui->empIdLineEdit->text().isEmpty() || 
        ui->firstNameLineEdit->text().isEmpty() || 
        ui->lastNameLineEdit->text().isEmpty() ||
        ui->emailLineEdit->text().isEmpty()) {
        
        QMessageBox::warning(this, "Validation Error", "Please fill in all required fields:\n- Employee ID\n- First Name\n- Last Name\n- Email");
        return;
    }
    
    // Show confirmation message
    QMessageBox::information(this, "Employee Updated", 
        QString("Employee %1 %2 information has been successfully updated!")
        .arg(ui->firstNameLineEdit->text())
        .arg(ui->lastNameLineEdit->text()));
    
    // Clear form and refresh table
    clearEmployeeForm();
    populateEmployeeTable(); // In a real application, this would update the employee in the table
}

void EmployerAdmin::clearEmployeeForm()
{
    ui->empIdLineEdit->clear();
    ui->firstNameLineEdit->clear();
    ui->lastNameLineEdit->clear();
    ui->positionLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->phoneLineEdit->clear();
    ui->salaryLineEdit->clear();
    ui->notesTextEdit->clear();
    
    ui->departmentComboBox->setCurrentIndex(0);
    ui->genderComboBox->setCurrentIndex(0);
    ui->statusComboBox->setCurrentIndex(0);
    ui->ageSpinBox->setValue(25);
    ui->hireDateEdit->setDate(QDate::currentDate());
    
    ui->photoLabel->setText("📷 Upload Employee Photo");
}


void EmployerAdmin::setupIcons()
{
    QSize iconSize(24, 24);  // Set consistent icon size
    
    // Debug: Test icon loading
    qDebug() << "🔍 Testing icon loading...";
    qDebug() << "Application directory:" << QApplication::applicationDirPath();
    
    // Try loading icons from multiple locations
    QString appDir = QApplication::applicationDirPath();
    QStringList employeePaths = {
        appDir + "/employees.png",           // Same directory as executable
        appDir + "/icons/employees.png",     // Icons subdirectory
        ":/icons/employees.png"              // Qt resources (if working)
    };
    
    QIcon employeesIcon;
    for (const QString& path : employeePaths) {
        employeesIcon = QIcon(path);
        if (!employeesIcon.isNull()) {
            ui->employeesButton->setIcon(employeesIcon);
            ui->employeesButton->setIconSize(iconSize);
            qDebug() << "✅ Employees icon loaded from:" << path;
            break;
        } else {
            qDebug() << "❌ Failed to load from:" << path;
        }
    }
    
    QStringList memberPaths = {
        appDir + "/members.png",
        appDir + "/icons/members.png",
        ":/icons/members.png"
    };
    
    QIcon membersIcon;
    for (const QString& path : memberPaths) {
        membersIcon = QIcon(path);
        if (!membersIcon.isNull()) {
            ui->membersButton->setIcon(membersIcon);
            ui->membersButton->setIconSize(iconSize);
            qDebug() << "✅ Members icon loaded from:" << path;
            break;
        } else {
            qDebug() << "❌ Failed to load from:" << path;
        }
    }
    
    // Only focus on employees and members icons for now
    qDebug() << "🔧 Icon setup completed for employees and members buttons only.";
    
    QResource activityConfirmRes(":/icons/confirm.png");
    if (activityConfirmRes.isValid()) {
        ui->activityConfirmButton->setIcon(QIcon(":/icons/confirm.png"));
        ui->activityConfirmButton->setIconSize(iconSize);
    }
    
    QResource activityUpdateRes(":/icons/edit.png");
    if (activityUpdateRes.isValid()) {
        ui->activityUpdateButton->setIcon(QIcon(":/icons/edit.png"));
        ui->activityUpdateButton->setIconSize(iconSize);
    }
}

void EmployerAdmin::setupButtonStyling()
{
    // Define the consistent navigation button style (like the Payments button)
    QString navButtonStyle = 
        "QPushButton {"
        "    background-color: #16a5b3;"  // Teal background like Payments
        "    color: white;"
        "    border: none;"
        "    border-radius: 8px;"
        "    padding: 12px 20px;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    text-align: left;"
        "    margin: 2px 0px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #139aa6;"  // Darker teal on hover
        "}"
        "QPushButton:pressed {"
        "    background-color: #0f8087;"  // Even darker when pressed
        "}"
        "QPushButton:checked {"
        "    background-color: #0d6b70;"  // Different color when selected
        "    font-weight: 600;"
        "}";
    
    // Apply the style to all navigation buttons
    ui->employeesButton->setStyleSheet(navButtonStyle);
    ui->membersButton->setStyleSheet(navButtonStyle);
    ui->equipmentButton->setStyleSheet(navButtonStyle);
    ui->activitiesButton->setStyleSheet(navButtonStyle);
    
    // Set buttons as checkable so they can show selected state
    ui->employeesButton->setCheckable(true);
    ui->membersButton->setCheckable(true);
    ui->equipmentButton->setCheckable(true);
    ui->activitiesButton->setCheckable(true);
    
    // Make sure only one button can be checked at a time (handled by QButtonGroup)
    navigationButtonGroup->setExclusive(true);
    
    // Set the first button as initially selected
    ui->employeesButton->setChecked(true);
    
    // Style action buttons with a different color scheme
    QString actionButtonStyle = 
        "QPushButton {"
        "    background-color: #3498db;"  // Blue background
        "    color: white;"
        "    border: none;"
        "    border-radius: 6px;"
        "    padding: 8px 16px;"
        "    font-size: 13px;"
        "    font-weight: 500;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2980b9;"  // Darker blue on hover
        "}"
        "QPushButton:pressed {"
        "    background-color: #21618c;"  // Even darker when pressed
        "}";
    
    // Apply styling to action buttons
    ui->employeeSearchButton->setStyleSheet(actionButtonStyle);
    ui->employeeUploadPhotoButton->setStyleSheet(actionButtonStyle);
    ui->confirmAddButton->setStyleSheet(actionButtonStyle);
    ui->confirmUpdateButton->setStyleSheet(actionButtonStyle);
    ui->memberSearchButton->setStyleSheet(actionButtonStyle);
    ui->memberUploadPhotoButton->setStyleSheet(actionButtonStyle);
    ui->memberConfirmAddButton->setStyleSheet(actionButtonStyle);
    ui->memberConfirmUpdateButton->setStyleSheet(actionButtonStyle);
    ui->activitySearchButton->setStyleSheet(actionButtonStyle);
    ui->activityConfirmButton->setStyleSheet(actionButtonStyle);
    ui->activityUpdateButton->setStyleSheet(actionButtonStyle);
}

void EmployerAdmin::updateNavigationStyle()
{
    // This function can be used to update navigation styling if needed
    // Currently, the styling is handled by setupButtonStyling()
}
