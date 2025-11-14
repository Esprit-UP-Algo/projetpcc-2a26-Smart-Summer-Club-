#ifndef PAYMENT_H
#define PAYMENT_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
#include <QDate>
#include <QMap>
#include <QPair>
#include "paymentmodel.h"
// upating tonight
QT_BEGIN_NAMESPACE
namespace Ui {
class EmployerAdmin;
}
QT_END_NAMESPACE

class Payment : public QObject
{
    Q_OBJECT

public:
    explicit Payment(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Payment();

    void setupPaymentTable();
    void loadPaymentsFromDatabase();
    void refreshPaymentTable();
    void resetForm();
    void populatePaymentStatistics();
    void onClearPaymentForm();

public slots:
    void onAddPayment();
    void onUpdatePayment();
    void onDeletePayment(const QStringList &paymentData, int row);
    void onEditPayment(const QStringList &paymentData);
    void onPaymentSearchTextChanged();
    void validateMemberId();

private:
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    PaymentModel *paymentModel;
    bool memberIdValid;
    QString currentEditingTransactionId;
    bool isEditingMode;

    void setEditingMode(bool editing, const QString &transactionId = QString());

    QString generateTransactionId();
    bool isValidMemberId(const QString &memberId);

    // Sorting and exporting
    void sortTableByName(QTableWidget* table, int nameColumnIndex);
    bool exportTableToCsv(QTableWidget* table, const QString& defaultName);
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);
};

#endif // PAYMENT_H
