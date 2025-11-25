#include "activitypanel.h"
#include <QApplication>
#include <QStandardPaths>
#include <QFileInfo>

ActivityPanel::ActivityPanel(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(nullptr)
    , m_mainSplitter(nullptr)
    , m_registrations()
    , m_refreshTimer(new QTimer(this))
    , m_nodeProcess(new QProcess(this))
{
    setupUI();
    
    // Setup timer for periodic refresh
    m_refreshTimer->setInterval(300000); // 5 minutes
    connect(m_refreshTimer, &QTimer::timeout, this, &ActivityPanel::onRefreshTimer);
    
    // Setup Node.js process
    connect(m_nodeProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &ActivityPanel::onNodeJSFinished);
    connect(m_nodeProcess, &QProcess::errorOccurred, this, &ActivityPanel::onNodeJSError);
    
    // Load existing data if available
    if (formsDataExists()) {
        loadDataFromJSON();
        updateDashboard();
        updateTable();
        updateAnalytics();
    }
    
    qDebug() << "✅ ActivityPanel initialized successfully";
}

void ActivityPanel::setupUI()
{
    // Main layout
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(10);
    
    // Create main splitter for responsive layout
    m_mainSplitter = new QSplitter(Qt::Vertical, this);
    m_mainLayout->addWidget(m_mainSplitter);
    
    // Setup sections
    setupDashboard();
    setupTable();
    setupAnalytics();
    
    // Configure splitter sizes
    m_mainSplitter->setSizes({200, 300, 250}); // Dashboard, Table, Analytics
    m_mainSplitter->setStretchFactor(0, 0); // Dashboard fixed size
    m_mainSplitter->setStretchFactor(1, 1); // Table takes most space
    m_mainSplitter->setStretchFactor(2, 0); // Analytics fixed size
    
    setStyleSheet(R"(
        QGroupBox {
            font-weight: bold;
            border: 2px solid #cccccc;
            border-radius: 8px;
            margin-top: 1ex;
            padding-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 10px 0 10px;
        }
    )");
}

void ActivityPanel::setupDashboard()
{
    // Dashboard widget
    m_dashboardWidget = new QWidget();
    m_dashboardLayout = new QGridLayout(m_dashboardWidget);
    m_dashboardLayout->setSpacing(15);
    
    // Create dashboard cards (removed Active Members card)
    m_totalResponsesCard = new QGroupBox("📊 Total Responses");
    m_latestActivityCard = new QGroupBox("🎯 Latest Activity");
    m_lastSyncCard = new QGroupBox("⏱️ Last Sync");
    
    // Setup card layouts and labels
    QVBoxLayout *totalLayout = new QVBoxLayout(m_totalResponsesCard);
    m_totalResponsesLabel = new QLabel("0");
    m_totalResponsesLabel->setAlignment(Qt::AlignCenter);
    m_totalResponsesLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2E86AB;");
    totalLayout->addWidget(m_totalResponsesLabel);
    
    // Active Members card removed
    
    QVBoxLayout *latestLayout = new QVBoxLayout(m_latestActivityCard);
    m_latestActivityLabel = new QLabel("None");
    m_latestActivityLabel->setAlignment(Qt::AlignCenter);
    m_latestActivityLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #F18F01;");
    m_latestActivityLabel->setWordWrap(true);
    latestLayout->addWidget(m_latestActivityLabel);
    
    QVBoxLayout *syncLayout = new QVBoxLayout(m_lastSyncCard);
    m_lastSyncLabel = new QLabel("Never");
    m_lastSyncLabel->setAlignment(Qt::AlignCenter);
    m_lastSyncLabel->setStyleSheet("font-size: 14px; color: #666666;");
    m_lastSyncLabel->setWordWrap(true);
    syncLayout->addWidget(m_lastSyncLabel);
    
    // Apply card styling
    setCardStyle(m_totalResponsesCard);
    setCardStyle(m_latestActivityCard);
    setCardStyle(m_lastSyncCard);
    
    // Sync button
    m_syncButton = new QPushButton("🔄 Sync Data");
    m_syncButton->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            border: none;
            color: white;
            padding: 12px 24px;
            text-align: center;
            font-size: 16px;
            font-weight: bold;
            border-radius: 6px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
        QPushButton:pressed {
            background-color: #3d8b40;
        }
        QPushButton:disabled {
            background-color: #cccccc;
            color: #666666;
        }
    )");
    connect(m_syncButton, &QPushButton::clicked, this, &ActivityPanel::onSyncData);
    
    // Progress bar
    m_syncProgressBar = new QProgressBar();
    m_syncProgressBar->setVisible(false);
    m_syncProgressBar->setStyleSheet(R"(
        QProgressBar {
            border: 2px solid #cccccc;
            border-radius: 5px;
            text-align: center;
        }
        QProgressBar::chunk {
            background-color: #4CAF50;
            border-radius: 3px;
        }
    )");
    
    // Layout dashboard (removed Active Members card)
    m_dashboardLayout->addWidget(m_totalResponsesCard, 0, 0);
    m_dashboardLayout->addWidget(m_latestActivityCard, 0, 1);
    m_dashboardLayout->addWidget(m_lastSyncCard, 0, 2);
    m_dashboardLayout->addWidget(m_syncButton, 1, 0, 1, 2);
    m_dashboardLayout->addWidget(m_syncProgressBar, 1, 1, 1, 2);
    
    m_mainSplitter->addWidget(m_dashboardWidget);
}

void ActivityPanel::setupTable()
{
    // Table widget container
    m_tableWidget = new QWidget();
    m_tableLayout = new QVBoxLayout(m_tableWidget);
    
    // Table controls
    m_tableControlsWidget = new QWidget();
    m_tableControlsLayout = new QHBoxLayout(m_tableControlsWidget);
    
    // Search
    QLabel *searchLabel = new QLabel("🔍 Search:");
    m_searchEdit = new QLineEdit();
    m_searchEdit->setPlaceholderText("Search by name, email, or activity...");
    connect(m_searchEdit, &QLineEdit::textChanged, this, &ActivityPanel::applyTableFilters);
    
    // Filter
    QLabel *filterLabel = new QLabel("📂 Filter:");
    m_filterComboBox = new QComboBox();
    m_filterComboBox->addItems({"All Activities", "Music", "Cinema & Acting Lab", "Sports & Fitness Program"});
    connect(m_filterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &ActivityPanel::applyTableFilters);
    
    // Sort
    QLabel *sortLabel = new QLabel("🔄 Sort:");
    m_sortComboBox = new QComboBox();
    m_sortComboBox->addItems({"Date (Newest First)", "Date (Oldest First)", "Name (A-Z)", "Activity Type"});
    connect(m_sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &ActivityPanel::applyTableFilters);
    
    m_tableControlsLayout->addWidget(searchLabel);
    m_tableControlsLayout->addWidget(m_searchEdit, 2);
    m_tableControlsLayout->addWidget(filterLabel);
    m_tableControlsLayout->addWidget(m_filterComboBox, 1);
    m_tableControlsLayout->addWidget(sortLabel);
    m_tableControlsLayout->addWidget(m_sortComboBox, 1);
    m_tableControlsLayout->addStretch();
    
    // Table group
    m_tableGroup = new QGroupBox("📋 Event Registrations");
    QVBoxLayout *tableGroupLayout = new QVBoxLayout(m_tableGroup);
    
    // Registration table
    m_registrationTable = new QTableWidget();
    m_registrationTable->setColumnCount(8);
    QStringList headers = {"#", "Date & Time", "Name", "Email", "Activity Type", "Phone", "Age", "Payment"};
    m_registrationTable->setHorizontalHeaderLabels(headers);
    
    // Table styling
    setTableStyle();
    
    connect(m_registrationTable, &QTableWidget::itemSelectionChanged, 
            this, &ActivityPanel::onTableSelectionChanged);
    
    tableGroupLayout->addWidget(m_registrationTable);
    
    // Layout table section
    m_tableLayout->addWidget(m_tableControlsWidget);
    m_tableLayout->addWidget(m_tableGroup);
    
    m_mainSplitter->addWidget(m_tableWidget);
}

void ActivityPanel::setupAnalytics()
{
    // Analytics widget (charts removed)
    m_analyticsWidget = new QWidget();
    m_analyticsLayout = new QHBoxLayout(m_analyticsWidget);
    
    setupInsights();
    
    m_mainSplitter->addWidget(m_analyticsWidget);
}

// setupCharts method removed to avoid QtCharts dependency

void ActivityPanel::setupInsights()
{
    // Insights group
    m_insightsGroup = new QGroupBox("📈 Insights & Recommendations");
    m_insightsLayout = new QVBoxLayout(m_insightsGroup);
    
    m_insightsText = new QTextEdit();
    m_insightsText->setReadOnly(true);
    m_insightsText->setMaximumHeight(200);
    m_insightsText->setStyleSheet(R"(
        QTextEdit {
            background-color: #f8f9fa;
            border: 1px solid #dee2e6;
            border-radius: 4px;
            padding: 10px;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 14px;
            line-height: 1.4;
        }
    )");
    
    m_insightsLayout->addWidget(m_insightsText);
    m_analyticsLayout->addWidget(m_insightsGroup, 1);
}

void ActivityPanel::onSyncData()
{
    qDebug() << "🔄 Starting data sync...";
    
    // Disable sync button and show progress
    m_syncButton->setEnabled(false);
    m_syncButton->setText("Syncing...");
    m_syncProgressBar->setVisible(true);
    m_syncProgressBar->setRange(0, 0); // Indeterminate progress
    
    // Run Node.js script to extract registration data
    // Define the source directory path (where the project files are located)
    QString sourceDir = "C:/Users/Khalil/Desktop/SummerClub_Advanced";
    QString scriptPath = sourceDir + "/forms_data_extractor.js";
    QFileInfo scriptInfo(scriptPath);
    
    qDebug() << "🔍 Looking for script at:" << scriptPath;
    qDebug() << "📁 Script exists:" << scriptInfo.exists();
    
    // If not found in source directory, try current directory
    if (!scriptInfo.exists()) {
        scriptPath = QDir::currentPath() + "/forms_data_extractor.js";
        scriptInfo.setFile(scriptPath);
        qDebug() << "🔍 Trying current directory:" << scriptPath;
        qDebug() << "📁 Script exists:" << scriptInfo.exists();
    }
    
    // If still not found, try relative path from build directory
    if (!scriptInfo.exists()) {
        scriptPath = QDir::currentPath() + "/../../../forms_data_extractor.js";
        scriptInfo.setFile(scriptPath);
        qDebug() << "🔍 Trying relative path:" << scriptPath;
        qDebug() << "📁 Script exists:" << scriptInfo.exists();
    }
    
    if (!scriptInfo.exists()) {
        qDebug() << "❌ Could not find forms_data_extractor.js script in any location";
        qDebug() << "📁 Current working directory:" << QDir::currentPath();
        showSyncStatus("Script not found: forms_data_extractor.js", false);
        m_syncProgressBar->setVisible(false);
        return;
    }
    
    QStringList arguments;
    arguments << scriptInfo.absoluteFilePath();
    
    qDebug() << "📋 Running Node.js script:" << scriptInfo.absoluteFilePath();
    qDebug() << "📁 Current working directory:" << QDir::currentPath();
    qDebug() << "📁 Script working directory:" << scriptInfo.absolutePath();
    
    // Set working directory to the source directory (where credentials.json is located)
    m_nodeProcess->setWorkingDirectory(sourceDir);
    qDebug() << "📁 Node.js working directory set to:" << sourceDir;
    
    m_nodeProcess->start("node", arguments);
    
    if (!m_nodeProcess->waitForStarted()) {
        qDebug() << "❌ Failed to start Node.js process";
        showSyncStatus("Failed to start sync process", false);
        m_syncButton->setEnabled(true);
        m_syncButton->setText("🔄 Sync Data");
        m_syncProgressBar->setVisible(false);
    }
}

void ActivityPanel::onNodeJSFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "📋 Node.js process finished with exit code:" << exitCode;
    
    // Re-enable sync button
    m_syncButton->setEnabled(true);
    m_syncButton->setText("🔄 Sync Data");
    m_syncProgressBar->setVisible(false);
    
    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
        qDebug() << "✅ Node.js script completed successfully";
        
        // Load the updated data
        loadDataFromJSON();
        updateDashboard();
        updateTable();
        updateAnalytics();
        
        // Update last sync time
        m_lastSyncLabel->setText(QDateTime::currentDateTime().toString("MMM dd, hh:mm AP"));
        
        showSyncStatus("Data synchronized successfully!", true);
        
        // Start periodic refresh timer
        m_refreshTimer->start();
        
    } else {
        qDebug() << "❌ Node.js script failed";
        showSyncStatus("Sync failed. Check your internet connection and try again.", false);
    }
}

void ActivityPanel::onNodeJSError(QProcess::ProcessError error)
{
    qDebug() << "❌ Node.js process error:" << error;
    
    m_syncButton->setEnabled(true);
    m_syncButton->setText("🔄 Sync Data");
    m_syncProgressBar->setVisible(false);
    
    QString errorMsg;
    switch (error) {
        case QProcess::FailedToStart:
            errorMsg = "Failed to start Node.js. Please ensure Node.js is installed.";
            break;
        case QProcess::Crashed:
            errorMsg = "Node.js process crashed during execution.";
            break;
        case QProcess::Timedout:
            errorMsg = "Node.js process timed out.";
            break;
        default:
            errorMsg = "Unknown error occurred during sync.";
    }
    
    showSyncStatus(errorMsg, false);
}

void ActivityPanel::loadDataFromJSON()
{
    // Try to load from the registration data JSON file created by Node.js script
    // Look for JSON file in the source directory first
    QString sourceDir = "C:/Users/Khalil/Desktop/SummerClub_Advanced";
    QString jsonPath = sourceDir + "/forms_registration_data.json";
    QFileInfo jsonInfo(jsonPath);
    
    qDebug() << "🔍 Looking for JSON at:" << jsonPath;
    qDebug() << "📄 JSON exists:" << jsonInfo.exists();
    
    // If not found in source directory, try current directory
    if (!jsonInfo.exists()) {
        jsonPath = QDir::currentPath() + "/forms_registration_data.json";
        jsonInfo.setFile(jsonPath);
        qDebug() << "🔍 Trying current directory for JSON:" << jsonPath;
        qDebug() << "📄 JSON exists:" << jsonInfo.exists();
    }
    
    // Use the path we found
    jsonPath = jsonInfo.exists() ? jsonInfo.absoluteFilePath() : jsonPath;
    QFile file(jsonPath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "❌ Could not open forms_registration_data.json";
        return;
    }
    
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (doc.isNull()) {
        qDebug() << "❌ Invalid JSON in forms_registration_data.json";
        return;
    }
    
    QJsonObject root = doc.object();
    QJsonArray responses = root["responses"].toArray();
    
    m_registrations.clear();
    
    for (const QJsonValue &value : responses) {
        QJsonObject responseObj = value.toObject();
        
        ActivityRegistration reg;
        reg.sequence = responseObj["sequence"].toInt();
        reg.responseId = responseObj["responseId"].toString();
        reg.createTime = responseObj["createTime"].toString();
        reg.createTimeReadable = responseObj["createTimeReadable"].toString();
        
        // Extract registration details from JSON
        reg.name = responseObj["name"].toString();
        reg.email = responseObj["email"].toString();
        reg.activityType = responseObj["activityType"].toString();
        reg.phoneNumber = responseObj["phoneNumber"].toString();
        reg.age = responseObj["age"].toString();
        reg.paymentConfirmed = responseObj["paymentConfirmed"].toBool();
        
        m_registrations.append(reg);
    }
    
    qDebug() << "📊 Loaded" << m_registrations.size() << "registrations from JSON";
}

void ActivityPanel::updateDashboard()
{
    if (m_registrations.isEmpty()) {
        m_totalResponsesLabel->setText("0");
        m_latestActivityLabel->setText("No data");
        return;
    }
    
    // Update total responses
    m_totalResponsesLabel->setText(QString::number(m_registrations.size()));
    
    // Update latest activity
    if (!m_registrations.isEmpty()) {
        const auto &latest = m_registrations.last();
        m_latestActivityLabel->setText(latest.activityType.isEmpty() ? "Recent Registration" : latest.activityType);
    }
}

void ActivityPanel::updateTable()
{
    if (!m_registrationTable) return;
    
    m_registrationTable->setRowCount(m_registrations.size());
    
    for (int i = 0; i < m_registrations.size(); ++i) {
        const auto &reg = m_registrations[i];
        
        // Sequence number
        QTableWidgetItem *seqItem = new QTableWidgetItem(QString::number(reg.sequence));
        seqItem->setTextAlignment(Qt::AlignCenter);
        m_registrationTable->setItem(i, 0, seqItem);
        
        // Date & Time
        QString formattedDate = formatDateTime(reg.createTime);
        QTableWidgetItem *dateItem = new QTableWidgetItem(formattedDate);
        m_registrationTable->setItem(i, 1, dateItem);
        
        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem(reg.name);
        m_registrationTable->setItem(i, 2, nameItem);
        
        // Email
        QTableWidgetItem *emailItem = new QTableWidgetItem(reg.email);
        m_registrationTable->setItem(i, 3, emailItem);
        
        // Activity Type with icon
        QString activityText = getActivityIcon(reg.activityType) + " " + reg.activityType;
        QTableWidgetItem *activityItem = new QTableWidgetItem(activityText);
        m_registrationTable->setItem(i, 4, activityItem);
        
        // Phone
        QTableWidgetItem *phoneItem = new QTableWidgetItem(reg.phoneNumber);
        m_registrationTable->setItem(i, 5, phoneItem);
        
        // Age
        QTableWidgetItem *ageItem = new QTableWidgetItem(reg.age);
        ageItem->setTextAlignment(Qt::AlignCenter);
        m_registrationTable->setItem(i, 6, ageItem);
        
        // Payment status
        QString paymentText = reg.paymentConfirmed ? "✅ Confirmed" : "⏳ Pending";
        QTableWidgetItem *paymentItem = new QTableWidgetItem(paymentText);
        m_registrationTable->setItem(i, 7, paymentItem);
    }
    
    // Auto-resize columns
    m_registrationTable->resizeColumnsToContents();
    m_registrationTable->horizontalHeader()->setStretchLastSection(true);
}

void ActivityPanel::updateAnalytics()
{
    updateDashboard();
    updateTable();
    updateInsights();
}

// updateCharts method removed to avoid QtCharts dependency

void ActivityPanel::updateInsights()
{
    if (m_registrations.isEmpty()) {
        m_insightsText->setHtml("<p><b>📊 No data available</b></p><p>Click 'Sync Data' to load registration information.</p>");
        return;
    }
    
    generateInsights();
}

void ActivityPanel::generateInsights()
{
    // Count activity types
    QMap<QString, int> activityCounts;
    QMap<QString, int> ageCounts;
    
    for (const auto &reg : m_registrations) {
        if (!reg.activityType.isEmpty()) {
            activityCounts[reg.activityType]++;
        }
        if (!reg.age.isEmpty()) {
            int age = reg.age.toInt();
            if (age < 20) ageCounts["Under 20"]++;
            else if (age <= 25) ageCounts["20-25"]++;
            else ageCounts["Over 25"]++;
        }
    }
    
    QString insights = "<h3>🎯 Key Insights</h3>";
    
    // Most popular activity
    if (!activityCounts.isEmpty()) {
        auto maxActivity = std::max_element(activityCounts.begin(), activityCounts.end());
        int total = m_registrations.size();
        int percentage = (maxActivity.value() * 100) / total;
        
        insights += QString("<p><b>🏆 Most Popular Activity:</b> %1 (%2% of registrations)</p>")
                   .arg(maxActivity.key()).arg(percentage);
    }
    
    // Age distribution
    if (!ageCounts.isEmpty()) {
        auto maxAge = std::max_element(ageCounts.begin(), ageCounts.end());
        insights += QString("<p><b>👥 Primary Age Group:</b> %1 years old</p>").arg(maxAge.key());
    }
    
    // Recommendations
    insights += "<h3>💡 Recommendations</h3>";
    
    if (activityCounts.contains("Sports & Fitness Program") && 
        activityCounts["Sports & Fitness Program"] > activityCounts.size() / 2) {
        insights += "<p>• Consider expanding sports facilities and programs</p>";
    }
    
    if (activityCounts.contains("Music") && activityCounts["Music"] > 0) {
        insights += "<p>• Music programs show interest - consider adding more music workshops</p>";
    }
    
    if (activityCounts.contains("Cinema & Acting Lab") && activityCounts["Cinema & Acting Lab"] > 0) {
        insights += "<p>• Acting programs are attracting members - explore drama club expansion</p>";
    }
    
    insights += QString("<p>• Total of <b>%1 active registrations</b> - great engagement!</p>").arg(m_registrations.size());
    
    m_insightsText->setHtml(insights);
}

void ActivityPanel::onTableSelectionChanged()
{
    // Handle table selection if needed
    QList<QTableWidgetItem*> selectedItems = m_registrationTable->selectedItems();
    if (!selectedItems.isEmpty()) {
        int row = selectedItems.first()->row();
        if (row >= 0 && row < m_registrations.size()) {
            const auto &reg = m_registrations[row];
            qDebug() << "Selected registration:" << reg.name << reg.activityType;
        }
    }
}

void ActivityPanel::onRefreshTimer()
{
    // Auto-sync every 5 minutes if no recent manual sync
    if (m_lastSyncLabel->text() != "Never") {
        qDebug() << "⏰ Auto-refresh timer triggered";
        onSyncData();
    }
}

void ActivityPanel::setCardStyle(QGroupBox *card)
{
    card->setStyleSheet(R"(
        QGroupBox {
            font-weight: bold;
            border: 2px solid #e0e0e0;
            border-radius: 8px;
            margin-top: 1ex;
            padding-top: 15px;
            background-color: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 10px 0 10px;
            color: #333333;
        }
    )");
    card->setMinimumHeight(80);
    card->setMaximumHeight(120);
}

void ActivityPanel::setTableStyle()
{
    m_registrationTable->setStyleSheet(R"(
        QTableWidget {
            gridline-color: #e0e0e0;
            background-color: white;
            alternate-background-color: #f8f9fa;
            selection-background-color: #e3f2fd;
        }
        QTableWidget::item {
            padding: 8px;
            border: none;
        }
        QHeaderView::section {
            background-color: #f5f5f5;
            color: #333333;
            padding: 10px;
            border: 1px solid #e0e0e0;
            font-weight: bold;
        }
    )");
    
    m_registrationTable->setAlternatingRowColors(true);
    m_registrationTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_registrationTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_registrationTable->verticalHeader()->setVisible(false);
    m_registrationTable->setSortingEnabled(true);
}

void ActivityPanel::applyTableFilters()
{
    // Implement filtering logic based on search and filter controls
    QString searchText = m_searchEdit->text().toLower();
    QString filterText = m_filterComboBox->currentText();
    
    for (int i = 0; i < m_registrationTable->rowCount(); ++i) {
        bool showRow = true;
        
        // Apply search filter
        if (!searchText.isEmpty()) {
            bool matchFound = false;
            for (int j = 0; j < m_registrationTable->columnCount(); ++j) {
                QTableWidgetItem *item = m_registrationTable->item(i, j);
                if (item && item->text().toLower().contains(searchText)) {
                    matchFound = true;
                    break;
                }
            }
            showRow = matchFound;
        }
        
        // Apply activity filter
        if (showRow && filterText != "All Activities") {
            QTableWidgetItem *activityItem = m_registrationTable->item(i, 4); // Activity Type column
            if (activityItem) {
                showRow = activityItem->text().contains(filterText);
            }
        }
        
        m_registrationTable->setRowHidden(i, !showRow);
    }
}

QString ActivityPanel::formatDateTime(const QString &isoDateTime)
{
    QDateTime dateTime = QDateTime::fromString(isoDateTime, Qt::ISODate);
    if (dateTime.isValid()) {
        return dateTime.toString("MMM dd, hh:mm AP");
    }
    return isoDateTime;
}

QString ActivityPanel::getActivityIcon(const QString &activityType)
{
    if (activityType.contains("Music", Qt::CaseInsensitive)) {
        return "🎵";
    } else if (activityType.contains("Cinema", Qt::CaseInsensitive) || 
               activityType.contains("Acting", Qt::CaseInsensitive)) {
        return "🎬";
    } else if (activityType.contains("Sports", Qt::CaseInsensitive) || 
               activityType.contains("Fitness", Qt::CaseInsensitive)) {
        return "🏃‍♂️";
    }
    return "🎯";
}

void ActivityPanel::showSyncStatus(const QString &message, bool success)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(success ? "Sync Successful" : "Sync Failed");
    msgBox.setText(message);
    msgBox.setIcon(success ? QMessageBox::Information : QMessageBox::Warning);
    msgBox.exec();
}

bool ActivityPanel::formsDataExists()
{
    QString sourceDir = "C:/Users/Khalil/Desktop/SummerClub_Advanced";
    QString jsonPath = sourceDir + "/forms_registration_data.json";
    QFileInfo jsonInfo(jsonPath);
    if (!jsonInfo.exists()) {
        jsonPath = QDir::currentPath() + "/forms_registration_data.json";
    } else {
        jsonPath = jsonInfo.absoluteFilePath();
    }
    return QFileInfo::exists(jsonPath);
}

QString ActivityPanel::getFormsDataPath()
{
    QString sourceDir = "C:/Users/Khalil/Desktop/SummerClub_Advanced";
    QString jsonPath = sourceDir + "/forms_registration_data.json";
    QFileInfo jsonInfo(jsonPath);
    if (jsonInfo.exists()) {
        return jsonInfo.absoluteFilePath();
    }
    return QDir::currentPath() + "/forms_registration_data.json";
}