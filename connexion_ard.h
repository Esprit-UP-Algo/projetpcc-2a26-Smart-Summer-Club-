#ifndef ARDUINO_CANDIDAT_H
#define ARDUINO_CANDIDAT_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QObject>

class Arduino : public QObject
{
    Q_OBJECT

public:
    Arduino(QObject *parent = nullptr);
    ~Arduino();
    
    int connect_arduino();
    int close_arduino();
    void write_to_arduino(QByteArray);
    QByteArray read_from_arduino();
    QSerialPort* getserial();
    QString getarduino_port_name();
    bool isConnected() const;
    QString getLastError() const;

    // RFID-specific methods
    void sendRFIDVerificationRequest(const QString &rfidUid);
    void sendAccessResponse(bool granted, const QString &memberName = "");
    bool isRFIDData(const QByteArray &data) const;
    QString extractRFIDFromData(const QByteArray &data) const;

private slots:
    void onSerialError(QSerialPort::SerialPortError error);
    void onDataAvailable();

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    bool arduino_is_available;
    QString arduino_port_name;
    QByteArray data;
    QString lastError;
    
    // Message buffering for fragmented data
    QByteArray messageBuffer;
    void processCompleteMessages();

signals:
    void connectionStatusChanged(bool connected);
    void dataReceived(QByteArray data);
    void errorOccurred(QString errorMessage);
    
    // RFID-specific signals
    void rfidCardDetected(QString rfidUid);
    void rfidVerificationRequest(QString rfidUid);
};

#endif // ARDUINO_CANDIDAT_H
