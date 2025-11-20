#include <QDebug>
#include <QApplication>
#include "totp.h"

void testWithKnownVectors() {
    qDebug() << "\n=== Testing TOTP with RFC 6238 Test Vectors ===";
    
    // RFC 6238 test secret: "12345678901234567890" (20 bytes)
    QByteArray testSecret = QByteArray::fromHex("3132333435363738393031323334353637383930");
    
    TOTP totp(testSecret);
    
    // Test vectors from RFC 6238
    struct TestVector {
        qint64 timestamp;
        QString expectedCode;
    };
    
    QList<TestVector> testVectors = {
        {59, "94287082"},           // 1970-01-01 00:00:59
        {1111111109, "07081804"},   // 2005-03-18 01:58:29
        {1111111111, "14050471"},   // 2005-03-18 01:58:31
        {1234567890, "89005924"},   // 2009-02-13 23:31:30
        {2000000000, "69279037"},   // 2033-05-18 03:33:20
        {20000000000LL, "65353130"} // 2603-10-11 11:33:20
    };
    
    for (const auto& test : testVectors) {
        qint64 timeCounter = test.timestamp / 30;
        QString result = totp.calculateTOTP(timeCounter);
        
        qDebug() << QString("Time: %1, Expected: %2, Got: %3, Match: %4")
                    .arg(test.timestamp)
                    .arg(test.expectedCode)
                    .arg(result)
                    .arg(result == test.expectedCode ? "✅" : "❌");
    }
}

void testCurrentTimeGeneration() {
    qDebug() << "\n=== Testing Current Time Code Generation ===";
    
    TOTP totp;
    
    for (int i = 0; i < 5; i++) {
        QString code = totp.generateCode();
        qint64 currentTime = QDateTime::currentSecsSinceEpoch();
        qint64 timeLeft = 30 - (currentTime % 30);
        
        qDebug() << QString("Generated Code: %1 (expires in %2 seconds)")
                    .arg(code)
                    .arg(timeLeft);
        
        QThread::sleep(1);
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    testWithKnownVectors();
    testCurrentTimeGeneration();
    
    return 0;
}