#ifndef PAYMENT_H
#define PAYMENT_H

#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QFileInfo>
#include <QIcon>
#include <QDebug>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QBrush>
#include <QColor>
#include <QMap>

// Forward declaration
namespace Ui {
class EmployerAdmin;
}

class Payment : public QObject
{
    Q_OBJECT

public:
    explicit Payment(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Payment();

    // Setup functions
    void setupPaymentTable();
    
    // Payment management functions
    void onAddPayment();
    void onClearPaymentForm();
    void onPaymentSearchTextChanged();
    void onEditPayment(const QStringList &paymentData);
    void onDeletePayment(const QStringList &paymentData, int row);
    void populatePaymentStatistics();

private:
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    
    // Helper functions
    void sortTableByName(QTableWidget* table, int nameColumnIndex = 1);
    bool exportTableToCsv(QTableWidget* table, const QString& defaultName);
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);
};

#endif // PAYMENT_H