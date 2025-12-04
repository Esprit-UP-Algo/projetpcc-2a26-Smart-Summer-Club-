#ifndef ACTIVITYCALENDAR_H
#define ACTIVITYCALENDAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QCalendarWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QScrollArea>
#include <QFrame>
#include <QGroupBox>
#include <QListWidget>
#include <QTextEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QMap>
#include <QList>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>

// Forward declarations
class QTableWidget;
class QTableWidgetItem;

// Clickable frame for activity cards
class ClickableFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ClickableFrame(QWidget *parent = nullptr) : QFrame(parent) {}

protected:
    void mousePressEvent(QMouseEvent *event) override {
        Q_UNUSED(event)
        emit clicked();
    }

signals:
    void clicked();
};

// Activity data structure
struct ActivityCalendarItem {
    int activityId;
    QString title;
    QString type;
    QDateTime startTime;
    QDateTime endTime;
    QString instructor;
    QString responsible;
    int currentParticipants;
    int maxCapacity;
    QString priority;
    QString status;
    QString location;
    QColor indicatorColor;
    
    // Constructor
    ActivityCalendarItem() : activityId(0), currentParticipants(0), maxCapacity(0) {}
};

// Custom Calendar Widget with activity indicators
class CustomCalendarWidget : public QCalendarWidget
{
    Q_OBJECT

public:
    explicit CustomCalendarWidget(QWidget *parent = nullptr);
    void setActivities(const QMap<QDate, QList<ActivityCalendarItem>> &activities);
    void addActivity(const QDate &date, const ActivityCalendarItem &activity);
    void removeActivity(const QDate &date, int activityId);
    void clearActivities();
    QColor getActivityColor(const QString &type) const;
    QChar getActivityIcon(const QString &type) const;

protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

private:
    QMap<QDate, QList<ActivityCalendarItem>> m_activities;

signals:
    void dayClicked(const QDate &date);
    void dayDoubleClicked(const QDate &date);
};

// Main Activity Calendar Widget
class ActivityCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityCalendar(QWidget *parent = nullptr);
    ~ActivityCalendar();

    // Public methods
    void refreshCalendarData();
    void navigateToDate(const QDate &date);
    void addNewActivity(const QDate &date = QDate());

signals:
    void addNewActivityRequested(const QDate &date);

public slots:
    void onDateSelected(const QDate &date);
    void onMonthChanged(int year, int month);
    void onFilterChanged();
    void onViewModeChanged();
    void onTodayClicked();
    void onPreviousMonthClicked();
    void onNextMonthClicked();
    void onAddActivityClicked();
    void onRefreshClicked();
    void onExportClicked();

    // Arduino LCD communication slots
    void onArduinoConnectClicked();
    void onArduinoDisconnectClicked();
    void onSerialErrorOccurred(QSerialPort::SerialPortError error);

private slots:
    void onActivityDoubleClicked(const QDate &date);
    void onActivityActionTriggered();
    void updateStatistics();
    void loadActivitiesFromDatabase();
    void addSampleActivities();

private:
    void setupUI();
    void setupCalendarSection();
    void setupControlsSection();
    void setupDetailsSection();
    void setupStatisticsSection();
    void applyStyles();
    void connectSignals();
    
    // Data management
    void loadActivitiesForDateRange(const QDate &startDate, const QDate &endDate);
    void updateSelectedDateActivities(const QDate &date);
    void clearDetailsPanel();
    void addActivityToDetailsPanel(const ActivityCalendarItem &activity);
    
    // Filter and view management
    void applyFilters();
    bool passesFilter(const ActivityCalendarItem &activity) const;
    
    // Context menu and actions
    void showContextMenu(const QPoint &pos);
    void editActivity(int activityId);
    void deleteActivity(int activityId);
    void duplicateActivity(int activityId);
    void viewActivityDetails(int activityId);
    
    // Arduino LCD communication methods
    void initializeArduinoConnection();
    void sendActivityToArduino(const QDate &date);
    void sendActivityDataToArduino(const ActivityCalendarItem &activity);
    void sendNoActivityToArduino();
    void disconnectArduino();
    
    // Statistics and analytics
    void updateMonthlyStatistics();
    void calculateCapacityStats();
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_topControlsLayout;
    QHBoxLayout *m_calendarLayout;
    QHBoxLayout *m_bottomLayout;
    
    // Top Controls
    QFrame *m_controlsFrame;
    QPushButton *m_previousButton;
    QPushButton *m_nextButton;
    QPushButton *m_todayButton;
    QLabel *m_monthYearLabel;
    QComboBox *m_viewModeCombo;
    QComboBox *m_activityTypeFilter;
    QComboBox *m_priorityFilter;
    QComboBox *m_statusFilter;
    QPushButton *m_addActivityButton;
    QPushButton *m_refreshButton;
    QPushButton *m_exportButton;
    QPushButton *m_arduinoConnectButton;
    QPushButton *m_arduinoDisconnectButton;
    QLabel *m_arduinoStatusLabel;
    
    // Calendar Section
    QFrame *m_calendarFrame;
    CustomCalendarWidget *m_calendar;
    
    // Statistics Panel (Right side)
    QFrame *m_statisticsFrame;
    QVBoxLayout *m_statisticsLayout;
    QGroupBox *m_statsGroup;
    QLabel *m_totalActivitiesLabel;
    QLabel *m_totalParticipantsLabel;
    QLabel *m_completedActivitiesLabel;
    QLabel *m_upcomingActivitiesLabel;
    QLabel *m_conflictsLabel;
    QLabel *m_avgAttendanceLabel;
    QProgressBar *m_capacityProgressBar;
    QLabel *m_capacityLabel;
    
    // Details Panel (Bottom)
    QFrame *m_detailsFrame;
    QVBoxLayout *m_detailsLayout;
    QLabel *m_selectedDateLabel;
    QScrollArea *m_activitiesScrollArea;
    QWidget *m_activitiesContainer;
    QHBoxLayout *m_activitiesContainerLayout;
    
    // Data
    QMap<QDate, QList<ActivityCalendarItem>> m_activities;
    QDate m_currentDate;
    QDate m_selectedDate;
    QString m_currentActivityTypeFilter;
    QString m_currentPriorityFilter;
    QString m_currentStatusFilter;
    
    // Statistics data
    int m_totalActivitiesCount;
    int m_totalParticipantsCount;
    int m_completedActivitiesCount;
    int m_upcomingActivitiesCount;
    int m_conflictsCount;
    double m_avgAttendanceRate;
    
    // Auto-refresh timer
    QTimer *m_refreshTimer;
    
    // Arduino LCD communication
    QSerialPort *m_serialPort;
    bool m_arduinoConnected;
    QString m_lastSentActivityData;
};

#endif // ACTIVITYCALENDAR_H