#ifndef RFIDPANEL_H
#define RFIDPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QTimer>
#include <QScrollArea>
#include <QTextEdit>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

#include "rfidcard.h"
#include "rfidmanager.h"
#include "member.h"
#include "rfidcarddialog.h"

class RFIDPanel : public QWidget
{
    Q_OBJECT

public:
    explicit RFIDPanel(QWidget *parent = nullptr);
    ~RFIDPanel();
    
    void setRFIDManager(RFIDManager *manager);
    void refreshAll();

private slots:
    // Card management
    void onAddCardClicked();
    void onEditCardClicked();
    void onDeleteCardClicked();
    void onToggleCardStatusClicked();
    void onViewCardDetailsClicked();
    void refreshCardTable();
    void onCardTableSelectionChanged();
    void onSearchTextChanged();
    void onStatusFilterChanged();
    
    // Activity feed
    void refreshActivityFeed();
    void onAutoRefreshToggled();
    void onRFIDAccessGranted(const QString &memberName, const QString &rfidUid);
    void onRFIDAccessDenied(const QString &rfidUid, const QString &reason);

private:
    void setupUI();
    void setupCardManagementSection();
    void setupActivitySection();
    void setupStyles();
    void connectSignals();
    
    // Helper methods
    void updateStatCard(QLabel *valueLabel, const QString &value, QLabel *statusLabel = nullptr, const QString &status = "");
    void loadCardData();
    void addActivityEntry(const QString &message, bool isSuccess = true);
    QString formatTimeAgo(const QDateTime &dateTime);
    
    // UI Components - Card Management Section
    QGroupBox *m_cardManagementGroup;
    QLineEdit *m_searchLineEdit;
    QComboBox *m_statusFilterCombo;
    QPushButton *m_addCardButton;
    QTableWidget *m_cardTableWidget;
    QPushButton *m_viewCardButton;
    QPushButton *m_editCardButton;
    QPushButton *m_deleteCardButton;
    QPushButton *m_toggleStatusButton;
    
    // UI Components - Activity Feed Section
    QGroupBox *m_activityGroup;
    QTextEdit *m_activityTextEdit;
    QPushButton *m_autoRefreshButton;
    QPushButton *m_clearActivityButton;
    
    // Data and functionality
    RFIDManager *m_rfidManager;
    QTimer *m_activityTimer;
    bool m_autoRefreshEnabled;
    int m_selectedCardRow;
};

#endif // RFIDPANEL_H