#include "finance_dashboard.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDate>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTabWidget>
#include <QGroupBox>
#include <QFrame>

class NumericItem : public QTableWidgetItem {
public:
    NumericItem(double value) { setData(Qt::EditRole, value); }
    bool operator< (const QTableWidgetItem &other) const override {
        return data(Qt::EditRole).toDouble() < other.data(Qt::EditRole).toDouble();
    }
};

FinanceDashboard::FinanceDashboard(QWidget *parent)
    : QMainWindow(parent), totalIncome(0), totalExpenses(0)
{
    // Set window properties
    setWindowTitle("Vibra Club - Finance Dashboard");
    resize(1200, 700);
    setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f8f9fa, stop:1 #e9ecef); font-family: 'Segoe UI', Arial, sans-serif;");

    // ---------------- Main Layout ----------------
    QWidget *centralWidget = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ---------------- Simplified Left Sidebar ----------------
    QWidget *sidebar = new QWidget();
    sidebar->setFixedWidth(220);
    sidebar->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop:0 #ffffff, stop:1 #118C8C);"
        "border-top-right-radius: 20px;"
        "border-bottom-right-radius: 20px;"
        "border-right: 3px solid #00ced1;"
        );

    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout->setSpacing(0);

    // Sidebar header with enhanced styling
    QWidget *sidebarHeader = new QWidget();
    sidebarHeader->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #00ced1, stop:1 #20b2aa);"
        "border-top-right-radius: 20px;"
        "padding: 25px 0px;"
        );
    QVBoxLayout *headerLayout = new QVBoxLayout(sidebarHeader);

    QLabel *sidebarTitle = new QLabel("VIBRA CLUB");
    sidebarTitle->setStyleSheet(
        "color: white;"
        "font-size: 18px;"
        "font-weight: bold;"
        "background: transparent;"
        "text-align: center;"
        );
    sidebarTitle->setAlignment(Qt::AlignCenter);


    headerLayout->addWidget(sidebarTitle);
    sidebarLayout->addWidget(sidebarHeader);

    // Only one Payment button in the sidebar
    QString menuItemStyle =
        "QPushButton {"
        "    background-color: transparent;"
        "    color: #2c3e50;"
        "    text-align: left;"
        "    padding: 18px 25px;"
        "    border: none;"
        "    font-weight: 500;"
        "    font-size: 14px;"
        "    border-radius: 0px;"
        "    border-left: 4px solid transparent;"
        "}"
        "QPushButton:hover {"
        "    background-color: #e0f7fa;"
        "    color: #008b8b;"
        "    border-right: 4px solid #00ced1;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #b2ebf2;"
        "}";

    QPushButton *btnPayment = new QPushButton("💰 Payment");
    QPushButton *btnExpenses = new QPushButton("Blank");
    QPushButton *btnReports = new QPushButton("Blank");
    QPushButton *btnSettings = new QPushButton("Blank");

    btnPayment->setStyleSheet(menuItemStyle);

    sidebarLayout->addWidget(btnPayment);
    sidebarLayout->addStretch();

    // Logout button with enhanced styling
    QPushButton *btnLogout = new QPushButton("🚪 Log Out");
    btnLogout->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 white, stop:1 #f8f9fa);"
        "    color: #e74c3c;"
        "    text-align: left;"
        "    padding: 18px 25px;"
        "    border: none;"
        "    font-weight: 500;"
        "    font-size: 14px;"
        "    border-bottom-right-radius: 20px;"
        "    border-top: 2px solid #e0f7fa;"
        "}"
        "QPushButton:hover {"
        "    background-color: #ffebee;"
        "    color: #c0392b;"
        "}"
        );
    sidebarLayout->addWidget(btnLogout);

    mainLayout->addWidget(sidebar);

    // ---------------- Enhanced Right Content Area ----------------
    QWidget *contentArea = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(contentArea);
    contentLayout->setContentsMargins(30, 30, 30, 30);
    contentLayout->setSpacing(20);

    // ---------------- Enhanced Top Navigation Bar ----------------
    QWidget *topNavWidget = new QWidget();
    topNavWidget->setStyleSheet("background: transparent;");
    QHBoxLayout *topNavLayout = new QHBoxLayout(topNavWidget);
    topNavLayout->setContentsMargins(0, 0, 0, 0);

    QString navButtonStyle =
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #00ced1, stop:1 #20b2aa);"
        "    color: white;"
        "    padding: 12px 25px;"
        "    border: none;"
        "    border-radius: 8px;"
        "    font-weight: bold;"
        "    font-size: 13px;"
        "    margin-right: 10px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #20b2aa, stop:1 #008b8b);"
        "    transform: translateY(-1px);"
        "}"
        "QPushButton:pressed {"
        "    background: #008b8b;"
        "}";

    btnDashboard = new QPushButton("📊 Dashboard");
    btnAddPayment = new QPushButton("💰 Add Payment");
    btnAddExpense = new QPushButton("💸 Add Expense");
    btnExportCSV = new QPushButton("📁 Export CSV");

    btnDashboard->setStyleSheet(navButtonStyle);
    btnAddPayment->setStyleSheet(navButtonStyle);
    btnAddExpense->setStyleSheet(navButtonStyle);
    btnExportCSV->setStyleSheet(navButtonStyle);

    topNavLayout->addWidget(btnDashboard);
    topNavLayout->addWidget(btnAddPayment);
    topNavLayout->addWidget(btnAddExpense);
    topNavLayout->addWidget(btnExportCSV);
    topNavLayout->addStretch();

    // Add welcome message
    QLabel *welcomeLabel = new QLabel("Finance Dashboard");
    welcomeLabel->setStyleSheet(
        "color: #2c3e50;"
        "font-size: 24px;"
        "font-weight: bold;"
        "background: transparent;"
        );
    contentLayout->addWidget(welcomeLabel);

    contentLayout->addWidget(topNavWidget);

    // ---------------- Enhanced Summary Cards ----------------
    QWidget *summaryWidget = new QWidget();
    summaryWidget->setStyleSheet("background: transparent;");
    QHBoxLayout *summaryLayout = new QHBoxLayout(summaryWidget);
    summaryLayout->setSpacing(20);

    QString cardStyle =
        "QLabel {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:1 #f8f9fa);"
        "    padding: 25px 20px;"
        "    border-radius: 15px;"
        "    border: 2px solid #e0f7fa;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    font-size: 14px;"
        "    min-height: 40px;"
        "}"
        "QLabel:hover {"
        "    border-color: #00ced1;"
        "    transform: translateY(-2px);"
        "}";

    totalIncomeLabel = new QLabel("💰 Total Income\n$0.00");
    totalExpensesLabel = new QLabel("💸 Total Expenses\n$0.00");
    balanceLabel = new QLabel("⚖️ Balance\n$0.00");

    totalIncomeLabel->setStyleSheet(cardStyle + "border-left: 5px solid #27ae60;");
    totalExpensesLabel->setStyleSheet(cardStyle + "border-left: 5px solid #e74c3c;");
    balanceLabel->setStyleSheet(cardStyle + "border-left: 5px solid #3498db;");

    totalIncomeLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    totalExpensesLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    balanceLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    totalIncomeLabel->setMinimumSize(200, 100);
    totalExpensesLabel->setMinimumSize(200, 100);
    balanceLabel->setMinimumSize(200, 100);

    summaryLayout->addWidget(totalIncomeLabel);
    summaryLayout->addWidget(totalExpensesLabel);
    summaryLayout->addWidget(balanceLabel);
    summaryLayout->addStretch();

    contentLayout->addWidget(summaryWidget);

    // ---------------- Stacked Widget for Pages ----------------
    stackedWidget = new QStackedWidget();
    stackedWidget->setStyleSheet("background: transparent;");
    contentLayout->addWidget(stackedWidget);

    mainLayout->addWidget(contentArea);
    setCentralWidget(centralWidget);

    // ---------------- Enhanced Add Payment Page ----------------
    addPaymentPage = new QWidget();
    addPaymentPage->setStyleSheet("background: transparent;");
    QVBoxLayout *paymentPageLayout = new QVBoxLayout(addPaymentPage);

    QGroupBox *paymentFormGroup = new QGroupBox("💳 Add New Payment");
    paymentFormGroup->setStyleSheet(
        "QGroupBox {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:1 #f8f9fa);"
        "    border: 2px solid #e0f7fa;"
        "    border-radius: 15px;"
        "    margin-top: 10px;"
        "    padding-top: 15px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    font-size: 16px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 15px;"
        "    padding: 0 10px 0 10px;"
        "    color: #00ced1;"
        "}"
        );

    QFormLayout *paymentForm = new QFormLayout(paymentFormGroup);
    paymentForm->setLabelAlignment(Qt::AlignRight);
    paymentForm->setSpacing(15);
    paymentForm->setContentsMargins(25, 25, 25, 25);

    paymentNameEdit = new QLineEdit();
    paymentAmountEdit = new QLineEdit();
    paymentMethodCombo = new QComboBox();
    paymentMethodCombo->addItems({"💵 Cash", "💳 Credit Card", "🏦 Bank Transfer", "📱 Mobile Payment"});
    paymentDateEdit = new QDateEdit();
    paymentDateEdit->setCalendarPopup(true);
    paymentDateEdit->setDate(QDate::currentDate());

    QString inputStyle =
        "QLineEdit, QComboBox, QDateEdit {"
        "    padding: 12px 15px;"
        "    border: 2px solid #16A6B3;"
        "    border-radius: 8px;"
        "    background-color: white;"
        "    font-size: 14px;"
        "    color: #2c3e50;"
        "}"
        "QLineEdit:focus, QComboBox:focus, QDateEdit:focus {"
        "    border-color: #00ced1;"
        "    background-color: #f0fdff;"
        "}";

    QString labelStyle =
        "QLabel {"
        "    color: #2c3e50;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    padding: 5px 0px;"
        "}";

    paymentNameEdit->setStyleSheet(inputStyle);
    paymentAmountEdit->setStyleSheet(inputStyle);
    paymentMethodCombo->setStyleSheet(inputStyle);
    paymentDateEdit->setStyleSheet(inputStyle);
    paymentDateEdit->setCalendarPopup(true);

    paymentForm->addRow(new QLabel("Payment Name:"), paymentNameEdit);
    paymentForm->addRow(new QLabel("Amount:"), paymentAmountEdit);
    paymentForm->addRow(new QLabel("Payment Method:"), paymentMethodCombo);
    paymentForm->addRow(new QLabel("Date:"), paymentDateEdit);

    submitPaymentBtn = new QPushButton("✅ Submit Payment");
    submitPaymentBtn->setStyleSheet(navButtonStyle + "padding: 15px 30px; font-size: 14px; margin-top: 10px;");
    paymentForm->addRow("", submitPaymentBtn);

    paymentPageLayout->addWidget(paymentFormGroup);

    // ---------------- Enhanced Add Expense Page ----------------
    addExpensePage = new QWidget();
    addExpensePage->setStyleSheet("background: transparent;");
    QVBoxLayout *expensePageLayout = new QVBoxLayout(addExpensePage);

    QGroupBox *expenseFormGroup = new QGroupBox("💸 Add New Expense");
    expenseFormGroup->setStyleSheet(
        "QGroupBox {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:1 #f8f9fa);"
        "    border: 2px solid #e0f7fa;"
        "    border-radius: 15px;"
        "    margin-top: 10px;"
        "    padding-top: 15px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    font-size: 16px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 15px;"
        "    padding: 0 10px 0 10px;"
        "    color: #00ced1;"
        "}"
        );

    QFormLayout *expenseForm = new QFormLayout(expenseFormGroup);
    expenseForm->setLabelAlignment(Qt::AlignRight);
    expenseForm->setSpacing(15);
    expenseForm->setContentsMargins(25, 25, 25, 25);

    expenseDescriptionEdit = new QLineEdit();
    expenseAmountEdit = new QLineEdit();
    expenseDateEdit = new QDateEdit();
    expenseDateEdit->setCalendarPopup(true);
    expenseDateEdit->setDate(QDate::currentDate());

    expenseDescriptionEdit->setStyleSheet(inputStyle);
    expenseAmountEdit->setStyleSheet(inputStyle);
    expenseDateEdit->setStyleSheet(inputStyle);

    expenseForm->addRow(new QLabel("Description:"), expenseDescriptionEdit);
    expenseForm->addRow(new QLabel("Amount:"), expenseAmountEdit);
    expenseForm->addRow(new QLabel("Date:"), expenseDateEdit);

    submitExpenseBtn = new QPushButton("✅ Submit Expense");
    submitExpenseBtn->setStyleSheet(navButtonStyle + "padding: 15px 30px; font-size: 14px; margin-top: 10px;");
    expenseForm->addRow("", submitExpenseBtn);

    expensePageLayout->addWidget(expenseFormGroup);

    // ---------------- Enhanced Dashboard Page ----------------
    dashboardPage = new QWidget();
    dashboardPage->setStyleSheet("background: transparent;");
    QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardPage);

    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->setStyleSheet(
        "QTabWidget::pane {"
        "    border: 2px solid #e0f7fa;"
        "    border-radius: 15px;"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:1 #f8f9fa);"
        "    top: -1px;"
        "}"
        "QTabBar::tab {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e0f7fa, stop:1 #b2ebf2);"
        "    border: 1px solid #b2ebf2;"
        "    padding: 12px 25px;"
        "    margin-right: 3px;"
        "    border-top-left-radius: 10px;"
        "    border-top-right-radius: 10px;"
        "    color: #2c3e50;"
        "    font-weight: bold;"
        "    font-size: 13px;"
        "}"
        "QTabBar::tab:selected {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:1 #f8f9fa);"
        "    border-bottom: none;"
        "    color: #00ced1;"
        "}"
        "QTabBar::tab:hover:!selected {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #b2ebf2, stop:1 #80deea);"
        "}"
        );

    // Enhanced table style
    QString tableStyle =
        "QTableWidget {"
        "    background-color: white;"
        "    border: 1px solid #e0f7fa;"
        "    border-radius: 10px;"
        "    gridline-color: #e0f7fa;"
        "    font-size: 13px;"
        "    outline: none;"
        "}"
        "QTableWidget::item {"
        "    padding: 12px 8px;"
        "    border-bottom: 1px solid #f0fdff;"
        "    color: #2c3e50;"
        "}"
        "QTableWidget::item:selected {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #00ced1, stop:1 #20b2aa);"
        "    color: white;"
        "}"
        "QTableWidget::item:hover {"
        "    background-color: #f0fdff;"
        "}"
        "QHeaderView::section {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #00ced1, stop:1 #20b2aa);"
        "    color: white;"
        "    padding: 15px 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "    font-size: 13px;"
        "}"
        "QTableWidget QScrollBar:vertical {"
        "    border: none;"
        "    background: #f0fdff;"
        "    width: 12px;"
        "    border-radius: 6px;"
        "}"
        "QTableWidget QScrollBar::handle:vertical {"
        "    background: #00ced1;"
        "    border-radius: 6px;"
        "    min-height: 20px;"
        "}"
        "QTableWidget QScrollBar::handle:vertical:hover {"
        "    background: #20b2aa;"
        "}";

    // Payments Tab
    QWidget *paymentsTab = new QWidget();
    paymentsTab->setStyleSheet("background: transparent;");
    QVBoxLayout *paymentsLayout = new QVBoxLayout(paymentsTab);
    paymentsTable = new QTableWidget();
    paymentsTable->setColumnCount(4);
    paymentsTable->setHorizontalHeaderLabels({"Name", "Amount", "Method", "Date"});
    paymentsTable->horizontalHeader()->setStretchLastSection(true);
    paymentsTable->setSortingEnabled(true);
    paymentsTable->setAlternatingRowColors(true);
    paymentsTable->setStyleSheet(tableStyle);
    paymentsLayout->addWidget(paymentsTable);
    tabWidget->addTab(paymentsTab, "💰 Payments");

    // Expenses Tab
    QWidget *expensesTab = new QWidget();
    expensesTab->setStyleSheet("background: transparent;");
    QVBoxLayout *expensesLayout = new QVBoxLayout(expensesTab);
    expensesTable = new QTableWidget();
    expensesTable->setColumnCount(3);
    expensesTable->setHorizontalHeaderLabels({"Description", "Amount", "Date"});
    expensesTable->horizontalHeader()->setStretchLastSection(true);
    expensesTable->setSortingEnabled(true);
    expensesTable->setAlternatingRowColors(true);
    expensesTable->setStyleSheet(tableStyle);
    expensesLayout->addWidget(expensesTable);
    tabWidget->addTab(expensesTab, "💸 Expenses");

    dashboardLayout->addWidget(tabWidget);

    // Add pages to stacked widget
    stackedWidget->addWidget(addPaymentPage);
    stackedWidget->addWidget(addExpensePage);
    stackedWidget->addWidget(dashboardPage);
    stackedWidget->setCurrentWidget(dashboardPage);

    // ---------------- Connections ----------------
    connect(btnAddPayment, &QPushButton::clicked, this, &FinanceDashboard::showAddPaymentPage);
    connect(btnAddExpense, &QPushButton::clicked, this, &FinanceDashboard::showAddExpensePage);
    connect(btnDashboard, &QPushButton::clicked, this, &FinanceDashboard::showDashboardPage);
    connect(btnPayment, &QPushButton::clicked, this, &FinanceDashboard::showAddPaymentPage);
    connect(submitPaymentBtn, &QPushButton::clicked, this, &FinanceDashboard::addPayment);
    connect(submitExpenseBtn, &QPushButton::clicked, this, &FinanceDashboard::addExpense);
    connect(btnExportCSV, &QPushButton::clicked, this, &FinanceDashboard::exportToCSV);
}

FinanceDashboard::~FinanceDashboard() {}

void FinanceDashboard::showAddPaymentPage() {
    stackedWidget->setCurrentWidget(addPaymentPage);
}

void FinanceDashboard::showAddExpensePage() {
    stackedWidget->setCurrentWidget(addExpensePage);
}

void FinanceDashboard::showDashboardPage() {
    stackedWidget->setCurrentWidget(dashboardPage);
}

void FinanceDashboard::addPayment() {
    QString name = paymentNameEdit->text();
    double amount = paymentAmountEdit->text().toDouble();
    QString method = paymentMethodCombo->currentText();
    QString date = paymentDateEdit->date().toString("yyyy-MM-dd");

    if(name.isEmpty() || amount <= 0) return;

    // Disable sorting temporarily
    paymentsTable->setSortingEnabled(false);

    int row = paymentsTable->rowCount();
    paymentsTable->insertRow(row);
    paymentsTable->setItem(row, 0, new QTableWidgetItem(name));
    paymentsTable->setItem(row, 1, new NumericItem(amount));
    paymentsTable->setItem(row, 2, new QTableWidgetItem(method));
    paymentsTable->setItem(row, 3, new QTableWidgetItem(date));

    // Re-enable sorting
    paymentsTable->setSortingEnabled(true);

    totalIncome += amount;
    updateSummary();

    paymentNameEdit->clear();
    paymentAmountEdit->clear();
}

void FinanceDashboard::addExpense() {
    QString description = expenseDescriptionEdit->text();
    double amount = expenseAmountEdit->text().toDouble();
    QString date = expenseDateEdit->date().toString("yyyy-MM-dd");

    if(description.isEmpty() || amount <= 0) return;

    // Disable sorting temporarily
    expensesTable->setSortingEnabled(false);

    int row = expensesTable->rowCount();
    expensesTable->insertRow(row);
    expensesTable->setItem(row, 0, new QTableWidgetItem(description));
    expensesTable->setItem(row, 1, new NumericItem(amount));
    expensesTable->setItem(row, 2, new QTableWidgetItem(date));

    // Re-enable sorting
    expensesTable->setSortingEnabled(true);

    totalExpenses += amount;
    updateSummary();

    expenseDescriptionEdit->clear();
    expenseAmountEdit->clear();
}

void FinanceDashboard::updateSummary() {
    totalIncomeLabel->setText("💰 Total Income\n$" + QString::number(totalIncome, 'f', 2));
    totalExpensesLabel->setText("💸 Total Expenses\n$" + QString::number(totalExpenses, 'f', 2));
    balanceLabel->setText("⚖️ Balance\n$" + QString::number(totalIncome - totalExpenses, 'f', 2));
}

void FinanceDashboard::exportToCSV() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export CSV", "", "*.csv");
    if(fileName.isEmpty()) return;

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out << "Type,Name/Description,Amount,Method,Date\n";

    // Payments
    for(int r=0; r<paymentsTable->rowCount(); ++r){
        QStringList rowData;
        rowData << "Payment";
        for(int c=0; c<paymentsTable->columnCount(); ++c){
            QTableWidgetItem *item = paymentsTable->item(r,c);
            rowData << (item ? item->text() : "");
        }
        out << rowData.join(",") << "\n";
    }

    // Expenses
    for(int r=0; r<expensesTable->rowCount(); ++r){
        QStringList rowData;
        rowData << "Expense";
        for(int c=0; c<expensesTable->columnCount(); ++c){
            QTableWidgetItem *item = expensesTable->item(r,c);
            rowData << (item ? item->text() : "");
        }
        rowData << "-"; // Method placeholder
        out << rowData.join(",") << "\n";
    }

    file.close();
}
