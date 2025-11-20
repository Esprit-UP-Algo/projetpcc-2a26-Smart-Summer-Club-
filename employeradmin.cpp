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
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLineSeries>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include "login.h"
#include "totpsetupdialog.h"

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
    navigationButtonGroup->addButton(ui->settingsButton, 5);   // Settings

    // Initialize management classes
    employeeManager = new Employee(ui, this);
    memberManager   = new Member(ui, this);
    activityManager = new Activity(ui, this);
    equipmentManager = new Equipment(ui, this);
    paymentManager  = new Payment(ui, this);
    emailPanel     = new EmailPanel(this);

    // Setup connections
    setupConnections();

    // Setup input field validators
    setupInputValidators();
    
    // Setup settings page
    setupSettingsPage();
    
    // Setup tables through management classes
    employeeManager->setupEmployeeTable();
    memberManager->setupMemberTable();
    activityManager->setupActivityTable();
    equipmentManager->setupEquipmentTable();
    // equipmentManager->setupEquipmentDetailsTable();  <-- REMOVED: Already called in Equipment constructor
    paymentManager->setupPaymentTable();
    
    // Setup SMS Panel
    setupEmailPanel();
    
    // Replace the SMS Panel placeholder with actual instance
    ui->memberSMSTabLayout->replaceWidget(ui->emailPanel, emailPanel);
    delete ui->emailPanel;  // Remove the placeholder

    // Update payment statistics
    paymentManager->populatePaymentStatistics();

    // Set initial state
    int defaultTab = 0;
    QString dept = Login::currentUser.department.trimmed().toLower();
    if (dept == "general administration" || Login::currentUser.isAdmin) {
        defaultTab = 0; // Employees
    } else if (dept == "activity management" || dept == "activity") {
        defaultTab = 3; // Activities
    } else if (dept == "member management" || dept == "member") {
        defaultTab = 1; // Members
    } else if (dept == "equipment") {
        defaultTab = 2; // Equipment
    } else if (dept == "transaction") {
        defaultTab = 4; // Payments
    }
    ui->stackedWidget->setCurrentIndex(defaultTab);
    // Optionally set tab widget index for each section if needed
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

    // Build employee statistics charts
    setupEmployeeStatisticsCharts();

    // Build member statistics charts
    setupMemberStatisticsCharts();
    // Build activity statistics charts
    setupActivityStatisticsCharts();

    // Populate employee statistic cards dynamically
    updateEmployeeStatisticsCards();
    
    // Populate member statistic cards dynamically
    updateMemberStatisticsCards();
    
    // Populate activity statistic cards dynamically
    updateActivityStatisticsCards();

    // Enable auto refresh (can be disabled later)
    setStatisticsAutoRefreshEnabled(true, 15000); // 15s default

    // Show user info
    showUserInfo();

    // Update tab visibility based on user role
    updateTabVisibility();

    // Auto-update user info every 5 seconds
    QTimer *userInfoTimer = new QTimer(this);
    connect(userInfoTimer, &QTimer::timeout, this, &EmployerAdmin::refreshUserInfoFromDatabase);
    userInfoTimer->start(5000);
}

EmployerAdmin::~EmployerAdmin()
{
    delete employeeManager;
    delete memberManager;
    delete activityManager;
    delete equipmentManager;
    delete paymentManager;
    delete emailPanel;
    delete ui;
}

void EmployerAdmin::setupConnections()
{
    // Navigation buttons
    connect(navigationButtonGroup, &QButtonGroup::idClicked,
            this, [this](int id) {
                // Don't switch if settings button is clicked (handled separately)
                if (id < 5) {
                    ui->stackedWidget->setCurrentIndex(id);
                    updateNavigationStyle();
                }
            });

    // Employee management buttons
    connect(ui->employeeSearchButton, &QPushButton::clicked, employeeManager, &Employee::onSearchEmployees);
    connect(ui->employeeUploadPhotoButton, &QPushButton::clicked, employeeManager, &Employee::onUploadPhoto);
    connect(ui->confirmAddButton, &QPushButton::clicked, employeeManager, &Employee::onConfirmAdd);
    connect(ui->confirmAddButton, &QPushButton::clicked, this, &EmployerAdmin::updateEmployeeStatisticsCards);
    connect(ui->confirmUpdateButton, &QPushButton::clicked, employeeManager, &Employee::onConfirmUpdate);
    connect(ui->confirmUpdateButton, &QPushButton::clicked, this, &EmployerAdmin::updateEmployeeStatisticsCards);
    connect(ui->employeeSortButton, &QPushButton::clicked, employeeManager, &Employee::onSortEmployees);
    connect(ui->employeeExportButton, &QPushButton::clicked, employeeManager, &Employee::onExportEmployees);

    // Member management buttons
    connect(ui->memberConfirmAddButton, &QPushButton::clicked, memberManager, &Member::onConfirmAdd);
    connect(ui->memberConfirmAddButton, &QPushButton::clicked, this, &EmployerAdmin::updateMemberStatisticsCards);
    connect(ui->memberConfirmUpdateButton, &QPushButton::clicked, memberManager, &Member::onConfirmUpdate);
    connect(ui->memberConfirmUpdateButton, &QPushButton::clicked, this, &EmployerAdmin::updateMemberStatisticsCards);
    connect(ui->memberUploadPhotoButton, &QPushButton::clicked, memberManager, &Member::onUploadPhoto);
    connect(ui->memberSearchLineEdit, &QLineEdit::textChanged, memberManager, &Member::onSearchMembers);
    connect(ui->memberSortButton, &QPushButton::clicked, memberManager, &Member::onSortMembers);
    connect(ui->memberExportButton, &QPushButton::clicked, memberManager, &Member::onExportMembers);

    // Activity management buttons
    connect(ui->activityConfirmButton, &QPushButton::clicked, activityManager, &Activity::onConfirmAdd);
    connect(ui->activityConfirmButton, &QPushButton::clicked, this, &EmployerAdmin::updateActivityStatisticsCards);
    connect(ui->activityUpdateButton, &QPushButton::clicked, activityManager, &Activity::onConfirmUpdate);
    connect(ui->activityUpdateButton, &QPushButton::clicked, this, &EmployerAdmin::updateActivityStatisticsCards);
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
    
    // Settings page buttons
    connect(ui->settingsButton, &QPushButton::clicked, this, &EmployerAdmin::onSettingsButtonClicked);
    connect(ui->setupTwoFactorButton, &QPushButton::clicked, this, &EmployerAdmin::onSetupTwoFactorClicked);
    connect(ui->disableTwoFactorButton, &QPushButton::clicked, this, &EmployerAdmin::onDisableTwoFactorClicked);
    
    // Logout button
    connect(ui->logoutButton, &QPushButton::clicked, this, &EmployerAdmin::onLogoutClicked);
    
    // Setup logout button red hover effect
    ui->logoutButton->setStyleSheet(
        "QPushButton#logoutButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    padding: 18px 24px;"
        "    text-align: left;"
        "    font-size: 15px;"
        "    font-weight: 500;"
        "    color: #34495e;"
        "    border-radius: 12px;"
        "    margin: 4px 16px;"
        "    transition: all 0.3s ease;"
        "    min-height: 20px;"
        "}"
        "QPushButton#logoutButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231, 76, 60, 0.12), stop:1 rgba(231, 76, 60, 0.08));"
        "    color: #e74c3c;"
        "    transform: translateX(4px);"
        "    box-shadow: 0 2px 8px rgba(231, 76, 60, 0.15);"
        "}"
    );
    connect(ui->changeProfilePictureButton, &QPushButton::clicked, this, &EmployerAdmin::onChangeProfilePictureClicked);
    connect(ui->changePasswordButton, &QPushButton::clicked, this, &EmployerAdmin::onChangePasswordClicked);
    connect(ui->applyThemeButton, &QPushButton::clicked, this, &EmployerAdmin::onApplyThemeClicked);
}

void EmployerAdmin::onNavigationButtonClicked()
{
    updateNavigationStyle();
}

void EmployerAdmin::setupEmployeeStatisticsCharts()
{
    buildEmployeeDepartmentChart();
    buildEmployeeStatusChart();
    buildEmployeeSalaryChart();
}

void EmployerAdmin::buildEmployeeDepartmentChart()
{
    if (employeeDepartmentChartView) { 
        employeeDepartmentChartView->deleteLater(); 
        employeeDepartmentChartView = nullptr; 
    }
    
    QMap<QString,int> counts;
    QSqlQuery q("SELECT DEPARTMENT, COUNT(*) FROM EMPLOYEES GROUP BY DEPARTMENT");
    while (q.next()) {
        QString dept = q.value(0).toString();
        if (dept.isEmpty()) dept = "Not Specified";
        counts[dept] = q.value(1).toInt();
    }
    
    if (counts.isEmpty()) {
        // Add some default data if no departments exist
        counts["HR"] = 1;
        counts["IT"] = 1;
        counts["Finance"] = 1;
    }
    
    int total = 0; 
    for (auto v : counts) total += v;
    
    QPieSeries *series = new QPieSeries();
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        double pct = total > 0 ? (it.value() * 100.0 / total) : 0.0;
        auto slice = series->append(QString("%1 (%2%)").arg(it.key()).arg(QString::number(pct, 'f', 1)), it.value());
        // Set colors based on department
        int hue = (qAbs(qHash(it.key())) % 360);
        slice->setColor(QColor::fromHsl(hue, 160, 120));
    }
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employee Department Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor("#f8fbfc")));
    chart->setTitleBrush(QBrush(QColor("#2c3e50")));
    chart->legend()->setAlignment(Qt::AlignBottom);
    
    employeeDepartmentChartView = new QChartView(chart);
    employeeDepartmentChartView->setRenderHint(QPainter::Antialiasing);
    employeeDepartmentChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    if (ui->employeeDepartmentChartFrame) {
        if (auto layout = ui->employeeDepartmentChartFrame->layout()) {
            if (ui->employeeDepartmentChartPlaceholder) {
                ui->employeeDepartmentChartPlaceholder->hide();
            }
            layout->addWidget(employeeDepartmentChartView);
        }
    }
}

void EmployerAdmin::buildEmployeeStatusChart()
{
    if (employeeStatusChartView) { 
        employeeStatusChartView->deleteLater(); 
        employeeStatusChartView = nullptr; 
    }
    
    QMap<QString,int> counts;
    QSqlQuery q("SELECT STATUS, COUNT(*) FROM EMPLOYEES GROUP BY STATUS");
    while (q.next()) {
        QString status = q.value(0).toString();
        if (status.isEmpty()) status = "Not Specified";
        counts[status] = q.value(1).toInt();
    }
    
    if (counts.isEmpty()) {
        // Add some default data if no statuses exist
        counts["Active"] = 1;
    }
    
    // Create bar series for histogram
    QBarSeries *series = new QBarSeries();
    QBarSet *barSet = new QBarSet("Employees");
    QStringList categories;
    
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        categories << it.key();
        *barSet << it.value();
    }
    
    barSet->setColor(QColor::fromHsl(200, 160, 120)); // Blue theme
    series->append(barSet);
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employee Status Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor("#f8fbfc")));
    chart->setTitleBrush(QBrush(QColor("#2c3e50")));
    chart->legend()->hide();
    
    // Create axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    int maxCount = 0;
    for (int count : counts) maxCount = std::max(maxCount, count);
    axisY->setRange(0, maxCount * 1.2);
    axisY->setTitleText("Number of Employees");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    employeeStatusChartView = new QChartView(chart);
    employeeStatusChartView->setRenderHint(QPainter::Antialiasing);
    employeeStatusChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    if (ui->employeeStatusChartFrame) {
        if (auto layout = ui->employeeStatusChartFrame->layout()) {
            if (ui->employeeStatusChartPlaceholder) {
                ui->employeeStatusChartPlaceholder->hide();
            }
            layout->addWidget(employeeStatusChartView);
        }
    }
}

void EmployerAdmin::buildEmployeeSalaryChart()
{
    if (employeeSalaryChartView) { 
        employeeSalaryChartView->deleteLater(); 
        employeeSalaryChartView = nullptr; 
    }
    
    // Get salary data sorted
    QVector<double> salaries;
    QSqlQuery q("SELECT SALARY FROM EMPLOYEES WHERE SALARY IS NOT NULL ORDER BY SALARY");
    while (q.next()) {
        salaries.append(q.value(0).toDouble());
    }
    
    if (salaries.isEmpty()) {
        // Add some default salary data if none exists
        salaries = {30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 70000, 75000};
    }
    
    // Create ECC (Empirical Cumulative Curve)
    QLineSeries *series = new QLineSeries();
    
    for (int i = 0; i < salaries.size(); ++i) {
        double percentile = (i + 1.0) / salaries.size() * 100.0; // Cumulative percentage
        series->append(salaries[i], percentile);
    }
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Salary Distribution (Empirical Cumulative Curve)");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor("#f8fbfc")));
    chart->setTitleBrush(QBrush(QColor("#2c3e50")));
    chart->legend()->hide();
    
    // Create axes
    QValueAxis *axisX = new QValueAxis();
    if (!salaries.isEmpty()) {
        axisX->setRange(salaries.first() * 0.9, salaries.last() * 1.1);
    }
    axisX->setTitleText("Salary");
    axisX->setLabelFormat("%.0f");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Cumulative Percentage (%)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    // Style the line
    QPen pen(QColor::fromHsl(160, 160, 120)); // Teal theme
    pen.setWidth(3);
    series->setPen(pen);
    
    employeeSalaryChartView = new QChartView(chart);
    employeeSalaryChartView->setRenderHint(QPainter::Antialiasing);
    employeeSalaryChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    if (ui->employeeSalaryChartFrame) {
        if (auto layout = ui->employeeSalaryChartFrame->layout()) {
            if (ui->employeeSalaryChartPlaceholder) {
                ui->employeeSalaryChartPlaceholder->hide();
            }
            layout->addWidget(employeeSalaryChartView);
        }
    }
}

void EmployerAdmin::setupMemberStatisticsCharts()
{
    buildMemberGenderChart();
    buildMemberAgeChart();
    buildMemberSubscriptionChart();
}

void EmployerAdmin::buildMemberGenderChart()
{
    if (memberGenderChartView) { memberGenderChartView->deleteLater(); memberGenderChartView = nullptr; }
    QMap<QString,int> counts;
    QSqlQuery q("SELECT GENDER, COUNT(*) FROM MEMBERS GROUP BY GENDER");
    while (q.next()) counts[q.value(0).toString()] = q.value(1).toInt();
    int total = 0; for (auto v : counts) total += v;
    QPieSeries *series = new QPieSeries();
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        double pct = total ? (double)it.value() / total * 100.0 : 0.0;
        auto slice = series->append(QString("%1 (%2%)").arg(it.key()).arg(QString::number(pct, 'f', 1)), it.value());
        slice->setLabelVisible(true);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Gender Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    memberGenderChartView = new QChartView(chart);
    memberGenderChartView->setRenderHint(QPainter::Antialiasing);
    memberGenderChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (ui->memberGenderChartFrame && ui->memberGenderChartFrame->layout()) {
        if (ui->memberGenderChartPlaceholder) ui->memberGenderChartPlaceholder->hide();
        ui->memberGenderChartFrame->layout()->addWidget(memberGenderChartView);
    }
}

void EmployerAdmin::buildMemberAgeChart()
{
    if (memberAgeChartView) { memberAgeChartView->deleteLater(); memberAgeChartView = nullptr; }
    // Age bins
    struct Bin { QString label; int min; int max; int count; };
    QVector<Bin> bins = {
        {"18-24",18,24,0}, {"25-34",25,34,0}, {"35-44",35,44,0}, {"45-54",45,54,0}, {"55+",55,200,0}
    };
    QSqlQuery q("SELECT AGE FROM MEMBERS");
    while (q.next()) {
        int age = q.value(0).toInt();
        for (auto &b : bins) { if (age >= b.min && age <= b.max) { b.count++; break; } }
    }
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Age Groups");
    QStringList categories;
    int maxCount = 0;
    for (auto &b : bins) { *set << b.count; categories << b.label; if (b.count > maxCount) maxCount = b.count; }
    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Age Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QBarCategoryAxis *axisX = new QBarCategoryAxis(); axisX->append(categories); chart->addAxis(axisX, Qt::AlignBottom); series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis(); axisY->setTitleText("Members"); axisY->setRange(0, std::max(1, maxCount)); chart->addAxis(axisY, Qt::AlignLeft); series->attachAxis(axisY);
    memberAgeChartView = new QChartView(chart);
    memberAgeChartView->setRenderHint(QPainter::Antialiasing);
    memberAgeChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (ui->memberAgeChartFrame && ui->memberAgeChartFrame->layout()) {
        if (ui->memberAgeChartPlaceholder) ui->memberAgeChartPlaceholder->hide();
        ui->memberAgeChartFrame->layout()->addWidget(memberAgeChartView);
    }
}

void EmployerAdmin::buildMemberSubscriptionChart()
{
    if (memberSubscriptionChartView) { memberSubscriptionChartView->deleteLater(); memberSubscriptionChartView = nullptr; }
    QMap<QString,int> counts;
    QSqlQuery q("SELECT SUBSCRIPTION_PLAN, COUNT(*) FROM MEMBERS GROUP BY SUBSCRIPTION_PLAN");
    while (q.next()) counts[q.value(0).toString()] = q.value(1).toInt();
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Plans");
    QStringList categories;
    int maxPlanCount = 0;
    for (auto it = counts.begin(); it != counts.end(); ++it) { *set << it.value(); categories << it.key(); if (it.value() > maxPlanCount) maxPlanCount = it.value(); }
    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Subscription Plan Histogram");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QBarCategoryAxis *axisX = new QBarCategoryAxis(); axisX->append(categories); chart->addAxis(axisX, Qt::AlignBottom); series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis(); axisY->setTitleText("Members"); axisY->setRange(0, std::max(1, maxPlanCount)); chart->addAxis(axisY, Qt::AlignLeft); series->attachAxis(axisY);
    memberSubscriptionChartView = new QChartView(chart);
    memberSubscriptionChartView->setRenderHint(QPainter::Antialiasing);
    memberSubscriptionChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (ui->memberSubscriptionChartFrame && ui->memberSubscriptionChartFrame->layout()) {
        if (ui->memberSubscriptionChartPlaceholder) ui->memberSubscriptionChartPlaceholder->hide();
        ui->memberSubscriptionChartFrame->layout()->addWidget(memberSubscriptionChartView);
    }
}

void EmployerAdmin::updateMemberStatisticsCards()
{
    // Total members
    int total = 0;
    int active = 0;
    int newThisMonth = 0;

    QSqlQuery qTotal("SELECT COUNT(*) FROM MEMBERS");
    if (qTotal.next()) total = qTotal.value(0).toInt();

    QSqlQuery qActive("SELECT COUNT(*) FROM MEMBERS WHERE STATUS='Active'");
    if (qActive.next()) active = qActive.value(0).toInt();

    // New members this month (JOIN_DATE in current month/year)
    QDate today = QDate::currentDate();
    QDate firstMonth(today.year(), today.month(), 1);
    QDate nextMonth = firstMonth.addMonths(1);
    QSqlQuery qNew;
    qNew.prepare("SELECT COUNT(*) FROM MEMBERS WHERE JOIN_DATE >= :start AND JOIN_DATE < :end");
    qNew.bindValue(":start", firstMonth);
    qNew.bindValue(":end", nextMonth);
    if (qNew.exec() && qNew.next()) newThisMonth = qNew.value(0).toInt();

    if (ui->totalMembersNumber) ui->totalMembersNumber->setText(QString::number(total));
    if (ui->activeMembersNumber) ui->activeMembersNumber->setText(QString::number(active));
    if (ui->newMembersNumber) ui->newMembersNumber->setText(QString::number(newThisMonth));
}

void EmployerAdmin::updateEmployeeStatisticsCards()
{
    QSqlQuery query;
    int total = 0, active = 0, newThisMonth = 0;

    // Total employees
    if (query.exec("SELECT COUNT(*) FROM EMPLOYEES")) {
        if (query.next()) total = query.value(0).toInt();
    }

    // Active employees (assuming STATUS column, or use a different criteria like not terminated)
    if (query.exec("SELECT COUNT(*) FROM EMPLOYEES WHERE STATUS = 'Active'")) {
        if (query.next()) active = query.value(0).toInt();
    } else {
        // Fallback: assume all employees are active if no status column
        active = total;
    }

    // New employees hired this month
    QDate currentDate = QDate::currentDate();
    QDate startOfMonth = QDate(currentDate.year(), currentDate.month(), 1);
    QString monthQuery = QString("SELECT COUNT(*) FROM EMPLOYEES WHERE HIRE_DATE >= TO_DATE('%1', 'YYYY-MM-DD') AND HIRE_DATE < TO_DATE('%2', 'YYYY-MM-DD')")
        .arg(startOfMonth.toString("yyyy-MM-dd"))
        .arg(startOfMonth.addMonths(1).toString("yyyy-MM-dd"));
    
    if (query.exec(monthQuery)) {
        if (query.next()) newThisMonth = query.value(0).toInt();
    }

    // Update UI labels
    if (ui->totalEmployeesNumber) ui->totalEmployeesNumber->setText(QString::number(total));
    if (ui->activeEmployeesNumber) ui->activeEmployeesNumber->setText(QString::number(active));
    if (ui->newEmployeesNumber) ui->newEmployeesNumber->setText(QString::number(newThisMonth));
}

void EmployerAdmin::updateActivityStatisticsCards()
{
    QSqlQuery query;
    int total = 0, upcoming = 0, activeToday = 0;

    // Total activities
    if (query.exec("SELECT COUNT(*) FROM ACTIVITIES")) {
        if (query.next()) total = query.value(0).toInt();
    }

    // Get current date
    QDate currentDate = QDate::currentDate();

    // Upcoming activities (activities with event date in the future)
    QSqlQuery upcomingQuery;
    upcomingQuery.prepare("SELECT COUNT(*) FROM ACTIVITIES WHERE EVENT_DATE > :currentDate");
    upcomingQuery.bindValue(":currentDate", currentDate);
    
    if (upcomingQuery.exec() && upcomingQuery.next()) {
        upcoming = upcomingQuery.value(0).toInt();
    }

    // Active today (activities that are happening today)
    QSqlQuery todayQuery;
    todayQuery.prepare("SELECT COUNT(*) FROM ACTIVITIES WHERE EVENT_DATE = :currentDate");
    todayQuery.bindValue(":currentDate", currentDate);
    
    if (todayQuery.exec() && todayQuery.next()) {
        activeToday = todayQuery.value(0).toInt();
    }

    // Update UI labels
    if (ui->totalActivitiesNumber) ui->totalActivitiesNumber->setText(QString::number(total));
    if (ui->upcomingActivitiesNumber) ui->upcomingActivitiesNumber->setText(QString::number(upcoming));
    if (ui->activeActivitiesNumber) ui->activeActivitiesNumber->setText(QString::number(activeToday));
}

void EmployerAdmin::refreshStatistics()
{
    updateEmployeeStatisticsCards();
    updateMemberStatisticsCards();
    updateActivityStatisticsCards();
    // Rebuild charts (could be optimized to update data only)
    setupEmployeeStatisticsCharts();
    setupMemberStatisticsCharts();
    setupActivityStatisticsCharts();
}

void EmployerAdmin::setStatisticsAutoRefreshEnabled(bool enabled, int intervalMs)
{
    if (!m_statsRefreshTimer) {
        m_statsRefreshTimer = new QTimer(this);
        connect(m_statsRefreshTimer, &QTimer::timeout, this, &EmployerAdmin::refreshStatistics);
    }
    if (enabled) {
        m_statsRefreshTimer->start(intervalMs);
    } else {
        m_statsRefreshTimer->stop();
    }
}

void EmployerAdmin::setupActivityStatisticsCharts()
{
    buildActivityTypeChart();
    buildActivityAgeChart();
}

void EmployerAdmin::buildActivityTypeChart()
{
    if (activityTypeChartView) { activityTypeChartView->deleteLater(); activityTypeChartView = nullptr; }
    QMap<QString,int> counts;
    QSqlQuery q("SELECT ACTIVITY_TYPE, COUNT(*) FROM ACTIVITIES GROUP BY ACTIVITY_TYPE");
    while (q.next()) counts[q.value(0).toString()] = q.value(1).toInt();
    int total = 0; for (auto v : counts) total += v;
    QPieSeries *series = new QPieSeries();
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        double pct = total ? (double)it.value() / total * 100.0 : 0.0;
        auto slice = series->append(QString("%1 (%2%)").arg(it.key()).arg(QString::number(pct,'f',1)), it.value());
        slice->setLabelVisible(true);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Activity Type Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    activityTypeChartView = new QChartView(chart);
    activityTypeChartView->setRenderHint(QPainter::Antialiasing);
    activityTypeChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (ui->activityTypeChartFrame && ui->activityTypeChartFrame->layout()) {
        if (ui->activityTypeChartPlaceholder) ui->activityTypeChartPlaceholder->hide();
        ui->activityTypeChartFrame->layout()->addWidget(activityTypeChartView);
    }
}

void EmployerAdmin::buildActivityAgeChart()
{
    if (activityAgeChartView) { activityAgeChartView->deleteLater(); activityAgeChartView = nullptr; }
    struct Bin { QString label; int min; int max; int count; };
    QVector<Bin> bins = {
        {"0-12",0,12,0},{"13-17",13,17,0},{"18-24",18,24,0},{"25-34",25,34,0},{"35-44",35,44,0},{"45-54",45,54,0},{"55+",55,200,0}
    };
    QSqlQuery q("SELECT AGE_REQUIREMENT FROM ACTIVITIES");
    while (q.next()) {
        int age = q.value(0).toInt();
        for (auto &b : bins) { if (age >= b.min && age <= b.max) { b.count++; break; } }
    }
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Age Requirement");
    QStringList categories;
    int maxCount = 0;
    for (auto &b : bins) { *set << b.count; categories << b.label; if (b.count > maxCount) maxCount = b.count; }
    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Age Requirement Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QBarCategoryAxis *axisX = new QBarCategoryAxis(); axisX->append(categories); chart->addAxis(axisX, Qt::AlignBottom); series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis(); axisY->setTitleText("Activities"); axisY->setRange(0, std::max(1, maxCount)); chart->addAxis(axisY, Qt::AlignLeft); series->attachAxis(axisY);
    activityAgeChartView = new QChartView(chart);
    activityAgeChartView->setRenderHint(QPainter::Antialiasing);
    activityAgeChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (ui->activityAgeChartFrame && ui->activityAgeChartFrame->layout()) {
        if (ui->activityAgeChartPlaceholder) ui->activityAgeChartPlaceholder->hide();
        ui->activityAgeChartFrame->layout()->addWidget(activityAgeChartView);
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
    ui->memberTabWidget->setTabIcon(2, QIcon(":/icons/icons/statistic.png"));
    ui->memberTabWidget->setTabIcon(3, QIcon(":/icons/icons/members.png"));

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

void EmployerAdmin::showUserInfo()
{
    // Set user name
    ui->userNameLabel->setText(Login::currentUser.firstName + " " + Login::currentUser.lastName);
    // Set user role
    ui->userRoleLabel->setText(Login::currentUser.department);
    // Set avatar
    if (!Login::currentUser.photo.isEmpty()) {
        QPixmap pixmap;
        pixmap.loadFromData(Login::currentUser.photo);
        QPixmap scaled = pixmap.scaled(40, 40, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QPixmap circular(40, 40);
        circular.fill(Qt::transparent);
        QPainter painter(&circular);
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addEllipse(0, 0, 40, 40);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, scaled);
        painter.end();
        ui->userAvatarLabel->setPixmap(circular);
        ui->userAvatarLabel->setText("");
    } else {
        QString initials = Login::currentUser.firstName.left(1).toUpper() + Login::currentUser.lastName.left(1).toUpper();
        ui->userAvatarLabel->setPixmap(QPixmap());
        ui->userAvatarLabel->setText(initials);
    }
}

void EmployerAdmin::refreshUserInfoFromDatabase() {
    QSqlQuery query;
    query.prepare("SELECT FIRST_NAME, LAST_NAME, DEPARTMENT, PHOTO FROM EMPLOYEES WHERE CIN = :cin");
    query.bindValue(":cin", Login::currentUser.cin);
    if (query.exec() && query.next()) {
        Login::currentUser.firstName = query.value(0).toString();
        Login::currentUser.lastName = query.value(1).toString();
        Login::currentUser.department = query.value(2).toString();
        Login::currentUser.photo = query.value(3).toByteArray();
        showUserInfo();
    }
}

void EmployerAdmin::updateTabVisibility()
{
    // Always show all navigation buttons
    ui->employeesButton->setVisible(true);
    ui->membersButton->setVisible(true);
    ui->equipmentButton->setVisible(true);
    ui->activitiesButton->setVisible(true);
    ui->paymentsButton->setVisible(true);

    QString dept = Login::currentUser.department.trimmed().toLower();
    if (dept == "general administration" || Login::currentUser.isAdmin) {
        // General Administration and Admin: all buttons enabled
        ui->employeesButton->setEnabled(true);
        ui->membersButton->setEnabled(true);
        ui->equipmentButton->setEnabled(true);
        ui->activitiesButton->setEnabled(true);
        ui->paymentsButton->setEnabled(true);
    } else if (dept == "activity management") {
        ui->employeesButton->setEnabled(false);
        ui->membersButton->setEnabled(false);
        ui->equipmentButton->setEnabled(false);
        ui->activitiesButton->setEnabled(true);
        ui->paymentsButton->setEnabled(false);
    } else if (dept == "member management") {
        ui->employeesButton->setEnabled(false);
        ui->membersButton->setEnabled(true);
        ui->equipmentButton->setEnabled(false);
        ui->activitiesButton->setEnabled(false);
        ui->paymentsButton->setEnabled(false);
    } else if (dept == "employee") {
        ui->employeesButton->setEnabled(true);
        ui->membersButton->setEnabled(false);
        ui->equipmentButton->setEnabled(false);
        ui->activitiesButton->setEnabled(false);
        ui->paymentsButton->setEnabled(false);
    } else if (dept == "member") {
        ui->employeesButton->setEnabled(false);
        ui->membersButton->setEnabled(true);
        ui->equipmentButton->setEnabled(false);
        ui->activitiesButton->setEnabled(false);
        ui->paymentsButton->setEnabled(false);
    } else if (dept == "equipment") {
        ui->employeesButton->setEnabled(false);
        ui->membersButton->setEnabled(false);
        ui->equipmentButton->setEnabled(true);
        ui->activitiesButton->setEnabled(false);
        ui->paymentsButton->setEnabled(false);
    } else if (dept == "activity") {
        ui->employeesButton->setEnabled(false);
        ui->membersButton->setEnabled(false);
        ui->equipmentButton->setEnabled(false);
        ui->activitiesButton->setEnabled(true);
        ui->paymentsButton->setEnabled(false);
    } else if (dept == "transaction") {
        ui->employeesButton->setEnabled(false);
        ui->membersButton->setEnabled(false);
        ui->equipmentButton->setEnabled(false);
        ui->activitiesButton->setEnabled(false);
        ui->paymentsButton->setEnabled(true);
    } else {
        // Unknown department: disable all
        ui->employeesButton->setEnabled(false);
        ui->membersButton->setEnabled(false);
        ui->equipmentButton->setEnabled(false);
        ui->activitiesButton->setEnabled(false);
        ui->paymentsButton->setEnabled(false);
    }
}

void EmployerAdmin::updateNavigationStyle()
{
    // Get current page index
    int currentIndex = ui->stackedWidget->currentIndex();
    
    // Set settings button active style when on settings page
    if (currentIndex == 5) { // Settings page
        ui->settingsButton->setStyleSheet(
            "QPushButton#settingsButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #16a5b3, stop:1 #139aa6);"
            "    color: white;"
            "    border: none;"
            "    padding: 18px 24px;"
            "    text-align: left;"
            "    font-size: 15px;"
            "    font-weight: 600;"
            "    border-radius: 12px;"
            "    margin: 4px 16px;"
            "    min-height: 20px;"
            "    box-shadow: 0 4px 12px rgba(22, 165, 179, 0.25);"
            "    transform: translateX(6px);"
            "}"
            "QPushButton#settingsButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #139aa6, stop:1 #0f858f);"
            "    box-shadow: 0 6px 16px rgba(22, 165, 179, 0.35);"
            "}"
        );
    } else {
        // Reset settings button to normal style
        ui->settingsButton->setStyleSheet(
            "QPushButton#settingsButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    padding: 18px 24px;"
            "    text-align: left;"
            "    font-size: 15px;"
            "    font-weight: 500;"
            "    color: #34495e;"
            "    border-radius: 12px;"
            "    margin: 4px 16px;"
            "    transition: all 0.3s ease;"
            "    min-height: 20px;"
            "}"
            "QPushButton#settingsButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 rgba(22, 165, 179, 0.12), stop:1 rgba(22, 165, 179, 0.08));"
            "    color: #16a5b3;"
            "    transform: translateX(4px);"
            "    box-shadow: 0 2px 8px rgba(22, 165, 179, 0.15);"
            "}"
        );
    }
}

void EmployerAdmin::setupSettingsPage()
{
    // Load user profile information
    loadUserProfileInfo();
    
    // Update 2FA status
    updateTwoFactorStatus();
    
    // Set up theme combo box
    ui->themeComboBox->setCurrentIndex(0); // Default to Light Theme
    
    // Set up default preferences
    ui->autoRefreshCheckBox->setChecked(true);
    ui->notificationsCheckBox->setChecked(true);
    ui->soundCheckBox->setChecked(false);
}

void EmployerAdmin::loadUserProfileInfo()
{
    // Update the settings page with current user info
    if (ui->currentUserNameLabel && ui->currentUserRoleLabel) {
        ui->currentUserNameLabel->setText(ui->userNameLabel->text());
        ui->currentUserRoleLabel->setText(ui->userRoleLabel->text());
    }
    
    // Set profile picture placeholder
    if (ui->profilePictureLabel) {
        QPixmap defaultAvatar(100, 100);
        defaultAvatar.fill(QColor("#16a5b3"));
        
        QPainter painter(&defaultAvatar);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::white, 2));
        painter.setFont(QFont("Arial", 24, QFont::Bold));
        painter.drawText(defaultAvatar.rect(), Qt::AlignCenter, ui->userAvatarLabel->text());
        
        ui->profilePictureLabel->setPixmap(defaultAvatar);
    }
}

void EmployerAdmin::updateTwoFactorStatus()
{
    // Check if 2FA is enabled for current user
    QSqlQuery query;
    query.prepare("SELECT is_enabled FROM employee_totp WHERE employee_cin = ?");
    query.addBindValue(Login::currentUser.cin);
    
    bool is2FAEnabled = false;
    if (query.exec() && query.next()) {
        is2FAEnabled = query.value(0).toBool();
    }
    
    // Update UI based on 2FA status
    if (is2FAEnabled) {
        ui->twoFactorStatusLabel->setText("✅ Enabled");
        ui->twoFactorStatusLabel->setStyleSheet("font-size: 14px; font-weight: 600; color: #27ae60;");
        ui->setupTwoFactorButton->setVisible(false);
        ui->disableTwoFactorButton->setVisible(true);
    } else {
        ui->twoFactorStatusLabel->setText("❌ Disabled");
        ui->twoFactorStatusLabel->setStyleSheet("font-size: 14px; font-weight: 600; color: #dc3545;");
        ui->setupTwoFactorButton->setVisible(true);
        ui->disableTwoFactorButton->setVisible(false);
    }
}

void EmployerAdmin::onSettingsButtonClicked()
{
    // Switch to settings page
    ui->stackedWidget->setCurrentIndex(5); // Settings page index
    
    // Update navigation button style - uncheck all main navigation buttons
    for (int i = 0; i < navigationButtonGroup->buttons().size() - 1; ++i) { // -1 to exclude settings button
        navigationButtonGroup->buttons()[i]->setChecked(false);
    }
    
    // Update navigation styling to show settings as active
    updateNavigationStyle();
    
    // Refresh settings page data
    loadUserProfileInfo();
    updateTwoFactorStatus();
}

void EmployerAdmin::onSetupTwoFactorClicked()
{
    // Create and show TOTP setup dialog
    QString fullName = QString("%1 %2").arg(Login::currentUser.firstName).arg(Login::currentUser.lastName);
    TOTPSetupDialog *dialog = new TOTPSetupDialog(Login::currentUser.cin, fullName, this);
    
    if (dialog->exec() == QDialog::Accepted) {
        // 2FA was successfully enabled
        updateTwoFactorStatus();
        
        QMessageBox::information(this, "2FA Enabled", 
            "🎉 Two-Factor Authentication has been successfully enabled for your account!\n\n"
            "Your account is now more secure. You'll need your authenticator app to log in from now on.\n\n"
            "Remember to keep your backup codes in a safe place!");
        
        qDebug() << "2FA enabled for user:" << Login::currentUser.cin;
    } else {
        qDebug() << "2FA setup cancelled by user";
    }
    
    dialog->deleteLater();
}

void EmployerAdmin::onDisableTwoFactorClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Disable 2FA", 
        "Are you sure you want to disable Two-Factor Authentication?\n\n"
        "This will make your account less secure.",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove 2FA from database
        QSqlQuery query;
        query.prepare("DELETE FROM employee_totp WHERE employee_cin = ?");
        query.addBindValue(Login::currentUser.cin);
        
        if (query.exec()) {
            QMessageBox::information(this, "Success", "Two-Factor Authentication has been disabled.");
            updateTwoFactorStatus();
        } else {
            QMessageBox::warning(this, "Error", "Failed to disable 2FA: " + query.lastError().text());
        }
    }
}

void EmployerAdmin::onLogoutClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
        "Logout",
        "Are you sure you want to logout?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Close the main window and return to login
        this->close();
    }
}

void EmployerAdmin::onChangeProfilePictureClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Profile Picture"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));
    
    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);
        if (!pixmap.isNull()) {
            // Scale and crop to circular profile picture
            QPixmap scaledPixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            
            QPixmap circularPixmap(100, 100);
            circularPixmap.fill(Qt::transparent);
            
            QPainter painter(&circularPixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setBrush(QBrush(scaledPixmap));
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(0, 0, 100, 100);
            
            ui->profilePictureLabel->setPixmap(circularPixmap);
            
            // TODO: Save profile picture to database
            QMessageBox::information(this, "Success", "Profile picture updated successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Invalid image file selected.");
        }
    }
}

void EmployerAdmin::onChangePasswordClicked()
{
    QString currentPassword = ui->currentPasswordLineEdit->text();
    QString newPassword = ui->newPasswordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();
    
    // Validate inputs
    if (currentPassword.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all password fields.");
        return;
    }
    
    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "Error", "New password and confirmation do not match.");
        return;
    }
    
    if (newPassword.length() < 6) {
        QMessageBox::warning(this, "Error", "New password must be at least 6 characters long.");
        return;
    }
    
    // Verify current password
    QSqlQuery query;
    query.prepare("SELECT password FROM EMPLOYEES WHERE CIN = ?");
    query.addBindValue(Login::currentUser.cin);
    
    if (query.exec() && query.next()) {
        QString storedPassword = query.value(0).toString();
        
        if (storedPassword != currentPassword) {
            QMessageBox::warning(this, "Error", "Current password is incorrect.");
            return;
        }
        
        // Update password
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE EMPLOYEES SET password = ? WHERE CIN = ?");
        updateQuery.addBindValue(newPassword);
        updateQuery.addBindValue(Login::currentUser.cin);
        
        if (updateQuery.exec()) {
            QMessageBox::information(this, "Success", "Password updated successfully!");
            
            // Clear password fields
            ui->currentPasswordLineEdit->clear();
            ui->newPasswordLineEdit->clear();
            ui->confirmPasswordLineEdit->clear();
        } else {
            QMessageBox::warning(this, "Error", "Failed to update password: " + updateQuery.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to verify current password.");
    }
}

void EmployerAdmin::onApplyThemeClicked()
{
    QString selectedTheme = ui->themeComboBox->currentText();
    
    // TODO: Implement theme switching logic
    QMessageBox::information(this, "Theme Applied", 
        QString("Theme switched to: %1\n\n"
                "Theme switching functionality will be implemented in the future.").arg(selectedTheme));
    
    // For now, just show a placeholder message
    // In the future, this would apply different stylesheets based on selection
}

void EmployerAdmin::setupEmailPanel()
{
    // Replace the placeholder widget in the UI with our SMS Panel
    QWidget* smsTabWidget = ui->memberSMSTab;
    QVBoxLayout* smsLayout = qobject_cast<QVBoxLayout*>(smsTabWidget->layout());
    
    if (smsLayout) {
        // Remove the placeholder widget
        QLayoutItem* item = smsLayout->takeAt(0);
        if (item && item->widget()) {
            item->widget()->deleteLater();
            delete item;
        }
        
        // Add our SMS Panel
        smsLayout->addWidget(emailPanel);
        
        // Load member data from database
        emailPanel->loadMembersFromDatabase();
    }
}
