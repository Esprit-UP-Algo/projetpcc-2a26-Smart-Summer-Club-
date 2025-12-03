#include "rfidmanager.h"

RFIDManager::RFIDManager(QObject *parent)
    : QObject(parent),
      m_rfidService(nullptr),
      m_arduino(nullptr),
      m_isRunning(false)
{
    qDebug() << "🔧 RFIDManager: Creating RFID system components...";
    
    // Create Arduino connection (only if no existing one provided)
    m_arduino = new Arduino(this);
    
    // Create RFID service
    m_rfidService = new RFIDService(this);
    
    // Setup all connections
    setupConnections();
    
    qDebug() << "✅ RFIDManager: Components created and connected";
}

RFIDManager::RFIDManager(Arduino *existingArduino, QObject *parent)
    : QObject(parent),
      m_rfidService(nullptr),
      m_arduino(existingArduino),
      m_isRunning(false)
{
    qDebug() << "🔧 RFIDManager: Using existing Arduino connection...";
    
    // Create RFID service
    m_rfidService = new RFIDService(this);
    
    // Setup all connections
    setupConnections();
    
    qDebug() << "✅ RFIDManager: Connected to existing Arduino";
}

RFIDManager::~RFIDManager()
{
    stopRFIDSystem();
    qDebug() << "🔧 RFIDManager: Destroyed";
}

bool RFIDManager::startRFIDSystem()
{
    qDebug() << "\n🚀 STARTING RFID SYSTEM";
    qDebug() << "========================";
    
    // Connect Arduino if not already connected
    if (!m_arduino->isConnected()) {
        qDebug() << "🔌 Connecting to Arduino...";
        if (m_arduino->connect_arduino() != 0) {
            qDebug() << "❌ Failed to connect to Arduino";
            return false;
        }
        qDebug() << "✅ Arduino connected on port:" << m_arduino->getarduino_port_name();
    } else {
        qDebug() << "✅ Using existing Arduino connection on port:" << m_arduino->getarduino_port_name();
    }
    
    // Initialize RFID service
    qDebug() << "🛡️ Initializing RFID service...";
    if (!m_rfidService->initializeService()) {
        qDebug() << "❌ Failed to initialize RFID service";
        return false;
    }
    qDebug() << "✅ RFID service initialized";
    
    // Set Arduino connection in RFID service
    m_rfidService->setArduinoConnection(m_arduino);
    
    // Start listening
    qDebug() << "👂 Starting RFID listening...";
    m_rfidService->startListening();
    
    m_isRunning = true;
    
    qDebug() << "✅ RFID SYSTEM IS NOW ACTIVE!";
    qDebug() << "💳 Present your RFID cards to test access...";
    qDebug() << "========================\n";
    
    return true;
}

void RFIDManager::stopRFIDSystem()
{
    if (!m_isRunning) return;
    
    qDebug() << "⏹️ Stopping RFID system...";
    
    if (m_rfidService) {
        m_rfidService->stopListening();
    }
    
    m_isRunning = false;
    qDebug() << "✅ RFID system stopped";
}

bool RFIDManager::isRunning() const
{
    return m_isRunning;
}

void RFIDManager::setupConnections()
{
    qDebug() << "🔗 Setting up RFID connections...";
    
    // Connect Arduino data to RFID service
    connect(m_arduino, &Arduino::dataReceived,
            m_rfidService, &RFIDService::onRFIDDataReceived);
    
    connect(m_arduino, &Arduino::rfidCardDetected,
            m_rfidService, &RFIDService::onRFIDCardDetected);
    
    // Connect RFID service signals to manager
    connect(m_rfidService, &RFIDService::accessAttempt,
            this, &RFIDManager::onAccessAttempt);
    
    connect(m_rfidService, &RFIDService::errorOccurred,
            this, &RFIDManager::onRFIDError);
    
    connect(m_rfidService, &RFIDService::debugMessage,
            this, &RFIDManager::onRFIDDebug);
    
    qDebug() << "✅ RFID connections established";
}

void RFIDManager::onAccessAttempt(const QString &rfidUid, bool granted, const QString &memberName)
{
    qDebug() << "\n🎯 =========================";
    qDebug() << "    ACCESS ATTEMPT RESULT";
    qDebug() << "🎯 =========================";
    qDebug() << "📱 Card UID:" << rfidUid;
    qDebug() << "🔐 Result:" << (granted ? "✅ ACCESS GRANTED" : "❌ ACCESS DENIED");
    qDebug() << "👤 Member:" << (memberName.isEmpty() ? "Unknown" : memberName);
    qDebug() << "🎯 =========================\n";
    
    if (granted) {
        emit accessGranted(memberName, rfidUid);
    } else {
        emit accessDenied(rfidUid, "Access denied");
    }
}

void RFIDManager::onRFIDError(const QString &error)
{
    qDebug() << "🚨 RFID Error:" << error;
}

void RFIDManager::onRFIDDebug(const QString &message)
{
    qDebug() << "🔍 RFID:" << message;
}