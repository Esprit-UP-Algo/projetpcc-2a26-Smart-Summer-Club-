#include "totpsetupdialog.h"
#include "totpinputdialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include <QtMath>

TOTPSetupDialog::TOTPSetupDialog(const QString &userCin, const QString &userName, QWidget *parent)
    : QDialog(parent)
    , m_userCin(userCin)
    , m_userName(userName)
    , m_totpEnabled(false)
    , m_isVerified(false)
{
    setWindowTitle("Setup Two-Factor Authentication - Summer Club");
    setModal(true);
    setMinimumSize(600, 800);
    resize(650, 900);
    
    setupUI();
    applyStyles();
    
    // Generate initial secret and QR code
    onGenerateNewSecret();
    
    // Setup countdown timer
    m_countdownTimer = new QTimer(this);
    connect(m_countdownTimer, &QTimer::timeout, this, &TOTPSetupDialog::updateCountdown);
    m_countdownTimer->start(1000); // Update every second
}

TOTPSetupDialog::~TOTPSetupDialog()
{
}

void TOTPSetupDialog::setupUI()
{
    // Main scroll area
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    
    m_mainWidget = new QWidget();
    m_mainLayout = new QVBoxLayout(m_mainWidget);
    m_mainLayout->setSpacing(20);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Header
    m_titleLabel = new QLabel("🔐 Setup Two-Factor Authentication");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");
    
    m_instructionLabel = new QLabel(
        "Follow these steps to secure your Summer Club account with 2FA:\n"
        "1. Scan the QR code with your authenticator app\n"
        "2. Enter the 6-digit code to verify\n"
        "3. Save your backup codes safely\n"
        "4. Complete the setup"
    );
    m_instructionLabel->setAlignment(Qt::AlignCenter);
    m_instructionLabel->setWordWrap(true);
    m_instructionLabel->setStyleSheet("font-size: 14px; color: #6c757d; line-height: 150%;");
    
    m_mainLayout->addWidget(m_titleLabel);
    m_mainLayout->addWidget(m_instructionLabel);
    m_mainLayout->addSpacing(10);
    
    // Step 1: QR Code Section
    m_qrGroup = new QGroupBox("📱 Step 1: Scan QR Code");
    QVBoxLayout *qrLayout = new QVBoxLayout(m_qrGroup);
    
    QLabel *qrInstruction = new QLabel(
        "📱 <b>Manual Setup Instructions:</b><br><br>"
        "1. Open your authenticator app (Google Authenticator, Authy, etc.)<br>"
        "2. Choose 'Add account' or 'Set up account'<br>"
        "3. Select 'Enter a setup key' or 'Manual entry'<br>"
        "4. Enter the following details:<br>"
        "   • <b>Account name:</b> Summer Club<br>"
        "   • <b>Your name:</b> " + m_userName + "<br>"
        "   • <b>Secret key:</b> (see below)<br>"
        "   • <b>Type:</b> Time-based<br>"
        "5. Save the account in your app"
    );
    qrInstruction->setWordWrap(true);
    qrInstruction->setStyleSheet("color: #495057; margin-bottom: 15px; background: #e3f2fd; padding: 15px; border-radius: 8px; border-left: 4px solid #2196f3;");
    
    m_qrCodeLabel = new QLabel();
    m_qrCodeLabel->setAlignment(Qt::AlignCenter);
    m_qrCodeLabel->setMinimumSize(250, 250);
    m_qrCodeLabel->setStyleSheet("border: 2px solid #e9ecef; border-radius: 8px; background: white; padding: 10px;");
    
    QLabel *manualLabel = new QLabel("🔑 <b>Secret Key (copy this into your authenticator app):</b>");
    manualLabel->setStyleSheet("color: #e74c3c; font-size: 14px; margin: 20px 0 5px 0; font-weight: bold;");
    
    QHBoxLayout *secretLayout = new QHBoxLayout();
    m_secretKeyLabel = new QLabel();
    m_secretKeyLabel->setWordWrap(true);
    m_secretKeyLabel->setStyleSheet(
        "font-family: 'Courier New', monospace; "
        "background: #fff3cd; "
        "padding: 15px; "
        "border: 2px solid #ffeaa7; "
        "border-radius: 6px; "
        "font-size: 16px; "
        "font-weight: bold; "
        "color: #d63031; "
        "letter-spacing: 2px;"
    );
    
    m_copySecretButton = new QPushButton("📋 Copy Secret Key");
    m_copySecretButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 12px 20px;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "   margin-left: 10px;"
        "}"
        "QPushButton:hover { background-color: #c0392b; }"
        "QPushButton:pressed { background-color: #a93226; }"
    );
    connect(m_copySecretButton, &QPushButton::clicked, this, &TOTPSetupDialog::onCopySecret);
    
    secretLayout->addWidget(m_secretKeyLabel, 1);
    secretLayout->addWidget(m_copySecretButton);
    
    m_regenerateButton = new QPushButton("🔄 Generate New Secret");
    connect(m_regenerateButton, &QPushButton::clicked, this, &TOTPSetupDialog::onGenerateNewSecret);
    
    qrLayout->addWidget(qrInstruction);
    qrLayout->addWidget(m_qrCodeLabel);
    qrLayout->addWidget(manualLabel);
    qrLayout->addLayout(secretLayout);
    qrLayout->addWidget(m_regenerateButton);
    
    // Step 2: Verification Section
    m_verifyGroup = new QGroupBox("✅ Step 2: Verify Setup");
    QVBoxLayout *verifyLayout = new QVBoxLayout(m_verifyGroup);
    
    QLabel *verifyInstruction = new QLabel("Enter the 6-digit code from your authenticator app:");
    verifyInstruction->setStyleSheet("color: #495057; margin-bottom: 10px;");
    
    QHBoxLayout *codeLayout = new QHBoxLayout();
    m_verificationCodeEdit = new QLineEdit();
    m_verificationCodeEdit->setMaxLength(6);
    m_verificationCodeEdit->setPlaceholderText("123456");
    m_verificationCodeEdit->setAlignment(Qt::AlignCenter);
    m_verificationCodeEdit->setStyleSheet(
        "font-size: 24px; font-weight: bold; padding: 12px; text-align: center; "
        "border: 2px solid #dee2e6; border-radius: 8px; letter-spacing: 5px;"
    );
    connect(m_verificationCodeEdit, &QLineEdit::textChanged, this, &TOTPSetupDialog::onCodeTextChanged);
    
    m_verifyButton = new QPushButton("Verify Code");
    m_verifyButton->setEnabled(false);
    m_verifyButton->setMinimumHeight(50);
    connect(m_verifyButton, &QPushButton::clicked, this, &TOTPSetupDialog::onVerifyCode);
    
    codeLayout->addWidget(m_verificationCodeEdit, 2);
    codeLayout->addWidget(m_verifyButton, 1);
    
    // Time progress bar
    QHBoxLayout *timeLayout = new QHBoxLayout();
    m_timeLabel = new QLabel("Code expires in:");
    m_timeLabel->setStyleSheet("color: #6c757d; font-size: 12px;");
    
    m_timeProgressBar = new QProgressBar();
    m_timeProgressBar->setMaximum(30);
    m_timeProgressBar->setTextVisible(true);
    m_timeProgressBar->setStyleSheet(
        "QProgressBar { border: 1px solid #dee2e6; border-radius: 4px; background: #f8f9fa; height: 8px; }"
        "QProgressBar::chunk { background: #16a5b3; border-radius: 3px; }"
    );
    
    timeLayout->addWidget(m_timeLabel);
    timeLayout->addWidget(m_timeProgressBar, 1);
    
    m_verificationStatusLabel = new QLabel();
    m_verificationStatusLabel->setAlignment(Qt::AlignCenter);
    m_verificationStatusLabel->hide();
    
    verifyLayout->addWidget(verifyInstruction);
    verifyLayout->addLayout(codeLayout);
    verifyLayout->addLayout(timeLayout);
    verifyLayout->addWidget(m_verificationStatusLabel);
    
    // Step 3: Backup Codes Section
    m_backupGroup = new QGroupBox("💾 Step 3: Save Backup Codes");
    QVBoxLayout *backupLayout = new QVBoxLayout(m_backupGroup);
    
    QLabel *backupInstruction = new QLabel(
        "⚠️ Important: Save these backup codes in a safe place. "
        "You can use them to access your account if you lose your phone."
    );
    backupInstruction->setWordWrap(true);
    backupInstruction->setStyleSheet("color: #856404; background: #fff3cd; padding: 10px; border-radius: 4px; border: 1px solid #ffeaa7;");
    
    m_backupCodesEdit = new QTextEdit();
    m_backupCodesEdit->setMaximumHeight(150);
    m_backupCodesEdit->setReadOnly(true);
    m_backupCodesEdit->setStyleSheet(
        "font-family: 'Courier New', monospace; background: #f8f9fa; "
        "border: 1px solid #dee2e6; border-radius: 4px; padding: 10px;"
    );
    
    m_copyBackupCodesButton = new QPushButton("📋 Copy Backup Codes");
    connect(m_copyBackupCodesButton, &QPushButton::clicked, this, &TOTPSetupDialog::onCopyBackupCodes);
    
    m_confirmBackupCheckBox = new QCheckBox("✅ I have saved my backup codes in a safe place");
    m_confirmBackupCheckBox->setStyleSheet("color: #495057; font-weight: 500;");
    
    backupLayout->addWidget(backupInstruction);
    backupLayout->addWidget(m_backupCodesEdit);
    backupLayout->addWidget(m_copyBackupCodesButton);
    backupLayout->addSpacing(10);
    backupLayout->addWidget(m_confirmBackupCheckBox);
    
    // Step 4: Finish Section
    m_finishFrame = new QFrame();
    m_finishFrame->setStyleSheet("background: #f8f9fa; border: 1px solid #dee2e6; border-radius: 8px; padding: 15px;");
    QHBoxLayout *finishLayout = new QHBoxLayout(m_finishFrame);
    
    QLabel *finishIcon = new QLabel("🎉");
    finishIcon->setStyleSheet("font-size: 32px;");
    
    QVBoxLayout *finishTextLayout = new QVBoxLayout();
    QLabel *finishTitle = new QLabel("Complete Setup");
    finishTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #2c3e50;");
    
    QLabel *finishText = new QLabel("Click 'Enable 2FA' to secure your account with two-factor authentication.");
    finishText->setStyleSheet("color: #6c757d; font-size: 14px;");
    finishText->setWordWrap(true);
    
    finishTextLayout->addWidget(finishTitle);
    finishTextLayout->addWidget(finishText);
    
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    m_finishButton = new QPushButton("🔐 Enable 2FA");
    m_finishButton->setEnabled(false);
    m_finishButton->setMinimumHeight(40);
    m_finishButton->setStyleSheet(getButtonStyle());
    connect(m_finishButton, &QPushButton::clicked, this, &TOTPSetupDialog::onFinishSetup);
    
    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setMinimumHeight(40);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    buttonLayout->addWidget(m_finishButton);
    buttonLayout->addWidget(m_cancelButton);
    
    finishLayout->addWidget(finishIcon);
    finishLayout->addLayout(finishTextLayout, 1);
    finishLayout->addLayout(buttonLayout);
    
    // Add all sections to main layout
    m_mainLayout->addWidget(m_qrGroup);
    m_mainLayout->addWidget(m_verifyGroup);
    m_mainLayout->addWidget(m_backupGroup);
    m_mainLayout->addWidget(m_finishFrame);
    m_mainLayout->addStretch();
    
    // Set scroll area
    m_scrollArea->setWidget(m_mainWidget);
    
    // Main dialog layout
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->setContentsMargins(0, 0, 0, 0);
    dialogLayout->addWidget(m_scrollArea);
    
    // Initial state
    m_verifyGroup->setEnabled(false);
    m_backupGroup->setEnabled(false);
}

void TOTPSetupDialog::applyStyles()
{
    // Apply group box styles
    QString groupStyle = getGroupBoxStyle();
    m_qrGroup->setStyleSheet(groupStyle);
    m_verifyGroup->setStyleSheet(groupStyle);
    m_backupGroup->setStyleSheet(groupStyle);
    
    // Apply button styles
    QString buttonStyle = getButtonStyle();
    m_regenerateButton->setStyleSheet(buttonStyle);
    m_copySecretButton->setStyleSheet(buttonStyle);
    m_verifyButton->setStyleSheet(buttonStyle);
    m_copyBackupCodesButton->setStyleSheet(buttonStyle);
    m_cancelButton->setStyleSheet("QPushButton { background: #6c757d; color: white; border: none; padding: 10px 20px; border-radius: 6px; font-weight: 600; } QPushButton:hover { background: #5a6268; }");
}

QString TOTPSetupDialog::getGroupBoxStyle() const
{
    return "QGroupBox { font-weight: bold; color: #2c3e50; padding-top: 15px; margin-top: 10px; border: 2px solid #e9ecef; border-radius: 8px; } "
           "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 10px 0 10px; }";
}

QString TOTPSetupDialog::getButtonStyle() const
{
    return "QPushButton { background: #16a5b3; color: white; border: none; padding: 10px 20px; border-radius: 6px; font-weight: 600; } "
           "QPushButton:hover { background: #139aa6; } "
           "QPushButton:pressed { background: #0f858f; } "
           "QPushButton:disabled { background: #dee2e6; color: #6c757d; }";
}

QString TOTPSetupDialog::getSuccessStyle() const
{
    return "color: #155724; background: #d4edda; padding: 8px; border-radius: 4px; border: 1px solid #c3e6cb; font-weight: 600;";
}

QString TOTPSetupDialog::getErrorStyle() const
{
    return "color: #721c24; background: #f8d7da; padding: 8px; border-radius: 4px; border: 1px solid #f5c6cb; font-weight: 600;";
}

void TOTPSetupDialog::onGenerateNewSecret()
{
    // Generate new secret
    QByteArray secret = TOTP::generateSecretKey();
    m_totp.setSecret(secret);
    
    // Update UI
    generateQRCode();
    generateBackupCodes();
    
    // Reset verification state
    m_isVerified = false;
    updateVerificationUI();
}

void TOTPSetupDialog::generateQRCode()
{
    // Generate OTP Auth URL
    QString otpUrl = m_totp.generateOTPAuthURL(
        QString("%1 (%2)").arg(m_userName).arg(m_userCin),
        "Summer Club"
    );
    
    qDebug() << "=== DEBUG: Generated OTP URL ===";
    qDebug() << otpUrl;
    
    // Generate QR code using online service (temporary solution)
    QString qrServiceUrl = QString("https://api.qrserver.com/v1/create-qr-code/?size=240x240&data=%1")
                           .arg(QString(QUrl::toPercentEncoding(otpUrl)));
    
    qDebug() << "QR Service URL:" << qrServiceUrl;
    
    // Create instructions image
    QPixmap instructions(240, 240);
    instructions.fill(QColor("#fff3cd"));
    
    QPainter painter(&instructions);
    painter.setPen(QColor("#d63031"));
    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.drawRect(0, 0, 239, 239);
    
    painter.drawText(QRect(10, 10, 220, 30), Qt::AlignCenter, 
                     "📱 Manual Setup Required");
    
    painter.setFont(QFont("Arial", 9));
    painter.setPen(QColor("#2c3e50"));
    painter.drawText(QRect(10, 50, 220, 90), Qt::AlignCenter | Qt::TextWordWrap,
                     "QR codes not yet implemented. Please use manual setup:");
    
    painter.setFont(QFont("Arial", 8, QFont::Bold));
    painter.setPen(QColor("#e74c3c"));
    painter.drawText(QRect(10, 140, 220, 50), Qt::AlignCenter | Qt::TextWordWrap,
                     "1. Open authenticator app\n2. Choose 'Manual entry'\n3. Copy secret key below");
    
    painter.setFont(QFont("Arial", 7));
    painter.setPen(QColor("#6c757d"));
    painter.drawText(QRect(10, 200, 220, 30), Qt::AlignCenter | Qt::TextWordWrap,
                     "Future versions will include\nfull QR code support");
    
    m_qrCodeLabel->setPixmap(instructions);
    
    // Update secret key display
    QString base32Secret = TOTP::encodeBase32(m_totp.getSecret());
    m_secretKeyLabel->setText(base32Secret);
    
    qDebug() << "=== DEBUG: Base32 Secret ===";
    qDebug() << base32Secret;
}

void TOTPSetupDialog::generateBackupCodes()
{
    m_backupCodes = TOTP::generateBackupCodes(10);
    
    QString codesText;
    for (int i = 0; i < m_backupCodes.size(); ++i) {
        codesText += QString("%1. %2\n").arg(i + 1, 2).arg(m_backupCodes[i]);
    }
    
    m_backupCodesEdit->setText(codesText);
}

void TOTPSetupDialog::onVerifyCode()
{
    // Show modern TOTP input dialog
    TOTPInputDialog *totpDialog = new TOTPInputDialog(this);
    totpDialog->setTitle("Verify Setup");
    totpDialog->setMessage("Enter the 6-digit code from your authenticator app to verify the setup");
    
    if (totpDialog->exec() == QDialog::Accepted) {
        QString userCode = totpDialog->getCode();
        
        if (m_totp.validateCode(userCode)) {
            m_isVerified = true;
            m_verificationStatusLabel->setText("✅ Code verified successfully!");
            m_verificationStatusLabel->setStyleSheet(getSuccessStyle());
            m_verificationStatusLabel->show();
            
            // Enable next steps
            m_backupGroup->setEnabled(true);
            updateVerificationUI();
            
            QMessageBox::information(this, "Success", "Verification successful! Please save your backup codes.");
        } else {
            totpDialog->showError("Invalid code. Please try again.");
            totpDialog->exec();
            
            m_verificationStatusLabel->setText("❌ Invalid code. Please try again.");
            m_verificationStatusLabel->setStyleSheet(getErrorStyle());
            m_verificationStatusLabel->show();
        }
    }
    
    totpDialog->deleteLater();
}

void TOTPSetupDialog::onCopySecret()
{
    QString secret = TOTP::encodeBase32(m_totp.getSecret());
    QApplication::clipboard()->setText(secret);
    
    m_copySecretButton->setText("✅ Copied!");
    QTimer::singleShot(2000, [this]() {
        m_copySecretButton->setText("📋 Copy Secret Key");
    });
}

void TOTPSetupDialog::onCopyBackupCodes()
{
    QApplication::clipboard()->setText(m_backupCodesEdit->toPlainText());
    
    m_copyBackupCodesButton->setText("✅ Copied!");
    QTimer::singleShot(2000, [this]() {
        m_copyBackupCodesButton->setText("📋 Copy Backup Codes");
    });
}

void TOTPSetupDialog::onFinishSetup()
{
    if (!m_isVerified) {
        QMessageBox::warning(this, "Setup Incomplete", "Please verify your setup by entering a valid code first.");
        return;
    }
    
    if (!m_confirmBackupCheckBox->isChecked()) {
        QMessageBox::warning(this, "Backup Codes", "Please confirm that you have saved your backup codes.");
        return;
    }
    
    // Save to database
    saveToDatabase();
    
    m_totpEnabled = true;
    // Don't auto-close - let user see the success message and close manually
}

void TOTPSetupDialog::updateCountdown()
{
    int secondsLeft = 30 - (QDateTime::currentSecsSinceEpoch() % 30);
    m_timeProgressBar->setValue(secondsLeft);
    m_timeProgressBar->setFormat(QString("%1s").arg(secondsLeft));
    
    if (secondsLeft <= 5) {
        m_timeProgressBar->setStyleSheet(
            "QProgressBar { border: 1px solid #dee2e6; border-radius: 4px; background: #f8f9fa; height: 8px; }"
            "QProgressBar::chunk { background: #dc3545; border-radius: 3px; }"
        );
    } else {
        m_timeProgressBar->setStyleSheet(
            "QProgressBar { border: 1px solid #dee2e6; border-radius: 4px; background: #f8f9fa; height: 8px; }"
            "QProgressBar::chunk { background: #16a5b3; border-radius: 3px; }"
        );
    }
}

void TOTPSetupDialog::onCodeTextChanged()
{
    QString code = m_verificationCodeEdit->text();
    m_verifyButton->setEnabled(code.length() == 6);
    
    // Auto-verify if 6 digits are entered
    if (code.length() == 6) {
        QTimer::singleShot(500, this, &TOTPSetupDialog::onVerifyCode);
    }
    
    // Hide previous status
    m_verificationStatusLabel->hide();
}

void TOTPSetupDialog::updateVerificationUI()
{
    if (m_isVerified) {
        m_verifyGroup->setEnabled(false);
        m_finishButton->setEnabled(true);
    } else {
        m_verifyGroup->setEnabled(true);
        m_finishButton->setEnabled(false);
    }
}

void TOTPSetupDialog::saveToDatabase()
{
    qDebug() << "=== DEBUG: Saving to Database ===";
    qDebug() << "User CIN:" << m_userCin;
    
    QSqlQuery query;
    
    QString base32Secret = TOTP::encodeBase32(m_totp.getSecret());
    qDebug() << "Base32 Secret:" << base32Secret;
    
    // Convert backup codes to JSON
    QJsonArray jsonCodes;
    for (const QString &code : m_backupCodes) {
        jsonCodes.append(code);
    }
    QJsonDocument jsonDoc(jsonCodes);
    QString backupCodesJson = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "Backup codes JSON:" << backupCodesJson;
    
    // First check if table exists
    query.prepare("SELECT COUNT(*) FROM user_tables WHERE table_name = 'EMPLOYEE_TOTP'");
    if (query.exec() && query.next()) {
        int tableCount = query.value(0).toInt();
        qDebug() << "EMPLOYEE_TOTP table exists:" << (tableCount > 0);
        if (tableCount == 0) {
            QMessageBox::critical(this, "Database Error", 
                "EMPLOYEE_TOTP table does not exist. Please run the setup SQL script first.");
            return;
        }
    }
    
    // First try to update existing record
    query.prepare("UPDATE employee_totp SET secret_key = ?, is_enabled = 1, backup_codes = ?, setup_date = ? WHERE employee_cin = ?");
    
    query.addBindValue(base32Secret);
    query.addBindValue(backupCodesJson);
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(m_userCin);
    
    qDebug() << "Attempting UPDATE...";
    if (!query.exec()) {
        qDebug() << "UPDATE failed:" << query.lastError().text();
        
        // If update failed, try insert
        query.prepare("INSERT INTO employee_totp (employee_cin, secret_key, is_enabled, backup_codes, setup_date) "
                      "VALUES (?, ?, 1, ?, ?)");
        
        query.addBindValue(m_userCin);
        query.addBindValue(base32Secret);
        query.addBindValue(backupCodesJson);
        query.addBindValue(QDateTime::currentDateTime());
        
        qDebug() << "Attempting INSERT...";
        if (!query.exec()) {
            qDebug() << "INSERT failed:" << query.lastError().text();
            QMessageBox::critical(this, "Database Error", 
                                 "Failed to save 2FA settings: " + query.lastError().text());
        } else {
            qDebug() << "INSERT successful!";
            QMessageBox::information(this, "Success", "Two-factor authentication has been set up successfully!\n\nYou can now close this dialog.");
            // Change finish button to close button
            m_finishButton->setText("✅ Close");
            disconnect(m_finishButton, &QPushButton::clicked, this, &TOTPSetupDialog::onFinishSetup);
            connect(m_finishButton, &QPushButton::clicked, this, &QDialog::accept);
        }
    } else {
        int rowsAffected = query.numRowsAffected();
        qDebug() << "UPDATE rows affected:" << rowsAffected;
        if (rowsAffected == 0) {
            qDebug() << "No rows updated, trying INSERT...";
            
            // If no rows were updated, try insert
            query.prepare("INSERT INTO employee_totp (employee_cin, secret_key, is_enabled, backup_codes, setup_date) "
                          "VALUES (?, ?, 1, ?, ?)");
            
            query.addBindValue(m_userCin);
            query.addBindValue(base32Secret);
            query.addBindValue(backupCodesJson);
            query.addBindValue(QDateTime::currentDateTime());
            
            if (!query.exec()) {
                qDebug() << "INSERT after UPDATE failed:" << query.lastError().text();
                QMessageBox::critical(this, "Database Error", 
                                     "Failed to save 2FA settings: " + query.lastError().text());
            } else {
                qDebug() << "INSERT after UPDATE successful!";
                QMessageBox::information(this, "Success", "Two-factor authentication has been set up successfully!\n\nYou can now close this dialog.");
                // Change finish button to close button
                m_finishButton->setText("✅ Close");
                disconnect(m_finishButton, &QPushButton::clicked, this, &TOTPSetupDialog::onFinishSetup);
                connect(m_finishButton, &QPushButton::clicked, this, &QDialog::accept);
            }
        } else {
            qDebug() << "UPDATE successful!";
            QMessageBox::information(this, "Success", "Two-factor authentication has been updated successfully!\n\nYou can now close this dialog.");
            // Change finish button to close button
            m_finishButton->setText("✅ Close");
            disconnect(m_finishButton, &QPushButton::clicked, this, &TOTPSetupDialog::onFinishSetup);
            connect(m_finishButton, &QPushButton::clicked, this, &QDialog::accept);
        }
    }
}