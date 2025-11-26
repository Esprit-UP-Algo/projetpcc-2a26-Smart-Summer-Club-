#include "paymentmodel.h"
#include "employeelogspanel.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

PaymentModel::PaymentModel(QObject *parent)
    : QObject(parent)
{
}

bool PaymentModel::beginTransaction()
{
    QSqlDatabase db = getDatabase();
    if (db.isOpen())
        return db.transaction();

    qDebug() << "Database not open for transaction";
    return false;
}

bool PaymentModel::commitTransaction()
{
    QSqlDatabase db = getDatabase();
    if (db.isOpen())
        return db.commit();

    return false;
}

bool PaymentModel::rollbackTransaction()
{
    QSqlDatabase db = getDatabase();
    if (db.isOpen())
        return db.rollback();

    return false;
}

bool PaymentModel::addPayment(const QString &transactionId,
                              const QDate &date,
                              const QString &description,
                              const QString &type,
                              double amount,
                              const QString &method,
                              const QString &status,
                              const QString &memberId)
{
    QSqlQuery query;

    query.prepare("INSERT INTO transactions (ID_TR, transaction_id, payment_date, description, "
                  "payment_type, amount, payment_method, status, member_id) "
                  "VALUES (TRANSACTION_ID_SEQ.NEXTVAL, :transaction_id, TO_DATE(:payment_date, 'YYYY-MM-DD'), "
                  ":description, :payment_type, :amount, :payment_method, :status, :member_id)");

    query.bindValue(":transaction_id", transactionId);
    query.bindValue(":payment_date", date.toString("yyyy-MM-dd"));
    query.bindValue(":description", description);
    query.bindValue(":payment_type", type);
    query.bindValue(":amount", amount);
    query.bindValue(":payment_method", method);
    query.bindValue(":status", status);
    query.bindValue(":member_id", memberId.isEmpty() ? QVariant() : memberId);

    bool success = query.exec();

    if (!success) {
        qDebug() << "Add payment error:" << query.lastError().text();
    } else {
        // Log the CREATE action
        QJsonObject paymentData;
        paymentData["transaction_id"] = transactionId;
        paymentData["payment_date"] = date.toString("yyyy-MM-dd");
        paymentData["description"] = description;
        paymentData["payment_type"] = type;
        paymentData["amount"] = QString::number(amount, 'f', 2);
        paymentData["payment_method"] = method;
        paymentData["status"] = status;
        paymentData["member_id"] = memberId.isEmpty() ? "NULL" : memberId;
        
        QJsonDocument doc(paymentData);
        EmployeeLogsPanel::logAction("CREATE", "Payment", transactionId, "", 
                                   doc.toJson(QJsonDocument::Compact), 
                                   QString("New payment added: %1 (%2)")
                                   .arg(transactionId, QString::number(amount, 'f', 2)));
    }

    return success;
}

bool PaymentModel::updatePayment(const QString &transactionId,
                                 const QDate &date,
                                 const QString &description,
                                 const QString &type,
                                 double amount,
                                 const QString &method,
                                 const QString &status,
                                 const QString &memberId)
{
    QSqlQuery query;

    query.prepare("UPDATE transactions SET payment_date = TO_DATE(:payment_date, 'YYYY-MM-DD'), "
                  "description = :description, payment_type = :payment_type, "
                  "amount = :amount, payment_method = :payment_method, "
                  "status = :status, member_id = :member_id "
                  "WHERE transaction_id = :transaction_id");

    query.bindValue(":transaction_id", transactionId);
    query.bindValue(":payment_date", date.toString("yyyy-MM-dd"));
    query.bindValue(":description", description);
    query.bindValue(":payment_type", type);
    query.bindValue(":amount", amount);
    query.bindValue(":payment_method", method);
    query.bindValue(":status", status);
    query.bindValue(":member_id", memberId.isEmpty() ? QVariant() : memberId);

    bool success = query.exec();

    if (!success) {
        qDebug() << "Update payment error:" << query.lastError().text();
    } else {
        // Log the UPDATE action
        QJsonObject afterData;
        afterData["transaction_id"] = transactionId;
        afterData["payment_date"] = date.toString("yyyy-MM-dd");
        afterData["description"] = description;
        afterData["payment_type"] = type;
        afterData["amount"] = QString::number(amount, 'f', 2);
        afterData["payment_method"] = method;
        afterData["status"] = status;
        afterData["member_id"] = memberId.isEmpty() ? "NULL" : memberId;
        
        QJsonDocument doc(afterData);
        EmployeeLogsPanel::logAction("UPDATE", "Payment", transactionId, "", 
                                   doc.toJson(QJsonDocument::Compact), 
                                   QString("Payment modified: %1 (%2)")
                                   .arg(transactionId, QString::number(amount, 'f', 2)));
    }

    return success;
}

bool PaymentModel::deletePayment(const QString &transactionId)
{
    // Get payment data before deletion for logging
    QJsonObject beforeData;
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM transactions WHERE transaction_id = :transaction_id");
    selectQuery.bindValue(":transaction_id", transactionId);
    
    if (selectQuery.exec() && selectQuery.next()) {
        beforeData["transaction_id"] = selectQuery.value("transaction_id").toString();
        beforeData["payment_date"] = selectQuery.value("payment_date").toString();
        beforeData["description"] = selectQuery.value("description").toString();
        beforeData["payment_type"] = selectQuery.value("payment_type").toString();
        beforeData["amount"] = selectQuery.value("amount").toString();
        beforeData["payment_method"] = selectQuery.value("payment_method").toString();
        beforeData["status"] = selectQuery.value("status").toString();
        beforeData["member_id"] = selectQuery.value("member_id").toString();
    }
    
    QSqlQuery query;
    query.prepare("DELETE FROM transactions WHERE transaction_id = :transaction_id");
    query.bindValue(":transaction_id", transactionId);

    bool success = query.exec();

    if (!success) {
        qDebug() << "Delete payment error:" << query.lastError().text();
    } else {
        // Log the DELETE action
        QJsonDocument doc(beforeData);
        EmployeeLogsPanel::logAction("DELETE", "Payment", transactionId, 
                                   doc.toJson(QJsonDocument::Compact), "", 
                                   QString("Payment deleted: %1 (%2)")
                                   .arg(transactionId, beforeData["amount"].toString()));
    }

    return success;
}

QSqlQueryModel* PaymentModel::getAllPayments()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT transaction_id, payment_date, description, "
                    "payment_type, amount, payment_method, status, member_id "
                    "FROM transactions ORDER BY payment_date DESC");

    if (model->lastError().isValid())
        qDebug() << "Get all payments error:" << model->lastError().text();

    return model;
}

QSqlQueryModel* PaymentModel::getPaymentById(const QString &transactionId)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryString = QString("SELECT transaction_id, payment_date, description, "
                                  "payment_type, amount, payment_method, status, member_id "
                                  "FROM transactions WHERE transaction_id = '%1'")
                              .arg(transactionId);

    model->setQuery(queryString);

    if (model->lastError().isValid())
        qDebug() << "Get payment by ID error:" << model->lastError().text();

    return model;
}

bool PaymentModel::paymentExists(const QString &transactionId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM transactions WHERE transaction_id = :transaction_id");
    query.bindValue(":transaction_id", transactionId);

    if (query.exec() && query.next())
        return query.value(0).toInt() > 0;

    return false;
}

QSqlDatabase PaymentModel::getDatabase()
{
    return QSqlDatabase::database();
}
