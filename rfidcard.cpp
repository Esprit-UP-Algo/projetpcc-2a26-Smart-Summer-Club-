#include "rfidcard.h"
#include "Connection.h"

RFIDCard::RFIDCard(QObject *parent)
    : QObject(parent), m_isNewRecord(true)
{
    initializeDefaults();
}

RFIDCard::RFIDCard(const QString &rfidUid, const QString &memberCin, 
                   CardStatus status, const QString &notes, QObject *parent)
    : QObject(parent), 
      m_rfidUid(rfidUid),
      m_memberCin(memberCin),
      m_cardStatus(status),
      m_notes(notes),
      m_isNewRecord(true)
{
    initializeDefaults();
}

void RFIDCard::initializeDefaults()
{
    m_rfidId = -1;
    m_cardStatus = Active;
    m_issuedDate = QDate::currentDate();
    m_createdDate = QDate::currentDate();
    m_updatedDate = QDate::currentDate();
}

// Getters
int RFIDCard::getRfidId() const { return m_rfidId; }
QString RFIDCard::getRfidUid() const { return m_rfidUid; }
QString RFIDCard::getMemberCin() const { return m_memberCin; }
RFIDCard::CardStatus RFIDCard::getCardStatus() const { return m_cardStatus; }
QDate RFIDCard::getIssuedDate() const { return m_issuedDate; }
QDateTime RFIDCard::getLastUsed() const { return m_lastUsed; }
QString RFIDCard::getNotes() const { return m_notes; }
QDate RFIDCard::getCreatedDate() const { return m_createdDate; }
QDate RFIDCard::getUpdatedDate() const { return m_updatedDate; }

// Setters
void RFIDCard::setRfidUid(const QString &rfidUid) { m_rfidUid = rfidUid; }
void RFIDCard::setMemberCin(const QString &memberCin) { m_memberCin = memberCin; }
void RFIDCard::setCardStatus(CardStatus status) { m_cardStatus = status; }
void RFIDCard::setNotes(const QString &notes) { m_notes = notes; }

bool RFIDCard::save()
{
    qDebug() << "💾 RFIDCard::save() called for:" << m_rfidUid;
    qDebug() << "   Member CIN:" << m_memberCin;
    qDebug() << "   Status:" << statusToString(m_cardStatus);
    qDebug() << "   Is New Record:" << m_isNewRecord;
    
    if (!validateData()) {
        qDebug() << "❌ RFIDCard validation failed";
        return false;
    }
    
    qDebug() << "✅ RFIDCard validation passed";
    
    bool success = m_isNewRecord ? executeInsert() : executeUpdate();
    
    if (success) {
        qDebug() << "✅ RFIDCard save operation successful";
        m_isNewRecord = false;
        emit cardSaved(m_rfidUid);
    } else {
        qDebug() << "❌ RFIDCard save operation failed";
    }
    
    return success;
}

bool RFIDCard::remove()
{
    if (m_rfidId <= 0) {
        qDebug() << "Cannot delete RFID card - invalid ID";
        return false;
    }
    
    QSqlQuery query;
    query.prepare("DELETE FROM SUMMERCLUB.RFID_CARDS WHERE RFID_ID = :rfid_id");
    query.bindValue(":rfid_id", m_rfidId);
    
    if (query.exec()) {
        emit cardRemoved(m_rfidUid);
        qDebug() << "RFID card removed:" << m_rfidUid;
        return true;
    } else {
        qDebug() << "Failed to remove RFID card:" << query.lastError().text();
        return false;
    }
}

bool RFIDCard::load(const QString &rfidUid)
{
    qDebug() << "📂 Loading RFID card by UID:" << rfidUid;
    
    QSqlQuery query;
    query.prepare("SELECT RFID_ID, RFID_UID, CIN, CARD_STATUS, ISSUED_DATE, "
                  "LAST_USED, NOTES, CREATED_DATE, UPDATED_DATE "
                  "FROM SUMMERCLUB.RFID_CARDS WHERE RFID_UID = :rfid_uid");
    query.bindValue(":rfid_uid", rfidUid);
    
    if (query.exec() && query.next()) {
        m_rfidId = query.value(0).toInt();
        m_rfidUid = query.value(1).toString();
        m_memberCin = query.value(2).toString();
        m_cardStatus = stringToStatus(query.value(3).toString());
        m_issuedDate = query.value(4).toDate();
        m_lastUsed = query.value(5).toDateTime();
        m_notes = query.value(6).toString();
        m_createdDate = query.value(7).toDate();
        m_updatedDate = query.value(8).toDate();
        
        qDebug() << "✅ Card loaded successfully:";
        qDebug() << "   RFID_ID:" << m_rfidId;
        qDebug() << "   RFID_UID:" << m_rfidUid;
        qDebug() << "   CIN:" << m_memberCin;
        qDebug() << "   Status:" << statusToString(m_cardStatus);
        
        m_isNewRecord = false;
        return true;
    } else {
        qDebug() << "❌ Failed to load card or card not found:" << rfidUid;
        if (!query.exec()) {
            qDebug() << "❌ SQL Error:" << query.lastError().text();
        }
    }
    
    return false;
}

bool RFIDCard::load(int rfidId)
{
    QSqlQuery query;
    query.prepare("SELECT RFID_ID, RFID_UID, CIN, CARD_STATUS, ISSUED_DATE, "
                  "LAST_USED, NOTES, CREATED_DATE, UPDATED_DATE "
                  "FROM SUMMERCLUB.RFID_CARDS WHERE RFID_ID = :rfid_id");
    query.bindValue(":rfid_id", rfidId);
    
    if (query.exec() && query.next()) {
        m_rfidId = query.value(0).toInt();
        m_rfidUid = query.value(1).toString();
        m_memberCin = query.value(2).toString();
        m_cardStatus = stringToStatus(query.value(3).toString());
        m_issuedDate = query.value(4).toDate();
        m_lastUsed = query.value(5).toDateTime();
        m_notes = query.value(6).toString();
        m_createdDate = query.value(7).toDate();
        m_updatedDate = query.value(8).toDate();
        
        m_isNewRecord = false;
        return true;
    }
    
    return false;
}

QSqlQueryModel* RFIDCard::getAllCards()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT r.RFID_ID, r.RFID_UID, r.CIN, "
                    "m.FIRST_NAME || ' ' || m.LAST_NAME as MEMBER_NAME, "
                    "r.CARD_STATUS, r.ISSUED_DATE, r.LAST_USED, r.NOTES "
                    "FROM SUMMERCLUB.RFID_CARDS r "
                    "LEFT JOIN SUMMERCLUB.MEMBERS m ON r.CIN = m.CIN "
                    "ORDER BY r.CREATED_DATE DESC");
    return model;
}

QSqlQueryModel* RFIDCard::getCardsByMember(const QString &memberCin)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT RFID_ID, RFID_UID, CARD_STATUS, ISSUED_DATE, "
                  "LAST_USED, NOTES FROM SUMMERCLUB.RFID_CARDS "
                  "WHERE CIN = :cin ORDER BY ISSUED_DATE DESC");
    query.bindValue(":cin", memberCin);
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

QSqlQueryModel* RFIDCard::getCardsByStatus(CardStatus status)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT r.RFID_ID, r.RFID_UID, r.CIN, "
                  "m.FIRST_NAME || ' ' || m.LAST_NAME as MEMBER_NAME, "
                  "r.ISSUED_DATE, r.LAST_USED, r.NOTES "
                  "FROM SUMMERCLUB.RFID_CARDS r "
                  "LEFT JOIN SUMMERCLUB.MEMBERS m ON r.CIN = m.CIN "
                  "WHERE r.CARD_STATUS = :status ORDER BY r.ISSUED_DATE DESC");
    query.bindValue(":status", statusToString(status));
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

RFIDCard* RFIDCard::findByUid(const QString &rfidUid)
{
    RFIDCard* card = new RFIDCard();
    if (card->load(rfidUid)) {
        return card;
    } else {
        delete card;
        return nullptr;
    }
}

RFIDCard* RFIDCard::findByMember(const QString &memberCin)
{
    QSqlQuery query;
    query.prepare("SELECT RFID_UID FROM SUMMERCLUB.RFID_CARDS "
                  "WHERE CIN = :cin AND CARD_STATUS = 'Active' "
                  "ORDER BY ISSUED_DATE DESC");
    query.bindValue(":cin", memberCin);
    
    if (query.exec() && query.next()) {
        return findByUid(query.value(0).toString());
    }
    
    return nullptr;
}

bool RFIDCard::deleteByUid(const QString &rfidUid)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SUMMERCLUB.RFID_CARDS WHERE RFID_UID = :rfid_uid");
    query.bindValue(":rfid_uid", rfidUid);
    
    return query.exec();
}

bool RFIDCard::isUidExists(const QString &rfidUid)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SUMMERCLUB.RFID_CARDS WHERE RFID_UID = :rfid_uid");
    query.bindValue(":rfid_uid", rfidUid);
    
    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

int RFIDCard::getActiveCardCount(const QString &memberCin)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SUMMERCLUB.RFID_CARDS "
                  "WHERE CIN = :cin AND CARD_STATUS = 'Active'");
    query.bindValue(":cin", memberCin);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    
    return 0;
}

QString RFIDCard::statusToString(CardStatus status)
{
    switch (status) {
        case Active: return "Active";
        case Disabled: return "Disabled";
        case Lost: return "Lost";
        case Expired: return "Expired";
        default: return "Active";
    }
}

RFIDCard::CardStatus RFIDCard::stringToStatus(const QString &statusStr)
{
    if (statusStr == "Disabled") return Disabled;
    if (statusStr == "Lost") return Lost;
    if (statusStr == "Expired") return Expired;
    return Active; // Default to Active
}

bool RFIDCard::updateLastUsed()
{
    if (m_rfidId <= 0) return false;
    
    QSqlQuery query;
    query.prepare("UPDATE SUMMERCLUB.RFID_CARDS SET LAST_USED = CURRENT_TIMESTAMP "
                  "WHERE RFID_ID = :rfid_id");
    query.bindValue(":rfid_id", m_rfidId);
    
    if (query.exec()) {
        m_lastUsed = QDateTime::currentDateTime();
        emit cardUsed(m_rfidUid, m_memberCin);
        return true;
    }
    
    return false;
}

bool RFIDCard::isValid() const
{
    return !m_rfidUid.isEmpty() && !m_memberCin.isEmpty() && validateRfidUid(m_rfidUid);
}

bool RFIDCard::validateRfidUid(const QString &rfidUid)
{
    if (rfidUid.isEmpty()) return false;
    
    // Check format: "XX XX XX XX" (hex bytes separated by spaces)
    QStringList parts = rfidUid.split(" ");
    if (parts.length() < 2 || parts.length() > 10) return false;
    
    for (const QString &part : parts) {
        if (part.length() != 2) return false;
        
        bool ok;
        part.toInt(&ok, 16);
        if (!ok) return false;
    }
    
    return true;
}

int RFIDCard::getTotalActiveCards()
{
    QSqlQuery query("SELECT COUNT(*) FROM SUMMERCLUB.RFID_CARDS WHERE CARD_STATUS = 'Active'");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int RFIDCard::getTotalCardsByStatus(CardStatus status)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SUMMERCLUB.RFID_CARDS WHERE CARD_STATUS = :status");
    query.bindValue(":status", statusToString(status));
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QSqlQueryModel* RFIDCard::getRecentlyUsedCards(int days)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT r.RFID_UID, r.CIN, "
                  "m.FIRST_NAME || ' ' || m.LAST_NAME as MEMBER_NAME, "
                  "r.LAST_USED FROM SUMMERCLUB.RFID_CARDS r "
                  "LEFT JOIN SUMMERCLUB.MEMBERS m ON r.CIN = m.CIN "
                  "WHERE r.LAST_USED >= SYSDATE - :days "
                  "ORDER BY r.LAST_USED DESC");
    query.bindValue(":days", days);
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

QSqlQueryModel* RFIDCard::getUnusedCards(int days)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT r.RFID_UID, r.CIN, "
                  "m.FIRST_NAME || ' ' || m.LAST_NAME as MEMBER_NAME, "
                  "r.ISSUED_DATE FROM SUMMERCLUB.RFID_CARDS r "
                  "LEFT JOIN SUMMERCLUB.MEMBERS m ON r.CIN = m.CIN "
                  "WHERE (r.LAST_USED IS NULL OR r.LAST_USED < SYSDATE - :days) "
                  "AND r.CARD_STATUS = 'Active' "
                  "ORDER BY r.ISSUED_DATE DESC");
    query.bindValue(":days", days);
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

bool RFIDCard::validateData() const
{
    if (m_rfidUid.isEmpty()) {
        qDebug() << "RFID UID is empty";
        return false;
    }
    
    if (m_memberCin.isEmpty()) {
        qDebug() << "Member CIN is empty";
        return false;
    }
    
    if (!validateRfidUid(m_rfidUid)) {
        qDebug() << "Invalid RFID UID format:" << m_rfidUid;
        return false;
    }
    
    return true;
}

bool RFIDCard::executeInsert()
{
    qDebug() << "➕ Executing INSERT for RFID card:" << m_rfidUid;
    
    QSqlQuery query;
    query.prepare("INSERT INTO SUMMERCLUB.RFID_CARDS "
                  "(RFID_UID, CIN, CARD_STATUS, NOTES) "
                  "VALUES (:rfid_uid, :cin, :status, :notes)");
    
    query.bindValue(":rfid_uid", m_rfidUid);
    query.bindValue(":cin", m_memberCin);
    query.bindValue(":status", statusToString(m_cardStatus));
    query.bindValue(":notes", m_notes);
    
    qDebug() << "   SQL Parameters:";
    qDebug() << "     RFID_UID:" << m_rfidUid;
    qDebug() << "     CIN:" << m_memberCin;
    qDebug() << "     STATUS:" << statusToString(m_cardStatus);
    qDebug() << "     NOTES:" << m_notes;
    
    if (query.exec()) {
        // Get the generated ID
        QSqlQuery idQuery("SELECT SUMMERCLUB.RFID_ID_SEQ.CURRVAL FROM DUAL");
        if (idQuery.exec() && idQuery.next()) {
            m_rfidId = idQuery.value(0).toInt();
            qDebug() << "✅ Card inserted with ID:" << m_rfidId;
        }
        
        qDebug() << "✅ RFID card inserted successfully:" << m_rfidUid;
        return true;
    } else {
        qDebug() << "❌ Failed to insert RFID card:" << query.lastError().text();
        qDebug() << "❌ SQL Error Type:" << query.lastError().type();
        qDebug() << "❌ SQL Driver Text:" << query.lastError().driverText();
        return false;
    }
}

bool RFIDCard::executeUpdate()
{
    qDebug() << "📝 Executing UPDATE for RFID card:" << m_rfidUid;
    qDebug() << "   RFID_ID:" << m_rfidId;
    qDebug() << "   Member CIN:" << m_memberCin;
    qDebug() << "   Status:" << statusToString(m_cardStatus);
    qDebug() << "   Notes:" << m_notes;
    
    if (m_rfidId <= 0) {
        qDebug() << "❌ Cannot update: Invalid RFID_ID" << m_rfidId;
        return false;
    }
    
    QSqlQuery query;
    query.prepare("UPDATE SUMMERCLUB.RFID_CARDS SET "
                  "RFID_UID = :rfid_uid, CIN = :cin, CARD_STATUS = :status, NOTES = :notes, "
                  "UPDATED_DATE = SYSDATE "
                  "WHERE RFID_ID = :rfid_id");
    
    query.bindValue(":rfid_uid", m_rfidUid);
    query.bindValue(":cin", m_memberCin);
    query.bindValue(":status", statusToString(m_cardStatus));
    query.bindValue(":notes", m_notes);
    query.bindValue(":rfid_id", m_rfidId);
    
    qDebug() << "   SQL Parameters:";
    qDebug() << "     RFID_UID:" << m_rfidUid;
    qDebug() << "     CIN:" << m_memberCin;
    qDebug() << "     STATUS:" << statusToString(m_cardStatus);
    qDebug() << "     NOTES:" << m_notes;
    qDebug() << "     RFID_ID:" << m_rfidId;
    
    if (query.exec()) {
        int rowsAffected = query.numRowsAffected();
        qDebug() << "✅ UPDATE executed. Rows affected:" << rowsAffected;
        
        if (rowsAffected > 0) {
            m_updatedDate = QDate::currentDate();
            emit cardStatusChanged(m_rfidUid, statusToString(m_cardStatus));
            qDebug() << "✅ RFID card updated successfully:" << m_rfidUid;
            return true;
        } else {
            qDebug() << "⚠️ No rows were updated - record may not exist with RFID_ID:" << m_rfidId;
            return false;
        }
    } else {
        qDebug() << "❌ Failed to update RFID card:" << query.lastError().text();
        qDebug() << "❌ SQL Error Type:" << query.lastError().type();
        qDebug() << "❌ Driver Text:" << query.lastError().driverText();
        return false;
    }
}