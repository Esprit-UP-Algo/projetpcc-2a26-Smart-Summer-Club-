#ifndef RFIDMANAGER_H
#define RFIDMANAGER_H

#include <QObject>
#include <QDebug>
#include "rfidservice.h"
#include "connexion_ard.h"

/**
 * Simple RFID Manager that you can add to your existing application
 * Just create one instance and call startRFIDSystem() 
 */
class RFIDManager : public QObject
{
    Q_OBJECT

public:
    explicit RFIDManager(QObject *parent = nullptr);
    explicit RFIDManager(Arduino *existingArduino, QObject *parent = nullptr);
    ~RFIDManager();

    // Simple methods to start/stop RFID
    bool startRFIDSystem();
    void stopRFIDSystem();
    bool isRunning() const;
    
    // Get Arduino instance for sharing
    Arduino* getArduino() const { return m_arduino; }

public slots:
    // Handle access results
    void onAccessAttempt(const QString &rfidUid, bool granted, const QString &memberName);
    void onRFIDError(const QString &error);
    void onRFIDDebug(const QString &message);

private:
    RFIDService *m_rfidService;
    Arduino *m_arduino;
    bool m_isRunning;

    void setupConnections();

signals:
    void accessGranted(const QString &memberName, const QString &rfidUid);
    void accessDenied(const QString &rfidUid, const QString &reason);
};

#endif // RFIDMANAGER_H