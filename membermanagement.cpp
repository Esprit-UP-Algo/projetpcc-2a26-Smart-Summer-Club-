#include "membermanagement.h"
#include "ui_membermanagement.h"
#include <QPixmap>
MemberManagement::MemberManagement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MemberManagement)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/khali/OneDrive/Desktop/projetpcc-2a26-vibraclub-integration/assests/VibraClubLogo.png");
    ui->logo->setPixmap(pix.scaled(50, 50, Qt::KeepAspectRatio));
    
    // Setup navigation button group
    navigationButtonGroup = new QButtonGroup(this);
    navigationButtonGroup->addButton(ui->membersButton, 0);      // Members
    
    // Setup connections
    setupConnections();
    
    // Setup tables
    setupMemberTable();
    
    // Populate with sample data
    populateMemberTable();
    
    // Setup and populate member statistics
    populateMemberStatistics();

    // Set initial state
    ui->stackedWidget->setCurrentIndex(0); // Show members page first
    
    // Setup icons (optional - won't break anything if icons don't exist)
    setupIcons();
    
    // Apply button styling
    setupButtonStyling();
}





MemberManagement::~MemberManagement()
{
    delete ui;
}

void MemberManagement::setupConnections()
{
    // Navigation buttons
    connect(navigationButtonGroup, &QButtonGroup::idClicked,
            this, [this](int id) {
                ui->stackedWidget->setCurrentIndex(id);
                updateNavigationStyle();
            });
    
    // Connect member management buttons if needed
    // (Member-specific connections can be added here)
}





void MemberManagement::onNavigationButtonClicked()
{
    updateNavigationStyle();
}

void MemberManagement::setupIcons()
{
    QSize iconSize(24, 24);  // Set consistent icon size
    
    // Debug: Test icon loading
    qDebug() << "Testing icon loading with updated icon names...";
    qDebug() << "Application directory:" << QApplication::applicationDirPath();
    
    // Set icons for navigation buttons with new names
    if (!QIcon(":/icons/icons/members.png").isNull()) {
        ui->membersButton->setIcon(QIcon(":/icons/icons/members.png"));
        ui->membersButton->setIconSize(iconSize);
        qDebug() << "Members icon loaded from resources";
    }
    
    // Set icons for action buttons with new names
    QSize actionIconSize(16, 16);  // Smaller icons for action buttons
    
    // Search buttons
    if (!QIcon(":/icons/icons/search.png").isNull()) {
        ui->memberSearchButton->setIcon(QIcon(":/icons/icons/search.png"));
        ui->memberSearchButton->setIconSize(actionIconSize);
        qDebug() << "Search icons loaded from resources";
    }
    
    // Add/Confirm buttons
    if (!QIcon(":/icons/icons/add.png").isNull()) {
        ui->memberConfirmAddButton->setIcon(QIcon(":/icons/icons/add.png"));
        ui->memberConfirmAddButton->setIconSize(actionIconSize);
        qDebug() << "Add icons loaded from resources";
    }
    
    // Update buttons
    if (!QIcon(":/icons/icons/edit.png").isNull()) {
        ui->memberConfirmUpdateButton->setIcon(QIcon(":/icons/icons/edit.png"));
        ui->memberConfirmUpdateButton->setIconSize(actionIconSize);
        qDebug() << "Edit icons loaded from resources";
    }
    
    // Upload buttons
    if (!QIcon(":/icons/icons/add.png").isNull()) {
        ui->memberUploadPhotoButton->setIcon(QIcon(":/icons/icons/add.png"));
        ui->memberUploadPhotoButton->setIconSize(actionIconSize);
        qDebug() << "Upload icons loaded from resources";
    }
    
    // Set icons for tab widgets programmatically (as backup to UI file settings)
    setupTabIcons();
    
    qDebug() << "Icon setup completed for all buttons and tabs with updated icon names.";
}

void MemberManagement::setupTabIcons()
{
    QSize tabIconSize(16, 16);
    
    // Member tab icons
    ui->memberTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));      // List tab
    ui->memberTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));       // Add tab
    ui->memberTabWidget->setTabIcon(2, QIcon(":/icons/icons/statistic.png")); // Statistics tab
    
    qDebug() << "Tab icons set programmatically for member tab widget";
}

void MemberManagement::setupButtonStyling()
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
    ui->membersButton->setStyleSheet(navButtonStyle);
    
    // Set buttons as checkable so they can show selected state
    ui->membersButton->setCheckable(true);
    
    // Make sure only one button can be checked at a time (handled by QButtonGroup)
    navigationButtonGroup->setExclusive(true);
    
    // Set the first button as initially selected
    ui->membersButton->setChecked(true);
    
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
    ui->memberSearchButton->setStyleSheet(actionButtonStyle);
    ui->memberUploadPhotoButton->setStyleSheet(actionButtonStyle);
    ui->memberConfirmAddButton->setStyleSheet(actionButtonStyle);
    ui->memberConfirmUpdateButton->setStyleSheet(actionButtonStyle);
}

void MemberManagement::updateNavigationStyle()
{
    // This function can be used to update navigation styling if needed
    // Currently, the styling is handled by setupButtonStyling()
}

void MemberManagement::setupMemberTable()
{
    // Set column count and headers
    ui->memberTable->setColumnCount(7);
    QStringList headers = {"ID", "Name", "Membership Type", "Plan", "Join Date", "Status", "Actions"};
    ui->memberTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->memberTable->setColumnWidth(0, 80);   // ID
    ui->memberTable->setColumnWidth(1, 150);  // Name
    ui->memberTable->setColumnWidth(2, 130);  // Membership Type
    ui->memberTable->setColumnWidth(3, 100);  // Plan
    ui->memberTable->setColumnWidth(4, 100);  // Join Date
    ui->memberTable->setColumnWidth(5, 80);   // Status
    ui->memberTable->setColumnWidth(6, 120);  // Actions
    
    // Set table properties
    ui->memberTable->setAlternatingRowColors(true);
    ui->memberTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->memberTable->setSortingEnabled(true);
}

void MemberManagement::populateMemberTable()
{
    // Sample member data
    QStringList members[] = {
        {"MEM001", "John Smith", "Premium", "Annual", "2024-01-15", "Active"},
        {"MEM002", "Sarah Johnson", "Basic", "Monthly", "2024-02-20", "Active"},
        {"MEM003", "Mike Wilson", "VIP", "Annual", "2024-01-05", "Active"},
        {"MEM004", "Emily Davis", "Student", "Semester", "2024-03-10", "Active"},
        {"MEM005", "Robert Brown", "Premium", "Quarterly", "2024-02-01", "Inactive"},
        {"MEM006", "Lisa Garcia", "Basic", "Monthly", "2024-03-15", "Active"},
        {"MEM007", "David Martinez", "Senior", "Annual", "2024-01-20", "Active"},
        {"MEM008", "Jennifer Taylor", "VIP", "Monthly", "2024-02-28", "Active"},
        {"MEM009", "Michael Anderson", "Premium", "Annual", "2024-01-08", "Suspended"},
        {"MEM010", "Amanda White", "Basic", "Monthly", "2024-03-05", "Active"},
        {"MEM011", "Christopher Lee", "Student", "Semester", "2024-02-12", "Active"},
        {"MEM012", "Jessica Moore", "Premium", "Quarterly", "2024-01-25", "Expired"}
    };
    
    int numMembers = sizeof(members) / sizeof(members[0]);
    ui->memberTable->setRowCount(numMembers);
    
    for (int i = 0; i < numMembers; ++i) {
        for (int j = 0; j < 6; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(members[i][j]);
            
            // Color code status column
            if (j == 5) { // Status column
                if (members[i][j] == "Active") {
                    item->setBackground(QColor(46, 204, 113, 50)); // Green
                    item->setForeground(QColor(39, 174, 96));
                } else if (members[i][j] == "Inactive") {
                    item->setBackground(QColor(241, 196, 15, 50)); // Yellow
                    item->setForeground(QColor(243, 156, 18));
                } else if (members[i][j] == "Suspended") {
                    item->setBackground(QColor(231, 76, 60, 50)); // Red
                    item->setForeground(QColor(192, 57, 43));
                } else if (members[i][j] == "Expired") {
                    item->setBackground(QColor(149, 165, 166, 50)); // Gray
                    item->setForeground(QColor(127, 140, 141));
                }
            }
            
            ui->memberTable->setItem(i, j, item);
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
            onEditMember(i);
        });
        connect(deleteBtn, &QPushButton::clicked, [this, i]() {
            onDeleteMember(i);
        });
        
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->addWidget(editBtn);
        actionLayout->addWidget(deleteBtn);
        actionLayout->setContentsMargins(5, 0, 5, 0);
        actionLayout->setSpacing(5);
        
        ui->memberTable->setCellWidget(i, 6, actionWidget);
    }
}

void MemberManagement::setupMemberStatisticsTable()
{
    // Set column count and headers for membership statistics table
    ui->membershipStatsTable->setColumnCount(3);
    QStringList headers = {"Membership Type", "Member Count", "Percentage"};
    ui->membershipStatsTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->membershipStatsTable->setColumnWidth(0, 150);  // Membership Type
    ui->membershipStatsTable->setColumnWidth(1, 120);  // Member Count
    ui->membershipStatsTable->setColumnWidth(2, 100);  // Percentage
    
    // Set table properties
    ui->membershipStatsTable->setAlternatingRowColors(true);
    ui->membershipStatsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->membershipStatsTable->setSortingEnabled(true);
    ui->membershipStatsTable->setRowCount(6);
}

void MemberManagement::populateMemberStatistics()
{
    // Sample membership type statistics
    QStringList membershipTypes[] = {
        {"Premium", "18", "38.3%"},
        {"Basic", "15", "31.9%"},
        {"VIP", "8", "17.0%"},
        {"Student", "4", "8.5%"},
        {"Senior", "2", "4.3%"}
    };
    
    setupMemberStatisticsTable();
    
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(membershipTypes[i][j]);
            
            // Color code based on membership type
            if (j == 0) { // Membership Type column
                if (membershipTypes[i][j] == "Premium") {
                    item->setBackground(QColor(22, 165, 179, 50));  // Teal
                    item->setForeground(QColor(22, 165, 179));
                } else if (membershipTypes[i][j] == "VIP") {
                    item->setBackground(QColor(155, 89, 182, 50));  // Purple
                    item->setForeground(QColor(142, 68, 173));
                } else if (membershipTypes[i][j] == "Basic") {
                    item->setBackground(QColor(52, 152, 219, 50));  // Blue
                    item->setForeground(QColor(41, 128, 185));
                } else if (membershipTypes[i][j] == "Student") {
                    item->setBackground(QColor(241, 196, 15, 50));  // Yellow
                    item->setForeground(QColor(243, 156, 18));
                } else if (membershipTypes[i][j] == "Senior") {
                    item->setBackground(QColor(230, 126, 34, 50));  // Orange
                    item->setForeground(QColor(211, 84, 0));
                }
            }
            
            ui->membershipStatsTable->setItem(i, j, item);
        }
    }
}

void MemberManagement::onEditMember(int row)
{
    // Get member data from the selected row
    QString memberId = ui->memberTable->item(row, 0)->text();
    QString memberName = ui->memberTable->item(row, 1)->text();
    QString membershipType = ui->memberTable->item(row, 2)->text();
    QString plan = ui->memberTable->item(row, 3)->text();
    QString joinDate = ui->memberTable->item(row, 4)->text();
    QString status = ui->memberTable->item(row, 5)->text();
    
    // Switch to the Add Member tab for editing
    ui->memberTabWidget->setCurrentIndex(1);
    
    // Populate the form with existing data
    ui->memberIdLineEdit->setText(memberId);
    
    // Split name into first and last name (simple approach)
    QStringList nameParts = memberName.split(" ");
    if (nameParts.size() >= 2) {
        ui->memberFirstNameLineEdit->setText(nameParts[0]);
        ui->memberLastNameLineEdit->setText(nameParts.last());
    } else {
        ui->memberFirstNameLineEdit->setText(memberName);
        ui->memberLastNameLineEdit->clear();
    }
    
    // Set membership type
    int typeIndex = ui->membershipTypeComboBox->findText(membershipType);
    if (typeIndex >= 0) {
        ui->membershipTypeComboBox->setCurrentIndex(typeIndex);
    }
    
    ui->membershipPlanLineEdit->setText(plan);
    
    // Set join date
    QDate date = QDate::fromString(joinDate, "yyyy-MM-dd");
    if (date.isValid()) {
        ui->memberJoinDateEdit->setDate(date);
    }
    
    // Set status
    int statusIndex = ui->memberStatusComboBox->findText(status);
    if (statusIndex >= 0) {
        ui->memberStatusComboBox->setCurrentIndex(statusIndex);
    }
    
    QMessageBox::information(this, "Edit Member", 
                           QString("Editing member: %1\nID: %2").arg(memberName, memberId));
}

void MemberManagement::onDeleteMember(int row)
{
    QString memberId = ui->memberTable->item(row, 0)->text();
    QString memberName = ui->memberTable->item(row, 1)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Member",
                                                             QString("Are you sure you want to delete member:\n%1 (ID: %2)?")
                                                             .arg(memberName, memberId),
                                                             QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        ui->memberTable->removeRow(row);
        QMessageBox::information(this, "Member Deleted", 
                               QString("Member %1 has been deleted successfully.").arg(memberName));
        
        // Update statistics after deletion
        populateMemberStatistics();
    }
}


