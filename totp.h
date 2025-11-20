#ifndef TOTP_H
#define TOTP_H

#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QMessageAuthenticationCode>
#include <QDebug>

class TOTP
{
public:
    TOTP();
    explicit TOTP(const QByteArray &secret);
    
    // Core TOTP functionality
    QString generateCode(qint64 timeStep = 0) const;
    bool validateCode(const QString &userCode, int windowSize = 1) const;
    
    // Secret key management
    static QByteArray generateSecretKey(int length = 20);
    void setSecret(const QByteArray &secret);
    QByteArray getSecret() const;
    
    // Base32 encoding/decoding for compatibility with authenticator apps
    static QString encodeBase32(const QByteArray &data);
    static QByteArray decodeBase32(const QString &encoded);
    
    // Generate OTP Auth URL for QR codes
    QString generateOTPAuthURL(const QString &accountName, const QString &issuer) const;
    
    // Backup codes generation
    static QStringList generateBackupCodes(int count = 10);
    
    // Constants
    static const int DEFAULT_DIGITS = 6;
    static const int DEFAULT_TIME_STEP = 30; // seconds
    static const int DEFAULT_SECRET_LENGTH = 20; // bytes

private:
    QByteArray m_secret;
    int m_digits;
    int m_timeStep;
    
    // Internal TOTP calculation
    QString calculateTOTP(qint64 timeCounter) const;
    qint64 getCurrentTimeCounter(qint64 timeStep = 0) const;
    
    // HMAC-SHA1 calculation
    QByteArray calculateHMAC(const QByteArray &key, const QByteArray &data) const;
    
    // Dynamic truncation as per RFC 4226
    quint32 dynamicTruncate(const QByteArray &hash) const;
};

#endif // TOTP_H