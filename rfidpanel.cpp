#include "rfidpanel.h"

RFIDPanel::RFIDPanel(QWidget *parent)
    : QWidget(parent),
      m_rfidManager(nullptr),
      m_autoRefreshEnabled(true),
      m_selectedCardRow(-1)
{
    setupUI();
    setupStyles();
    connectSignals();
    
    // Setup timers for auto-refresh
    m_activityTimer = new QTimer(this);
    m_activityTimer->setInterval(5000); // 5 seconds
    connect(m_activityTimer, &QTimer::timeout, this, &RFIDPanel::refreshActivityFeed);
    
    // Start timers
    m_activityTimer->start();
    
    // Initial data load
    refreshAll();
    
    qDebug() << "🎨 RFIDPanel: Dashboard interface created successfully";
}

RFIDPanel::~RFIDPanel()
{
    if (m_activityTimer) m_activityTimer->stop();
}

void RFIDPanel::setupUI()
{
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // Setup each section
    setupCardManagementSection();
    setupActivitySection();
    
    // Add sections to main layout
    mainLayout->addWidget(m_cardManagementGroup, 3); // Much more space to card management
    mainLayout->addWidget(m_activityGroup, 1); // Some space for activity feed
    
    setLayout(mainLayout);
}



void RFIDPanel::setupCardManagementSection()
{
    m_cardManagementGroup = new QGroupBox("💳 Manage RFID Cards", this);
    QVBoxLayout *cardLayout = new QVBoxLayout(m_cardManagementGroup);
    
    // Search and filter row
    QHBoxLayout *searchLayout = new QHBoxLayout();
    
    searchLayout->addWidget(new QLabel("🔍 Search:"));
    m_searchLineEdit = new QLineEdit();
    m_searchLineEdit->setPlaceholderText("Enter member name or card UID...");
    searchLayout->addWidget(m_searchLineEdit);
    
    searchLayout->addWidget(new QLabel("Status Filter:"));
    m_statusFilterCombo = new QComboBox();
    m_statusFilterCombo->addItems({"All", "Active", "Disabled", "Lost", "Expired"});
    searchLayout->addWidget(m_statusFilterCombo);
    
    searchLayout->addStretch();
    
    m_addCardButton = new QPushButton("➕ Add New Card");
    m_addCardButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px 16px; border: none; border-radius: 4px; font-weight: bold; }");
    searchLayout->addWidget(m_addCardButton);
    
    cardLayout->addLayout(searchLayout);
    
    // Create new RFID cards table with proper header visibility
    m_cardTableWidget = new QTableWidget(0, 4, this);
    
    // Set column headers immediately
    QStringList columnHeaders;
    columnHeaders << "Member Name" << "Card UID" << "Status" << "Last Access";
    m_cardTableWidget->setHorizontalHeaderLabels(columnHeaders);
    
    // Configure table behavior
    m_cardTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_cardTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_cardTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_cardTableWidget->setAlternatingRowColors(true);
    m_cardTableWidget->setShowGrid(true);
    m_cardTableWidget->setSortingEnabled(false);
    
    // Configure horizontal header with forced visibility and proper sizing
    QHeaderView *hHeader = m_cardTableWidget->horizontalHeader();
    hHeader->setVisible(true);
    hHeader->show(); // Force show
    hHeader->setHighlightSections(false);
    hHeader->setDefaultSectionSize(150);
    hHeader->setMinimumSectionSize(100);
    hHeader->setMinimumHeight(45); // Force minimum height for headers
    hHeader->setMaximumHeight(45); // Set fixed header height
    hHeader->setStretchLastSection(true);
    hHeader->setSectionResizeMode(0, QHeaderView::Stretch);
    hHeader->setSectionResizeMode(1, QHeaderView::Interactive);
    hHeader->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    hHeader->setSectionResizeMode(3, QHeaderView::Interactive);
    
    // Force header to stay visible
    hHeader->setHidden(false);
    hHeader->raise(); // Bring to front
    
    // Hide vertical header
    m_cardTableWidget->verticalHeader()->setVisible(false);
    
    // Set table dimensions with proper header height
    m_cardTableWidget->setMinimumHeight(300);
    m_cardTableWidget->verticalHeader()->setDefaultSectionSize(30);
    
    // Force header height after table creation
    m_cardTableWidget->horizontalHeader()->setFixedHeight(45);
    m_cardTableWidget->horizontalHeader()->setVisible(true);
    
    // Apply comprehensive styling
    QString tableStyle = 
        "QTableWidget {"
        "    background-color: white;"
        "    gridline-color: #d0d0d0;"
        "    selection-background-color: #e3f2fd;"
        "    alternate-background-color: #f8f9fa;"
        "    border: 1px solid #cccccc;"
        "}"
        "QTableWidget::item {"
        "    padding: 6px 8px;"
        "    border: none;"
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #16a5b3;"
        "    color: white;"
        "}"
        "QHeaderView::section {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #16a5b3, stop:1 #14919c);"
        "    color: white;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    padding: 12px 8px;"
        "    border: none;"
        "    border-right: 1px solid #14919c;"
        "    text-align: center;"
        "    min-height: 40px;"
        "    height: 45px;"
        "    max-height: 45px;"
        "}"
        "QHeaderView {"
        "    height: 45px;"
        "    min-height: 45px;"
        "    max-height: 45px;"
        "    background-color: #16a5b3;"
        "}";
    m_cardTableWidget->setStyleSheet(tableStyle);
    
    cardLayout->addWidget(m_cardTableWidget);
    
    // Final header configuration after everything is set up
    QTimer::singleShot(100, [this]() {
        // Force headers to be visible with a slight delay
        QHeaderView *header = m_cardTableWidget->horizontalHeader();
        header->setVisible(true);
        header->show();
        header->setFixedHeight(45);
        
        // Set headers again to ensure they're displayed
        QStringList headers;
        headers << "👤 Member Name" << "💳 Card UID" << "🔘 Status" << "⏰ Last Access";
        m_cardTableWidget->setHorizontalHeaderLabels(headers);
        
        // Force table update
        m_cardTableWidget->update();
        m_cardTableWidget->repaint();
        
        qDebug() << "🔧 Headers forced visible - Height:" << header->height() << "Visible:" << header->isVisible();
    });
    
    // Action buttons row
    QHBoxLayout *actionsLayout = new QHBoxLayout();
    
    m_viewCardButton = new QPushButton("👁️ View");
    m_editCardButton = new QPushButton("✏️ Edit");
    m_deleteCardButton = new QPushButton("🗑️ Delete");
    m_toggleStatusButton = new QPushButton("🚫 Disable");
    
    // Style action buttons
    QString buttonStyle = "QPushButton { padding: 6px 12px; border: 1px solid #ddd; border-radius: 4px; }";
    m_viewCardButton->setStyleSheet(buttonStyle + "QPushButton { background-color: #2196F3; color: white; }");
    m_editCardButton->setStyleSheet(buttonStyle + "QPushButton { background-color: #FF9800; color: white; }");
    m_deleteCardButton->setStyleSheet(buttonStyle + "QPushButton { background-color: #F44336; color: white; }");
    m_toggleStatusButton->setStyleSheet(buttonStyle + "QPushButton { background-color: #9E9E9E; color: white; }");
    
    // Initially disable action buttons
    m_viewCardButton->setEnabled(false);
    m_editCardButton->setEnabled(false);
    m_deleteCardButton->setEnabled(false);
    m_toggleStatusButton->setEnabled(false);
    
    actionsLayout->addWidget(m_viewCardButton);
    actionsLayout->addWidget(m_editCardButton);
    actionsLayout->addWidget(m_deleteCardButton);
    actionsLayout->addWidget(m_toggleStatusButton);
    actionsLayout->addStretch();
    
    cardLayout->addLayout(actionsLayout);
}

void RFIDPanel::setupActivitySection()
{
    m_activityGroup = new QGroupBox("📋 Recent Access Activity", this);
    QVBoxLayout *activityLayout = new QVBoxLayout(m_activityGroup);
    
    // Activity controls
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    
    m_autoRefreshButton = new QPushButton("🔄 Auto-refresh: ON");
    m_autoRefreshButton->setCheckable(true);
    m_autoRefreshButton->setChecked(true);
    m_autoRefreshButton->setStyleSheet("QPushButton:checked { background-color: #4CAF50; color: white; }");
    
    m_clearActivityButton = new QPushButton("🗑️ Clear");
    
    controlsLayout->addWidget(m_autoRefreshButton);
    controlsLayout->addWidget(m_clearActivityButton);
    controlsLayout->addStretch();
    
    activityLayout->addLayout(controlsLayout);
    
    // Activity feed
    m_activityTextEdit = new QTextEdit();
    m_activityTextEdit->setMaximumHeight(150);
    m_activityTextEdit->setReadOnly(true);
    m_activityTextEdit->setStyleSheet("QTextEdit { background-color: #f5f5f5; border: 1px solid #ddd; }");
    
    activityLayout->addWidget(m_activityTextEdit);
}

void RFIDPanel::setupStyles()
{
    // Main panel style
    setStyleSheet(
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #cccccc;"
        "    border-radius: 8px;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px 0 5px;"
        "}"
        "QFrame {"
        "    background-color: white;"
        "    border: 1px solid #e0e0e0;"
        "    border-radius: 6px;"
        "    padding: 10px;"
        "    margin: 5px;"
        "}"
        "QTableWidget {"
        "    gridline-color: #e0e0e0;"
        "    selection-background-color: #e3f2fd;"
        "}"
        "QLineEdit {"
        "    border: 1px solid #ddd;"
        "    border-radius: 4px;"
        "    padding: 6px;"
        "}"
        "QComboBox {"
        "    border: 1px solid #ddd;"
        "    border-radius: 4px;"
        "    padding: 6px;"
        "}"
    );
}

void RFIDPanel::connectSignals()
{
    // Card management signals
    connect(m_addCardButton, &QPushButton::clicked, this, &RFIDPanel::onAddCardClicked);
    connect(m_viewCardButton, &QPushButton::clicked, this, &RFIDPanel::onViewCardDetailsClicked);
    connect(m_editCardButton, &QPushButton::clicked, this, &RFIDPanel::onEditCardClicked);
    connect(m_deleteCardButton, &QPushButton::clicked, this, &RFIDPanel::onDeleteCardClicked);
    connect(m_toggleStatusButton, &QPushButton::clicked, this, &RFIDPanel::onToggleCardStatusClicked);
    
    // Table selection
    connect(m_cardTableWidget, &QTableWidget::itemSelectionChanged, this, &RFIDPanel::onCardTableSelectionChanged);
    
    // Search and filter
    connect(m_searchLineEdit, &QLineEdit::textChanged, this, &RFIDPanel::onSearchTextChanged);
    connect(m_statusFilterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RFIDPanel::onStatusFilterChanged);
    
    // Activity controls
    connect(m_autoRefreshButton, &QPushButton::toggled, this, &RFIDPanel::onAutoRefreshToggled);
    connect(m_clearActivityButton, &QPushButton::clicked, [this]() {
        m_activityTextEdit->clear();
        addActivityEntry("Activity feed cleared", true);
    });
}

void RFIDPanel::setRFIDManager(RFIDManager *manager)
{
    m_rfidManager = manager;
    
    if (m_rfidManager) {
        // Connect RFID manager signals for real-time updates
        connect(m_rfidManager, &RFIDManager::accessGranted, this, &RFIDPanel::onRFIDAccessGranted);
        connect(m_rfidManager, &RFIDManager::accessDenied, this, &RFIDPanel::onRFIDAccessDenied);
        
        qDebug() << "🔗 RFIDPanel connected to RFIDManager";
    }
}

void RFIDPanel::refreshAll()
{
    refreshCardTable();
    refreshActivityFeed();
}



void RFIDPanel::refreshCardTable()
{
    qDebug() << "🔄 Refreshing RFID card table...";
    
    // Clear existing data
    m_cardTableWidget->setRowCount(0);
    
    QSqlQuery query;
    QString baseQuery = "SELECT r.RFID_ID, r.RFID_UID, r.CIN, "
                       "NVL(m.FIRST_NAME || ' ' || m.LAST_NAME, 'Unknown Member') as MEMBER_NAME, "
                       "r.CARD_STATUS, r.LAST_USED "
                       "FROM SUMMERCLUB.RFID_CARDS r "
                       "LEFT JOIN SUMMERCLUB.MEMBERS m ON r.CIN = m.CIN ";
    
    QString whereClause = "WHERE 1=1 ";
    
    // Add search filter
    QString searchText = m_searchLineEdit->text().trimmed();
    if (!searchText.isEmpty()) {
        whereClause += "AND (UPPER(NVL(m.FIRST_NAME || ' ' || m.LAST_NAME, 'Unknown')) LIKE UPPER('%" + searchText + "%') "
                      "OR UPPER(r.RFID_UID) LIKE UPPER('%" + searchText + "%')) ";
    }
    
    // Add status filter
    QString statusFilter = m_statusFilterCombo->currentText();
    if (statusFilter != "All") {
        whereClause += "AND r.CARD_STATUS = '" + statusFilter + "' ";
    }
    
    QString fullQuery = baseQuery + whereClause + "ORDER BY r.RFID_ID DESC";
    
    qDebug() << "📊 Executing query:" << fullQuery;
    
    if (query.exec(fullQuery)) {
        int row = 0;
        while (query.next()) {
            m_cardTableWidget->insertRow(row);
            
            QString memberName = query.value("MEMBER_NAME").toString();
            QString cardUid = query.value("RFID_UID").toString();
            QString cardStatus = query.value("CARD_STATUS").toString();
            QDateTime lastUsed = query.value("LAST_USED").toDateTime();
            int rfidId = query.value("RFID_ID").toInt();
            
            // Column 0: Member name
            QTableWidgetItem *memberItem = new QTableWidgetItem(memberName.isEmpty() ? "Unknown Member" : memberName);
            memberItem->setData(Qt::UserRole, rfidId); // Store ID for reference
            memberItem->setFlags(memberItem->flags() & ~Qt::ItemIsEditable); // Make non-editable
            m_cardTableWidget->setItem(row, 0, memberItem);
            
            // Column 1: Card UID
            QTableWidgetItem *uidItem = new QTableWidgetItem(cardUid);
            uidItem->setFont(QFont("Courier", 9)); // Monospace font for UID
            uidItem->setFlags(uidItem->flags() & ~Qt::ItemIsEditable); // Make non-editable
            m_cardTableWidget->setItem(row, 1, uidItem);
            
            
            // Column 2: Status with emoji and color
            QString statusText = cardStatus;
            QTableWidgetItem *statusItem = new QTableWidgetItem();
            
            if (cardStatus == "Active") {
                statusText = "✅ Active";
                statusItem->setForeground(QColor("#4CAF50"));
            } else if (cardStatus == "Disabled") {
                statusText = "🚫 Disabled";
                statusItem->setForeground(QColor("#FF9800"));
            } else if (cardStatus == "Lost") {
                statusText = "📱 Lost";
                statusItem->setForeground(QColor("#F44336"));
            } else if (cardStatus == "Expired") {
                statusText = "⏰ Expired";
                statusItem->setForeground(QColor("#9E9E9E"));
            }
            
            statusItem->setText(statusText);
            statusItem->setFont(QFont("", 9, QFont::Bold));
            statusItem->setFlags(statusItem->flags() & ~Qt::ItemIsEditable); // Make non-editable
            m_cardTableWidget->setItem(row, 2, statusItem);
            
            // Column 3: Last access
            QString lastAccessText = lastUsed.isValid() ? formatTimeAgo(lastUsed) : "Never";
            QTableWidgetItem *accessItem = new QTableWidgetItem(lastAccessText);
            if (!lastUsed.isValid()) {
                accessItem->setForeground(QColor("#9E9E9E"));
                QFont italicFont("", 9);
                italicFont.setItalic(true);
                accessItem->setFont(italicFont);
            }
            accessItem->setFlags(accessItem->flags() & ~Qt::ItemIsEditable); // Make non-editable
            m_cardTableWidget->setItem(row, 3, accessItem);
            
            row++;
        }
        
        qDebug() << "✅ Loaded" << row << "RFID cards into table";
    } else {
        qDebug() << "❌ Failed to load RFID cards:" << query.lastError().text();
        m_cardTableWidget->setRowCount(0);
    }
    
    // Force headers to be visible and refresh
    QStringList headers;
    headers << "👤 Member Name" << "💳 Card UID" << "🔘 Status" << "⏰ Last Access";
    m_cardTableWidget->setHorizontalHeaderLabels(headers);
    
    QHeaderView *header = m_cardTableWidget->horizontalHeader();
    header->setVisible(true);
    header->show();
    header->setFixedHeight(45);
    header->setHidden(false);
    header->raise();
    
    // Force complete widget refresh
    m_cardTableWidget->update();
    m_cardTableWidget->repaint();
    header->update();
    header->repaint();
    
    qDebug() << "🔄 Table refresh complete - Header visible:" << header->isVisible() << "Height:" << header->height();
}

void RFIDPanel::refreshActivityFeed()
{
    if (!m_autoRefreshEnabled) return;
    
    // Get recent activity from database (last 50 entries)
    QSqlQuery query;
    query.prepare("SELECT ACCESS_TIME, MEMBER_NAME, RFID_UID, ACCESS_RESULT "
                  "FROM SUMMERCLUB.RFID_ACCESS_LOG "
                  "ORDER BY ACCESS_TIME DESC "
                  "FETCH FIRST 10 ROWS ONLY");
    
    if (query.exec()) {
        QString activityHtml = "<html><body style='font-family: monospace; font-size: 12px;'>";
        
        while (query.next()) {
            QDateTime accessTime = query.value("ACCESS_TIME").toDateTime();
            QString memberName = query.value("MEMBER_NAME").toString();
            QString rfidUid = query.value("RFID_UID").toString();
            QString result = query.value("ACCESS_RESULT").toString();
            
            QString timeStr = accessTime.toString("hh:mm:ss");
            QString color = result.contains("GRANTED") ? "#4CAF50" : "#F44336";
            QString emoji = result.contains("GRANTED") ? "🟢" : "🔴";
            QString memberText = memberName.isEmpty() ? "Unknown" : memberName;
            QString statusText = result.contains("GRANTED") ? "✅ GRANTED" : "❌ DENIED";
            
            activityHtml += QString("<div style='margin: 2px 0; color: %1;'>").arg(color);
            activityHtml += QString("%1 %2 - %3 accessed via %4 - %5").arg(emoji, timeStr, memberText, rfidUid, statusText);
            activityHtml += "</div>";
        }
        
        activityHtml += "</body></html>";
        m_activityTextEdit->setHtml(activityHtml);
    }
}

QString RFIDPanel::formatTimeAgo(const QDateTime &dateTime)
{
    QDateTime now = QDateTime::currentDateTime();
    qint64 seconds = dateTime.secsTo(now);
    
    if (seconds < 60) return QString("%1 sec ago").arg(seconds);
    if (seconds < 3600) return QString("%1 min ago").arg(seconds / 60);
    if (seconds < 86400) return QString("%1 hr ago").arg(seconds / 3600);
    return QString("%1 days ago").arg(seconds / 86400);
}

void RFIDPanel::addActivityEntry(const QString &message, bool isSuccess)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString color = isSuccess ? "#4CAF50" : "#F44336";
    QString emoji = isSuccess ? "🟢" : "🔴";
    
    m_activityTextEdit->append(QString("<span style='color: %1;'>%2 %3 - %4</span>").arg(color, emoji, timestamp, message));
}

// Slot implementations for card management
void RFIDPanel::onAddCardClicked()
{
    qDebug() << "➕ Add card button clicked";
    
    // Use shared Arduino instance if available
    Arduino *arduino = m_rfidManager ? m_rfidManager->getArduino() : nullptr;
    RFIDCardDialog dialog(arduino, this);
    if (dialog.exec() == QDialog::Accepted) {
        refreshCardTable();
        addActivityEntry(QString("New RFID card added: %1").arg(dialog.getCardUid()), true);
    }
}

void RFIDPanel::onEditCardClicked()
{
    if (m_selectedCardRow >= 0) {
        QString cardUid = m_cardTableWidget->item(m_selectedCardRow, 1)->text();
        qDebug() << "✏️ Edit card button clicked for:" << cardUid;
        
        // Use shared Arduino instance if available
        Arduino *arduino = m_rfidManager ? m_rfidManager->getArduino() : nullptr;
        RFIDCardDialog dialog(cardUid, arduino, this);
        if (dialog.exec() == QDialog::Accepted) {
            refreshCardTable();
            addActivityEntry(QString("RFID card updated: %1").arg(cardUid), true);
        }
    }
}

void RFIDPanel::onDeleteCardClicked()
{
    if (m_selectedCardRow >= 0) {
        QString cardUid = m_cardTableWidget->item(m_selectedCardRow, 1)->text();
        QString memberName = m_cardTableWidget->item(m_selectedCardRow, 0)->text();
        
        int ret = QMessageBox::warning(this, "Delete Card", 
                                      QString("Are you sure you want to delete card %1 for %2?\n\nThis action cannot be undone.").arg(cardUid, memberName),
                                      QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            if (RFIDCard::deleteByUid(cardUid)) {
                refreshCardTable();
                addActivityEntry(QString("RFID card deleted: %1 (%2)").arg(cardUid, memberName), true);
                QMessageBox::information(this, "Success", "RFID card deleted successfully!");
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete RFID card.");
                addActivityEntry(QString("Failed to delete card: %1").arg(cardUid), false);
            }
        }
    }
}

void RFIDPanel::onToggleCardStatusClicked()
{
    if (m_selectedCardRow >= 0) {
        QString cardUid = m_cardTableWidget->item(m_selectedCardRow, 1)->text();
        QString currentStatus = m_cardTableWidget->item(m_selectedCardRow, 2)->text();
        QString memberName = m_cardTableWidget->item(m_selectedCardRow, 0)->text();
        
        bool isActive = currentStatus.contains("Active");
        QString newStatus = isActive ? "Disabled" : "Active";
        QString action = isActive ? "disable" : "enable";
        
        int ret = QMessageBox::question(this, "Change Card Status", 
                                       QString("Do you want to %1 card %2 for %3?").arg(action, cardUid, memberName),
                                       QMessageBox::Yes | QMessageBox::No);
        
        if (ret == QMessageBox::Yes) {
            RFIDCard *card = RFIDCard::findByUid(cardUid);
            if (card) {
                card->setCardStatus(RFIDCard::stringToStatus(newStatus));
                if (card->save()) {
                    refreshCardTable();
                    addActivityEntry(QString("Card %1 for %2: %3").arg(cardUid, memberName, newStatus.toUpper()), true);
                    QMessageBox::information(this, "Success", QString("Card %1 successfully!").arg(action + "d"));
                } else {
                    QMessageBox::critical(this, "Error", "Failed to update card status.");
                    addActivityEntry(QString("Failed to %1 card: %2").arg(action, cardUid), false);
                }
                delete card;
            } else {
                QMessageBox::critical(this, "Error", "Card not found.");
            }
        }
    }
}

void RFIDPanel::onViewCardDetailsClicked()
{
    if (m_selectedCardRow >= 0) {
        QString cardUid = m_cardTableWidget->item(m_selectedCardRow, 1)->text();
        qDebug() << "👁️ View details for card:" << cardUid;
        // TODO: Implement card details dialog
        QMessageBox::information(this, "Card Details", QString("Viewing details for card: %1").arg(cardUid));
    }
}

void RFIDPanel::onCardTableSelectionChanged()
{
    QList<QTableWidgetItem*> selectedItems = m_cardTableWidget->selectedItems();
    m_selectedCardRow = selectedItems.isEmpty() ? -1 : selectedItems.first()->row();
    
    bool hasSelection = m_selectedCardRow >= 0;
    m_viewCardButton->setEnabled(hasSelection);
    m_editCardButton->setEnabled(hasSelection);
    m_deleteCardButton->setEnabled(hasSelection);
    m_toggleStatusButton->setEnabled(hasSelection);
    
    if (hasSelection) {
        QString status = m_cardTableWidget->item(m_selectedCardRow, 2)->text();
        if (status.contains("Active")) {
            m_toggleStatusButton->setText("🚫 Disable");
        } else {
            m_toggleStatusButton->setText("✅ Enable");
        }
    }
}

void RFIDPanel::onSearchTextChanged()
{
    refreshCardTable();
}

void RFIDPanel::onStatusFilterChanged()
{
    refreshCardTable();
}

void RFIDPanel::onAutoRefreshToggled()
{
    m_autoRefreshEnabled = m_autoRefreshButton->isChecked();
    m_autoRefreshButton->setText(m_autoRefreshEnabled ? "🔄 Auto-refresh: ON" : "🔄 Auto-refresh: OFF");
    
    if (m_autoRefreshEnabled) {
        m_activityTimer->start();
        addActivityEntry("Auto-refresh enabled", true);
    } else {
        m_activityTimer->stop();
        addActivityEntry("Auto-refresh disabled", false);
    }
}

void RFIDPanel::onRFIDAccessGranted(const QString &memberName, const QString &rfidUid)
{
    addActivityEntry(QString("%1 accessed via %2 - ✅ GRANTED").arg(memberName, rfidUid), true);
}

void RFIDPanel::onRFIDAccessDenied(const QString &rfidUid, const QString &reason)
{
    addActivityEntry(QString("Unknown accessed via %1 - ❌ DENIED (%2)").arg(rfidUid, reason), false);
}