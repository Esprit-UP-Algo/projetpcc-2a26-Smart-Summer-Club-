#ifndef ACTIVITYPANEL_H
#define ACTIVITYPANEL_H

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
#include <QProcess>
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
#include <QFrame>
#include <QApplication>
#include <QCoreApplication>
#include <QFileInfo>

struct ActivityRegistration {
    int sequence;
    QString responseId;
    QString createTime;
    QString createTimeReadable;
    QString name;
    QString email;
    QString activityType;
    QString phoneNumber;
    QString age;
    bool paymentConfirmed;
};

class ActivityPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityPanel(QWidget *parent = nullptr);

private slots:
    void onSyncData();
    void onNodeJSFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onNodeJSError(QProcess::ProcessError error);
    void onTableSelectionChanged();
    void onRefreshTimer();

private:
    // Main layout
    QVBoxLayout *m_mainLayout;
    QSplitter *m_mainSplitter;
    
    // Top dashboard section
    QWidget *m_dashboardWidget;
    QGridLayout *m_dashboardLayout;
    
    // Dashboard cards
    QGroupBox *m_totalResponsesCard;
    QGroupBox *m_latestActivityCard;
    QGroupBox *m_lastSyncCard;
    QPushButton *m_syncButton;
    
    // Dashboard labels
    QLabel *m_totalResponsesLabel;
    QLabel *m_latestActivityLabel;
    QLabel *m_lastSyncLabel;
    
    // Progress bar for sync
    QProgressBar *m_syncProgressBar;
    
    // Middle section - data table
    QWidget *m_tableWidget;
    QVBoxLayout *m_tableLayout;
    QGroupBox *m_tableGroup;
    QTableWidget *m_registrationTable;
    
    // Table controls
    QWidget *m_tableControlsWidget;
    QHBoxLayout *m_tableControlsLayout;
    QLineEdit *m_searchEdit;
    QComboBox *m_filterComboBox;
    QComboBox *m_sortComboBox;
    
    // Bottom section - analytics
    QWidget *m_analyticsWidget;
    QHBoxLayout *m_analyticsLayout;
    
    // Removed charts section to avoid QtCharts dependency
    
    // Insights section
    QGroupBox *m_insightsGroup;
    QVBoxLayout *m_insightsLayout;
    QTextEdit *m_insightsText;
    
    // Data management
    QList<ActivityRegistration> m_registrations;
    QTimer *m_refreshTimer;
    QProcess *m_nodeProcess;
    
    // Setup methods
    void setupUI();
    void setupDashboard();
    void setupTable();
    void setupAnalytics();
    void setupInsights();
    
    // Data methods
    void loadDataFromJSON();
    void updateDashboard();
    void updateTable();
    void updateAnalytics();
    void updateInsights();
    
    // Utility methods
    void setCardStyle(QGroupBox *card);
    void setTableStyle();
    void applyTableFilters();
    QString formatDateTime(const QString &isoDateTime);
    QString getActivityIcon(const QString &activityType);
    void showSyncStatus(const QString &message, bool success = true);
    void generateInsights();
    
    // File operations
    bool formsDataExists();
    QString getFormsDataPath();
    bool ensureNodeJsScriptsExists();
    QString findActualProjectLocation();
    bool copyDirectoryRecursively(const QString &sourceDir, const QString &destDir);
};

#endif // ACTIVITYPANEL_H