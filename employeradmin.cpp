// employeradmin.cpp
#include "employeradmin.h"
#include "ui_employeradmin.h"
#include <QPixmap>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QButtonGroup>
#include <QChart>
#include <QHorizontalBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QPainter>

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
    navigationButtonGroup->addButton(ui->employeesButton, 0); // Employees
    navigationButtonGroup->addButton(ui->membersButton, 1);   // Members
    navigationButtonGroup->addButton(ui->equipmentButton, 2); // Equipment
    navigationButtonGroup->addButton(ui->activitiesButton, 3); // Activities
    navigationButtonGroup->addButton(ui->paymentsButton, 4);   // Payments

    // Initialize management classes
    employeeManager = new Employee(ui, this);
    memberManager   = new Member(ui, this);
    activityManager = new Activity(ui, this);
    equipmentManager = new Equipment(ui, this);
    paymentManager  = new Payment(ui, this);

    // Setup connections
    setupConnections();

    // Setup input field validators
    setupInputValidators();

    // Setup tables through management classes
    employeeManager->setupEmployeeTable();
    memberManager->setupMemberTable();
    activityManager->setupActivityTable();
    equipmentManager->setupEquipmentTable();
    // equipmentManager->setupEquipmentDetailsTable();  <-- REMOVED: Already called in Equipment constructor
    paymentManager->setupPaymentTable();

    // Update payment statistics
    paymentManager->populatePaymentStatistics();

    // Set initial state
    ui->stackedWidget->setCurrentIndex(0); // Show employee page first
    ui->employeeTabWidget->setCurrentIndex(0); // Show list tab first

    // Set current date for hire date
    ui->hireDateEdit->setDate(QDate::currentDate());

    // Initialize button visibility (hide Update buttons, show Add buttons)
    ui->confirmUpdateButton->setVisible(false);         // Employee Update
    ui->memberConfirmUpdateButton->setVisible(false);   // Member Update
    ui->activityUpdateButton->setVisible(false);        // Activity Update

    // Enable sorting on list tables
    ui->employeeTable->setSortingEnabled(true);
    ui->memberTable->setSortingEnabled(true);
    ui->activityTable->setSortingEnabled(true);
    ui->equipmentTable->setSortingEnabled(true);

    // Setup icons
    setupIcons();

    // Build advanced Cost Analysis chart
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

    // Employee management buttons
    connect(ui->employeeSearchButton, &QPushButton::clicked, employeeManager, &Employee::onSearchEmployees);
    connect(ui->employeeUploadPhotoButton, &QPushButton::clicked, employeeManager, &Employee::onUploadPhoto);
    connect(ui->confirmAddButton, &QPushButton::clicked, employeeManager, &Employee::onConfirmAdd);
    connect(ui->confirmUpdateButton, &QPushButton::clicked, employeeManager, &Employee::onConfirmUpdate);
    connect(ui->employeeSortButton, &QPushButton::clicked, employeeManager, &Employee::onSortEmployees);
    connect(ui->employeeExportButton, &QPushButton::clicked, employeeManager, &Employee::onExportEmployees);

    // Member management buttons
    connect(ui->memberConfirmAddButton, &QPushButton::clicked, memberManager, &Member::onConfirmAdd);
    connect(ui->memberConfirmUpdateButton, &QPushButton::clicked, memberManager, &Member::onConfirmUpdate);
    connect(ui->memberUploadPhotoButton, &QPushButton::clicked, memberManager, &Member::onUploadPhoto);
    connect(ui->memberSearchLineEdit, &QLineEdit::textChanged, memberManager, &Member::onSearchMembers);
    connect(ui->memberSortButton, &QPushButton::clicked, memberManager, &Member::onSortMembers);
    connect(ui->memberExportButton, &QPushButton::clicked, memberManager, &Member::onExportMembers);

    // Activity management buttons
    connect(ui->activityConfirmButton, &QPushButton::clicked, activityManager, &Activity::onConfirmAdd);
    connect(ui->activityUpdateButton, &QPushButton::clicked, activityManager, &Activity::onConfirmUpdate);
    connect(ui->activitySearchLineEdit, &QLineEdit::textChanged, activityManager, &Activity::onSearchActivities);
    connect(ui->activitySortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            activityManager, &Activity::onSortComboBoxChanged);
    connect(ui->activityExportButton, &QPushButton::clicked, activityManager, &Activity::onExportActivities);
    connect(ui->responsibleToggleButton, &QPushButton::clicked, activityManager, &Activity::onToggleResponsibleInput);

    // Equipment management buttons
    connect(ui->equipmentSortButton, &QPushButton::clicked, equipmentManager, &Equipment::onSortEquipment);
    connect(ui->equipmentExportButton, &QPushButton::clicked, equipmentManager, &Equipment::onExportEquipment);

    // Payment management buttons
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
    QHorizontalBarSeries *series = new QHorizontalBarSeries();

    QBarSet *equipment = new QBarSet("Equipment");
    QBarSet *staff     = new QBarSet("Staff");
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

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Cost Analysis Breakdown");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor("#f8fbfc")));
    chart->setTitleBrush(QBrush(QColor("#2c3e50")));

    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(QStringList() << "Costs");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 100);
    axisX->setTitleText("Percentage (%)");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(400, 250);

    if (auto layout = ui->costStatsFrame->layout()) {
        layout->addWidget(view);
    }
}

void EmployerAdmin::setupIcons()
{
    QSize iconSize(24, 24);

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

    ui->employeeSearchButton->setIcon(QIcon(":/icons/icons/search.png"));
    ui->employeeSearchButton->setIconSize(iconSize);

    setupTabIcons();
}

void EmployerAdmin::setupTabIcons()
{
    ui->employeeTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->employeeTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));

    ui->memberTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->memberTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));

    ui->activityTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->activityTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));

    ui->equipmentTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->equipmentTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));

    ui->paymentTabWidget->setTabIcon(0, QIcon(":/icons/icons/list.png"));
    ui->paymentTabWidget->setTabIcon(1, QIcon(":/icons/icons/add.png"));
    ui->paymentTabWidget->setTabIcon(2, QIcon(":/icons/icons/statistic.png"));
}

void EmployerAdmin::setupButtonStyling()
{
    QString actionButtonStyle =
        "QPushButton {"
        " background-color: rgba(22, 165, 179, 0.10);"
        " color: #2c3e50;"
        " border: 1.5px solid rgba(22, 165, 179, 0.65);"
        " padding: 8px 16px;"
        " border-radius: 6px;"
        " font-size: 14px;"
        " font-weight: 500;"
        "}"
        "QPushButton:hover {"
        " background-color: rgba(22, 165, 179, 0.20);"
        " border: 1.5px solid #16a5b3;"
        "}"
        "QPushButton:pressed {"
        " background-color: rgba(22, 165, 179, 0.30);"
        "}";

    ui->employeeSearchButton->setStyleSheet(actionButtonStyle);
    ui->employeeUploadPhotoButton->setStyleSheet(actionButtonStyle);
    ui->confirmAddButton->setStyleSheet(actionButtonStyle);
    ui->confirmUpdateButton->setStyleSheet(actionButtonStyle);

    ui->activitySearchButton->setStyleSheet(actionButtonStyle);
    ui->activityConfirmButton->setStyleSheet(actionButtonStyle);
    ui->activityUpdateButton->setStyleSheet(actionButtonStyle);
}

void EmployerAdmin::setupInputValidators()
{
    QRegularExpression cinRegex("^[0-9]{0,8}$");
    QRegularExpression phoneRegex("^[0-9]{0,8}$");
    QRegularExpression nameRegex("^[A-Za-zÀ-ÿ\\s\\-']*$");
    QRegularExpression equipmentNameRegex("^[A-Za-zÀ-ÿ0-9\\s\\-']*$");

    // EMPLOYEE VALIDATORS
    QRegularExpressionValidator *cinValidator = new QRegularExpressionValidator(cinRegex, this);
    ui->empIdLineEdit->setValidator(cinValidator);
    ui->empIdLineEdit->setMaxLength(8);

    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    ui->phoneLineEdit->setValidator(phoneValidator);
    ui->phoneLineEdit->setMaxLength(8);

    QDoubleValidator *salaryValidator = new QDoubleValidator(0.0, 999999999.99, 2, this);
    salaryValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->salaryLineEdit->setValidator(salaryValidator);

    QRegularExpressionValidator *firstNameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->firstNameLineEdit->setValidator(firstNameValidator);

    QRegularExpressionValidator *lastNameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->lastNameLineEdit->setValidator(lastNameValidator);

    // MEMBER VALIDATORS
    QRegularExpressionValidator *memberIdValidator = new QRegularExpressionValidator(cinRegex, this);
    ui->memberIdLineEdit->setValidator(memberIdValidator);
    ui->memberIdLineEdit->setMaxLength(8);

    QRegularExpressionValidator *memberPhoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    ui->memberPhoneLineEdit->setValidator(memberPhoneValidator);
    ui->memberPhoneLineEdit->setMaxLength(8);

    QRegularExpressionValidator *memberFirstNameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->memberFirstNameLineEdit->setValidator(memberFirstNameValidator);

    QRegularExpressionValidator *memberLastNameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->memberLastNameLineEdit->setValidator(memberLastNameValidator);

    QRegularExpression memberEmailRegex("^[A-Za-z0-9._%+-]*@?[A-Za-z0-9.-]*\\.?[A-Za-z]*$");
    QRegularExpressionValidator *memberEmailValidator = new QRegularExpressionValidator(memberEmailRegex, this);
    ui->memberEmailLineEdit->setValidator(memberEmailValidator);

    // EQUIPMENT VALIDATORS
    QDoubleValidator *equipmentPriceValidator = new QDoubleValidator(0.0, 999999999.99, 2, this);
    equipmentPriceValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->equipmentPriceLineEdit->setValidator(equipmentPriceValidator);

    QRegularExpressionValidator *equipmentNameValidator = new QRegularExpressionValidator(equipmentNameRegex, this);
    ui->equipmentNameLineEdit->setValidator(equipmentNameValidator);

    QRegularExpressionValidator *equipmentBrandValidator = new QRegularExpressionValidator(equipmentNameRegex, this);
    ui->equipmentBrandLineEdit->setValidator(equipmentBrandValidator);

    QRegularExpressionValidator *equipmentModelValidator = new QRegularExpressionValidator(equipmentNameRegex, this);
    ui->equipmentModelLineEdit->setValidator(equipmentModelValidator);

    // ACTIVITY VALIDATORS
    QRegularExpressionValidator *responsibleValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->responsibleLineEdit->setValidator(responsibleValidator);

    // PAYMENT VALIDATORS
    QRegularExpressionValidator *paymentMemberValidator = new QRegularExpressionValidator(cinRegex, this);
    ui->paymentMemberEdit->setValidator(paymentMemberValidator);
    ui->paymentMemberEdit->setMaxLength(8);

    // TOOLTIPS
    ui->empIdLineEdit->setToolTip("Enter exactly 8 numeric digits (e.g., 12345678)");
    ui->phoneLineEdit->setToolTip("Enter exactly 8 numeric digits (e.g., 55123456)");
    ui->salaryLineEdit->setToolTip("Enter a positive salary amount (e.g., 1500.50)");
    ui->firstNameLineEdit->setToolTip("Enter first name (letters, spaces, hyphens, apostrophes only)");
    ui->lastNameLineEdit->setToolTip("Enter last name (letters, spaces, hyphens, apostrophes only)");

    ui->memberIdLineEdit->setToolTip("Enter exactly 8 numeric digits (e.g., 12345678)");
    ui->memberPhoneLineEdit->setToolTip("Enter exactly 8 numeric digits (e.g., 55123456)");
    ui->memberFirstNameLineEdit->setToolTip("Enter first name (letters, spaces, hyphens, apostrophes only)");
    ui->memberLastNameLineEdit->setToolTip("Enter last name (letters, spaces, hyphens, apostrophes only)");
    ui->memberEmailLineEdit->setToolTip("Enter valid email address (e.g., member@example.com)");

    ui->equipmentPriceLineEdit->setToolTip("Enter a positive price amount (e.g., 299.99)");
    ui->equipmentNameLineEdit->setToolTip("Enter equipment name (letters, numbers, spaces, hyphens, apostrophes)");
    ui->equipmentBrandLineEdit->setToolTip("Enter equipment brand (letters, numbers, spaces, hyphens, apostrophes)");
    ui->equipmentModelLineEdit->setToolTip("Enter equipment model (letters, numbers, spaces, hyphens, apostrophes)");

    ui->responsibleLineEdit->setToolTip("Enter responsible employee name (letters, spaces, hyphens, apostrophes only)");
    ui->paymentMemberEdit->setToolTip("Enter member ID if applicable (exactly 8 numeric digits)");

    // PLACEHOLDERS
    ui->empIdLineEdit->setPlaceholderText("12345678 (8 digits)");
    ui->phoneLineEdit->setPlaceholderText("55123456 (8 digits)");
    ui->salaryLineEdit->setPlaceholderText("1500.50");

    ui->memberIdLineEdit->setPlaceholderText("12345678 (8 digits)");
    ui->memberPhoneLineEdit->setPlaceholderText("55123456 (8 digits)");
    ui->memberEmailLineEdit->setPlaceholderText("member@example.com");

    ui->equipmentPriceLineEdit->setPlaceholderText("299.99");
    ui->paymentMemberEdit->setPlaceholderText("12345678 (optional)");
}

void EmployerAdmin::updateNavigationStyle()
{
    // Placeholder for future styling
}
