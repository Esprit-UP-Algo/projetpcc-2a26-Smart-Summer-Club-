#ifndef RFIDCARDDIALOG_H
#define RFIDCARDDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QGroupBox>
#include <QTimer>
#include "rfidcard.h"
#include "connexion_ard.h"

class RFIDCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RFIDCardDialog(QWidget *parent = nullptr);
    explicit RFIDCardDialog(const QString &cardUid, QWidget *parent = nullptr);
    explicit RFIDCardDialog(Arduino *arduino, QWidget *parent = nullptr);
    explicit RFIDCardDialog(const QString &cardUid, Arduino *arduino, QWidget *parent = nullptr);
    ~RFIDCardDialog();
    
    bool isEditMode() const { return m_isEditMode; }
    QString getCardUid() const;
    
private slots:
    void onSaveClicked();
    void onCancelClicked();
    void onMemberChanged();
    void onScanCardClicked();
    void onRFIDCardDetected(const QString &rfidUid);
    void onScanTimeout();
    
private:
    void setupUI();
    void setupStyles();
    void connectSignals();
    void loadMembersList();
    void loadCardData();
    void validateForm();
    void setupArduinoConnection(Arduino *sharedArduino = nullptr);
    
    // UI Components
    QGroupBox *m_cardInfoGroup;
    QGroupBox *m_memberInfoGroup;
    
    QLineEdit *m_cardUidLineEdit;
    QComboBox *m_memberComboBox;
    QComboBox *m_statusComboBox;
    QTextEdit *m_notesTextEdit;
    QPushButton *m_scanCardButton;
    
    QLabel *m_memberCinLabel;
    QLabel *m_memberNameLabel;
    QLabel *m_memberPhoneLabel;
    QLabel *m_memberEmailLabel;
    
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    
    // Data
    bool m_isEditMode;
    QString m_originalCardUid;
    RFIDCard *m_rfidCard;
    
    // RFID Scanning
    class Arduino *m_arduino;
    bool m_isScanning;
};

#endif // RFIDCARDDIALOG_H