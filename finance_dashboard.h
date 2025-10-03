#ifndef FINANCE_DASHBOARD_H
#define FINANCE_DASHBOARD_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QLabel>
#include <QPushButton>

class FinanceDashboard : public QMainWindow
{
    Q_OBJECT

public:
    FinanceDashboard(QWidget *parent = nullptr);
    ~FinanceDashboard();

private slots:
    void showAddPaymentPage();
    void showAddExpensePage();
    void showDashboardPage();
    void addPayment();
    void addExpense();
    void exportToCSV();

private:
    void updateSummary();

    QStackedWidget *stackedWidget;

    // Pages
    QWidget *addPaymentPage;
    QWidget *addExpensePage;
    QWidget *dashboardPage;

    // Add Payment widgets
    QLineEdit *paymentNameEdit;
    QLineEdit *paymentAmountEdit;
    QComboBox *paymentMethodCombo;
    QDateEdit *paymentDateEdit;
    QPushButton *submitPaymentBtn;

    // Add Expense widgets
    QLineEdit *expenseDescriptionEdit;
    QLineEdit *expenseAmountEdit;
    QDateEdit *expenseDateEdit;
    QPushButton *submitExpenseBtn;

    // Dashboard tables
    QTableWidget *paymentsTable;
    QTableWidget *expensesTable;

    // Top buttons
    QPushButton *btnAddPayment;
    QPushButton *btnAddExpense;
    QPushButton *btnDashboard;
    QPushButton *btnExportCSV;

    // Summary labels
    QLabel *totalIncomeLabel;
    QLabel *totalExpensesLabel;
    QLabel *balanceLabel;

    // Totals
    double totalIncome;
    double totalExpenses;
};

#endif // FINANCE_DASHBOARD_H
