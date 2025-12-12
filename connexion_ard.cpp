#include "connexion_ard.h"

Arduino::Arduino(QObject *parent)
    : QObject(parent),
      serial(nullptr),
      arduino_is_available(false),
      arduino_port_name(""),
      data(""),
      lastError("")
{
    serial = new QSerialPort(this);
    
    // Connect errorOccurred signal (this is the one that emits the error code)
    connect(serial, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::errorOccurred),
            this, &Arduino::onSerialError);
    
    // Connect readyRead signal for asynchronous reading
    connect(serial, &QSerialPort::readyRead,
            this, &Arduino::onDataAvailable);
    
    qDebug() << "Arduino object initialized";
}

int Arduino::connect_arduino() {
    arduino_is_available = false;
    lastError = "";
    
    // Scan for available serial ports
    qDebug() << "\n=== Scanning for Arduino Devices (RFID Reader) ===";
    qDebug() << "Looking for Arduino Uno (VID:9025, PID:67)";
    
    const auto availablePorts = QSerialPortInfo::availablePorts();
    qDebug() << "Available ports found:" << availablePorts.size();
    
    if (availablePorts.isEmpty()) {
        lastError = "No serial ports available";
        qDebug() << lastError;
        emit errorOccurred(lastError);
        return -1;
    }
    
    QStringList foundArduinoPorts;
    QString firstAvailablePort;
    
    foreach (const QSerialPortInfo &serial_port_info, availablePorts) {
        qDebug() << "  Port:" << serial_port_info.portName();
        qDebug() << "    Description:" << serial_port_info.description();
        
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            qDebug() << "    VID:" << serial_port_info.vendorIdentifier() 
                    << "PID:" << serial_port_info.productIdentifier();
            
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && 
               serial_port_info.productIdentifier() == arduino_uno_product_id) {
                foundArduinoPorts.append(serial_port_info.portName());
                if (firstAvailablePort.isEmpty()) {
                    firstAvailablePort = serial_port_info.portName();
                }
                qDebug() << "    >>> ARDUINO DEVICE FOUND! <<<";
            }
        }
    }
    
    if(foundArduinoPorts.isEmpty()) {
        lastError = "Arduino device not found on any port. Please check:\n" 
                   "1. Arduino is connected via USB\n"
                   "2. Arduino drivers are installed\n"
                   "3. USB cable is working properly";
        qDebug() << lastError;
        emit errorOccurred(lastError);
        return -1;
    }
    
    qDebug() << "\n=== Found" << foundArduinoPorts.size() << "Arduino device(s) ===";
    
    // Try to connect to each found Arduino until one works
    for (const QString &portName : foundArduinoPorts) {
        qDebug() << "\n=== Attempting to connect to port:" << portName << "===";
        serial->setPortName(portName);
        
        if(serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            
            arduino_is_available = true;
            arduino_port_name = portName;
            
            qDebug() << "✅ SUCCESS! Port:" << arduino_port_name << "opened successfully";
            qDebug() << "Baud Rate: 9600, Data Bits: 8, Parity: None, Stop Bits: 1";
            qDebug() << "==================================";
            
            emit connectionStatusChanged(true);
            return 0;
        } else {
            QString portError = serial->errorString();
            qDebug() << "⚠️ Could not open port" << portName << "-" << portError;
            
            if (portError.contains("Access is denied") || portError.contains("Permission denied")) {
                qDebug() << "   → Port is likely in use by another application (maybe LCD Arduino?)";
            }
        }
    }
    
    // If we get here, none of the ports could be opened
    lastError = QString("Found %1 Arduino device(s), but could not connect to any.\n\n")
                .arg(foundArduinoPorts.size()) +
                "Possible reasons:\n"
                "• Another Arduino (LCD) is already connected - disconnect it first\n"
                "• Port is in use by another application\n"
                "• Insufficient permissions\n\n"
                "Note: You can only connect to ONE Arduino at a time.\n"
                "If the LCD Arduino is connected, disconnect it before connecting RFID reader.";
    
    qDebug() << "❌" << lastError;
    emit errorOccurred(lastError);
    return 1;
}

int Arduino::close_arduino()
{
    if(serial->isOpen())
    {
        serial->close();
        qDebug() << "Arduino connection closed";
        emit connectionStatusChanged(false);
        return 0;
    }
    lastError = "Serial port not open";
    qDebug() << lastError;
    return 1;
}

Arduino::~Arduino()
{
    if(serial && serial->isOpen())
    {
        serial->close();
        qDebug() << "Arduino destructor: connection closed";
    }
    // serial will be automatically deleted due to parent-child relationship
}

QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable())
    {
        data = serial->readAll();
        if (!data.isEmpty()) {
            qDebug() << "Data received from Arduino:" << data;
            emit dataReceived(data);
        }
        return data;
    }
    return QByteArray();
}

void Arduino::write_to_arduino(QByteArray d)
{
    if(serial->isWritable())
    {
        qint64 bytesWritten = serial->write(d);
        serial->flush();
        qDebug() << "Data sent to Arduino (" << bytesWritten << "bytes):" << d;
    } else {
        lastError = "Serial port not writable";
        qDebug() << lastError;
        emit errorOccurred(lastError);
    }
}

QSerialPort* Arduino::getserial()
{
    return serial;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

bool Arduino::isConnected() const
{
    return serial && serial->isOpen() && arduino_is_available;
}

QString Arduino::getLastError() const
{
    return lastError;
}

void Arduino::onSerialError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        lastError = serial->errorString();
        qDebug() << "Serial Port Error:" << lastError;
        
        if (error == QSerialPort::DeviceNotFoundError ||
            error == QSerialPort::PermissionError ||
            error == QSerialPort::OpenError) {
            emit connectionStatusChanged(false);
        }
        
        emit errorOccurred(lastError);
    }
}

void Arduino::onDataAvailable()
{
    // This slot is called automatically when data is available
    QByteArray receivedData = read_from_arduino();
    
    if (!receivedData.isEmpty()) {
        // Add to buffer instead of processing immediately
        messageBuffer.append(receivedData);
        
        // Process complete messages
        processCompleteMessages();
    }
}

void Arduino::processCompleteMessages()
{
    // Process complete lines (ending with \n)
    while (messageBuffer.contains('\n')) {
        int lineEnd = messageBuffer.indexOf('\n');
        QByteArray completeLine = messageBuffer.left(lineEnd + 1);
        messageBuffer.remove(0, lineEnd + 1);
        
        QString messageStr = QString::fromUtf8(completeLine).trimmed();
        
        // Only log important messages to reduce noise
        if (messageStr.contains("VERIFY:") || 
            messageStr.contains("Card detected! UID:") ||
            messageStr.contains("ACCESS:") ||
            messageStr.contains("System Ready")) {
            qDebug() << "📡 Arduino:" << messageStr;
        }
        
        // Check if this is RFID-related data
        if (isRFIDData(completeLine)) {
            QString rfidUid = extractRFIDFromData(completeLine);
            
            if (!rfidUid.isEmpty()) {
                qDebug() << "🏷️ RFID Card Detected:" << rfidUid;
                emit rfidCardDetected(rfidUid);
                emit rfidVerificationRequest(rfidUid);
            }
        }
    }
    
    // Prevent buffer from growing too large
    if (messageBuffer.size() > 1024) {
        qDebug() << "⚠️ Arduino buffer overflow, clearing...";
        messageBuffer.clear();
    }
}

void Arduino::sendRFIDVerificationRequest(const QString &rfidUid)
{
    if (isConnected()) {
        QString command = "VERIFY:" + rfidUid;
        write_to_arduino(command.toUtf8());
        qDebug() << "Sent RFID verification request:" << command;
    } else {
        qDebug() << "Cannot send RFID request - Arduino not connected";
    }
}

void Arduino::sendAccessResponse(bool granted, const QString &memberName)
{
    if (!isConnected()) {
        qDebug() << "Cannot send access response - Arduino not connected";
        return;
    }
    
    QString response;
    if (granted) {
        response = "ACCESS:GRANTED:" + memberName;
    } else {
        response = "ACCESS:DENIED";
    }
    
    write_to_arduino(response.toUtf8());
    qDebug() << "Sent access response:" << response;
}

bool Arduino::isRFIDData(const QByteArray &data) const
{
    QString dataStr = QString::fromUtf8(data).trimmed();
    
    // Check for RFID UID patterns or verification requests
    return dataStr.startsWith("UID:") || 
           dataStr.startsWith("VERIFY:") || 
           dataStr.contains("Card detected") ||
           (dataStr.contains(" ") && dataStr.length() > 8 && dataStr.length() < 50);
}

QString Arduino::extractRFIDFromData(const QByteArray &data) const
{
    QString dataStr = QString::fromUtf8(data).trimmed();
    
    // Handle different RFID data formats from Arduino
    if (dataStr.startsWith("UID:")) {
        return dataStr.mid(4).trimmed();
    }
    
    if (dataStr.startsWith("VERIFY:")) {
        return dataStr.mid(7).trimmed();
    }
    
    // Check if data looks like a raw UID (hex bytes with spaces)
    QStringList parts = dataStr.split(" ");
    if (parts.length() >= 2 && parts.length() <= 10) {
        bool allHex = true;
        for (const QString &part : parts) {
            if (part.length() != 2) {
                allHex = false;
                break;
            }
            bool ok;
            part.toInt(&ok, 16);
            if (!ok) {
                allHex = false;
                break;
            }
        }
        if (allHex) {
            return dataStr;
        }
    }
    
    return QString();
}
