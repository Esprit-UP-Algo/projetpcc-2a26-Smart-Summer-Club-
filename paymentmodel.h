#ifndef PAYMENTMODEL_H
#define PAYMENTMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDate>
// upating tonight
class PaymentModel : public QObject
{
    Q_OBJECT
public:
    explicit PaymentModel(QObject *parent = nullptr);

    // Transaction control
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

    // CRUD operations
    bool addPayment(const QString &transactionId,
                    const QDate &date,
                    const QString &description,
                    const QString &type,
                    double amount,
                    const QString &method,
                    const QString &status,
                    const QString &memberId);

    bool updatePayment(const QString &transactionId,
                       const QDate &date,
                       const QString &description,
                       const QString &type,
                       double amount,
                       const QString &method,
                       const QString &status,
                       const QString &memberId);

    bool deletePayment(const QString &transactionId);

    // Retrieval
    QSqlQueryModel* getAllPayments();
    QSqlQueryModel* getPaymentById(const QString &transactionId);

    // Validation
    bool paymentExists(const QString &transactionId);

private:
    QSqlDatabase getDatabase();
};

#endif // PAYMENTMODEL_H

