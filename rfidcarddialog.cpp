#include "rfidcarddialog.h"

RFIDCardDialog::RFIDCardDialog(QWidget *parent)
    : QDialog(parent),
      m_isEditMode(false),
      m_rfidCard(new RFIDCard(this)),
      m_arduino(nullptr),
      m_isScanning(false)
{
    setWindowTitle("Add New RFID Card");
    setModal(true);
    resize(500, 400);
    
    setupUI();
    setupStyles();
    connectSignals();
    loadMembersList();
}

RFIDCardDialog::RFIDCardDialog(const QString &cardUid, QWidget *parent)
    : QDialog(parent),
      m_isEditMode(true),
      m_originalCardUid(cardUid),
      m_rfidCard(new RFIDCard(this)),
      m_arduino(nullptr),
      m_isScanning(false)
{
    setWindowTitle("Edit RFID Card");
    setModal(true);
    resize(500, 400);
    
    setupUI();
    setupStyles();
    connectSignals();
    setupArduinoConnection();
    loadMembersList();
    loadCardData();
}

RFIDCardDialog::RFIDCardDialog(Arduino *arduino, QWidget *parent)
    : QDialog(parent),
      m_isEditMode(false),
      m_rfidCard(new RFIDCard(this)),
      m_arduino(nullptr),
      m_isScanning(false)
{
    setWindowTitle("Add New RFID Card");
    setModal(true);
    resize(500, 400);
    
    setupUI();
    setupStyles();
    connectSignals();
    setupArduinoConnection(arduino);
    loadMembersList();
}

RFIDCardDialog::RFIDCardDialog(const QString &cardUid, Arduino *arduino, QWidget *parent)
    : QDialog(parent),
      m_isEditMode(true),
      m_originalCardUid(cardUid),
      m_rfidCard(new RFIDCard(this)),
      m_arduino(nullptr),
      m_isScanning(false)
{
    setWindowTitle("Edit RFID Card");
    setModal(true);
    resize(500, 400);
    
    setupUI();
    setupStyles();
    connectSignals();
    setupArduinoConnection(arduino);
    loadMembersList();
    loadCardData();
}

RFIDCardDialog::~RFIDCardDialog()
{
    // RFIDCard will be deleted automatically as it's a child object
}

void RFIDCardDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Card Information Group
    m_cardInfoGroup = new QGroupBox("💳 Card Information", this);
    QFormLayout *cardFormLayout = new QFormLayout(m_cardInfoGroup);
    
    // Card UID
    QHBoxLayout *cardUidLayout = new QHBoxLayout();
    m_cardUidLineEdit = new QLineEdit();
    m_cardUidLineEdit->setPlaceholderText("Enter card UID (e.g., A3 89 36 A6)");
    m_scanCardButton = new QPushButton("📱 Scan Card");
    m_scanCardButton->setToolTip("Scan RFID card to get UID automatically");
    cardUidLayout->addWidget(m_cardUidLineEdit);
    cardUidLayout->addWidget(m_scanCardButton);
    cardFormLayout->addRow("Card UID:", cardUidLayout);
    
    // Member Selection
    m_memberComboBox = new QComboBox();
    m_memberComboBox->setEditable(false);
    cardFormLayout->addRow("Member:", m_memberComboBox);
    
    // Card Status
    m_statusComboBox = new QComboBox();
    m_statusComboBox->addItems({"Active", "Disabled", "Lost", "Expired"});
    cardFormLayout->addRow("Status:", m_statusComboBox);
    
    // Notes
    m_notesTextEdit = new QTextEdit();
    m_notesTextEdit->setMaximumHeight(80);
    m_notesTextEdit->setPlaceholderText("Optional notes about this card...");
    cardFormLayout->addRow("Notes:", m_notesTextEdit);
    
    mainLayout->addWidget(m_cardInfoGroup);
    
    // Member Information Group (Read-only display)
    m_memberInfoGroup = new QGroupBox("👤 Member Details", this);
    QFormLayout *memberFormLayout = new QFormLayout(m_memberInfoGroup);
    
    m_memberCinLabel = new QLabel("-");
    m_memberNameLabel = new QLabel("-");
    m_memberPhoneLabel = new QLabel("-");
    m_memberEmailLabel = new QLabel("-");
    
    memberFormLayout->addRow("CIN:", m_memberCinLabel);
    memberFormLayout->addRow("Name:", m_memberNameLabel);
    memberFormLayout->addRow("Phone:", m_memberPhoneLabel);
    memberFormLayout->addRow("Email:", m_memberEmailLabel);
    
    mainLayout->addWidget(m_memberInfoGroup);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    m_saveButton = new QPushButton(m_isEditMode ? "💾 Update Card" : "➕ Add Card");
    m_cancelButton = new QPushButton("❌ Cancel");
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);
}

void RFIDCardDialog::setupStyles()
{
    setStyleSheet(
        "QDialog {"
        "    background-color: #f8f9fa;"
        "}"
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #16a5b3;"
        "    border-radius: 8px;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "    background-color: white;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px 0 5px;"
        "    color: #16a5b3;"
        "}"
        "QLineEdit, QComboBox {"
        "    border: 1px solid #ddd;"
        "    border-radius: 4px;"
        "    padding: 8px;"
        "    background-color: white;"
        "}"
        "QLineEdit:focus, QComboBox:focus {"
        "    border-color: #16a5b3;"
        "    box-shadow: 0 0 0 2px rgba(22, 165, 179, 0.2);"
        "}"
        "QTextEdit {"
        "    border: 1px solid #ddd;"
        "    border-radius: 4px;"
        "    padding: 8px;"
        "    background-color: white;"
        "}"
        "QTextEdit:focus {"
        "    border-color: #16a5b3;"
        "}"
        "QPushButton {"
        "    padding: 8px 16px;"
        "    border: none;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "#scanCardButton {"
        "    background-color: #FF9800;"
        "    color: white;"
        "}"
        "#scanCardButton:hover {"
        "    background-color: #F57C00;"
        "}"
        "QPushButton[text*='Add'], QPushButton[text*='Update'] {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "}"
        "QPushButton[text*='Add']:hover, QPushButton[text*='Update']:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton[text*='Cancel'] {"
        "    background-color: #f44336;"
        "    color: white;"
        "}"
        "QPushButton[text*='Cancel']:hover {"
        "    background-color: #da190b;"
        "}"
        "QLabel {"
        "    color: #333;"
        "    padding: 4px;"
        "}"
    );
    
    m_scanCardButton->setObjectName("scanCardButton");
}

void RFIDCardDialog::connectSignals()
{
    connect(m_saveButton, &QPushButton::clicked, this, &RFIDCardDialog::onSaveClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &RFIDCardDialog::onCancelClicked);
    connect(m_memberComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RFIDCardDialog::onMemberChanged);
    connect(m_scanCardButton, &QPushButton::clicked, this, &RFIDCardDialog::onScanCardClicked);
    
    // Enable/disable save button based on form validity
    connect(m_cardUidLineEdit, &QLineEdit::textChanged, this, &RFIDCardDialog::validateForm);
    connect(m_memberComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RFIDCardDialog::validateForm);
}

void RFIDCardDialog::setupArduinoConnection(Arduino *sharedArduino)
{
    if (sharedArduino) {
        // Use shared Arduino instance
        m_arduino = sharedArduino;
        qDebug() << "🔗 RFID Card Dialog: Using shared Arduino connection";
    } else {
        // Create new Arduino connection (fallback for old code)
        m_arduino = new Arduino(this);
        qDebug() << "🔌 RFID Card Dialog: Created new Arduino connection";
    }
    
    // Connect Arduino signals
    connect(m_arduino, &Arduino::rfidCardDetected, this, &RFIDCardDialog::onRFIDCardDetected);
    
    qDebug() << "🔌 RFID Card Dialog: Arduino connection setup complete";
}

void RFIDCardDialog::loadMembersList()
{
    m_memberComboBox->clear();
    m_memberComboBox->addItem("Select a member...", "");
    
    QSqlQuery query;
    query.prepare("SELECT CIN, FIRST_NAME || ' ' || LAST_NAME as FULL_NAME "
                  "FROM SUMMERCLUB.MEMBERS "
                  "ORDER BY FULL_NAME");
    
    if (query.exec()) {
        while (query.next()) {
            QString cin = query.value("CIN").toString();
            QString fullName = query.value("FULL_NAME").toString();
            m_memberComboBox->addItem(QString("%1 (%2)").arg(fullName, cin), cin);
        }
        qDebug() << "📋 Loaded" << m_memberComboBox->count() - 1 << "members into combo box";
    } else {
        qDebug() << "❌ Failed to load members:" << query.lastError().text();
        QMessageBox::warning(this, "Database Error", "Failed to load members list.");
    }
}

void RFIDCardDialog::loadCardData()
{
    if (!m_isEditMode || m_originalCardUid.isEmpty()) return;
    
    if (m_rfidCard->load(m_originalCardUid)) {
        // Populate form with existing data
        m_cardUidLineEdit->setText(m_rfidCard->getRfidUid());
        m_cardUidLineEdit->setReadOnly(true); // Don't allow UID changes in edit mode
        
        // Find and select the member
        QString memberCin = m_rfidCard->getMemberCin();
        for (int i = 0; i < m_memberComboBox->count(); i++) {
            if (m_memberComboBox->itemData(i).toString() == memberCin) {
                m_memberComboBox->setCurrentIndex(i);
                break;
            }
        }
        
        // Set status
        QString status = RFIDCard::statusToString(m_rfidCard->getCardStatus());
        int statusIndex = m_statusComboBox->findText(status);
        if (statusIndex >= 0) {
            m_statusComboBox->setCurrentIndex(statusIndex);
        }
        
        // Set notes
        m_notesTextEdit->setPlainText(m_rfidCard->getNotes());
        
        qDebug() << "📝 Loaded card data for editing:" << m_originalCardUid;
    } else {
        QMessageBox::critical(this, "Error", "Failed to load card data for editing.");
        reject();
    }
}

void RFIDCardDialog::onMemberChanged()
{
    QString selectedCin = m_memberComboBox->currentData().toString();
    
    if (selectedCin.isEmpty()) {
        m_memberCinLabel->setText("-");
        m_memberNameLabel->setText("-");
        m_memberPhoneLabel->setText("-");
        m_memberEmailLabel->setText("-");
        return;
    }
    
    // Load member details
    QSqlQuery query;
    query.prepare("SELECT FIRST_NAME, LAST_NAME, PHONE, EMAIL FROM SUMMERCLUB.MEMBERS WHERE CIN = :cin");
    query.bindValue(":cin", selectedCin);
    
    if (query.exec() && query.next()) {
        m_memberCinLabel->setText(selectedCin);
        m_memberNameLabel->setText(query.value("FIRST_NAME").toString() + " " + query.value("LAST_NAME").toString());
        m_memberPhoneLabel->setText(query.value("PHONE").toString());
        m_memberEmailLabel->setText(query.value("EMAIL").toString());
    } else {
        m_memberCinLabel->setText(selectedCin);
        m_memberNameLabel->setText("Error loading member details");
        m_memberPhoneLabel->setText("-");
        m_memberEmailLabel->setText("-");
    }
}

void RFIDCardDialog::onScanCardClicked()
{
    if (m_isScanning) {
        // Stop scanning
        m_isScanning = false;
        m_scanCardButton->setText("📱 Scan Card");
        m_scanCardButton->setStyleSheet("");
        // Don't close shared Arduino connection
        if (m_arduino && m_arduino->parent() == this) {
            m_arduino->close_arduino();
        }
        return;
    }
    
    // Start scanning
    qDebug() << "🔍 Starting RFID card scan...";
    
    // Check Arduino connection (don't try to connect if using shared instance)
    if (!m_arduino->isConnected()) {
        // Only try to connect if we created our own Arduino instance
        if (m_arduino->parent() == this) {
            if (m_arduino->connect_arduino() != 0) {
                QMessageBox::critical(this, "Connection Error", 
                                    "Failed to connect to Arduino.\n\n"
                                    "Please check that the Arduino is connected and try again.");
                return;
            }
        } else {
            QMessageBox::warning(this, "Arduino Not Connected", 
                               "The Arduino is not connected to the main system.\n\n"
                               "Please ensure the main RFID system is running.");
            return;
        }
    }
    
    m_isScanning = true;
    m_scanCardButton->setText("🛑 Stop Scanning");
    m_scanCardButton->setStyleSheet("background-color: #f44336; color: white;");
    
    QMessageBox::information(this, "Scan Card", 
                           "🔍 Scanning for RFID cards...\n\n"
                           "Present your RFID card to the reader now.\n"
                           "The card UID will be automatically filled in when detected.\n\n"
                           "Click 'Stop Scanning' to cancel.");
    
    // Set a timeout for scanning (30 seconds)
    QTimer::singleShot(30000, this, &RFIDCardDialog::onScanTimeout);
}

void RFIDCardDialog::onRFIDCardDetected(const QString &rfidUid)
{
    if (!m_isScanning) return;
    
    qDebug() << "🎯 Card detected during scan:" << rfidUid;
    
    // Stop scanning
    m_isScanning = false;
    m_scanCardButton->setText("📱 Scan Card");
    m_scanCardButton->setStyleSheet("");
    
    // Fill in the card UID
    m_cardUidLineEdit->setText(rfidUid);
    
    // Show success message
    QMessageBox::information(this, "Card Detected", 
                           QString("✅ RFID card detected successfully!\n\n"
                                  "Card UID: %1\n\n"
                                  "Please select a member to associate with this card.").arg(rfidUid));
    
    // Focus on member selection
    m_memberComboBox->setFocus();
}

void RFIDCardDialog::onScanTimeout()
{
    if (!m_isScanning) return;
    
    m_isScanning = false;
    m_scanCardButton->setText("📱 Scan Card");
    m_scanCardButton->setStyleSheet("");
    
    QMessageBox::information(this, "Scan Timeout", 
                           "⏱️ Card scanning has timed out.\n\n"
                           "No card was detected within 30 seconds.\n"
                           "Please try again.");
}

void RFIDCardDialog::validateForm()
{
    bool isValid = !m_cardUidLineEdit->text().trimmed().isEmpty() &&
                   !m_memberComboBox->currentData().toString().isEmpty();
    
    m_saveButton->setEnabled(isValid);
}

void RFIDCardDialog::onSaveClicked()
{
    QString cardUid = m_cardUidLineEdit->text().trimmed();
    QString memberCin = m_memberComboBox->currentData().toString();
    QString status = m_statusComboBox->currentText();
    QString notes = m_notesTextEdit->toPlainText().trimmed();
    
    qDebug() << "💾 Save clicked - Data:";
    qDebug() << "   Card UID:" << cardUid;
    qDebug() << "   Member CIN:" << memberCin;
    qDebug() << "   Status:" << status;
    qDebug() << "   Notes:" << notes;
    qDebug() << "   Edit Mode:" << m_isEditMode;
    
    // Validate inputs
    if (cardUid.isEmpty()) {
        qDebug() << "❌ Validation failed: Card UID is empty";
        QMessageBox::warning(this, "Validation Error", "Please enter a card UID.");
        return;
    }
    
    if (memberCin.isEmpty()) {
        qDebug() << "❌ Validation failed: Member CIN is empty";
        QMessageBox::warning(this, "Validation Error", "Please select a member.");
        return;
    }
    
    // Check if card UID already exists (for new cards or if UID changed)
    if (!m_isEditMode || cardUid != m_originalCardUid) {
        qDebug() << "🔍 Checking if card UID exists:" << cardUid;
        if (RFIDCard::isUidExists(cardUid)) {
            qDebug() << "❌ Card UID already exists:" << cardUid;
            QMessageBox::warning(this, "Card Already Exists", 
                               QString("A card with UID '%1' already exists.").arg(cardUid));
            return;
        }
        qDebug() << "✅ Card UID is unique";
    }
    
    // Save the card
    try {
        if (m_isEditMode) {
            qDebug() << "📝 Updating existing card";
            // Update existing card
            m_rfidCard->setRfidUid(cardUid);
            m_rfidCard->setMemberCin(memberCin);
            m_rfidCard->setCardStatus(RFIDCard::stringToStatus(status));
            m_rfidCard->setNotes(notes);
            
            qDebug() << "💾 Attempting to save updated card...";
            if (m_rfidCard->save()) {
                qDebug() << "✅ Card updated successfully";
                QMessageBox::information(this, "Success", "RFID card updated successfully!");
                accept();
            } else {
                qDebug() << "❌ Failed to update card";
                QMessageBox::critical(this, "Error", "Failed to update RFID card.");
            }
        } else {
            qDebug() << "➕ Creating new card";
            // Create new card
            RFIDCard newCard(cardUid, memberCin, RFIDCard::stringToStatus(status), notes);
            
            qDebug() << "💾 Attempting to save new card...";
            if (newCard.save()) {
                qDebug() << "✅ New card saved successfully";
                QMessageBox::information(this, "Success", "RFID card added successfully!");
                accept();
            } else {
                qDebug() << "❌ Failed to save new card";
                QMessageBox::critical(this, "Error", "Failed to add RFID card.");
            }
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("An error occurred: %1").arg(e.what()));
    }
}

void RFIDCardDialog::onCancelClicked()
{
    reject();
}

QString RFIDCardDialog::getCardUid() const
{
    return m_cardUidLineEdit->text().trimmed();
}