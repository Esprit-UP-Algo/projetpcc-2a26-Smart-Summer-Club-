#include "employeradmin.h"
#include "ui_employeradmin.h"
#include <QPixmap>
#include <QFile>
#include <QStringConverter>
#include <QTextCursor>
EmployerAdmin::EmployerAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmployerAdmin)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/khali/OneDrive/Desktop/projetpcc-2a26-vibraclub-integration/assests/VibraClubLogo.png");
    ui->logo->setPixmap(pix.scaled(50, 50, Qt::KeepAspectRatio));
    
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
     setupMemberTable();
     setupActivityTable();
     setupEquipmentTable();
     setupEquipmentDetailsTable(); // Setup dynamic details table
     setupPaymentTable();
    //  setupStatisticsTable();
    
    // Populate with sample data
    populateEmployeeTable();
    populateMemberTable();
    populateActivityTable();
    populateEquipmentTable();
    populatePaymentTable();
    populatePaymentStatistics();
    // populateStatistics();

    // Set initial state
    ui->stackedWidget->setCurrentIndex(0); // Show employee page first
    ui->employeeTabWidget->setCurrentIndex(0); // Show list tab first
    
    // Set current date for hire date
    ui->hireDateEdit->setDate(QDate::currentDate());
    
    // Enable sorting on list tables
    ui->employeeTable->setSortingEnabled(true);
    ui->memberTable->setSortingEnabled(true);
    ui->activityTable->setSortingEnabled(true);
    ui->equipmentTable->setSortingEnabled(true);
    
    // Setup icons (optional - won't break anything if icons don't exist)
    setupIcons();
    
    // CSS styling is now handled in the UI file
    // setupButtonStyling();

    // Build advanced Cost Analysis chart (horizontal percentage bars)
    setupCostAnalysisChart();
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

    // Sort/Export - Employees
    connect(ui->employeeSortButton, &QPushButton::clicked, this, &EmployerAdmin::onSortEmployees);
    connect(ui->employeeExportButton, &QPushButton::clicked, this, &EmployerAdmin::onExportEmployees);

    // Sort/Export - Members
    connect(ui->memberSortButton, &QPushButton::clicked, this, &EmployerAdmin::onSortMembers);
    connect(ui->memberExportButton, &QPushButton::clicked, this, &EmployerAdmin::onExportMembers);

    // Sort/Export - Activities
    connect(ui->activitySortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &EmployerAdmin::onSortActivities);
    connect(ui->activityExportButton, &QPushButton::clicked, this, &EmployerAdmin::onExportActivities);

    // Sort/Export - Equipment
    connect(ui->equipmentSortButton, &QPushButton::clicked, this, &EmployerAdmin::onSortEquipment);
    connect(ui->equipmentExportButton, &QPushButton::clicked, this, &EmployerAdmin::onExportEquipment);
}

void EmployerAdmin::setupEmployeeTable()
{
    ui->employeeTable->setColumnCount(13);
    QStringList headers = {"Employee ID", "First Name", "Last Name", "Position", "Department", 
                          "Gender", "Age", "Salary", "Email", "Phone", "Hire Date", "Status", "Actions"};
    ui->employeeTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->employeeTable->setColumnWidth(0, 100);  // Employee ID
    ui->employeeTable->setColumnWidth(1, 120);  // First Name
    ui->employeeTable->setColumnWidth(2, 120);  // Last Name
    ui->employeeTable->setColumnWidth(3, 120);  // Position
    ui->employeeTable->setColumnWidth(4, 130);  // Department
    ui->employeeTable->setColumnWidth(5, 80);   // Gender
    ui->employeeTable->setColumnWidth(6, 60);   // Age
    ui->employeeTable->setColumnWidth(7, 100);  // Salary
    ui->employeeTable->setColumnWidth(8, 200);  // Email
    ui->employeeTable->setColumnWidth(9, 130);  // Phone
    ui->employeeTable->setColumnWidth(10, 100); // Hire Date
    ui->employeeTable->setColumnWidth(11, 80);  // Status
    ui->employeeTable->setColumnWidth(12, 150); // Actions
    
    // Make table read-only
    ui->employeeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// Generic sort by Name column (default index 1)
void EmployerAdmin::sortTableByName(QTableWidget* table, int nameColumnIndex)
{
    if (!table) return;

    // Toggle sorting order: if already sorted ascending, switch to descending
    static Qt::SortOrder lastOrder = Qt::AscendingOrder;
    lastOrder = (lastOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

    table->sortItems(nameColumnIndex, lastOrder);
}

// Export a QTableWidget to CSV (visible rows only, excluding action button cells)
bool EmployerAdmin::exportTableToCsv(QTableWidget* table, const QString& defaultName)
{
    if (!table) return false;

    QString filter = "CSV Files (*.csv)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export to CSV"), defaultName, filter);
    if (fileName.isEmpty()) return false;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Export Failed"), tr("Could not open file for writing."));
        return false;
    }

    QTextStream out(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    out.setEncoding(QStringConverter::Utf8);
#else
    out.setCodec("UTF-8");
#endif

    // Write header (exclude last column if it is Actions)
    int columns = table->columnCount();
    int headerColumns = columns;
    if (columns > 0) {
        QTableWidgetItem* lastHeader = table->horizontalHeaderItem(columns - 1);
        if (lastHeader && lastHeader->text().trimmed().compare("Actions", Qt::CaseInsensitive) == 0) {
            headerColumns = columns - 1;
        }
    }
    for (int c = 0; c < headerColumns; ++c) {
        QString h = table->horizontalHeaderItem(c) ? table->horizontalHeaderItem(c)->text() : QString();
        // CSV escaping: double any embedded quotes
        h.replace("\"", "\"\"");
        out << '"' << h << '"';
        if (c < headerColumns - 1) out << ',';
    }
    out << '\n';

    // Write data rows (visible only)
    for (int r = 0; r < table->rowCount(); ++r) {
        if (table->isRowHidden(r)) continue; // skip filtered-out rows
        for (int c = 0; c < headerColumns; ++c) {
            QTableWidgetItem* item = table->item(r, c);
            QString val = item ? item->text() : QString();
            // CSV escaping: double any embedded quotes
            val.replace("\"", "\"\"");
            out << '"' << val << '"';
            if (c < headerColumns - 1) out << ',';
        }
        out << '\n';
    }

    file.close();
    QMessageBox::information(this, tr("Export Complete"), tr("Data exported successfully to:\n%1").arg(QFileInfo(fileName).fileName()));
    return true;
}

// Export a QTableWidget to PDF (visible rows only, omit Actions)
bool EmployerAdmin::exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title)
{
    if (!table) return false;

    QString filter = "PDF Files (*.pdf)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export to PDF"), defaultName, filter);
    if (fileName.isEmpty()) return false;

    // Build simple HTML with branding and table
    int columns = table->columnCount();
    int headerColumns = columns;
    if (columns > 0) {
        QTableWidgetItem* lastHeader = table->horizontalHeaderItem(columns - 1);
        if (lastHeader && lastHeader->text().trimmed().compare("Actions", Qt::CaseInsensitive) == 0) {
            headerColumns = columns - 1;
        }
    }

    QString html;
    html += "<html><head>";
    html += "<meta charset='utf-8'>";
    html += "<style>"
            "body{font-family:Arial,Helvetica,sans-serif;color:#2c3e50;}"
            ".title{font-size:22px;font-weight:700;margin-bottom:8px;}"
            ".subtitle{color:#7f8c8d;margin-bottom:16px;}"
            "table{border-collapse:collapse;width:100%;}"
            "th,td{border:1px solid #e0e4e7;padding:8px;font-size:12px;}"
            "th{background:#16a5b3;color:#fff;text-align:left;}"
            "tr:nth-child(even){background:#f8fbfc;}"
            "</style>";
    html += "</head><body>";
    html += QString("<div class='title'>%1</div>").arg(title.toHtmlEscaped());
    html += "<div class='subtitle'>Generated by VIBRA CLUB • " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm") + "</div>";
    html += "<table><thead><tr>";
    for (int c = 0; c < headerColumns; ++c) {
        QString h = table->horizontalHeaderItem(c) ? table->horizontalHeaderItem(c)->text() : QString();
        html += "<th>" + h.toHtmlEscaped() + "</th>";
    }
    html += "</tr></thead><tbody>";
    for (int r = 0; r < table->rowCount(); ++r) {
        if (table->isRowHidden(r)) continue;
        html += "<tr>";
        for (int c = 0; c < headerColumns; ++c) {
            QString val = table->item(r, c) ? table->item(r, c)->text() : QString();
            html += "<td>" + val.toHtmlEscaped() + "</td>";
        }
        html += "</tr>";
    }
    html += "</tbody></table></body></html>";

    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::PrinterMode::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageMargins(QMarginsF(12, 12, 12, 12));
    doc.print(&printer);

    QMessageBox::information(this, tr("Export Complete"), tr("PDF exported successfully to:\n%1").arg(QFileInfo(fileName).fileName()));
    return true;
}

// Slots for sort/export per tab
void EmployerAdmin::onSortEmployees()
{
    // Sort by Hire Date column (index 4)
    sortTableByName(ui->employeeTable, 4);
}

void EmployerAdmin::onExportEmployees()
{
    exportTableToPdf(ui->employeeTable, "employees.pdf", tr("List of Employees"));
}

void EmployerAdmin::onSortMembers()
{
    // Sort by Join Date column (index 4)
    sortTableByName(ui->memberTable, 4);
}

void EmployerAdmin::onExportMembers()
{
    exportTableToPdf(ui->memberTable, "members.pdf", tr("List of Members"));
}

void EmployerAdmin::onSortActivities(int index)
{
    // Sort based on ComboBox selection:
    // 0: Sort by Date (Event Date column - index 2)
    // 1: Sort by Age (Age column - index 5) 
    // 2: Sort by Activity (Activity ID column - index 0)
    
    switch(index) {
        case 0: // Sort by Date
            sortTableByName(ui->activityTable, 2); // Event Date column
            break;
        case 1: // Sort by Age
            sortTableByName(ui->activityTable, 5); // Age column
            break;
        case 2: // Sort by Activity
            sortTableByName(ui->activityTable, 0); // Activity ID column
            break;
        default:
            sortTableByName(ui->activityTable, 2); // Default to Date
            break;
    }
}

void EmployerAdmin::onExportActivities()
{
    exportTableToPdf(ui->activityTable, "activities.pdf", tr("List of Activities"));
}

void EmployerAdmin::setupStatisticsTable()
{
    ui->departmentStatsTable->setRowCount(5);
    ui->departmentStatsTable->setColumnWidth(0, 220);  // Employee/Department
    ui->departmentStatsTable->setColumnWidth(1, 140);  // Hours Worked
    ui->departmentStatsTable->setColumnWidth(2, 100);  // Percentage
    
    // Make table read-only
    ui->departmentStatsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void EmployerAdmin::setupCostAnalysisChart()
{
    // Example data: map categories to percentages (Salary vs Revenue composition for demo)
    // You can later compute these from real data.
    struct Item { QString label; qreal percent; };
    QVector<Item> items = {
        {"Salaries", 32.0},
        {"Operations", 27.0},
        {"Marketing", 10.0},
        {"Miscellaneous", 6.0},
        {"Profit", 25.0}
    };

    // Build a single horizontal bar series for percentages
    auto *set = new QBarSet("");
    QStringList categories;
    for (const auto &it : items) {
        *set << it.percent;
        categories << it.label;
    }

    auto *series = new QHorizontalBarSeries();
    series->append(set);

    // Color styling to match brand (#16a5b3)
    QBrush teal(QColor("#16a5b3"));
    set->setBrush(teal);
    set->setPen(QPen(QColor("#1294a0")));

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->setBackgroundRoundness(8);
    chart->setBackgroundBrush(QBrush(Qt::transparent));
    chart->setPlotAreaBackgroundVisible(true);
    chart->setPlotAreaBackgroundBrush(QBrush(Qt::white));
    chart->setMargins(QMargins(8, 8, 16, 12));

    // Axes: categories at Y, percentage at X
    auto *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    axisY->setLabelsColor(QColor("#2c3e50"));
    axisY->setGridLineVisible(false);

    auto *axisX = new QValueAxis();
    axisX->setRange(0, 35); // visible up to ~35% as in design
    axisX->setTickCount(8); // 0,5,10,15,20,25,30,35
    axisX->setLabelFormat("%d%%");
    axisX->setLabelsColor(QColor("#7f8c8d"));
    axisX->setGridLineColor(QColor(0xCC, 0xD4, 0xD9));
    axisX->setGridLinePen(QPen(axisX->gridLineColor(), 1, Qt::DashLine));
    axisX->setMinorGridLineVisible(false);

    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisY);
    series->attachAxis(axisX);

    // Value labels at the end of bars: set labels on the series
    series->setLabelsVisible(true);
    series->setLabelsFormat("@value%");
    series->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);

    // Embed into a QChartView and place in costStatsFrame
    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumHeight(220);
    view->setStyleSheet("QChartView { background: transparent; }");

    // Insert at top of costStatsLayout (above the table)
    if (auto layout = ui->costStatsFrame->layout()) {
        layout->addWidget(view);
    }
}

void EmployerAdmin::populateEmployeeTable()
{
    // Clear existing data
    ui->employeeTable->setRowCount(0);
    
    // Sample employee data with all form fields
    // Format: {ID, FirstName, LastName, Position, Department, Gender, Age, Salary, Email, Phone, HireDate, Status}
    QStringList employees[] = {
        {"EMP001", "John", "Doe", "Manager", "Activity Management", "Male", "35", "$75,000", "john.doe@vibraclub.com", "+216 55 123 001", "2023-01-15", "Active"},
        {"EMP002", "Jane", "Smith", "Instructor", "Activity Management", "Female", "28", "$45,000", "jane.smith@vibraclub.com", "+216 55 123 002", "2023-02-20", "Active"},
        {"EMP003", "Mike", "Johnson", "Coordinator", "Member Management", "Male", "32", "$50,000", "mike.johnson@vibraclub.com", "+216 55 123 003", "2023-03-10", "Active"},
        {"EMP004", "Sarah", "Wilson", "Supervisor", "Equipment Management", "Female", "29", "$55,000", "sarah.wilson@vibraclub.com", "+216 55 123 004", "2023-01-25", "On Leave"},
        {"EMP005", "David", "Brown", "Assistant", "Payment Management", "Male", "26", "$40,000", "david.brown@vibraclub.com", "+216 55 123 005", "2023-04-05", "Active"},
        {"EMP006", "Lisa", "Garcia", "Trainer", "Activity Management", "Female", "31", "$48,000", "lisa.garcia@vibraclub.com", "+216 55 123 006", "2023-02-15", "Active"},
        {"EMP007", "Tom", "Anderson", "Maintenance", "Equipment Management", "Male", "45", "$42,000", "tom.anderson@vibraclub.com", "+216 55 123 007", "2023-03-20", "Active"},
        {"EMP008", "Emma", "Davis", "Receptionist", "General Administration", "Female", "24", "$35,000", "emma.davis@vibraclub.com", "+216 55 123 008", "2023-01-30", "Active"},
        {"EMP009", "Alex", "Martinez", "Trainer", "Activity Management", "Male", "27", "$46,000", "alex.martinez@vibraclub.com", "+216 55 123 009", "2023-05-10", "Active"},
        {"EMP010", "Sophie", "Turner", "Manager", "Member Management", "Female", "33", "$65,000", "sophie.turner@vibraclub.com", "+216 55 123 010", "2023-01-08", "Active"}
    };
    
    int numEmployees = sizeof(employees) / sizeof(employees[0]);
    ui->employeeTable->setRowCount(numEmployees);
    
    for (int i = 0; i < numEmployees; ++i) {
        for (int j = 0; j < 12; ++j) { // 12 data columns (excluding Actions)
            ui->employeeTable->setItem(i, j, new QTableWidgetItem(employees[i][j]));
        }
        
        // Add action buttons with proper icons
        QPushButton *editBtn = new QPushButton("Edit");
        QPushButton *deleteBtn = new QPushButton("Delete");
        
        // Set icons for action buttons
        editBtn->setIcon(QIcon(":/icons/icons/edit.png"));
        editBtn->setIconSize(QSize(16, 16));
        deleteBtn->setIcon(QIcon(":/icons/icons/delete.png"));
        deleteBtn->setIconSize(QSize(16, 16));
        
        // Style the buttons
        editBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65);   padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
        deleteBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");
        
        // Connect button signals (you can implement these slots)
        connect(editBtn, &QPushButton::clicked, [this, i]() {
            // Handle edit action for row i
            onEditEmployee(i);
        });
        connect(deleteBtn, &QPushButton::clicked, [this, i]() {
            // Handle delete action for row i
            onDeleteEmployee(i);
        });
        
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->addWidget(editBtn);
        actionLayout->addWidget(deleteBtn);
        actionLayout->setContentsMargins(5, 0, 5, 0);
        actionLayout->setSpacing(5);
        
        ui->employeeTable->setCellWidget(i, 12, actionWidget);
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
        ui->photoLabel->setText("Photo Selected: " + QFileInfo(fileName).fileName());
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
    
    ui->departmentComboBox->setCurrentIndex(0);
    ui->genderComboBox->setCurrentIndex(0);
    ui->statusComboBox->setCurrentIndex(0);
    ui->ageSpinBox->setValue(25);
    ui->hireDateEdit->setDate(QDate::currentDate());
    
    ui->photoLabel->setText("Upload Employee Photo");
}


void EmployerAdmin::setupIcons()
{
    QSize iconSize(24, 24);  // Set consistent icon size
    
    // Debug: Test icon loading
    qDebug() << "Testing icon loading with updated icon names...";
    qDebug() << "Application directory:" << QApplication::applicationDirPath();
    
    // Set icons for navigation buttons with new names
    if (!QIcon(":/icons/icons/employee.png").isNull()) {
        ui->employeesButton->setIcon(QIcon(":/icons/icons/employee.png"));
        ui->employeesButton->setIconSize(iconSize);
        qDebug() << "Employee icon loaded from resources";
    }
    
    if (!QIcon(":/icons/icons/members.png").isNull()) {
        ui->membersButton->setIcon(QIcon(":/icons/icons/members.png"));
        ui->membersButton->setIconSize(iconSize);
        qDebug() << "Members icon loaded from resources";
    }
    
    if (!QIcon(":/icons/icons/equipement.png").isNull()) {
        ui->equipmentButton->setIcon(QIcon(":/icons/icons/equipement.png"));
        ui->equipmentButton->setIconSize(iconSize);
        qDebug() << "Equipment icon loaded from resources";
    }
    
    if (!QIcon(":/icons/icons/activity.png").isNull()) {
        ui->activitiesButton->setIcon(QIcon(":/icons/icons/activity.png"));
        ui->activitiesButton->setIconSize(iconSize);
        qDebug() << "Activities icon loaded from resources";
    }
    
    if (!QIcon(":/icons/icons/payment.png").isNull()) {
        ui->paymentsButton->setIcon(QIcon(":/icons/icons/payment.png"));
        ui->paymentsButton->setIconSize(iconSize);
        qDebug() << "Payments icon loaded from resources";
    }
    
    // Set icons for action buttons with new names
    QSize actionIconSize(16, 16);  // Smaller icons for action buttons
    
    // Search buttons
    if (!QIcon(":/icons/icons/search.png").isNull()) {
        ui->employeeSearchButton->setIcon(QIcon(":/icons/icons/search.png"));
        ui->employeeSearchButton->setIconSize(actionIconSize);
        ui->memberSearchButton->setIcon(QIcon(":/icons/icons/search.png"));
        ui->memberSearchButton->setIconSize(actionIconSize);
        ui->activitySearchButton->setIcon(QIcon(":/icons/icons/search.png"));
        ui->activitySearchButton->setIconSize(actionIconSize);
        qDebug() << "Search icons loaded from resources";
    }

    // Sort buttons (using list icon as a generic sort symbol)
    if (!QIcon(":/icons/icons/list.png").isNull()) {
        ui->employeeSortButton->setIcon(QIcon(":/icons/icons/list.png"));
        ui->employeeSortButton->setIconSize(actionIconSize);
        ui->memberSortButton->setIcon(QIcon(":/icons/icons/list.png"));
        ui->memberSortButton->setIconSize(actionIconSize);
        // activitySortComboBox uses custom styling, no icon needed
    }

    // Export buttons (using payment icon as a placeholder for export)
    if (!QIcon(":/icons/icons/payment.png").isNull()) {
        ui->employeeExportButton->setIcon(QIcon(":/icons/icons/payment.png"));
        ui->employeeExportButton->setIconSize(actionIconSize);
        ui->memberExportButton->setIcon(QIcon(":/icons/icons/payment.png"));
        ui->memberExportButton->setIconSize(actionIconSize);
        ui->activityExportButton->setIcon(QIcon(":/icons/icons/payment.png"));
        ui->activityExportButton->setIconSize(actionIconSize);
    }
    
    // Add/Confirm buttons
    if (!QIcon(":/icons/icons/add.png").isNull()) {
        ui->confirmAddButton->setIcon(QIcon(":/icons/icons/add.png"));
        ui->confirmAddButton->setIconSize(actionIconSize);
        ui->memberConfirmAddButton->setIcon(QIcon(":/icons/icons/add.png"));
        ui->memberConfirmAddButton->setIconSize(actionIconSize);
        ui->activityConfirmButton->setIcon(QIcon(":/icons/icons/add.png"));
        ui->activityConfirmButton->setIconSize(actionIconSize);
        qDebug() << "Add icons loaded from resources";
    }
    
    // Update buttons
    if (!QIcon(":/icons/icons/edit.png").isNull()) {
        ui->confirmUpdateButton->setIcon(QIcon(":/icons/icons/edit.png"));
        ui->confirmUpdateButton->setIconSize(actionIconSize);
        ui->memberConfirmUpdateButton->setIcon(QIcon(":/icons/icons/edit.png"));
        ui->memberConfirmUpdateButton->setIconSize(actionIconSize);
        ui->activityUpdateButton->setIcon(QIcon(":/icons/icons/edit.png"));
        ui->activityUpdateButton->setIconSize(actionIconSize);
        qDebug() << "Edit icons loaded from resources";
    }
    
    // Upload buttons
    if (!QIcon(":/icons/icons/add.png").isNull()) {
        ui->employeeUploadPhotoButton->setIcon(QIcon(":/icons/icons/add.png"));
        ui->employeeUploadPhotoButton->setIconSize(actionIconSize);
        ui->memberUploadPhotoButton->setIcon(QIcon(":/icons/icons/add.png"));
        ui->memberUploadPhotoButton->setIconSize(actionIconSize);
        qDebug() << "Upload icons loaded from resources";
    }
    
    // Set icons for tab widgets programmatically (as backup to UI file settings)
    setupTabIcons();
    
    qDebug() << "Icon setup completed for all buttons and tabs with updated icon names.";
}

void EmployerAdmin::setupTabIcons()
{
    QSize tabIconSize(16, 16);
    
    // Employee tab icons
    ui->employeeTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));      // List tab
    ui->employeeTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));       // Add tab
    ui->employeeTabWidget->setTabIcon(2, QIcon(":/icons/icons/statistic.png")); // Statistics tab
    
    // Member tab icons
    ui->memberTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));      // List tab
    ui->memberTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));       // Add tab
    ui->memberTabWidget->setTabIcon(2, QIcon(":/icons/icons/statistic.png")); // Statistics tab
    
    // Activity tab icons
    ui->activityTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));      // List tab
    ui->activityTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));       // Add tab
    ui->activityTabWidget->setTabIcon(2, QIcon(":/icons/icons/statistic.png")); // Statistics tab
    
    qDebug() << "Tab icons set programmatically for all tab widgets";
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

void EmployerAdmin::onEditEmployee(int row)
{
    // Get employee data from the selected row
    QString id = ui->employeeTable->item(row, 0)->text();
    QString name = ui->employeeTable->item(row, 1)->text();
    QString position = ui->employeeTable->item(row, 2)->text();
    QString department = ui->employeeTable->item(row, 3)->text();
    QString hireDate = ui->employeeTable->item(row, 4)->text();
    QString status = ui->employeeTable->item(row, 5)->text();
    
    // Switch to Add Employee tab and populate form with existing data
    ui->employeeTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    // Populate the form fields with selected employee data
    // (You would need to identify the actual form field names from the UI)
    // This is a basic implementation - you may need to adjust based on your form fields
    
    QMessageBox::information(this, "Edit Employee", 
        QString("Editing employee: %1\nID: %2\nPosition: %3").arg(name, id, position));
}

void EmployerAdmin::onDeleteEmployee(int row)
{
    // Get employee data from the selected row
    QString id = ui->employeeTable->item(row, 0)->text();
    QString name = ui->employeeTable->item(row, 1)->text();
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Delete Employee", 
        QString("Are you sure you want to delete employee:\n%1 (ID: %2)?").arg(name, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->employeeTable->removeRow(row);
        
        QMessageBox::information(this, "Employee Deleted", 
            QString("Employee %1 has been deleted successfully.").arg(name));
    }
}

void EmployerAdmin::setupMemberTable()
{
    ui->memberTable->setColumnCount(10);
    QStringList headers = {"Member ID", "First Name", "Last Name", "Gender", "Age", 
                          "Email", "Phone Number", "Subscription Plan", "Join Date", "Actions"};
    ui->memberTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->memberTable->setColumnWidth(0, 100);  // Member ID
    ui->memberTable->setColumnWidth(1, 120);  // First Name
    ui->memberTable->setColumnWidth(2, 120);  // Last Name
    ui->memberTable->setColumnWidth(3, 80);   // Gender
    ui->memberTable->setColumnWidth(4, 60);   // Age
    ui->memberTable->setColumnWidth(5, 200);  // Email
    ui->memberTable->setColumnWidth(6, 130);  // Phone
    ui->memberTable->setColumnWidth(7, 120);  // Subscription
    ui->memberTable->setColumnWidth(8, 100);  // Join Date
    ui->memberTable->setColumnWidth(9, 150);  // Actions
}

void EmployerAdmin::populateMemberTable()
{
    // Clear existing data
    ui->memberTable->setRowCount(0);
    
    // Sample member data
    QStringList members[] = {
        {"MEM001", "Ahmed", "Ben Ali", "Male", "25", "ahmed.benali@email.com", "+216 55 123 456", "Monthly", "2024-01-15", ""},
        {"MEM002", "Fatma", "Gharbi", "Female", "28", "fatma.gharbi@email.com", "+216 56 234 567", "Weekly", "2024-02-20", ""},
        {"MEM003", "Mohamed", "Trabelsi", "Male", "32", "mohamed.trabelsi@email.com", "+216 57 345 678", "Monthly", "2024-01-10", ""},
        {"MEM004", "Sarra", "Mansouri", "Female", "24", "sarra.mansouri@email.com", "+216 58 456 789", "Daily", "2024-03-05", ""},
        {"MEM005", "Omar", "Bouazizi", "Male", "29", "omar.bouazizi@email.com", "+216 59 567 890", "Monthly", "2024-01-25", ""},
        {"MEM006", "Leila", "Jemli", "Female", "26", "leila.jemli@email.com", "+216 50 678 901", "Weekly", "2024-02-10", ""},
        {"MEM007", "Karim", "Selmi", "Male", "35", "karim.selmi@email.com", "+216 51 789 012", "Monthly", "2024-01-08", ""},
        {"MEM008", "Nadia", "Chakroun", "Female", "22", "nadia.chakroun@email.com", "+216 52 890 123", "Daily", "2024-03-12", ""},
        {"MEM009", "Youssef", "Hammami", "Male", "30", "youssef.hammami@email.com", "+216 53 901 234", "Monthly", "2024-02-01", ""},
        {"MEM010", "Rim", "Sassi", "Female", "27", "rim.sassi@email.com", "+216 54 012 345", "Weekly", "2024-02-18", ""}
    };
    
    int memberCount = sizeof(members) / sizeof(members[0]);
    ui->memberTable->setRowCount(memberCount);
    
    for (int row = 0; row < memberCount; ++row) {
        for (int col = 0; col < 9; ++col) { // 9 data columns (excluding Actions)
            QTableWidgetItem *item = new QTableWidgetItem(members[row][col]);
            ui->memberTable->setItem(row, col, item);
        }
        
        // Add Action buttons
        QPushButton *editBtn = new QPushButton("Edit");
        QPushButton *deleteBtn = new QPushButton("Delete");
        
        // Set icons for action buttons
        editBtn->setIcon(QIcon(":/icons/icons/edit.png"));
        editBtn->setIconSize(QSize(16, 16));
        deleteBtn->setIcon(QIcon(":/icons/icons/delete.png"));
        deleteBtn->setIconSize(QSize(16, 16));
        
        // Style the buttons
        editBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
        deleteBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");
        
        // Connect button signals
        connect(editBtn, &QPushButton::clicked, [this, row]() {
            onEditMember(row);
        });
        connect(deleteBtn, &QPushButton::clicked, [this, row]() {
            onDeleteMember(row);
        });
        
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->addWidget(editBtn);
        layout->addWidget(deleteBtn);
        layout->setContentsMargins(5, 0, 5, 0);
        layout->setSpacing(5);
        
        ui->memberTable->setCellWidget(row, 9, actionWidget);
        
        // Connect buttons (you can implement these handlers)
        connect(editBtn, &QPushButton::clicked, [this, row]() {
            QMessageBox::information(this, "Edit Member", QString("Edit member at row %1").arg(row + 1));
        });
        
        connect(deleteBtn, &QPushButton::clicked, [this, row]() {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Member", 
                QString("Are you sure you want to delete this member?"),
                QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                ui->memberTable->removeRow(row);
            }
        });
    }
}

void EmployerAdmin::setupActivityTable()
{
    ui->activityTable->setColumnCount(8);
    QStringList headers = {"Activity ID", "Type", "Event Date", "Time", "Responsible", 
                          "Age", "Status", "Actions"};
    ui->activityTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->activityTable->setColumnWidth(0, 100);  // Activity ID
    ui->activityTable->setColumnWidth(1, 150);  // Type
    ui->activityTable->setColumnWidth(2, 120);  // Event Date
    ui->activityTable->setColumnWidth(3, 80);   // Time
    ui->activityTable->setColumnWidth(4, 150);  // Responsible
    ui->activityTable->setColumnWidth(5, 60);   // Age
    ui->activityTable->setColumnWidth(6, 100);  // Status
    ui->activityTable->setColumnWidth(7, 150);  // Actions
}

void EmployerAdmin::populateActivityTable()
{
    // Clear existing data
    ui->activityTable->setRowCount(0);
    
    // Sample activity data
    QStringList activities[] = {
        {"ACT001", "Group Class", "2024-10-08", "09:00", "Ahmed Trainer", "18", "Scheduled", ""},
        {"ACT002", "Personal Training", "2024-10-08", "10:30", "Fatma Coach", "25", "In Progress", ""},
        {"ACT003", "Workshop", "2024-10-09", "14:00", "Mohamed Expert", "20", "Scheduled", ""},
        {"ACT004", "Competition", "2024-10-10", "16:00", "Sarra Judge", "18", "Completed", ""},
        {"ACT005", "Group Class", "2024-10-08", "18:00", "Omar Instructor", "16", "Scheduled", ""},
        {"ACT006", "Event", "2024-10-11", "19:30", "Leila Organizer", "21", "Cancelled", ""},
        {"ACT007", "Personal Training", "2024-10-09", "08:00", "Karim Trainer", "30", "Scheduled", ""},
        {"ACT008", "Maintenance", "2024-10-08", "07:00", "Nadia Tech", "0", "In Progress", ""},
        {"ACT009", "Workshop", "2024-10-12", "15:00", "Youssef Master", "22", "Scheduled", ""},
        {"ACT010", "Group Class", "2024-10-08", "20:00", "Rim Instructor", "18", "Postponed", ""},
        {"ACT011", "Competition", "2024-10-13", "17:00", "Ahmed Judge", "25", "Scheduled", ""},
        {"ACT012", "Event", "2024-10-14", "12:00", "Fatma Host", "16", "Scheduled", ""}
    };
    
    int activityCount = sizeof(activities) / sizeof(activities[0]);
    ui->activityTable->setRowCount(activityCount);
    
    for (int row = 0; row < activityCount; ++row) {
        for (int col = 0; col < 7; ++col) { // 7 data columns (excluding Actions)
            QTableWidgetItem *item = new QTableWidgetItem(activities[row][col]);
            ui->activityTable->setItem(row, col, item);
        }
        
        // Add Action buttons
        QPushButton *editBtn = new QPushButton("Edit");
        QPushButton *deleteBtn = new QPushButton("Delete");
        
        // Set icons for action buttons
        editBtn->setIcon(QIcon(":/icons/icons/edit.png"));
        editBtn->setIconSize(QSize(16, 16));
        deleteBtn->setIcon(QIcon(":/icons/icons/delete.png"));
        deleteBtn->setIconSize(QSize(16, 16));
        
        // Style the buttons
        editBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
        deleteBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");
        
        // Connect button signals
        connect(editBtn, &QPushButton::clicked, [this, row]() {
            onEditActivity(row);
        });
        connect(deleteBtn, &QPushButton::clicked, [this, row]() {
            onDeleteActivity(row);
        });
        
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->addWidget(editBtn);
        layout->addWidget(deleteBtn);
        layout->setContentsMargins(5, 0, 5, 0);
        layout->setSpacing(5);
        
        ui->activityTable->setCellWidget(row, 7, actionWidget);
        
        connect(deleteBtn, &QPushButton::clicked, [this, row]() {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Activity", 
                QString("Are you sure you want to delete this activity?"),
                QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                ui->activityTable->removeRow(row);
            }
        });
    }
}

void EmployerAdmin::onEditMember(int row)
{
    // Get member data from the selected row
    QString id = ui->memberTable->item(row, 0)->text();
    QString firstName = ui->memberTable->item(row, 1)->text();
    QString lastName = ui->memberTable->item(row, 2)->text();
    QString gender = ui->memberTable->item(row, 3)->text();
    QString age = ui->memberTable->item(row, 4)->text();
    QString email = ui->memberTable->item(row, 5)->text();
    QString phone = ui->memberTable->item(row, 6)->text();
    QString subscription = ui->memberTable->item(row, 7)->text();
    QString joinDate = ui->memberTable->item(row, 8)->text();
    
    // Switch to Add Member tab for editing
    ui->memberTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    // Populate the form fields with selected member data
    ui->memberIdLineEdit->setText(id);
    ui->memberFirstNameLineEdit->setText(firstName);
    ui->memberLastNameLineEdit->setText(lastName);
    ui->memberAgeSpinBox->setValue(age.toInt());
    ui->memberEmailLineEdit->setText(email);
    ui->memberPhoneLineEdit->setText(phone);
    
    // Set gender combo box
    int genderIndex = ui->memberGenderComboBox->findText(gender);
    if (genderIndex >= 0) {
        ui->memberGenderComboBox->setCurrentIndex(genderIndex);
    }
    
    // Set subscription combo box
    int subscriptionIndex = ui->memberSubscriptionComboBox->findText(subscription);
    if (subscriptionIndex >= 0) {
        ui->memberSubscriptionComboBox->setCurrentIndex(subscriptionIndex);
    }
    
    // Set join date
    QDate date = QDate::fromString(joinDate, "yyyy-MM-dd");
    ui->memberJoinDateEdit->setDate(date);
    
    QMessageBox::information(this, "Edit Member", 
        QString("Editing member: %1 %2\nID: %3").arg(firstName, lastName, id));
}

void EmployerAdmin::onDeleteMember(int row)
{
    // Get member data from the selected row
    QString id = ui->memberTable->item(row, 0)->text();
    QString firstName = ui->memberTable->item(row, 1)->text();
    QString lastName = ui->memberTable->item(row, 2)->text();
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Delete Member", 
        QString("Are you sure you want to delete member:\n%1 %2 (ID: %3)?").arg(firstName, lastName, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->memberTable->removeRow(row);
        
        QMessageBox::information(this, "Member Deleted", 
            QString("Member %1 %2 has been successfully deleted.").arg(firstName, lastName));
    }
}

void EmployerAdmin::onEditActivity(int row)
{
    // Get activity data from the selected row
    QString activityId = ui->activityTable->item(row, 0)->text();
    QString type = ui->activityTable->item(row, 1)->text();
    QString eventDate = ui->activityTable->item(row, 2)->text();
    QString time = ui->activityTable->item(row, 3)->text();
    QString responsible = ui->activityTable->item(row, 4)->text();
    QString age = ui->activityTable->item(row, 5)->text();
    QString status = ui->activityTable->item(row, 6)->text();
    
    // Switch to Add Activity tab for editing
    ui->activityTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    // Populate the form fields with selected activity data
    ui->activityIdLineEdit->setText(activityId);
    ui->responsibleLineEdit->setText(responsible);
    ui->activityAgeSpinBox->setValue(age.toInt());
    
    // Set type combo box
    int typeIndex = ui->activityTypeComboBox->findText(type);
    if (typeIndex >= 0) {
        ui->activityTypeComboBox->setCurrentIndex(typeIndex);
    }
    
    // Set status combo box
    int statusIndex = ui->activityStatusComboBox->findText(status);
    if (statusIndex >= 0) {
        ui->activityStatusComboBox->setCurrentIndex(statusIndex);
    }
    
    // Set event date
    QDate date = QDate::fromString(eventDate, "yyyy-MM-dd");
    ui->eventDateEdit->setDate(date);
    
    // Set event time
    QTime timeObj = QTime::fromString(time, "hh:mm");
    ui->eventTimeEdit->setTime(timeObj);
    
    QMessageBox::information(this, "Edit Activity", 
        QString("Editing activity: %1\nID: %2\nType: %3").arg(responsible, activityId, type));
}

void EmployerAdmin::onDeleteActivity(int row)
{
    // Get activity data from the selected row
    QString activityId = ui->activityTable->item(row, 0)->text();
    QString type = ui->activityTable->item(row, 1)->text();
    QString responsible = ui->activityTable->item(row, 4)->text();
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Delete Activity", 
        QString("Are you sure you want to delete activity:\n%1 - %2 (ID: %3)?").arg(type, responsible, activityId),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->activityTable->removeRow(row);
        
        QMessageBox::information(this, "Activity Deleted", 
            QString("Activity %1 has been successfully deleted.").arg(activityId));
    }
}

void EmployerAdmin::setupEquipmentTable()
{
    ui->equipmentTable->setColumnCount(6);
    QStringList headers = {"Equipment ID", "Name", "Category", "Total Stock", "Status", "Actions"};
    ui->equipmentTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->equipmentTable->setColumnWidth(0, 100);  // Equipment ID
    ui->equipmentTable->setColumnWidth(1, 150);  // Name
    ui->equipmentTable->setColumnWidth(2, 120);  // Category
    ui->equipmentTable->setColumnWidth(3, 80);   // Total Stock
    ui->equipmentTable->setColumnWidth(4, 100);  // Status
    ui->equipmentTable->setColumnWidth(5, 220);  // Actions
    
    // Make table read-only
    ui->equipmentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void EmployerAdmin::populateEquipmentTable()
{
    // Clear existing data
    ui->equipmentTable->setRowCount(0);
    
    // Sample equipment data - showing equipment TYPES with stock information
    QStringList equipmentTypes[] = {
        {"EQ001", "Treadmill", "Cardio", "15", "12", "3", "0", "Available"},
        {"EQ002", "Elliptical Machine", "Cardio", "8", "6", "2", "0", "Available"},
        {"EQ003", "Stationary Bike", "Cardio", "12", "10", "1", "1", "Maintenance Required"},
        {"EQ004", "Leg Press Machine", "Strength Training", "4", "3", "1", "0", "Available"},
        {"EQ005", "Bench Press", "Strength Training", "6", "4", "2", "0", "Available"},
        {"EQ006", "Dumbbells Set", "Free Weights", "25", "20", "5", "0", "Available"},
        {"EQ007", "Barbell Set", "Free Weights", "10", "8", "2", "0", "Available"},
        {"EQ008", "Kettlebells", "Functional Training", "20", "18", "2", "0", "Available"},
        {"EQ009", "Medicine Balls", "Functional Training", "15", "12", "3", "0", "Available"},
        {"EQ010", "Rowing Machine", "Cardio", "6", "5", "0", "1", "Maintenance Required"},
        {"EQ011", "Cable Machine", "Strength Training", "8", "7", "1", "0", "Available"},
        {"EQ012", "Yoga Mats", "Accessories", "50", "45", "5", "0", "Available"},
        {"EQ013", "Resistance Bands", "Accessories", "30", "25", "5", "0", "Available"},
        {"EQ014", "Safety Gloves", "Safety Equipment", "100", "85", "10", "5", "Low Stock"},
        {"EQ015", "First Aid Kit", "Safety Equipment", "5", "5", "0", "0", "Available"}
    };
    
    int equipmentCount = sizeof(equipmentTypes) / sizeof(equipmentTypes[0]);
    ui->equipmentTable->setRowCount(equipmentCount);
    
    for (int row = 0; row < equipmentCount; ++row) {
        // Only populate main columns: ID, Name, Category, Total Stock, Status
        ui->equipmentTable->setItem(row, 0, new QTableWidgetItem(equipmentTypes[row][0])); // ID
        ui->equipmentTable->setItem(row, 1, new QTableWidgetItem(equipmentTypes[row][1])); // Name
        ui->equipmentTable->setItem(row, 2, new QTableWidgetItem(equipmentTypes[row][2])); // Category
        ui->equipmentTable->setItem(row, 3, new QTableWidgetItem(equipmentTypes[row][3])); // Total Stock
        ui->equipmentTable->setItem(row, 4, new QTableWidgetItem(equipmentTypes[row][7])); // Status
        
        // Add Action buttons with equipment data captured for proper tracking
        QPushButton *detailsBtn = new QPushButton("Details");
        QPushButton *editBtn = new QPushButton("Edit");
        QPushButton *deleteBtn = new QPushButton("Delete");
        
        // Set icons for action buttons
        detailsBtn->setIcon(QIcon(":/icons/icons/list.png"));
        detailsBtn->setIconSize(QSize(16, 16));
        editBtn->setIcon(QIcon(":/icons/icons/edit.png"));
        editBtn->setIconSize(QSize(16, 16));
        deleteBtn->setIcon(QIcon(":/icons/icons/delete.png"));
        deleteBtn->setIconSize(QSize(16, 16));
        
        // Style the buttons
        detailsBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #3498db; }");
        editBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
        deleteBtn->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");
        
        // Capture equipment data to avoid row index issues
        QStringList equipmentData = equipmentTypes[row];
        
        // Connect button signals for equipment-specific actions with captured data
        connect(detailsBtn, &QPushButton::clicked, [this, equipmentData]() {
            onEquipmentDetails(equipmentData);
        });
        connect(editBtn, &QPushButton::clicked, [this, equipmentData]() {
            onEquipmentManage(equipmentData);
        });
        connect(deleteBtn, &QPushButton::clicked, [this, equipmentData, row]() {
            onEquipmentDelete(equipmentData, row);
        });
        
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->addWidget(detailsBtn);
        layout->addWidget(editBtn);
        layout->addWidget(deleteBtn);
        layout->setContentsMargins(5, 0, 5, 0);
        layout->setSpacing(3);
        
        ui->equipmentTable->setCellWidget(row, 5, actionWidget);
    }
}

void EmployerAdmin::onSortEquipment()
{
    // Sort by equipment name (index 1)
    sortTableByName(ui->equipmentTable, 1);
}

void EmployerAdmin::onExportEquipment()
{
    exportTableToPdf(ui->equipmentTable, "equipment.pdf", tr("Equipment Inventory Report"));
}

void EmployerAdmin::onEquipmentDetails(const QStringList &equipmentData)
{
    // Debug output
    qDebug() << "Details button clicked, isDetailsTableVisible:" << isDetailsTableVisible;
    qDebug() << "equipmentDetailsWidget exists:" << (equipmentDetailsWidget != nullptr);
    qDebug() << "equipmentDetailsTable exists:" << (equipmentDetailsTable != nullptr);
    
    // Toggle the details table visibility
    if (isDetailsTableVisible) {
        hideEquipmentDetailsTable();
    } else {
        showEquipmentDetailsTable(equipmentData);
    }
}

void EmployerAdmin::onEquipmentManage(const QStringList &equipmentData)
{
    // Extract equipment data from the passed list
    QString equipmentId = equipmentData[0];
    QString name = equipmentData[1];
    QString category = equipmentData[2];
    
    // Switch to Add Equipment tab for editing
    ui->equipmentTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    // Populate the form fields with selected equipment data
    ui->equipmentNameLineEdit->setText(name);
    
    // Set category combo box
    int categoryIndex = ui->equipmentCategoryComboBox->findText(category);
    if (categoryIndex >= 0) {
        ui->equipmentCategoryComboBox->setCurrentIndex(categoryIndex);
    }
    
    QMessageBox::information(this, "Edit Equipment", 
        QString("Editing equipment: %1\nID: %2\nCategory: %3").arg(name, equipmentId, category));
}

void EmployerAdmin::onEquipmentDelete(const QStringList &equipmentData, int row)
{
    // Extract equipment data from the passed list
    QString equipmentId = equipmentData[0];
    QString name = equipmentData[1];
    QString category = equipmentData[2];
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Delete Equipment", 
        QString("Are you sure you want to delete equipment:\n%1 - %2 (ID: %3)?").arg(category, name, equipmentId),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->equipmentTable->removeRow(row);
        
        QMessageBox::information(this, "Equipment Deleted", 
            QString("Equipment %1 has been successfully deleted.").arg(name));
    }
}

void EmployerAdmin::setupEquipmentDetailsTable()
{
    // Create the dynamic details widget and table
    equipmentDetailsWidget = new QWidget();
    equipmentDetailsWidget->setFixedSize(400, 400);
    equipmentDetailsWidget->setVisible(false);
    isDetailsTableVisible = false;
    
    // Set styling for the details widget
    equipmentDetailsWidget->setStyleSheet(
        "QWidget { "
        "background-color: white; "
        "border: 2px solid #16a5b3; "
        "border-radius: 8px; "
        "}"
    );
    
    // Create the details table
    equipmentDetailsTable = new QTableWidget();
    equipmentDetailsTable->setColumnCount(2);
    equipmentDetailsTable->setRowCount(6);
    equipmentDetailsTable->setHorizontalHeaderLabels(QStringList() << "Property" << "Value");
    equipmentDetailsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    equipmentDetailsTable->verticalHeader()->setVisible(false);
    equipmentDetailsTable->setAlternatingRowColors(true);
    equipmentDetailsTable->setFixedSize(360, 300);
    
    // Set row height for better visibility
    equipmentDetailsTable->verticalHeader()->setDefaultSectionSize(40);
    
    // Set column widths
    equipmentDetailsTable->setColumnWidth(0, 170);
    equipmentDetailsTable->setColumnWidth(1, 170);
    
    // Style the details table
    equipmentDetailsTable->setStyleSheet(
        "QTableWidget { "
        "border: 1px solid #e0e4e7; "
        "border-radius: 4px; "
        "background-color: #f8fbfc; "
        "font-size: 14px; "
        "} "
        "QHeaderView::section { "
        "background-color: #16a5b3; "
        "color: white; "
        "padding: 10px; "
        "border: none; "
        "font-weight: bold; "
        "font-size: 14px; "
        "}"
    );
    
    // Create layout for details widget
    QVBoxLayout *detailsLayout = new QVBoxLayout(equipmentDetailsWidget);
    
    // Add title label
    QLabel *titleLabel = new QLabel("Equipment Details");
    titleLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #2c3e50; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    // Add close button
    QPushButton *closeBtn = new QPushButton("×");
    closeBtn->setFixedSize(25, 25);
    closeBtn->setStyleSheet(
        "QPushButton { "
        "background-color: #c0392b; "
        "color: white; "
        "border: none; "
        "border-radius: 12px; "
        "font-size: 16px; "
        "font-weight: bold; "
        "} "
        "QPushButton:hover { "
        "background-color: #a93226; "
        "}"
    );
    
    connect(closeBtn, &QPushButton::clicked, this, &EmployerAdmin::hideEquipmentDetailsTable);
    
    // Create top layout with title and close button
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();
    topLayout->addWidget(closeBtn);
    
    detailsLayout->addLayout(topLayout);
    detailsLayout->addWidget(equipmentDetailsTable);
    detailsLayout->setContentsMargins(10, 10, 10, 10);
    
    // Create a horizontal layout container for the equipmentListTab
    if (ui->equipmentListTab) {
        // Create a main horizontal layout for the tab content
        QHBoxLayout *mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(15);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        
        // Create a container widget for the existing equipment table and controls
        QWidget *tableContainer = new QWidget();
        QVBoxLayout *tableLayout = new QVBoxLayout(tableContainer);
        tableLayout->setContentsMargins(0, 0, 0, 0);
        
        // Move the existing equipment table to the container
        // (The equipment table should already be in the tab, we'll work around the existing layout)
        
        // Add the table container and details widget to the main layout
        mainLayout->addWidget(tableContainer, 3); // Table takes 75% of width
        mainLayout->addWidget(equipmentDetailsWidget, 1); // Details take 25% of width
        
        // If the tab already has a layout, we need to work with it
        QLayout *existingLayout = ui->equipmentListTab->layout();
        if (!existingLayout) {
            // If no layout exists, set our new layout
            ui->equipmentListTab->setLayout(mainLayout);
        } else {
            // If layout exists, we'll add our details widget as a child of the tab
            // and position it manually (fallback approach)
            equipmentDetailsWidget->setParent(ui->equipmentListTab);
        }
    }
}

void EmployerAdmin::showEquipmentDetailsTable(const QStringList &equipmentData)
{
    qDebug() << "showEquipmentDetailsTable called";
    if (!equipmentDetailsTable || !equipmentDetailsWidget) {
        qDebug() << "equipmentDetailsTable or equipmentDetailsWidget is null!";
        return;
    }
    
    // Extract data from the equipment data list
    QString equipmentId = equipmentData[0];
    QString name = equipmentData[1];
    QString category = equipmentData[2];
    QString totalStock = equipmentData[3];
    QString available = equipmentData[4];
    QString inUse = equipmentData[5];
    QString maintenance = equipmentData[6];
    
    // Calculate percentages
    double totalStockNum = totalStock.toDouble();
    double usageRate = totalStockNum > 0 ? (inUse.toDouble() / totalStockNum) * 100 : 0;
    double availableRate = totalStockNum > 0 ? (available.toDouble() / totalStockNum) * 100 : 0;
    
    // Populate the details table
    equipmentDetailsTable->setItem(0, 0, new QTableWidgetItem("Equipment ID"));
    equipmentDetailsTable->setItem(0, 1, new QTableWidgetItem(equipmentId));
    
    equipmentDetailsTable->setItem(1, 0, new QTableWidgetItem("Available"));
    equipmentDetailsTable->setItem(1, 1, new QTableWidgetItem(available + " units"));
    
    equipmentDetailsTable->setItem(2, 0, new QTableWidgetItem("In Use"));
    equipmentDetailsTable->setItem(2, 1, new QTableWidgetItem(inUse + " units"));
    
    equipmentDetailsTable->setItem(3, 0, new QTableWidgetItem("Under Maintenance"));
    equipmentDetailsTable->setItem(3, 1, new QTableWidgetItem(maintenance + " units"));
    
    equipmentDetailsTable->setItem(4, 0, new QTableWidgetItem("Usage Rate"));
    equipmentDetailsTable->setItem(4, 1, new QTableWidgetItem(QString::number(usageRate, 'f', 1) + "%"));
    
    equipmentDetailsTable->setItem(5, 0, new QTableWidgetItem("Availability Rate"));
    equipmentDetailsTable->setItem(5, 1, new QTableWidgetItem(QString::number(availableRate, 'f', 1) + "%"));
    
    // Position the details widget to the right side of the tab
    if (ui->equipmentListTab && ui->equipmentTable) {
        // Get the equipment table position and size
        QRect tableGeometry = ui->equipmentTable->geometry();
        QSize tabSize = ui->equipmentListTab->size();
        
        // Position the details widget to the right of the equipment table
        int x = tableGeometry.right() + 20; // 20 pixels margin from the table
        int y = tableGeometry.top(); // Align with the top of the table
        
        // Make sure it fits within the tab bounds
        if (x + equipmentDetailsWidget->width() > tabSize.width()) {
            x = tabSize.width() - equipmentDetailsWidget->width() - 10;
        }
        
        // Ensure it doesn't go off screen
        if (x < tableGeometry.right() + 10) {
            x = tableGeometry.right() + 10;
        }
        
        equipmentDetailsWidget->move(x, y);
    }
    
    // Show the details widget
    qDebug() << "Setting widget visible at position:" << equipmentDetailsWidget->pos();
    qDebug() << "Widget size:" << equipmentDetailsWidget->size();
    equipmentDetailsWidget->setVisible(true);
    equipmentDetailsWidget->raise(); // Bring to front
    isDetailsTableVisible = true;
    qDebug() << "Widget visibility set to:" << equipmentDetailsWidget->isVisible();
}

void EmployerAdmin::hideEquipmentDetailsTable()
{
    if (equipmentDetailsWidget) {
        equipmentDetailsWidget->setVisible(false);
        isDetailsTableVisible = false;
    }
}

// ===============================
// PAYMENT MANAGEMENT FUNCTIONS
// ===============================

void EmployerAdmin::setupPaymentTable()
{
    QTableWidget* paymentTable = ui->paymentTable;
    
    // Configure table properties
    paymentTable->setRowCount(0);
    paymentTable->setColumnCount(9);
    
    QStringList headers;
    headers << "Transaction ID" << "Date" << "Description" << "Type" << "Amount" << "Method" << "Status" << "Member ID" << "Actions";
    paymentTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    paymentTable->setColumnWidth(0, 100); // Transaction ID
    paymentTable->setColumnWidth(1, 100); // Date  
    paymentTable->setColumnWidth(2, 200); // Description
    paymentTable->setColumnWidth(3, 80);  // Type
    paymentTable->setColumnWidth(4, 100); // Amount
    paymentTable->setColumnWidth(5, 120); // Method
    paymentTable->setColumnWidth(6, 80);  // Status
    paymentTable->setColumnWidth(7, 100); // Member ID
    paymentTable->setColumnWidth(8, 160); // Actions
    
    // Setup connections for form and filters
    connect(ui->addPaymentButton, &QPushButton::clicked, this, &EmployerAdmin::onAddPayment);
    connect(ui->clearPaymentFormButton, &QPushButton::clicked, this, &EmployerAdmin::onClearPaymentForm);
    connect(ui->paymentSearchLineEdit, &QLineEdit::textChanged, this, &EmployerAdmin::onPaymentSearchTextChanged);
}

void EmployerAdmin::populatePaymentTable()
{
    QTableWidget* paymentTable = ui->paymentTable;
    
    // Sample payment data
    QList<QStringList> payments = {
        {"PAY001", "2025-10-01", "Monthly Membership - John Smith", "Income", "$50.00", "Credit Card", "Completed", "MEM001"},
        {"PAY002", "2025-10-02", "Equipment Purchase - Surfboard", "Expense", "$300.00", "Bank Transfer", "Completed", ""},
        {"PAY003", "2025-10-03", "Coaching Session - Sarah Johnson", "Income", "$25.00", "Cash", "Completed", "MEM015"},
        {"PAY004", "2025-10-04", "Utility Bill - Electricity", "Expense", "$150.00", "Online Payment", "Pending", ""},
        {"PAY005", "2025-10-05", "Annual Membership - Mike Wilson", "Income", "$500.00", "Check", "Completed", "MEM008"},
        {"PAY006", "2025-10-06", "Staff Salary - October", "Expense", "$2500.00", "Bank Transfer", "Completed", ""},
        {"PAY007", "2025-10-07", "Equipment Maintenance", "Expense", "$75.00", "Cash", "Completed", ""},
        {"PAY008", "2025-10-08", "Guest Pass - Day Access", "Income", "$15.00", "Credit Card", "Completed", "GUEST001"}
    };
    
    paymentTable->setRowCount(payments.size());
    
    for (int i = 0; i < payments.size(); ++i) {
        const QStringList &payment = payments[i];
        
        // Add payment data to columns
        for (int j = 0; j < payment.size(); ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(payment[j]);
            
            // Color coding for amount column based on type
            if (j == 4) { // Amount column
                if (payment[3] == "Income") {
                    item->setForeground(QBrush(QColor("#2ecc71"))); // Green for income
                } else {
                    item->setForeground(QBrush(QColor("#e74c3c"))); // Red for expenses
                }
                item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
            
            // Color coding for status column
            if (j == 6) { // Status column
                if (payment[6] == "Completed") {
                    item->setForeground(QBrush(QColor("#2ecc71"))); // Green
                } else if (payment[6] == "Pending") {
                    item->setForeground(QBrush(QColor("#f39c12"))); // Orange
                } else if (payment[6] == "Failed") {
                    item->setForeground(QBrush(QColor("#e74c3c"))); // Red
                }
            }
            
            paymentTable->setItem(i, j, item);
        }
        
        // Add action buttons in the last column
        QWidget* actionWidget = new QWidget();
        QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(5, 0, 5, 0);
        actionLayout->setSpacing(5);
        
        QPushButton* editButton = new QPushButton("Edit");
        QPushButton* deleteButton = new QPushButton("Delete");
        
        // Set icons for action buttons
        editButton->setIcon(QIcon(":/icons/icons/edit.png"));
        editButton->setIconSize(QSize(16, 16));
        deleteButton->setIcon(QIcon(":/icons/icons/delete.png"));
        deleteButton->setIconSize(QSize(16, 16));
        
        // Style the buttons to match employee table
        editButton->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
        deleteButton->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");
        
        // Capture payment data for button callbacks
        QStringList paymentData = payment;
        
        connect(editButton, &QPushButton::clicked, [this, paymentData]() {
            onEditPayment(paymentData);
        });
        
        connect(deleteButton, &QPushButton::clicked, [this, paymentData, i]() {
            onDeletePayment(paymentData, i);
        });
        
        actionLayout->addWidget(editButton);
        actionLayout->addWidget(deleteButton);
        actionWidget->setLayout(actionLayout);
        
        paymentTable->setCellWidget(i, 8, actionWidget);
    }
}

void EmployerAdmin::populatePaymentStatistics()
{
    // Calculate totals from payment table
    QTableWidget* paymentTable = ui->paymentTable;
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    
    for (int i = 0; i < paymentTable->rowCount(); ++i) {
        QString typeText = paymentTable->item(i, 3)->text(); // Type column
        QString amountText = paymentTable->item(i, 4)->text(); // Amount column
        
        // Extract numeric value from amount (remove $ symbol)
        QString numericAmount = amountText;
        numericAmount.remove("$");
        double amount = numericAmount.toDouble();
        
        if (typeText == "Income") {
            totalIncome += amount;
        } else if (typeText == "Expense") {
            totalExpense += amount;
        }
    }
    
    double netBalance = totalIncome - totalExpense;
    
    // Update summary labels
    ui->totalIncomeValue->setText(QString("$%1").arg(totalIncome, 0, 'f', 2));
    ui->totalExpenseValue->setText(QString("$%1").arg(totalExpense, 0, 'f', 2));
    ui->netBalanceValue->setText(QString("$%1").arg(netBalance, 0, 'f', 2));
    
    // Color code net balance value text (keeping card white)
    if (netBalance >= 0) {
        ui->netBalanceValue->setStyleSheet("font-size: 20px; font-weight: bold; color: #2ecc71;");
    } else {
        ui->netBalanceValue->setStyleSheet("font-size: 20px; font-weight: bold; color: #e74c3c;");
    }
    
    // Populate payment method statistics
    QTableWidget* methodStatsTable = ui->paymentMethodStatsTable;
    QMap<QString, QPair<int, double>> methodStats; // method -> (count, total amount)
    
    for (int i = 0; i < paymentTable->rowCount(); ++i) {
        QString method = paymentTable->item(i, 5)->text(); // Method column
        QString amountText = paymentTable->item(i, 4)->text(); // Amount column
        
        QString numericAmount = amountText;
        numericAmount.remove("$");
        double amount = numericAmount.toDouble();
        
        if (methodStats.contains(method)) {
            methodStats[method].first += 1;
            methodStats[method].second += amount;
        } else {
            methodStats[method] = QPair<int, double>(1, amount);
        }
    }
    
    methodStatsTable->setRowCount(methodStats.size());
    int row = 0;
    double totalAmount = totalIncome + totalExpense;
    
    for (auto it = methodStats.begin(); it != methodStats.end(); ++it) {
        QString method = it.key();
        int count = it.value().first;
        double amount = it.value().second;
        double percentage = (totalAmount > 0) ? (amount / totalAmount) * 100.0 : 0.0;
        
        methodStatsTable->setItem(row, 0, new QTableWidgetItem(method));
        methodStatsTable->setItem(row, 1, new QTableWidgetItem(QString::number(count)));
        methodStatsTable->setItem(row, 2, new QTableWidgetItem(QString("$%1").arg(amount, 0, 'f', 2)));
        methodStatsTable->setItem(row, 3, new QTableWidgetItem(QString("%1%").arg(percentage, 0, 'f', 1)));
        
        row++;
    }
    
    // Populate recent payments table (last 10 transactions)
    QTableWidget* recentTable = ui->recentPaymentsTable;
    int recentCount = qMin(10, paymentTable->rowCount());
    recentTable->setRowCount(recentCount);
    
    for (int i = 0; i < recentCount; ++i) {
        // Copy data from main payment table (most recent first)
        int sourceRow = paymentTable->rowCount() - 1 - i;
        
        recentTable->setItem(i, 0, new QTableWidgetItem(paymentTable->item(sourceRow, 1)->text())); // Date
        recentTable->setItem(i, 1, new QTableWidgetItem(paymentTable->item(sourceRow, 2)->text())); // Description
        recentTable->setItem(i, 2, new QTableWidgetItem(paymentTable->item(sourceRow, 3)->text())); // Type
        
        // Amount with color coding
        QTableWidgetItem* amountItem = new QTableWidgetItem(paymentTable->item(sourceRow, 4)->text());
        QString type = paymentTable->item(sourceRow, 3)->text();
        if (type == "Income") {
            amountItem->setForeground(QBrush(QColor("#2ecc71")));
        } else {
            amountItem->setForeground(QBrush(QColor("#e74c3c")));
        }
        amountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        recentTable->setItem(i, 3, amountItem);
        
        // Status with color coding
        QTableWidgetItem* statusItem = new QTableWidgetItem(paymentTable->item(sourceRow, 6)->text());
        QString status = paymentTable->item(sourceRow, 6)->text();
        if (status == "Completed") {
            statusItem->setForeground(QBrush(QColor("#2ecc71")));
        } else if (status == "Pending") {
            statusItem->setForeground(QBrush(QColor("#f39c12")));
        } else if (status == "Failed") {
            statusItem->setForeground(QBrush(QColor("#e74c3c")));
        }
        recentTable->setItem(i, 4, statusItem);
    }
}

void EmployerAdmin::onAddPayment()
{
    // Validate required fields
    if (ui->paymentDescriptionEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a description for the transaction.");
        return;
    }
    
    if (ui->paymentAmountSpinBox->value() <= 0) {
        QMessageBox::warning(this, "Warning", "Please enter a valid amount greater than 0.");
        return;
    }
    
    // Generate new transaction ID
    QTableWidget* paymentTable = ui->paymentTable;
    QString newTransactionId = QString("PAY%1").arg(paymentTable->rowCount() + 1, 3, 10, QChar('0'));
    
    // Get form data
    QString type = ui->paymentTypeCombo->currentText();
    QString date = ui->paymentDateEdit->date().toString("yyyy-MM-dd");
    QString description = ui->paymentDescriptionEdit->text().trimmed();
    QString amount = QString("$%1").arg(ui->paymentAmountSpinBox->value(), 0, 'f', 2);
    QString method = ui->paymentMethodCombo->currentText();
    QString category = ui->paymentCategoryCombo->currentText();
    QString memberId = ui->paymentMemberEdit->text().trimmed();
    QString status = ui->paymentStatusCombo->currentText();
    
    // Add new row to table
    int newRow = paymentTable->rowCount();
    paymentTable->insertRow(newRow);
    
    // Create payment data list
    QStringList newPayment = {newTransactionId, date, description, type, amount, method, status, memberId};
    
    // Add data to table
    for (int j = 0; j < newPayment.size(); ++j) {
        QTableWidgetItem* item = new QTableWidgetItem(newPayment[j]);
        
        // Color coding for amount
        if (j == 4) { // Amount column
            if (type == "Income") {
                item->setForeground(QBrush(QColor("#2ecc71")));
            } else {
                item->setForeground(QBrush(QColor("#e74c3c")));
            }
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }
        
        // Color coding for status
        if (j == 6) { // Status column
            if (status == "Completed") {
                item->setForeground(QBrush(QColor("#2ecc71")));
            } else if (status == "Pending") {
                item->setForeground(QBrush(QColor("#f39c12")));
            } else if (status == "Failed") {
                item->setForeground(QBrush(QColor("#e74c3c")));
            }
        }
        
        paymentTable->setItem(newRow, j, item);
    }
    
    // Add action buttons
    QWidget* actionWidget = new QWidget();
    QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
    actionLayout->setContentsMargins(5, 0, 5, 0);
    actionLayout->setSpacing(5);
    
    QPushButton* editButton = new QPushButton("Edit");
    QPushButton* deleteButton = new QPushButton("Delete");
    
    // Set icons for action buttons
    editButton->setIcon(QIcon(":/icons/icons/edit.png"));
    editButton->setIconSize(QSize(16, 16));
    deleteButton->setIcon(QIcon(":/icons/icons/delete.png"));
    deleteButton->setIconSize(QSize(16, 16));
    
    // Style the buttons to match employee table
    editButton->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
    deleteButton->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");
    
    connect(editButton, &QPushButton::clicked, [this, newPayment]() {
        onEditPayment(newPayment);
    });
    
    connect(deleteButton, &QPushButton::clicked, [this, newPayment, newRow]() {
        onDeletePayment(newPayment, newRow);
    });
    
    actionLayout->addWidget(editButton);
    actionLayout->addWidget(deleteButton);
    paymentTable->setCellWidget(newRow, 8, actionWidget);
    
    // Update statistics
    populatePaymentStatistics();
    
    // Clear form
    onClearPaymentForm();
    
    // Show success message
    QMessageBox::information(this, "Success", "Payment transaction added successfully!");
    
    // Switch to payment list tab
    ui->paymentTabWidget->setCurrentIndex(0);
}

void EmployerAdmin::onClearPaymentForm()
{
    ui->paymentTypeCombo->setCurrentIndex(0);
    ui->paymentDateEdit->setDate(QDate::currentDate());
    ui->paymentDescriptionEdit->clear();
    ui->paymentAmountSpinBox->setValue(0.00);
    ui->paymentMethodCombo->setCurrentIndex(0);
    ui->paymentCategoryCombo->setCurrentIndex(0);
    ui->paymentMemberEdit->clear();
    ui->paymentStatusCombo->setCurrentIndex(0);
}

void EmployerAdmin::onPaymentSearchTextChanged()
{
    QString searchText = ui->paymentSearchLineEdit->text().trimmed().toLower();
    QTableWidget* paymentTable = ui->paymentTable;
    
    for (int i = 0; i < paymentTable->rowCount(); ++i) {
        bool shouldShow = false;
        
        // Search in relevant columns (Transaction ID, Description, Member ID)
        QList<int> searchColumns = {0, 2, 7}; // Transaction ID, Description, Member ID
        
        for (int col : searchColumns) {
            QTableWidgetItem* item = paymentTable->item(i, col);
            if (item && item->text().toLower().contains(searchText)) {
                shouldShow = true;
                break;
            }
        }
        
        paymentTable->setRowHidden(i, !shouldShow);
    }
}



void EmployerAdmin::onEditPayment(const QStringList &paymentData)
{
    // Switch to add payment tab
    ui->paymentTabWidget->setCurrentIndex(1);
    
    // Populate form with existing data
    if (paymentData.size() >= 8) {
        // Set type
        QString type = paymentData[3];
        int typeIndex = ui->paymentTypeCombo->findText(type);
        if (typeIndex >= 0) ui->paymentTypeCombo->setCurrentIndex(typeIndex);
        
        // Set date
        QDate date = QDate::fromString(paymentData[1], "yyyy-MM-dd");
        if (date.isValid()) ui->paymentDateEdit->setDate(date);
        
        // Set description
        ui->paymentDescriptionEdit->setText(paymentData[2]);
        
        // Set amount (remove $ symbol)
        QString amountText = paymentData[4];
        amountText.remove("$");
        ui->paymentAmountSpinBox->setValue(amountText.toDouble());
        
        // Set method
        QString method = paymentData[5];
        int methodIndex = ui->paymentMethodCombo->findText(method);
        if (methodIndex >= 0) ui->paymentMethodCombo->setCurrentIndex(methodIndex);
        
        // Set status
        QString status = paymentData[6];
        int statusIndex = ui->paymentStatusCombo->findText(status);
        if (statusIndex >= 0) ui->paymentStatusCombo->setCurrentIndex(statusIndex);
        
        // Set member ID
        ui->paymentMemberEdit->setText(paymentData[7]);
    }
    
    QMessageBox::information(this, "Edit Payment", 
        "Payment data loaded into form. Modify the fields and click 'Add Payment' to update.\n\n"
        "Note: This will create a new entry. You may want to delete the original entry first.");
}

void EmployerAdmin::onDeletePayment(const QStringList &paymentData, int row)
{
    QString transactionId = paymentData[0];
    QString description = paymentData[2];
    
    int result = QMessageBox::question(this, "Confirm Delete",
        QString("Are you sure you want to delete this payment transaction?\n\n"
                "Transaction ID: %1\n"
                "Description: %2").arg(transactionId, description),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    
    if (result == QMessageBox::Yes) {
        ui->paymentTable->removeRow(row);
        populatePaymentStatistics(); // Update statistics after deletion
        QMessageBox::information(this, "Deleted", "Payment transaction deleted successfully!");
    }
}
