#include "activitymanagement.h"
#include "ui_activitymanagement.h"
#include <QPixmap>

ActivityManagement::ActivityManagement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ActivityManagement)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/khali/OneDrive/Desktop/projetpcc-2a26-vibraclub-integration/assests/VibraClubLogo.png");
    ui->logo->setPixmap(pix.scaled(50, 50, Qt::KeepAspectRatio));
    
    // Setup connections for activity management
    setupConnections();
    
    // Setup activity table
    setupActivityTable();
    
    // Populate with sample activity data
    populateActivityTable();
    populateActivityStatistics();

    // Set initial state - activities page only
    ui->stackedWidget->setCurrentIndex(0); // Show activities page
    ui->activityTabWidget->setCurrentIndex(0); // Show list tab first
    
    // Set current date for event date
    ui->eventDateEdit->setDate(QDate::currentDate());
    
    // Setup icons
    setupIcons();
}

ActivityManagement::~ActivityManagement()
{
    delete ui;
}

void ActivityManagement::setupConnections()
{
    // Activity management buttons
    connect(ui->activitySearchButton, &QPushButton::clicked, this, &ActivityManagement::onSearchActivities);
    connect(ui->activityConfirmButton, &QPushButton::clicked, this, &ActivityManagement::onConfirmAddActivity);
    connect(ui->activityUpdateButton, &QPushButton::clicked, this, &ActivityManagement::onConfirmUpdateActivity);
}

void ActivityManagement::setupActivityTable()
{
    ui->activityTable->setColumnWidth(0, 80);   // Activity ID
    ui->activityTable->setColumnWidth(1, 150);  // Activity Name
    ui->activityTable->setColumnWidth(2, 120);  // Type
    ui->activityTable->setColumnWidth(3, 100);  // Event Date
    ui->activityTable->setColumnWidth(4, 80);   // Time
    ui->activityTable->setColumnWidth(5, 120);  // Responsible
    ui->activityTable->setColumnWidth(6, 80);   // Status
    ui->activityTable->setColumnWidth(7, 120);  // Actions
    
    // Make table read-only
    ui->activityTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ActivityManagement::setupActivityStatisticsTable()
{
    ui->activityTypeStatsTable->setRowCount(6);
    ui->activityTypeStatsTable->setColumnWidth(0, 150);  // Activity Type
    ui->activityTypeStatsTable->setColumnWidth(1, 80);   // Count
    ui->activityTypeStatsTable->setColumnWidth(2, 100);  // Percentage
    ui->activityTypeStatsTable->setColumnWidth(3, 100);  // This Month
    
    // Make table read-only
    ui->activityTypeStatsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ActivityManagement::populateActivityTable()
{
    // Sample activity data
    QStringList activities[] = {
        {"ACT001", "Morning Yoga", "Group Class", "2024-10-05", "08:00", "Sarah Wilson", "Scheduled"},
        {"ACT002", "Personal Training", "Personal Training", "2024-10-05", "10:30", "Mike Johnson", "In Progress"},
        {"ACT003", "Swimming Workshop", "Workshop", "2024-10-06", "14:00", "Lisa Garcia", "Scheduled"},
        {"ACT004", "Fitness Competition", "Competition", "2024-10-07", "16:00", "Tom Anderson", "Scheduled"},
        {"ACT005", "Equipment Maintenance", "Maintenance", "2024-10-05", "09:00", "David Brown", "Completed"},
        {"ACT006", "Dance Class", "Group Class", "2024-10-05", "18:00", "Emma Davis", "Scheduled"},
        {"ACT007", "Nutrition Seminar", "Event", "2024-10-08", "11:00", "John Doe", "Scheduled"},
        {"ACT008", "Advanced Training", "Personal Training", "2024-10-05", "15:30", "Jane Smith", "In Progress"}
    };
    
    int numActivities = sizeof(activities) / sizeof(activities[0]);
    ui->activityTable->setRowCount(numActivities);
    
    for (int i = 0; i < numActivities; ++i) {
        for (int j = 0; j < 7; ++j) {
            ui->activityTable->setItem(i, j, new QTableWidgetItem(activities[i][j]));
        }
        
        // Add action buttons
        QPushButton *editBtn = new QPushButton("Edit");
        QPushButton *deleteBtn = new QPushButton("Delete");
        
        // Set icons for action buttons
        editBtn->setIcon(QIcon(":/icons/icons/edit.png"));
        editBtn->setIconSize(QSize(16, 16));
        deleteBtn->setIcon(QIcon(":/icons/icons/delete.png"));
        deleteBtn->setIconSize(QSize(16, 16));
        
        // Style the buttons
        editBtn->setStyleSheet("QPushButton { background-color: #f39c12; color: white; border: none; padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
        deleteBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");
        
        // Connect button signals
        connect(editBtn, &QPushButton::clicked, [this, i]() {
            onEditActivity(i);
        });
        connect(deleteBtn, &QPushButton::clicked, [this, i]() {
            onDeleteActivity(i);
        });
        
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->addWidget(editBtn);
        actionLayout->addWidget(deleteBtn);
        actionLayout->setContentsMargins(5, 0, 5, 0);
        actionLayout->setSpacing(5);
        
        ui->activityTable->setCellWidget(i, 7, actionWidget);
    }
}

void ActivityManagement::populateActivityStatistics()
{
    // Sample activity type statistics
    QStringList activityTypes[] = {
        {"Group Class", "45", "35.4%", "12"},
        {"Personal Training", "32", "25.2%", "8"},
        {"Workshop", "20", "15.7%", "5"},
        {"Competition", "15", "11.8%", "3"},
        {"Event", "10", "7.9%", "2"},
        {"Maintenance", "5", "3.9%", "1"}
    };
    
    setupActivityStatisticsTable();
    
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            ui->activityTypeStatsTable->setItem(i, j, new QTableWidgetItem(activityTypes[i][j]));
        }
    }
}

void ActivityManagement::onSearchActivities()
{
    QString searchTerm = ui->activitySearchLineEdit->text().toLower();
    
    for (int i = 0; i < ui->activityTable->rowCount(); ++i) {
        bool showRow = false;
        
        // Search in all columns except actions
        for (int j = 0; j < 7; ++j) {
            QTableWidgetItem *item = ui->activityTable->item(i, j);
            if (item && item->text().toLower().contains(searchTerm)) {
                showRow = true;
                break;
            }
        }
        
        ui->activityTable->setRowHidden(i, !showRow);
    }
    
    if (searchTerm.isEmpty()) {
        // Show all rows if search is empty
        for (int i = 0; i < ui->activityTable->rowCount(); ++i) {
            ui->activityTable->setRowHidden(i, false);
        }
    }
}

void ActivityManagement::onConfirmAddActivity()
{
    // Validate required fields
    if (ui->activityIdLineEdit->text().isEmpty() || 
        ui->responsibleLineEdit->text().isEmpty()) {
        
        QMessageBox::warning(this, "Validation Error", "Please fill in all required fields:\n- Activity ID\n- Responsible Person");
        return;
    }
    
    // Show confirmation message
    QMessageBox::information(this, "Activity Added", 
        QString("Activity %1 has been successfully added to the system!")
        .arg(ui->activityIdLineEdit->text()));
    
    // Clear form and refresh table
    clearActivityForm();
    populateActivityTable(); // In a real application, this would add the new activity to the table
}

void ActivityManagement::onConfirmUpdateActivity()
{
    // Validate required fields
    if (ui->activityIdLineEdit->text().isEmpty() || 
        ui->responsibleLineEdit->text().isEmpty()) {
        
        QMessageBox::warning(this, "Validation Error", "Please fill in all required fields:\n- Activity ID\n- Responsible Person");
        return;
    }
    
    // Show confirmation message
    QMessageBox::information(this, "Activity Updated", 
        QString("Activity %1 information has been successfully updated!")
        .arg(ui->activityIdLineEdit->text()));
    
    // Clear form and refresh table
    clearActivityForm();
    populateActivityTable(); // In a real application, this would update the activity in the table
}

void ActivityManagement::clearActivityForm()
{
    ui->activityIdLineEdit->clear();
    ui->responsibleLineEdit->clear();
    ui->activityDescriptionTextEdit->clear();
    
    ui->activityTypeComboBox->setCurrentIndex(0);
    ui->activityStatusComboBox->setCurrentIndex(0);
    ui->eventDateEdit->setDate(QDate::currentDate());
    ui->eventTimeEdit->setTime(QTime::currentTime());
}

void ActivityManagement::setupIcons()
{
    QSize iconSize(24, 24);  // Set consistent icon size
    
    // Debug: Test icon loading
    qDebug() << "Testing icon loading...";
    qDebug() << "Application directory:" << QApplication::applicationDirPath();
    
    // Set icons for action buttons
    QSize actionIconSize(16, 16);  // Smaller icons for action buttons
    
    // Search buttons
    if (!QIcon(":/icons/icons/search.png").isNull()) {
        ui->activitySearchButton->setIcon(QIcon(":/icons/icons/search.png"));
        ui->activitySearchButton->setIconSize(actionIconSize);
        qDebug() << "Search icons loaded from resources";
    }
    
    // Add/Confirm buttons
    if (!QIcon(":/icons/icons/add.png").isNull()) {
        ui->activityConfirmButton->setIcon(QIcon(":/icons/icons/add.png"));
        ui->activityConfirmButton->setIconSize(actionIconSize);
        qDebug() << "Add icons loaded from resources";
    }
    
    // Update buttons
    if (!QIcon(":/icons/icons/edit.png").isNull()) {
        ui->activityUpdateButton->setIcon(QIcon(":/icons/icons/edit.png"));
        ui->activityUpdateButton->setIconSize(actionIconSize);
        qDebug() << "Edit icons loaded from resources";
    }
    
    // Set icons for tab widgets programmatically
    setupTabIcons();
    
    qDebug() << "Icon setup completed for activity management buttons and tabs.";
}

void ActivityManagement::setupTabIcons()
{
    QSize tabIconSize(16, 16);
    
    // Activity tab icons
    ui->activityTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));      // List tab
    ui->activityTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));       // Add tab
    ui->activityTabWidget->setTabIcon(2, QIcon(":/icons/icons/statistic.png")); // Statistics tab
    
    qDebug() << "Tab icons set programmatically for activity tab widget";
}

void ActivityManagement::onEditActivity(int row)
{
    // Get activity data from the selected row
    QString id = ui->activityTable->item(row, 0)->text();
    QString name = ui->activityTable->item(row, 1)->text();
    QString type = ui->activityTable->item(row, 2)->text();
    QString date = ui->activityTable->item(row, 3)->text();
    QString time = ui->activityTable->item(row, 4)->text();
    QString responsible = ui->activityTable->item(row, 5)->text();
    QString status = ui->activityTable->item(row, 6)->text();
    
    // Switch to Add Activity tab and populate form with existing data
    ui->activityTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    // Populate the form fields with selected activity data
    ui->activityIdLineEdit->setText(id);
    ui->responsibleLineEdit->setText(responsible);
    
    // Set combo box values
    int typeIndex = ui->activityTypeComboBox->findText(type);
    if (typeIndex >= 0) ui->activityTypeComboBox->setCurrentIndex(typeIndex);
    
    int statusIndex = ui->activityStatusComboBox->findText(status);
    if (statusIndex >= 0) ui->activityStatusComboBox->setCurrentIndex(statusIndex);
    
    // Set date and time
    ui->eventDateEdit->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    ui->eventTimeEdit->setTime(QTime::fromString(time, "hh:mm"));
    
    QMessageBox::information(this, "Edit Activity", 
        QString("Editing activity: %1\nID: %2\nType: %3").arg(name, id, type));
}

void ActivityManagement::onDeleteActivity(int row)
{
    // Get activity data from the selected row
    QString id = ui->activityTable->item(row, 0)->text();
    QString name = ui->activityTable->item(row, 1)->text();
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Delete Activity", 
        QString("Are you sure you want to delete activity:\n%1 (ID: %2)?").arg(name, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->activityTable->removeRow(row);
        
        QMessageBox::information(this, "Activity Deleted", 
            QString("Activity %1 has been deleted successfully.").arg(name));
    }
}
