#include "paymentmodel.h"
#include "employeelogspanel.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlError>

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

    query.prepare("INSERT INTO SUMMERCLUB.TRANSACTIONS (ID_TR, TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, "
                  "PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID) "
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

    query.prepare("UPDATE SUMMERCLUB.TRANSACTIONS SET PAYMENT_DATE = TO_DATE(:payment_date, 'YYYY-MM-DD'), "
                  "DESCRIPTION = :description, PAYMENT_TYPE = :payment_type, "
                  "AMOUNT = :amount, PAYMENT_METHOD = :payment_method, "
                  "STATUS = :status, MEMBER_ID = :member_id "
                  "WHERE TRANSACTION_ID = :transaction_id");

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
    selectQuery.prepare("SELECT * FROM SUMMERCLUB.TRANSACTIONS WHERE TRANSACTION_ID = :transaction_id");
    selectQuery.bindValue(":transaction_id", transactionId);
    
    if (selectQuery.exec() && selectQuery.next()) {
        beforeData["transaction_id"] = selectQuery.value("TRANSACTION_ID").toString();
        beforeData["payment_date"] = selectQuery.value("PAYMENT_DATE").toString();
        beforeData["description"] = selectQuery.value("DESCRIPTION").toString();
        beforeData["payment_type"] = selectQuery.value("PAYMENT_TYPE").toString();
        beforeData["amount"] = selectQuery.value("AMOUNT").toString();
        beforeData["payment_method"] = selectQuery.value("PAYMENT_METHOD").toString();
        beforeData["status"] = selectQuery.value("STATUS").toString();
        beforeData["member_id"] = selectQuery.value("MEMBER_ID").toString();
    }
    
    QSqlQuery query;
    query.prepare("DELETE FROM SUMMERCLUB.TRANSACTIONS WHERE TRANSACTION_ID = :transaction_id");
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
    QSqlDatabase db = getDatabase();

    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "GetAllPayments: database not open:" << db.lastError().text();
        }
    }
    
    // Try with schema prefix first
    model->setQuery("SELECT TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, "
                    "PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID "
                    "FROM SUMMERCLUB.TRANSACTIONS ORDER BY PAYMENT_DATE DESC");

    if (model->lastError().isValid()) {
        qDebug() << "Get all payments error with schema:" << model->lastError().text();
        // Try without schema prefix as fallback
        model->setQuery("SELECT TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, "
                        "PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID "
                        "FROM TRANSACTIONS ORDER BY PAYMENT_DATE DESC");
        
        if (model->lastError().isValid()) {
            qDebug() << "Get all payments error without schema:" << model->lastError().text();
        } else {
            qDebug() << "Successfully loaded payments without schema prefix";
            while (model->canFetchMore()) model->fetchMore();
        }
    } else {
        qDebug() << "Successfully loaded payments with schema prefix";
        while (model->canFetchMore()) model->fetchMore();
    }
    
    qDebug() << "PaymentModel::getAllPayments() returning" << model->rowCount() << "rows";
    return model;
}

QSqlQueryModel* PaymentModel::getPaymentById(const QString &transactionId)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryString = QString("SELECT TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, "
                                  "PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID "
                                  "FROM SUMMERCLUB.TRANSACTIONS WHERE TRANSACTION_ID = '%1'")
                              .arg(transactionId);

    model->setQuery(queryString);

    if (model->lastError().isValid())
        qDebug() << "Get payment by ID error:" << model->lastError().text();

    return model;
}

bool PaymentModel::paymentExists(const QString &transactionId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SUMMERCLUB.TRANSACTIONS WHERE TRANSACTION_ID = :transaction_id");
    query.bindValue(":transaction_id", transactionId);

    if (query.exec() && query.next())
        return query.value(0).toInt() > 0;

    return false;
}

QSqlDatabase PaymentModel::getDatabase()
{
    return QSqlDatabase::database();
}
