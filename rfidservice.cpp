#include "rfidservice.h"
#include "Connection.h"

// Initialize static constants
const QString RFIDService::VERIFY_COMMAND_PREFIX = "VERIFY:";
const QString RFIDService::ACCESS_GRANTED_RESPONSE = "ACCESS:GRANTED:";
const QString RFIDService::ACCESS_DENIED_RESPONSE = "ACCESS:DENIED";

RFIDService::RFIDService(QObject *parent)
    : QObject(parent),
      m_arduino(nullptr),
      m_processTimer(new QTimer(this)),
      m_serviceActive(false)
{
    // Setup processing timer
    m_processTimer->setSingleShot(false);
    m_processTimer->setInterval(PROCESS_INTERVAL_MS);
    connect(m_processTimer, &QTimer::timeout, this, &RFIDService::processRFIDQueue);
    
    qDebug() << "RFIDService initialized";
}

RFIDService::~RFIDService()
{
    stopListening();
    qDebug() << "RFIDService destroyed";
}

bool RFIDService::initializeService()
{
    // Check database connection
    Connection* conn = Connection::getInstance();
    if (!conn) {
        emit errorOccurred("Failed to get database connection");
        return false;
    }
    
    // Test RFID_CARDS table access
    QSqlQuery testQuery;
    if (!testQuery.exec("SELECT COUNT(*) FROM SUMMERCLUB.RFID_CARDS")) {
        emit errorOccurred("RFID_CARDS table not accessible: " + testQuery.lastError().text());
        return false;
    }
    
    emit debugMessage("RFIDService initialized successfully");
    return true;
}

void RFIDService::startListening()
{
    if (!m_arduino) {
        emit errorOccurred("Arduino connection not set");
        return;
    }
    
    if (!m_arduino->isConnected()) {
        emit errorOccurred("Arduino not connected");
        return;
    }
    
    m_serviceActive = true;
    m_processTimer->start();
    emit serviceStatusChanged(true);
    emit debugMessage("RFID service started listening");
}

void RFIDService::stopListening()
{
    m_serviceActive = false;
    m_processTimer->stop();
    m_rfidQueue.clear();
    emit serviceStatusChanged(false);
    emit debugMessage("RFID service stopped listening");
}

bool RFIDService::isServiceActive() const
{
    return m_serviceActive;
}

RFIDService::AccessResult RFIDService::verifyRFIDAccess(const QString &rfidUid)
{
    AccessResult result;
    result.granted = false;
    result.rfidUid = rfidUid;
    result.memberName = "";
    result.memberCin = "";
    result.message = "Access Denied";
    
    emit debugMessage("🔍 === STARTING RFID VERIFICATION ===");
    emit debugMessage("📱 Card UID: " + rfidUid);
    
    if (!validateRFIDFormat(rfidUid)) {
        result.message = "Invalid RFID format";
        emit debugMessage("❌ Invalid RFID format: " + rfidUid);
        logAccessAttempt(rfidUid, "", "INVALID_FORMAT");
        return result;
    }
    
    emit debugMessage("✅ RFID format valid, querying database...");
    
    QSqlQuery query;
    query.prepare("SELECT r.CIN, m.FIRST_NAME, m.LAST_NAME, r.CARD_STATUS "
                  "FROM SUMMERCLUB.RFID_CARDS r "
                  "JOIN SUMMERCLUB.MEMBERS m ON r.CIN = m.CIN "
                  "WHERE r.RFID_UID = :rfid_uid");
    query.bindValue(":rfid_uid", rfidUid);
    
    if (!query.exec()) {
        result.message = "Database error: " + query.lastError().text();
        emit debugMessage("❌ Database query failed: " + query.lastError().text());
        emit errorOccurred(result.message);
        logAccessAttempt(rfidUid, "", "DATABASE_ERROR");
        return result;
    }
    
    emit debugMessage("💾 Database query executed successfully");
    
    if (query.next()) {
        result.memberCin = query.value(0).toString();
        QString firstName = query.value(1).toString();
        QString lastName = query.value(2).toString();
        QString cardStatus = query.value(3).toString();
        
        result.memberName = firstName + " " + lastName;
        
        emit debugMessage("👤 Found Member: " + result.memberName);
        emit debugMessage("🆔 Member CIN: " + result.memberCin);
        emit debugMessage("💳 Card Status: " + cardStatus);
        
        if (cardStatus == "Active") {
            result.granted = true;
            result.message = "Access Granted to " + result.memberName;
            emit debugMessage("✅ ACCESS GRANTED for " + result.memberName + " (CIN: " + result.memberCin + ")");
            updateLastUsed(rfidUid);
            logAccessAttempt(rfidUid, result.memberCin, "GRANTED");
        } else {
            result.message = "Card " + cardStatus + " - Access Denied";
            emit debugMessage("❌ ACCESS DENIED - Card status: " + cardStatus + " for " + result.memberName + " (CIN: " + result.memberCin + ")");
            logAccessAttempt(rfidUid, result.memberCin, "CARD_" + cardStatus.toUpper());
        }
    } else {
        result.message = "Unknown RFID Card";
        emit debugMessage("❓ Card not found in database: " + rfidUid);
        emit debugMessage("💡 Suggestion: Register this card with a member first");
        logAccessAttempt(rfidUid, "", "UNKNOWN_CARD");
    }
    
    emit debugMessage("🏁 === VERIFICATION COMPLETE ===");
    emit accessAttempt(rfidUid, result.granted, result.memberName);
    return result;
}

bool RFIDService::registerRFIDCard(const QString &memberCin, const QString &rfidUid, const QString &notes)
{
    if (!validateRFIDFormat(rfidUid)) {
        emit errorOccurred("Invalid RFID UID format");
        return false;
    }
    
    if (!isMemberExists(memberCin)) {
        emit errorOccurred("Member with CIN " + memberCin + " does not exist");
        return false;
    }
    
    if (isRFIDCardExists(rfidUid)) {
        emit errorOccurred("RFID card " + rfidUid + " is already registered");
        return false;
    }
    
    QSqlQuery query;
    query.prepare("INSERT INTO SUMMERCLUB.RFID_CARDS (RFID_UID, CIN, NOTES) "
                  "VALUES (:rfid_uid, :cin, :notes)");
    query.bindValue(":rfid_uid", rfidUid);
    query.bindValue(":cin", memberCin);
    query.bindValue(":notes", notes);
    
    if (query.exec()) {
        emit cardRegistered(rfidUid, memberCin);
        emit debugMessage("RFID card registered: " + rfidUid + " for member: " + memberCin);
        return true;
    } else {
        emit errorOccurred("Failed to register RFID card: " + query.lastError().text());
        return false;
    }
}

bool RFIDService::updateCardStatus(const QString &rfidUid, const QString &status)
{
    QStringList validStatuses = {"Active", "Disabled", "Lost", "Expired"};
    if (!validStatuses.contains(status)) {
        emit errorOccurred("Invalid card status: " + status);
        return false;
    }
    
    QSqlQuery query;
    query.prepare("UPDATE SUMMERCLUB.RFID_CARDS SET CARD_STATUS = :status, "
                  "UPDATED_DATE = SYSDATE WHERE RFID_UID = :rfid_uid");
    query.bindValue(":status", status);
    query.bindValue(":rfid_uid", rfidUid);
    
    if (query.exec() && query.numRowsAffected() > 0) {
        emit debugMessage("Card status updated: " + rfidUid + " -> " + status);
        return true;
    } else {
        emit errorOccurred("Failed to update card status: " + query.lastError().text());
        return false;
    }
}

bool RFIDService::removeRFIDCard(const QString &rfidUid)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SUMMERCLUB.RFID_CARDS WHERE RFID_UID = :rfid_uid");
    query.bindValue(":rfid_uid", rfidUid);
    
    if (query.exec() && query.numRowsAffected() > 0) {
        emit debugMessage("RFID card removed: " + rfidUid);
        return true;
    } else {
        emit errorOccurred("Failed to remove RFID card: " + query.lastError().text());
        return false;
    }
}

QString RFIDService::getMemberNameByRFID(const QString &rfidUid)
{
    QSqlQuery query;
    query.prepare("SELECT m.FIRST_NAME || ' ' || m.LAST_NAME as FULL_NAME "
                  "FROM SUMMERCLUB.RFID_CARDS r "
                  "JOIN SUMMERCLUB.MEMBERS m ON r.CIN = m.CIN "
                  "WHERE r.RFID_UID = :rfid_uid");
    query.bindValue(":rfid_uid", rfidUid);
    
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}

bool RFIDService::isRFIDCardExists(const QString &rfidUid)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SUMMERCLUB.RFID_CARDS WHERE RFID_UID = :rfid_uid");
    query.bindValue(":rfid_uid", rfidUid);
    
    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

bool RFIDService::isMemberExists(const QString &cin)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SUMMERCLUB.MEMBERS WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    
    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

QStringList RFIDService::getMemberRFIDCards(const QString &cin)
{
    QStringList cards;
    QSqlQuery query;
    query.prepare("SELECT RFID_UID FROM SUMMERCLUB.RFID_CARDS WHERE CIN = :cin AND CARD_STATUS = 'Active'");
    query.bindValue(":cin", cin);
    
    if (query.exec()) {
        while (query.next()) {
            cards.append(query.value(0).toString());
        }
    }
    return cards;
}

void RFIDService::setArduinoConnection(Arduino* arduino)
{
    if (m_arduino) {
        disconnect(m_arduino, &Arduino::dataReceived, this, &RFIDService::onRFIDDataReceived);
        disconnect(m_arduino, &Arduino::connectionStatusChanged, this, &RFIDService::onArduinoConnectionChanged);
    }
    
    m_arduino = arduino;
    
    if (m_arduino) {
        connect(m_arduino, &Arduino::dataReceived, this, &RFIDService::onRFIDDataReceived);
        connect(m_arduino, &Arduino::connectionStatusChanged, this, &RFIDService::onArduinoConnectionChanged);
        emit debugMessage("Arduino connection set for RFID service");
    }
}

Arduino* RFIDService::getArduinoConnection() const
{
    return m_arduino;
}

void RFIDService::onRFIDDataReceived(const QByteArray &data)
{
    if (!m_serviceActive) {
        emit debugMessage("⚠️ RFID service not active - ignoring data");
        return;
    }
    
    QString dataStr = QString::fromUtf8(data).trimmed();
    emit debugMessage("📡 Received data: " + dataStr);
    
    // Check if this is a VERIFY command or contains VERIFY
    if (dataStr.startsWith(VERIFY_COMMAND_PREFIX)) {
        QString rfidUid = dataStr.mid(VERIFY_COMMAND_PREFIX.length()).trimmed();
        emit debugMessage("🔍 Extracted UID from VERIFY: " + rfidUid);
        
        if (!rfidUid.isEmpty()) {
            if (!m_rfidQueue.contains(rfidUid)) {
                m_rfidQueue.append(rfidUid);
                emit debugMessage("➕ Added to queue: " + rfidUid + " (Queue size: " + QString::number(m_rfidQueue.size()) + ")");
            } else {
                emit debugMessage("⚠️ UID already in queue: " + rfidUid);
            }
        } else {
            emit debugMessage("❌ Empty UID from VERIFY command");
        }
    } else if (dataStr.contains("VERIFY:")) {
        // Handle case where VERIFY might be in the middle of the string
        int verifyIndex = dataStr.indexOf("VERIFY:");
        QString verifyPart = dataStr.mid(verifyIndex);
        emit debugMessage("🔍 Found VERIFY in data: " + verifyPart);
        
        QString rfidUid = verifyPart.mid(7).trimmed(); // Skip "VERIFY:"
        if (!rfidUid.isEmpty() && !m_rfidQueue.contains(rfidUid)) {
            m_rfidQueue.append(rfidUid);
            emit debugMessage("➕ Added to queue (partial): " + rfidUid);
        }
    } else {
        emit debugMessage("ℹ️ Non-VERIFY data: " + dataStr);
    }
}

void RFIDService::onRFIDCardDetected(const QString &rfidUid)
{
    if (!m_serviceActive) {
        emit debugMessage("⚠️ Service not active - ignoring card: " + rfidUid);
        return;
    }
    
    emit debugMessage("🏷️ Direct RFID card detected: " + rfidUid);
    
    if (!rfidUid.isEmpty() && !m_rfidQueue.contains(rfidUid)) {
        m_rfidQueue.append(rfidUid);
        emit debugMessage("➕ Added to queue (direct): " + rfidUid + " (Queue size: " + QString::number(m_rfidQueue.size()) + ")");
    }
}

void RFIDService::onArduinoConnectionChanged(bool connected)
{
    if (!connected && m_serviceActive) {
        stopListening();
        emit errorOccurred("Arduino disconnected - RFID service stopped");
    }
}

void RFIDService::processRFIDQueue()
{
    if (m_rfidQueue.isEmpty()) return;
    
    QString rfidUid = m_rfidQueue.takeFirst();
    emit debugMessage("🔄 Processing queue item: " + rfidUid + " (Remaining: " + QString::number(m_rfidQueue.size()) + ")");
    
    AccessResult result = verifyRFIDAccess(rfidUid);
    
    // Detailed result message
    QString status = result.granted ? "✅ ACCESS GRANTED" : "❌ ACCESS DENIED";
    QString member = result.memberName.isEmpty() ? "Unknown Card" : result.memberName;
    emit debugMessage("\n🎯 RESULT: " + status + " - " + member + " (" + rfidUid + ")");
    emit debugMessage("Message: " + result.message);
    
    sendAccessResponse(result.granted, result.memberName);
    emit debugMessage("📤 Response sent to Arduino\n");
    
    // Emit the access attempt signal
    emit accessAttempt(rfidUid, result.granted, result.memberName);
}

void RFIDService::updateLastUsed(const QString &rfidUid)
{
    QSqlQuery query;
    query.prepare("UPDATE SUMMERCLUB.RFID_CARDS SET LAST_USED = CURRENT_TIMESTAMP "
                  "WHERE RFID_UID = :rfid_uid");
    query.bindValue(":rfid_uid", rfidUid);
    query.exec(); // Fire and forget - not critical if this fails
}

void RFIDService::sendAccessResponse(bool granted, const QString &memberName)
{
    if (!m_arduino || !m_arduino->isConnected()) return;
    
    QString response;
    if (granted) {
        response = ACCESS_GRANTED_RESPONSE + memberName;
    } else {
        response = ACCESS_DENIED_RESPONSE;
    }
    
    m_arduino->write_to_arduino(response.toUtf8());
    emit debugMessage("Sent to Arduino: " + response);
}

bool RFIDService::validateRFIDFormat(const QString &rfidUid)
{
    if (rfidUid.isEmpty()) return false;
    
    // Check format: "XX XX XX XX" (hex bytes separated by spaces)
    QStringList parts = rfidUid.split(" ");
    if (parts.length() < 2 || parts.length() > 10) return false; // Typical UID is 4-10 bytes
    
    for (const QString &part : parts) {
        if (part.length() != 2) return false;
        
        bool ok;
        part.toInt(&ok, 16);
        if (!ok) return false;
    }
    
    return true;
}

void RFIDService::logAccessAttempt(const QString &rfidUid, const QString &memberCin, const QString &result)
{
    // Get member name for logging
    QString memberName = "";
    if (!memberCin.isEmpty()) {
        QSqlQuery nameQuery;
        nameQuery.prepare("SELECT FIRST_NAME || ' ' || LAST_NAME FROM SUMMERCLUB.MEMBERS WHERE CIN = :cin");
        nameQuery.bindValue(":cin", memberCin);
        if (nameQuery.exec() && nameQuery.next()) {
            memberName = nameQuery.value(0).toString();
        }
    }
    
    // Insert into access log table
    QSqlQuery logQuery;
    logQuery.prepare("INSERT INTO SUMMERCLUB.RFID_ACCESS_LOG "
                    "(RFID_UID, MEMBER_CIN, ACCESS_RESULT, MEMBER_NAME, DEVICE_LOCATION) "
                    "VALUES (:rfid_uid, :member_cin, :access_result, :member_name, :device_location)");
    logQuery.bindValue(":rfid_uid", rfidUid);
    logQuery.bindValue(":member_cin", memberCin.isEmpty() ? QVariant() : memberCin);
    logQuery.bindValue(":access_result", result);
    logQuery.bindValue(":member_name", memberName.isEmpty() ? QVariant() : memberName);
    logQuery.bindValue(":device_location", "Main Entrance");
    
    if (!logQuery.exec()) {
        emit debugMessage("⚠️ Failed to log access attempt: " + logQuery.lastError().text());
    } else {
        emit debugMessage("📝 Access logged: " + result + " - " + (memberName.isEmpty() ? "Unknown" : memberName));
    }
    
    // Also emit simple debug message for immediate visibility
    QString logMessage = QString("📊 ACCESS LOG: %1 | %2 | %3 | %4")
                        .arg(rfidUid, memberCin.isEmpty() ? "Unknown" : memberCin, result, memberName.isEmpty() ? "Unknown" : memberName);
    emit debugMessage(logMessage);
}