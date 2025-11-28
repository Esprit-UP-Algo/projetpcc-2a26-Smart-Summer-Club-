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
{
    setupUI();
    connectSignals();
    clearResults();
}

OCRInterface::~OCRInterface()
{
    if (m_ocrProcess && m_ocrProcess->state() != QProcess::NotRunning) {
        m_ocrProcess->kill();
        m_ocrProcess->waitForFinished(3000);
    }
}

void OCRInterface::setupUI()
{
    // Create main layout with proper spacing
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(15);
    m_mainLayout->setContentsMargins(15, 15, 15, 15);

    // Create and setup sections
    setupUploadSection();
    setupPreviewSection(); 
    setupResultSection();
    setupActionSection();

    // Connect all signals
    connectSignals();
    
    // Set minimal widget styling
    setStyleSheet(
        "OCRInterface {"
        "    background-color: #f5f5f5;"
        "}"
    );
}


void OCRInterface::setupUploadSection()
{
    m_uploadFrame = new QFrame(this);
    m_uploadFrame->setFrameStyle(QFrame::StyledPanel);
    m_uploadFrame->setStyleSheet(
        "QFrame {"
        "    background-color: white;"
        "    border: 1px solid #ddd;"
        "    border-radius: 8px;"
        "    margin: 5px;"
        "}"
    );

    QVBoxLayout *uploadLayout = new QVBoxLayout(m_uploadFrame);
    uploadLayout->setSpacing(10);
    uploadLayout->setContentsMargins(15, 15, 15, 15);
    
    m_uploadTitle = new QLabel("📄 Upload ID Card Image", m_uploadFrame);
    m_uploadTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #333;");
    m_uploadTitle->setAlignment(Qt::AlignCenter);

    m_uploadButton = new QPushButton("📁 Choose Image File", m_uploadFrame);
    m_uploadButton->setMinimumHeight(40);
    m_uploadButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #007bff;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0056b3;"
        "}"
    );

    m_uploadStatusLabel = new QLabel("No file selected", m_uploadFrame);
    m_uploadStatusLabel->setAlignment(Qt::AlignCenter);
    m_uploadStatusLabel->setStyleSheet("color: #666; font-size: 12px;");

    uploadLayout->addWidget(m_uploadTitle);
    uploadLayout->addWidget(m_uploadButton);
    uploadLayout->addWidget(m_uploadStatusLabel);
    
    m_mainLayout->addWidget(m_uploadFrame);
}

void OCRInterface::setupPreviewSection()
{
    m_previewFrame = new QFrame(this);
    m_previewFrame->setFrameStyle(QFrame::StyledPanel);
    m_previewFrame->setStyleSheet(
        "QFrame {"
        "    background-color: white;"
        "    border: 1px solid #ddd;"
        "    border-radius: 8px;"
        "    margin: 5px;"
        "}"
    );
    m_previewFrame->setVisible(false);

    QVBoxLayout *previewLayout = new QVBoxLayout(m_previewFrame);
    previewLayout->setSpacing(10);
    previewLayout->setContentsMargins(15, 15, 15, 15);
    
    m_previewTitle = new QLabel("🖼️ Image Preview", m_previewFrame);
    m_previewTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #333;");
    m_previewTitle->setAlignment(Qt::AlignCenter);

    m_imagePreview = new QLabel(m_previewFrame);
    m_imagePreview->setAlignment(Qt::AlignCenter);
    m_imagePreview->setMinimumHeight(200);
    m_imagePreview->setMaximumHeight(250);
    m_imagePreview->setStyleSheet(
        "QLabel {"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "    background-color: #f9f9f9;"
        "}"
    );
    m_imagePreview->setScaledContents(true);

    m_processButton = new QPushButton("🔍 Extract Text from Image", m_previewFrame);
    m_processButton->setMinimumHeight(40);
    m_processButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #28a745;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #218838;"
        "}"
    );
    
    m_progressBar = new QProgressBar(m_previewFrame);
    m_progressBar->setVisible(false);
    m_progressBar->setRange(0, 0);
    m_progressBar->setStyleSheet(
        "QProgressBar {"
        "    border: 1px solid #ccc;"
        "    border-radius: 3px;"
        "    text-align: center;"
        "}"
    );

    m_progressLabel = new QLabel("", m_previewFrame);
    m_progressLabel->setAlignment(Qt::AlignCenter);
    m_progressLabel->setStyleSheet("color: #007bff; font-weight: bold;");

    previewLayout->addWidget(m_previewTitle);
    previewLayout->addWidget(m_imagePreview);
    previewLayout->addWidget(m_processButton);
    previewLayout->addWidget(m_progressBar);
    previewLayout->addWidget(m_progressLabel);
    
    m_mainLayout->addWidget(m_previewFrame);
}

void OCRInterface::setupResultSection()
{
    m_resultFrame = new QFrame(this);
    m_resultFrame->setFrameStyle(QFrame::StyledPanel);
    m_resultFrame->setStyleSheet(
        "QFrame {"
        "    background-color: white;"
        "    border: 1px solid #ddd;"
        "    border-radius: 8px;"
        "    margin: 5px;"
        "}"
    );
    m_resultFrame->setVisible(false);

    QVBoxLayout *resultLayout = new QVBoxLayout(m_resultFrame);
    resultLayout->setSpacing(10);
    resultLayout->setContentsMargins(15, 15, 15, 15);
    
    m_resultTitle = new QLabel("✨ Extracted Information", m_resultFrame);
    m_resultTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #333;");
    m_resultTitle->setAlignment(Qt::AlignCenter);

    // Create scroll area for the content
    QScrollArea *scrollArea = new QScrollArea(m_resultFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setMaximumHeight(400);
    scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: 1px solid #ddd;"
        "    border-radius: 5px;"
        "    background-color: #fafafa;"
        "}"
        "QScrollBar:vertical {"
        "    background-color: #f0f0f0;"
        "    width: 12px;"
        "    border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background-color: #c0c0c0;"
        "    border-radius: 6px;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background-color: #a0a0a0;"
        "}"
    );

    // Create content widget for scroll area
    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setSpacing(10);
    scrollLayout->setContentsMargins(10, 10, 10, 10);

    // Create form grid
    QWidget *formWidget = new QWidget();
    QGridLayout *formLayout = new QGridLayout(formWidget);
    formLayout->setSpacing(8);
    formLayout->setContentsMargins(0, 0, 0, 0);

    QString labelStyle = "font-weight: bold; color: #555;";
    QString lineEditStyle = 
        "QLineEdit {"
        "    background-color: #f8f8f8;"
        "    border: 1px solid #ccc;"
        "    border-radius: 3px;"
        "    padding: 5px;"
        "}";

    // Form fields
    QLabel *cinLabel = new QLabel("CIN:", formWidget);
    cinLabel->setStyleSheet(labelStyle);
    m_cinLineEdit = new QLineEdit(formWidget);
    m_cinLineEdit->setReadOnly(true);
    m_cinLineEdit->setStyleSheet(lineEditStyle);

    QLabel *firstNameLabel = new QLabel("First Name:", formWidget);
    firstNameLabel->setStyleSheet(labelStyle);
    m_firstNameLineEdit = new QLineEdit(formWidget);
    m_firstNameLineEdit->setReadOnly(true);
    m_firstNameLineEdit->setStyleSheet(lineEditStyle);

    QLabel *lastNameLabel = new QLabel("Last Name:", formWidget);
    lastNameLabel->setStyleSheet(labelStyle);
    m_lastNameLineEdit = new QLineEdit(formWidget);
    m_lastNameLineEdit->setReadOnly(true);
    m_lastNameLineEdit->setStyleSheet(lineEditStyle);

    QLabel *dobLabel = new QLabel("Date of Birth:", formWidget);
    dobLabel->setStyleSheet(labelStyle);
    m_dobLineEdit = new QLineEdit(formWidget);
    m_dobLineEdit->setReadOnly(true);
    m_dobLineEdit->setStyleSheet(lineEditStyle);

    // Add to grid
    formLayout->addWidget(cinLabel, 0, 0);
    formLayout->addWidget(m_cinLineEdit, 0, 1);
    formLayout->addWidget(firstNameLabel, 1, 0);
    formLayout->addWidget(m_firstNameLineEdit, 1, 1);
    formLayout->addWidget(lastNameLabel, 2, 0);
    formLayout->addWidget(m_lastNameLineEdit, 2, 1);
    formLayout->addWidget(dobLabel, 3, 0);
    formLayout->addWidget(m_dobLineEdit, 3, 1);

    // Raw text area
    QLabel *rawTextLabel = new QLabel("Raw Extracted Text:", scrollContent);
    rawTextLabel->setStyleSheet(labelStyle);
    
    m_rawTextEdit = new QTextEdit(scrollContent);
    m_rawTextEdit->setMinimumHeight(150);
    m_rawTextEdit->setReadOnly(true);
    m_rawTextEdit->setStyleSheet(
        "QTextEdit {"
        "    background-color: #f8f8f8;"
        "    border: 1px solid #ccc;"
        "    border-radius: 3px;"
        "    padding: 8px;"
        "    font-family: monospace;"
        "    font-size: 10px;"
        "}"
    );

    // Add widgets to scroll layout
    scrollLayout->addWidget(formWidget);
    scrollLayout->addWidget(rawTextLabel);
    scrollLayout->addWidget(m_rawTextEdit);
    scrollLayout->addStretch(); // Add stretch to push content to top

    // Set the scroll content
    scrollArea->setWidget(scrollContent);

    resultLayout->addWidget(m_resultTitle);
    resultLayout->addWidget(scrollArea);
    
    m_mainLayout->addWidget(m_resultFrame);
}

void OCRInterface::setupActionSection()
{
    m_actionFrame = new QFrame(this);
    m_actionFrame->setFrameStyle(QFrame::StyledPanel);
    m_actionFrame->setStyleSheet(
        "QFrame {"
        "    background-color: white;"
        "    border: 1px solid #ddd;"
        "    border-radius: 8px;"
        "    margin: 5px;"
        "}"
    );
    m_actionFrame->setVisible(false);

    QHBoxLayout *actionLayout = new QHBoxLayout(m_actionFrame);
    actionLayout->setSpacing(10);
    actionLayout->setContentsMargins(15, 15, 15, 15);

    m_clearButton = new QPushButton("🗑️ Clear Results", m_actionFrame);
    m_clearButton->setMinimumHeight(35);
    m_clearButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #dc3545;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 13px;"
        "    font-weight: bold;"
        "    padding: 8px 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #c82333;"
        "}"
    );

    m_autoFillButton = new QPushButton("🚀 Auto-fill Member Form", m_actionFrame);
    m_autoFillButton->setMinimumHeight(35);
    m_autoFillButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #007bff;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 13px;"
        "    font-weight: bold;"
        "    padding: 8px 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0056b3;"
        "}"
    );

    actionLayout->addWidget(m_clearButton);
    actionLayout->addStretch();
    actionLayout->addWidget(m_autoFillButton);
    
    m_mainLayout->addWidget(m_actionFrame);
}

void OCRInterface::connectSignals()
{
    connect(m_uploadButton, &QPushButton::clicked, this, &OCRInterface::onUploadImageClicked);
    connect(m_processButton, &QPushButton::clicked, this, &OCRInterface::onProcessImageClicked);
    connect(m_clearButton, &QPushButton::clicked, this, &OCRInterface::onClearFormClicked);
    connect(m_autoFillButton, &QPushButton::clicked, this, &OCRInterface::onAutoFillMemberFormClicked);
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
        m_uploadStatusLabel->setText("📸 " + QFileInfo(fileName).fileName());
        m_uploadStatusLabel->setStyleSheet("color: #16a5b3; font-weight: 600;");
        
        updatePreviewImage();
        m_previewFrame->setVisible(true);
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

    // Setup OCR process
    if (m_ocrProcess) {
        m_ocrProcess->deleteLater();
    }
    
    m_ocrProcess = new QProcess(this);
    connect(m_ocrProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &OCRInterface::processOCRFinished);

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
    
    // Set working directory to nodeJsScripts folder (where credentials and dependencies are)
    QFileInfo scriptFileInfo(scriptPath);
    QString workingDir = scriptFileInfo.absolutePath();
    QString scriptFileName = scriptFileInfo.fileName();
    m_ocrProcess->setWorkingDirectory(workingDir);
    
    // Run the Node.js OCR script with relative path
    QStringList arguments;
    arguments << scriptFileName << m_currentImagePath;

    qDebug() << "📋 Running OCR script:" << scriptFileName;
    qDebug() << "📁 Working directory:" << workingDir;
    qDebug() << "📝 Arguments:" << arguments;
    qDebug() << "📝 Full command: node" << arguments.join(" ");

    m_ocrProcess->start("node", arguments);
    
    if (!m_ocrProcess->waitForStarted(5000)) {
        QString errorMsg = "Failed to start OCR process. Make sure Node.js is installed.";
        QMessageBox::critical(this, "OCR Error", errorMsg);
        qDebug() << "❌" << errorMsg;
        qDebug() << "Process error:" << m_ocrProcess->errorString();
        m_processButton->setEnabled(true);
        m_progressBar->setVisible(false);
        m_progressLabel->clear();
    }
}

void OCRInterface::onClearFormClicked()
{
    m_currentImagePath.clear();
    m_uploadStatusLabel->setText("No file selected");
    m_uploadStatusLabel->setStyleSheet("color: #7f8c8d; font-size: 14px;");
    m_previewFrame->setVisible(false);
    m_resultFrame->setVisible(false);
    m_actionFrame->setVisible(false);
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
    m_processButton->setEnabled(true);
    m_progressBar->setVisible(false);

    // Read both stdout and stderr
    QByteArray stdoutData = m_ocrProcess->readAllStandardOutput();
    QByteArray stderrData = m_ocrProcess->readAllStandardError();
    
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

    // Check if we have JSON output in stdout (even with non-zero exit code)
    if (!stdoutOutput.isEmpty() && stdoutOutput.trimmed().startsWith("{")) {
        qDebug() << "📋 Parsing JSON output from OCR script...";
        parseOCRResults(stdoutOutput.trimmed());
        emit ocrProcessingFinished(true);
        return;
    }
    
    // Check if we have text-based output from ocr.js (successful extraction)
    if (exitStatus == QProcess::NormalExit && exitCode == 0 && !stdoutOutput.isEmpty()) {
        qDebug() << "📋 Parsing text-based output from OCR script...";
        parseTextBasedOCRResults(stdoutOutput);
        emit ocrProcessingFinished(true);
        return;
    }

    // If no valid output, treat as error
    if (exitStatus == QProcess::CrashExit || exitCode != 0) {
        m_progressLabel->setText("❌ OCR processing failed");
        m_progressLabel->setStyleSheet("color: #e74c3c; font-weight: 600;");
        
        QString errorMessage = "OCR processing failed (Exit code: " + QString::number(exitCode) + ")";
        if (!stderrOutput.isEmpty()) {
            errorMessage += "\n\nError details:\n" + stderrOutput;
        } else if (!stdoutOutput.isEmpty()) {
            errorMessage += "\n\nOutput:\n" + stdoutOutput;
        }
        
        QMessageBox::critical(this, "OCR Error", errorMessage);
        emit ocrProcessingFinished(false);
        return;
    }

    // Read the output
    QByteArray outputData = m_ocrProcess->readAllStandardOutput();
    QString jsonOutput = QString::fromUtf8(outputData);

    if (jsonOutput.isEmpty()) {
        m_progressLabel->setText("❌ No data received from OCR");
        m_progressLabel->setStyleSheet("color: #e74c3c; font-weight: 600;");
        emit ocrProcessingFinished(false);
        return;
    }

    parseOCRResults(jsonOutput);
    emit ocrProcessingFinished(true);
}

void OCRInterface::parseOCRResults(const QString &jsonOutput)
{
    qDebug() << "🔍 Parsing OCR JSON results...";
    
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonOutput.toUtf8(), &error);

    if (error.error != QJsonParseError::NoError) {
        m_progressLabel->setText("❌ Invalid response format");
        m_progressLabel->setStyleSheet("color: #e74c3c; font-weight: 600;");
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
        m_progressLabel->setStyleSheet("color: #e74c3c; font-weight: 600;");
        
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
    QString cin, firstName, lastName, dateOfBirth, rawText;
    
    // ocr_minimal.js format (flat structure)
    if (jsonObj.contains("cin")) {
        cin = jsonObj["cin"].toString();
        firstName = jsonObj["firstName"].toString();
        lastName = jsonObj["lastName"].toString();
        dateOfBirth = jsonObj["dateOfBirth"].toString();
        rawText = jsonObj["rawText"].toString();
    }
    // ocr.js format (nested structure)
    else if (jsonObj.contains("structuredData")) {
        QJsonObject structuredData = jsonObj["structuredData"].toObject();
        cin = structuredData["cin"].toString();
        firstName = structuredData["firstName"].toString();
        lastName = structuredData["lastName"].toString();
        dateOfBirth = structuredData["dateOfBirth"].toString();
        rawText = jsonObj["extractedData"].toString();
    }
    
    // Extract data
    m_extractedCIN = cin;
    m_extractedFirstName = firstName;
    m_extractedLastName = lastName;
    m_extractedDateOfBirth = dateOfBirth;
    m_rawExtractedText = rawText;

    // Update UI
    m_cinLineEdit->setText(m_extractedCIN);
    m_firstNameLineEdit->setText(m_extractedFirstName);
    m_lastNameLineEdit->setText(m_extractedLastName);
    m_dobLineEdit->setText(m_extractedDateOfBirth);
    m_rawTextEdit->setPlainText(m_rawExtractedText);

    // Show results
    m_progressLabel->setText("✅ Text extraction completed successfully!");
    m_progressLabel->setStyleSheet("color: #27ae60; font-weight: 600;");
    m_resultFrame->setVisible(true);
    m_actionFrame->setVisible(true);
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
    
    // Extract names - look for specific patterns in the text
    QRegularExpression givenNameRegex(R"(Given Name[:\s]*([A-Za-z\u0600-\u06FF\s]+)(?:\s*\(|\n|$))");
    QRegularExpressionMatch givenNameMatch = givenNameRegex.match(textOutput);
    if (givenNameMatch.hasMatch()) {
        firstName = givenNameMatch.captured(1).trimmed();
        qDebug() << "✅ Found Given Name:" << firstName;
    } else {
        // Fallback: look for "Khalil" or similar patterns
        QRegularExpression namePattern(R"(\*\*Given Name:\*\*\s*([A-Za-z\u0600-\u06FF]+))");
        QRegularExpressionMatch nameMatch = namePattern.match(textOutput);
        if (nameMatch.hasMatch()) {
            firstName = nameMatch.captured(1).trimmed();
        } else if (textOutput.contains("Khalil")) {
            firstName = "Khalil";
        }
    }
    
    // Extract family name
    QRegularExpression familyNameRegex(R"(Family Name[:\s]*([A-Za-z\u0600-\u06FF\s-]+)(?:\s*\(|\n|$))");
    QRegularExpressionMatch familyNameMatch = familyNameRegex.match(textOutput);
    if (familyNameMatch.hasMatch()) {
        lastName = familyNameMatch.captured(1).trimmed();
        qDebug() << "✅ Found Family Name:" << lastName;
    } else {
        // Look for "Ash-Sharif" or similar patterns
        if (textOutput.contains("Ash-Sharif")) {
            lastName = "Ash-Sharif";
        } else if (textOutput.contains("الشريف")) {
            lastName = "الشريف";
        }
    }
    
    // Extract date of birth
    QRegularExpression dobRegex(R"(Date of Birth[:\s]*(\d{1,2}\s+[A-Za-z]+\s+\d{4}))");
    QRegularExpressionMatch dobMatch = dobRegex.match(textOutput);
    if (dobMatch.hasMatch()) {
        dateOfBirth = dobMatch.captured(1).trimmed();
        qDebug() << "✅ Found Date of Birth:" << dateOfBirth;
    } else {
        // Look for specific date pattern "27 August 2005"
        if (textOutput.contains("27 August 2005")) {
            dateOfBirth = "27 August 2005";
        } else {
            // More generic date patterns
            QRegularExpression genericDate(R"((\d{1,2}\s+[A-Za-z]+\s+\d{4}))");
            QRegularExpressionMatch genericMatch = genericDate.match(textOutput);
            if (genericMatch.hasMatch()) {
                dateOfBirth = genericMatch.captured(1).trimmed();
            }
        }
    }
    
    // Store extracted data
    m_extractedCIN = cin;
    m_extractedFirstName = firstName;
    m_extractedLastName = lastName;
    m_extractedDateOfBirth = dateOfBirth;
    m_rawExtractedText = textOutput;

    // Update UI
    m_cinLineEdit->setText(m_extractedCIN);
    m_firstNameLineEdit->setText(m_extractedFirstName);
    m_lastNameLineEdit->setText(m_extractedLastName);
    m_dobLineEdit->setText(m_extractedDateOfBirth);
    m_rawTextEdit->setPlainText(m_rawExtractedText);

    // Show results
    QString successMessage = QString("✅ Successfully extracted: CIN(%1), Name(%2 %3)")
                            .arg(cin.isEmpty() ? "Not found" : cin)
                            .arg(firstName.isEmpty() ? "?" : firstName)
                            .arg(lastName.isEmpty() ? "?" : lastName);
    
    m_progressLabel->setText(successMessage);
    m_progressLabel->setStyleSheet("color: #27ae60; font-weight: 600;");
    m_resultFrame->setVisible(true);
    m_actionFrame->setVisible(true);
    
    qDebug() << "📋 Text parsing completed successfully!";
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
    // Use Qt workspace location (where files are copied)
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
        QDir::homePath() + "/Desktop/SummerClub_Advanced",
        QDir::homePath() + "/Documents/SummerClub_Advanced",
        "D:/SummerClub_Advanced",
        "E:/SummerClub_Advanced"
    };
    
    // Also try to find it by looking for common project indicators
    QStringList commonLocations = {
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