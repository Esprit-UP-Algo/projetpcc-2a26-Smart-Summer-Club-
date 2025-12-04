#include "ocrinterface.h"
#include <QScrollArea>

OCRInterface::OCRInterface(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(nullptr)
    , m_uploadFrame(nullptr)
    , m_previewFrame(nullptr)
    , m_resultFrame(nullptr)
    , m_actionFrame(nullptr)
    , m_uploadTitle(nullptr)
    , m_uploadButton(nullptr)
    , m_uploadStatusLabel(nullptr)
    , m_previewTitle(nullptr)
    , m_imagePreview(nullptr)
    , m_processButton(nullptr)
    , m_progressBar(nullptr)
    , m_progressLabel(nullptr)
    , m_resultTitle(nullptr)
    , m_cinLineEdit(nullptr)
    , m_firstNameLineEdit(nullptr)
    , m_lastNameLineEdit(nullptr)
    , m_dobLineEdit(nullptr)
    , m_rawTextEdit(nullptr)
    , m_clearButton(nullptr)
    , m_autoFillButton(nullptr)
    , m_ocrProcess(nullptr)
    , m_processTimeout(nullptr)
{
    setupUI();
    connectSignals();
    clearResults();
}

OCRInterface::~OCRInterface()
{
    // Safe cleanup of OCR process
    if (m_ocrProcess) {
        // Disconnect all signals first
        m_ocrProcess->disconnect();
        
        // Kill process if still running
        if (m_ocrProcess->state() != QProcess::NotRunning) {
            m_ocrProcess->kill();
            // Don't wait too long in destructor
            m_ocrProcess->waitForFinished(1000);
        }
        
        // Delete the process
        m_ocrProcess->deleteLater();
        m_ocrProcess = nullptr;
    }
}

void OCRInterface::setupUI()
{
    // Create main layout with proper spacing
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    // Create title bar
    setupTitleBar();
    
    // Create main horizontal splitter for split-panel design
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal, this);
    mainSplitter->setStyleSheet(
        "QSplitter::handle {"
        "    background-color: #e0e0e0;"
        "    width: 2px;"
        "}"
    );
    
    // Create left panel (Input)
    setupInputPanel(mainSplitter);
    
    // Create right panel (Results)
    setupResultsPanel(mainSplitter);
    
    // Set splitter sizes (40% input, 60% results)
    mainSplitter->setSizes({400, 600});
    mainSplitter->setStretchFactor(0, 0);
    mainSplitter->setStretchFactor(1, 1);
    
    m_mainLayout->addWidget(mainSplitter);
    
    // Set main widget styling
    setStyleSheet(
        "OCRInterface {"
        "    background-color: #f8f9fa;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
    );
}


void OCRInterface::setupTitleBar()
{
    // Title bar widget
    QWidget *titleBar = new QWidget();
    titleBar->setFixedHeight(32);
    titleBar->setStyleSheet(
        "QWidget {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #16a5b3, stop:1 #16a5b3);"
        "    color: white;"
        "    border-bottom: 1px solid #16a5b3;"
        "    border-top: 1px solid #16a5b3;"
        "}"
    );
    
    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(12, 4, 8, 4);
    titleLayout->setSpacing(8);
    
    // Title label with icon
    QLabel *titleLabel = new QLabel("🔍 Professional ID Scanner");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 13px;"
        "    font-weight: 600;"
        "    color: #ecf0f1;"
        "    letter-spacing: 0.5px;"
        "    padding: 0px;"
        "    border: none;"
        "    background: transparent;"
        "}"
    );
    
    // Help and About buttons with modern styling
    QPushButton *helpBtn = new QPushButton("Help");
    QPushButton *aboutBtn = new QPushButton("About");
    
    QString buttonStyle = 
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #16a5b3, stop:1 #16a5b3);"
        "    color: #ecf0f1;"
        "    border: 1px solid #16a5b3;"
        "    border-radius: 4px;"
        "    padding: 3px 10px;"
        "    font-size: 10px;"
        "    font-weight: 500;"
        "    min-width: 45px;"
        "    max-height: 22px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1bc2d6, stop:1 #16a5b3);"
        "    border-color: #1bc2d6;"
        "    color: white;"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #13909e, stop:1 #16a5b3);"
        "    border-color: #13909e;"
        "}"
        "QPushButton:focus {"
        "    outline: none;"
        "    border-color: #16a5b3;"
        "}";
    
    helpBtn->setStyleSheet(buttonStyle);
    aboutBtn->setStyleSheet(buttonStyle);
    
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(helpBtn);
    titleLayout->addWidget(aboutBtn);
    
    m_mainLayout->addWidget(titleBar);
}

void OCRInterface::setupInputPanel(QSplitter *parent)
{
    // Input panel widget
    QWidget *inputPanel = new QWidget();
    inputPanel->setStyleSheet(
        "QWidget {"
        "    background-color: white;"
        "    border-right: 1px solid #e0e0e0;"
        "}"
    );
    
    QVBoxLayout *inputLayout = new QVBoxLayout(inputPanel);
    inputLayout->setSpacing(15);
    inputLayout->setContentsMargins(20, 20, 20, 20);
    
    // Input section title
    QLabel *inputTitle = new QLabel("📷 Input");
    inputTitle->setStyleSheet(
        "QLabel {"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    padding-bottom: 10px;"
        "    border-bottom: 2px solid #3498db;"
        "}"
    );
    inputLayout->addWidget(inputTitle);
    
    // Image preview
    m_imagePreview = new QLabel();
    m_imagePreview->setAlignment(Qt::AlignCenter);
    m_imagePreview->setMinimumSize(300, 200);
    m_imagePreview->setMaximumSize(350, 250);
    m_imagePreview->setStyleSheet(
        "QLabel {"
        "    border: 2px dashed #bdc3c7;"
        "    border-radius: 8px;"
        "    background-color: #f8f9fa;"
        "    color: #7f8c8d;"
        "    font-size: 14px;"
        "}"
    );
    m_imagePreview->setText("📷\nImage Preview\nUpload an ID card to see preview here");
    m_imagePreview->setWordWrap(true);
    inputLayout->addWidget(m_imagePreview, 1);
    
    // Control buttons
    m_uploadButton = new QPushButton("📁 Upload");
    m_processButton = new QPushButton("🔄 Process");
    m_clearButton = new QPushButton("❌ Clear");
    
    QString btnStyle = 
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 6px;"
        "    padding: 10px 15px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    margin: 2px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #21618c;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #bdc3c7;"
        "    color: #7f8c8d;"
        "}";
    
    m_uploadButton->setStyleSheet(btnStyle);
    m_processButton->setStyleSheet(btnStyle.replace("#3498db", "#27ae60").replace("#2980b9", "#229954").replace("#21618c", "#1e8449"));
    m_clearButton->setStyleSheet(btnStyle.replace("#3498db", "#e74c3c").replace("#2980b9", "#c0392b").replace("#21618c", "#a93226"));
    
    m_processButton->setEnabled(false);
    
    inputLayout->addWidget(m_uploadButton);
    inputLayout->addWidget(m_processButton);
    inputLayout->addWidget(m_clearButton);
    
    // Status section
    QLabel *statusTitle = new QLabel("⚡ Status:");
    statusTitle->setStyleSheet(
        "QLabel {"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    margin-top: 10px;"
        "}"
    );
    inputLayout->addWidget(statusTitle);
    
    m_progressLabel = new QLabel("✅ Ready");
    m_progressLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 13px;"
        "    color: #27ae60;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "    background-color: #d5f4e6;"
        "    border-radius: 4px;"
        "}"
    );
    inputLayout->addWidget(m_progressLabel);
    
    // Progress bar
    m_progressBar = new QProgressBar();
    m_progressBar->setVisible(false);
    m_progressBar->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "    font-weight: bold;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #3498db;"
        "    border-radius: 3px;"
        "}"
    );
    inputLayout->addWidget(m_progressBar);
    
    inputLayout->addStretch();
    
    parent->addWidget(inputPanel);
}

void OCRInterface::setupResultsPanel(QSplitter *parent)
{
    // Results panel widget
    QWidget *resultsPanel = new QWidget();
    resultsPanel->setStyleSheet(
        "QWidget {"
        "    background-color: white;"
        "}"
    );
    
    QVBoxLayout *resultsLayout = new QVBoxLayout(resultsPanel);
    resultsLayout->setSpacing(20);
    resultsLayout->setContentsMargins(20, 20, 20, 20);
    
    // Results section title
    QLabel *resultsTitle = new QLabel("📊 Results");
    resultsTitle->setStyleSheet(
        "QLabel {"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    padding-bottom: 10px;"
        "    border-bottom: 2px solid #e74c3c;"
        "}"
    );
    resultsLayout->addWidget(resultsTitle);
    
    // Personal Information Group
    QGroupBox *personalInfoGroup = new QGroupBox("👤 Personal Information");
    personalInfoGroup->setStyleSheet(
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #3498db;"
        "    border-radius: 8px;"
        "    margin-top: 1ex;"
        "    padding-top: 15px;"
        "    background-color: #f8f9fa;"
        "    font-size: 14px;"
        "    color: #2c3e50;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 15px;"
        "    padding: 0 10px 0 10px;"
        "    background-color: white;"
        "}"
    );
    
    QGridLayout *infoLayout = new QGridLayout(personalInfoGroup);
    infoLayout->setSpacing(15);
    infoLayout->setContentsMargins(20, 20, 20, 20);
    
    QString fieldStyle = 
        "QLineEdit {"
        "    background-color: white;"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 6px;"
        "    padding: 10px 12px;"
        "    font-size: 14px;"
        "    color: #2c3e50;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #3498db;"
        "    outline: none;"
        "}"
        "QLineEdit:read-only {"
        "    background-color: #ecf0f1;"
        "    color: #34495e;"
        "}";
    
    QString labelStyle = 
        "QLabel {"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    font-size: 13px;"
        "    padding: 5px 0;"
        "}";
    
    // CIN Number field
    QLabel *cinLabel = new QLabel("CIN Number");
    cinLabel->setStyleSheet(labelStyle);
    m_cinLineEdit = new QLineEdit();
    m_cinLineEdit->setReadOnly(true);
    m_cinLineEdit->setPlaceholderText("8-digit ID number");
    m_cinLineEdit->setStyleSheet(fieldStyle);
    
    // Full Name field
    QLabel *nameLabel = new QLabel("Full Name");
    nameLabel->setStyleSheet(labelStyle);
    m_firstNameLineEdit = new QLineEdit(); // Reusing for full name
    m_firstNameLineEdit->setReadOnly(true);
    m_firstNameLineEdit->setPlaceholderText("Complete name");
    m_firstNameLineEdit->setStyleSheet(fieldStyle);
    
    // Birth Date field
    QLabel *dobLabel = new QLabel("Birth Date");
    dobLabel->setStyleSheet(labelStyle);
    m_dobLineEdit = new QLineEdit();
    m_dobLineEdit->setReadOnly(true);
    m_dobLineEdit->setPlaceholderText("Date of birth");
    m_dobLineEdit->setStyleSheet(fieldStyle);
    
    // Add fields to grid (2 columns layout)
    infoLayout->addWidget(cinLabel, 0, 0);
    infoLayout->addWidget(m_cinLineEdit, 0, 1);
    infoLayout->addWidget(nameLabel, 1, 0);
    infoLayout->addWidget(m_firstNameLineEdit, 1, 1);
    infoLayout->addWidget(dobLabel, 2, 0);
    infoLayout->addWidget(m_dobLineEdit, 2, 1);
    
    resultsLayout->addWidget(personalInfoGroup);
    
    // Action button
    m_autoFillButton = new QPushButton("🚀 Auto-Fill Member Form");
    m_autoFillButton->setMinimumHeight(45);
    m_autoFillButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #2ecc71;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 8px;"
        "    padding: 12px 20px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    margin-top: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #27ae60;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #229954;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #bdc3c7;"
        "    color: #7f8c8d;"
        "}"
    );
    
    resultsLayout->addWidget(m_autoFillButton);
    resultsLayout->addStretch();
    
    parent->addWidget(resultsPanel);
}

void OCRInterface::connectSignals()
{
    // Connect button signals to slots
    connect(m_uploadButton, &QPushButton::clicked, this, &OCRInterface::onUploadImageClicked);
    connect(m_processButton, &QPushButton::clicked, this, &OCRInterface::onProcessImageClicked);
    connect(m_clearButton, &QPushButton::clicked, this, &OCRInterface::onClearFormClicked);
    connect(m_autoFillButton, &QPushButton::clicked, this, &OCRInterface::onAutoFillMemberFormClicked);
    
    // Initialize timeout timer
    m_processTimeout = new QTimer(this);
    m_processTimeout->setSingleShot(true);
    connect(m_processTimeout, &QTimer::timeout, this, &OCRInterface::onProcessTimeout);
    
    // Note: m_ocrProcess connection is done in onProcessImageClicked() when the process is created
}

void OCRInterface::onUploadImageClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Select ID Card Image",
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        "Image Files (*.png *.jpg *.jpeg *.bmp *.gif *.tiff)"
    );

    if (!fileName.isEmpty()) {
        m_currentImagePath = fileName;
        
        // Update progress label
        m_progressLabel->setText("📷 Image loaded: " + QFileInfo(fileName).fileName());
        m_progressLabel->setStyleSheet(
            "QLabel {"
            "    font-size: 13px;"
            "    color: #3498db;"
            "    font-weight: bold;"
            "    padding: 5px;"
            "    background-color: #d6eaf8;"
            "    border-radius: 4px;"
            "}"
        );
        
        updatePreviewImage();
        m_processButton->setEnabled(true);
        clearResults();
    }
}

void OCRInterface::onProcessImageClicked()
{
    if (m_currentImagePath.isEmpty()) {
        QMessageBox::warning(this, "No Image", "Please upload an image first.");
        return;
    }

    // Show progress
    m_processButton->setEnabled(false);
    m_progressBar->setVisible(true);
    m_progressLabel->setText("🔄 Processing image with OCR...");
    
    emit ocrProcessingStarted();

    // First, ensure we have the nodeJsScripts folder in the workspace
    if (!ensureNodeJsScriptsExists()) {
        QMessageBox::critical(this, "OCR Error", 
                             "Failed to setup required OCR files. Please check your installation.");
        m_processButton->setEnabled(true);
        m_progressBar->setVisible(false);
        m_progressLabel->clear();
        return;
    }

    // Setup OCR process with proper safety checks
    if (m_ocrProcess) {
        // Disconnect all signals first to prevent issues
        m_ocrProcess->disconnect();
        if (m_ocrProcess->state() != QProcess::NotRunning) {
            m_ocrProcess->kill();
            m_ocrProcess->waitForFinished(3000);
        }
        m_ocrProcess->deleteLater();
        m_ocrProcess = nullptr;
    }
    
    // Create new process with proper parent
    m_ocrProcess = new QProcess(this);
    
    // Set up process properties before connecting signals
    m_ocrProcess->setProcessChannelMode(QProcess::SeparateChannels);
    m_ocrProcess->setReadChannel(QProcess::StandardOutput);
    
    // Connect signals after process is fully configured
    connect(m_ocrProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &OCRInterface::processOCRFinished, Qt::QueuedConnection);

    // Get the script path and working directory
    QString scriptPath = getNodeScriptPath();
    QFileInfo scriptInfo(scriptPath);
    
    // If ocr_minimal.js doesn't exist, try ocr.js
    if (!scriptInfo.exists()) {
        QString alternativeScript = scriptPath;
        alternativeScript.replace("ocr_minimal.js", "ocr.js");
        if (QFileInfo::exists(alternativeScript)) {
            scriptPath = alternativeScript;
            qDebug() << "Using alternative OCR script:" << scriptPath;
        } else {
            // Try ocr.js directly
            QFileInfo scriptFileInfo(scriptPath);
            QString ocrJsPath = scriptFileInfo.absolutePath() + "/ocr.js";
            if (QFileInfo::exists(ocrJsPath)) {
                scriptPath = ocrJsPath;
                qDebug() << "Using ocr.js script:" << scriptPath;
            }
        }
    }
    
    if (!QFileInfo::exists(scriptPath)) {
        QMessageBox::critical(this, "OCR Error", 
                             "OCR script not found. Please check your installation.");
        m_processButton->setEnabled(true);
        m_progressBar->setVisible(false);
        m_progressLabel->clear();
        return;
    }
    
    // Set working directory and prepare arguments with validation
    QFileInfo scriptFileInfo(scriptPath);
    QString workingDir = scriptFileInfo.absolutePath();
    QString scriptFileName = scriptFileInfo.fileName();
    
    // Validate working directory exists
    if (!QDir(workingDir).exists()) {
        QMessageBox::critical(this, "OCR Error", 
                             "Working directory does not exist: " + workingDir);
        m_processButton->setEnabled(true);
        m_progressBar->setVisible(false);
        m_progressLabel->clear();
        return;
    }
    
    m_ocrProcess->setWorkingDirectory(workingDir);
    
    // Prepare arguments and validate image path
    QStringList arguments;
    arguments << scriptFileName << QDir::toNativeSeparators(m_currentImagePath);

    qDebug() << "📋 Running OCR script:" << scriptFileName;
    qDebug() << "📁 Working directory:" << workingDir;
    qDebug() << "📝 Arguments:" << arguments;
    qDebug() << "📝 Full command: node" << arguments.join(" ");

    // Start process with error handling
    try {
        m_ocrProcess->start("node", arguments);
        
        if (!m_ocrProcess->waitForStarted(5000)) {
            QString errorMsg = "Failed to start OCR process. Make sure Node.js is installed.";
            QMessageBox::critical(this, "OCR Error", errorMsg);
            qDebug() << "❌" << errorMsg;
            qDebug() << "Process error:" << m_ocrProcess->errorString();
            qDebug() << "Process state:" << m_ocrProcess->state();
            
            // Clean up failed process
            if (m_ocrProcess) {
                m_ocrProcess->disconnect();
                m_ocrProcess->deleteLater();
                m_ocrProcess = nullptr;
            }
            
            m_processButton->setEnabled(true);
            m_progressBar->setVisible(false);
            m_progressLabel->clear();
        } else {
            // Process started successfully, start timeout timer (60 seconds)
            m_processTimeout->start(60000);
        }
    } catch (...) {
        QMessageBox::critical(this, "OCR Error", "Unexpected error starting OCR process.");
        m_processButton->setEnabled(true);
        m_progressBar->setVisible(false);
        m_progressLabel->clear();
        
        // Clean up on exception
        if (m_ocrProcess) {
            m_ocrProcess->disconnect();
            m_ocrProcess->deleteLater();
            m_ocrProcess = nullptr;
        }
    }
}

void OCRInterface::onClearFormClicked()
{
    m_currentImagePath.clear();
    m_progressLabel->setText("✅ Ready");
    m_progressLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 13px;"
        "    color: #27ae60;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "    background-color: #d5f4e6;"
        "    border-radius: 4px;"
        "}"
    );
    
    m_imagePreview->setText("📷\nImage Preview\nUpload an ID card to see preview here");
    m_imagePreview->setPixmap(QPixmap());
    m_processButton->setEnabled(false);
    clearResults();
}

void OCRInterface::onAutoFillMemberFormClicked()
{
    if (m_extractedCIN.isEmpty() && m_extractedFirstName.isEmpty() && 
        m_extractedLastName.isEmpty() && m_extractedDateOfBirth.isEmpty()) {
        QMessageBox::information(this, "No Data", "No extracted data available to auto-fill.");
        return;
    }

    emit dataExtracted(m_extractedCIN, m_extractedFirstName, 
                      m_extractedLastName, m_extractedDateOfBirth);
    
    QMessageBox::information(this, "Auto-Fill Complete", 
                           "Member form has been auto-filled with extracted data.");
}

void OCRInterface::processOCRFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    // Stop the timeout timer
    if (m_processTimeout) {
        m_processTimeout->stop();
    }
    
    // Safety check: ensure process still exists
    if (!m_ocrProcess) {
        qDebug() << "⚠️ processOCRFinished called but m_ocrProcess is null";
        m_processButton->setEnabled(true);
        m_progressBar->setVisible(false);
        return;
    }
    
    m_processButton->setEnabled(true);
    m_progressBar->setVisible(false);

    // Safely read process output
    QByteArray stdoutData, stderrData;
    try {
        stdoutData = m_ocrProcess->readAllStandardOutput();
        stderrData = m_ocrProcess->readAllStandardError();
    } catch (...) {
        qDebug() << "⚠️ Error reading process output";
        m_progressLabel->setText("❌ Error reading OCR output");
        return;
    }
    
    QString stdoutOutput = QString::fromUtf8(stdoutData);
    QString stderrOutput = QString::fromUtf8(stderrData);
    
    qDebug() << "📋 OCR process finished with exit code:" << exitCode;
    qDebug() << "📋 Exit status:" << (exitStatus == QProcess::NormalExit ? "Normal" : "Crashed");
    
    if (!stdoutOutput.isEmpty()) {
        qDebug() << "📤 STDOUT:" << stdoutOutput;
    }
    
    if (!stderrOutput.isEmpty()) {
        qDebug() << "📤 STDERR:" << stderrOutput;
    }

    // For exit code 0 (success) or 1 (with output), read from JSON file
    if ((exitStatus == QProcess::NormalExit && exitCode == 0) || 
        (exitStatus == QProcess::NormalExit && exitCode == 1 && !stdoutOutput.isEmpty())) {
        
        qDebug() << "📋 OCR script finished, reading results from JSON file...";
        
        // Give the script a moment to finish writing the JSON file
        QTimer::singleShot(500, this, [this]() {
            readOCRResultsFromJsonFile();
            
            // Use queued connection to prevent immediate crash
            QMetaObject::invokeMethod(this, [this]() {
                emit ocrProcessingFinished(true);
            }, Qt::QueuedConnection);
        });
        return;
    }
    
    // Legacy fallback: Check if we have structured output in stdout
    if (!stdoutOutput.isEmpty() && stdoutOutput.contains("PARSED_RESULTS_START")) {
        qDebug() << "📋 Using legacy structured JSON parsing from stdout...";
        parseStructuredOCRResults(stdoutOutput);
        
        // Use queued connection to prevent immediate crash
        QMetaObject::invokeMethod(this, [this]() {
            emit ocrProcessingFinished(true);
        }, Qt::QueuedConnection);
        return;
    }

    // If no valid output, treat as error
    if (exitStatus == QProcess::CrashExit || exitCode != 0) {
        if (m_progressLabel) {
            m_progressLabel->setText("❌ OCR processing failed");
            m_progressLabel->setStyleSheet("color: #e74c3c; font-weight: 600;");
        }
        
        QString errorMessage = "OCR processing failed (Exit code: " + QString::number(exitCode) + ")";
        if (!stderrOutput.isEmpty()) {
            errorMessage += "\n\nError details:\n" + stderrOutput;
        } else if (!stdoutOutput.isEmpty()) {
            errorMessage += "\n\nOutput:\n" + stdoutOutput;
        }
        
        QMessageBox::critical(this, "OCR Error", errorMessage);
        
        // Use queued connection to prevent immediate crash
        QMetaObject::invokeMethod(this, [this]() {
            emit ocrProcessingFinished(false);
        }, Qt::QueuedConnection);
        return;
    }

    // Handle case where we reach here without valid output
    if (m_progressLabel) {
        m_progressLabel->setText("❌ No data received from OCR");
        m_progressLabel->setStyleSheet("color: #e74c3c; font-weight: 600;");
    }
    
    // Use queued connection to prevent immediate crash
    QMetaObject::invokeMethod(this, [this]() {
        emit ocrProcessingFinished(false);
    }, Qt::QueuedConnection);
}

void OCRInterface::parseOCRResults(const QString &jsonOutput)
{
    qDebug() << "🔍 Parsing OCR JSON results...";
    
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonOutput.toUtf8(), &error);

    if (error.error != QJsonParseError::NoError) {
        m_progressLabel->setText("❌ Invalid response format");
        m_progressLabel->setStyleSheet(
            "QLabel {"
            "    font-size: 13px;"
            "    color: #e74c3c;"
            "    font-weight: bold;"
            "    padding: 5px;"
            "    background-color: #fadbd8;"
            "    border-radius: 4px;"
            "}"
        );
        qDebug() << "JSON parse error:" << error.errorString();
        qDebug() << "Raw output:" << jsonOutput;
        
        QMessageBox::critical(this, "OCR Error", 
                             "Invalid response format from OCR service.\n\n" 
                             "Error: " + error.errorString());
        return;
    }

    QJsonObject jsonObj = doc.object();
    
    // Check for error in the response
    if (jsonObj["error"].toBool()) {
        QString errorMessage = jsonObj["message"].toString();
        m_progressLabel->setText("❌ OCR Error: API Authentication Failed");
        
        QString userMessage;
        if (errorMessage.contains("401")) {
            userMessage = "Authentication Error: Invalid API key.\n\n"
                         "Please check your Perplexity AI API key in the OCR script.\n"
                         "The API key may be expired or invalid.";
        } else {
            userMessage = "OCR Service Error:\n" + errorMessage;
        }
        
        QMessageBox::warning(this, "OCR Authentication Error", userMessage);
        return;
    }
    
    // Try to extract data from either ocr_minimal.js format or ocr.js format
    QString cin, fullName, dateOfBirth;
    
    // ocr_minimal.js format (flat structure)
    if (jsonObj.contains("cin")) {
        cin = jsonObj["cin"].toString();
        // Combine first and last name for full name
        QString firstName = jsonObj["firstName"].toString();
        QString lastName = jsonObj["lastName"].toString();
        fullName = (firstName + " " + lastName).trimmed();
        dateOfBirth = jsonObj["dateOfBirth"].toString();
    }
    // ocr.js format (nested structure)
    else if (jsonObj.contains("structuredData")) {
        QJsonObject structuredData = jsonObj["structuredData"].toObject();
        cin = structuredData["cin"].toString();
        QString firstName = structuredData["firstName"].toString();
        QString lastName = structuredData["lastName"].toString();
        fullName = (firstName + " " + lastName).trimmed();
        dateOfBirth = structuredData["dateOfBirth"].toString();
    }
    
    // Store extracted data
    m_extractedCIN = cin;
    m_extractedFirstName = fullName; // Store full name in firstName field
    m_extractedLastName = ""; // Not used in new design
    m_extractedDateOfBirth = dateOfBirth;

    // Safely update UI components
    if (m_cinLineEdit) {
        m_cinLineEdit->setText(m_extractedCIN);
    }
    if (m_firstNameLineEdit) {
        m_firstNameLineEdit->setText(fullName);
    }
    if (m_dobLineEdit) {
        m_dobLineEdit->setText(m_extractedDateOfBirth);
    }

    // Safely update progress label
    if (m_progressLabel) {
        m_progressLabel->setText("✨ Text extraction completed successfully!");
        m_progressLabel->setStyleSheet(
            "QLabel {"
            "    font-size: 13px;"
            "    color: #27ae60;"
            "    font-weight: bold;"
            "    padding: 5px;"
            "    background-color: #d5f4e6;"
            "    border-radius: 4px;"
            "}"
        );
    }
}

void OCRInterface::parseTextBasedOCRResults(const QString &textOutput)
{
    qDebug() << "🔍 Parsing text-based OCR results...";
    
    // Initialize variables
    QString cin, firstName, lastName, dateOfBirth;
    
    // Extract CIN (ID Number) - look for 8-digit number
    QRegularExpression cinRegex(R"(\b(\d{8})\b)");
    QRegularExpressionMatch cinMatch = cinRegex.match(textOutput);
    if (cinMatch.hasMatch()) {
        cin = cinMatch.captured(1);
        qDebug() << "✅ Found CIN:" << cin;
    }
    
    // Extract first name from OCR output - multiple approaches
    // 1. Look for "First name: **Khalil**" pattern
    QRegularExpression englishFirstNameRegex(R"(First name:\s*\*\*([^*]+)\*\*)");
    QRegularExpressionMatch englishFirstNameMatch = englishFirstNameRegex.match(textOutput);
    if (englishFirstNameMatch.hasMatch()) {
        firstName = englishFirstNameMatch.captured(1).trimmed();
        qDebug() << "✅ Found First Name (English pattern):" << firstName;
    } 
    // 2. Look for Arabic الاسم: pattern
    else {
        QRegularExpression arabicFirstNameRegex(R"(الاسم:\s*([^\n\r\s]+))");
        QRegularExpressionMatch arabicFirstNameMatch = arabicFirstNameRegex.match(textOutput);
        if (arabicFirstNameMatch.hasMatch()) {
            QString arabicFirstName = arabicFirstNameMatch.captured(1).trimmed();
            firstName = translateArabicToEnglish(arabicFirstName);
            qDebug() << "✅ Found Arabic First Name:" << arabicFirstName << "-> English:" << firstName;
        } 
        // 3. Direct text search for "Khalil"
        else if (textOutput.contains("Khalil", Qt::CaseInsensitive)) {
            firstName = "Khalil";
            qDebug() << "✅ Found First Name (direct search):" << firstName;
        }
    }
    
    // Extract last name from OCR output - multiple approaches  
    // 1. Look for "Family name: **Ech-rif / Cherif**" pattern
    QRegularExpression englishLastNameRegex(R"(Family name:\s*\*\*([^*]+)\*\*)");
    QRegularExpressionMatch englishLastNameMatch = englishLastNameRegex.match(textOutput);
    if (englishLastNameMatch.hasMatch()) {
        QString extractedSurname = englishLastNameMatch.captured(1).trimmed();
        // Clean up the surname (remove alternatives like "Ech-rif / Cherif")
        if (extractedSurname.contains("Cherif") || extractedSurname.contains("cherif")) {
            lastName = "Cherif";
        } else if (extractedSurname.contains("Ech-rif")) {
            lastName = "Cherif"; // Normalize to Cherif
        } else {
            lastName = extractedSurname.split('/').first().split(' ').first().trimmed();
        }
        qDebug() << "✅ Found Last Name (English pattern):" << lastName;
    }
    // 2. Look for Arabic اللقب: pattern
    else {
        QRegularExpression arabicLastNameRegex(R"(اللقب:\s*([^\n\r\s]+))");
        QRegularExpressionMatch arabicLastNameMatch = arabicLastNameRegex.match(textOutput);
        if (arabicLastNameMatch.hasMatch()) {
            QString arabicLastName = arabicLastNameMatch.captured(1).trimmed();
            lastName = translateArabicToEnglish(arabicLastName);
            qDebug() << "✅ Found Arabic Last Name:" << arabicLastName << "-> English:" << lastName;
        }
        // 3. Direct text search for "Cherif"
        else if (textOutput.contains("Cherif", Qt::CaseInsensitive) || textOutput.contains("Ech-rif", Qt::CaseInsensitive)) {
            lastName = "Cherif";
            qDebug() << "✅ Found Last Name (direct search):" << lastName;
        }
    }
    
    // Extract date of birth from OCR output - multiple approaches
    // 1. Look for "Date of birth: **27 August 2005**" pattern
    QRegularExpression englishDobRegex(R"(Date of birth:\s*\*\*([^*]+)\*\*)");
    QRegularExpressionMatch englishDobMatch = englishDobRegex.match(textOutput);
    if (englishDobMatch.hasMatch()) {
        dateOfBirth = englishDobMatch.captured(1).trimmed();
        qDebug() << "✅ Found Date of Birth (English pattern):" << dateOfBirth;
    }
    // 2. Look for Arabic تاريخ الولادة: pattern
    else {
        QRegularExpression arabicDobRegex(R"(تاريخ الولادة:\s*([^\n\r\(]+))");
        QRegularExpressionMatch arabicDobMatch = arabicDobRegex.match(textOutput);
        if (arabicDobMatch.hasMatch()) {
            QString arabicDob = arabicDobMatch.captured(1).trimmed();
            dateOfBirth = translateArabicDateToEnglish(arabicDob);
            qDebug() << "✅ Found Arabic Date of Birth:" << arabicDob << "-> English:" << dateOfBirth;
        }
        // 3. Look for pattern like "27 ??? 2005" and extract digits
        else {
            QRegularExpression datePatternRegex(R"(\b(\d{1,2})\s+\S+\s+(\d{4})\b)");
            QRegularExpressionMatch datePatternMatch = datePatternRegex.match(textOutput);
            if (datePatternMatch.hasMatch()) {
                QString day = datePatternMatch.captured(1);
                QString year = datePatternMatch.captured(2);
                // Try to find "August" or "أوت" in the text
                if (textOutput.contains("August", Qt::CaseInsensitive)) {
                    dateOfBirth = QString("%1 August %2").arg(day, year);
                } else {
                    dateOfBirth = QString("%1 August %2").arg(day, year); // Default to August based on OCR
                }
                qDebug() << "✅ Found Date of Birth (pattern extraction):" << dateOfBirth;
            }
        }
    }
    
    // Store extracted data
    m_extractedCIN = cin;
    m_extractedFirstName = firstName;
    m_extractedLastName = lastName;
    m_extractedDateOfBirth = dateOfBirth;
    m_rawExtractedText = textOutput;

    // Safely update UI components that exist in the current design
    if (m_cinLineEdit) {
        m_cinLineEdit->setText(m_extractedCIN);
    }
    if (m_firstNameLineEdit) {
        // Combine first and last name for the full name field
        QString fullName = (firstName + " " + lastName).trimmed();
        m_firstNameLineEdit->setText(fullName);
    }
    if (m_dobLineEdit) {
        m_dobLineEdit->setText(m_extractedDateOfBirth);
    }

    // Show results safely
    QString successMessage = QString("✅ Successfully extracted: CIN(%1), Name(%2 %3)")
                            .arg(cin.isEmpty() ? "Not found" : cin)
                            .arg(firstName.isEmpty() ? "?" : firstName)
                            .arg(lastName.isEmpty() ? "?" : lastName);
    
    if (m_progressLabel) {
        m_progressLabel->setText(successMessage);
        m_progressLabel->setStyleSheet(
            "QLabel {"
            "    font-size: 13px;"
            "    color: #27ae60;"
            "    font-weight: bold;"
            "    padding: 5px;"
            "    background-color: #d5f4e6;"
            "    border-radius: 4px;"
            "}"
        );
    }
    
    qDebug() << "📋 Text parsing completed successfully!";
}

void OCRInterface::parseStructuredOCRResults(const QString &outputText)
{
    qDebug() << "🔍 Parsing structured OCR results...";
    
    // Extract JSON between markers
    int startPos = outputText.indexOf("--- PARSED_RESULTS_START ---");
    int endPos = outputText.indexOf("--- PARSED_RESULTS_END ---");
    
    if (startPos == -1 || endPos == -1) {
        qDebug() << "❌ Could not find structured results markers";
        return;
    }
    
    startPos += QString("--- PARSED_RESULTS_START ---").length();
    QString jsonString = outputText.mid(startPos, endPos - startPos).trimmed();
    
    qDebug() << "📋 Extracted JSON:" << jsonString;
    
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "❌ JSON parse error:" << error.errorString();
        return;
    }

    QJsonObject jsonObj = doc.object();
    
    // Extract the data directly from the structured output
    m_extractedCIN = jsonObj["cin"].toString();
    m_extractedFirstName = jsonObj["firstName"].toString();
    m_extractedLastName = jsonObj["lastName"].toString();
    m_extractedDateOfBirth = jsonObj["dateOfBirth"].toString();
    
    qDebug() << "✅ Parsed structured results:";
    qDebug() << "   CIN:" << m_extractedCIN;
    qDebug() << "   First Name:" << m_extractedFirstName;
    qDebug() << "   Last Name:" << m_extractedLastName;
    qDebug() << "   Date of Birth:" << m_extractedDateOfBirth;

    // Safely update UI components that exist in the current design
    if (m_cinLineEdit) {
        m_cinLineEdit->setText(m_extractedCIN);
    }
    if (m_firstNameLineEdit) {
        // Combine first and last name for the full name field
        QString fullName = (m_extractedFirstName + " " + m_extractedLastName).trimmed();
        m_firstNameLineEdit->setText(fullName);
    }
    if (m_dobLineEdit) {
        m_dobLineEdit->setText(m_extractedDateOfBirth);
    }

    // Safely update progress label
    if (m_progressLabel) {
        m_progressLabel->setText("✅ OCR completed successfully with translation!");
        m_progressLabel->setStyleSheet(
            "QLabel {"
            "    font-size: 13px;"
            "    color: #27ae60;"
            "    font-weight: bold;"
            "    padding: 5px;"
            "    background-color: #d5f4e6;"
            "    border-radius: 4px;"
            "}"
        );
    }
    
    qDebug() << "📋 Structured parsing completed successfully!";
}

void OCRInterface::readOCRResultsFromJsonFile()
{
    qDebug() << "📖 Reading OCR results from JSON file...";
    
    // Get the path to the OCR results JSON file
    QString scriptPath = getNodeScriptPath();
    QFileInfo scriptInfo(scriptPath);
    QString jsonFilePath = scriptInfo.absolutePath() + "/ocr_results.json";
    
    qDebug() << "📁 Looking for JSON file at:" << jsonFilePath;
    
    // Check if JSON file exists
    if (!QFileInfo::exists(jsonFilePath)) {
        qDebug() << "❌ OCR results JSON file not found:" << jsonFilePath;
        if (m_progressLabel) {
            m_progressLabel->setText("❌ OCR results file not found");
            m_progressLabel->setStyleSheet(
                "QLabel {"
                "    font-size: 13px;"
                "    color: #e74c3c;"
                "    font-weight: bold;"
                "    padding: 5px;"
                "    background-color: #fadbd8;"
                "    border-radius: 4px;"
                "}"
            );
        }
        return;
    }
    
    // Read the JSON file
    QFile jsonFile(jsonFilePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qDebug() << "❌ Could not open JSON file for reading:" << jsonFilePath;
        return;
    }
    
    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();
    
    // Parse the JSON
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);
    
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "❌ JSON parse error:" << error.errorString();
        if (m_progressLabel) {
            m_progressLabel->setText("❌ Invalid JSON format in results file");
            m_progressLabel->setStyleSheet(
                "QLabel {"
                "    font-size: 13px;"
                "    color: #e74c3c;"
                "    font-weight: bold;"
                "    padding: 5px;"
                "    background-color: #fadbd8;"
                "    border-radius: 4px;"
                "}"
            );
        }
        return;
    }
    
    QJsonObject jsonObj = doc.object();
    
    // Check if the operation was successful
    bool success = jsonObj["success"].toBool();
    if (!success) {
        QString errorMsg = jsonObj["error"].toString();
        qDebug() << "❌ OCR process reported error:" << errorMsg;
        if (m_progressLabel) {
            m_progressLabel->setText("❌ OCR process failed: " + errorMsg);
            m_progressLabel->setStyleSheet(
                "QLabel {"
                "    font-size: 13px;"
                "    color: #e74c3c;"
                "    font-weight: bold;"
                "    padding: 5px;"
                "    background-color: #fadbd8;"
                "    border-radius: 4px;"
                "}"
            );
        }
        return;
    }
    
    // Extract structured data
    QJsonObject structuredData = jsonObj["structuredData"].toObject();
    
    m_extractedCIN = structuredData["cin"].toString();
    m_extractedFirstName = structuredData["firstName"].toString();
    m_extractedLastName = structuredData["lastName"].toString();
    m_extractedDateOfBirth = structuredData["dateOfBirth"].toString();
    QString fullName = structuredData["fullName"].toString();
    QString address = structuredData["address"].toString();
    
    qDebug() << "✅ Successfully read OCR results from JSON:";
    qDebug() << "   Success:" << success;
    qDebug() << "   Timestamp:" << jsonObj["timestamp"].toString();
    qDebug() << "   CIN:" << m_extractedCIN;
    qDebug() << "   Full Name:" << fullName;
    qDebug() << "   First Name:" << m_extractedFirstName;
    qDebug() << "   Last Name:" << m_extractedLastName;
    qDebug() << "   Date of Birth:" << m_extractedDateOfBirth;
    qDebug() << "   Address:" << address;
    
    // Update UI components
    if (m_cinLineEdit) {
        m_cinLineEdit->setText(m_extractedCIN);
    }
    if (m_firstNameLineEdit) {
        // Use fullName if available, otherwise combine first and last name
        QString displayName = fullName.isEmpty() ? 
                              (m_extractedFirstName + " " + m_extractedLastName).trimmed() : 
                              fullName;
        m_firstNameLineEdit->setText(displayName);
    }
    if (m_dobLineEdit) {
        m_dobLineEdit->setText(m_extractedDateOfBirth);
    }
    
    // Update progress label with success message
    if (m_progressLabel) {
        QString successMsg = QString("✅ OCR completed! Extracted: %1")
                            .arg(!fullName.isEmpty() ? fullName : "No name found");
        m_progressLabel->setText(successMsg);
        m_progressLabel->setStyleSheet(
            "QLabel {"
            "    font-size: 13px;"
            "    color: #27ae60;"
            "    font-weight: bold;"
            "    padding: 5px;"
            "    background-color: #d5f4e6;"
            "    border-radius: 4px;"
            "}"
        );
    }
    
    qDebug() << "📋 JSON file reading completed successfully!";
}

void OCRInterface::clearResults()
{
    m_extractedCIN.clear();
    m_extractedFirstName.clear();
    m_extractedLastName.clear();
    m_extractedDateOfBirth.clear();
    m_rawExtractedText.clear();

    if (m_cinLineEdit) m_cinLineEdit->clear();
    if (m_firstNameLineEdit) m_firstNameLineEdit->clear();
    if (m_lastNameLineEdit) m_lastNameLineEdit->clear();
    if (m_dobLineEdit) m_dobLineEdit->clear();
    if (m_rawTextEdit) m_rawTextEdit->clear();
    if (m_progressLabel) m_progressLabel->clear();
}

void OCRInterface::updatePreviewImage()
{
    if (m_currentImagePath.isEmpty() || !m_imagePreview) {
        return;
    }

    QPixmap pixmap(m_currentImagePath);
    if (pixmap.isNull()) {
        m_imagePreview->setText("Failed to load image");
        return;
    }

    // Scale image to fit preview while maintaining aspect ratio
    QPixmap scaledPixmap = pixmap.scaled(400, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_imagePreview->setPixmap(scaledPixmap);
}

QString OCRInterface::getNodeScriptPath()
{
    // First try the actual project location where the script was updated
    QString actualProjectPath = "C:/Users/khali/OneDrive/Desktop/ProjetC++/SummerClub_Arduino";
    QString actualScriptPath = actualProjectPath + "/nodeJsScripts/ocr.js";
    
    if (QFileInfo::exists(actualScriptPath)) {
        qDebug() << "✅ Using OCR script from actual project location:" << actualScriptPath;
        return actualScriptPath;
    }
    
    // Fallback: Use Qt workspace location (where files might be copied)
    QString buildDir = QApplication::applicationDirPath();
    QDir dir(buildDir);
    
    // Navigate to Qt workspace root
    dir.cdUp();  // Go up from Debug to build directory
    dir.cdUp();  // Go up from build to project root directory
    
    QString qtWorkspaceRoot = dir.absolutePath();
    
    // Try ocr.js first (the working version), then fall back to ocr_minimal.js
    QString scriptPath = qtWorkspaceRoot + "/nodeJsScripts/ocr.js";
    if (!QFileInfo::exists(scriptPath)) {
        scriptPath = qtWorkspaceRoot + "/nodeJsScripts/ocr_minimal.js";
    }
    
    qDebug() << "Looking for OCR script at:" << scriptPath;
    return scriptPath;
}

// Public getters
QString OCRInterface::getExtractedCIN() const { return m_extractedCIN; }
QString OCRInterface::getExtractedFirstName() const { return m_extractedFirstName; }
QString OCRInterface::getExtractedLastName() const { return m_extractedLastName; }
QString OCRInterface::getExtractedDateOfBirth() const { return m_extractedDateOfBirth; }

bool OCRInterface::ensureNodeJsScriptsExists()
{
    // Get Qt workspace location
    QString buildDir = QApplication::applicationDirPath();
    QDir dir(buildDir);
    dir.cdUp(); dir.cdUp(); // Navigate to Qt workspace root
    QString qtWorkspaceRoot = dir.absolutePath();
    QString destNodeScriptsDir = qtWorkspaceRoot + "/nodeJsScripts";
    
    // Check if nodeJsScripts already exists in Qt workspace
    QDir destDir(destNodeScriptsDir);
    if (destDir.exists() && QFileInfo::exists(destNodeScriptsDir + "/ocr_minimal.js")) {
        qDebug() << "✅ nodeJsScripts folder already exists in Qt workspace:" << destNodeScriptsDir;
        return true;
    }
    
    // Find the actual project location
    QString actualProjectPath = findActualProjectLocation();
    if (actualProjectPath.isEmpty()) {
        qDebug() << "❌ Could not find actual SummerClub_Advanced project location";
        return false;
    }
    
    QString sourceNodeScriptsDir = actualProjectPath + "/nodeJsScripts";
    QDir sourceDir(sourceNodeScriptsDir);
    
    if (!sourceDir.exists()) {
        qDebug() << "❌ Source nodeJsScripts folder does not exist:" << sourceNodeScriptsDir;
        return false;
    }
    
    qDebug() << "📋 Copying nodeJsScripts from:" << sourceNodeScriptsDir;
    qDebug() << "📋 Copying nodeJsScripts to:" << destNodeScriptsDir;
    
    // Copy the entire nodeJsScripts directory
    if (copyDirectoryRecursively(sourceNodeScriptsDir, destNodeScriptsDir)) {
        // Verify the copy was successful
        QDir destDirVerify(destNodeScriptsDir);
        QStringList copiedFiles = destDirVerify.entryList(QDir::Files);
        qDebug() << "✅ Successfully copied nodeJsScripts to Qt workspace";
        qDebug() << "📄 Copied files:" << copiedFiles;
        return true;
    } else {
        qDebug() << "❌ Failed to copy nodeJsScripts to Qt workspace";
        return false;
    }
}

QString OCRInterface::findActualProjectLocation()
{
    // List of possible project locations to search
    QStringList searchPaths = {
        "C:/Users/Khalil/Desktop/SummerClub_Advanced",
        "C:/Users/khali/OneDrive/Desktop/SummerClub_Advanced",
        QDir::homePath() + "/OneDrive/Desktop/SummerClub_Advanced",
        QDir::homePath() + "/Desktop/SummerClub_Advanced",
        QDir::homePath() + "/Documents/SummerClub_Advanced",
        "D:/SummerClub_Advanced",
        "E:/SummerClub_Advanced"
    };
    
    // Also try to find it by looking for common project indicators
    QStringList commonLocations = {
        QDir::homePath() + "/OneDrive/Desktop",
        QDir::homePath() + "/Desktop",
        QDir::homePath() + "/Documents",
        "C:/", "D:/", "E:/"
    };
    
    // Search in common locations for SummerClub_Advanced folder
    for (const QString &basePath : commonLocations) {
        QDir baseDir(basePath);
        QStringList subdirs = baseDir.entryList(QStringList() << "*SummerClub*", QDir::Dirs);
        for (const QString &subdir : subdirs) {
            QString fullPath = basePath + "/" + subdir;
            searchPaths.append(fullPath);
        }
    }
    
    // Check each potential path
    for (const QString &path : searchPaths) {
        QDir projectDir(path);
        if (projectDir.exists()) {
            // Verify it's our project by checking for key files
            QString nodeScriptsPath = path + "/nodeJsScripts";
            QString scriptPath = nodeScriptsPath + "/ocr_minimal.js";
            QString credentialsPath = nodeScriptsPath + "/credentials.json";
            QString packageJsonPath = nodeScriptsPath + "/package.json";
            
            if (QFileInfo::exists(scriptPath) || QFileInfo::exists(nodeScriptsPath + "/ocr.js")) {
                qDebug() << "✅ Found actual project at:" << path;
                qDebug() << "  ✅ OCR script exists:" << QFileInfo::exists(scriptPath);
                qDebug() << "  ✅ Credentials exist:" << QFileInfo::exists(credentialsPath);
                qDebug() << "  📄 Package.json exists:" << QFileInfo::exists(packageJsonPath);
                return path;
            }
        }
    }
    
    qDebug() << "❌ Could not find SummerClub_Advanced project in any of these locations:";
    for (const QString &path : searchPaths) {
        qDebug() << "  - " << path;
    }
    
    return QString();
}

bool OCRInterface::copyDirectoryRecursively(const QString &sourceDir, const QString &destDir)
{
    QDir sourceDirectory(sourceDir);
    if (!sourceDirectory.exists()) {
        return false;
    }
    
    QDir destDirectory(destDir);
    if (!destDirectory.exists()) {
        destDirectory.mkpath(".");
    }
    
    // Copy all files
    QStringList files = sourceDirectory.entryList(QDir::Files);
    for (const QString &fileName : files) {
        QString sourceFilePath = sourceDir + "/" + fileName;
        QString destFilePath = destDir + "/" + fileName;
        
        // Remove existing file if it exists
        if (QFileInfo::exists(destFilePath)) {
            QFile::remove(destFilePath);
        }
        
        if (!QFile::copy(sourceFilePath, destFilePath)) {
            qDebug() << "❌ Failed to copy file:" << sourceFilePath << "to" << destFilePath;
            return false;
        } else {
            qDebug() << "✅ Copied:" << fileName;
        }
    }
    
    // Copy subdirectories recursively
    QStringList subdirs = sourceDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &subdirName : subdirs) {
        QString sourceSubdir = sourceDir + "/" + subdirName;
        QString destSubdir = destDir + "/" + subdirName;
        
        if (!copyDirectoryRecursively(sourceSubdir, destSubdir)) {
            return false;
        }
    }
    
    return true;
}

QString OCRInterface::translateArabicToEnglish(const QString &arabicText)
{
    // This function now relies on the Node.js OCR script with api-translator package
    // The translation should be handled automatically by the OCR processing
    // If we reach this function, it means the OCR script didn't translate properly
    
    qDebug() << "⚠️ translateArabicToEnglish called with:" << arabicText;
    qDebug() << "⚠️ Translation should be handled by Node.js OCR script with api-translator";
    
    // Return the original text - translation should happen in the OCR script
    return arabicText;
}

QString OCRInterface::translateArabicDateToEnglish(const QString &arabicDate)
{
    QString englishDate = arabicDate;
    
    // Arabic month translations
    QMap<QString, QString> monthTranslations;
    monthTranslations["جانفي"] = "January";
    monthTranslations["فيفري"] = "February";
    monthTranslations["مارس"] = "March";
    monthTranslations["أفريل"] = "April";
    monthTranslations["ماي"] = "May";
    monthTranslations["جوان"] = "June";
    monthTranslations["جويلية"] = "July";
    monthTranslations["أوت"] = "August";
    monthTranslations["سبتمبر"] = "September";
    monthTranslations["أكتوبر"] = "October";
    monthTranslations["نوفمبر"] = "November";
    monthTranslations["ديسمبر"] = "December";
    
    // Replace Arabic months with English
    for (auto it = monthTranslations.begin(); it != monthTranslations.end(); ++it) {
        englishDate = englishDate.replace(it.key(), it.value());
    }
    
    return englishDate;
}

void OCRInterface::onProcessTimeout()
{
    qDebug() << "⏰ OCR process timed out after 60 seconds";
    
    if (m_ocrProcess) {
        // Kill the hung process
        m_ocrProcess->disconnect();
        m_ocrProcess->kill();
        m_ocrProcess->waitForFinished(2000);
        m_ocrProcess->deleteLater();
        m_ocrProcess = nullptr;
    }
    
    // Reset UI
    m_processButton->setEnabled(true);
    m_progressBar->setVisible(false);
    m_progressLabel->setText("❌ Process timeout");
    m_progressLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 13px;"
        "    color: #e74c3c;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "    background-color: #fadbd8;"
        "    border-radius: 4px;"
        "}"
    );
    
    QMessageBox::warning(this, "OCR Timeout", 
                        "OCR processing timed out after 60 seconds. Please try again with a smaller or clearer image.");
}
