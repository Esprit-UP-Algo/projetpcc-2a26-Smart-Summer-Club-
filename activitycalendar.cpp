#include "activitycalendar.h"
#include "Connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSplitter>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSizePolicy>
#include <algorithm>

// =============================================================================
// CustomCalendarWidget Implementation
// =============================================================================

CustomCalendarWidget::CustomCalendarWidget(QWidget *parent)
    : QCalendarWidget(parent)
{
    // Configure calendar appearance
    setGridVisible(true);
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
    setSelectionMode(QCalendarWidget::SingleSelection);
    
    // Set minimum date to prevent issues
    setMinimumDate(QDate(2020, 1, 1));
    setMaximumDate(QDate(2030, 12, 31));
    
    // Ensure the calendar is visible and properly sized
    setVisible(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // Set current date to ensure proper initialization
    setSelectedDate(QDate::currentDate());
    
    // Enable custom drawing
    setAttribute(Qt::WA_OpaquePaintEvent, false);
    setAutoFillBackground(false);
    
    // Connect selection changed signal
    connect(this, &QCalendarWidget::selectionChanged, this, [this]() {
        emit dayClicked(selectedDate());
    });
    
    qDebug() << "📅 CustomCalendarWidget initialized";
}

void CustomCalendarWidget::setActivities(const QMap<QDate, QList<ActivityCalendarItem>> &activities)
{
    qDebug() << "🎨 CustomCalendarWidget::setActivities called with" << activities.size() << "days of activities";
    m_activities = activities;
    
    // Debug: Print some activity details
    for (auto it = activities.begin(); it != activities.end(); ++it) {
        qDebug() << "📅 Date:" << it.key().toString() << "has" << it.value().size() << "activities";
    }
    
    // Use QCalendarWidget's built-in date formatting to color dates
    // Clear any existing formats first
    QMap<QDate, QTextCharFormat> formats;
    
    // Apply colored formats to dates with activities
    for (auto it = activities.begin(); it != activities.end(); ++it) {
        const QDate& date = it.key();
        const QList<ActivityCalendarItem>& dayActivities = it.value();
        
        if (!dayActivities.isEmpty()) {
            QTextCharFormat format;
            QColor activityColor = getActivityColor(dayActivities.first().type);
            
            // Set background color
            format.setBackground(QBrush(activityColor.lighter(180)));
            
            // Set border
            format.setProperty(QTextFormat::OutlinePen, QPen(activityColor, 2));
            
            // Make text bold and colored
            format.setFontWeight(QFont::Bold);
            format.setForeground(QBrush(activityColor.darker(150)));
            
            // Apply the format to this date
            setDateTextFormat(date, format);
            
            qDebug() << "🎨 Applied format to date" << date.toString() << "with color" << activityColor.name();
        }
    }
    
    update(); // Trigger repaint
    repaint(); // Force immediate repaint
}

void CustomCalendarWidget::addActivity(const QDate &date, const ActivityCalendarItem &activity)
{
    m_activities[date].append(activity);
    update();
}

void CustomCalendarWidget::removeActivity(const QDate &date, int activityId)
{
    if (m_activities.contains(date)) {
        auto &activities = m_activities[date];
        activities.erase(std::remove_if(activities.begin(), activities.end(),
            [activityId](const ActivityCalendarItem &activity) {
                return activity.activityId == activityId;
            }), activities.end());
        
        if (activities.isEmpty()) {
            m_activities.remove(date);
        }
        update();
    }
}

void CustomCalendarWidget::clearActivities()
{
    m_activities.clear();
    update();
}

void CustomCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    // Call base implementation first
    QCalendarWidget::paintCell(painter, rect, date);
    
    // Debug: Check if we have activities data
    static bool debugPrinted = false;
    if (!debugPrinted) {
        qDebug() << "🎨 paintCell called. Total activity days:" << m_activities.size();
        debugPrinted = true;
    }
    
    // Check if this date has activities
    if (m_activities.contains(date)) {
        const auto &activities = m_activities[date];
        if (!activities.isEmpty()) {
            qDebug() << "🎨 Painting" << activities.size() << "activities for date" << date.toString();
            
            // First, draw colored background for days with activities
            QRect bgRect = rect.adjusted(1, 1, -1, -1);
            
            // Use the color of the first activity as the primary color
            QColor primaryColor = getActivityColor(activities.first().type);
            qDebug() << "🎨 Using color" << primaryColor.name() << "for activity type" << activities.first().type;
            
            // Create a more visible colored background (less transparency)
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing);
            
            // Make the background much more visible
            QColor bgColor = primaryColor.lighter(140); // Much less light, more visible
            painter->setBrush(QBrush(bgColor));
            painter->setPen(QPen(primaryColor.darker(110), 2));
            painter->drawRoundedRect(bgRect, 6, 6);
            
            painter->restore();
            
            // Draw activity indicators at the bottom
            painter->save();
            
            int indicatorSize = 6;
            int spacing = 2;
            int maxIndicators = std::min(static_cast<int>(activities.size()), 4); // Max 4 indicators per day
            
            int totalWidth = maxIndicators * indicatorSize + (maxIndicators - 1) * spacing;
            int startX = rect.x() + (rect.width() - totalWidth) / 2;
            int startY = rect.bottom() - indicatorSize - 2;
            
            for (int i = 0; i < maxIndicators; ++i) {
                QColor indicatorColor = getActivityColor(activities[i].type);
                painter->setBrush(QBrush(indicatorColor));
                painter->setPen(QPen(indicatorColor.darker(120), 1));
                
                QRect indicatorRect(startX + i * (indicatorSize + spacing), 
                                  startY, indicatorSize, indicatorSize);
                painter->drawEllipse(indicatorRect);
            }
            
            // If more than 4 activities, show a count
            if (activities.size() > 4) {
                painter->setPen(QPen(QColor("#2c3e50"), 1));
                painter->setFont(QFont("Arial", 8, QFont::Bold));
                QString overflowText = QString("+%1").arg(activities.size() - 4);
                painter->drawText(rect.adjusted(2, 2, -2, -2), Qt::AlignTop | Qt::AlignRight, overflowText);
            }
            
            painter->restore();
        }
    }
}

QColor CustomCalendarWidget::getActivityColor(const QString &type) const
{
    static QMap<QString, QColor> colorMap = {
        {"Mini Hackathon Kids", QColor("#3498db")},      // Blue
        {"Event", QColor("#e74c3c")},                     // Red
        {"Group Class", QColor("#27ae60")},              // Green
        {"Musique", QColor("#f39c12")},                  // Orange
        {"Workshop", QColor("#9b59b6")},                 // Purple
        {"Aeronautics Workshop", QColor("#e67e22")},     // Dark Orange
        {"Cinema & Acting Lab", QColor("#e91e63")},      // Pink
        {"Art", QColor("#795548")},                      // Brown
        {"Sports & Fitness Program", QColor("#607d8b")}, // Blue Grey
        {"Special Events", QColor("#ff5722")}            // Deep Orange
    };
    
    return colorMap.value(type, QColor("#16a5b3")); // Default teal color
}

QChar CustomCalendarWidget::getActivityIcon(const QString &type) const
{
    static QMap<QString, QChar> iconMap = {
        {"Mini Hackathon Kids", QChar(0x1F4BB)},     // 💻
        {"Event", QChar(0x1F389)},                   // 🎉
        {"Group Class", QChar(0x1F91D)},             // 🤝
        {"Musique", QChar(0x1F3B5)},                 // 🎵
        {"Workshop", QChar(0x1F6E0)},                // 🛠️
        {"Aeronautics Workshop", QChar(0x2708)},     // ✈️
        {"Cinema & Acting Lab", QChar(0x1F3AC)},     // 🎬
        {"Art", QChar(0x1F3A8)},                     // 🎨
        {"Sports & Fitness Program", QChar(0x1F3CB)}, // 🏋️
        {"Special Events", QChar(0x2B50)}            // ⭐
    };
    
    return iconMap.value(type, QChar(0x1F4C5)); // Default calendar icon 📅
}

// =============================================================================
// ActivityCalendar Implementation
// =============================================================================

ActivityCalendar::ActivityCalendar(QWidget *parent)
    : QWidget(parent)
    , m_currentDate(QDate::currentDate())
    , m_selectedDate(QDate::currentDate())
    , m_totalActivitiesCount(0)
    , m_totalParticipantsCount(0)
    , m_completedActivitiesCount(0)
    , m_upcomingActivitiesCount(0)
    , m_conflictsCount(0)
    , m_avgAttendanceRate(0.0)
    , m_serialPort(nullptr)
    , m_arduinoConnected(false)
    , m_activityCycleTimer(nullptr)
    , m_currentActivityIndex(0)
{
    setupUI();
    connectSignals();
    applyStyles();
    
    // Initialize activity cycling timer for LCD
    m_activityCycleTimer = new QTimer(this);
    m_activityCycleTimer->setInterval(5000); // 5 seconds between activities
    connect(m_activityCycleTimer, &QTimer::timeout, this, &ActivityCalendar::onActivityCycleTimeout);
    
    // Initialize filter values to default "All" options
    m_currentActivityTypeFilter = "All Types";
    m_currentPriorityFilter = "All Priorities";
    m_currentStatusFilter = "All Status";
    
    // Initialize the month year label
    m_monthYearLabel->setText(m_currentDate.toString("MMMM yyyy"));
    
    // Initialize with current month data
    loadActivitiesFromDatabase();
    updateStatistics();
    
    // Add sample activities for testing if no activities are found
    if (m_activities.isEmpty()) {
        qDebug() << "🎯 No activities found, adding sample activities for testing";
        addSampleActivities();
    }
    
    // Navigate to November 2025 where we have activities
    m_calendar->setCurrentPage(2025, 11);
    m_currentDate = QDate(2025, 11, 1);
    
    // Setup auto-refresh timer (refresh every 5 minutes)
    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, &QTimer::timeout, this, &ActivityCalendar::loadActivitiesFromDatabase);
    m_refreshTimer->start(300000); // 5 minutes
    
    // Initialize Arduino communication
    initializeArduinoConnection();
}

ActivityCalendar::~ActivityCalendar()
{
    if (m_refreshTimer) {
        m_refreshTimer->stop();
    }
    
    if (m_activityCycleTimer) {
        m_activityCycleTimer->stop();
    }
    
    // Cleanup Arduino connection
    if (m_serialPort && m_serialPort->isOpen()) {
        m_serialPort->close();
    }
}

void ActivityCalendar::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(12);
    m_mainLayout->setContentsMargins(16, 16, 16, 16);
    
    // Set minimum size for the entire widget
    setMinimumSize(1200, 800);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    setupControlsSection();
    
    // Create main content splitter
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal, this);
    mainSplitter->setChildrenCollapsible(false);
    mainSplitter->setHandleWidth(4);
    
    setupCalendarSection();
    setupStatisticsSection();
    
    mainSplitter->addWidget(m_calendarFrame);
    mainSplitter->addWidget(m_statisticsFrame);
    
    // Set specific sizes instead of just stretch factors
    QList<int> sizes;
    sizes << 800 << 300; // Calendar: 800px, Statistics: 300px
    mainSplitter->setSizes(sizes);
    
    m_mainLayout->addWidget(mainSplitter, 1); // Give it stretch factor
    
    setupDetailsSection();
    m_mainLayout->addWidget(m_detailsFrame, 0); // No stretch for details
    
    // Set initial selections
    m_calendar->setSelectedDate(m_currentDate);
    updateSelectedDateActivities(m_currentDate);
}

void ActivityCalendar::setupControlsSection()
{
    m_controlsFrame = new QFrame(this);
    m_controlsFrame->setObjectName("controlsFrame");
    m_controlsFrame->setMinimumHeight(60);
    m_controlsFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_topControlsLayout = new QHBoxLayout(m_controlsFrame);
    m_topControlsLayout->setSpacing(8);
    m_topControlsLayout->setContentsMargins(12, 8, 12, 8);
    
    // Navigation buttons
    m_previousButton = new QPushButton("◀ Previous", this);
    m_previousButton->setMinimumWidth(100);
    m_nextButton = new QPushButton("Next ▶", this);
    m_nextButton->setMinimumWidth(100);
    m_todayButton = new QPushButton("📅 Today", this);
    m_todayButton->setMinimumWidth(90);
    
    m_monthYearLabel = new QLabel(this);
    m_monthYearLabel->setAlignment(Qt::AlignCenter);
    m_monthYearLabel->setMinimumWidth(200);
    QFont labelFont = m_monthYearLabel->font();
    labelFont.setPointSize(16);
    labelFont.setBold(true);
    m_monthYearLabel->setFont(labelFont);
    
    // View mode combo
    m_viewModeCombo = new QComboBox(this);
    m_viewModeCombo->addItems({"Month View", "Week View", "Day View"});
    
    // Filters
    m_activityTypeFilter = new QComboBox(this);
    m_activityTypeFilter->addItems({"All Types", "Mini Hackathon Kids", "Event", "Group Class", 
                                   "Musique", "Workshop", "Aeronautics Workshop", "Cinema & Acting Lab", 
                                   "Art", "Sports & Fitness Program", "Special Events"});
    m_activityTypeFilter->setMinimumWidth(120);
    
    m_statusFilter = new QComboBox(this);
    m_statusFilter->addItems({"All Status", "Scheduled", "In Progress", "Completed", "Cancelled", "Postponed"});
    m_statusFilter->setMinimumWidth(120);
    
    // Action buttons
    m_refreshButton = new QPushButton("🔄 Refresh", this);
    m_refreshButton->setMinimumWidth(100);
    
    // Arduino LCD button (toggles between Connect/Disconnect)
    m_arduinoConnectButton = new QPushButton("🔌 Connect LCD", this);
    m_arduinoConnectButton->setMinimumWidth(130);
    
    // Arduino status label
    m_arduinoStatusLabel = new QLabel("LCD: Disconnected", this);
    m_arduinoStatusLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
    
    // LCD cycle delay control
    QLabel *cycleDelayLabel = new QLabel("⏱️ Cycle:", this);
    cycleDelayLabel->setToolTip("Delay between activities when multiple activities exist for a day");
    
    QSpinBox *cycleDelaySpinBox = new QSpinBox(this);
    cycleDelaySpinBox->setMinimum(2);
    cycleDelaySpinBox->setMaximum(30);
    cycleDelaySpinBox->setValue(5);
    cycleDelaySpinBox->setSuffix(" sec");
    cycleDelaySpinBox->setToolTip("Time to display each activity before switching to the next");
    cycleDelaySpinBox->setMinimumWidth(80);
    
    connect(cycleDelaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this](int value) {
        m_activityCycleTimer->setInterval(value * 1000);
        qDebug() << "📺 LCD activity cycle delay changed to" << value << "seconds";
    });
    
    // Layout controls
    m_topControlsLayout->addWidget(m_previousButton);
    m_topControlsLayout->addWidget(m_todayButton);
    m_topControlsLayout->addWidget(m_nextButton);
    m_topControlsLayout->addWidget(m_monthYearLabel);
    
    // Add view mode selector
    m_topControlsLayout->addSpacing(20);
    m_topControlsLayout->addWidget(m_viewModeCombo);
    
    m_topControlsLayout->addStretch();
    
    // Filters group
    m_topControlsLayout->addWidget(new QLabel("🔍 Filters:"));
    m_topControlsLayout->addWidget(m_activityTypeFilter);
    m_topControlsLayout->addWidget(m_statusFilter);
    m_topControlsLayout->addStretch();
    
    // Action buttons
    m_topControlsLayout->addWidget(m_refreshButton);
    
    m_topControlsLayout->addSpacing(20);
    
    // Arduino LCD controls
    m_topControlsLayout->addWidget(new QLabel("📺 LCD:"));
    m_topControlsLayout->addWidget(m_arduinoStatusLabel);
    m_topControlsLayout->addWidget(cycleDelayLabel);
    m_topControlsLayout->addWidget(cycleDelaySpinBox);
    m_topControlsLayout->addWidget(m_arduinoConnectButton);
    
    m_mainLayout->addWidget(m_controlsFrame);
}

void ActivityCalendar::setupCalendarSection()
{
    m_calendarFrame = new QFrame(this);
    m_calendarFrame->setObjectName("calendarFrame");
    m_calendarFrame->setMinimumSize(600, 350);
    m_calendarFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QVBoxLayout *calendarLayout = new QVBoxLayout(m_calendarFrame);
    calendarLayout->setContentsMargins(12, 12, 12, 12);
    
    m_calendar = new CustomCalendarWidget(this);
    m_calendar->setMinimumSize(550, 320);
    m_calendar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    calendarLayout->addWidget(m_calendar);
}

void ActivityCalendar::setupStatisticsSection()
{
    m_statisticsFrame = new QFrame(this);
    m_statisticsFrame->setObjectName("statisticsFrame");
    m_statisticsFrame->setMinimumWidth(300);
    m_statisticsFrame->setMaximumWidth(350);
    m_statisticsFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_statisticsLayout = new QVBoxLayout(m_statisticsFrame);
    m_statisticsLayout->setContentsMargins(12, 12, 12, 12);
    
    // Statistics group
    m_statsGroup = new QGroupBox("📊 Monthly Overview", this);
    QVBoxLayout *statsLayout = new QVBoxLayout(m_statsGroup);
    
    // Create statistics labels
    m_totalActivitiesLabel = new QLabel("Total Activities: 0", this);
    m_totalParticipantsLabel = new QLabel("👥 Total Participants: 0", this);
    m_completedActivitiesLabel = new QLabel("✅ Completed: 0", this);
    m_upcomingActivitiesLabel = new QLabel("⏳ Upcoming: 0", this);
    m_conflictsLabel = new QLabel("⚠️ Conflicts: 0", this);
    m_avgAttendanceLabel = new QLabel("📈 Avg Attendance: 0%", this);
    
    // Capacity progress bar
    m_capacityLabel = new QLabel("Overall Capacity:", this);
    m_capacityProgressBar = new QProgressBar(this);
    m_capacityProgressBar->setRange(0, 100);
    m_capacityProgressBar->setValue(0);
    
    // Add to layout
    statsLayout->addWidget(m_totalActivitiesLabel);
    statsLayout->addWidget(m_totalParticipantsLabel);
    statsLayout->addWidget(m_completedActivitiesLabel);
    statsLayout->addWidget(m_upcomingActivitiesLabel);
    statsLayout->addWidget(m_conflictsLabel);
    statsLayout->addWidget(m_avgAttendanceLabel);
    statsLayout->addSpacing(10);
    statsLayout->addWidget(m_capacityLabel);
    statsLayout->addWidget(m_capacityProgressBar);
    statsLayout->addStretch();
    
    m_statisticsLayout->addWidget(m_statsGroup);
}

void ActivityCalendar::setupDetailsSection()
{
    m_detailsFrame = new QFrame(this);
    m_detailsFrame->setObjectName("detailsFrame");
    m_detailsFrame->setMinimumHeight(280);
    m_detailsFrame->setMaximumHeight(350);
    m_detailsFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    m_detailsLayout = new QVBoxLayout(m_detailsFrame);
    m_detailsLayout->setContentsMargins(12, 12, 12, 12);
    
    // Selected date label
    m_selectedDateLabel = new QLabel(QString("📋 Selected Day: %1").arg(m_selectedDate.toString("dddd, MMMM d, yyyy")), this);
    QFont dateFont = m_selectedDateLabel->font();
    dateFont.setPointSize(14);
    dateFont.setBold(true);
    m_selectedDateLabel->setFont(dateFont);
    
    // Activities scroll area
    m_activitiesScrollArea = new QScrollArea(this);
    m_activitiesScrollArea->setWidgetResizable(true);
    m_activitiesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_activitiesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    m_activitiesContainer = new QWidget();
    m_activitiesContainerLayout = new QHBoxLayout(m_activitiesContainer);
    m_activitiesContainerLayout->setSpacing(16);
    m_activitiesContainerLayout->setContentsMargins(12, 12, 12, 12);
    
    m_activitiesScrollArea->setWidget(m_activitiesContainer);
    
    // Ensure scroll area and container are visible
    m_activitiesScrollArea->setVisible(true);
    m_activitiesContainer->setVisible(true);
    
    m_detailsLayout->addWidget(m_selectedDateLabel);
    m_detailsLayout->addWidget(m_activitiesScrollArea);
}

void ActivityCalendar::applyStyles()
{
    // Apply consistent styling
    QString frameStyle = 
        "QFrame#controlsFrame, QFrame#calendarFrame, QFrame#statisticsFrame, QFrame#detailsFrame {"
        "    background-color: white;"
        "    border: 2px solid #16a5b3;"
        "    border-radius: 12px;"
        "    padding: 8px;"
        "}"
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #e0e4e7;"
        "    border-radius: 8px;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px 0 5px;"
        "}";
    
    setStyleSheet(frameStyle);
    
    // Apply specific styling to calendar widget to fix year/month editing
    QString calendarStyle = 
        "QCalendarWidget QWidget {"
        "    background-color: white;"
        "}"
        "QCalendarWidget QAbstractItemView {"
        "    background-color: white;"
        "    selection-background-color: #16a5b3;"
        "    selection-color: white;"
        "}"
        "QCalendarWidget QWidget#qt_calendar_navigationbar {"
        "    background-color: #f8f9fa;"
        "    border-bottom: 1px solid #e0e4e7;"
        "}"
        "QCalendarWidget QToolButton {"
        "    background-color: transparent;"
        "    border: 1px solid transparent;"
        "    border-radius: 4px;"
        "    padding: 4px 8px;"
        "    margin: 2px;"
        "    color: #2c3e50;"
        "    font-weight: 500;"
        "}"
        "QCalendarWidget QToolButton:hover {"
        "    background-color: rgba(22, 165, 179, 0.1);"
        "    border-color: #16a5b3;"
        "}"
        "QCalendarWidget QToolButton:pressed {"
        "    background-color: rgba(22, 165, 179, 0.2);"
        "}"
        "QCalendarWidget QSpinBox {"
        "    background-color: white;"
        "    border: 1px solid #e0e4e7;"
        "    border-radius: 4px;"
        "    padding: 4px 8px;"
        "    margin: 2px;"
        "    color: #2c3e50;"
        "    font-weight: 500;"
        "    min-width: 60px;"
        "}"
        "QCalendarWidget QSpinBox:focus {"
        "    border-color: #16a5b3;"
        "    background-color: white;"
        "}"
        "QCalendarWidget QSpinBox::up-button,"
        "QCalendarWidget QSpinBox::down-button {"
        "    background-color: transparent;"
        "    border: none;"
        "    width: 16px;"
        "}"
        "QCalendarWidget QSpinBox::up-arrow,"
        "QCalendarWidget QSpinBox::down-arrow {"
        "    width: 10px;"
        "    height: 10px;"
        "}"
        "QCalendarWidget QHeaderView::section {"
        "    background-color: #f8f9fa;"
        "    border: none;"
        "    padding: 8px;"
        "    font-weight: 600;"
        "    color: #2c3e50;"
        "}"
        "QCalendarWidget QTableView {"
        "    background-color: white;"
        "    gridline-color: #e0e4e7;"
        "    alternate-background-color: #f8f9fa;"
        "}";
    
    m_calendar->setStyleSheet(calendarStyle);
    
    // Style buttons with teal theme
    QString buttonStyle = 
        "QPushButton {"
        "    background-color: rgba(22, 165, 179, 0.10);"
        "    color: #2c3e50;"
        "    border: 1.5px solid rgba(22, 165, 179, 0.65);"
        "    padding: 8px 16px;"
        "    border-radius: 8px;"
        "    font-weight: 500;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(22, 165, 179, 0.18);"
        "    border-color: #16a5b3;"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(22, 165, 179, 0.26);"
        "}";
    
    // Apply to all buttons
    m_previousButton->setStyleSheet(buttonStyle);
    m_nextButton->setStyleSheet(buttonStyle);
    m_todayButton->setStyleSheet(buttonStyle);
    m_refreshButton->setStyleSheet(buttonStyle);
    m_arduinoConnectButton->setStyleSheet(buttonStyle);
    
    // Style combo boxes
    QString comboStyle = 
        "QComboBox {"
        "    background-color: white;"
        "    border: 1px solid #e0e4e7;"
        "    border-radius: 6px;"
        "    padding: 6px 12px;"
        "    min-width: 80px;"
        "}"
        "QComboBox:hover {"
        "    border-color: #16a5b3;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "}"
        "QComboBox::down-arrow {"
        "    image: none;"
        "    border: none;"
        "}";
    
    m_viewModeCombo->setStyleSheet(comboStyle);
    m_activityTypeFilter->setStyleSheet(comboStyle);
    m_statusFilter->setStyleSheet(comboStyle);
}

void ActivityCalendar::connectSignals()
{
    // Calendar signals
    connect(m_calendar, &CustomCalendarWidget::dayClicked, this, &ActivityCalendar::onDateSelected);
    connect(m_calendar, &QCalendarWidget::currentPageChanged, this, &ActivityCalendar::onMonthChanged);
    
    // Navigation buttons
    connect(m_previousButton, &QPushButton::clicked, this, &ActivityCalendar::onPreviousMonthClicked);
    connect(m_nextButton, &QPushButton::clicked, this, &ActivityCalendar::onNextMonthClicked);
    connect(m_todayButton, &QPushButton::clicked, this, &ActivityCalendar::onTodayClicked);
    
    // View mode combo
    connect(m_viewModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ActivityCalendar::onViewModeChanged);
    
    // Filter combos
    connect(m_activityTypeFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ActivityCalendar::onFilterChanged);
    connect(m_activityTypeFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ActivityCalendar::onFilterChanged);
    connect(m_statusFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ActivityCalendar::onFilterChanged);
    
    // Action buttons
    connect(m_refreshButton, &QPushButton::clicked, this, &ActivityCalendar::onRefreshClicked);
    
    // Arduino LCD button (handles both connect and disconnect)
    connect(m_arduinoConnectButton, &QPushButton::clicked, this, &ActivityCalendar::onArduinoToggleClicked);
}

void ActivityCalendar::loadActivitiesFromDatabase()
{
    qDebug() << "📅 Loading activities from database...";
    
    m_activities.clear();
    
    // Check if database connection is available
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "❌ Database connection is not open!";
        return;
    }
    
    try {
        QSqlQuery query;
        
        // Load all activities from database (no date filtering for now)
        
        // Query to load actual activities from database
        query.prepare(
            "SELECT ID_A, ACTIVITY_TYPE, EVENT_DATE, EVENT_TIME, RESPONSIBLE, "
            "AGE_REQUIREMENT, STATUS, DESCRIPTION, CAPACITY "
            "FROM SUMMERCLUB.ACTIVITIES "
            "ORDER BY EVENT_DATE, EVENT_TIME"
        );
        
        qDebug() << "📅 Querying all activities from database...";
        
        if (query.exec()) {
            int activitiesFound = 0;
            while (query.next()) {
                activitiesFound++;
                ActivityCalendarItem activity;
                activity.activityId = query.value("ID_A").toInt();
                activity.type = query.value("ACTIVITY_TYPE").toString();
                activity.title = activity.type; // Use type as title
                
                QDate eventDate = query.value("EVENT_DATE").toDate();
                QVariant timeVariant = query.value("EVENT_TIME");
                
                // Handle different time formats
                QTime eventTime;
                if (timeVariant.canConvert<QDateTime>()) {
                    eventTime = timeVariant.toDateTime().time();
                } else if (timeVariant.canConvert<QTime>()) {
                    eventTime = timeVariant.toTime();
                } else {
                    // Try to parse as string (format like "20:03" or "00:33")
                    QString timeStr = timeVariant.toString();
                    eventTime = QTime::fromString(timeStr, "hh:mm");
                    if (!eventTime.isValid()) {
                        eventTime = QTime::fromString(timeStr, "h:mm");
                    }
                    if (!eventTime.isValid()) {
                        eventTime = QTime(9, 0); // Default fallback
                    }
                }
                
                activity.startTime = QDateTime(eventDate, eventTime);
                activity.endTime = activity.startTime.addSecs(2 * 3600); // 2 hours duration
                
                activity.responsible = query.value("RESPONSIBLE").toString();
                activity.instructor = activity.responsible; // Use responsible as instructor
                activity.currentParticipants = 12; // Default participants for display
                activity.maxCapacity = query.value("CAPACITY").toInt();
                if (activity.maxCapacity == 0) activity.maxCapacity = 20; // Default capacity
                activity.priority = "Medium"; // Default priority since not in DB
                activity.status = query.value("STATUS").toString();
                if (activity.status.isEmpty()) activity.status = "Scheduled";
                activity.location = "Summer Club"; // Default location since not in DB
                
                // Determine indicator color based on activity type (use existing method)
                activity.indicatorColor = m_calendar->getActivityColor(activity.type);
                
                m_activities[eventDate].append(activity);
                
                qDebug() << "📅 Loaded activity:" << activity.activityId << "-" << activity.type 
                         << "on" << eventDate.toString() << "at" << eventTime.toString()
                         << "by" << activity.responsible << "status:" << activity.status;
            }
            
            qDebug() << "✅ Loaded" << activitiesFound << "activities from database";
            qDebug() << "📊 Activities distributed across" << m_activities.size() << "days";
            
            // Show message if no activities found
            if (activitiesFound == 0) {
                qDebug() << "⚠️ No activities found in database";
            }
            
            // Update calendar display
            m_calendar->setActivities(m_activities);
            m_calendar->update();
            m_calendar->repaint(); // Force immediate repaint
            updateStatistics();
            updateSelectedDateActivities(m_selectedDate);
            
        } else {
            qDebug() << "❌ Failed to load activities:" << query.lastError().text();
            qDebug() << "📝 Query was:" << query.lastQuery();
            
            // Try a simple query to check if any activities exist at all
            QSqlQuery testQuery;
            testQuery.prepare("SELECT COUNT(*) as total FROM SUMMERCLUB.ACTIVITIES");
            if (testQuery.exec() && testQuery.next()) {
                int totalActivities = testQuery.value("total").toInt();
                qDebug() << "📊 Total activities in database:" << totalActivities;
            }
        }
        
    } catch (const std::exception& e) {
        qDebug() << "❌ Exception loading activities:" << e.what();
    }
}

void ActivityCalendar::onDateSelected(const QDate &date)
{
    m_selectedDate = date;
    qDebug() << "📅 Date selected:" << date.toString();
    
    // If this date is outside our loaded range, reload activities
    QDate currentMonthStart = QDate(m_currentDate.year(), m_currentDate.month(), 1);
    QDate loadedStart = currentMonthStart.addMonths(-2);
    QDate loadedEnd = currentMonthStart.addMonths(3).addDays(-1);
    
    if (date < loadedStart || date > loadedEnd) {
        qDebug() << "🔄 Selected date outside loaded range, reloading activities...";
        m_currentDate = QDate(date.year(), date.month(), 1);
        loadActivitiesFromDatabase();
    } else {
        updateSelectedDateActivities(date);
    }
    
    // Send selected date activities to Arduino LCD
    if (m_arduinoConnected) {
        sendActivityToArduino(date);
    }
}

void ActivityCalendar::onMonthChanged(int year, int month)
{
    m_currentDate = QDate(year, month, 1);
    m_monthYearLabel->setText(m_currentDate.toString("MMMM yyyy"));
    
    // Reload activities for new month
    loadActivitiesFromDatabase();
    
    qDebug() << "📅 Month changed to:" << m_currentDate.toString("MMMM yyyy");
}

void ActivityCalendar::onFilterChanged()
{
    applyFilters();
    qDebug() << "🔍 Filters applied";
}

void ActivityCalendar::onViewModeChanged()
{
    // TODO: Implement different view modes (Week, Day)
    qDebug() << "👁️ View mode changed";
}

void ActivityCalendar::onTodayClicked()
{
    QDate today = QDate::currentDate();
    m_calendar->setSelectedDate(today);
    m_selectedDate = today;
    
    // If today is in a different month, navigate there
    if (today.month() != m_currentDate.month() || today.year() != m_currentDate.year()) {
        m_currentDate = today;
        m_calendar->setCurrentPage(today.year(), today.month());
    }
    
    updateSelectedDateActivities(today);
    qDebug() << "📅 Navigated to today:" << today.toString();
}

void ActivityCalendar::onPreviousMonthClicked()
{
    QDate previousMonth = m_currentDate.addMonths(-1);
    m_calendar->setCurrentPage(previousMonth.year(), previousMonth.month());
}

void ActivityCalendar::onNextMonthClicked()
{
    QDate nextMonth = m_currentDate.addMonths(1);
    m_calendar->setCurrentPage(nextMonth.year(), nextMonth.month());
}

void ActivityCalendar::onRefreshClicked()
{
    loadActivitiesFromDatabase();
    updateStatistics();
    updateSelectedDateActivities(m_selectedDate);
    
    QMessageBox::information(this, "Calendar Refreshed", "Activity data has been refreshed from the database.");
}

void ActivityCalendar::updateSelectedDateActivities(const QDate &date)
{
    // Update selected date label
    m_selectedDateLabel->setText(QString("📋 Selected Day: %1").arg(date.toString("dddd, MMMM d, yyyy")));
    
    qDebug() << "📅 Updating activities for date:" << date.toString();
    qDebug() << "📊 Total days with activities:" << m_activities.keys().size();
    
    // Clear previous activities
    clearDetailsPanel();
    
    // Add activities for selected date
    if (m_activities.contains(date)) {
        const auto &activities = m_activities[date];
        qDebug() << "✅ Found" << activities.size() << "activities for" << date.toString();
        int addedCount = 0;
        for (const auto &activity : activities) {
            qDebug() << "🔍 Checking activity:" << activity.title << "Type:" << activity.type << "Priority:" << activity.priority << "Status:" << activity.status;
            qDebug() << "🔧 Current filters - Type:" << m_currentActivityTypeFilter << "Priority:" << m_currentPriorityFilter << "Status:" << m_currentStatusFilter;
            
            if (passesFilter(activity)) {
                addActivityToDetailsPanel(activity);
                addedCount++;
                qDebug() << "📋 Added activity:" << activity.title << "at" << activity.startTime.toString();
            } else {
                qDebug() << "❌ Activity filtered out:" << activity.title;
            }
        }
        qDebug() << "🎯 Total activities added to details panel:" << addedCount;
    } else {
        qDebug() << "⚠️ No activities found for" << date.toString();
        qDebug() << "📅 Available dates with activities:" << m_activities.keys();
    }
    
    // Add "Add New Activity" card
    ClickableFrame *addCard = new ClickableFrame();
    addCard->setObjectName("addActivityCard");
    addCard->setFixedSize(220, 160);
    addCard->setStyleSheet(
        "QFrame#addActivityCard {"
        "    background-color: rgba(22, 165, 179, 0.1);"
        "    border: 2px dashed #16a5b3;"
        "    border-radius: 8px;"
        "}"
        "QFrame#addActivityCard:hover {"
        "    background-color: rgba(22, 165, 179, 0.15);"
        "}"
    );
    
    QVBoxLayout *addLayout = new QVBoxLayout(addCard);
    QLabel *addIcon = new QLabel("➕", addCard);
    addIcon->setAlignment(Qt::AlignCenter);
    addIcon->setStyleSheet("font-size: 24px; color: #16a5b3;");
    
    QLabel *addText = new QLabel("Add New\nActivity", addCard);
    addText->setAlignment(Qt::AlignCenter);
    addText->setStyleSheet("color: #16a5b3; font-weight: bold;");
    
    addLayout->addWidget(addIcon);
    addLayout->addWidget(addText);
    
    // Make it clickable
    addCard->setCursor(Qt::PointingHandCursor);
    addCard->setToolTip("Click to add new activity");
    connect(addCard, &ClickableFrame::clicked, [this, date]() {
        addNewActivity(date);
    });
    
    m_activitiesContainerLayout->addWidget(addCard);
    m_activitiesContainerLayout->addStretch();
}

void ActivityCalendar::clearDetailsPanel()
{
    qDebug() << "🧹 Clearing details panel. Current widget count:" << m_activitiesContainerLayout->count();
    
    // Remove all activity cards except the container
    while (QLayoutItem *item = m_activitiesContainerLayout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    
    qDebug() << "✅ Details panel cleared. New widget count:" << m_activitiesContainerLayout->count();
}

void ActivityCalendar::addActivityToDetailsPanel(const ActivityCalendarItem &activity)
{
    qDebug() << "🔧 Creating activity card for:" << activity.title;
    
    QFrame *activityCard = new QFrame();
    activityCard->setObjectName("activityCard");
    activityCard->setFixedSize(220, 160);
    activityCard->setVisible(true);
    activityCard->setStyleSheet(
        "QFrame#activityCard {"
        "    background-color: white;"
        "    border: 2px solid #e0e4e7;"
        "    border-radius: 8px;"
        "    padding: 8px;"
        "}"
        "QFrame#activityCard:hover {"
        "    border-color: #16a5b3;"
        "    box-shadow: 0 2px 8px rgba(22, 165, 179, 0.15);"
        "}"
    );
    
    QVBoxLayout *cardLayout = new QVBoxLayout(activityCard);
    cardLayout->setSpacing(6);
    cardLayout->setContentsMargins(10, 10, 10, 10);
    
    // Activity header
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *typeIcon = new QLabel(QString(activity.indicatorColor.name()), activityCard);
    typeIcon->setStyleSheet(QString("background-color: %1; color: white; border-radius: 10px; padding: 2px 6px; font-size: 10px; font-weight: bold;").arg(activity.indicatorColor.name()));
    typeIcon->setText(activity.type.left(3).toUpper());
    
    QLabel *timeLabel = new QLabel(activity.startTime.toString("hh:mm"), activityCard);
    timeLabel->setStyleSheet("font-size: 11px; color: #7f8c8d;");
    
    headerLayout->addWidget(typeIcon);
    headerLayout->addStretch();
    headerLayout->addWidget(timeLabel);
    
    // Activity title
    QLabel *titleLabel = new QLabel(activity.title, activityCard);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 12px; color: #2c3e50;");
    titleLabel->setWordWrap(true);
    
    // Instructor/Responsible
    QLabel *instructorLabel = new QLabel(QString("👨‍🏫 %1").arg(activity.instructor), activityCard);
    instructorLabel->setStyleSheet("font-size: 10px; color: #7f8c8d;");
    
    // Participants
    QLabel *participantsLabel = new QLabel(QString("👥 %1/%2 registered").arg(activity.currentParticipants).arg(activity.maxCapacity), activityCard);
    participantsLabel->setStyleSheet("font-size: 10px; color: #7f8c8d;");
    
    // Status/Priority indicator
    QString statusColor = "#16a5b3";
    if (activity.priority == "High") statusColor = "#e74c3c";
    else if (activity.priority == "Medium") statusColor = "#f39c12";
    else if (activity.priority == "Low") statusColor = "#27ae60";
    
    QLabel *statusLabel = new QLabel(activity.status, activityCard);
    statusLabel->setStyleSheet(QString("background-color: %1; color: white; border-radius: 4px; padding: 1px 4px; font-size: 9px; font-weight: bold;").arg(statusColor));
    statusLabel->setAlignment(Qt::AlignCenter);
    
    cardLayout->addLayout(headerLayout);
    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(instructorLabel);
    cardLayout->addWidget(participantsLabel);
    cardLayout->addWidget(statusLabel);
    cardLayout->addStretch();
    
    m_activitiesContainerLayout->addWidget(activityCard);
    qDebug() << "✅ Activity card added to layout. Total widgets in layout:" << m_activitiesContainerLayout->count();
}

void ActivityCalendar::updateStatistics()
{
    // Calculate statistics for current month
    m_totalActivitiesCount = 0;
    m_totalParticipantsCount = 0;
    m_completedActivitiesCount = 0;
    m_upcomingActivitiesCount = 0;
    m_conflictsCount = 0;
    
    QDate currentDate = QDate::currentDate();
    int totalCapacity = 0;
    int usedCapacity = 0;
    
    // Iterate through all activities in current month
    QDate firstDayOfMonth(m_currentDate.year(), m_currentDate.month(), 1);
    QDate lastDayOfMonth = firstDayOfMonth.addMonths(1).addDays(-1);
    
    for (QDate date = firstDayOfMonth; date <= lastDayOfMonth; date = date.addDays(1)) {
        if (m_activities.contains(date)) {
            const auto &dayActivities = m_activities[date];
            
            for (const auto &activity : dayActivities) {
                m_totalActivitiesCount++;
                m_totalParticipantsCount += activity.currentParticipants;
                totalCapacity += activity.maxCapacity;
                usedCapacity += activity.currentParticipants;
                
                if (activity.status == "Completed") {
                    m_completedActivitiesCount++;
                } else if (activity.startTime.date() >= currentDate) {
                    m_upcomingActivitiesCount++;
                }
            }
            
            // Check for conflicts (overlapping activities)
            if (dayActivities.size() > 1) {
                for (int i = 0; i < dayActivities.size() - 1; ++i) {
                    for (int j = i + 1; j < dayActivities.size(); ++j) {
                        if (dayActivities[i].startTime < dayActivities[j].endTime &&
                            dayActivities[j].startTime < dayActivities[i].endTime) {
                            m_conflictsCount++;
                        }
                    }
                }
            }
        }
    }
    
    // Calculate average attendance rate
    if (totalCapacity > 0) {
        m_avgAttendanceRate = (static_cast<double>(usedCapacity) / totalCapacity) * 100.0;
    }
    
    // Update UI labels
    m_totalActivitiesLabel->setText(QString("📅 Total Activities: %1").arg(m_totalActivitiesCount));
    m_totalParticipantsLabel->setText(QString("👥 Total Participants: %1").arg(m_totalParticipantsCount));
    m_completedActivitiesLabel->setText(QString("✅ Completed: %1").arg(m_completedActivitiesCount));
    m_upcomingActivitiesLabel->setText(QString("⏳ Upcoming: %1").arg(m_upcomingActivitiesCount));
    m_conflictsLabel->setText(QString("⚠️ Conflicts: %1").arg(m_conflictsCount));
    m_avgAttendanceLabel->setText(QString("📈 Avg Attendance: %1%").arg(m_avgAttendanceRate, 0, 'f', 1));
    
    // Update capacity progress bar
    m_capacityProgressBar->setValue(static_cast<int>(m_avgAttendanceRate));
    
    // Update month year label
    m_monthYearLabel->setText(m_currentDate.toString("MMMM yyyy"));
    
    qDebug() << "📊 Statistics updated - Activities:" << m_totalActivitiesCount << "Participants:" << m_totalParticipantsCount;
}

void ActivityCalendar::applyFilters()
{
    // Get current filter values
    m_currentActivityTypeFilter = m_activityTypeFilter->currentText();
    m_currentStatusFilter = m_statusFilter->currentText();
    
    // Update calendar display and details panel
    updateSelectedDateActivities(m_selectedDate);
    
    // TODO: Could also filter the calendar indicators themselves
}

bool ActivityCalendar::passesFilter(const ActivityCalendarItem &activity) const
{
    // Check activity type filter
    if (m_currentActivityTypeFilter != "All Types" && activity.type != m_currentActivityTypeFilter) {
        qDebug() << "🚫 Activity filtered by TYPE - Expected:" << m_currentActivityTypeFilter << "Got:" << activity.type;
        return false;
    }
    
    // Check priority filter
    if (m_currentPriorityFilter != "All Priorities" && activity.priority != m_currentPriorityFilter) {
        qDebug() << "🚫 Activity filtered by PRIORITY - Expected:" << m_currentPriorityFilter << "Got:" << activity.priority;
        return false;
    }
    
    // Check status filter
    if (m_currentStatusFilter != "All Status" && activity.status != m_currentStatusFilter) {
        qDebug() << "🚫 Activity filtered by STATUS - Expected:" << m_currentStatusFilter << "Got:" << activity.status;
        return false;
    }
    
    qDebug() << "✅ Activity passes all filters:" << activity.title;
    return true;
}

void ActivityCalendar::addNewActivity(const QDate &date)
{
    // Emit signal to request switching to Add Activity tab with pre-filled date
    QDate targetDate = date.isValid() ? date : m_selectedDate;
    qDebug() << "🎯 Requesting add new activity for date:" << targetDate.toString();
    emit addNewActivityRequested(targetDate);
}

void ActivityCalendar::refreshCalendarData()
{
    loadActivitiesFromDatabase();
}

void ActivityCalendar::navigateToDate(const QDate &date)
{
    m_calendar->setSelectedDate(date);
    if (date.month() != m_currentDate.month() || date.year() != m_currentDate.year()) {
        m_calendar->setCurrentPage(date.year(), date.month());
    }
    updateSelectedDateActivities(date);
}

void ActivityCalendar::addSampleActivities()
{
    qDebug() << "Adding sample activities for testing...";
    
    // Create sample activities for the current month and the selected date
    QDate baseDate = QDate::currentDate();
    
    // Add activity for November 19, 2025 (the date you selected)
    ActivityCalendarItem hackathon;
    hackathon.activityId = 1001;
    hackathon.title = "Mini Hackathon Kids";
    hackathon.type = "Mini Hackathon Kids";
    hackathon.startTime = QDateTime(QDate(2025, 11, 19), QTime(10, 0));
    hackathon.endTime = hackathon.startTime.addSecs(3600 * 3); // 3 hours
    hackathon.instructor = "Tech Instructor";
    hackathon.responsible = "Tech Team";
    hackathon.currentParticipants = 12;
    hackathon.maxCapacity = 20;
    hackathon.priority = "High";
    hackathon.status = "Scheduled";
    hackathon.location = "Computer Lab";
    hackathon.indicatorColor = QColor("#3498db");
    
    // Aeronautics Workshop
    ActivityCalendarItem aero;
    aero.activityId = 1002;
    aero.title = "Aeronautics Workshop";
    aero.type = "Aeronautics Workshop";
    aero.startTime = QDateTime(baseDate.addDays(3), QTime(14, 30));
    aero.endTime = aero.startTime.addSecs(5400); // 1.5 hours
    aero.instructor = "Pilot Instructor";
    aero.responsible = "Aviation Team";
    aero.currentParticipants = 8;
    aero.maxCapacity = 15;
    aero.priority = "Medium";
    aero.status = "Scheduled";
    aero.location = "Workshop Room";
    aero.indicatorColor = QColor("#e74c3c");
    
    // Sports & Fitness Program
    ActivityCalendarItem sports;
    sports.activityId = 1003;
    sports.title = "Sports & Fitness Program";
    sports.type = "Sports & Fitness Program";
    sports.startTime = QDateTime(baseDate.addDays(7), QTime(16, 0));
    sports.endTime = sports.startTime.addSecs(7200); // 2 hours
    sports.instructor = "Coach Ahmed";
    sports.responsible = "Sports Team";
    sports.currentParticipants = 18;
    sports.maxCapacity = 25;
    sports.priority = "High";
    sports.status = "Scheduled";
    sports.location = "Sports Hall";
    sports.indicatorColor = QColor("#9b59b6");
    
    // Add activities to the map
    m_activities[hackathon.startTime.date()].append(hackathon);
    m_activities[aero.startTime.date()].append(aero);
    m_activities[sports.startTime.date()].append(sports);
    
    // Add Art activity
    ActivityCalendarItem art;
    art.activityId = 1004;
    art.title = "Art Workshop";
    art.type = "Art";
    art.startTime = QDateTime(baseDate.addDays(10), QTime(9, 0));
    art.endTime = art.startTime.addSecs(3600);
    art.instructor = "Art Teacher";
    art.responsible = "Creative Team";
    art.currentParticipants = 10;
    art.maxCapacity = 15;
    art.priority = "Medium";
    art.status = "Scheduled";
    art.location = "Art Studio";
    art.indicatorColor = QColor("#e67e22");
    
    m_activities[art.startTime.date()].append(art);
    
    qDebug() << "✅ Added" << 4 << "sample activities";
}

void ActivityCalendar::onActivityDoubleClicked(const QDate &date)
{
    // Handle double-click on activity - could open detailed view or edit dialog
    qDebug() << "Activity double-clicked for date:" << date.toString();
    
    if (m_activities.contains(date) && !m_activities[date].isEmpty()) {
        // For now, just show a message with activity details
        const auto &activities = m_activities[date];
        QString message = QString("Activities on %1:\n\n").arg(date.toString("dddd, MMMM d, yyyy"));
        
        for (const auto &activity : activities) {
            message += QString("• %1 (%2)\n  Time: %3\n  Instructor: %4\n  Participants: %5/%6\n\n")
                       .arg(activity.title)
                       .arg(activity.type)
                       .arg(activity.startTime.toString("hh:mm"))
                       .arg(activity.instructor)
                       .arg(activity.currentParticipants)
                       .arg(activity.maxCapacity);
        }
        
        QMessageBox::information(this, "Activity Details", message);
    }
}

void ActivityCalendar::onActivityActionTriggered()
{
    // Handle activity-related actions from context menu or toolbar
    qDebug() << "Activity action triggered";
    
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        QString actionText = action->text();
        qDebug() << "Action triggered:" << actionText;
        
        if (actionText.contains("Edit")) {
            // TODO: Implement edit activity dialog
            QMessageBox::information(this, "Edit Activity", "Edit activity functionality will be implemented here.");
        } else if (actionText.contains("Delete")) {
            // TODO: Implement delete activity confirmation
            QMessageBox::information(this, "Delete Activity", "Delete activity functionality will be implemented here.");
        } else if (actionText.contains("View")) {
            // TODO: Implement view activity details
            QMessageBox::information(this, "View Activity", "View activity details functionality will be implemented here.");
        }
    }
}

// ============================================================================
// ARDUINO LCD COMMUNICATION METHODS
// ============================================================================

void ActivityCalendar::initializeArduinoConnection()
{
    m_serialPort = new QSerialPort(this);
    m_arduinoConnected = false;
    
    // Connect error handling
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &ActivityCalendar::onSerialErrorOccurred);
    
    qDebug() << "🔌 Arduino communication initialized";
}

void ActivityCalendar::onArduinoToggleClicked()
{
    if (m_arduinoConnected) {
        // Currently connected, so disconnect
        disconnectArduino();
        QMessageBox::information(this, "Arduino Connection", "Arduino LCD disconnected.");
    } else {
        // Currently disconnected, so connect
        onArduinoConnectClicked();
    }
}

void ActivityCalendar::onArduinoConnectClicked()
{
    if (m_serialPort && m_serialPort->isOpen()) {
        m_serialPort->close();
    }
    
    qDebug() << "=== Initializing Arduino Connection ===";
    qDebug() << "=== Scanning for Arduino Devices ===";
    
    // Find available Arduino ports
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    QString selectedPort;
    
    qDebug() << "Available ports found:" << availablePorts.size();
    
    // Look for Arduino (common VID/PID or description)
    for (const QSerialPortInfo &info : availablePorts) {
        QString description = info.description();
        QString manufacturer = info.manufacturer();
        
        qDebug() << "  Port:" << QString("\"%1\"").arg(info.portName());
        qDebug() << "    Description:" << QString("\"%1\"").arg(description);
        if (!manufacturer.isEmpty()) {
            qDebug() << "    Manufacturer:" << QString("\"%1\"").arg(manufacturer);
        }
        qDebug() << "    VID:" << info.vendorIdentifier() << "PID:" << info.productIdentifier();
        
        // Check if this is an Arduino
        if (description.toLower().contains("arduino") || 
            manufacturer.toLower().contains("arduino") ||
            description.toLower().contains("ch340") ||
            description.toLower().contains("cp2102") ||
            info.vendorIdentifier() == 0x2341 || // Arduino VID
            info.vendorIdentifier() == 0x1A86) { // CH340 VID
            selectedPort = info.portName();
            qDebug() << "    >>> ARDUINO FOUND! <<<";
        }
    }
    
    // If no Arduino found automatically, try first available port
    if (selectedPort.isEmpty() && !availablePorts.isEmpty()) {
        selectedPort = availablePorts.first().portName();
        qDebug() << "⚠️ No Arduino detected, trying first available port:" << selectedPort;
    }
    
    if (selectedPort.isEmpty()) {
        QMessageBox::warning(this, "Arduino Connection", 
            "No serial ports available. Please check Arduino connection and drivers.");
        return;
    }
    
    qDebug() << "\n=== Testing Port Availability ===";
    QSerialPort testPort;
    testPort.setPortName(selectedPort);
    
    // Configure test port settings first
    testPort.setBaudRate(QSerialPort::Baud9600);
    testPort.setDataBits(QSerialPort::Data8);
    testPort.setParity(QSerialPort::NoParity);
    testPort.setStopBits(QSerialPort::OneStop);
    testPort.setFlowControl(QSerialPort::NoFlowControl);
    
    if (!testPort.open(QIODevice::WriteOnly)) {
        QSerialPort::SerialPortError error = testPort.error();
        QString errorMsg = testPort.errorString();
        qDebug() << "❌ Port test failed. Error code:" << error << "Message:" << errorMsg;
        
        // Provide specific error messages based on error code
        switch (error) {
            case QSerialPort::PermissionError:
                QMessageBox::warning(this, "Port Access Error", 
                    QString("Cannot access %1: Port is being used by another program.\n\n"
                           "Please close:\n"
                           "• Arduino IDE Serial Monitor\n"
                           "• Any other serial terminal programs\n"
                           "• PuTTY or other terminal emulators\n"
                           "• Previous instances of this application\n\n"
                           "Then try connecting again.").arg(selectedPort));
                break;
            case QSerialPort::DeviceNotFoundError:
                QMessageBox::warning(this, "Arduino Connection", 
                    QString("Arduino not found on port %1.\n"
                           "Please check:\n"
                           "• Arduino is properly connected\n"
                           "• USB cable is working\n"
                           "• Arduino drivers are installed").arg(selectedPort));
                break;
            case QSerialPort::OpenError:
                QMessageBox::warning(this, "Connection Error", 
                    QString("Cannot open port %1.\n"
                           "Error: %2\n\n"
                           "Try:\n"
                           "• Disconnect and reconnect Arduino\n"
                           "• Use a different USB port\n"
                           "• Check Device Manager for conflicts").arg(selectedPort, errorMsg));
                break;
            default:
                QMessageBox::warning(this, "Connection Error", 
                    QString("Failed to access port %1.\n"
                           "Error: %2\n"
                           "Code: %3").arg(selectedPort, errorMsg).arg(error));
                break;
        }
        return;
    }
    
    testPort.close();
    qDebug() << "✅ Port availability test passed";
    
    // Configure serial port
    m_serialPort->setPortName(selectedPort);
    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    
    qDebug() << "\n=== Configuring Serial Connection ===";
    qDebug() << "Port:" << QString("\"%1\"").arg(selectedPort) << "opened successfully";
    qDebug() << "Baud Rate: 9600, Data Bits: 8, Parity: None, Stop Bits: 1";
    
    if (m_serialPort->open(QIODevice::WriteOnly)) {
        m_arduinoConnected = true;
        m_arduinoConnectButton->setText("🔌 Disconnect LCD");
        m_arduinoConnectButton->setEnabled(true);
        m_arduinoStatusLabel->setText("LCD: Connected");
        m_arduinoStatusLabel->setStyleSheet("color: #27ae60; font-weight: bold;");
        
        qDebug() << "✅ Arduino LCD connected on port:" << selectedPort;
        qDebug() << "Connection successful - sending initial data...";
        
        // Give Arduino time to initialize
        QThread::msleep(2000);
        
        // Send current selected date activities
        sendActivityToArduino(m_selectedDate);
        
        QMessageBox::information(this, "Arduino Connection", 
            QString("Successfully connected to Arduino LCD on port %1\n\n"
                   "The LCD should now display activity information when you select dates on the calendar.").arg(selectedPort));
    } else {
        QSerialPort::SerialPortError error = m_serialPort->error();
        QString errorMsg = m_serialPort->errorString();
        
        qDebug() << "❌ Failed to connect to Arduino. Error code:" << error << "Message:" << errorMsg;
        
        QMessageBox::critical(this, "Arduino Connection Failed", 
            QString("Failed to connect to Arduino on port %1\n\n"
                   "Error: %2\n"
                   "Error Code: %3\n\n"
                   "This should not happen since the port test passed.\n"
                   "Please try again or restart the application.")
            .arg(selectedPort, errorMsg).arg(error));
    }
}

void ActivityCalendar::disconnectArduino()
{
    if (m_serialPort && m_serialPort->isOpen()) {
        // Send clear command before disconnecting
        m_serialPort->write("CLEAR\\n");
        m_serialPort->flush();
        QThread::msleep(100); // Give time for the command to be processed
        
        m_serialPort->close();
    }
    
    // Stop activity cycling
    if (m_activityCycleTimer) {
        m_activityCycleTimer->stop();
    }
    
    m_arduinoConnected = false;
    m_arduinoConnectButton->setText("🔌 Connect LCD");
    m_arduinoConnectButton->setEnabled(true);
    m_arduinoStatusLabel->setText("LCD: Disconnected");
    m_arduinoStatusLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
    
    qDebug() << "🔌 Arduino LCD disconnected";
}

void ActivityCalendar::onSerialErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        qDebug() << "❌ Arduino serial error:" << error;
        
        if (m_arduinoConnected) {
            m_arduinoConnected = false;
            m_arduinoConnectButton->setText("🔌 Connect LCD");
            m_arduinoConnectButton->setEnabled(true);
            m_arduinoStatusLabel->setText("LCD: Error");
            m_arduinoStatusLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
            
            QString errorMsg = "Arduino connection error occurred.";
            switch (error) {
                case QSerialPort::DeviceNotFoundError:
                    errorMsg = "Arduino device not found. Please check connection.";
                    break;
                case QSerialPort::PermissionError:
                    errorMsg = "Permission error. Port may be in use by another application.";
                    break;
                case QSerialPort::WriteError:
                    errorMsg = "Failed to write data to Arduino.";
                    break;
                default:
                    errorMsg = QString("Arduino connection error: %1").arg(m_serialPort->errorString());
                    break;
            }
            
            QMessageBox::warning(this, "Arduino Error", errorMsg);
        }
    }
}

void ActivityCalendar::sendActivityToArduino(const QDate &date)
{
        if (!m_arduinoConnected || !m_serialPort || !m_serialPort->isOpen()) {
        return;
    }
    
    qDebug() << "📺 Sending activities for date" << date.toString() << "to Arduino LCD";
    
    // Stop any ongoing cycling
    m_activityCycleTimer->stop();
    
    if (m_activities.contains(date) && !m_activities[date].isEmpty()) {
        const auto &dayActivities = m_activities[date];
        
        // Store activities for cycling
        m_currentDayActivities = dayActivities;
        m_currentActivityIndex = 0;
        m_currentDisplayDate = date;
        
        // Send first activity immediately
        sendActivityDataToArduino(m_currentDayActivities[0]);
        
        // If multiple activities, start cycling timer
        if (dayActivities.size() > 1) {
            qDebug() << "📺 Multiple activities found (" << dayActivities.size() << "), starting cycle display";
            qDebug() << "📺 Activities will rotate every" << (m_activityCycleTimer->interval() / 1000) << "seconds";
            m_activityCycleTimer->start();
        } else {
            qDebug() << "📺 Single activity for this date";
        }
    } else {
        // No activities - clear cycling and show no activity message
        m_currentDayActivities.clear();
        m_currentActivityIndex = 0;
        sendNoActivityToArduino();
    }
}

void ActivityCalendar::sendActivityDataToArduino(const ActivityCalendarItem &activity)
{
    if (!m_serialPort || !m_serialPort->isOpen()) return;
    
    // Protocol: ACTIVITY:date|time|type|responsible|participants|capacity|status
    QString activityData = QString("ACTIVITY:%1|%2|%3|%4|%5|%6|%7\\n")
        .arg(activity.startTime.date().toString("yyyy-MM-dd"))
        .arg(activity.startTime.time().toString("hh:mm"))
        .arg(activity.type)
        .arg(activity.instructor.isEmpty() ? activity.responsible : activity.instructor)
        .arg(activity.currentParticipants)
        .arg(activity.maxCapacity)
        .arg(activity.status);
    
    // Avoid sending the same data repeatedly
    if (activityData == m_lastSentActivityData) {
        return;
    }
    
    qDebug() << "📺 Sending to Arduino:" << activityData.trimmed();
    
    QByteArray data = activityData.toUtf8();
    qint64 bytesWritten = m_serialPort->write(data);
    
    if (bytesWritten == -1) {
        qDebug() << "❌ Failed to write to Arduino:" << m_serialPort->errorString();
    } else {
        m_serialPort->flush(); // Ensure data is sent immediately
        m_lastSentActivityData = activityData;
        qDebug() << "✅ Sent" << bytesWritten << "bytes to Arduino LCD";
    }
}

void ActivityCalendar::sendNoActivityToArduino()
{
    if (!m_serialPort || !m_serialPort->isOpen()) return;
    
    QString noActivityMsg = "NO_ACTIVITY\\n";
    
    // Avoid sending the same message repeatedly
    if (noActivityMsg == m_lastSentActivityData) {
        return;
    }
    
    qDebug() << "📺 Sending 'No Activity' message to Arduino";
    
    QByteArray data = noActivityMsg.toUtf8();
    qint64 bytesWritten = m_serialPort->write(data);
    
    if (bytesWritten == -1) {
        qDebug() << "❌ Failed to write to Arduino:" << m_serialPort->errorString();
    } else {
        m_serialPort->flush();
        m_lastSentActivityData = noActivityMsg;
        qDebug() << "✅ Sent 'No Activity' message to Arduino LCD";
    }
}

void ActivityCalendar::onActivityCycleTimeout()
{
    // This slot is called by the timer to cycle through activities
    if (m_currentDayActivities.isEmpty() || !m_arduinoConnected) {
        m_activityCycleTimer->stop();
        return;
    }
    
    // Move to next activity
    m_currentActivityIndex++;
    if (m_currentActivityIndex >= m_currentDayActivities.size()) {
        m_currentActivityIndex = 0; // Loop back to first activity
    }
    
    // Send the current activity
    const ActivityCalendarItem &activity = m_currentDayActivities[m_currentActivityIndex];
    qDebug() << "🔄 Cycling to activity" << (m_currentActivityIndex + 1) << "of" << m_currentDayActivities.size();
    
    // Temporarily clear last sent data to force sending
    m_lastSentActivityData.clear();
    sendActivityDataToArduino(activity);
}
