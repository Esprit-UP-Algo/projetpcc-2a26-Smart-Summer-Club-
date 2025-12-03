#ifndef RFIDCARD_H
#define RFIDCARD_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

class RFIDCard : public QObject
{
    Q_OBJECT

public:
    // Card status enum
    enum CardStatus {
        Active,
        Disabled,
        Lost,
        Expired
    };

    // Constructors
    RFIDCard(QObject *parent = nullptr);
    RFIDCard(const QString &rfidUid, const QString &memberCin, 
             CardStatus status = Active, const QString &notes = "", 
             QObject *parent = nullptr);
    
    // Getters
    int getRfidId() const;
    QString getRfidUid() const;
    QString getMemberCin() const;
    CardStatus getCardStatus() const;
    QDate getIssuedDate() const;
    QDateTime getLastUsed() const;
    QString getNotes() const;
    QDate getCreatedDate() const;
    QDate getUpdatedDate() const;
    
    // Setters
    void setRfidUid(const QString &rfidUid);
    void setMemberCin(const QString &memberCin);
    void setCardStatus(CardStatus status);
    void setNotes(const QString &notes);
    
    // CRUD Operations
    bool save();  // Create or Update
    bool remove();  // Delete
    bool load(const QString &rfidUid);  // Load by RFID UID
    bool load(int rfidId);  // Load by ID
    
    // Static methods for database operations
    static QSqlQueryModel* getAllCards();
    static QSqlQueryModel* getCardsByMember(const QString &memberCin);
    static QSqlQueryModel* getCardsByStatus(CardStatus status);
    static RFIDCard* findByUid(const QString &rfidUid);
    static RFIDCard* findByMember(const QString &memberCin);
    static bool deleteByUid(const QString &rfidUid);
    static bool isUidExists(const QString &rfidUid);
    static int getActiveCardCount(const QString &memberCin);
    
    // Utility methods
    static QString statusToString(CardStatus status);
    static CardStatus stringToStatus(const QString &statusStr);
    bool updateLastUsed();
    bool isValid() const;
    
    // Validation
    static bool validateRfidUid(const QString &rfidUid);
    
    // Statistics
    static int getTotalActiveCards();
    static int getTotalCardsByStatus(CardStatus status);
    static QSqlQueryModel* getRecentlyUsedCards(int days = 30);
    static QSqlQueryModel* getUnusedCards(int days = 30);

signals:
    void cardSaved(const QString &rfidUid);
    void cardRemoved(const QString &rfidUid);
    void cardStatusChanged(const QString &rfidUid, const QString &newStatus);
    void cardUsed(const QString &rfidUid, const QString &memberCin);

private:
    // Member variables
    int m_rfidId;
    QString m_rfidUid;
    QString m_memberCin;
    CardStatus m_cardStatus;
    QDate m_issuedDate;
    QDateTime m_lastUsed;
    QString m_notes;
    QDate m_createdDate;
    QDate m_updatedDate;
    
    bool m_isNewRecord;
    
    // Helper methods
    void initializeDefaults();
    bool validateData() const;
    bool executeInsert();
    bool executeUpdate();
};

#endif // RFIDCARD_H