#ifndef RFIDSERVICE_H
#define RFIDSERVICE_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include "connexion_ard.h"

class RFIDService : public QObject
{
    Q_OBJECT

public:
    struct AccessResult {
        bool granted;
        QString memberName;
        QString memberCin;
        QString message;
        QString rfidUid;
    };

    explicit RFIDService(QObject *parent = nullptr);
    ~RFIDService();

    // Main service methods
    bool initializeService();
    void startListening();
    void stopListening();
    bool isServiceActive() const;

    // RFID verification
    AccessResult verifyRFIDAccess(const QString &rfidUid);
    
    // RFID card management
    bool registerRFIDCard(const QString &memberCin, const QString &rfidUid, const QString &notes = "");
    bool updateCardStatus(const QString &rfidUid, const QString &status);
    bool removeRFIDCard(const QString &rfidUid);
    QString getMemberNameByRFID(const QString &rfidUid);
    
    // Database queries
    bool isRFIDCardExists(const QString &rfidUid);
    bool isMemberExists(const QString &cin);
    QStringList getMemberRFIDCards(const QString &cin);
    
    // Arduino integration
    void setArduinoConnection(Arduino* arduino);
    Arduino* getArduinoConnection() const;

signals:
    void accessAttempt(const QString &rfidUid, bool granted, const QString &memberName);
    void cardRegistered(const QString &rfidUid, const QString &memberCin);
    void serviceStatusChanged(bool active);
    void errorOccurred(const QString &error);
    void debugMessage(const QString &message);

public slots:
    void onRFIDDataReceived(const QByteArray &data);
    void onRFIDCardDetected(const QString &rfidUid);
    void onArduinoConnectionChanged(bool connected);

private slots:
    void processRFIDQueue();

private:
    Arduino *m_arduino;
    QTimer *m_processTimer;
    bool m_serviceActive;
    QStringList m_rfidQueue;
    
    // Helper methods
    void updateLastUsed(const QString &rfidUid);
    void sendAccessResponse(bool granted, const QString &memberName = "");
    bool validateRFIDFormat(const QString &rfidUid);
    void logAccessAttempt(const QString &rfidUid, const QString &memberCin, const QString &result);
    
    // Constants
    static const int PROCESS_INTERVAL_MS = 1000; // 1 second
    static const QString VERIFY_COMMAND_PREFIX;
    static const QString ACCESS_GRANTED_RESPONSE;
    static const QString ACCESS_DENIED_RESPONSE;
};

#endif // RFIDSERVICE_H