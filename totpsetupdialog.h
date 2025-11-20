#ifndef TOTPSETUPDIALOG_H
#define TOTPSETUPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QProgressBar>
#include <QTimer>
#include <QPixmap>
#include <QFrame>
#include <QCheckBox>
#include <QScrollArea>
#include <QGridLayout>
#include <QSpacerItem>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>

#include "totp.h"
#include "qrcodegenerator.h"

class TOTPSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TOTPSetupDialog(const QString &userCin, const QString &userName, QWidget *parent = nullptr);
    ~TOTPSetupDialog();
    
    bool isTOTPEnabled() const { return m_totpEnabled; }
    QByteArray getSecretKey() const { return m_totp.getSecret(); }
    QStringList getBackupCodes() const { return m_backupCodes; }

private slots:
    void onGenerateNewSecret();
    void onVerifyCode();
    void onCopySecret();
    void onCopyBackupCodes();
    void onFinishSetup();
    void updateCountdown();
    void onCodeTextChanged();

private:
    void setupUI();
    void generateQRCode();
    void generateBackupCodes();
    void updateVerificationUI();
    void saveToDatabase();
    
    // UI Components
    QScrollArea *m_scrollArea;
    QWidget *m_mainWidget;
    QVBoxLayout *m_mainLayout;
    
    // Header
    QLabel *m_titleLabel;
    QLabel *m_instructionLabel;
    
    // Step 1: QR Code
    QGroupBox *m_qrGroup;
    QLabel *m_qrCodeLabel;
    QLabel *m_secretKeyLabel;
    QPushButton *m_copySecretButton;
    QPushButton *m_regenerateButton;
    
    // Step 2: Verification
    QGroupBox *m_verifyGroup;
    QLineEdit *m_verificationCodeEdit;
    QPushButton *m_verifyButton;
    QProgressBar *m_timeProgressBar;
    QLabel *m_timeLabel;
    QLabel *m_verificationStatusLabel;
    
    // Step 3: Backup Codes
    QGroupBox *m_backupGroup;
    QTextEdit *m_backupCodesEdit;
    QPushButton *m_copyBackupCodesButton;
    QCheckBox *m_confirmBackupCheckBox;
    
    // Step 4: Finish
    QFrame *m_finishFrame;
    QPushButton *m_finishButton;
    QPushButton *m_cancelButton;
    
    // Data
    QString m_userCin;
    QString m_userName;
    TOTP m_totp;
    QStringList m_backupCodes;
    bool m_totpEnabled;
    bool m_isVerified;
    QTimer *m_countdownTimer;
    
    // Styling
    void applyStyles();
    QString getGroupBoxStyle() const;
    QString getButtonStyle() const;
    QString getSuccessStyle() const;
    QString getErrorStyle() const;
};

#endif // TOTPSETUPDIALOG_H