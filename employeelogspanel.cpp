#include "employeelogspanel.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QUrl>
#include <QUuid>

// Static member definitions
QMutex EmployeeLogsPanel::s_logMutex;
const int EmployeeLogsPanel::MAX_LOG_ENTRIES_PER_FILE = 10000;
const int EmployeeLogsPanel::LOG_RETENTION_DAYS = 365;
const QString EmployeeLogsPanel::LOG_FILE_EXTENSION = ".audit";
const QString EmployeeLogsPanel::ARCHIVE_FOLDER_NAME = "audit_archive";

EmployeeLogsPanel::EmployeeLogsPanel(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(nullptr)
    , m_mainSplitter(nullptr)
    , m_timelineViewEnabled(false)
    , m_autoRefreshEnabled(true)
    , m_currentUserId("admin01") // TODO: Get from authentication system
    , m_currentUserName("System Administrator")
    , m_currentUserRole("Admin")
    , m_currentSessionId(QUuid::createUuid().toString(QUuid::WithoutBraces))
{
    setupUI();
    loadLogsFromFile();
    updateDashboard();
    updateTable();
    
    // Setup timers
    m_refreshTimer = new QTimer(this);
    m_refreshTimer->setInterval(30000); // 30 seconds
    connect(m_refreshTimer, &QTimer::timeout, this, &EmployeeLogsPanel::refreshLogs);
    
    m_riskAssessmentTimer = new QTimer(this);
    m_riskAssessmentTimer->setInterval(60000); // 1 minute
    connect(m_riskAssessmentTimer, &QTimer::timeout, this, &EmployeeLogsPanel::highlightSuspiciousActivity);
    
    if (m_autoRefreshEnabled) {
        m_refreshTimer->start();
        m_riskAssessmentTimer->start();
    }
    
    qDebug() << "🔍 EmployeeLogsPanel initialized with session:" << m_currentSessionId;
    
    // Test log entry to verify logging system is working
    EmployeeLogsPanel::logAction("SYSTEM", "Application", "startup", "", "", 
        "Employee Logs Panel initialized successfully");
}

void EmployeeLogsPanel::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(20);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Create main splitter
    m_mainSplitter = new QSplitter(Qt::Vertical, this);
    
    setupDashboard();
    setupFilters();
    setupTable();
    setupTimeline();
    setupRiskAssessment();
    setupInsights();
    
    // Add to main layout
    m_mainLayout->addWidget(m_mainSplitter);
    
    // Set splitter proportions
    m_mainSplitter->setSizes({200, 100, 400, 200}); // Dashboard, Filters, Table, Risk Assessment
}

void EmployeeLogsPanel::setupDashboard()
{
    m_dashboardWidget = new QWidget();
    m_dashboardLayout = new QGridLayout(m_dashboardWidget);
    m_dashboardLayout->setSpacing(15);
    
    // Total Logs Card
    m_totalLogsCard = new QGroupBox("📊 Total Audit Logs");
    setCardStyle(m_totalLogsCard, "#3498db");
    QVBoxLayout *totalLayout = new QVBoxLayout(m_totalLogsCard);
    m_totalLogsLabel = new QLabel("0");
    m_totalLogsLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #3498db;");
    m_totalLogsLabel->setAlignment(Qt::AlignCenter);
    totalLayout->addWidget(m_totalLogsLabel);
    QLabel *totalSubLabel = new QLabel("entries logged");
    totalSubLabel->setStyleSheet("color: #7f8c8d; font-size: 14px;");
    totalSubLabel->setAlignment(Qt::AlignCenter);
    totalLayout->addWidget(totalSubLabel);
    
    // Today's Activity Card
    m_todayActivityCard = new QGroupBox("📅 Today's Activity");
    setCardStyle(m_todayActivityCard, "#27ae60");
    QVBoxLayout *todayLayout = new QVBoxLayout(m_todayActivityCard);
    m_todayActivityLabel = new QLabel("0");
    m_todayActivityLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #27ae60;");
    m_todayActivityLabel->setAlignment(Qt::AlignCenter);
    todayLayout->addWidget(m_todayActivityLabel);
    QLabel *todaySubLabel = new QLabel("actions today");
    todaySubLabel->setStyleSheet("color: #7f8c8d; font-size: 14px;");
    todaySubLabel->setAlignment(Qt::AlignCenter);
    todayLayout->addWidget(todaySubLabel);
    
    // Risk Alerts Card
    m_riskAlertsCard = new QGroupBox("⚠️ Risk Alerts");
    setCardStyle(m_riskAlertsCard, "#e74c3c");
    QVBoxLayout *riskLayout = new QVBoxLayout(m_riskAlertsCard);
    m_riskAlertsLabel = new QLabel("0");
    m_riskAlertsLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #e74c3c;");
    m_riskAlertsLabel->setAlignment(Qt::AlignCenter);
    riskLayout->addWidget(m_riskAlertsLabel);
    QLabel *riskSubLabel = new QLabel("high-risk events");
    riskSubLabel->setStyleSheet("color: #7f8c8d; font-size: 14px;");
    riskSubLabel->setAlignment(Qt::AlignCenter);
    riskLayout->addWidget(riskSubLabel);
    
    // Last Activity Card
    m_lastActivityCard = new QGroupBox("🕒 Last Activity");
    setCardStyle(m_lastActivityCard, "#f39c12");
    QVBoxLayout *lastLayout = new QVBoxLayout(m_lastActivityCard);
    m_lastActivityLabel = new QLabel("No activity");
    m_lastActivityLabel->setStyleSheet("font-size: 18px; font-weight: 500; color: #f39c12;");
    m_lastActivityLabel->setAlignment(Qt::AlignCenter);
    m_lastActivityLabel->setWordWrap(true);
    lastLayout->addWidget(m_lastActivityLabel);
    
    // Layout dashboard cards
    m_dashboardLayout->addWidget(m_totalLogsCard, 0, 0);
    m_dashboardLayout->addWidget(m_todayActivityCard, 0, 1);
    m_dashboardLayout->addWidget(m_riskAlertsCard, 0, 2);
    m_dashboardLayout->addWidget(m_lastActivityCard, 0, 3);
    
    m_mainSplitter->addWidget(m_dashboardWidget);
}

void EmployeeLogsPanel::setupFilters()
{
    m_filterWidget = new QWidget();
    m_filterLayout = new QGridLayout(m_filterWidget);
    
    m_filterGroup = new QGroupBox("🔍 Advanced Filters & Controls");
    setCardStyle(m_filterGroup);
    QGridLayout *filterGroupLayout = new QGridLayout(m_filterGroup);
    
    // Search bar
    QLabel *searchLabel = new QLabel("Search:");
    searchLabel->setStyleSheet("font-weight: 600; color: #2c3e50;");
    m_searchEdit = new QLineEdit();
    m_searchEdit->setPlaceholderText("Search logs by description, user, action...");
    m_searchEdit->setStyleSheet(R"(
        QLineEdit {
            padding: 12px 16px;
            border: 2px solid #e0e4e7;
            border-radius: 8px;
            font-size: 14px;
            background-color: white;
        }
        QLineEdit:focus {
            border-color: #16a5b3;
            box-shadow: 0 0 0 3px rgba(22, 165, 179, 0.1);
        }
    )");
    connect(m_searchEdit, &QLineEdit::textChanged, this, &EmployeeLogsPanel::onSearchTextChanged);
    
    // Action filter
    QLabel *actionLabel = new QLabel("Action:");
    actionLabel->setStyleSheet("font-weight: 600; color: #2c3e50;");
    m_actionFilterCombo = new QComboBox();
    m_actionFilterCombo->addItems({"All Actions", "CREATE", "UPDATE", "DELETE", "LOGIN", "LOGOUT", "EXPORT", "IMPORT"});
    connect(m_actionFilterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &EmployeeLogsPanel::onFilterChanged);
    
    // Entity filter
    QLabel *entityLabel = new QLabel("Entity:");
    entityLabel->setStyleSheet("font-weight: 600; color: #2c3e50;");
    m_entityFilterCombo = new QComboBox();
    m_entityFilterCombo->addItems({"All Entities", "Employee", "Member", "Activity", "Equipment", "Payment"});
    connect(m_entityFilterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &EmployeeLogsPanel::onFilterChanged);
    
    // Risk level filter
    QLabel *riskLabel = new QLabel("Risk Level:");
    riskLabel->setStyleSheet("font-weight: 600; color: #2c3e50;");
    m_riskFilterCombo = new QComboBox();
    m_riskFilterCombo->addItems({"All Levels", "LOW", "MEDIUM", "HIGH", "CRITICAL"});
    connect(m_riskFilterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &EmployeeLogsPanel::onRiskLevelFilterChanged);
    
    // Date range
    QLabel *startDateLabel = new QLabel("From:");
    startDateLabel->setStyleSheet("font-weight: 600; color: #2c3e50;");
    m_startDateEdit = new QDateEdit(QDate::currentDate().addDays(-30));
    m_startDateEdit->setCalendarPopup(true);
    connect(m_startDateEdit, &QDateEdit::dateChanged, this, &EmployeeLogsPanel::onDateRangeChanged);
    
    QLabel *endDateLabel = new QLabel("To:");
    endDateLabel->setStyleSheet("font-weight: 600; color: #2c3e50;");
    m_endDateEdit = new QDateEdit(QDate::currentDate());
    m_endDateEdit->setCalendarPopup(true);
    connect(m_endDateEdit, &QDateEdit::dateChanged, this, &EmployeeLogsPanel::onDateRangeChanged);
    
    // Control buttons
    m_applyFilterButton = new QPushButton("Apply Filters");
    m_applyFilterButton->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #16a5b3, stop:1 #139aa6);
            color: white;
            border: none;
            padding: 12px 20px;
            border-radius: 8px;
            font-weight: 600;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #139aa6, stop:1 #0f858f);
        }
    )");
    connect(m_applyFilterButton, &QPushButton::clicked, this, &EmployeeLogsPanel::applyFilters);
    
    m_clearFilterButton = new QPushButton("Clear Filters");
    m_clearFilterButton->setStyleSheet(R"(
        QPushButton {
            background-color: rgba(22, 165, 179, 0.1);
            color: #16a5b3;
            border: 2px solid #16a5b3;
            padding: 12px 20px;
            border-radius: 8px;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: rgba(22, 165, 179, 0.2);
        }
    )");
    connect(m_clearFilterButton, &QPushButton::clicked, this, &EmployeeLogsPanel::clearFilters);
    
    m_exportButton = new QPushButton("📄 Export Logs");
    m_exportButton->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #27ae60, stop:1 #229954);
            color: white;
            border: none;
            padding: 12px 20px;
            border-radius: 8px;
            font-weight: 600;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #229954, stop:1 #1e8449);
        }
    )");
    connect(m_exportButton, &QPushButton::clicked, this, &EmployeeLogsPanel::exportLogs);
    
    // Auto-refresh checkbox
    m_autoRefreshCheckBox = new QCheckBox("Auto-refresh (30s)");
    m_autoRefreshCheckBox->setChecked(m_autoRefreshEnabled);
    connect(m_autoRefreshCheckBox, &QCheckBox::toggled, this, &EmployeeLogsPanel::onAutoRefreshToggled);
    
    // View toggle buttons
    m_tableToggleButton = new QPushButton("📋 Table View");
    m_tableToggleButton->setCheckable(true);
    m_tableToggleButton->setChecked(true);
    
    m_timelineToggleButton = new QPushButton("📅 Timeline View");
    m_timelineToggleButton->setCheckable(true);
    
    // Layout filters
    filterGroupLayout->addWidget(searchLabel, 0, 0);
    filterGroupLayout->addWidget(m_searchEdit, 0, 1, 1, 3);
    
    filterGroupLayout->addWidget(actionLabel, 1, 0);
    filterGroupLayout->addWidget(m_actionFilterCombo, 1, 1);
    filterGroupLayout->addWidget(entityLabel, 1, 2);
    filterGroupLayout->addWidget(m_entityFilterCombo, 1, 3);
    
    filterGroupLayout->addWidget(riskLabel, 2, 0);
    filterGroupLayout->addWidget(m_riskFilterCombo, 2, 1);
    filterGroupLayout->addWidget(startDateLabel, 2, 2);
    filterGroupLayout->addWidget(m_startDateEdit, 2, 3);
    
    filterGroupLayout->addWidget(endDateLabel, 3, 0);
    filterGroupLayout->addWidget(m_endDateEdit, 3, 1);
    filterGroupLayout->addWidget(m_autoRefreshCheckBox, 3, 2);
    
    filterGroupLayout->addWidget(m_applyFilterButton, 4, 0);
    filterGroupLayout->addWidget(m_clearFilterButton, 4, 1);
    filterGroupLayout->addWidget(m_exportButton, 4, 2);
    
    filterGroupLayout->addWidget(m_tableToggleButton, 4, 3);
    filterGroupLayout->addWidget(m_timelineToggleButton, 5, 3);
    
    m_filterLayout->addWidget(m_filterGroup);
    m_mainSplitter->addWidget(m_filterWidget);
}

void EmployeeLogsPanel::setupTable()
{
    m_tableWidget = new QWidget();
    m_tableLayout = new QVBoxLayout(m_tableWidget);
    
    // Create table
    m_logsTable = new QTableWidget();
    m_logsTable->setColumnCount(9);
    QStringList headers = {
        "Log ID", "Timestamp", "User", "Action", "Entity", 
        "Target ID", "Risk Level", "Status", "Description"
    };
    m_logsTable->setHorizontalHeaderLabels(headers);
    
    // Table styling
    setTableStyle();
    
    // Enable sorting and selection
    m_logsTable->setSortingEnabled(true);
    m_logsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_logsTable->setAlternatingRowColors(true);
    
    // Context menu
    m_logsTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_logsTable, &QTableWidget::customContextMenuRequested, 
            this, &EmployeeLogsPanel::showContextMenu);
    
    // Selection changed
    connect(m_logsTable, &QTableWidget::itemSelectionChanged,
            this, &EmployeeLogsPanel::onTableSelectionChanged);
    
    // Double-click for details
    connect(m_logsTable, &QTableWidget::cellDoubleClicked,
            this, &EmployeeLogsPanel::showLogDetails);
    
    m_tableLayout->addWidget(m_logsTable);
    m_mainSplitter->addWidget(m_tableWidget);
}

void EmployeeLogsPanel::setupTimeline()
{
    m_timelineWidget = new QWidget();
    m_timelineLayout = new QVBoxLayout(m_timelineWidget);
    
    // Timeline scroll area
    m_timelineScrollArea = new QScrollArea();
    m_timelineScrollArea->setWidgetResizable(true);
    m_timelineScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_timelineScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    m_timelineContent = new QWidget();
    m_timelineScrollArea->setWidget(m_timelineContent);
    
    m_timelineLayout->addWidget(m_timelineScrollArea);
    
    // Initially hidden
    m_timelineWidget->setVisible(false);
    m_mainSplitter->addWidget(m_timelineWidget);
}

void EmployeeLogsPanel::setupRiskAssessment()
{
    m_riskWidget = new QWidget();
    m_riskLayout = new QVBoxLayout(m_riskWidget);
    
    m_riskGroup = new QGroupBox("⚠️ Risk Assessment & Security Alerts");
    setCardStyle(m_riskGroup, "#e74c3c");
    QVBoxLayout *riskGroupLayout = new QVBoxLayout(m_riskGroup);
    
    m_riskAnalysisText = new QTextEdit();
    m_riskAnalysisText->setMaximumHeight(150);
    m_riskAnalysisText->setReadOnly(true);
    m_riskAnalysisText->setStyleSheet(R"(
        QTextEdit {
            background-color: #fff5f5;
            border: 1px solid #feb2b2;
            border-radius: 8px;
            padding: 12px;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 14px;
        }
    )");
    
    riskGroupLayout->addWidget(m_riskAnalysisText);
    m_riskLayout->addWidget(m_riskGroup);
    m_mainSplitter->addWidget(m_riskWidget);
}

void EmployeeLogsPanel::setupInsights()
{
    m_insightsGroup = new QGroupBox("💡 Insights & Recommendations");
    setCardStyle(m_insightsGroup, "#9b59b6");
    QVBoxLayout *insightsGroupLayout = new QVBoxLayout(m_insightsGroup);
    
    m_insightsText = new QTextEdit();
    m_insightsText->setMaximumHeight(120);
    m_insightsText->setReadOnly(true);
    m_insightsText->setStyleSheet(R"(
        QTextEdit {
            background-color: #f8f9fa;
            border: 1px solid #dee2e6;
            border-radius: 8px;
            padding: 12px;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 14px;
        }
    )");
    
    insightsGroupLayout->addWidget(m_insightsText);
    m_riskLayout->addWidget(m_insightsGroup);
}

// Core logging functionality
void EmployeeLogsPanel::logAction(const QString &action, const QString &entityType, 
                                 const QString &entityId, const QString &beforeData, 
                                 const QString &afterData, const QString &description)
{
    QMutexLocker locker(&s_logMutex);
    
    AuditLogEntry entry;
    entry.logId = generateLogId();
    entry.timestamp = QDateTime::currentDateTime();
    entry.userId = getCurrentUserId();
    entry.userName = getCurrentUserName();
    entry.userRole = getCurrentUserRole();
    entry.action = action;
    entry.entityType = entityType;
    entry.entityId = entityId;
    entry.beforeData = beforeData;
    entry.afterData = afterData;
    entry.sessionId = getCurrentSessionId();
    entry.riskLevel = EmployeeLogsPanel::formatRiskLevel(QString::number(static_cast<int>(assessRisk(action, entityType, entry.userId, entry.timestamp))));
    entry.success = true; // Assume success unless explicitly set otherwise
    entry.description = description.isEmpty() ? 
        QString("%1 %2 %3").arg(action, entityType, entityId) : description;
    
    writeLogEntry(entry);
    
    qDebug() << "📝 Logged action:" << action << "on" << entityType << entityId 
             << "by" << entry.userName << "Risk:" << entry.riskLevel;
}

// Static helper methods
QString EmployeeLogsPanel::generateLogId()
{
    return QUuid::createUuid().toString(QUuid::WithoutBraces).left(8);
}

QString EmployeeLogsPanel::getCurrentUserId()
{
    // TODO: Get from authentication system
    return "admin01";
}

QString EmployeeLogsPanel::getCurrentUserName()
{
    // TODO: Get from authentication system
    return "System Administrator";
}

QString EmployeeLogsPanel::getCurrentUserRole()
{
    // TODO: Get from authentication system
    return "Admin";
}

QString EmployeeLogsPanel::getCurrentSessionId()
{
    // TODO: Get from authentication system
    static QString sessionId = QUuid::createUuid().toString(QUuid::WithoutBraces);
    return sessionId;
}



void EmployeeLogsPanel::writeLogEntry(const AuditLogEntry &entry)
{
    QString logFilePath = getLogsFilePath();
    QFile file(logFilePath);
    
    // Create logs directory if it doesn't exist
    QFileInfo fileInfo(logFilePath);
    QDir().mkpath(fileInfo.absolutePath());
    
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&file);
        
        // Write as JSON line
        QJsonObject jsonEntry;
        jsonEntry["logId"] = entry.logId;
        jsonEntry["timestamp"] = entry.timestamp.toString(Qt::ISODate);
        jsonEntry["userId"] = entry.userId;
        jsonEntry["userName"] = entry.userName;
        jsonEntry["userRole"] = entry.userRole;
        jsonEntry["action"] = entry.action;
        jsonEntry["entityType"] = entry.entityType;
        jsonEntry["entityId"] = entry.entityId;
        jsonEntry["beforeData"] = entry.beforeData;
        jsonEntry["afterData"] = entry.afterData;
        jsonEntry["sessionId"] = entry.sessionId;
        jsonEntry["riskLevel"] = entry.riskLevel;
        jsonEntry["success"] = entry.success;
        jsonEntry["errorMessage"] = entry.errorMessage;
        jsonEntry["description"] = entry.description;
        
        QJsonDocument doc(jsonEntry);
        stream << doc.toJson(QJsonDocument::Compact) << "\n";
        file.close();
        
        // Check if log rotation is needed
        rotateLogsIfNeeded();
    } else {
        qWarning() << "❌ Failed to write to audit log file:" << logFilePath;
    }
}

QString EmployeeLogsPanel::getLogsFilePath()
{
    // Navigate backwards from build directory to source project directory
    QString buildDir = QCoreApplication::applicationDirPath();
    QDir dir(buildDir);
    
    // Navigate backwards: build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/ -> build/ -> project/
    dir.cdUp();  // Go up from Debug to build directory
    dir.cdUp();  // Go up from build to project root directory
    dir.cdUp();
    
    QString projectRoot = dir.absolutePath();
    QString logsDir = projectRoot + "/logs";
    
    // Create logs directory if it doesn't exist
    QDir().mkpath(logsDir);
    
    QString fileName = QString("employee_audit_%1%2")
                      .arg(QDate::currentDate().toString("yyyy-MM-dd"))
                      .arg(LOG_FILE_EXTENSION);
    
    qDebug() << "📂 Build dir:" << buildDir;
    qDebug() << "📂 Project root:" << projectRoot;
    qDebug() << "📂 Logs dir:" << logsDir;
    
    return logsDir + "/" + fileName;
}

void EmployeeLogsPanel::rotateLogsIfNeeded()
{
    QString currentLogFile = getLogsFilePath();
    QFileInfo fileInfo(currentLogFile);
    
    // Check file size (rotate if > 10MB)
    if (fileInfo.exists() && fileInfo.size() > 10 * 1024 * 1024) {
        QString archiveDir = fileInfo.absolutePath() + "/" + ARCHIVE_FOLDER_NAME;
        QDir().mkpath(archiveDir);
        
        QString archiveName = QString("employee_audit_%1_%2%3")
                             .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss"))
                             .arg("rotated")
                             .arg(LOG_FILE_EXTENSION);
        
        QString archivePath = archiveDir + "/" + archiveName;
        
        if (QFile::copy(currentLogFile, archivePath)) {
            QFile::remove(currentLogFile);
            qDebug() << "🔄 Log file rotated to:" << archivePath;
        }
    }
}

EmployeeLogsPanel::RiskLevel EmployeeLogsPanel::assessRisk(const QString &action, const QString &entityType, 
                                                          const QString &userId, const QDateTime &timestamp)
{
    // Simple risk assessment logic
    if (action == "DELETE" && entityType == "Employee") {
        return CRITICAL;
    } else if (action == "UPDATE" && entityType == "Employee") {
        return MEDIUM;
    } else if (action == "LOGIN" && timestamp.time().hour() < 6) {
        return HIGH; // Login outside business hours
    } else if (action == "CREATE") {
        return LOW;
    }
    
    return LOW;
}

void EmployeeLogsPanel::loadLogsFromFile()
{
    m_logEntries.clear();
    
    QString logFilePath = getLogsFilePath();
    QFile file(logFilePath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "📂 No existing log file found, starting fresh";
        return;
    }
    
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
        if (doc.isNull()) continue;
        
        QJsonObject jsonEntry = doc.object();
        
        AuditLogEntry entry;
        entry.logId = jsonEntry["logId"].toString();
        entry.timestamp = QDateTime::fromString(jsonEntry["timestamp"].toString(), Qt::ISODate);
        entry.userId = jsonEntry["userId"].toString();
        entry.userName = jsonEntry["userName"].toString();
        entry.userRole = jsonEntry["userRole"].toString();
        entry.action = jsonEntry["action"].toString();
        entry.entityType = jsonEntry["entityType"].toString();
        entry.entityId = jsonEntry["entityId"].toString();
        entry.beforeData = jsonEntry["beforeData"].toString();
        entry.afterData = jsonEntry["afterData"].toString();
        entry.sessionId = jsonEntry["sessionId"].toString();
        entry.riskLevel = jsonEntry["riskLevel"].toString();
        entry.success = jsonEntry["success"].toBool();
        entry.errorMessage = jsonEntry["errorMessage"].toString();
        entry.description = jsonEntry["description"].toString();
        
        m_logEntries.append(entry);
    }
    
    file.close();
    qDebug() << "📊 Loaded" << m_logEntries.size() << "log entries";
}

void EmployeeLogsPanel::updateDashboard()
{
    if (m_logEntries.isEmpty()) {
        m_totalLogsLabel->setText("0");
        m_todayActivityLabel->setText("0");
        m_riskAlertsLabel->setText("0");
        m_lastActivityLabel->setText("No activity");
        return;
    }
    
    // Total logs
    m_totalLogsLabel->setText(QString::number(m_logEntries.size()));
    animateCard(m_totalLogsCard);
    
    // Today's activity
    QDate today = QDate::currentDate();
    int todayCount = 0;
    for (const auto &entry : m_logEntries) {
        if (entry.timestamp.date() == today) {
            todayCount++;
        }
    }
    m_todayActivityLabel->setText(QString::number(todayCount));
    animateCard(m_todayActivityCard);
    
    // Risk alerts
    int riskCount = 0;
    for (const auto &entry : m_logEntries) {
        if (entry.riskLevel == "HIGH" || entry.riskLevel == "CRITICAL") {
            riskCount++;
        }
    }
    m_riskAlertsLabel->setText(QString::number(riskCount));
    animateCard(m_riskAlertsCard);
    
    // Last activity
    if (!m_logEntries.isEmpty()) {
        const auto &lastEntry = m_logEntries.last();
        QString lastActivity = QString("%1 %2 by %3")
                              .arg(getActionIcon(lastEntry.action))
                              .arg(lastEntry.action)
                              .arg(lastEntry.userName);
        m_lastActivityLabel->setText(lastActivity);
        animateCard(m_lastActivityCard);
    }
}

void EmployeeLogsPanel::updateTable()
{
    if (!m_logsTable) return;
    
    m_logsTable->setRowCount(m_filteredEntries.size());
    
    for (int i = 0; i < m_filteredEntries.size(); ++i) {
        const auto &entry = m_filteredEntries[i];
        
        // Set table items
        m_logsTable->setItem(i, 0, new QTableWidgetItem(entry.logId));
        m_logsTable->setItem(i, 1, new QTableWidgetItem(formatTimestamp(entry.timestamp)));
        m_logsTable->setItem(i, 2, new QTableWidgetItem(entry.userName));
        
        // Action with icon
        QTableWidgetItem *actionItem = new QTableWidgetItem(getActionIcon(entry.action) + " " + entry.action);
        m_logsTable->setItem(i, 3, actionItem);
        
        m_logsTable->setItem(i, 4, new QTableWidgetItem(entry.entityType));
        m_logsTable->setItem(i, 5, new QTableWidgetItem(entry.entityId));
        
        // Risk level with color coding
        QTableWidgetItem *riskItem = new QTableWidgetItem(getRiskIcon(entry.riskLevel) + " " + entry.riskLevel);
        if (entry.riskLevel == "CRITICAL") {
            riskItem->setBackground(QColor("#ffebee"));
            riskItem->setForeground(QColor("#d32f2f"));
        } else if (entry.riskLevel == "HIGH") {
            riskItem->setBackground(QColor("#fff3e0"));
            riskItem->setForeground(QColor("#f57c00"));
        } else if (entry.riskLevel == "MEDIUM") {
            riskItem->setBackground(QColor("#fff8e1"));
            riskItem->setForeground(QColor("#fbc02d"));
        }
        m_logsTable->setItem(i, 6, riskItem);
        
        // Status
        QString statusText = entry.success ? "✅ Success" : "❌ Failed";
        QTableWidgetItem *statusItem = new QTableWidgetItem(statusText);
        statusItem->setForeground(entry.success ? QColor("#27ae60") : QColor("#e74c3c"));
        m_logsTable->setItem(i, 7, statusItem);
        
        m_logsTable->setItem(i, 8, new QTableWidgetItem(entry.description));
    }
    
    // Auto-resize columns
    m_logsTable->resizeColumnsToContents();
    m_logsTable->horizontalHeader()->setStretchLastSection(true);
}

void EmployeeLogsPanel::updateRiskAssessment()
{
    if (!m_riskAnalysisText) return;
    
    analyzeActivityPatterns();
    detectAnomalies();
    generateRiskReport();
}

void EmployeeLogsPanel::updateInsights()
{
    if (!m_insightsText || m_logEntries.isEmpty()) {
        m_insightsText->setHtml("<p><b>💡 No insights available</b></p><p>More data needed for analysis.</p>");
        return;
    }
    
    QString insights = "<h3>📈 System Activity Insights</h3>";
    
    // Most active users
    QMap<QString, int> userActivity;
    for (const auto &entry : m_logEntries) {
        userActivity[entry.userName]++;
    }
    
    QString mostActiveUser;
    int maxActivity = 0;
    for (auto it = userActivity.begin(); it != userActivity.end(); ++it) {
        if (it.value() > maxActivity) {
            maxActivity = it.value();
            mostActiveUser = it.key();
        }
    }
    
    insights += QString("<p><b>Most Active User:</b> %1 (%2 actions)</p>").arg(mostActiveUser).arg(maxActivity);
    
    // Peak activity time
    QMap<int, int> hourlyActivity;
    for (const auto &entry : m_logEntries) {
        hourlyActivity[entry.timestamp.time().hour()]++;
    }
    
    int peakHour = 0;
    int peakActivity = 0;
    for (auto it = hourlyActivity.begin(); it != hourlyActivity.end(); ++it) {
        if (it.value() > peakActivity) {
            peakActivity = it.value();
            peakHour = it.key();
        }
    }
    
    insights += QString("<p><b>Peak Activity Hour:</b> %1:00 (%2 actions)</p>").arg(peakHour).arg(peakActivity);
    
    // Recommendations
    insights += "<p><b>🎯 Recommendations:</b></p>";
    insights += "<ul>";
    if (userActivity.size() == 1) {
        insights += "<li>Consider adding more administrative users for better workload distribution</li>";
    }
    if (peakHour < 8 || peakHour > 18) {
        insights += "<li>⚠️ Unusual activity detected outside business hours - review security protocols</li>";
    }
    insights += "<li>Regular audit log reviews are recommended for security compliance</li>";
    insights += "</ul>";
    
    m_insightsText->setHtml(insights);
}

void EmployeeLogsPanel::applyFilters()
{
    m_filteredEntries.clear();
    
    QString searchText = m_searchEdit->text().toLower();
    QString actionFilter = m_actionFilterCombo->currentText();
    QString entityFilter = m_entityFilterCombo->currentText();
    QString riskFilter = m_riskFilterCombo->currentText();
    QDate startDate = m_startDateEdit->date();
    QDate endDate = m_endDateEdit->date();
    
    for (const auto &entry : m_logEntries) {
        // Date range filter
        if (entry.timestamp.date() < startDate || entry.timestamp.date() > endDate) {
            continue;
        }
        
        // Action filter
        if (actionFilter != "All Actions" && entry.action != actionFilter) {
            continue;
        }
        
        // Entity filter
        if (entityFilter != "All Entities" && entry.entityType != entityFilter) {
            continue;
        }
        
        // Risk filter
        if (riskFilter != "All Levels" && entry.riskLevel != riskFilter) {
            continue;
        }
        
        // Search filter
        if (!searchText.isEmpty()) {
            QString searchableText = (entry.description + " " + entry.userName + " " + 
                                    entry.action + " " + entry.entityType).toLower();
            if (!searchableText.contains(searchText)) {
                continue;
            }
        }
        
        m_filteredEntries.append(entry);
    }
    
    updateTable();
    qDebug() << "🔍 Applied filters, showing" << m_filteredEntries.size() << "of" << m_logEntries.size() << "entries";
}

// Slot implementations
void EmployeeLogsPanel::refreshLogs()
{
    loadLogsFromFile();
    applyFilters();
    updateDashboard();
    updateRiskAssessment();
    updateInsights();
    qDebug() << "🔄 Logs refreshed";
}

void EmployeeLogsPanel::exportLogs()
{
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Export Audit Logs", 
        QString("audit_logs_%1.pdf").arg(QDate::currentDate().toString("yyyy-MM-dd")),
        "PDF Files (*.pdf);;CSV Files (*.csv);;JSON Files (*.json)");
    
    if (fileName.isEmpty()) return;
    
    QFileInfo fileInfo(fileName);
    QString extension = fileInfo.suffix().toLower();
    
    if (extension == "pdf") {
        exportToPDF();
    } else if (extension == "csv") {
        exportToCSV();
    } else if (extension == "json") {
        exportToJSON();
    }
    
    QMessageBox::information(this, "Export Complete", 
        QString("Audit logs exported successfully to:\n%1").arg(fileName));
}

void EmployeeLogsPanel::clearFilters()
{
    m_searchEdit->clear();
    m_actionFilterCombo->setCurrentIndex(0);
    m_entityFilterCombo->setCurrentIndex(0);
    m_riskFilterCombo->setCurrentIndex(0);
    m_startDateEdit->setDate(QDate::currentDate().addDays(-30));
    m_endDateEdit->setDate(QDate::currentDate());
    
    applyFilters();
}

void EmployeeLogsPanel::showLogDetails(int row, int column)
{
    Q_UNUSED(column)
    
    if (row < 0 || row >= m_filteredEntries.size()) return;
    
    const auto &entry = m_filteredEntries[row];
    showLogEntryDetails(entry);
}

void EmployeeLogsPanel::onFilterChanged()
{
    applyFilters();
}

void EmployeeLogsPanel::onDateRangeChanged()
{
    applyFilters();
}

void EmployeeLogsPanel::onSearchTextChanged()
{
    applyFilters();
}

void EmployeeLogsPanel::onTableSelectionChanged()
{
    // Update risk assessment based on selected entries
    updateRiskAssessment();
}

void EmployeeLogsPanel::onAutoRefreshToggled(bool enabled)
{
    m_autoRefreshEnabled = enabled;
    
    if (enabled) {
        m_refreshTimer->start();
        m_riskAssessmentTimer->start();
    } else {
        m_refreshTimer->stop();
        m_riskAssessmentTimer->stop();
    }
}

void EmployeeLogsPanel::onRiskLevelFilterChanged()
{
    applyFilters();
}

void EmployeeLogsPanel::showContextMenu(const QPoint &pos)
{
    Q_UNUSED(pos)
    // TODO: Implement context menu for log operations
}

void EmployeeLogsPanel::highlightSuspiciousActivity()
{
    // TODO: Implement suspicious activity detection and highlighting
}

// Utility methods
void EmployeeLogsPanel::setTableStyle()
{
    if (!m_logsTable) return;
    
    m_logsTable->setStyleSheet(R"(
        QTableWidget {
            background-color: white;
            gridline-color: #e6eef0;
            border: 2px solid #16a5b3;
            border-radius: 12px;
            selection-background-color: rgba(22, 165, 179, 0.14);
            selection-color: #2c3e50;
        }
        QHeaderView::section {
            background-color: #16a5b3;
            color: white;
            padding: 12px 8px;
            border: none;
            font-weight: 600;
            border-right: 1px solid rgba(255,255,255,0.25);
        }
        QTableWidget::item:alternate {
            background: rgba(22, 165, 179, 0.03);
        }
        QTableWidget::item:selected {
            background: rgba(22, 165, 179, 0.14);
            color: #2c3e50;
        }
        QTableCornerButton::section {
            background-color: #16a5b3;
            border: none;
        }
    )");
}

void EmployeeLogsPanel::setCardStyle(QGroupBox *card, const QString &color)
{
    if (!card) return;
    
    card->setStyleSheet(QString(R"(
        QGroupBox {
            background-color: white;
            border: 2px solid %1;
            border-radius: 16px;
            padding: 20px 10px 10px 10px;
            font-size: 16px;
            font-weight: 600;
            color: %1;
            margin-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top center;
            padding: 0 10px;
            background-color: white;
        }
    )").arg(color));
}

QString EmployeeLogsPanel::formatTimestamp(const QDateTime &timestamp)
{
    return timestamp.toString("yyyy-MM-dd hh:mm:ss");
}

QString EmployeeLogsPanel::formatRiskLevel(const QString &riskLevel)
{
    if (riskLevel == "0") return "LOW";
    if (riskLevel == "1") return "MEDIUM";
    if (riskLevel == "2") return "HIGH";
    if (riskLevel == "3") return "CRITICAL";
    return riskLevel;
}

QString EmployeeLogsPanel::getActionIcon(const QString &action)
{
    if (action == "CREATE") return "➕";
    if (action == "UPDATE") return "✏️";
    if (action == "DELETE") return "🗑️";
    if (action == "LOGIN") return "🔑";
    if (action == "LOGOUT") return "🚪";
    if (action == "EXPORT") return "📤";
    if (action == "IMPORT") return "📥";
    return "📋";
}

QString EmployeeLogsPanel::getRiskIcon(const QString &riskLevel)
{
    if (riskLevel == "CRITICAL") return "🔴";
    if (riskLevel == "HIGH") return "🟠";
    if (riskLevel == "MEDIUM") return "🟡";
    return "🟢";
}

void EmployeeLogsPanel::showLogEntryDetails(const AuditLogEntry &entry)
{
    QString details = QString(R"(
        <h2>📋 Audit Log Details</h2>
        <table style="width: 100%; border-collapse: collapse;">
        <tr><td style="font-weight: bold;">Log ID:</td><td>%1</td></tr>
        <tr><td style="font-weight: bold;">Timestamp:</td><td>%2</td></tr>
        <tr><td style="font-weight: bold;">User:</td><td>%3 (%4)</td></tr>
        <tr><td style="font-weight: bold;">Action:</td><td>%5 %6</td></tr>
        <tr><td style="font-weight: bold;">Entity:</td><td>%7 (ID: %8)</td></tr>
        <tr><td style="font-weight: bold;">Risk Level:</td><td>%9 %10</td></tr>
        <tr><td style="font-weight: bold;">Status:</td><td>%11</td></tr>
        <tr><td style="font-weight: bold;">Session ID:</td><td>%12</td></tr>
        <tr><td style="font-weight: bold;">Description:</td><td>%13</td></tr>
        </table>
    )")
    .arg(entry.logId)
    .arg(formatTimestamp(entry.timestamp))
    .arg(entry.userName, entry.userRole)
    .arg(getActionIcon(entry.action), entry.action)
    .arg(entry.entityType, entry.entityId)
    .arg(getRiskIcon(entry.riskLevel), entry.riskLevel)
    .arg(entry.success ? "✅ Success" : "❌ Failed")
    .arg(entry.sessionId)
    .arg(entry.description);
    
    if (!entry.beforeData.isEmpty() || !entry.afterData.isEmpty()) {
        details += "<h3>📊 Data Changes</h3>";
        if (!entry.beforeData.isEmpty()) {
            details += QString("<p><b>Before:</b><br><pre>%1</pre></p>").arg(entry.beforeData);
        }
        if (!entry.afterData.isEmpty()) {
            details += QString("<p><b>After:</b><br><pre>%1</pre></p>").arg(entry.afterData);
        }
    }
    
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Audit Log Entry Details");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(details);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void EmployeeLogsPanel::animateCard(QGroupBox *card)
{
    if (!card) return;
    
    QPropertyAnimation *animation = new QPropertyAnimation(card, "geometry");
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    
    QRect startRect = card->geometry();
    QRect endRect = startRect;
    endRect.adjust(-2, -2, 2, 2);
    
    animation->setStartValue(startRect);
    animation->setKeyValueAt(0.5, endRect);
    animation->setEndValue(startRect);
    
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

// Risk assessment and analytics methods
void EmployeeLogsPanel::analyzeActivityPatterns()
{
    // TODO: Implement pattern analysis
}

void EmployeeLogsPanel::detectAnomalies()
{
    // TODO: Implement anomaly detection
}

void EmployeeLogsPanel::generateRiskReport()
{
    if (!m_riskAnalysisText) return;
    
    QString report = "<h3>⚠️ Risk Assessment Report</h3>";
    
    QStringList highRiskActivities = getHighRiskActivities();
    if (highRiskActivities.isEmpty()) {
        report += "<p style='color: #27ae60;'><b>✅ No high-risk activities detected</b></p>";
        report += "<p>System activity appears normal. Continue monitoring.</p>";
    } else {
        report += "<p style='color: #e74c3c;'><b>🚨 High-risk activities detected:</b></p>";
        report += "<ul>";
        for (const QString &activity : highRiskActivities) {
            report += QString("<li>%1</li>").arg(activity);
        }
        report += "</ul>";
        report += "<p><b>Recommended actions:</b></p>";
        report += "<ul>";
        report += "<li>Review the flagged activities immediately</li>";
        report += "<li>Verify user permissions and access levels</li>";
        report += "<li>Consider implementing additional security measures</li>";
        report += "</ul>";
    }
    
    m_riskAnalysisText->setHtml(report);
}

QStringList EmployeeLogsPanel::getHighRiskActivities()
{
    QStringList highRiskActivities;
    
    for (const auto &entry : m_logEntries) {
        if (entry.riskLevel == "HIGH" || entry.riskLevel == "CRITICAL") {
            QString activity = QString("%1 %2 %3 by %4 at %5")
                              .arg(entry.action)
                              .arg(entry.entityType)
                              .arg(entry.entityId)
                              .arg(entry.userName)
                              .arg(formatTimestamp(entry.timestamp));
            highRiskActivities.append(activity);
        }
    }
    
    return highRiskActivities;
}

// Export methods (stub implementations)
void EmployeeLogsPanel::exportToPDF()
{
    // TODO: Implement PDF export
    qDebug() << "📄 PDF export not yet implemented";
}

void EmployeeLogsPanel::exportToCSV()
{
    // TODO: Implement CSV export
    qDebug() << "📊 CSV export not yet implemented";
}

void EmployeeLogsPanel::exportToJSON()
{
    // TODO: Implement JSON export
    qDebug() << "📋 JSON export not yet implemented";
}