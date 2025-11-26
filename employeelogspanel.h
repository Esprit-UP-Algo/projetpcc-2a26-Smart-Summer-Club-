#ifndef EMPLOYEELOGSPANEL_H
#define EMPLOYEELOGSPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QGroupBox>
#include <QProgressBar>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QSplitter>
#include <QTextEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QFrame>
#include <QApplication>
#include <QCoreApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QScrollArea>
#include <QSpacerItem>
#include <QCheckBox>
#include <QButtonGroup>
#include <QCalendarWidget>
#include <QTextStream>
#include <QCryptographicHash>
#include <QMutex>
#include <QMutexLocker>
#include <QThread>
#include <QDateTime>
#include <QTimeZone>
#include <QStandardPaths>
#include <QUuid>

// Forward declarations
class QPropertyAnimation;
class QSequentialAnimationGroup;

/**
 * @brief Log entry structure for audit trail
 */
struct AuditLogEntry {
    QString logId;                    // Unique log identifier
    QDateTime timestamp;              // When the action occurred
    QString userId;                   // Who performed the action
    QString userName;                 // Display name of user
    QString userRole;                 // Role of the user (Admin, Manager, etc.)
    QString action;                   // Action type (CREATE, UPDATE, DELETE, LOGIN, etc.)
    QString entityType;               // What was affected (Employee, Member, etc.)
    QString entityId;                 // ID of affected entity
    QString beforeData;               // Data before change (JSON)
    QString afterData;                // Data after change (JSON)
    QString sessionId;                // Session identifier
    QString riskLevel;                // LOW, MEDIUM, HIGH, CRITICAL
    bool success;                     // Whether operation succeeded
    QString errorMessage;             // Error details if failed
    QString description;              // Human-readable description
    
    // Constructor
    AuditLogEntry() : success(true), riskLevel("LOW") {}
};

/**
 * @class EmployeeLogsPanel
 * @brief Advanced audit logging system for employee management
 * 
 * This class provides a comprehensive audit trail system that tracks
 * all database changes and user activities with enterprise-grade security.
 * 
 * Features:
 * - Real-time activity monitoring
 * - Advanced filtering and search
 * - Risk assessment and alerts
 * - Export capabilities (PDF, CSV, JSON)
 * - Timeline visualization
 * - Pattern detection
 * - Secure file-based logging with encryption
 * - Log rotation and archival
 */
class EmployeeLogsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeLogsPanel(QWidget *parent = nullptr);
    
    // Public logging interface
    static void logAction(const QString &action, const QString &entityType, 
                         const QString &entityId, const QString &beforeData = "", 
                         const QString &afterData = "", const QString &description = "");
    
    // Risk assessment
    enum RiskLevel { LOW, MEDIUM, HIGH, CRITICAL };
    static RiskLevel assessRisk(const QString &action, const QString &entityType, 
                               const QString &userId, const QDateTime &timestamp);

public slots:
    void refreshLogs();
    void exportLogs();
    void clearFilters();
    void showLogDetails(int row, int column);

private slots:
    void onFilterChanged();
    void onDateRangeChanged();
    void onSearchTextChanged();
    void onTableSelectionChanged();
    void onAutoRefreshToggled(bool enabled);
    void onRiskLevelFilterChanged();
    void showContextMenu(const QPoint &pos);
    void highlightSuspiciousActivity();

private:
    // Main layout components
    QVBoxLayout *m_mainLayout;
    QSplitter *m_mainSplitter;
    
    // Dashboard section (top)
    QWidget *m_dashboardWidget;
    QGridLayout *m_dashboardLayout;
    
    // Dashboard cards
    QGroupBox *m_totalLogsCard;
    QGroupBox *m_todayActivityCard;
    QGroupBox *m_riskAlertsCard;
    QGroupBox *m_lastActivityCard;
    
    // Dashboard labels
    QLabel *m_totalLogsLabel;
    QLabel *m_todayActivityLabel;
    QLabel *m_riskAlertsLabel;
    QLabel *m_lastActivityLabel;
    
    // Filter section (middle top)
    QWidget *m_filterWidget;
    QGridLayout *m_filterLayout;
    QGroupBox *m_filterGroup;
    
    // Filter controls
    QLineEdit *m_searchEdit;
    QComboBox *m_actionFilterCombo;
    QComboBox *m_entityFilterCombo;
    QComboBox *m_userFilterCombo;
    QComboBox *m_riskFilterCombo;
    QDateEdit *m_startDateEdit;
    QDateEdit *m_endDateEdit;
    QPushButton *m_applyFilterButton;
    QPushButton *m_clearFilterButton;
    QPushButton *m_exportButton;
    QCheckBox *m_autoRefreshCheckBox;
    
    // Timeline view toggle
    QPushButton *m_timelineToggleButton;
    QPushButton *m_tableToggleButton;
    
    // Table section (middle)
    QWidget *m_tableWidget;
    QVBoxLayout *m_tableLayout;
    QTableWidget *m_logsTable;
    
    // Timeline section (alternative view)
    QWidget *m_timelineWidget;
    QVBoxLayout *m_timelineLayout;
    QScrollArea *m_timelineScrollArea;
    QWidget *m_timelineContent;
    
    // Risk assessment panel (bottom)
    QWidget *m_riskWidget;
    QVBoxLayout *m_riskLayout;
    QGroupBox *m_riskGroup;
    QTextEdit *m_riskAnalysisText;
    
    // Insights and recommendations
    QGroupBox *m_insightsGroup;
    QTextEdit *m_insightsText;
    
    // Data management
    QList<AuditLogEntry> m_logEntries;
    QList<AuditLogEntry> m_filteredEntries;
    QTimer *m_refreshTimer;
    QTimer *m_riskAssessmentTimer;
    
    // Current user context
    QString m_currentUserId;
    QString m_currentUserName;
    QString m_currentUserRole;
    QString m_currentSessionId;
    
    // View state
    bool m_timelineViewEnabled;
    bool m_autoRefreshEnabled;
    
    // Setup methods
    void setupUI();
    void setupDashboard();
    void setupFilters();
    void setupTable();
    void setupTimeline();
    void setupRiskAssessment();
    void setupInsights();
    
    // Data methods
    void loadLogsFromFile();
    void saveLogsToFile();
    void updateDashboard();
    void updateTable();
    void updateTimeline();
    void updateRiskAssessment();
    void updateInsights();
    void applyFilters();
    
    // Logging core methods
    static void writeLogEntry(const AuditLogEntry &entry);
    static QString generateLogId();
    static QString getCurrentUserId();
    static QString getCurrentUserName();
    static QString getCurrentUserRole();
    static QString getCurrentSessionId();
    
    // File management
    static QString getLogsFilePath();
    static QString getArchiveFilePath(const QDate &date);
    static void rotateLogsIfNeeded();
    static bool encryptLogFile(const QString &filePath);
    static bool decryptLogFile(const QString &filePath);
    
    // Risk assessment methods
    void analyzeActivityPatterns();
    void detectAnomalies();
    void generateRiskReport();
    QStringList getHighRiskActivities();
    
    // Export methods
    void exportToPDF();
    void exportToCSV();
    void exportToJSON();
    
    // Utility methods
    void setTableStyle();
    void setCardStyle(QGroupBox *card, const QString &color = "#16a5b3");
    QString formatTimestamp(const QDateTime &timestamp);
    static QString formatRiskLevel(const QString &riskLevel);
    static QString getActionIcon(const QString &action);
    static QString getRiskIcon(const QString &riskLevel);
    void showLogEntryDetails(const AuditLogEntry &entry);
    void animateCard(QGroupBox *card);
    
    // Security methods
    static QString hashData(const QString &data);
    static bool verifyLogIntegrity(const AuditLogEntry &entry);
    
    // Thread safety
    static QMutex s_logMutex;
    
    // Constants
    static const int MAX_LOG_ENTRIES_PER_FILE;
    static const int LOG_RETENTION_DAYS;
    static const QString LOG_FILE_EXTENSION;
    static const QString ARCHIVE_FOLDER_NAME;
};

#endif // EMPLOYEELOGSPANEL_H