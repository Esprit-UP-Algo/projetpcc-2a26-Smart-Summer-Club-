#ifndef EMAILPANEL_H
#define EMAILPANEL_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QProgressDialog>
#include <QThread>
#include <QRegularExpression>
#include <QDateTimeEdit>
#include <QGroupBox>
#include <QProgressBar>
#include <QTableWidget>
#include <QHeaderView>
#include <QFrame>
#include <QScrollArea>
#include <QButtonGroup>
#include <QRadioButton>
#include <QTcpSocket>
#include <QSslSocket>
#include <QMimeData>
#include <QFileDialog>
#include <QMimeDatabase>
#include <QTimer>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class EmailPanel : public QWidget
{
    Q_OBJECT

public:
    explicit EmailPanel(QWidget *parent = nullptr);
    
    // Public methods for database integration
    void loadMembersFromDatabase();
    void refreshMemberData();

private slots:
    void onMemberSelectionChanged();
    void onTemplateChanged();
    void onMessageTextChanged();
    void onSendClicked();
    void onScheduleClicked();
    void onPreviewClicked();
    void onSelectAllMembers(bool checked);
    void onFilterChanged();
    void onSearchTextChanged();
    void onCreateTemplateClicked();
    void onTestAPIClicked();

private:
    void setupUI();
    void setupLeftPanel();
    void setupRightPanel();
    void setupMemberList();
    void setupMessageComposer();
    void setupTemplatesSection();
    void setupHistorySection();
    void setupStatusBar();
    void applyStyles();
    
    void loadMembers();
    void loadTemplates();
    void updateMemberCount();
    void updateCharacterCount();
    void updateCostEstimate();
    void filterMembers();
    
    // Database integration methods (private implementation)
    void refreshMemberList();
    void applyMemberFilters();
    
    // Email sending methods
    void sendEmailToSelectedMembers();
    bool sendSingleEmail(const QString& emailAddress, const QString& subject, const QString& htmlContent, const QStringList& attachments = QStringList());
    bool sendViaSMTP(const QString& to, const QString& subject, const QString& htmlContent, const QStringList& attachments);
    QString generateEmailHTML(const QString& content, const QString& memberName);
    QString validateEmailAddress(const QString& email);
    void setupEmailTemplates();
    void addAttachment(const QString& filePath);
    void removeAttachment(const QString& filePath);
    QString encodeBase64File(const QString& filePath);
    void scheduleEmail(const QDateTime& sendTime);
    void trackEmailDelivery(const QString& emailId, const QString& recipient);
    QString formatEmailAddress(const QString& email);
    
    // Missing method declarations for compilation
    void onSubjectChanged();
    void onAttachFileClicked();
    bool tryEmailSMTP(const QString& apiUrl, const QString& emailAddress, const QString& message);
    
    // Main layout
    QSplitter *m_mainSplitter;
    
    // Left panel
    QWidget *m_leftPanel;
    QVBoxLayout *m_leftLayout;
    
    // Member selection section
    QGroupBox *m_memberGroup;
    QVBoxLayout *m_memberLayout;
    QLineEdit *m_searchEdit;
    QComboBox *m_filterComboBox;
    QCheckBox *m_selectAllCheckBox;
    QListWidget *m_memberListWidget;
    QLabel *m_selectedCountLabel;
    
    // History section
    QGroupBox *m_historyGroup;
    QVBoxLayout *m_historyLayout;
    QLabel *m_todayCountLabel;
    QLabel *m_weekCountLabel;
    QLabel *m_monthCountLabel;
    QPushButton *m_viewHistoryButton;
    
    // Right panel
    QWidget *m_rightPanel;
    QVBoxLayout *m_rightLayout;
    
    // Message composer section
    QGroupBox *m_composerGroup;
    QVBoxLayout *m_composerLayout;
    QComboBox *m_templateComboBox;
    QPushButton *m_createTemplateButton;
    QTextEdit *m_messageTextEdit;
    QLabel *m_variablesLabel;
    
    // Scheduling section
    QGroupBox *m_scheduleGroup;
    QHBoxLayout *m_scheduleLayout;
    QRadioButton *m_sendNowRadio;
    QRadioButton *m_scheduleRadio;
    QDateTimeEdit *m_scheduleDateTimeEdit;
    
    // Templates section
    QGroupBox *m_templatesGroup;
    QVBoxLayout *m_templatesLayout;
    QListWidget *m_templatesListWidget;
    
    // Status bar
    QFrame *m_statusFrame;
    QHBoxLayout *m_statusLayout;
    QLabel *m_recipientsLabel;
    QLabel *m_charactersLabel;
    QLabel *m_costLabel;
    QPushButton *m_testButton;
    QPushButton *m_previewButton;
    QPushButton *m_sendButton;
    
    // Email-specific UI components
    QLineEdit *m_subjectLineEdit;
    QListWidget *m_attachmentsListWidget;
    QPushButton *m_addAttachmentButton;
    QPushButton *m_removeAttachmentButton;
    QGroupBox *m_attachmentsGroup;
    
    // SMTP configuration
    QLineEdit *m_smtpServerEdit;
    QSpinBox *m_smtpPortSpinBox;
    QLineEdit *m_smtpUsernameEdit;
    QLineEdit *m_smtpPasswordEdit;
    QCheckBox *m_enableSSLCheckBox;
    
    // Email tracking
    QTimer *m_deliveryTimer;
    QStringList m_pendingEmails;
    QStringList m_attachmentPaths;
    
    // Member data structure
    struct MemberData {
        QString cin;
        QString firstName;
        QString lastName;
        QString email;
        QString subscriptionPlan;
        QString gender;
        int age;
        QString joinDate;
    };
    
    QList<MemberData> m_allMembers;
    QList<MemberData> m_filteredMembers;
    
    // Network manager for email APIs and SMTP
    QNetworkAccessManager *m_networkManager;
    
    // Data
    QStringList m_availableTemplates;
    QMap<QString, QString> m_templateContents;
    int m_selectedMemberCount;
    int m_characterCount;
    double m_estimatedCost;
    
    // Email-specific variables
    QString m_currentSubject;
    QStringList m_currentAttachments;
    QString m_smtpServer;
    int m_smtpPort;
    QString m_smtpUsername;
    QString m_smtpPassword;
    bool m_useSSL;
    int m_emailsSentToday;
    int m_emailsSentThisWeek;
    int m_emailsSentThisMonth;
};

#endif // EMAILPANEL_H