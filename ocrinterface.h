#ifndef OCRINTERFACE_H
#define OCRINTERFACE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QProgressBar>
#include <QFrame>
#include <QScrollArea>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QApplication>
#include <QSplitter>
#include <QGroupBox>
#include <QTimer>
#include <QMetaObject>

class OCRInterface : public QWidget
{
    Q_OBJECT

public:
    explicit OCRInterface(QWidget *parent = nullptr);
    ~OCRInterface();

    // Public methods to access extracted data
    QString getExtractedCIN() const;
    QString getExtractedFirstName() const;
    QString getExtractedLastName() const;
    QString getExtractedDateOfBirth() const;

private slots:
    void onUploadImageClicked();
    void onProcessImageClicked();
    void onClearFormClicked();
    void onAutoFillMemberFormClicked();
    void processOCRFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessTimeout();

private:
    // UI Setup methods
    void setupUI();
    void setupTitleBar();
    void setupInputPanel(QSplitter *parent);
    void setupResultsPanel(QSplitter *parent);
    void connectSignals();
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    QFrame *m_uploadFrame;
    QFrame *m_previewFrame;
    QFrame *m_resultFrame;
    QFrame *m_actionFrame;

    // Main UI elements
    QLabel *m_uploadTitle;
    QPushButton *m_uploadButton;
    QLabel *m_uploadStatusLabel;
    QLabel *m_previewTitle;
    QLabel *m_imagePreview;
    QPushButton *m_processButton;
    QProgressBar *m_progressBar;
    QLabel *m_progressLabel;
    QLabel *m_resultTitle;
    QLineEdit *m_cinLineEdit;
    QLineEdit *m_firstNameLineEdit;
    QLineEdit *m_lastNameLineEdit;
    QLineEdit *m_dobLineEdit;
    QTextEdit *m_rawTextEdit;
    QPushButton *m_clearButton;
    QPushButton *m_autoFillButton;

    // Data members
    QString m_currentImagePath;
    QString m_extractedCIN;
    QString m_extractedFirstName;
    QString m_extractedLastName;
    QString m_extractedDateOfBirth;
    QString m_rawExtractedText;

    // Process handling
    QProcess *m_ocrProcess;
    QTimer *m_processTimeout;

    // Helper methods
    void clearResults();
    void updatePreviewImage();
    void parseOCRResults(const QString &jsonOutput);
    void parseTextBasedOCRResults(const QString &textOutput);
    void parseStructuredOCRResults(const QString &outputText);
    void readOCRResultsFromJsonFile();
    QString getNodeScriptPath();
    bool ensureNodeJsScriptsExists();
    QString findActualProjectLocation();
    bool copyDirectoryRecursively(const QString &sourceDir, const QString &destDir);
    QString translateArabicToEnglish(const QString &arabicText);
    QString translateArabicDateToEnglish(const QString &arabicDate);

signals:
    void dataExtracted(const QString &cin, const QString &firstName, 
                      const QString &lastName, const QString &dateOfBirth);
    void ocrProcessingStarted();
    void ocrProcessingFinished(bool success);
};

#endif // OCRINTERFACE_H