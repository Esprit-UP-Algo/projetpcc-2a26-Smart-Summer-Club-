#include "activitypanel.h"
#include <QApplication>
#include <QStandardPaths>
#include <QFileInfo>
#include <QProcessEnvironment>

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
    
    // First, ensure we have the nodeJsScripts folder in the workspace
    if (!ensureNodeJsScriptsExists()) {
        qDebug() << "❌ Failed to setup nodeJsScripts folder";
        showSyncStatus("Failed to setup required files", false);
        m_syncButton->setEnabled(true);
        m_syncButton->setText("🔄 Sync Data");
        m_syncProgressBar->setVisible(false);
        return;
    }
    
    // Check if Node.js is available
    QProcess nodeCheck;
    nodeCheck.start("node", QStringList() << "--version");
    if (nodeCheck.waitForFinished(3000)) {
        QString nodeVersion = nodeCheck.readAllStandardOutput().trimmed();
        qDebug() << "🔍 Node.js version:" << nodeVersion;
    } else {
        qDebug() << "⚠️ Warning: Could not detect Node.js version";
    }
    
    // Use Qt workspace location (where files were copied)
    QString buildDir = QCoreApplication::applicationDirPath();
    QDir dir(buildDir);
    
    // Navigate to Qt workspace root
    dir.cdUp();  // Go up from Debug to build directory
    dir.cdUp();  // Go up from build to project root directory
    
    QString qtWorkspaceRoot = dir.absolutePath();
    QString nodeScriptsDir = qtWorkspaceRoot + "/nodeJsScripts";
    QString scriptPath = nodeScriptsDir + "/forms_data_extractor.js";
    
    QFileInfo scriptInfo(scriptPath);
    
    qDebug() << "📂 Build dir:" << buildDir;
    qDebug() << "📂 Qt workspace root:" << qtWorkspaceRoot;
    qDebug() << "📂 NodeJS scripts dir:" << nodeScriptsDir;
    qDebug() << "🔍 Looking for script at:" << scriptPath;
    qDebug() << "📁 Script exists:" << scriptInfo.exists();
    
    if (!scriptInfo.exists()) {
        qDebug() << "❌ Could not find forms_data_extractor.js script";
        showSyncStatus("Script not found: forms_data_extractor.js", false);
        m_syncButton->setEnabled(true);
        m_syncButton->setText("🔄 Sync Data");
        m_syncProgressBar->setVisible(false);
        return;
    }
    
    // Check if package.json exists (for dependencies)
    QString packageJsonPath = nodeScriptsDir + "/package.json";
    QFileInfo packageJsonInfo(packageJsonPath);
    qDebug() << "📄 package.json exists:" << packageJsonInfo.exists();
    
    // Check if node_modules exists
    QString nodeModulesPath = nodeScriptsDir + "/node_modules";
    QDir nodeModulesDir(nodeModulesPath);
    qDebug() << "📁 node_modules exists:" << nodeModulesDir.exists();
    
    if (packageJsonInfo.exists() && !nodeModulesDir.exists()) {
        qDebug() << "⚠️ Warning: package.json exists but node_modules missing. Run 'npm install' in" << nodeScriptsDir;
    }
    
    QStringList arguments;
    arguments << scriptInfo.absoluteFilePath();
    
    qDebug() << "📋 Running Node.js script:" << scriptInfo.absoluteFilePath();
    qDebug() << "📝 Full command: node" << arguments.join(" ");
    
    // Verify credentials.json exists
    QString credentialsPath = nodeScriptsDir + "/credentials.json";
    QFileInfo credentialsInfo(credentialsPath);
    qDebug() << "🔑 credentials.json exists:" << credentialsInfo.exists();
    
    // Set working directory to nodeJsScripts folder (where credentials.json is located)
    m_nodeProcess->setWorkingDirectory(nodeScriptsDir);
    qDebug() << "📁 Node.js working directory set to:" << nodeScriptsDir;
    qDebug() << "📁 Working directory exists:" << QDir(nodeScriptsDir).exists();
    
    // Capture both stdout and stderr
    m_nodeProcess->setProcessChannelMode(QProcess::MergedChannels);
    
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
    // Use Qt workspace location where files were copied
    QString buildDir = QCoreApplication::applicationDirPath();
    QDir dir(buildDir);
    
    // Navigate to Qt workspace root
    dir.cdUp();  // Debug -> build
    dir.cdUp();  // build -> Qt workspace root
    
    QString qtWorkspaceRoot = dir.absolutePath();
    QString jsonPath = qtWorkspaceRoot + "/nodeJsScripts/forms_registration_data.json";
    
    qDebug() << "🔍 Looking for JSON at:" << jsonPath;
    
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
    QString buildDir = QCoreApplication::applicationDirPath();
    QDir dir(buildDir);
    dir.cdUp(); dir.cdUp(); // Navigate to Qt workspace root
    
    QString jsonPath = dir.absolutePath() + "/nodeJsScripts/forms_registration_data.json";
    QFileInfo fileInfo(jsonPath);
    
    qDebug() << "📁 Checking if forms data exists at:" << jsonPath;
    qDebug() << "📁 File exists:" << fileInfo.exists();
    
    return fileInfo.exists();
}

QString ActivityPanel::getFormsDataPath()
{
    QString buildDir = QCoreApplication::applicationDirPath();
    QDir dir(buildDir);
    dir.cdUp(); // Go up from debug
    dir.cdUp(); // Go up from build to Qt workspace root
    
    return dir.absolutePath() + "/nodeJsScripts/forms_registration_data.json";
}

bool ActivityPanel::ensureNodeJsScriptsExists()
{
    // Get Qt workspace location
    QString buildDir = QCoreApplication::applicationDirPath();
    QDir dir(buildDir);
    dir.cdUp(); dir.cdUp(); // Navigate to Qt workspace root
    QString qtWorkspaceRoot = dir.absolutePath();
    QString destNodeScriptsDir = qtWorkspaceRoot + "/nodeJsScripts";
    
    // Check if nodeJsScripts already exists in Qt workspace
    QDir destDir(destNodeScriptsDir);
    if (destDir.exists() && QFileInfo::exists(destNodeScriptsDir + "/forms_data_extractor.js")) {
        qDebug() << "✅ nodeJsScripts folder already exists in Qt workspace:" << destNodeScriptsDir;
        return true;
    }
    
    // Find the actual project location
    QString actualProjectPath = findActualProjectLocation();
    if (actualProjectPath.isEmpty()) {
        qDebug() << "❌ Could not find actual SummerClub_Advanced project location";
        return false;
    }
    
    QString sourceNodeScriptsDir = actualProjectPath + "/nodeJsScripts";
    QDir sourceDir(sourceNodeScriptsDir);
    
    if (!sourceDir.exists()) {
        qDebug() << "❌ Source nodeJsScripts folder does not exist:" << sourceNodeScriptsDir;
        return false;
    }
    
    qDebug() << "📋 Copying nodeJsScripts from:" << sourceNodeScriptsDir;
    qDebug() << "📋 Copying nodeJsScripts to:" << destNodeScriptsDir;
    
    // List files that will be copied
    QStringList filesToCopy = sourceDir.entryList(QDir::Files);
    qDebug() << "📄 Files to copy:" << filesToCopy;
    
    // Copy the entire nodeJsScripts directory
    if (copyDirectoryRecursively(sourceNodeScriptsDir, destNodeScriptsDir)) {
        // Verify the copy was successful
        QDir destDirVerify(destNodeScriptsDir);
        QStringList copiedFiles = destDirVerify.entryList(QDir::Files);
        qDebug() << "✅ Successfully copied nodeJsScripts to Qt workspace";
        qDebug() << "📄 Copied files:" << copiedFiles;
        return true;
    } else {
        qDebug() << "❌ Failed to copy nodeJsScripts to Qt workspace";
        return false;
    }
}

QString ActivityPanel::findActualProjectLocation()
{
    qDebug() << "🔍 Starting comprehensive project location search...";
    qDebug() << "🏠 Current user home path:" << QDir::homePath();
    qDebug() << "👤 Current username:" << qgetenv("USERNAME");
    
    // Get current username for dynamic path construction
    QString currentUser = qgetenv("USERNAME");
    if (currentUser.isEmpty()) {
        currentUser = qgetenv("USER"); // For Unix-like systems
    }
    
    QStringList searchPaths;
    
    // 1. Common user-specific paths with current username
    if (!currentUser.isEmpty()) {
        searchPaths << QString("C:/Users/%1/Desktop/ProjetC++/SummerClub_Advanced").arg(currentUser);
        searchPaths << QString("C:/Users/%1/Desktop/SummerClub_Advanced").arg(currentUser);
        searchPaths << QString("C:/Users/%1/OneDrive/Desktop/ProjetC++/SummerClub_Advanced").arg(currentUser);
        searchPaths << QString("C:/Users/%1/OneDrive/Desktop/SummerClub_Advanced").arg(currentUser);
        searchPaths << QString("C:/Users/%1/Documents/ProjetC++/SummerClub_Advanced").arg(currentUser);
        searchPaths << QString("C:/Users/%1/Documents/SummerClub_Advanced").arg(currentUser);
        searchPaths << QString("C:/Users/%1/Downloads/SummerClub_Advanced").arg(currentUser);
    }
    
    // 2. Qt-based home directory paths (cross-platform)
    searchPaths << QDir::homePath() + "/Desktop/ProjetC++/SummerClub_Advanced";
    searchPaths << QDir::homePath() + "/Desktop/SummerClub_Advanced"; 
    searchPaths << QDir::homePath() + "/OneDrive/Desktop/ProjetC++/SummerClub_Advanced";
    searchPaths << QDir::homePath() + "/OneDrive/Desktop/SummerClub_Advanced";
    searchPaths << QDir::homePath() + "/Documents/ProjetC++/SummerClub_Advanced";
    searchPaths << QDir::homePath() + "/Documents/SummerClub_Advanced";
    searchPaths << QDir::homePath() + "/Downloads/SummerClub_Advanced";
    
    // 3. Known specific user paths (for backwards compatibility)
    searchPaths << "C:/Users/Khalil/Desktop/ProjetC++/SummerClub_Advanced";
    searchPaths << "C:/Users/Khalil/Desktop/SummerClub_Advanced";
    searchPaths << "C:/Users/khali/OneDrive/Desktop/SummerClub_Advanced";
    
    // 4. Root drive locations
    searchPaths << "C:/ProjetC++/SummerClub_Advanced";
    searchPaths << "C:/SummerClub_Advanced";
    searchPaths << "D:/ProjetC++/SummerClub_Advanced";
    searchPaths << "D:/SummerClub_Advanced";
    searchPaths << "E:/ProjetC++/SummerClub_Advanced";
    searchPaths << "E:/SummerClub_Advanced";
    
    // 5. Dynamic search in common base locations
    QStringList baseSearchLocations = {
        QDir::homePath() + "/OneDrive/Desktop",
        QDir::homePath() + "/Desktop",
        QDir::homePath() + "/Documents", 
        QDir::homePath() + "/Downloads",
        "C:/Users/" + currentUser + "/Desktop",
        "C:/Users/" + currentUser + "/OneDrive/Desktop",
        "C:/Users/" + currentUser + "/Documents",
        "C:/", "D:/", "E:/", "F:/"
    };
    
    qDebug() << "🔍 Searching for SummerClub* folders in common locations...";
    for (const QString &basePath : baseSearchLocations) {
        QDir baseDir(basePath);
        if (baseDir.exists()) {
            // Look for any folder containing "SummerClub" (case insensitive)
            QStringList filters;
            filters << "*SummerClub*" << "*summerclub*" << "*SUMMERCLUB*" << "*ProjetC++*" << "*projetc++*";
            
            QStringList subdirs = baseDir.entryList(filters, QDir::Dirs);
            for (const QString &subdir : subdirs) {
                QString fullPath = basePath + "/" + subdir;
                searchPaths.append(fullPath);
                
                // Also check subdirectories for nested projects
                QDir subDirObj(fullPath);
                QStringList nestedDirs = subDirObj.entryList(QStringList() << "*SummerClub*", QDir::Dirs);
                for (const QString &nestedDir : nestedDirs) {
                    searchPaths.append(fullPath + "/" + nestedDir);
                }
            }
        }
    }
    
    // Remove duplicates and sort by most likely paths first
    searchPaths.removeDuplicates();
    
    qDebug() << "🔍 Total search paths to check:" << searchPaths.size();
    
    // Check each potential path
    for (const QString &path : searchPaths) {
        QDir projectDir(path);
        if (projectDir.exists()) {
            // Verify it's our project by checking for key files
            QString nodeScriptsPath = path + "/nodeJsScripts";
            QString formsScriptPath = nodeScriptsPath + "/forms_data_extractor.js";
            QString credentialsPath = nodeScriptsPath + "/credentials.json";
            QString packageJsonPath = nodeScriptsPath + "/package.json";
            QString activityFile = path + "/activity.cpp";
            QString activityPanelFile = path + "/activitypanel.cpp";
            QString employerAdminFile = path + "/employeradmin.cpp";
            
            // Check for multiple indicators to ensure it's the right project
            bool hasNodeScripts = QFileInfo::exists(nodeScriptsPath);
            bool hasFormsScript = QFileInfo::exists(formsScriptPath);
            bool hasCredentials = QFileInfo::exists(credentialsPath);
            bool hasActivityFiles = QFileInfo::exists(activityFile) && QFileInfo::exists(activityPanelFile);
            bool hasMainProject = QFileInfo::exists(employerAdminFile);
            
            // Must have nodeJsScripts folder AND either forms script or (activity files AND credentials)
            if (hasNodeScripts && (hasFormsScript || (hasActivityFiles && hasCredentials && hasMainProject))) {
                qDebug() << "✅ Found actual project at:" << path;
                qDebug() << "  ✅ NodeJs scripts folder:" << hasNodeScripts;
                qDebug() << "  ✅ Forms script exists:" << hasFormsScript;
                qDebug() << "  ✅ Credentials exist:" << hasCredentials;
                qDebug() << "  ✅ Activity files:" << hasActivityFiles;
                qDebug() << "  ✅ Main project files:" << hasMainProject;
                qDebug() << "  📄 Package.json exists:" << QFileInfo::exists(packageJsonPath);
                return path;
            }
        }
    }
    
    qDebug() << "❌ Could not find SummerClub_Advanced project in any location";
    qDebug() << "🔍 Searched paths:";
    for (int i = 0; i < qMin(10, searchPaths.size()); ++i) { // Show first 10 for brevity
        qDebug() << "  - " << searchPaths[i];
    }
    if (searchPaths.size() > 10) {
        qDebug() << "  ... and" << (searchPaths.size() - 10) << "more locations";
    }
    
    return QString();
}

bool ActivityPanel::copyDirectoryRecursively(const QString &sourceDir, const QString &destDir)
{
    QDir sourceDirectory(sourceDir);
    if (!sourceDirectory.exists()) {
        return false;
    }
    
    QDir destDirectory(destDir);
    if (!destDirectory.exists()) {
        destDirectory.mkpath(".");
    }
    
    // Copy all files
    QStringList files = sourceDirectory.entryList(QDir::Files);
    for (const QString &fileName : files) {
        QString sourceFilePath = sourceDir + "/" + fileName;
        QString destFilePath = destDir + "/" + fileName;
        
        // Remove existing file if it exists
        if (QFileInfo::exists(destFilePath)) {
            QFile::remove(destFilePath);
        }
        
        if (!QFile::copy(sourceFilePath, destFilePath)) {
            qDebug() << "❌ Failed to copy file:" << sourceFilePath << "to" << destFilePath;
            return false;
        } else {
            qDebug() << "✅ Copied:" << fileName;
        }
    }
    
    // Copy subdirectories recursively
    QStringList subdirs = sourceDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &subdirName : subdirs) {
        QString sourceSubdir = sourceDir + "/" + subdirName;
        QString destSubdir = destDir + "/" + subdirName;
        
        if (!copyDirectoryRecursively(sourceSubdir, destSubdir)) {
            return false;
        }
    }
    
    return true;
}