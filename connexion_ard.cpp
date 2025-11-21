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
    qDebug() << "\n=== Scanning for Arduino Devices ===";
    qDebug() << "Looking for Arduino Uno (VID:9025, PID:67)";
    
    const auto availablePorts = QSerialPortInfo::availablePorts();
    qDebug() << "Available ports found:" << availablePorts.size();
    
    if (availablePorts.isEmpty()) {
        lastError = "No serial ports available";
        qDebug() << lastError;
        emit errorOccurred(lastError);
        return -1;
    }
    
    foreach (const QSerialPortInfo &serial_port_info, availablePorts) {
        qDebug() << "  Port:" << serial_port_info.portName();
        qDebug() << "    Description:" << serial_port_info.description();
        
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            qDebug() << "    VID:" << serial_port_info.vendorIdentifier() 
                    << "PID:" << serial_port_info.productIdentifier();
            
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && 
               serial_port_info.productIdentifier() == arduino_uno_product_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "    >>> ARDUINO FOUND! <<<";
            }
        }
    }
    
    if(!arduino_is_available) {
        lastError = "Arduino device not found on any port";
        qDebug() << lastError;
        emit errorOccurred(lastError);
        return -1;
    }
    
    // Configure serial connection
    qDebug() << "\n=== Configuring Serial Connection ===";
    serial->setPortName(arduino_port_name);
    
    if(serial->open(QSerialPort::ReadWrite)) {
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        
        qDebug() << "Port:" << arduino_port_name << "opened successfully";
        qDebug() << "Baud Rate: 9600, Data Bits: 8, Parity: None, Stop Bits: 1";
        qDebug() << "==================================";
        
        emit connectionStatusChanged(true);
        return 0;
    } else {
        lastError = "Failed to open serial port: " + serial->errorString();
        qDebug() << lastError;
        emit errorOccurred(lastError);
        return 1;
    }
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
    read_from_arduino();
}
