#include "emailpanel.h"
#include "Connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QRegularExpression>
#include <QTcpSocket>
#include <QSslSocket>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>

EmailPanel::EmailPanel(QWidget *parent)
    : QWidget(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_selectedMemberCount(0)
    , m_characterCount(0)
    , m_estimatedCost(0.0)
    , m_smtpSocket(nullptr)
    , m_smtpState(0)
    , m_lastMemberCount(0)
{
    setupUI();
    applyStyles();
    loadMembers();
    loadTemplates();
    
    // Setup auto-refresh timer for database changes
    m_refreshTimer = new QTimer(this);
    m_refreshTimer->setInterval(30000); // Check every 30 seconds
    connect(m_refreshTimer, &QTimer::timeout, this, &EmailPanel::checkForDatabaseUpdates);
    m_refreshTimer->start();
    
    // Setup statistics refresh timer
    m_statsTimer = new QTimer(this);
    m_statsTimer->setInterval(60000); // Update every minute
    connect(m_statsTimer, &QTimer::timeout, this, &EmailPanel::updateEmailStatistics);
    m_statsTimer->start();
    
    // Load initial statistics
    updateEmailStatistics();
    
    qDebug() << "📊 Email Panel initialized with auto-refresh enabled";
}

void EmailPanel::setupUI()
{
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    
    // Title
    QLabel *titleLabel = new QLabel("📧 Email Communications Center");
    titleLabel->setStyleSheet(
        "font-size: 24px; "
        "font-weight: bold; "
        "color: #2c3e50; "
        "padding: 10px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "stop:0 rgba(22, 165, 179, 0.1), stop:1 rgba(22, 165, 179, 0.05));"
        "border-radius: 8px; "
        "margin-bottom: 10px;"
    );
    titleLabel->setAlignment(Qt::AlignCenter);
    
    mainLayout->addWidget(titleLabel);
    
    // Main splitter
    m_mainSplitter = new QSplitter(Qt::Horizontal, this);
    m_mainSplitter->setHandleWidth(3);
    
    setupLeftPanel();
    setupRightPanel();
    
    m_mainSplitter->addWidget(m_leftPanel);
    m_mainSplitter->addWidget(m_rightPanel);
    m_mainSplitter->setSizes({300, 500}); // Left panel smaller
    
    mainLayout->addWidget(m_mainSplitter);
    
    setupStatusBar();
    mainLayout->addWidget(m_statusFrame);
}

void EmailPanel::setupLeftPanel()
{
    m_leftPanel = new QWidget();
    m_leftLayout = new QVBoxLayout(m_leftPanel);
    m_leftLayout->setSpacing(15);
    
    setupMemberList();
    setupHistorySection();
}

void EmailPanel::setupMemberList()
{
    // Member selection group
    m_memberGroup = new QGroupBox("👥 Select Recipients");
    m_memberLayout = new QVBoxLayout(m_memberGroup);
    
    // Search and filter row
    QHBoxLayout *searchLayout = new QHBoxLayout();
    
    m_searchEdit = new QLineEdit();
    m_searchEdit->setPlaceholderText("🔍 Search members...");
    m_searchEdit->setStyleSheet(
        "QLineEdit {"
        "   padding: 8px 12px;"
        "   border: 2px solid #e1e5e9;"
        "   border-radius: 6px;"
        "   font-size: 14px;"
        "}"
        "QLineEdit:focus {"
        "   border-color: #16a5b3;"
        "   outline: none;"
        "}"
    );
    
    m_filterComboBox = new QComboBox();
    m_filterComboBox->addItems({"All Members", "Active Only", "Inactive Only", 
                               "Payment Due", "Premium Members", "Basic Members"});
    m_filterComboBox->setStyleSheet(
        "QComboBox {"
        "   padding: 8px 12px;"
        "   border: 2px solid #e1e5e9;"
        "   border-radius: 6px;"
        "   font-size: 14px;"
        "   min-width: 120px;"
        "}"
        "QComboBox:focus {"
        "   border-color: #16a5b3;"
        "}"
    );
    
    // Refresh button
    m_refreshButton = new QPushButton("🔄 Refresh");
    m_refreshButton->setStyleSheet(
        "QPushButton {"
        "   padding: 8px 12px;"
        "   border: 2px solid #27ae60;"
        "   border-radius: 6px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   background: #27ae60;"
        "   color: white;"
        "   min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "   background: #229954;"
        "   border-color: #229954;"
        "}"
        "QPushButton:pressed {"
        "   background: #1e8449;"
        "   border-color: #1e8449;"
        "}"
    );
    m_refreshButton->setToolTip("Refresh member list from database");
    
    searchLayout->addWidget(m_searchEdit, 2);
    searchLayout->addWidget(m_filterComboBox, 1);
    searchLayout->addWidget(m_refreshButton, 0);
    
    // Select all checkbox
    m_selectAllCheckBox = new QCheckBox("Select All");
    m_selectAllCheckBox->setStyleSheet(
        "QCheckBox {"
        "   font-weight: bold;"
        "   color: #16a5b3;"
        "   spacing: 8px;"
        "}"
        "QCheckBox::indicator {"
        "   width: 18px;"
        "   height: 18px;"
        "}"
        "QCheckBox::indicator:unchecked {"
        "   border: 2px solid #bdc3c7;"
        "   border-radius: 3px;"
        "   background: white;"
        "}"
        "QCheckBox::indicator:checked {"
        "   border: 2px solid #16a5b3;"
        "   border-radius: 3px;"
        "   background: #16a5b3;"
        "   image: url(:/icons/icons/check.png);"
        "}"
    );
    
    // Member list
    m_memberListWidget = new QListWidget();
    m_memberListWidget->setStyleSheet(
        "QListWidget {"
        "   border: 2px solid #e1e5e9;"
        "   border-radius: 8px;"
        "   background: white;"
        "   selection-background-color: rgba(22, 165, 179, 0.1);"
        "}"
        "QListWidget::item {"
        "   padding: 8px 12px;"
        "   border-bottom: 1px solid #f1f3f4;"
        "}"
        "QListWidget::item:hover {"
        "   background: rgba(22, 165, 179, 0.05);"
        "}"
        "QListWidget::item:selected {"
        "   background: rgba(22, 165, 179, 0.15);"
        "   color: #2c3e50;"
        "}"
    );
    m_memberListWidget->setMinimumHeight(200);
    
    // Selected count label
    m_selectedCountLabel = new QLabel("0 members selected");
    m_selectedCountLabel->setStyleSheet(
        "color: #16a5b3; "
        "font-weight: bold; "
        "padding: 5px; "
        "background: rgba(22, 165, 179, 0.1); "
        "border-radius: 4px;"
    );
    m_selectedCountLabel->setAlignment(Qt::AlignCenter);
    
    // Add to layout
    m_memberLayout->addLayout(searchLayout);
    m_memberLayout->addWidget(m_selectAllCheckBox);
    m_memberLayout->addWidget(m_memberListWidget, 1);
    m_memberLayout->addWidget(m_selectedCountLabel);
    
    m_leftLayout->addWidget(m_memberGroup, 1);
    
    // Connect signals
    connect(m_searchEdit, &QLineEdit::textChanged, this, &EmailPanel::onSearchTextChanged);
    connect(m_filterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &EmailPanel::onFilterChanged);
    connect(m_refreshButton, &QPushButton::clicked, this, &EmailPanel::onRefreshMembersClicked);
    connect(m_selectAllCheckBox, &QCheckBox::toggled, this, &EmailPanel::onSelectAllMembers);
    connect(m_memberListWidget, &QListWidget::itemChanged, this, &EmailPanel::onMemberSelectionChanged);
}

void EmailPanel::setupHistorySection()
{
    // History group
    m_historyGroup = new QGroupBox("📊 Email Statistics");
    m_historyLayout = new QVBoxLayout(m_historyGroup);
    
    // Statistics labels
    m_todayCountLabel = new QLabel("Today: 0 sent");
    m_weekCountLabel = new QLabel("This Week: 0 sent");
    m_monthCountLabel = new QLabel("This Month: 0 sent");
    
    QString statLabelStyle = 
        "QLabel {"
        "   padding: 8px 12px;"
        "   background: rgba(22, 165, 179, 0.05);"
        "   border-left: 4px solid #16a5b3;"
        "   margin: 2px 0;"
        "   font-size: 14px;"
        "}";
    
    m_todayCountLabel->setStyleSheet(statLabelStyle);
    m_weekCountLabel->setStyleSheet(statLabelStyle);
    m_monthCountLabel->setStyleSheet(statLabelStyle);
    
    m_viewHistoryButton = new QPushButton("📈 View Full History");
    m_viewHistoryButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "   stop:0 #16a5b3, stop:1 #139aa6);"
        "   color: white;"
        "   border: none;"
        "   padding: 10px 15px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "   stop:0 #139aa6, stop:1 #0f858f);"
        "}"
    );
    
    // Add to layout
    m_historyLayout->addWidget(m_todayCountLabel);
    m_historyLayout->addWidget(m_weekCountLabel);
    m_historyLayout->addWidget(m_monthCountLabel);
    m_historyLayout->addSpacing(10);
    m_historyLayout->addWidget(m_viewHistoryButton);
    
    m_leftLayout->addWidget(m_historyGroup);
}

void EmailPanel::setupRightPanel()
{
    m_rightPanel = new QWidget();
    m_rightLayout = new QVBoxLayout(m_rightPanel);
    m_rightLayout->setSpacing(15);
    
    setupMessageComposer();
    setupAttachmentSection();
}

void EmailPanel::setupMessageComposer()
{
    // Message composer group
    m_composerGroup = new QGroupBox("✍️ Compose Message");
    m_composerLayout = new QVBoxLayout(m_composerGroup);
    
    // Template selection row
    QHBoxLayout *templateLayout = new QHBoxLayout();
    
    QLabel *templateLabel = new QLabel("Template:");
    templateLabel->setStyleSheet("font-weight: bold; color: #2c3e50;");
    
    m_templateComboBox = new QComboBox();
    m_templateComboBox->addItems({"Select Template...", "Welcome Message", 
                                 "Payment Reminder", "Activity Alert", 
                                 "Membership Expiry", "Summer Activities", "Custom Message"});
    m_templateComboBox->setStyleSheet(
        "QComboBox {"
        "   padding: 8px 12px;"
        "   border: 2px solid #e1e5e9;"
        "   border-radius: 6px;"
        "   font-size: 14px;"
        "   min-width: 150px;"
        "}"
        "QComboBox:focus {"
        "   border-color: #16a5b3;"
        "}"
    );
    
    m_createTemplateButton = new QPushButton("+ Create Template");
    m_createTemplateButton->setStyleSheet(
        "QPushButton {"
        "   background: rgba(22, 165, 179, 0.1);"
        "   color: #16a5b3;"
        "   border: 2px solid rgba(22, 165, 179, 0.3);"
        "   padding: 8px 15px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(22, 165, 179, 0.2);"
        "   border-color: #16a5b3;"
        "}"
    );
    
    templateLayout->addWidget(templateLabel);
    templateLayout->addWidget(m_templateComboBox, 1);
    templateLayout->addWidget(m_createTemplateButton);
    
    // Message text area
    QLabel *messageLabel = new QLabel("Message:");
    messageLabel->setStyleSheet("font-weight: bold; color: #2c3e50; margin-top: 10px;");
    
    m_messageTextEdit = new QTextEdit();
    m_messageTextEdit->setPlaceholderText("Type your message here...\n\nUse variables like:\n{name} - Member name\n{balance} - Account balance\n{membership_type} - Membership type");
    m_messageTextEdit->setStyleSheet(
        "QTextEdit {"
        "   border: 2px solid #e1e5e9;"
        "   border-radius: 8px;"
        "   padding: 12px;"
        "   font-size: 14px;"
        "   line-height: 1.4;"
        "}"
        "QTextEdit:focus {"
        "   border-color: #16a5b3;"
        "   outline: none;"
        "}"
    );
    m_messageTextEdit->setMinimumHeight(120);
    m_messageTextEdit->setMaximumHeight(180);
    
    // Variables help
    m_variablesLabel = new QLabel(
        "💡 <b>Available variables:</b> {name}, {email}, {balance}, {membership_type}, {expiry_date}"
    );
    m_variablesLabel->setStyleSheet(
        "color: #6c757d; "
        "background: rgba(108, 117, 125, 0.1); "
        "padding: 8px 12px; "
        "border-radius: 6px; "
        "font-size: 12px;"
    );
    m_variablesLabel->setWordWrap(true);
    
    // Scheduling section
    m_scheduleGroup = new QGroupBox("⏰ Send Options");
    m_scheduleLayout = new QHBoxLayout(m_scheduleGroup);
    
    m_sendNowRadio = new QRadioButton("Send Now");
    m_sendNowRadio->setChecked(true);
    m_sendNowRadio->setStyleSheet("font-weight: bold; color: #27ae60;");
    
    m_scheduleRadio = new QRadioButton("Schedule for:");
    m_scheduleRadio->setStyleSheet("font-weight: bold; color: #f39c12;");
    
    m_scheduleDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime().addSecs(3600));
    m_scheduleDateTimeEdit->setDisplayFormat("MMM dd, yyyy - hh:mm AP");
    m_scheduleDateTimeEdit->setEnabled(false);
    m_scheduleDateTimeEdit->setStyleSheet(
        "QDateTimeEdit {"
        "   padding: 8px 12px;"
        "   border: 2px solid #e1e5e9;"
        "   border-radius: 6px;"
        "   font-size: 14px;"
        "}"
        "QDateTimeEdit:enabled:focus {"
        "   border-color: #f39c12;"
        "}"
        "QDateTimeEdit:disabled {"
        "   background: #f8f9fa;"
        "   color: #6c757d;"
        "}"
    );
    
    m_scheduleLayout->addWidget(m_sendNowRadio);
    m_scheduleLayout->addWidget(m_scheduleRadio);
    m_scheduleLayout->addWidget(m_scheduleDateTimeEdit, 1);
    
    // Add to layout
    m_composerLayout->addLayout(templateLayout);
    m_composerLayout->addWidget(messageLabel);
    m_composerLayout->addWidget(m_messageTextEdit, 1);
    m_composerLayout->addWidget(m_variablesLabel);
    m_composerLayout->addWidget(m_scheduleGroup);
    
    m_rightLayout->addWidget(m_composerGroup, 1);
    
    // Connect signals
    connect(m_templateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &EmailPanel::onTemplateChanged);
    connect(m_messageTextEdit, &QTextEdit::textChanged, this, &EmailPanel::onMessageTextChanged);
    connect(m_createTemplateButton, &QPushButton::clicked, this, &EmailPanel::onCreateTemplateClicked);
    connect(m_scheduleRadio, &QRadioButton::toggled, 
            [this](bool checked) { m_scheduleDateTimeEdit->setEnabled(checked); });
}

void EmailPanel::setupAttachmentSection()
{
    // Attachment group
    m_attachmentGroup = new QGroupBox("📎 Attachments (Optional)");
    m_attachmentLayout = new QVBoxLayout(m_attachmentGroup);
    
    // Add attachment button
    m_addAttachmentButton = new QPushButton("+ Add File");
    m_addAttachmentButton->setStyleSheet(
        "QPushButton {"
        "   background: rgba(52, 152, 219, 0.1);"
        "   color: #3498db;"
        "   border: 2px solid rgba(52, 152, 219, 0.3);"
        "   padding: 10px 20px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(52, 152, 219, 0.2);"
        "   border-color: #3498db;"
        "}"
    );
    
    // Attachments list
    m_attachmentListWidget = new QListWidget();
    m_attachmentListWidget->setStyleSheet(
        "QListWidget {"
        "   border: 2px solid #e1e5e9;"
        "   border-radius: 8px;"
        "   background: white;"
        "   min-height: 80px;"
        "   max-height: 120px;"
        "}"
        "QListWidget::item {"
        "   padding: 6px 10px;"
        "   border-bottom: 1px solid #f1f3f4;"
        "   font-size: 13px;"
        "}"
        "QListWidget::item:hover {"
        "   background: rgba(231, 76, 60, 0.05);"
        "}"
        "QListWidget::item:selected {"
        "   background: rgba(231, 76, 60, 0.1);"
        "   color: #e74c3c;"
        "}"
    );
    
    // Clear attachments button
    m_clearAttachmentsButton = new QPushButton("🗑️ Clear All");
    m_clearAttachmentsButton->setStyleSheet(
        "QPushButton {"
        "   background: rgba(231, 76, 60, 0.1);"
        "   color: #e74c3c;"
        "   border: 2px solid rgba(231, 76, 60, 0.3);"
        "   padding: 8px 16px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(231, 76, 60, 0.2);"
        "   border-color: #e74c3c;"
        "}"
    );
    m_clearAttachmentsButton->setEnabled(false);
    
    // Attachment info label
    m_attachmentInfoLabel = new QLabel("No attachments selected");
    m_attachmentInfoLabel->setStyleSheet(
        "color: #6c757d;"
        "font-size: 12px;"
        "padding: 5px;"
        "background: rgba(108, 117, 125, 0.1);"
        "border-radius: 4px;"
    );
    m_attachmentInfoLabel->setAlignment(Qt::AlignCenter);
    
    // Layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_addAttachmentButton);
    buttonLayout->addWidget(m_clearAttachmentsButton);
    
    m_attachmentLayout->addLayout(buttonLayout);
    m_attachmentLayout->addWidget(m_attachmentListWidget);
    m_attachmentLayout->addWidget(m_attachmentInfoLabel);
    
    m_rightLayout->addWidget(m_attachmentGroup);
    
    // Connect signals
    connect(m_addAttachmentButton, &QPushButton::clicked, this, &EmailPanel::onAddAttachmentClicked);
    connect(m_clearAttachmentsButton, &QPushButton::clicked, this, &EmailPanel::onClearAttachmentsClicked);
    connect(m_attachmentListWidget, &QListWidget::itemDoubleClicked, this, &EmailPanel::onRemoveAttachmentClicked);
}

void EmailPanel::setupStatusBar()
{
    m_statusFrame = new QFrame();
    m_statusFrame->setFrameStyle(QFrame::StyledPanel);
    m_statusFrame->setStyleSheet(
        "QFrame {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "   stop:0 rgba(22, 165, 179, 0.05), stop:1 rgba(22, 165, 179, 0.02));"
        "   border: 2px solid rgba(22, 165, 179, 0.2);"
        "   border-radius: 8px;"
        "   padding: 8px;"
        "}"
    );
    
    m_statusLayout = new QHBoxLayout(m_statusFrame);
    
    // Status labels
    m_recipientsLabel = new QLabel("Recipients: 0");
    m_charactersLabel = new QLabel("Characters: 0/160");
    m_costLabel = new QLabel("Est. Cost: $0.00");
    
    QString statusLabelStyle = 
        "QLabel {"
        "   font-weight: bold;"
        "   color: #2c3e50;"
        "   padding: 5px 10px;"
        "   background: rgba(255, 255, 255, 0.7);"
        "   border-radius: 4px;"
        "}";
    
    m_recipientsLabel->setStyleSheet(statusLabelStyle);
    m_charactersLabel->setStyleSheet(statusLabelStyle);
    m_costLabel->setStyleSheet(statusLabelStyle);
    
    // Action buttons
    m_previewButton = new QPushButton("👁️ Preview");
    m_previewButton->setStyleSheet(
        "QPushButton {"
        "   background: rgba(52, 152, 219, 0.1);"
        "   color: #3498db;"
        "   border: 2px solid rgba(52, 152, 219, 0.3);"
        "   padding: 10px 20px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(52, 152, 219, 0.2);"
        "   border-color: #3498db;"
        "}"
    );
    
    m_testButton = new QPushButton("🧪 Test API");
    m_testButton->setStyleSheet(
        "QPushButton {"
        "   background: rgba(243, 156, 18, 0.1);"
        "   color: #f39c12;"
        "   border: 2px solid rgba(243, 156, 18, 0.3);"
        "   padding: 10px 20px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(243, 156, 18, 0.2);"
        "   border-color: #f39c12;"
        "}"
    );
    
    m_sendButton = new QPushButton("📧 Send Email");
    m_sendButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "   stop:0 #27ae60, stop:1 #229954);"
        "   color: white;"
        "   border: none;"
        "   padding: 12px 25px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "   stop:0 #229954, stop:1 #1e8449);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "   stop:0 #1e8449, stop:1 #196f3d);"
        "}"
    );
    m_sendButton->setEnabled(false);
    
    // Add to layout
    m_statusLayout->addWidget(m_recipientsLabel);
    m_statusLayout->addWidget(m_charactersLabel);
    m_statusLayout->addWidget(m_costLabel);
    m_statusLayout->addStretch();
    m_statusLayout->addWidget(m_testButton);
    m_statusLayout->addWidget(m_previewButton);
    m_statusLayout->addWidget(m_sendButton);
    
    // Connect signals
    connect(m_testButton, &QPushButton::clicked, this, &EmailPanel::onTestAPIClicked);
    connect(m_previewButton, &QPushButton::clicked, this, &EmailPanel::onPreviewClicked);
    connect(m_sendButton, &QPushButton::clicked, this, &EmailPanel::onSendClicked);
}

void EmailPanel::applyStyles()
{
    // Apply consistent styling to group boxes
    QString groupBoxStyle = 
        "QGroupBox {"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "   color: #2c3e50;"
        "   border: 2px solid rgba(22, 165, 179, 0.2);"
        "   border-radius: 8px;"
        "   margin-top: 10px;"
        "   padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top left;"
        "   padding: 5px 10px;"
        "   background: rgba(22, 165, 179, 0.1);"
        "   border-radius: 4px;"
        "   color: #16a5b3;"
        "}";
    
    m_memberGroup->setStyleSheet(groupBoxStyle);
    m_historyGroup->setStyleSheet(groupBoxStyle);
    m_composerGroup->setStyleSheet(groupBoxStyle);
    m_attachmentGroup->setStyleSheet(groupBoxStyle);
    m_scheduleGroup->setStyleSheet(groupBoxStyle);
    
    // Splitter styling
    m_mainSplitter->setStyleSheet(
        "QSplitter::handle {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "   stop:0 rgba(22, 165, 179, 0.3), stop:1 rgba(22, 165, 179, 0.1));"
        "   border-radius: 1px;"
        "}"
        "QSplitter::handle:hover {"
        "   background: rgba(22, 165, 179, 0.5);"
        "}"
    );
}

void EmailPanel::loadMembers()
{
    // Load actual members from database
    loadMembersFromDatabase();
}

void EmailPanel::loadTemplates()
{
    // Initialize HTML template contents with dynamic placeholders
    m_templateContents["Welcome Message"] = 
        "We're thrilled to welcome you to our **Summer Club 2025**! Your {membership_type} membership is now active. "
        "Join us for a season full of exciting activities, learning opportunities, and unforgettable memories.";
    
    m_templateContents["Payment Reminder"] = 
        "Your Summer Club payment reminder! Your {membership_type} payment of ${balance} is due soon. "
        "Please visit our office or pay online to ensure uninterrupted access to all club activities and services.";
    
    m_templateContents["Activity Alert"] = 
        "Exciting news about our Summer Club activities! We have new programs and events designed just for our members. "
        "Don't miss out on swimming lessons, sports tournaments, arts & crafts, and outdoor adventures.";
    
    m_templateContents["Membership Expiry"] = 
        "Important notice about your Summer Club membership! Your {membership_type} membership expires on {expiry_date}. "
        "Renew now to continue enjoying our summer activities, facilities, and exclusive member benefits.";
        
    m_templateContents["Summer Activities"] = 
        "Get ready for an amazing summer at Summer Club 2025! We have incredible activities planned including swimming, "
        "sports, arts & crafts, outdoor adventures, and special events. Your membership gives you access to all facilities.";
    
    // Templates are now loaded only for the dropdown combo box
    // Attachment section replaces the template list widget
}

// Slot implementations
void EmailPanel::onMemberSelectionChanged()
{
    updateMemberCount();
    updateCostEstimate();
}

void EmailPanel::onTemplateChanged()
{
    QString selectedTemplate = m_templateComboBox->currentText();
    if (m_templateContents.contains(selectedTemplate)) {
        m_messageTextEdit->setPlainText(m_templateContents[selectedTemplate]);
    } else if (selectedTemplate == "Custom Message") {
        m_messageTextEdit->clear();
        m_messageTextEdit->setFocus();
    }
}

void EmailPanel::onMessageTextChanged()
{
    updateCharacterCount();
    updateCostEstimate();
}

void EmailPanel::onSendClicked()
{
    if (m_selectedMemberCount == 0) {
        QMessageBox::warning(this, "No Recipients", 
            "Please select at least one member to send email to.");
        return;
    }
    
    if (m_messageTextEdit->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Empty Message", 
            "Please enter a message to send.");
        return;
    }
    
    // Confirmation for bulk sends
    if (m_selectedMemberCount > 5) {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
            "Bulk Email Confirmation",
            QString("You are about to send email to %1 members.\n"
                   "Estimated cost: $%2\n\n"
                   "Are you sure you want to continue?")
            .arg(m_selectedMemberCount)
            .arg(m_estimatedCost, 0, 'f', 2),
            QMessageBox::Yes | QMessageBox::No);
        
        if (reply != QMessageBox::Yes) {
            return;
        }
    }
    
    // Send real Email using textbelt API
    sendEmailToSelectedMembers();
}

void EmailPanel::onScheduleClicked()
{
    // TODO: Implement scheduling functionality
}

void EmailPanel::onPreviewClicked()
{
    if (m_messageTextEdit->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Empty Message", 
            "Please enter a message to preview.");
        return;
    }
    
    // TODO: Show preview dialog with variable substitution
    QString message = m_messageTextEdit->toPlainText();
    QString previewMessage = message;
    previewMessage.replace("{name}", "John Smith");
    previewMessage.replace("{balance}", "45.00");
    previewMessage.replace("{membership_type}", "Premium");
    previewMessage.replace("{expiry_date}", "Dec 31, 2025");
    
    QMessageBox::information(this, "Message Preview", 
        QString("Preview (with sample data):\n\n%1").arg(previewMessage));
}

void EmailPanel::onSelectAllMembers(bool checked)
{
    for (int i = 0; i < m_memberListWidget->count(); ++i) {
        QListWidgetItem *item = m_memberListWidget->item(i);
        item->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
    }
    updateMemberCount();
}

void EmailPanel::onFilterChanged()
{
    applyMemberFilters();
}

void EmailPanel::onSearchTextChanged()
{
    applyMemberFilters();
}

void EmailPanel::onCreateTemplateClicked()
{
    // TODO: Implement template creation dialog
    QMessageBox::information(this, "Create Template", 
        "Template creation dialog will be implemented here.");
}

void EmailPanel::onTestAPIClicked()
{
    // Test Infobip API with a simple request
    QString testMessage = "🧪 Test Email from Summer Club Management System\n\nThis is a test email sent via Infobip API to verify the email system is working correctly.\n\nTimestamp: " + QDateTime::currentDateTime().toString();
    QString testEmail = "khalil27805@gmail.com"; // Your test email address
    
    QMessageBox::information(this, "Infobip API Test", 
        "Testing Infobip email API...\nThis will validate your email system configuration.");
    
    qDebug() << "=== Starting Infobip API Test ===";
    
    bool result = sendEmailInfobip(testEmail, "🧪 Summer Club - Infobip API Test", testMessage);
    
    if (result) {
        QMessageBox::information(this, "Infobip API Test Success", 
            "✅ Infobip API is working perfectly!\n\n"
            "Your email system is configured correctly.\n"
            "Check your email inbox for the test message!");
    } else {
        QMessageBox::warning(this, "Infobip API Test Failed", 
            "❌ Infobip API test failed!\n\n"
            "Check the console output for detailed error information.\n\n"
            "Common issues:\n"
            "• API key expired or invalid\n"
            "• Network/firewall blocking\n"
            "• Insufficient account credits\n"
            "• Sender email not verified");
    }
    
    qDebug() << "=== API Test Complete ===";
}

void EmailPanel::onAddAttachmentClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Select File to Attach",
        "",
        "All Files (*.*);;"
        "Documents (*.pdf *.doc *.docx *.txt);;"
        "Images (*.png *.jpg *.jpeg *.gif *.bmp);;"
        "Spreadsheets (*.xls *.xlsx *.csv)");
    
    if (!fileName.isEmpty()) {
        // Check if file already exists in attachments
        if (m_attachmentPaths.contains(fileName)) {
            QMessageBox::information(this, "File Already Attached", 
                "This file is already attached to the email.");
            return;
        }
        
        // Check file size (limit to 10MB)
        QFileInfo fileInfo(fileName);
        qint64 fileSize = fileInfo.size();
        const qint64 maxSize = 10 * 1024 * 1024; // 10MB
        
        if (fileSize > maxSize) {
            QMessageBox::warning(this, "File Too Large", 
                QString("File size (%1 MB) exceeds the 10MB limit.\nPlease select a smaller file.")
                .arg(fileSize / (1024.0 * 1024.0), 0, 'f', 1));
            return;
        }
        
        // Add to attachments
        m_attachmentPaths.append(fileName);
        
        // Update UI
        QString displayName = fileInfo.fileName();
        QString sizeStr = QString("(%1 KB)").arg(fileSize / 1024.0, 0, 'f', 1);
        
        QListWidgetItem *item = new QListWidgetItem(QString("📎 %1 %2").arg(displayName, sizeStr));
        item->setData(Qt::UserRole, fileName); // Store full path
        item->setToolTip(QString("Full path: %1\nDouble-click to remove").arg(fileName));
        m_attachmentListWidget->addItem(item);
        
        updateAttachmentInfo();
        
        qDebug() << "📎 Attachment added:" << displayName << "(" << sizeStr << ")";
    }
}

void EmailPanel::onClearAttachmentsClicked()
{
    if (m_attachmentPaths.isEmpty()) {
        return;
    }
    
    QMessageBox::StandardButton reply = QMessageBox::question(this,
        "Clear Attachments",
        QString("Remove all %1 attachments?").arg(m_attachmentPaths.size()),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        m_attachmentPaths.clear();
        m_attachmentListWidget->clear();
        updateAttachmentInfo();
        qDebug() << "📎 All attachments cleared";
    }
}

void EmailPanel::onRemoveAttachmentClicked(QListWidgetItem* item)
{
    if (!item) return;
    
    QString filePath = item->data(Qt::UserRole).toString();
    QString fileName = QFileInfo(filePath).fileName();
    
    QMessageBox::StandardButton reply = QMessageBox::question(this,
        "Remove Attachment",
        QString("Remove \"%1\" from attachments?").arg(fileName),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        m_attachmentPaths.removeAll(filePath);
        delete item;
        updateAttachmentInfo();
        qDebug() << "📎 Attachment removed:" << fileName;
    }
}

void EmailPanel::updateAttachmentInfo()
{
    if (m_attachmentPaths.isEmpty()) {
        m_attachmentInfoLabel->setText("No attachments selected");
        m_attachmentInfoLabel->setStyleSheet(
            "color: #6c757d;"
            "font-size: 12px;"
            "padding: 5px;"
            "background: rgba(108, 117, 125, 0.1);"
            "border-radius: 4px;"
        );
        m_clearAttachmentsButton->setEnabled(false);
    } else {
        // Calculate total size
        qint64 totalSize = 0;
        for (const QString& path : m_attachmentPaths) {
            totalSize += QFileInfo(path).size();
        }
        
        QString sizeStr;
        if (totalSize < 1024 * 1024) {
            sizeStr = QString("%1 KB").arg(totalSize / 1024.0, 0, 'f', 1);
        } else {
            sizeStr = QString("%1 MB").arg(totalSize / (1024.0 * 1024.0), 0, 'f', 1);
        }
        
        m_attachmentInfoLabel->setText(QString("%1 file(s) attached • %2")
            .arg(m_attachmentPaths.size()).arg(sizeStr));
        m_attachmentInfoLabel->setStyleSheet(
            "color: #27ae60;"
            "font-size: 12px;"
            "padding: 5px;"
            "background: rgba(39, 174, 96, 0.1);"
            "border-radius: 4px;"
        );
        m_clearAttachmentsButton->setEnabled(true);
    }
}

void EmailPanel::onRefreshMembersClicked()
{
    // Show loading feedback
    m_refreshButton->setText("🔄 Refreshing...");
    m_refreshButton->setEnabled(false);
    
    // Force refresh from database
    qDebug() << "🔄 Manual refresh requested - reloading members from database";
    
    // Clear current selections
    m_selectAllCheckBox->setChecked(false);
    
    // Reload members from database
    loadMembers();
    
    // Update member count for auto-refresh tracking
    if (!m_allMembers.isEmpty()) {
        m_lastMemberCount = m_allMembers.size();
        qDebug() << "✅ Manual refresh complete - loaded" << m_lastMemberCount << "members";
        
        // Show success feedback briefly
        m_refreshButton->setText("✅ Updated!");
        QTimer::singleShot(1500, [this]() {
            m_refreshButton->setText("🔄 Refresh");
            m_refreshButton->setEnabled(true);
        });
    } else {
        qDebug() << "⚠️ No members loaded during refresh";
        m_refreshButton->setText("🔄 Refresh");
        m_refreshButton->setEnabled(true);
    }
}

void EmailPanel::updateMemberCount()
{
    int count = 0;
    for (int i = 0; i < m_memberListWidget->count(); ++i) {
        if (m_memberListWidget->item(i)->checkState() == Qt::Checked) {
            count++;
        }
    }
    
    m_selectedMemberCount = count;
    m_selectedCountLabel->setText(QString("%1 members selected").arg(count));
    m_recipientsLabel->setText(QString("Recipients: %1").arg(count));
    
    // Enable/disable send button
    m_sendButton->setEnabled(count > 0 && !m_messageTextEdit->toPlainText().trimmed().isEmpty());
}

void EmailPanel::updateCharacterCount()
{
    m_characterCount = m_messageTextEdit->toPlainText().length();
    m_charactersLabel->setText(QString("Characters: %1/160").arg(m_characterCount));
    
    // Change color based on character count
    if (m_characterCount > 160) {
        m_charactersLabel->setStyleSheet(
            "QLabel { font-weight: bold; color: #e74c3c; "
            "padding: 5px 10px; background: rgba(231, 76, 60, 0.1); border-radius: 4px; }"
        );
    } else if (m_characterCount > 140) {
        m_charactersLabel->setStyleSheet(
            "QLabel { font-weight: bold; color: #f39c12; "
            "padding: 5px 10px; background: rgba(243, 156, 18, 0.1); border-radius: 4px; }"
        );
    } else {
        m_charactersLabel->setStyleSheet(
            "QLabel { font-weight: bold; color: #2c3e50; "
            "padding: 5px 10px; background: rgba(255, 255, 255, 0.7); border-radius: 4px; }"
        );
    }
    
    // Enable/disable send button
    m_sendButton->setEnabled(m_selectedMemberCount > 0 && !m_messageTextEdit->toPlainText().trimmed().isEmpty());
}

void EmailPanel::updateCostEstimate()
{
    // textbelt is free for 1 Email per day, then paid
    // For estimation: $0.075 per Email (typical rate)
    double costPerEmail = 0.075;
    int EmailCount = m_selectedMemberCount;
    
    // If message is over 160 characters, it becomes multiple Email
    if (m_characterCount > 160) {
        int parts = (m_characterCount + 159) / 160; // Ceiling division
        EmailCount *= parts;
    }
    
    m_estimatedCost = EmailCount * costPerEmail;
    m_costLabel->setText(QString("Est. Cost: $%1").arg(m_estimatedCost, 0, 'f', 2));
    
    // Change color based on cost
    if (m_estimatedCost > 5.0) {
        m_costLabel->setStyleSheet(
            "QLabel { font-weight: bold; color: #e74c3c; "
            "padding: 5px 10px; background: rgba(231, 76, 60, 0.1); border-radius: 4px; }"
        );
    } else if (m_estimatedCost > 1.0) {
        m_costLabel->setStyleSheet(
            "QLabel { font-weight: bold; color: #f39c12; "
            "padding: 5px 10px; background: rgba(243, 156, 18, 0.1); border-radius: 4px; }"
        );
    } else {
        m_costLabel->setStyleSheet(
            "QLabel { font-weight: bold; color: #27ae60; "
            "padding: 5px 10px; background: rgba(39, 174, 96, 0.1); border-radius: 4px; }"
        );
    }
}

void EmailPanel::filterMembers()
{
    QString searchText = m_searchEdit->text().toLower();
    QString filterType = m_filterComboBox->currentText();
    
    for (int i = 0; i < m_memberListWidget->count(); ++i) {
        QListWidgetItem *item = m_memberListWidget->item(i);
        QString itemText = item->text().toLower();
        
        bool matchesSearch = searchText.isEmpty() || itemText.contains(searchText);
        bool matchesFilter = true;
        
        if (filterType == "Active Only") {
            matchesFilter = itemText.contains("(active)");
        } else if (filterType == "Inactive Only") {
            matchesFilter = itemText.contains("(inactive)");
        } else if (filterType == "Payment Due") {
            matchesFilter = itemText.contains("(payment due)");
        } else if (filterType == "Premium Members") {
            matchesFilter = itemText.contains("premium");
        } else if (filterType == "Basic Members") {
            matchesFilter = itemText.contains("basic");
        }
        
        item->setHidden(!(matchesSearch && matchesFilter));
    }
}

void EmailPanel::loadMembersFromDatabase()
{
    m_allMembers.clear();
    
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME, LAST_NAME, EMAIL, SUBSCRIPTION_PLAN, GENDER, AGE, JOIN_DATE FROM SUMMERCLUB.MEMBERS ORDER BY FIRST_NAME, LAST_NAME");
    
    if (query.exec()) {
        while (query.next()) {
            MemberData member;
            member.cin = query.value("CIN").toString();
            member.firstName = query.value("FIRST_NAME").toString();
            member.lastName = query.value("LAST_NAME").toString();
            member.email = query.value("EMAIL").toString();
            member.subscriptionPlan = query.value("SUBSCRIPTION_PLAN").toString();
            member.gender = query.value("GENDER").toString();
            member.age = query.value("AGE").toInt();
            member.joinDate = query.value("JOIN_DATE").toDate().toString("dd/MM/yyyy");
            
            // Only add members with valid email addresses
            if (!member.email.isEmpty() && member.email != "N/A" && member.email.contains("@")) {
                m_allMembers.append(member);
            }
        }
        
        // Update the filtered list and refresh UI
        m_filteredMembers = m_allMembers;
        refreshMemberList();
        
        qDebug() << "Loaded" << m_allMembers.size() << "members from database";
        
    } else {
        QMessageBox::warning(this, "Database Error", 
            "Failed to load members from database: " + query.lastError().text());
    }
}

void EmailPanel::refreshMemberList()
{
    m_memberListWidget->clear();
    
    for (const MemberData& member : m_filteredMembers) {
        QString displayText = QString("%1 %2 (%3)")
            .arg(member.firstName)
            .arg(member.lastName)
            .arg(member.email);
            
        QString detailText = QString("Plan: %1 | Age: %2 | Gender: %3")
            .arg(member.subscriptionPlan)
            .arg(member.age)
            .arg(member.gender);
            
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(displayText + "\n" + detailText);
        item->setData(Qt::UserRole, member.cin); // Store CIN for identification
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        
        // Add styling based on subscription plan
        if (member.subscriptionPlan.toLower().contains("premium")) {
            item->setBackground(QColor(255, 248, 220)); // Light gold
        } else if (member.subscriptionPlan.toLower().contains("annual")) {
            item->setBackground(QColor(240, 248, 255)); // Light blue
        }
        
        m_memberListWidget->addItem(item);
    }
    
    updateMemberCount();
}

void EmailPanel::applyMemberFilters()
{
    QString searchText = m_searchEdit->text().toLower();
    QString filterType = m_filterComboBox->currentText();
    
    m_filteredMembers.clear();
    
    for (const MemberData& member : m_allMembers) {
        // Apply search filter
        bool matchesSearch = searchText.isEmpty() || 
            member.firstName.toLower().contains(searchText) ||
            member.lastName.toLower().contains(searchText) ||
            member.email.contains(searchText) ||
            member.email.toLower().contains(searchText);
            
        // Apply category filter
        bool matchesFilter = true;
        if (filterType == "Premium Members") {
            matchesFilter = member.subscriptionPlan.toLower().contains("premium");
        } else if (filterType == "Basic Members") {
            matchesFilter = member.subscriptionPlan.toLower().contains("basic") || 
                           member.subscriptionPlan.toLower().contains("monthly");
        } else if (filterType == "Annual Members") {
            matchesFilter = member.subscriptionPlan.toLower().contains("annual");
        } else if (filterType == "Male Members") {
            matchesFilter = member.gender.toLower() == "male";
        } else if (filterType == "Female Members") {
            matchesFilter = member.gender.toLower() == "female";
        } else if (filterType == "Under 25") {
            matchesFilter = member.age < 25;
        } else if (filterType == "25-40") {
            matchesFilter = member.age >= 25 && member.age <= 40;
        } else if (filterType == "Over 40") {
            matchesFilter = member.age > 40;
        }
        
        if (matchesSearch && matchesFilter) {
            m_filteredMembers.append(member);
        }
    }
    
    refreshMemberList();
}

void EmailPanel::refreshMemberData()
{
    // Reload members from database to get latest data
    loadMembersFromDatabase();
}

QString EmailPanel::formatEmailAddress(const QString& email)
{
    // Validate and format email address
    QString cleanEmail = email.trimmed().toLower();
    
    // Basic email validation
    if (!cleanEmail.contains('@') || !cleanEmail.contains('.')) {
        return QString(); // Invalid email
    }
    
    // Additional validation - check for valid domain
    QStringList parts = cleanEmail.split('@');
    if (parts.size() != 2 || parts[0].isEmpty() || parts[1].isEmpty()) {
        return QString();
    }
    
    return cleanEmail;
}

QString EmailPanel::generateHTMLEmail(const QString& content, const QString& memberName, const QString& membershipType, const QStringList& attachments)
{
    // Base HTML template with Summer Club 2025 styling
    QString htmlTemplate = R"(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Summer Club 2025</title>
  <style>
    body { font-family: Arial, sans-serif; margin:0; padding:0; background-color:#f4f4f4; }
    .container { max-width:600px; margin:20px auto; background-color:#ffffff; border-radius:10px; overflow:hidden; box-shadow:0 4px 8px rgba(0,0,0,0.1); }
    .header {
      background: linear-gradient(135deg, #a069b0, #ffb347);
      color:white;
      text-align:center;
      padding:30px 20px;
      position: relative;
    }
    .header img { width:100%; border-bottom:2px solid white; border-radius:10px 10px 0 0; }
    .header h1 { margin:20px 0 5px 0; font-size:28px; }
    .header p { margin:0; font-size:16px; }
    .content { padding:20px; color:#333333; line-height:1.6; }
    .content h2 { color:#a069b0; }
    .button { display:inline-block; padding:12px 20px; margin:20px 0; background-color:#a069b0; color:white; text-decoration:none; border-radius:5px; }
    .footer { text-align:center; font-size:12px; color:#888888; padding:15px; background-color:#f4f4f4; }
    ul { padding-left:20px; }
    .highlight { background-color: #fff3cd; padding: 10px; border-left: 4px solid #a069b0; margin: 15px 0; }
  </style>
</head>
<body>
  <div class="container">
    <div class="header">
      <img src="https://cdn.discordapp.com/attachments/1355329351566102581/1442219551805931611/ABS2GSmxSmsPinmZXsfQnFcOUR1PV1wzq7sndtQ8ieGVZdwxO1M74WAPiUIfWZuDM-45AKUm4M1DYXqR-CQ8cqNiwyzMgYtuDF4VbkNJE3tTuF-n81NSXXtUGuicfQGeTWpdPXRfJS5zGe5ZIC8qO9c9nG24WYC8TEtGFQ8MgX29Aqm_iCZTIws1024-rj.png?ex=6924a320&is=692351a0&hm=3081103ca2272fecd3a1b071e23142c36a25445da5405791ca0570f7b3fe575a&" alt="Summer Fun Banner">
      <h1>Summer Club 2025</h1>
      <p>Adventure, Fun & Learning Await!</p>
    </div>
    <div class="content">
      <h2>Hello {MEMBER_NAME},</h2>
      <div class="highlight">
        {MAIN_CONTENT}
      </div>
      <h3>Your Membership Details:</h3>
      <ul>
        <li><strong>Plan:</strong> {MEMBERSHIP_TYPE}</li>
        <li><strong>Status:</strong> Active</li>
        <li><strong>Expires:</strong> {EXPIRY_DATE}</li>
      </ul>
      <p><strong>Club Location:</strong> Summer Club Center<br>
      <strong>Contact:</strong> SummerClub@selfserve.worlds-connected.co</p>
      {ATTACHMENTS_SECTION}
      <a href="mailto:SummerClub@selfserve.worlds-connected.co" class="button">Contact Us for More Info</a>
      <p>Thank you for being part of our Summer Club family!</p>
    </div>
    <div class="footer">
      <p>Summer Club 2025 | SummerClub@selfserve.worlds-connected.co | +216 72 797 221</p>
      <p>This email was sent to {EMAIL_ADDRESS}. If you received this by mistake, please ignore it.</p>
    </div>
  </div>
</body>
</html>
)";
    
    // Replace placeholders with actual data
    htmlTemplate.replace("{MEMBER_NAME}", memberName);
    htmlTemplate.replace("{MAIN_CONTENT}", content);
    htmlTemplate.replace("{MEMBERSHIP_TYPE}", membershipType);
    
    // Add attachments section if attachments exist
    QString attachmentsSection = "";
    if (!attachments.isEmpty()) {
        attachmentsSection = "<div class='highlight'><h3>📎 Attached Files:</h3><ul>";
        for (const QString& filePath : attachments) {
            QFileInfo fileInfo(filePath);
            QString fileName = fileInfo.fileName();
            QString fileSize = QString::number(fileInfo.size() / 1024.0, 'f', 1) + " KB";
            attachmentsSection += QString("<li><strong>%1</strong> (%2)</li>").arg(fileName, fileSize);
        }
        attachmentsSection += "</ul><p><em>Please find the attached files with this email.</em></p></div>";
    }
    htmlTemplate.replace("{ATTACHMENTS_SECTION}", attachmentsSection);
    
    return htmlTemplate;
}

void EmailPanel::sendEmailToSelectedMembers()
{
    QString message = m_messageTextEdit->toPlainText();
    int successCount = 0;
    int totalSelected = 0;
    
    // Count selected members and collect their info
    QList<MemberData> selectedMembers;
    for (int i = 0; i < m_memberListWidget->count(); ++i) {
        QListWidgetItem *item = m_memberListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            QString cin = item->data(Qt::UserRole).toString();
            // Find the member data
            for (const MemberData& member : m_filteredMembers) {
                if (member.cin == cin) {
                    selectedMembers.append(member);
                    break;
                }
            }
        }
    }
    
    totalSelected = selectedMembers.size();
    
    if (totalSelected == 0) {
        QMessageBox::warning(this, "No Recipients", "No members selected for Email.");
        return;
    }
    
    // Show progress dialog
    QProgressDialog *progressDialog = new QProgressDialog("Sending Email messages...", "Cancel", 0, totalSelected, this);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->show();
    
    // Send email to each selected member
    for (int i = 0; i < selectedMembers.size(); ++i) {
        const MemberData& member = selectedMembers[i];
        
        // Update progress
        progressDialog->setValue(i);
        progressDialog->setLabelText(QString("Sending to %1 %2...").arg(member.firstName, member.lastName));
        QApplication::processEvents();
        
        if (progressDialog->wasCanceled()) {
            break;
        }
        
        // Calculate dynamic expiry date based on subscription plan
        QDate currentDate = QDate::currentDate();
        QDate expiryDate;
        
        QString planLower = member.subscriptionPlan.toLower();
        if (planLower.contains("daily")) {
            expiryDate = currentDate.addDays(1);
        } else if (planLower.contains("weekly")) {
            expiryDate = currentDate.addDays(7);
        } else if (planLower.contains("monthly") || planLower.contains("month")) {
            expiryDate = currentDate.addDays(30);
        } else if (planLower.contains("annual") || planLower.contains("yearly") || planLower.contains("year")) {
            expiryDate = currentDate.addDays(365);
        } else {
            // Default to monthly for unknown plans
            expiryDate = currentDate.addDays(30);
        }
        
        QString formattedExpiryDate = expiryDate.toString("MMM dd, yyyy");
        
        // Personalize message content with member data
        QString personalizedContent = message;
        personalizedContent.replace("{name}", member.firstName + " " + member.lastName);
        personalizedContent.replace("{first_name}", member.firstName);
        personalizedContent.replace("{membership_type}", member.subscriptionPlan);
        personalizedContent.replace("{email}", member.email);
        personalizedContent.replace("{balance}", "0.00"); // Placeholder
        personalizedContent.replace("{expiry_date}", formattedExpiryDate);
        
        // Generate full HTML email using template
        QString htmlEmail = generateHTMLEmail(personalizedContent, 
                                              member.firstName + " " + member.lastName,
                                              member.subscriptionPlan,
                                              m_attachmentPaths);
        
        // Replace remaining placeholders in HTML template
        htmlEmail.replace("{EXPIRY_DATE}", formattedExpiryDate);
        htmlEmail.replace("{EMAIL_ADDRESS}", member.email);
        
        // Format and validate email address
        QString formattedEmail = formatEmailAddress(member.email);
        if (formattedEmail.isEmpty()) {
            qDebug() << "Invalid email address format:" << member.email;
            continue; // Skip this member
        }
        
        // Send HTML email via API with attachments
        if (sendSingleEmail(formattedEmail, "Summer Club 2025 - Update", htmlEmail, m_attachmentPaths)) {
            successCount++;
        }
        
        // Small delay to avoid rate limiting
        QThread::msleep(100);
    }
    
    progressDialog->setValue(totalSelected);
    progressDialog->close();
    delete progressDialog;
    
    // Show results
    if (successCount == totalSelected) {
        QMessageBox::information(this, "Email Sent Successfully", 
            QString("All %1 Email messages sent successfully!").arg(successCount));
    } else if (successCount > 0) {
        QMessageBox::warning(this, "Partial Success", 
            QString("Sent %1 out of %2 Email messages.\nSome messages may have failed due to network issues or invalid email addresss.").arg(successCount).arg(totalSelected));
    } else {
        QMessageBox::critical(this, "Email Failed", 
            "Failed to send email messages. Please check your internet connection and try again.");
    }
}

bool EmailPanel::sendSingleEmail(const QString& emailAddress, const QString& subject, const QString& htmlContent, const QStringList& attachments)
{
    qDebug() << "📧 Sending email via Infobip API to:" << emailAddress;
    qDebug() << "📎 Attachments count:" << attachments.size();
    
    // Use Infobip API with attachments support
    return sendEmailInfobip(emailAddress, subject, htmlContent, attachments);
}

// Infobip API Implementation Methods
bool EmailPanel::sendEmailInfobip(const QString& emailAddress, const QString& subject, const QString& htmlContent, const QStringList& attachments)
{
    qDebug() << "📧 Sending email via Infobip API to:" << emailAddress;
    qDebug() << "📝 Subject:" << subject;
    
    // Prepare Infobip API request
    QUrl url("https://jjk2wk.api.infobip.com/email/4/messages");
    QNetworkRequest request(url);
    
    // Set headers exactly like your Node.js test
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "App API_KEY_HERE"); // Replace with your actual API key
    request.setRawHeader("Accept", "application/json");
    
    // Create JSON payload matching your Node.js structure
    QJsonObject message;
    
    // Destinations array
    QJsonArray destinations;
    QJsonObject destination;
    QJsonArray toArray;
    QJsonObject toRecipient;
    toRecipient["destination"] = emailAddress;
    toArray.append(toRecipient);
    destination["to"] = toArray;
    destinations.append(destination);
    
    message["destinations"] = destinations;
    message["sender"] = "SummerClub@selfserve.worlds-connected.co";
    
    // Content
    QJsonObject content;
    content["subject"] = subject;
    
    // Convert HTML to plain text if needed
    QString plainText = htmlContent;
    plainText.remove(QRegularExpression("<[^>]*>"));  // Remove HTML tags
    
    // Use HTML if available, otherwise plain text
    if (htmlContent.contains("<html>") || htmlContent.contains("<p>") || htmlContent.contains("<br>")) {
        content["html"] = htmlContent;
        content["text"] = plainText;
    } else {
        content["text"] = htmlContent;
    }
    
    message["content"] = content;
    
    // Add attachments if any
    if (!attachments.isEmpty()) {
        QJsonArray attachmentsArray;
        for (const QString& filePath : attachments) {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly)) {
                QByteArray fileData = file.readAll();
                QString base64Data = fileData.toBase64();
                
                QJsonObject attachment;
                QFileInfo fileInfo(filePath);
                attachment["filename"] = fileInfo.fileName();
                attachment["content"] = base64Data;
                
                // Set content type based on file extension
                QString suffix = fileInfo.suffix().toLower();
                if (suffix == "pdf") {
                    attachment["contentType"] = "application/pdf";
                } else if (suffix == "jpg" || suffix == "jpeg") {
                    attachment["contentType"] = "image/jpeg";
                } else if (suffix == "png") {
                    attachment["contentType"] = "image/png";
                } else if (suffix == "txt") {
                    attachment["contentType"] = "text/plain";
                } else if (suffix == "doc" || suffix == "docx") {
                    attachment["contentType"] = "application/msword";
                } else {
                    attachment["contentType"] = "application/octet-stream";
                }
                
                attachmentsArray.append(attachment);
                qDebug() << "📎 Added attachment:" << fileInfo.fileName() << "(" << fileData.size() << "bytes)";
            } else {
                qDebug() << "❌ Failed to read attachment:" << filePath;
            }
        }
        
        if (!attachmentsArray.isEmpty()) {
            message["attachments"] = attachmentsArray;
            qDebug() << "📎 Total attachments added:" << attachmentsArray.size();
        }
    }
    
    // Wrap in messages array (like your Node.js example)
    QJsonObject payload;
    QJsonArray messages;
    messages.append(message);
    payload["messages"] = messages;
    
    // Convert to JSON
    QJsonDocument jsonDoc(payload);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);
    
    qDebug() << "📤 Infobip API Request:" << QString::fromUtf8(jsonData);
    
    // Send POST request
    QNetworkReply *reply = m_networkManager->post(request, jsonData);
    
    // Wait for response
    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    timeoutTimer.setInterval(15000); // 15 second timeout
    
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
    
    timeoutTimer.start();
    loop.exec();
    
    bool success = false;
    
    if (timeoutTimer.isActive()) {
        timeoutTimer.stop();
        
        int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QByteArray responseData = reply->readAll();
        
        qDebug() << "📥 Infobip Response Status:" << httpStatus;
        qDebug() << "📥 Infobip Response:" << QString::fromUtf8(responseData);
        
        if (httpStatus == 200 || httpStatus == 201 || httpStatus == 202) {
            // Parse response JSON
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
            if (!responseDoc.isNull()) {
                QJsonObject responseObj = responseDoc.object();
                QJsonArray messages = responseObj["messages"].toArray();
                
                if (!messages.isEmpty()) {
                    QJsonObject firstMessage = messages[0].toObject();
                    QJsonObject status = firstMessage["status"].toObject();
                    
                    int statusId = status["id"].toInt();
                    QString statusName = status["name"].toString();
                    QString statusDescription = status["description"].toString();
                    QString messageId = firstMessage["messageId"].toString();
                    
                    qDebug() << "📬 Message Status ID:" << statusId;
                    qDebug() << "📬 Message Status:" << statusName;
                    qDebug() << "📬 Message ID:" << messageId;
                    qDebug() << "📬 Description:" << statusDescription;
                    
                    // Status ID 1 means PENDING_ACCEPTED (success)
                    if (statusId == 1 || statusName.contains("PENDING") || statusName.contains("ACCEPTED")) {
                        success = true;
                        qDebug() << "✅ Email successfully sent via Infobip!";
                        
                        // Show success message to user
                        QMessageBox::information(this, "Email Sent Successfully", 
                            QString("Email sent successfully to %1!\n\n"
                                   "Message ID: %2\n"
                                   "Status: %3")
                            .arg(emailAddress, messageId, statusDescription));
                    } else {
                        qDebug() << "❌ Infobip rejected email:" << statusDescription;
                        
                        QMessageBox::warning(this, "Email Delivery Issue", 
                            QString("Email was submitted but may have delivery issues:\n\n"
                                   "Status: %1\n"
                                   "Description: %2\n"
                                   "Message ID: %3")
                            .arg(statusName, statusDescription, messageId));
                    }
                } else {
                    qDebug() << "❌ Empty messages array in Infobip response";
                }
            } else {
                qDebug() << "❌ Invalid JSON in Infobip response";
            }
        } else {
            // Handle API errors
            QString errorMsg = QString("HTTP %1").arg(httpStatus);
            
            QJsonDocument errorDoc = QJsonDocument::fromJson(responseData);
            if (!errorDoc.isNull()) {
                QJsonObject errorObj = errorDoc.object();
                QJsonObject requestError = errorObj["requestError"].toObject();
                
                if (!requestError.isEmpty()) {
                    errorMsg = QString("%1: %2")
                        .arg(requestError["text"].toString())
                        .arg(requestError["description"].toString());
                }
            }
            
            qDebug() << "❌ Infobip API Error:" << errorMsg;
            
            QMessageBox::warning(this, "Infobip API Error", 
                QString("Failed to send email via Infobip:\n\n%1\n\n"
                       "Please check:\n"
                       "• API key is valid and active\n"
                       "• Sender email is verified\n"
                       "• Account has sufficient credits\n"
                       "• Recipient email is valid")
                .arg(errorMsg));
        }
    } else {
        // Timeout
        reply->abort();
        qDebug() << "❌ Infobip API request timeout";
        
        QMessageBox::warning(this, "Request Timeout", 
            "Infobip API request timed out. Please check your connection and try again.");
    }
    
    // Log the email attempt to the database for statistics
    logEmailSent(emailAddress, subject, success);
    
    reply->deleteLater();
    return success;
}

// SMTP Implementation Methods
bool EmailPanel::sendEmailSMTP(const QString& emailAddress, const QString& subject, const QString& htmlContent)
{
    // Store email details for the SMTP session
    m_currentEmailAddress = emailAddress;
    m_currentSubject = subject;
    m_currentMessage = htmlContent;
    m_smtpState = 0;
    
    // Create SSL socket for secure SMTP connection
    if (m_smtpSocket) {
        m_smtpSocket->deleteLater();
    }
    
    m_smtpSocket = new QSslSocket(this);
    
    // Connect SMTP signals
    connect(m_smtpSocket, &QSslSocket::connected, this, &EmailPanel::onSMTPConnected);
    connect(m_smtpSocket, &QSslSocket::readyRead, this, &EmailPanel::onSMTPReadyRead);
    connect(m_smtpSocket, &QAbstractSocket::errorOccurred, this, &EmailPanel::onSMTPError);
    
    qDebug() << "🌐 Connecting to Brevo SMTP: smtp-relay.brevo.com:587";
    qDebug() << "📧 Email to:" << emailAddress;
    qDebug() << "📝 Subject:" << subject;
    
    // Connect to SMTP server
    m_smtpSocket->connectToHost("smtp-relay.brevo.com", 587);
    
    // Wait for connection with timeout
    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    timeoutTimer.setInterval(15000); // 15 second timeout
    
    bool emailSent = false;
    bool connectionFinished = false;
    
    connect(m_smtpSocket, &QSslSocket::disconnected, [&loop, &connectionFinished]() {
        connectionFinished = true;
        loop.quit();
    });
    
    connect(&timeoutTimer, &QTimer::timeout, [&loop, &emailSent, &connectionFinished]() {
        emailSent = false;
        connectionFinished = true;
        loop.quit();
    });
    
    // Wait for SMTP process to complete
    connect(this, &EmailPanel::emailSentSuccessfully, [&loop, &emailSent, &connectionFinished](bool success) {
        emailSent = success;
        connectionFinished = true;
        loop.quit();
    });
    
    timeoutTimer.start();
    loop.exec();
    
    // Note: Socket cleanup is handled by the SMTP state machine in cleanupSMTPConnection()
    return emailSent;
}

void EmailPanel::onSMTPConnected()
{
    qDebug() << "✅ Connected to Brevo SMTP server";
}

void EmailPanel::onSMTPReadyRead()
{
    if (!m_smtpSocket) {
        qDebug() << "❌ SMTP ReadyRead called but socket is null";
        return;
    }
    
    QByteArray response = m_smtpSocket->readAll();
    QString responseStr = QString::fromUtf8(response).trimmed();
    qDebug() << "SMTP Response:" << responseStr;
    
    // Parse SMTP response code
    int responseCode = responseStr.left(3).toInt();
    
    switch (m_smtpState) {
    case 0: // Initial connection
        if (responseCode == 220) {
            // Start TLS encryption
            sendSMTPCommand("STARTTLS");
            m_smtpState = 1;
        }
        break;
        
    case 1: // STARTTLS response
        if (responseCode == 220) {
            qDebug() << "🔒 Starting TLS encryption";
            m_smtpSocket->startClientEncryption();
            // Send EHLO after TLS
            sendSMTPCommand("EHLO summerclub.local");
            m_smtpState = 2;
        }
        break;
        
    case 2: // EHLO response
        if (responseCode == 250) {
            // Authenticate with Brevo credentials
            sendSMTPCommand("AUTH LOGIN");
            m_smtpState = 3;
        }
        break;
        
    case 3: // AUTH LOGIN response
        if (responseCode == 334) {
            // Send base64 encoded username
            QString encodedUsername = encodeBase64("9bd853001@smtp-brevo.com");
            sendSMTPCommand(encodedUsername);
            m_smtpState = 4;
        }
        break;
        
    case 4: // Username sent
        if (responseCode == 334) {
            // Send base64 encoded password
            QString encodedPassword = encodeBase64("");
            sendSMTPCommand(encodedPassword);
            m_smtpState = 5;
        }
        break;
        
        case 5: // Authentication response
        if (responseCode == 235) {
            qDebug() << "🔑 SMTP Authentication successful";
            // Set sender (MAIL FROM) - use the authenticated email address
            sendSMTPCommand(QString("MAIL FROM:<%1>").arg("9bd853001@smtp-brevo.com"));
            m_smtpState = 6;
        } else {
            qDebug() << "❌ SMTP Authentication failed:" << responseStr;
            emit emailSentSuccessfully(false);
            cleanupSMTPConnection();
        }
        break;    case 6: // MAIL FROM response
        if (responseCode == 250) {
            // Set recipient (RCPT TO)
            sendSMTPCommand(QString("RCPT TO:<%1>").arg(m_currentEmailAddress));
            m_smtpState = 7;
        } else {
            qDebug() << "❌ MAIL FROM failed:" << responseStr;
            emit emailSentSuccessfully(false);
            cleanupSMTPConnection();
        }
        break;
        
    case 7: // RCPT TO response
        if (responseCode == 250) {
            // Start message data
            sendSMTPCommand("DATA");
            m_smtpState = 8;
        } else {
            qDebug() << "❌ RCPT TO failed:" << responseStr;
            emit emailSentSuccessfully(false);
            cleanupSMTPConnection();
        }
        break;
        
    case 8: // DATA response
        if (responseCode == 354) {
            // Send email message
            QString emailMessage = createEmailMessage(m_currentEmailAddress, m_currentSubject, m_currentMessage);
            m_smtpSocket->write(emailMessage.toUtf8());
            m_smtpSocket->write("\r\n.\r\n"); // End of message
            m_smtpState = 9;
        } else {
            qDebug() << "❌ DATA command failed:" << responseStr;
            emit emailSentSuccessfully(false);
            cleanupSMTPConnection();
        }
        break;
        
    case 9: // Message sent response
        if (responseCode == 250) {
            qDebug() << "✅ Email sent successfully to:" << m_currentEmailAddress;
            sendSMTPCommand("QUIT");
            m_smtpState = 10;
        } else {
            qDebug() << "❌ Email sending failed:" << responseStr;
            emit emailSentSuccessfully(false);
            cleanupSMTPConnection();
        }
        break;
        
    case 10: // QUIT response
        qDebug() << "📤 SMTP session ended";
        qDebug() << "📬 Email queued for delivery to:" << m_currentEmailAddress;
        qDebug() << "🔍 Check your email inbox and spam folder";
        emit emailSentSuccessfully(true);
        cleanupSMTPConnection();
        break;
    }
}

void EmailPanel::onSMTPError(QAbstractSocket::SocketError error)
{
    QString errorString = m_smtpSocket ? m_smtpSocket->errorString() : "Socket is null";
    qDebug() << "❌ SMTP Error:" << error << errorString;
    
    QString errorMsg;
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        errorMsg = "Connection refused. Check SMTP server and port.";
        break;
    case QAbstractSocket::HostNotFoundError:
        errorMsg = "SMTP server not found. Check server address.";
        break;
    case QAbstractSocket::SocketTimeoutError:
        errorMsg = "Connection timeout. Check internet connection.";
        break;
    default:
        errorMsg = QString("Network error: %1").arg(m_smtpSocket->errorString());
    }
    
    QMessageBox::warning(this, "SMTP Error", 
        QString("Failed to connect to email server:\n\n%1\n\n"
               "Server: smtp-relay.brevo.com:587\n"
               "Please check your internet connection and try again.")
        .arg(errorMsg));
    
    emit emailSentSuccessfully(false);
    cleanupSMTPConnection();
}

void EmailPanel::cleanupSMTPConnection()
{
    if (m_smtpSocket) {
        // Disconnect all signals to prevent crashes
        m_smtpSocket->disconnect();
        
        // Close connection gracefully
        if (m_smtpSocket->state() == QAbstractSocket::ConnectedState) {
            m_smtpSocket->disconnectFromHost();
            if (m_smtpSocket->state() != QAbstractSocket::UnconnectedState) {
                m_smtpSocket->waitForDisconnected(1000); // Wait up to 1 second
            }
        }
        
        // Schedule for deletion
        m_smtpSocket->deleteLater();
        m_smtpSocket = nullptr;
    }
    m_smtpState = 0;
}

void EmailPanel::sendSMTPCommand(const QString& command)
{
    if (!m_smtpSocket) {
        qDebug() << "❌ Cannot send SMTP command: socket is null";
        return;
    }
    
    qDebug() << "SMTP CMD:" << command;
    m_smtpSocket->write((command + "\r\n").toUtf8());
}

QString EmailPanel::encodeBase64(const QString& text)
{
    return QString::fromUtf8(text.toUtf8().toBase64());
}

QString EmailPanel::createEmailMessage(const QString& to, const QString& subject, const QString& body)
{
    QString message = QString(
        "From: Test Message <9bd853001@smtp-brevo.com>\r\n"
        "To: %1\r\n"
        "Subject: %2\r\n"
        "Date: %4\r\n"
        "Message-ID: <%5@smtp-brevo.com>\r\n"
        "Reply-To: 9bd853001@smtp-brevo.com\r\n"
        "Return-Path: 9bd853001@smtp-brevo.com\r\n"
        "X-Mailer: Summer Club Management System\r\n"
        "X-Priority: 3\r\n"
        "MIME-Version: 1.0\r\n"
        "Content-Type: text/plain; charset=UTF-8\r\n"
        "Content-Transfer-Encoding: 8bit\r\n"
        "\r\n"
        "Summer Club Management System\r\n"
        "=============================\r\n\r\n"
        "%3\r\n\r\n"
        "---\r\n"
        "This email was sent from Summer Club Management System.\r\n"
        "If you received this email by mistake, please ignore it.\r\n"
    );
    
    QString formattedBody = body;
    formattedBody.replace("\n", "<br>\n");
    
    // Add proper date and message ID
    QString currentDate = QDateTime::currentDateTime().toString("ddd, dd MMM yyyy hh:mm:ss +0000");
    QString messageId = QString::number(QDateTime::currentMSecsSinceEpoch());
    
    return message.arg(to, subject, formattedBody, currentDate, messageId);
}

// Legacy method - now unused
bool EmailPanel::tryEmailSMTP(const QString& apiUrl, const QString& emailAddress, const QString& message)
{
    QUrl url(apiUrl);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    
    // Enhanced headers to bypass Cloudflare protection
    request.setHeader(QNetworkRequest::UserAgentHeader, 
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36");
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8");
    request.setRawHeader("Accept-Language", "en-US,en;q=0.9");
    request.setRawHeader("Accept-Encoding", "identity");  // Disable compression to avoid binary data
    request.setRawHeader("Cache-Control", "no-cache");
    request.setRawHeader("Pragma", "no-cache");
    request.setRawHeader("Upgrade-Insecure-Requests", "1");
    request.setRawHeader("Sec-Fetch-Dest", "document");
    request.setRawHeader("Sec-Fetch-Mode", "navigate");
    request.setRawHeader("Sec-Fetch-Site", "none");
    request.setRawHeader("Sec-Ch-Ua", "\"Not_A Brand\";v=\"8\", \"Chromium\";v=\"121\", \"Google Chrome\";v=\"121\"");
    request.setRawHeader("Sec-Ch-Ua-Mobile", "?0");
    request.setRawHeader("Sec-Ch-Ua-Platform", "\"Windows\"");
    request.setRawHeader("Connection", "keep-alive");
    
    // Don't set Referer and Origin for initial bypass attempt
    
    // Prepare POST data
    QUrlQuery postData;
    postData.addQueryItem("email", emailAddress);
    postData.addQueryItem("message", message);  
    postData.addQueryItem("key", "textbelt"); // Free key (1 Email per day per IP)
    
    qDebug() << "Trying Email API:" << apiUrl;
    qDebug() << "Email:" << emailAddress;
    qDebug() << "Message:" << message;
    
    // Send POST request
    QNetworkReply *reply = m_networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    
    // Wait for response with timeout
    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    timeoutTimer.setInterval(10000); // 10 second timeout
    
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
    
    timeoutTimer.start();
    loop.exec();
    
    bool success = false;
    QString errorMessage;
    
    if (timeoutTimer.isActive()) {
        timeoutTimer.stop();
        
        // Check HTTP status code
        int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP Status Code:" << httpStatus;
        
        // textbelt returns 201 (Created) for successful Email, which Qt considers "no error"
        // But sometimes Qt reports it as an error, so we check both conditions
        if (reply->error() == QNetworkReply::NoError || httpStatus == 200 || httpStatus == 201) {
            QByteArray responseData = reply->readAll();
            qDebug() << "API Response:" << responseData;
            
            // Check for Cloudflare protection (binary/compressed data or HTML challenge)
            QString responseText = QString::fromUtf8(responseData);
            if (responseData.size() > 0 && responseText.isEmpty()) {
                qDebug() << "Binary/compressed response detected - likely Cloudflare protection";
                return false; // Try alternative service
            }
            
            if (responseText.contains("Just a moment...") || 
                responseText.contains("challenge") ||
                responseText.contains("cloudflare") ||
                responseText.contains("checking your browser")) {
                qDebug() << "Cloudflare challenge page detected";
                return false; // Try alternative service
            }
            
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (jsonDoc.isNull()) {
                errorMessage = "Invalid JSON response from API";
                qDebug() << "JSON Parse Error - Raw response:" << responseData;
            } else {
                QJsonObject jsonObj = jsonDoc.object();
                success = jsonObj["success"].toBool();
                
                if (!success) {
                    errorMessage = jsonObj["error"].toString();
                    qDebug() << "Email API Error:" << errorMessage;
                    
                    // Show detailed error to user for the first failure
                    static bool firstError = true;
                    if (firstError) {
                        firstError = false;
                        QMessageBox::warning(this, "Email API Error", 
                            QString("textbelt API Error: %1\n\n"
                                   "Common issues:\n"
                                   "• Free tier allows only 1 Email per day per IP\n"
                                   "• Email address must be in valid format (user@domain.com)\n"
                                   "• Some email providers may not be supported\n\n"
                                   "Email: %2\nMessage: %3")
                            .arg(errorMessage, emailAddress, message));
                    }
                } else {
                    qDebug() << "Email sent successfully to" << emailAddress;
                }
            }
        } else {
            // Get response data even on "error" (might be HTTP 201 or Cloudflare protection)
            QByteArray responseData = reply->readAll();
            errorMessage = QString("Network error: %1 (%2) - HTTP Status: %3").arg(reply->errorString()).arg(reply->error()).arg(httpStatus);
            qDebug() << errorMessage;
            qDebug() << "Response data despite error:" << responseData;
            
            // Check for Cloudflare protection on error responses
            if (httpStatus == 403) {
                QString responseText = QString::fromUtf8(responseData);
                if (responseData.size() > 0 && (responseText.isEmpty() || responseText.contains("cloudflare"))) {
                    qDebug() << "HTTP 403 with Cloudflare protection detected - trying alternative service";
                    return false; // Don't show error, just try next service
                }
            }
            
            // Check if we got a response despite the "error"
            if (!responseData.isEmpty() && httpStatus == 201) {
                qDebug() << "HTTP 201 received - checking JSON response";
                QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
                if (!jsonDoc.isNull()) {
                    QJsonObject jsonObj = jsonDoc.object();
                    success = jsonObj["success"].toBool();
                    
                    if (success) {
                        qDebug() << "Email actually sent successfully despite Qt error!";
                        return true; // Override the error, Email was successful
                    } else {
                        errorMessage = jsonObj["error"].toString();
                        qDebug() << "Email API Error (HTTP 201):" << errorMessage;
                    }
                }
            }
            
            // Show network error details only for real network issues
            if (httpStatus != 201) {
                QMessageBox::critical(this, "Network Error", 
                    QString("Failed to connect to Email API:\n%1\n\n"
                           "Please check:\n"
                           "• Internet connection\n"
                           "• Firewall settings\n"
                           "• Proxy configuration")
                    .arg(errorMessage));
            }
        }
    } else {
        // Timeout occurred
        reply->abort();
        errorMessage = "Request timeout (10 seconds)";
        qDebug() << errorMessage;
        
        QMessageBox::warning(this, "Email Timeout", 
            "Email request timed out. The API may be temporarily unavailable.");
    }
    
    reply->deleteLater();
    return success;
}

void EmailPanel::checkForDatabaseUpdates()
{
    try {
        // Check current member count using default database connection
        QSqlQuery countQuery;
        countQuery.prepare("SELECT COUNT(*) FROM SUMMERCLUB.MEMBERS WHERE EMAIL IS NOT NULL AND TRIM(EMAIL) != ''");
        
        if (countQuery.exec() && countQuery.next()) {
            int currentCount = countQuery.value(0).toInt();
            
            if (currentCount != m_lastMemberCount) {
                qDebug() << "📊 Database change detected - Members:" << m_lastMemberCount << "→" << currentCount;
                
                // Refresh the member list
                loadMembers();
                m_lastMemberCount = currentCount;
                
                // Show notification to user
                if (currentCount > m_lastMemberCount) {
                    qDebug() << "✅ New members detected - refreshing recipient list";
                } else if (currentCount < m_lastMemberCount) {
                    qDebug() << "⚠️ Members removed - refreshing recipient list";
                }
            }
        }
        
    } catch (const std::exception& e) {
        qDebug() << "❌ Error checking database updates:" << e.what();
    }
}

void EmailPanel::updateEmailStatistics()
{
    try {
        // Create email_logs table if it doesn't exist
        QSqlQuery createTableQuery;
        createTableQuery.exec(
            "CREATE TABLE IF NOT EXISTS SUMMERCLUB.EMAIL_LOGS ("
            "ID NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, "
            "RECIPIENT_EMAIL VARCHAR2(255), "
            "SUBJECT VARCHAR2(500), "
            "SENT_DATE DATE DEFAULT SYSDATE, "
            "SUCCESS NUMBER(1) DEFAULT 1"
            ")"
        );
        
        QDateTime now = QDateTime::currentDateTime();
        QDateTime startOfDay = QDateTime(now.date(), QTime(0, 0, 0));
        QDateTime startOfWeek = startOfDay.addDays(-now.date().dayOfWeek() + 1);
        QDateTime startOfMonth = QDateTime(QDate(now.date().year(), now.date().month(), 1), QTime(0, 0, 0));
        
        // Today's count
        QSqlQuery todayQuery;
        todayQuery.prepare("SELECT COUNT(*) FROM SUMMERCLUB.EMAIL_LOGS WHERE SENT_DATE >= ? AND SUCCESS = 1");
        todayQuery.addBindValue(startOfDay);
        
        int todayCount = 0;
        if (todayQuery.exec() && todayQuery.next()) {
            todayCount = todayQuery.value(0).toInt();
        }
        
        // This week's count
        QSqlQuery weekQuery;
        weekQuery.prepare("SELECT COUNT(*) FROM SUMMERCLUB.EMAIL_LOGS WHERE SENT_DATE >= ? AND SUCCESS = 1");
        weekQuery.addBindValue(startOfWeek);
        
        int weekCount = 0;
        if (weekQuery.exec() && weekQuery.next()) {
            weekCount = weekQuery.value(0).toInt();
        }
        
        // This month's count
        QSqlQuery monthQuery;
        monthQuery.prepare("SELECT COUNT(*) FROM SUMMERCLUB.EMAIL_LOGS WHERE SENT_DATE >= ? AND SUCCESS = 1");
        monthQuery.addBindValue(startOfMonth);
        
        int monthCount = 0;
        if (monthQuery.exec() && monthQuery.next()) {
            monthCount = monthQuery.value(0).toInt();
        }
        
        // Update the statistics labels
        m_todayCountLabel->setText(QString("Today: %1 sent").arg(todayCount));
        m_weekCountLabel->setText(QString("This Week: %1 sent").arg(weekCount));
        m_monthCountLabel->setText(QString("This Month: %1 sent").arg(monthCount));
        
        qDebug() << "📊 Statistics updated - Today:" << todayCount << "Week:" << weekCount << "Month:" << monthCount;
        
    } catch (const std::exception& e) {
        qDebug() << "❌ Error updating email statistics:" << e.what();
    }
}

void EmailPanel::logEmailSent(const QString& recipientEmail, const QString& subject, bool success)
{
    try {
        QSqlQuery logQuery;
        logQuery.prepare(
            "INSERT INTO SUMMERCLUB.EMAIL_LOGS (RECIPIENT_EMAIL, SUBJECT, SUCCESS) "
            "VALUES (?, ?, ?)"
        );
        logQuery.addBindValue(recipientEmail);
        logQuery.addBindValue(subject);
        logQuery.addBindValue(success ? 1 : 0);
        
        if (logQuery.exec()) {
            qDebug() << "✅ Email logged successfully:" << recipientEmail << (success ? "SUCCESS" : "FAILED");
        } else {
            qDebug() << "❌ Failed to log email:" << logQuery.lastError().text();
        }
        
    } catch (const std::exception& e) {
        qDebug() << "❌ Error logging email:" << e.what();
    }
}


