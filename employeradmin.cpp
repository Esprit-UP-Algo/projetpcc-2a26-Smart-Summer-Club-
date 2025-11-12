#include "employeradmin.h"
#include "ui_employeradmin.h"
#include <QPixmap>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

EmployerAdmin::EmployerAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmployerAdmin)
    , employeeManager(nullptr)
    , memberManager(nullptr)
    , activityManager(nullptr)
    , equipmentManager(nullptr)
    , paymentManager(nullptr)
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
    
    // Initialize management classes
    employeeManager = new Employee(ui, this);
    memberManager = new Member(ui, this);
    activityManager = new Activity(ui, this);
    equipmentManager = new Equipment(ui, this);
    paymentManager = new Payment(ui, this);
    
    // Setup connections
    setupConnections();
    
    // Setup input field validators
    setupInputValidators();
    
    // Setup tables through management classes
    employeeManager->setupEmployeeTable();
    memberManager->setupMemberTable();
    activityManager->setupActivityTable();
    equipmentManager->setupEquipmentTable();
    equipmentManager->setupEquipmentDetailsTable();
    paymentManager->setupPaymentTable();
    
    // Update payment statistics
    paymentManager->populatePaymentStatistics();

    // Set initial state
    ui->stackedWidget->setCurrentIndex(0); // Show employee page first
    ui->employeeTabWidget->setCurrentIndex(0); // Show list tab first
    
    // Set current date for hire date
    ui->hireDateEdit->setDate(QDate::currentDate());
    
    // Initialize button visibility (hide Update buttons, show Add buttons)
    ui->confirmUpdateButton->setVisible(false);  // Employee Update button hidden by default
    ui->memberConfirmUpdateButton->setVisible(false);  // Member Update button hidden by default
    ui->activityUpdateButton->setVisible(false);  // Activity Update button hidden by default
    
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
    delete employeeManager;
    delete memberManager;
    delete activityManager;
    delete equipmentManager;
    delete paymentManager;
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
    
    // Employee management buttons - delegate to employeeManager
    connect(ui->employeeSearchButton, &QPushButton::clicked, employeeManager, &Employee::onSearchEmployees);
    connect(ui->employeeUploadPhotoButton, &QPushButton::clicked, employeeManager, &Employee::onUploadPhoto);
    connect(ui->confirmAddButton, &QPushButton::clicked, employeeManager, &Employee::onConfirmAdd);
    connect(ui->confirmUpdateButton, &QPushButton::clicked, employeeManager, &Employee::onConfirmUpdate);
    connect(ui->employeeSortButton, &QPushButton::clicked, employeeManager, &Employee::onSortEmployees);
    connect(ui->employeeExportButton, &QPushButton::clicked, employeeManager, &Employee::onExportEmployees);

    // Member management buttons - delegate to memberManager
    connect(ui->memberConfirmAddButton, &QPushButton::clicked, memberManager, &Member::onConfirmAdd);
    connect(ui->memberConfirmUpdateButton, &QPushButton::clicked, memberManager, &Member::onConfirmUpdate);
    connect(ui->memberUploadPhotoButton, &QPushButton::clicked, memberManager, &Member::onUploadPhoto);
    connect(ui->memberSearchLineEdit, &QLineEdit::textChanged, memberManager, &Member::onSearchMembers);
    connect(ui->memberSortButton, &QPushButton::clicked, memberManager, &Member::onSortMembers);
    connect(ui->memberExportButton, &QPushButton::clicked, memberManager, &Member::onExportMembers);

    // Activity management buttons - delegate to activityManager
    connect(ui->activityConfirmButton, &QPushButton::clicked, activityManager, &Activity::onConfirmAdd);
    connect(ui->activityUpdateButton, &QPushButton::clicked, activityManager, &Activity::onConfirmUpdate);
    connect(ui->activitySearchLineEdit, &QLineEdit::textChanged, activityManager, &Activity::onSearchActivities);
    connect(ui->activitySortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), activityManager, &Activity::onSortComboBoxChanged);
    connect(ui->activityExportButton, &QPushButton::clicked, activityManager, &Activity::onExportActivities);
    connect(ui->responsibleToggleButton, &QPushButton::clicked, activityManager, &Activity::onToggleResponsibleInput);

    // Equipment management buttons - delegate to equipmentManager
    connect(ui->equipmentSortButton, &QPushButton::clicked, equipmentManager, &Equipment::onSortEquipment);
    connect(ui->equipmentExportButton, &QPushButton::clicked, equipmentManager, &Equipment::onExportEquipment);
    
    // Payment management buttons - delegate to paymentManager
    connect(ui->addPaymentButton, &QPushButton::clicked, paymentManager, &Payment::onAddPayment);
    connect(ui->clearPaymentFormButton, &QPushButton::clicked, paymentManager, &Payment::onClearPaymentForm);
    connect(ui->paymentSearchLineEdit, &QLineEdit::textChanged, paymentManager, &Payment::onPaymentSearchTextChanged);
}

void EmployerAdmin::onNavigationButtonClicked()
{
    updateNavigationStyle();
}

void EmployerAdmin::setupCostAnalysisChart()
{
    // Create horizontal bar chart for cost analysis
    QHorizontalBarSeries *series = new QHorizontalBarSeries();
    
    // Sample cost data (in percentages)
    QBarSet *equipment = new QBarSet("Equipment");
    QBarSet *staff = new QBarSet("Staff");
    QBarSet *maintenance = new QBarSet("Maintenance");
    QBarSet *utilities = new QBarSet("Utilities");
    
    *equipment << 35;
    *staff << 40;
    *maintenance << 15;
    *utilities << 10;
    
    series->append(equipment);
    series->append(staff);
    series->append(maintenance);
    series->append(utilities);
    
    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Cost Analysis Breakdown");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Customize the chart appearance
    chart->setBackgroundBrush(QBrush(QColor("#f8fbfc")));
    chart->setTitleBrush(QBrush(QColor("#2c3e50")));
    
    // Create category axis
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(QStringList() << "Costs");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    // Create value axis (0-100 for percentages)
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 100);
    axisX->setTitleText("Percentage (%)");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    // Create chart view
    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(400, 250);
    
    // Insert at top of costStatsLayout (above the table)
    if (auto layout = ui->costStatsFrame->layout()) {
        layout->addWidget(view);
    }
}

void EmployerAdmin::setupIcons()
{
    QSize iconSize(24, 24);  // Set consistent icon size
    
    // Set icons for main navigation buttons
    ui->employeesButton->setIcon(QIcon(":/icons/icons/employee.png"));
    ui->employeesButton->setIconSize(iconSize);
    
    ui->membersButton->setIcon(QIcon(":/icons/icons/members.png"));
    ui->membersButton->setIconSize(iconSize);
    
    ui->equipmentButton->setIcon(QIcon(":/icons/icons/equipement.png"));
    ui->equipmentButton->setIconSize(iconSize);
    
    ui->activitiesButton->setIcon(QIcon(":/icons/icons/activity.png"));
    ui->activitiesButton->setIconSize(iconSize);
    
    ui->paymentsButton->setIcon(QIcon(":/icons/icons/payment.png"));
    ui->paymentsButton->setIconSize(iconSize);
    
    // Set icons for action buttons
    ui->employeeSearchButton->setIcon(QIcon(":/icons/icons/search.png"));
    ui->employeeSearchButton->setIconSize(iconSize);
    
    // Setup tab icons
    setupTabIcons();
}

void EmployerAdmin::setupTabIcons()
{
    QSize tabIconSize(20, 20);
    
    // Employee tab widget icons
    ui->employeeTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->employeeTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));
    
    // Member tab widget icons  
    ui->memberTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->memberTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));
    
    // Activity tab widget icons
    ui->activityTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->activityTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));
    
    // Equipment tab widget icons
    ui->equipmentTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->equipmentTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));
    
    // Payment tab widget icons
    ui->paymentTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->paymentTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));
    ui->paymentTabWidget->setTabIcon(2, QIcon(":/icons/icons/statistic.png"));
}

void EmployerAdmin::setupButtonStyling()
{
    QString actionButtonStyle = 
        "QPushButton {"
        "    background-color: rgba(22, 165, 179, 0.10);"
        "    color: #2c3e50;"
        "    border: 1.5px solid rgba(22, 165, 179, 0.65);"
        "    padding: 8px 16px;"
        "    border-radius: 6px;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(22, 165, 179, 0.20);"
        "    border: 1.5px solid #16a5b3;"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(22, 165, 179, 0.30);"
        "}";
    
    // Apply to action buttons
    ui->employeeSearchButton->setStyleSheet(actionButtonStyle);
    ui->employeeUploadPhotoButton->setStyleSheet(actionButtonStyle);
    ui->confirmAddButton->setStyleSheet(actionButtonStyle);
    ui->confirmUpdateButton->setStyleSheet(actionButtonStyle);
    
    // Activity buttons
    ui->activitySearchButton->setStyleSheet(actionButtonStyle);
    ui->activityConfirmButton->setStyleSheet(actionButtonStyle);
    ui->activityUpdateButton->setStyleSheet(actionButtonStyle);
}

void EmployerAdmin::setupInputValidators()
{
    // ============================================================================
    // EMPLOYEE FORM VALIDATORS
    // ============================================================================
    
    // CIN Field (empIdLineEdit) - Only 8 numeric digits (Tunisian CIN format)
    QRegularExpression cinRegex("^[0-9]{0,8}$");
    QRegularExpressionValidator *cinValidator = new QRegularExpressionValidator(cinRegex, this);
    ui->empIdLineEdit->setValidator(cinValidator);
    ui->empIdLineEdit->setMaxLength(8);  // Limit to exactly 8 digits
    
    // Phone Field (phoneLineEdit) - Only 8 numeric digits (Tunisian phone format)
    QRegularExpression phoneRegex("^[0-9]{0,8}$");
    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    ui->phoneLineEdit->setValidator(phoneValidator);
    ui->phoneLineEdit->setMaxLength(8);  // Limit to exactly 8 digits
    
    // Salary Field (salaryLineEdit) - Only positive decimal numbers
    QDoubleValidator *salaryValidator = new QDoubleValidator(0.0, 999999999.99, 2, this);
    salaryValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->salaryLineEdit->setValidator(salaryValidator);
    
    // First Name Field (firstNameLineEdit) - Only letters, spaces, hyphens, apostrophes
    QRegularExpression nameRegex("^[A-Za-zÀ-ÿ\\s\\-']*$");
    QRegularExpressionValidator *firstNameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->firstNameLineEdit->setValidator(firstNameValidator);
    
    // Last Name Field (lastNameLineEdit) - Only letters, spaces, hyphens, apostrophes
    QRegularExpressionValidator *lastNameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->lastNameLineEdit->setValidator(lastNameValidator);
    

    
    // ============================================================================
    // MEMBER FORM VALIDATORS
    // ============================================================================
    
    // Member ID Field (memberIdLineEdit) - Only 8 numeric digits (Tunisian CIN format)
    QRegularExpressionValidator *memberIdValidator = new QRegularExpressionValidator(cinRegex, this);
    ui->memberIdLineEdit->setValidator(memberIdValidator);
    ui->memberIdLineEdit->setMaxLength(8);  // Limit to exactly 8 digits
    
    // Member Phone Field (memberPhoneLineEdit) - Only 8 numeric digits
    QRegularExpressionValidator *memberPhoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    ui->memberPhoneLineEdit->setValidator(memberPhoneValidator);
    ui->memberPhoneLineEdit->setMaxLength(8);  // Limit to exactly 8 digits
    
    // Member First Name Field (memberFirstNameLineEdit) - Only letters, spaces, hyphens, apostrophes
    QRegularExpressionValidator *memberFirstNameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->memberFirstNameLineEdit->setValidator(memberFirstNameValidator);
    
    // Member Last Name Field (memberLastNameLineEdit) - Only letters, spaces, hyphens, apostrophes
    QRegularExpressionValidator *memberLastNameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->memberLastNameLineEdit->setValidator(memberLastNameValidator);
    
    // Member Email Field (memberEmailLineEdit) - Email format validation
    QRegularExpression memberEmailRegex("^[A-Za-z0-9._%+-]*@?[A-Za-z0-9.-]*\\.?[A-Za-z]*$");
    QRegularExpressionValidator *memberEmailValidator = new QRegularExpressionValidator(memberEmailRegex, this);
    ui->memberEmailLineEdit->setValidator(memberEmailValidator);
    
    // ============================================================================
    // EQUIPMENT FORM VALIDATORS
    // ============================================================================
    
    // Equipment Price Field (equipmentPriceLineEdit) - Only positive decimal numbers
    QDoubleValidator *equipmentPriceValidator = new QDoubleValidator(0.0, 999999999.99, 2, this);
    equipmentPriceValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->equipmentPriceLineEdit->setValidator(equipmentPriceValidator);
    
    // Equipment Name Field (equipmentNameLineEdit) - Letters, spaces, numbers, hyphens, apostrophes
    QRegularExpression equipmentNameRegex("^[A-Za-zÀ-ÿ0-9\\s\\-']*$");
    QRegularExpressionValidator *equipmentNameValidator = new QRegularExpressionValidator(equipmentNameRegex, this);
    ui->equipmentNameLineEdit->setValidator(equipmentNameValidator);
    
    // Equipment Brand Field (equipmentBrandLineEdit) - Letters, spaces, numbers, hyphens, apostrophes
    QRegularExpressionValidator *equipmentBrandValidator = new QRegularExpressionValidator(equipmentNameRegex, this);
    ui->equipmentBrandLineEdit->setValidator(equipmentBrandValidator);
    
    // Equipment Model Field (equipmentModelLineEdit) - Letters, spaces, numbers, hyphens, apostrophes
    QRegularExpressionValidator *equipmentModelValidator = new QRegularExpressionValidator(equipmentNameRegex, this);
    ui->equipmentModelLineEdit->setValidator(equipmentModelValidator);
    
    // ============================================================================
    // ACTIVITY FORM VALIDATORS
    // ============================================================================
    
    // Activity Responsible Field (responsibleLineEdit) - Only letters, spaces, hyphens, apostrophes
    QRegularExpressionValidator *responsibleValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->responsibleLineEdit->setValidator(responsibleValidator);
    
    // ============================================================================
    // PAYMENT FORM VALIDATORS
    // ============================================================================
    
    // Payment Member ID Field (paymentMemberEdit) - Only 8 numeric digits (optional field)
    QRegularExpressionValidator *paymentMemberValidator = new QRegularExpressionValidator(cinRegex, this);
    ui->paymentMemberEdit->setValidator(paymentMemberValidator);
    ui->paymentMemberEdit->setMaxLength(8);  // Limit to exactly 8 digits
    
    // ============================================================================
    // TOOLTIPS AND PLACEHOLDERS
    // ============================================================================
    
    // Employee field tooltips
    ui->empIdLineEdit->setToolTip("Enter exactly 8 numeric digits (e.g., 12345678)");
    ui->phoneLineEdit->setToolTip("Enter exactly 8 numeric digits (e.g., 55123456)");
    ui->salaryLineEdit->setToolTip("Enter a positive salary amount (e.g., 1500.50)");
    ui->firstNameLineEdit->setToolTip("Enter first name (letters, spaces, hyphens, apostrophes only)");
    ui->lastNameLineEdit->setToolTip("Enter last name (letters, spaces, hyphens, apostrophes only)");

    
    // Member field tooltips
    ui->memberIdLineEdit->setToolTip("Enter exactly 8 numeric digits (e.g., 12345678)");
    ui->memberPhoneLineEdit->setToolTip("Enter exactly 8 numeric digits (e.g., 55123456)");
    ui->memberFirstNameLineEdit->setToolTip("Enter first name (letters, spaces, hyphens, apostrophes only)");
    ui->memberLastNameLineEdit->setToolTip("Enter last name (letters, spaces, hyphens, apostrophes only)");
    ui->memberEmailLineEdit->setToolTip("Enter valid email address (e.g., member@example.com)");
    
    // Equipment field tooltips
    ui->equipmentPriceLineEdit->setToolTip("Enter a positive price amount (e.g., 299.99)");
    ui->equipmentNameLineEdit->setToolTip("Enter equipment name (letters, numbers, spaces, hyphens, apostrophes)");
    ui->equipmentBrandLineEdit->setToolTip("Enter equipment brand (letters, numbers, spaces, hyphens, apostrophes)");
    ui->equipmentModelLineEdit->setToolTip("Enter equipment model (letters, numbers, spaces, hyphens, apostrophes)");
    
    // Activity field tooltips
    ui->responsibleLineEdit->setToolTip("Enter responsible employee name (letters, spaces, hyphens, apostrophes only)");
    
    // Payment field tooltips
    ui->paymentMemberEdit->setToolTip("Enter member ID if applicable (exactly 8 numeric digits)");
    
    // Employee field placeholders
    ui->empIdLineEdit->setPlaceholderText("12345678 (8 digits)");
    ui->phoneLineEdit->setPlaceholderText("55123456 (8 digits)");
    ui->salaryLineEdit->setPlaceholderText("1500.50");
    
    // Member field placeholders
    ui->memberIdLineEdit->setPlaceholderText("12345678 (8 digits)");
    ui->memberPhoneLineEdit->setPlaceholderText("55123456 (8 digits)");
    ui->memberEmailLineEdit->setPlaceholderText("member@example.com");
    
    // Equipment field placeholders
    ui->equipmentPriceLineEdit->setPlaceholderText("299.99");
    
    // Payment field placeholders
    ui->paymentMemberEdit->setPlaceholderText("12345678 (optional)");
}

void EmployerAdmin::updateNavigationStyle()
{
    // This function can be used to update navigation styling if needed
    // Currently, the styling is handled by setupButtonStyling()
}