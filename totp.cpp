#include "totp.h"
#include <QRandomGenerator>
#include <QUrl>
#include <QtEndian>
#include <QDebug>
#include <cmath>

TOTP::TOTP()
    : m_digits(DEFAULT_DIGITS)
    , m_timeStep(DEFAULT_TIME_STEP)
{
    // Generate a random secret if none provided
    m_secret = generateSecretKey();
}

TOTP::TOTP(const QByteArray &secret)
    : m_secret(secret)
    , m_digits(DEFAULT_DIGITS)
    , m_timeStep(DEFAULT_TIME_STEP)
{
}

QString TOTP::generateCode(qint64 timeStep) const
{
    if (m_secret.isEmpty()) {
        qWarning() << "TOTP: No secret key set";
        return QString();
    }
    
    qint64 timeCounter = getCurrentTimeCounter(timeStep);
    return calculateTOTP(timeCounter);
}

bool TOTP::validateCode(const QString &userCode, int windowSize) const
{
    if (userCode.length() != m_digits || m_secret.isEmpty()) {
        return false;
    }
    
    qint64 currentTime = getCurrentTimeCounter();
    
    // Check current time window and adjacent windows (±windowSize)
    for (int i = -windowSize; i <= windowSize; ++i) {
        qint64 testTimeCounter = currentTime + i;
        QString expectedCode = calculateTOTP(testTimeCounter);
        
        if (userCode == expectedCode) {
            return true;
        }
    }
    
    return false;
}

QByteArray TOTP::generateSecretKey(int length)
{
    QByteArray secret;
    secret.reserve(length);
    
    QRandomGenerator *rng = QRandomGenerator::system();
    for (int i = 0; i < length; ++i) {
        secret.append(static_cast<char>(rng->bounded(256)));
    }
    
    qDebug() << "Generated secret (hex):" << secret.toHex();
    qDebug() << "Generated secret (base32):" << encodeBase32(secret);
    
    return secret;
}

void TOTP::setSecret(const QByteArray &secret)
{
    m_secret = secret;
}

QByteArray TOTP::getSecret() const
{
    return m_secret;
}

QString TOTP::encodeBase32(const QByteArray &data)
{
    const QString base32Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    QString result;
    
    int bits = 0;
    int value = 0;
    
    for (char byte : data) {
        value = (value << 8) | (static_cast<unsigned char>(byte));
        bits += 8;
        
        while (bits >= 5) {
            result.append(base32Chars[(value >> (bits - 5)) & 31]);
            bits -= 5;
        }
    }
    
    if (bits > 0) {
        result.append(base32Chars[(value << (5 - bits)) & 31]);
    }
    
    // Add padding
    while (result.length() % 8 != 0) {
        result.append('=');
    }
    
    return result;
}

QByteArray TOTP::decodeBase32(const QString &encoded)
{
    const QString base32Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    QByteArray result;
    
    int bits = 0;
    int value = 0;
    
    for (QChar c : encoded) {
        if (c == '=') {
            break; // Padding
        }
        
        int index = base32Chars.indexOf(c.toUpper());
        if (index == -1) {
            continue; // Invalid character, skip
        }
        
        value = (value << 5) | index;
        bits += 5;
        
        if (bits >= 8) {
            result.append(static_cast<char>((value >> (bits - 8)) & 255));
            bits -= 8;
        }
    }
    
    return result;
}

QString TOTP::generateOTPAuthURL(const QString &accountName, const QString &issuer) const
{
    QString base32Secret = encodeBase32(m_secret);
    
    QString url = QString("otpauth://totp/%1:%2?secret=%3&issuer=%4&digits=%5&period=%6")
                  .arg(QUrl::toPercentEncoding(issuer))
                  .arg(QUrl::toPercentEncoding(accountName))
                  .arg(base32Secret)
                  .arg(QUrl::toPercentEncoding(issuer))
                  .arg(m_digits)
                  .arg(m_timeStep);
    
    return url;
}

QStringList TOTP::generateBackupCodes(int count)
{
    QStringList codes;
    QRandomGenerator *rng = QRandomGenerator::system();
    
    for (int i = 0; i < count; ++i) {
        // Generate 8-digit backup codes
        QString code = QString("%1").arg(rng->bounded(10000000, 99999999));
        codes.append(code);
    }
    
    return codes;
}

QString TOTP::calculateTOTP(qint64 timeCounter) const
{
    // Debug output
    qDebug() << "=== TOTP Calculation Debug ===";
    qDebug() << "Time Counter:" << timeCounter;
    qDebug() << "Secret length:" << m_secret.length();
    
    // Convert time counter to 8-byte big-endian
    QByteArray timeBytes(8, 0);
    qToBigEndian(static_cast<quint64>(timeCounter), timeBytes.data());
    
    qDebug() << "Time bytes (hex):" << timeBytes.toHex();
    
    // Calculate HMAC-SHA1
    QByteArray hash = calculateHMAC(m_secret, timeBytes);
    qDebug() << "HMAC hash (hex):" << hash.toHex();
    
    // Dynamic truncation
    quint32 code = dynamicTruncate(hash);
    qDebug() << "After truncation:" << code;
    
    // Generate final code with specified number of digits
    code %= static_cast<quint32>(std::pow(10, m_digits));
    qDebug() << "Final code (numeric):" << code;
    
    // Format with leading zeros
    QString result = QString("%1").arg(code, m_digits, 10, QChar('0'));
    qDebug() << "Final code (formatted):" << result;
    qDebug() << "=== End TOTP Debug ===";
    
    return result;
}

qint64 TOTP::getCurrentTimeCounter(qint64 timeStep) const
{
    qint64 currentTime = QDateTime::currentSecsSinceEpoch();
    if (timeStep != 0) {
        currentTime = timeStep;
    }
    return currentTime / m_timeStep;
}

QByteArray TOTP::calculateHMAC(const QByteArray &key, const QByteArray &data) const
{
    return QMessageAuthenticationCode::hash(data, key, QCryptographicHash::Sha1);
}

quint32 TOTP::dynamicTruncate(const QByteArray &hash) const
{
    // Get the last 4 bits of the hash as offset
    int offset = hash.at(hash.length() - 1) & 0x0F;
    
    // Extract 4 bytes starting from offset
    quint32 code = ((hash.at(offset) & 0x7F) << 24) |
                   ((hash.at(offset + 1) & 0xFF) << 16) |
                   ((hash.at(offset + 2) & 0xFF) << 8) |
                   (hash.at(offset + 3) & 0xFF);
    
    return code;
}