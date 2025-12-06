#include "payment.h"
#include "ui_employeradmin.h"
#include "paymentmodel.h"
#include <QPixmap>
#include <QFile>
#include <QStringConverter>
#include <QTextCursor>
#include <QDateTime>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QHBoxLayout>
#include <QPushButton>
#include <QBrush>
#include <QColor>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

Payment::Payment(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), ui(ui), parentWidget(parent), memberIdValid(false),
    currentEditingTransactionId(""), isEditingMode(false)
{
    paymentModel = new PaymentModel(this);
    setupPaymentTable();
    loadPaymentsFromDatabase();

    // Connect real-time validation
    connect(ui->paymentMemberEdit, &QLineEdit::textChanged,
            this, &Payment::validateMemberId);
}

Payment::~Payment()
{
    delete paymentModel;
}

void Payment::resetForm()
{
    // Clear editing mode first
    setEditingMode(false);

    // Clear the form
    onClearPaymentForm();
}

void Payment::onClearPaymentForm()
{
    ui->paymentTypeCombo->setCurrentIndex(0);
    ui->paymentDateEdit->setDate(QDate::currentDate());
    ui->paymentDescriptionEdit->clear();
    ui->paymentAmountSpinBox->setValue(0.00);
    ui->paymentMethodCombo->setCurrentIndex(0);
    ui->paymentMemberEdit->clear();
    ui->paymentStatusCombo->setCurrentIndex(0);

    // Reset the member edit field style
    ui->paymentMemberEdit->setStyleSheet("");
    memberIdValid = false;
}

void Payment::setupPaymentTable()
{
    QTableWidget* paymentTable = ui->paymentTable;

    // Configure table properties
    paymentTable->setRowCount(0);
    paymentTable->setColumnCount(9);

    QStringList headers;
    headers << "Transaction ID" << "Date" << "Description" << "Type" << "Amount" << "Method" << "Status" << "Member ID" << "Actions";
    paymentTable->setHorizontalHeaderLabels(headers);

    // Set column widths
    paymentTable->setColumnWidth(0, 100); // Transaction ID
    paymentTable->setColumnWidth(1, 100); // Date
    paymentTable->setColumnWidth(2, 200); // Description
    paymentTable->setColumnWidth(3, 80);  // Type
    paymentTable->setColumnWidth(4, 100); // Amount
    paymentTable->setColumnWidth(5, 120); // Method
    paymentTable->setColumnWidth(6, 80);  // Status
    paymentTable->setColumnWidth(7, 100); // Member ID
    paymentTable->setColumnWidth(8, 160); // Actions
}

void Payment::loadPaymentsFromDatabase()
{
    // Ensure database is open; if not, try to open or retry shortly
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Payment::loadPaymentsFromDatabase: DB not open yet; retrying shortly";
            QTimer::singleShot(300, this, &Payment::loadPaymentsFromDatabase);
            return;
        }
    }

    qDebug() << "Starting to load payments from database...";

    // Test database connection and table structure
    QSqlQuery structureQuery;
    if (structureQuery.exec("SELECT column_name FROM user_tab_columns WHERE table_name = 'TRANSACTIONS' ORDER BY column_id")) {
        qDebug() << "TRANSACTIONS table columns:";
        while (structureQuery.next()) {
            qDebug() << "  -" << structureQuery.value(0).toString();
        }
    }

    // First, let's test if there's any data in the transactions table at all
    QSqlQuery testQuery;
    testQuery.exec("SELECT COUNT(*) FROM SUMMERCLUB.TRANSACTIONS");
    if (testQuery.next()) {
        int totalRecords = testQuery.value(0).toInt();
        qDebug() << "Total records in SUMMERCLUB.TRANSACTIONS table:" << totalRecords;
    } else {
        qDebug() << "Failed to execute test query:" << testQuery.lastError().text();
        // Try without schema prefix as fallback
        testQuery.exec("SELECT COUNT(*) FROM TRANSACTIONS");
        if (testQuery.next()) {
            int totalRecords = testQuery.value(0).toInt();
            qDebug() << "Total records in TRANSACTIONS table (no schema):" << totalRecords;
        } else {
            qDebug() << "Failed to execute fallback test query:" << testQuery.lastError().text();
        }
    }

    QSqlQueryModel* model = paymentModel->getAllPayments();
    QTableWidget* paymentTable = ui->paymentTable;

    // Check if model is valid
    if (!model) {
        qDebug() << "Error: Failed to get payments model from database";
        return;
    }

    // Ensure the model fetches all available rows before inspecting rowCount
    while (model->canFetchMore()) model->fetchMore();

    qDebug() << "Model retrieved successfully. Row count:" << model->rowCount();

    // If no rows from model, try direct query as fallback
    if (model->rowCount() == 0) {
        qDebug() << "No rows from PaymentModel, trying direct SQL query...";
        QSqlQuery directQuery;
        // Try with schema prefix first
        directQuery.exec("SELECT TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID FROM SUMMERCLUB.TRANSACTIONS ORDER BY PAYMENT_DATE DESC");
        
        int directCount = 0;
        while (directQuery.next()) {
            directCount++;
        }
        
        if (directCount == 0) {
            // Try without schema prefix as fallback
            directQuery.exec("SELECT TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID FROM TRANSACTIONS ORDER BY PAYMENT_DATE DESC");
            while (directQuery.next()) {
                directCount++;
            }
        }
        
        qDebug() << "Direct query found" << directCount << "records";
        
        if (directCount > 0) {
            qDebug() << "Data exists but PaymentModel::getAllPayments() returned empty. Check PaymentModel implementation.";
        }
    }

    paymentTable->setRowCount(0);

    // Load existing transactions with error handling
    int loadedCount = 0;
    for (int i = 0; i < model->rowCount(); ++i) {
        try {
            QSqlRecord record = model->record(i);
            
            // Validate record data before processing
            if (record.isEmpty()) {
                qDebug() << "Warning: Empty record at row" << i << "- skipping";
                continue;
            }
            
            QString transactionId = record.value("transaction_id").toString();
            QString date = record.value("payment_date").toString();
            QString description = record.value("description").toString();
            QString type = record.value("payment_type").toString();
            QString amount = QString("$%1").arg(record.value("amount").toDouble(), 0, 'f', 2);
            QString method = record.value("payment_method").toString();
            QString status = record.value("status").toString();
            QString memberId = record.value("member_id").toString();
            
            // Validate essential fields
            if (transactionId.isEmpty()) {
                qDebug() << "Warning: Transaction with empty ID at row" << i << "- skipping";
                continue;
            }

            // Debug the loaded data
            qDebug() << "Loading payment row" << i << ":" << transactionId << date << description << type << amount;

            // Add new row to table
            int newRow = paymentTable->rowCount();
            paymentTable->insertRow(newRow);

            QStringList paymentData = {transactionId, date, description, type, amount, method, status, memberId};

        // Add data to table
        for (int j = 0; j < paymentData.size(); ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(paymentData[j]);

            // Color coding for amount
            if (j == 4) { // Amount column
                if (type == "Income") {
                    item->setForeground(QBrush(QColor("#2ecc71")));
                } else {
                    item->setForeground(QBrush(QColor("#e74c3c")));
                }
                item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }

            // Color coding for status
            if (j == 6) { // Status column
                if (status == "Completed") {
                    item->setForeground(QBrush(QColor("#2ecc71")));
                } else if (status == "Pending") {
                    item->setForeground(QBrush(QColor("#f39c12")));
                } else if (status == "Failed") {
                    item->setForeground(QBrush(QColor("#e74c3c")));
                }
            }

            paymentTable->setItem(newRow, j, item);
        }

        // Add action buttons
        QWidget* actionWidget = new QWidget();
        QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(5, 0, 5, 0);
        actionLayout->setSpacing(5);

        QPushButton* editButton = new QPushButton("Edit");
        QPushButton* deleteButton = new QPushButton("Delete");

        // Set icons for action buttons
        editButton->setIcon(QIcon(":/icons/icons/edit.png"));
        editButton->setIconSize(QSize(16, 16));
        deleteButton->setIcon(QIcon(":/icons/icons/delete.png"));
        deleteButton->setIconSize(QSize(16, 16));

        // Style the buttons to match employee table
        editButton->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
        deleteButton->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");

        connect(editButton, &QPushButton::clicked, [this, paymentData]() {
            onEditPayment(paymentData);
        });

        connect(deleteButton, &QPushButton::clicked, [this, paymentData, newRow]() {
            onDeletePayment(paymentData, newRow);
        });

        actionLayout->addWidget(editButton);
        actionLayout->addWidget(deleteButton);
        paymentTable->setCellWidget(newRow, 8, actionWidget);
        
        loadedCount++;
        
        } catch (const std::exception& e) {
            qDebug() << "Error loading payment record at row" << i << ":" << e.what();
            continue;
        } catch (...) {
            qDebug() << "Unknown error loading payment record at row" << i;
            continue;
        }
    }

    // If no transactions loaded, try direct SQL fallback
    if (loadedCount == 0) {
        qDebug() << "No data loaded via PaymentModel, attempting direct SQL fallback...";
        
        QSqlQuery fallbackQuery;
        // Try with schema prefix first
        fallbackQuery.prepare("SELECT TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID, CIN FROM SUMMERCLUB.TRANSACTIONS ORDER BY PAYMENT_DATE DESC");
        
        if (!fallbackQuery.exec()) {
            // Try without schema prefix as fallback
            qDebug() << "Schema query failed, trying without schema:" << fallbackQuery.lastError().text();
            fallbackQuery.prepare("SELECT TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID, CIN FROM TRANSACTIONS ORDER BY PAYMENT_DATE DESC");
        }
        
        if (fallbackQuery.exec()) {
            while (fallbackQuery.next()) {
                QString transactionId = fallbackQuery.value("TRANSACTION_ID").toString();
                QString date = fallbackQuery.value("PAYMENT_DATE").toString();
                QString description = fallbackQuery.value("DESCRIPTION").toString();
                QString type = fallbackQuery.value("PAYMENT_TYPE").toString();
                QString amount = QString("$%1").arg(fallbackQuery.value("AMOUNT").toDouble(), 0, 'f', 2);
                QString method = fallbackQuery.value("PAYMENT_METHOD").toString();
                QString status = fallbackQuery.value("STATUS").toString();
                QString memberId = fallbackQuery.value("MEMBER_ID").toString();
                
                // Debug each loaded record
                qDebug() << "Fallback loading:" << transactionId << date << description << type << amount;
                
                // Add new row to table
                int newRow = paymentTable->rowCount();
                paymentTable->insertRow(newRow);
                
                QStringList paymentData = {transactionId, date, description, type, amount, method, status, memberId};
                
                // Add data to table
                for (int j = 0; j < paymentData.size(); ++j) {
                    QTableWidgetItem* item = new QTableWidgetItem(paymentData[j]);
                    
                    // Color coding for amount
                    if (j == 4) { // Amount column
                        if (type == "Income") {
                            item->setForeground(QBrush(QColor("#2ecc71")));
                        } else {
                            item->setForeground(QBrush(QColor("#e74c3c")));
                        }
                        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                    }
                    
                    // Color coding for status
                    if (j == 6) { // Status column
                        if (status == "Completed") {
                            item->setForeground(QBrush(QColor("#2ecc71")));
                        } else if (status == "Pending") {
                            item->setForeground(QBrush(QColor("#f39c12")));
                        } else if (status == "Failed") {
                            item->setForeground(QBrush(QColor("#e74c3c")));
                        }
                    }
                    
                    paymentTable->setItem(newRow, j, item);
                }
                
                // Create action buttons (simplified version)
                QWidget* actionWidget = new QWidget();
                QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
                actionLayout->setContentsMargins(5, 0, 5, 0);
                actionLayout->setSpacing(5);

                QPushButton* editButton = new QPushButton("Edit");
                QPushButton* deleteButton = new QPushButton("Delete");

                editButton->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #e67e22; }");
                deleteButton->setStyleSheet("QPushButton { background-color: rgba(22, 165, 179, 0.10); color: #2c3e50; border: 1.5px solid rgba(22, 165, 179, 0.65); padding: 5px 10px; border-radius: 4px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");

                connect(editButton, &QPushButton::clicked, [this, paymentData]() {
                    onEditPayment(paymentData);
                });

                connect(deleteButton, &QPushButton::clicked, [this, paymentData, newRow]() {
                    onDeletePayment(paymentData, newRow);
                });

                actionLayout->addWidget(editButton);
                actionLayout->addWidget(deleteButton);
                paymentTable->setCellWidget(newRow, 8, actionWidget);
                
                loadedCount++;
            }
            qDebug() << "Fallback SQL loaded" << loadedCount << "payment transactions";
        } else {
            qDebug() << "Fallback SQL query failed:" << fallbackQuery.lastError().text();
        }
        
        // If still no data loaded and table is empty, offer to create sample data
        if (loadedCount == 0) {
            qDebug() << "No transaction data found. Table might be empty or there might be a connection issue.";
            qDebug() << "Consider adding some sample transactions to test the loading functionality.";
            
            // Try to insert a test record to verify the connection works
            QSqlQuery testInsert;
            testInsert.prepare("INSERT INTO SUMMERCLUB.TRANSACTIONS (TRANSACTION_ID, PAYMENT_DATE, DESCRIPTION, PAYMENT_TYPE, AMOUNT, PAYMENT_METHOD, STATUS, MEMBER_ID) VALUES (?, SYSDATE, ?, ?, ?, ?, ?, ?)");
            testInsert.addBindValue("TEST001");
            testInsert.addBindValue("Test Transaction - Loading Check");
            testInsert.addBindValue("Income");
            testInsert.addBindValue(100.00);
            testInsert.addBindValue("Cash");
            testInsert.addBindValue("Completed");
            testInsert.addBindValue("11111111");
            
            if (testInsert.exec()) {
                qDebug() << "Successfully inserted test transaction. Database connection is working.";
                // Remove the test record
                QSqlQuery cleanup;
                cleanup.prepare("DELETE FROM SUMMERCLUB.TRANSACTIONS WHERE TRANSACTION_ID = 'TEST001'");
                cleanup.exec();
            } else {
                qDebug() << "Failed to insert test transaction:" << testInsert.lastError().text();
            }
        }
    }

    // Log successful loading
    qDebug() << "Successfully loaded" << loadedCount << "payment transactions from database";
    qDebug() << "Total table rows after loading:" << paymentTable->rowCount();
    
    populatePaymentStatistics();
    
    delete model;
}

QString Payment::generateTransactionId()
{
    QSqlQuery query;

    // Get the maximum existing transaction_id from TRANSACTIONS table
    if (!query.exec("SELECT MAX(TO_NUMBER(REGEXP_SUBSTR(TRANSACTION_ID, '[0-9]+'))) FROM SUMMERCLUB.TRANSACTIONS WHERE TRANSACTION_ID LIKE 'TXN%'")) {
        // Try without schema as fallback
        query.exec("SELECT MAX(TO_NUMBER(REGEXP_SUBSTR(TRANSACTION_ID, '[0-9]+'))) FROM TRANSACTIONS WHERE TRANSACTION_ID LIKE 'TXN%'");
    }

    int maxId = 0;
    if (query.next() && !query.value(0).isNull()) {
        maxId = query.value(0).toInt();
    }

    int newIdNumber = maxId + 1;
    QString newId = QString("TXN%1").arg(newIdNumber, 3, 10, QChar('0'));

    qDebug() << "Max existing ID:" << maxId << "New ID:" << newId;

    return newId;
}

void Payment::setEditingMode(bool editing, const QString &transactionId)
{
    isEditingMode = editing;
    currentEditingTransactionId = transactionId;

    if (editing) {
        ui->addPaymentButton->setText("Update Payment");
        ui->addPaymentButton->setStyleSheet("background-color: #f39c12; color: white; font-weight: bold;");
    } else {
        ui->addPaymentButton->setText("Add Payment");
        ui->addPaymentButton->setStyleSheet(""); // Reset to default style
        currentEditingTransactionId.clear();
    }
}

// NEW: Reset form completely
void Payment::onAddPayment()
{
    // Check if we're in edit mode
    if (isEditingMode && !currentEditingTransactionId.isEmpty()) {
        onUpdatePayment();
        return;
    }

    // Validate required fields
    if (ui->paymentDescriptionEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(parentWidget, "Warning", "Please enter a description for the transaction.");
        return;
    }

    if (ui->paymentAmountSpinBox->value() <= 0) {
        QMessageBox::warning(parentWidget, "Warning", "Please enter a valid amount greater than 0.");
        return;
    }

    // **CORRECTED: Member CIN is MANDATORY**
    QString memberId = ui->paymentMemberEdit->text().trimmed();
    if (memberId.isEmpty()) {
        QMessageBox::warning(parentWidget, "Missing Member ID",
                             "Member ID (CIN) is required. Please enter a valid member CIN from the members list.");
        ui->paymentMemberEdit->setFocus();
        return;
    }

    if (!isValidMemberId(memberId)) {
        QMessageBox::warning(parentWidget, "Invalid Member ID",
                             QString("The member CIN '%1' does not exist in the database.\n\n"
                                     "Please enter a valid CIN from the members list made of 8 characters.\n\n").arg(memberId));
        ui->paymentMemberEdit->setFocus();
        return;
    }


    // Generate new transaction ID
    QString newTransactionId = generateTransactionId();

    // Get form data
    QString type = ui->paymentTypeCombo->currentText();
    QDate date = ui->paymentDateEdit->date();
    QString description = ui->paymentDescriptionEdit->text().trimmed();
    double amount = ui->paymentAmountSpinBox->value();
    QString method = ui->paymentMethodCombo->currentText();
    QString status = ui->paymentStatusCombo->currentText();

    // BEGIN TRANSACTION
    if (!paymentModel->beginTransaction()) {
        QMessageBox::critical(parentWidget, "Error", "Failed to start database transaction!");
        return;
    }

    try {
        // Add to database using prepared statement
        bool dbSuccess = paymentModel->addPayment(newTransactionId, date, description,
                                                  type, amount, method, status, memberId);

        if (!dbSuccess) {
            paymentModel->rollbackTransaction();
            QMessageBox::critical(parentWidget, "Database Error",
                                  "Failed to add payment to database!\nTransaction rolled back.");
            return;
        }

        // Commit transaction
        if (!paymentModel->commitTransaction()) {
            paymentModel->rollbackTransaction();
            QMessageBox::critical(parentWidget, "Error", "Failed to commit transaction!");
            return;
        }

        // Refresh table from database
        refreshPaymentTable();

        // Clear form
        resetForm();

        // Show success message
        QMessageBox::information(parentWidget, "Success",
                                 "Payment transaction added successfully to database!");

        // Switch to payment list tab
        ui->paymentTabWidget->setCurrentIndex(0);

    } catch (const std::exception& e) {
        paymentModel->rollbackTransaction();
        QMessageBox::critical(parentWidget, "Error",
                              QString("Transaction failed: %1").arg(e.what()));
    } catch (...) {
        paymentModel->rollbackTransaction();
        QMessageBox::critical(parentWidget, "Error", "Unknown error occurred during transaction!");
    }
}

// NEW: Update payment method
void Payment::onUpdatePayment()
{
    if (!isEditingMode || currentEditingTransactionId.isEmpty()) {
        QMessageBox::warning(parentWidget, "Warning", "No transaction selected for update.");
        return;
    }

    // Validation
    if (ui->paymentDescriptionEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(parentWidget, "Warning", "Please enter a description.");
        return;
    }

    if (ui->paymentAmountSpinBox->value() <= 0) {
        QMessageBox::warning(parentWidget, "Warning", "Please enter a valid amount.");
        return;
    }

    QString memberId = ui->paymentMemberEdit->text().trimmed();
    if (memberId.isEmpty()) {
        QMessageBox::warning(parentWidget, "Missing Member ID",
                             "Member ID (CIN) is required. Please enter a valid member CIN.");
        ui->paymentMemberEdit->setFocus();
        return;
    }

    if (!isValidMemberId(memberId)) {
        QMessageBox::warning(parentWidget, "Invalid Member ID",
                             QString("The member CIN '%1' does not exist in the database.\n\n"
                                     "Please enter a valid CIN from the members list.\n\n"
                                     "Valid CINs: 11111111, 12345678, 11112222, 11111115").arg(memberId));
        ui->paymentMemberEdit->setFocus();
        return;
    }

    // Get form data
    QDate date = ui->paymentDateEdit->date();
    QString description = ui->paymentDescriptionEdit->text().trimmed();
    QString type = ui->paymentTypeCombo->currentText();
    double amount = ui->paymentAmountSpinBox->value();
    QString method = ui->paymentMethodCombo->currentText();
    QString status = ui->paymentStatusCombo->currentText();

    // Begin transaction
    if (!paymentModel->beginTransaction()) {
        QMessageBox::critical(parentWidget, "Error", "Failed to start transaction!");
        return;
    }

    try {
        bool dbSuccess = paymentModel->updatePayment(currentEditingTransactionId, date,
                                                     description, type, amount, method,
                                                     status, memberId);

        if (!dbSuccess) {
            paymentModel->rollbackTransaction();
            QMessageBox::critical(parentWidget, "Error", "Failed to update payment!");
            return;
        }

        if (!paymentModel->commitTransaction()) {
            paymentModel->rollbackTransaction();
            QMessageBox::critical(parentWidget, "Error", "Failed to commit transaction!");
            return;
        }

        // Refresh and reset
        refreshPaymentTable();
        resetForm();

        QMessageBox::information(parentWidget, "Success", "Payment updated successfully!");
        ui->paymentTabWidget->setCurrentIndex(0);

    } catch (...) {
        paymentModel->rollbackTransaction();
        QMessageBox::critical(parentWidget, "Error", "Unknown error during update!");
    }
}

void Payment::refreshPaymentTable()
{
    loadPaymentsFromDatabase();
}

void Payment::onEditPayment(const QStringList &paymentData)
{
    if (paymentData.size() < 8) return;

    QString transactionId = paymentData[0];

    // Set editing mode
    setEditingMode(true, transactionId);

    // Switch to add payment tab
    ui->paymentTabWidget->setCurrentIndex(1);

    // Populate form with existing data
    QString type = paymentData[3];
    int typeIndex = ui->paymentTypeCombo->findText(type);
    if (typeIndex >= 0) ui->paymentTypeCombo->setCurrentIndex(typeIndex);

    QDate date = QDate::fromString(paymentData[1], "yyyy-MM-dd");
    if (date.isValid()) ui->paymentDateEdit->setDate(date);

    ui->paymentDescriptionEdit->setText(paymentData[2]);

    QString amountText = paymentData[4];
    amountText.remove("$");
    ui->paymentAmountSpinBox->setValue(amountText.toDouble());

    QString method = paymentData[5];
    int methodIndex = ui->paymentMethodCombo->findText(method);
    if (methodIndex >= 0) ui->paymentMethodCombo->setCurrentIndex(methodIndex);

    QString status = paymentData[6];
    int statusIndex = ui->paymentStatusCombo->findText(status);
    if (statusIndex >= 0) ui->paymentStatusCombo->setCurrentIndex(statusIndex);

    ui->paymentMemberEdit->setText(paymentData[7]);
}

void Payment::onDeletePayment(const QStringList &paymentData, int row)
{
    Q_UNUSED(row)

    QString transactionId = paymentData[0];
    QString description = paymentData[2];

    int result = QMessageBox::question(parentWidget, "Confirm Delete",
                                       QString("Are you sure you want to delete this payment transaction?\n\n"
                                               "Transaction ID: %1\n"
                                               "Description: %2").arg(transactionId, description),
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (result == QMessageBox::Yes) {
        // BEGIN TRANSACTION
        if (!paymentModel->beginTransaction()) {
            QMessageBox::critical(parentWidget, "Error", "Failed to start database transaction!");
            return;
        }

        try {
            bool dbSuccess = paymentModel->deletePayment(transactionId);

            if (!dbSuccess) {
                paymentModel->rollbackTransaction();
                QMessageBox::critical(parentWidget, "Database Error",
                                      "Failed to delete payment from database!\nTransaction rolled back.");
                return;
            }

            // Commit transaction
            if (!paymentModel->commitTransaction()) {
                paymentModel->rollbackTransaction();
                QMessageBox::critical(parentWidget, "Error", "Failed to commit transaction!");
                return;
            }

            // Refresh table from database
            refreshPaymentTable();

            QMessageBox::information(parentWidget, "Deleted", "Payment transaction deleted successfully from database!");

        } catch (const std::exception& e) {
            paymentModel->rollbackTransaction();
            QMessageBox::critical(parentWidget, "Error",
                                  QString("Transaction failed: %1").arg(e.what()));
        } catch (...) {
            paymentModel->rollbackTransaction();
            QMessageBox::critical(parentWidget, "Error", "Unknown error occurred during transaction!");
        }
    }
}

void Payment::populatePaymentStatistics()
{
    // Calculate totals from payment table
    QTableWidget* paymentTable = ui->paymentTable;
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    for (int i = 0; i < paymentTable->rowCount(); ++i) {
        QString typeText = paymentTable->item(i, 3)->text(); // Type column
        QString amountText = paymentTable->item(i, 4)->text(); // Amount column

        // Extract numeric value from amount (remove $ symbol)
        QString numericAmount = amountText;
        numericAmount.remove("$");
        double amount = numericAmount.toDouble();

        if (typeText == "Income") {
            totalIncome += amount;
        } else if (typeText == "Expense") {
            totalExpense += amount;
        }
    }

    double netBalance = totalIncome - totalExpense;

    // Update summary labels
    ui->totalIncomeValue->setText(QString("$%1").arg(totalIncome, 0, 'f', 2));
    ui->totalExpenseValue->setText(QString("$%1").arg(totalExpense, 0, 'f', 2));
    ui->netBalanceValue->setText(QString("$%1").arg(netBalance, 0, 'f', 2));

    // Color code net balance value text (keeping card white)
    if (netBalance >= 0) {
        ui->netBalanceValue->setStyleSheet("font-size: 20px; font-weight: bold; color: #2ecc71;");
    } else {
        ui->netBalanceValue->setStyleSheet("font-size: 20px; font-weight: bold; color: #e74c3c;");
    }

    // Populate payment method statistics
    QTableWidget* methodStatsTable = ui->paymentMethodStatsTable;
    QMap<QString, QPair<int, double>> methodStats; // method -> (count, total amount)

    for (int i = 0; i < paymentTable->rowCount(); ++i) {
        QString method = paymentTable->item(i, 5)->text(); // Method column
        QString amountText = paymentTable->item(i, 4)->text(); // Amount column

        QString numericAmount = amountText;
        numericAmount.remove("$");
        double amount = numericAmount.toDouble();

        if (methodStats.contains(method)) {
            methodStats[method].first += 1;
            methodStats[method].second += amount;
        } else {
            methodStats[method] = QPair<int, double>(1, amount);
        }
    }

    methodStatsTable->setRowCount(methodStats.size());
    int row = 0;
    double totalAmount = totalIncome + totalExpense;

    for (auto it = methodStats.begin(); it != methodStats.end(); ++it) {
        QString method = it.key();
        int count = it.value().first;
        double amount = it.value().second;
        double percentage = (totalAmount > 0) ? (amount / totalAmount) * 100.0 : 0.0;

        methodStatsTable->setItem(row, 0, new QTableWidgetItem(method));
        methodStatsTable->setItem(row, 1, new QTableWidgetItem(QString::number(count)));
        methodStatsTable->setItem(row, 2, new QTableWidgetItem(QString("$%1").arg(amount, 0, 'f', 2)));
        methodStatsTable->setItem(row, 3, new QTableWidgetItem(QString("%1%").arg(percentage, 0, 'f', 1)));

        row++;
    }

    // Populate recent payments table (last 10 transactions)
    QTableWidget* recentTable = ui->recentPaymentsTable;
    int recentCount = qMin(10, paymentTable->rowCount());
    recentTable->setRowCount(recentCount);

    for (int i = 0; i < recentCount; ++i) {
        // Copy data from main payment table (most recent first)
        int sourceRow = paymentTable->rowCount() - 1 - i;

        recentTable->setItem(i, 0, new QTableWidgetItem(paymentTable->item(sourceRow, 1)->text())); // Date
        recentTable->setItem(i, 1, new QTableWidgetItem(paymentTable->item(sourceRow, 2)->text())); // Description
        recentTable->setItem(i, 2, new QTableWidgetItem(paymentTable->item(sourceRow, 3)->text())); // Type

        // Amount with color coding
        QTableWidgetItem* amountItem = new QTableWidgetItem(paymentTable->item(sourceRow, 4)->text());
        QString type = paymentTable->item(sourceRow, 3)->text();
        if (type == "Income") {
            amountItem->setForeground(QBrush(QColor("#2ecc71")));
        } else {
            amountItem->setForeground(QBrush(QColor("#e74c3c")));
        }
        amountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        recentTable->setItem(i, 3, amountItem);

        // Status with color coding
        QTableWidgetItem* statusItem = new QTableWidgetItem(paymentTable->item(sourceRow, 6)->text());
        QString status = paymentTable->item(sourceRow, 6)->text();
        if (status == "Completed") {
            statusItem->setForeground(QBrush(QColor("#2ecc71")));
        } else if (status == "Pending") {
            statusItem->setForeground(QBrush(QColor("#f39c12")));
        } else if (status == "Failed") {
            statusItem->setForeground(QBrush(QColor("#e74c3c")));
        }
        recentTable->setItem(i, 4, statusItem);
    }
}

// Generic sort by Name column (default index 1)
void Payment::sortTableByName(QTableWidget* table, int nameColumnIndex)
{
    if (!table) return;

    // Toggle sorting order: if already sorted ascending, switch to descending
    static Qt::SortOrder lastOrder = Qt::AscendingOrder;
    lastOrder = (lastOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

    table->sortItems(nameColumnIndex, lastOrder);
}

// Export a QTableWidget to CSV (visible rows only, excluding action button cells)
bool Payment::exportTableToCsv(QTableWidget* table, const QString& defaultName)
{
    if (!table) return false;

    QString filter = "CSV Files (*.csv)";
    QString fileName = QFileDialog::getSaveFileName(parentWidget, tr("Export to CSV"), defaultName, filter);
    if (fileName.isEmpty()) return false;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(parentWidget, tr("Export Failed"), tr("Could not open file for writing."));
        return false;
    }

    QTextStream out(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    out.setEncoding(QStringConverter::Utf8);
#else
    out.setCodec("UTF-8");
#endif

    // Write header (exclude last column if it is Actions)
    int columns = table->columnCount();
    int headerColumns = columns;
    if (columns > 0) {
        QTableWidgetItem* lastHeader = table->horizontalHeaderItem(columns - 1);
        if (lastHeader && lastHeader->text().trimmed().compare("Actions", Qt::CaseInsensitive) == 0) {
            headerColumns = columns - 1;
        }
    }
    for (int c = 0; c < headerColumns; ++c) {
        QString h = table->horizontalHeaderItem(c) ? table->horizontalHeaderItem(c)->text() : QString();
        // CSV escaping: double any embedded quotes
        h.replace("\"", "\"\"");
        out << '"' << h << '"';
        if (c < headerColumns - 1) out << ',';
    }
    out << '\n';

    // Write data rows (visible only)
    for (int r = 0; r < table->rowCount(); ++r) {
        if (table->isRowHidden(r)) continue; // skip filtered-out rows
        for (int c = 0; c < headerColumns; ++c) {
            QTableWidgetItem* item = table->item(r, c);
            QString val = item ? item->text() : QString();
            // CSV escaping: double any embedded quotes
            val.replace("\"", "\"\"");
            out << '"' << val << '"';
            if (c < headerColumns - 1) out << ',';
        }
        out << '\n';
    }

    file.close();
    QMessageBox::information(parentWidget, tr("Export Successful"), tr("Data exported to CSV successfully."));
    return true;
}

bool Payment::exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title)
{
    if (!table) return false;

    QString filter = "PDF Files (*.pdf)";
    QString fileName = QFileDialog::getSaveFileName(parentWidget, tr("Export to PDF"), defaultName, filter);
    if (fileName.isEmpty()) return false;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QTextDocument document;
    QString html = "<html><head><style>";
    html += "table { border-collapse: collapse; width: 100%; font-family: Arial, sans-serif; }";
    html += "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }";
    html += "th { background-color: #f2f2f2; font-weight: bold; }";
    html += "tr:nth-child(even) { background-color: #f9f9f9; }";
    html += ".title { font-size: 18px; font-weight: bold; text-align: center; margin-bottom: 10px; }";
    html += ".subtitle { font-size: 12px; text-align: center; margin-bottom: 20px; color: #666; }";
    html += "</style></head><body>";

    html += QString("<div class='title'>%1</div>").arg(title.toHtmlEscaped());
    html += "<div class='subtitle'>Generated by VIBRA CLUB • " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm") + "</div>";

    html += "<table>";

    // Add headers (exclude Actions column)
    html += "<tr>";
    int headerColumns = table->columnCount();
    if (headerColumns > 0) {
        QTableWidgetItem* lastHeader = table->horizontalHeaderItem(headerColumns - 1);
        if (lastHeader && lastHeader->text().trimmed().compare("Actions", Qt::CaseInsensitive) == 0) {
            headerColumns = headerColumns - 1;
        }
    }
    for (int c = 0; c < headerColumns; ++c) {
        QString header = table->horizontalHeaderItem(c) ? table->horizontalHeaderItem(c)->text() : QString();
        html += QString("<th>%1</th>").arg(header.toHtmlEscaped());
    }
    html += "</tr>";

    // Add data rows (visible only)
    for (int r = 0; r < table->rowCount(); ++r) {
        if (table->isRowHidden(r)) continue;
        html += "<tr>";
        for (int c = 0; c < headerColumns; ++c) {
            QTableWidgetItem* item = table->item(r, c);
            QString cellText = item ? item->text() : QString();
            html += QString("<td>%1</td>").arg(cellText.toHtmlEscaped());
        }
        html += "</tr>";
    }

    html += "</table></body></html>";

    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(parentWidget, tr("Export Successful"), tr("Data exported to PDF successfully."));
    return true;
}
void Payment::validateMemberId()
{
    QString memberId = ui->paymentMemberEdit->text().trimmed();
    memberIdValid = isValidMemberId(memberId);

    // Optional: Visual feedback
    if (memberId.isEmpty()) {
        ui->paymentMemberEdit->setStyleSheet("");
    } else if (memberIdValid) {
        ui->paymentMemberEdit->setStyleSheet("border: 2px solid #2ecc71;");
    } else {
        ui->paymentMemberEdit->setStyleSheet("border: 2px solid #e74c3c;");
    }
}

bool Payment::isValidMemberId(const QString &memberId)
{
    if (memberId.isEmpty()) {
        return false; // Empty is NOT allowed - it's mandatory!
    }

    QSqlQuery query;
    // Check if the CIN exists in MEMBERS table
    query.prepare("SELECT COUNT(*) FROM MEMBERS WHERE CIN = :cin");
    query.bindValue(":cin", memberId);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "Member ID validation for CIN:" << memberId << "Found:" << count;
        return count > 0;
    }

    qDebug() << "Member ID validation query failed:" << query.lastError().text();
    return false;
}

void Payment::onSortByDate()
{
    QTableWidget* paymentTable = ui->paymentTable;

    // Toggle sorting order
    static bool ascending = true;

    // Sort by date column (index 1)
    paymentTable->sortItems(1, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);

    // Toggle for next click
    ascending = !ascending;

    // Update button text to show current sort order
    QString buttonText = ascending ? "Sort by Date (↑)" : "Sort by Date (↓)";
    ui->paymentSortButton->setText(buttonText);
}

void Payment::onPaymentSearchTextChanged(const QString &searchText)
{
    if (!ui->paymentTable) return;

    // For QTableWidget, we need to manually hide/show rows
    for (int row = 0; row < ui->paymentTable->rowCount(); ++row) {
        bool matchFound = false;

        // Check each column in this row for the search text
        for (int col = 0; col < ui->paymentTable->columnCount(); ++col) {
            QTableWidgetItem *item = ui->paymentTable->item(row, col);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                matchFound = true;
                break;
            }
        }

        // Show or hide the row based on search match
        ui->paymentTable->setRowHidden(row, !matchFound && !searchText.isEmpty());
    }

    // Visual feedback on search field
    if (ui->paymentSearchLineEdit) {
        int visibleRows = 0;
        for (int row = 0; row < ui->paymentTable->rowCount(); ++row) {
            if (!ui->paymentTable->isRowHidden(row)) {
                visibleRows++;
            }
        }

        if (searchText.isEmpty()) {
            ui->paymentSearchLineEdit->setStyleSheet("");
            ui->paymentSearchLineEdit->setToolTip(QString("Total payments: %1").arg(ui->paymentTable->rowCount()));
        } else if (visibleRows == 0) {
            ui->paymentSearchLineEdit->setStyleSheet("QLineEdit { border: 2px solid #e74c3c; background-color: #fdf2f2; }");
            ui->paymentSearchLineEdit->setToolTip("No payments found matching your search");
        } else {
            ui->paymentSearchLineEdit->setStyleSheet("QLineEdit { border: 2px solid #27ae60; background-color: #f2fdf2; }");
            ui->paymentSearchLineEdit->setToolTip(QString("Found %1 of %2 payments").arg(visibleRows).arg(ui->paymentTable->rowCount()));
        }
    }
}
void Payment::onExportToPDF()
{
    QString fileName = QFileDialog::getSaveFileName(
        nullptr,
        "Export Payments to PDF",
        QDir::homePath() + "/payments_report_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".pdf",
        "PDF Files (*.pdf)"
        );

    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument document;
    QTextCursor cursor(&document);

    // Get table model
    QAbstractItemModel *model = ui->paymentTable->model();
    if (!model) {
        QMessageBox::warning(nullptr, "Error", "No data to export!");
        return;
    }

    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    if (rowCount == 0) {
        QMessageBox::warning(nullptr, "Error", "No payments data to export!");
        return;
    }

    // Identify columns
    int amountColumn = -1;
    int typeColumn = -1;
    int categoryColumn = -1;
    int descriptionColumn = -1;
    int dateColumn = -1;

    for (int col = 0; col < columnCount; ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString().toLower();

        if (header.contains("amount") || header.contains("price") || header.contains("total")) {
            amountColumn = col;
        }
        else if (header.contains("type") || header.contains("payment_type")) {
            typeColumn = col;
        }
        else if (header.contains("category")) {
            categoryColumn = col;
        }
        else if (header.contains("description") || header.contains("note")) {
            descriptionColumn = col;
        }
        else if (header.contains("date")) {
            dateColumn = col;
        }
    }

    qDebug() << "Identified columns - Amount:" << amountColumn << "Type:" << typeColumn
             << "Category:" << categoryColumn << "Description:" << descriptionColumn;

    // Calculate totals
    double totalIncome = 0.0;
    double totalExpenses = 0.0;
    int incomeCount = 0;
    int expenseCount = 0;

    // Lists to store transactions for detailed breakdown
    QList<QStringList> incomeTransactions;
    QList<QStringList> expenseTransactions;

    for (int row = 0; row < rowCount; ++row) {
        if (amountColumn != -1) {
            QString amountStr = model->index(row, amountColumn).data().toString();
            QString cleanAmount = amountStr.replace("$", "").replace(",", "").replace("€", "").replace(" ", "").trimmed();

            bool ok;
            double amount = cleanAmount.toDouble(&ok);

            if (ok && amount != 0) {
                // Determine if this is income or expense
                bool isIncome = false;
                bool isExpense = false;
                QString transactionType = "Unknown";
                QString description = "";

                // Get description if available
                if (descriptionColumn != -1) {
                    description = model->index(row, descriptionColumn).data().toString();
                }

                // Method 1: Check type column first
                if (typeColumn != -1) {
                    QString type = model->index(row, typeColumn).data().toString().toLower();
                    if (type.contains("income") || type.contains("revenue") || type.contains("payment") ||
                        type.contains("subscription") || type.contains("fee") || type.contains("membership") ||
                        type.contains("deposit")) {
                        isIncome = true;
                        transactionType = "Income";
                    }
                    else if (type.contains("expense") || type.contains("purchase") || type.contains("bill") ||
                             type.contains("salary") || type.contains("maintenance") || type.contains("cost") ||
                             type.contains("withdrawal") || type.contains("refund")) {
                        isExpense = true;
                        transactionType = "Expense";
                    }
                }

                // Method 2: Check category column
                if (categoryColumn != -1 && !isIncome && !isExpense) {
                    QString category = model->index(row, categoryColumn).data().toString().toLower();
                    if (category.contains("membership") || category.contains("subscription") ||
                        category.contains("class") || category.contains("training") || category.contains("session") ||
                        category.contains("fee") || category.contains("payment")) {
                        isIncome = true;
                        transactionType = "Income (" + category + ")";
                    }
                    else if (category.contains("equipment") || category.contains("salary") ||
                             category.contains("maintenance") || category.contains("utility") ||
                             category.contains("rent") || category.contains("supply") || category.contains("tax")) {
                        isExpense = true;
                        transactionType = "Expense (" + category + ")";
                    }
                }

                // Method 3: Check description for clues
                if (!isIncome && !isExpense && !description.isEmpty()) {
                    QString descLower = description.toLower();
                    if (descLower.contains("membership") || descLower.contains("subscription") ||
                        descLower.contains("payment") || descLower.contains("fee")) {
                        isIncome = true;
                        transactionType = "Income";
                    }
                    else if (descLower.contains("purchase") || descLower.contains("buy") ||
                             descLower.contains("salary") || descLower.contains("bill") ||
                             descLower.contains("maintenance") || descLower.contains("repair")) {
                        isExpense = true;
                        transactionType = "Expense";
                    }
                }

                // Method 4: Default based on amount sign
                if (!isIncome && !isExpense) {
                    if (amount > 0) {
                        isIncome = true;
                        transactionType = "Income (Assumed)";
                    } else {
                        isExpense = true;
                        amount = -amount; // Convert to positive for expense total
                        transactionType = "Expense (Assumed)";
                    }
                }

                // Add to appropriate total and list
                if (isIncome) {
                    totalIncome += amount;
                    incomeCount++;

                    // Store income transaction details
                    QStringList incomeDetails;
                    incomeDetails << QString::number(amount, 'f', 2);
                    if (dateColumn != -1) incomeDetails << model->index(row, dateColumn).data().toString();
                    incomeDetails << description;
                    incomeDetails << transactionType;
                    incomeTransactions.append(incomeDetails);
                }
                else if (isExpense) {
                    totalExpenses += amount;
                    expenseCount++;

                    // Store expense transaction details
                    QStringList expenseDetails;
                    expenseDetails << QString::number(amount, 'f', 2);
                    if (dateColumn != -1) expenseDetails << model->index(row, dateColumn).data().toString();
                    expenseDetails << description;
                    expenseDetails << transactionType;
                    expenseTransactions.append(expenseDetails);
                }
            }
        }
    }

    double netAmount = totalIncome - totalExpenses;

    // Add title and header
    QTextCharFormat titleFormat;
    titleFormat.setFontPointSize(16);
    titleFormat.setFontWeight(QFont::Bold);
    titleFormat.setForeground(Qt::darkBlue);
    cursor.insertText("Financial Report - Income vs Expenses\n", titleFormat);

    QTextCharFormat dateFormat;
    dateFormat.setFontPointSize(10);
    dateFormat.setForeground(Qt::darkGray);
    cursor.insertText("Generated on: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "\n\n", dateFormat);

    // Create main table for all transactions
    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    tableFormat.setBorder(1);
    tableFormat.setCellSpacing(0);
    tableFormat.setCellPadding(4);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextTable *table = cursor.insertTable(rowCount + 1, columnCount, tableFormat);

    // Add headers
    QTextCharFormat headerFormat;
    headerFormat.setBackground(QColor(240, 240, 240));
    headerFormat.setFontWeight(QFont::Bold);

    for (int col = 0; col < columnCount; ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        QTextTableCell cell = table->cellAt(0, col);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(header, headerFormat);
    }

    // Add data rows
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QModelIndex index = model->index(row, col);
            QString data = model->data(index).toString();

            QTextTableCell cell = table->cellAt(row + 1, col);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.insertText(data);
        }
    }

    // Add detailed financial summary
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n\n");

    QTextCharFormat summaryTitleFormat;
    summaryTitleFormat.setFontPointSize(14);
    summaryTitleFormat.setFontWeight(QFont::Bold);
    summaryTitleFormat.setForeground(QColor(0, 51, 102));
    cursor.insertText("FINANCIAL SUMMARY\n\n", summaryTitleFormat);

    // Income section
    QTextCharFormat incomeTitleFormat;
    incomeTitleFormat.setFontWeight(QFont::Bold);
    incomeTitleFormat.setForeground(QColor(0, 128, 0)); // Green
    cursor.insertText("INCOME:\n", incomeTitleFormat);
    cursor.insertText(QString("• Total Income: $%1\n").arg(QString::number(totalIncome, 'f', 2)));
    cursor.insertText(QString("• Income Transactions: %1\n").arg(incomeCount));

    if (!incomeTransactions.isEmpty()) {
        cursor.insertText("• Recent Income Transactions:\n");
        for (int i = 0; i < qMin(5, incomeTransactions.size()); ++i) {
            QStringList details = incomeTransactions[i];
            cursor.insertText(QString("  - $%1: %2\n").arg(details[0]).arg(details[2]));
        }
    }
    cursor.insertText("\n");

    // Expenses section
    QTextCharFormat expenseTitleFormat;
    expenseTitleFormat.setFontWeight(QFont::Bold);
    expenseTitleFormat.setForeground(QColor(220, 0, 0)); // Red
    cursor.insertText("EXPENSES:\n", expenseTitleFormat);
    cursor.insertText(QString("• Total Expenses: $%1\n").arg(QString::number(totalExpenses, 'f', 2)));
    cursor.insertText(QString("• Expense Transactions: %1\n").arg(expenseCount));

    if (!expenseTransactions.isEmpty()) {
        cursor.insertText("• Recent Expense Transactions:\n");
        for (int i = 0; i < qMin(5, expenseTransactions.size()); ++i) {
            QStringList details = expenseTransactions[i];
            cursor.insertText(QString("  - $%1: %2\n").arg(details[0]).arg(details[2]));
        }
    }
    cursor.insertText("\n");

    // Net amount section
    QTextCharFormat netFormat;
    netFormat.setFontWeight(QFont::Bold);
    netFormat.setFontPointSize(12);

    if (netAmount > 0) {
        netFormat.setForeground(QColor(0, 128, 0)); // Green for profit
        cursor.insertText(QString("NET PROFIT: $%1\n").arg(QString::number(netAmount, 'f', 2)), netFormat);
    } else if (netAmount < 0) {
        netFormat.setForeground(QColor(220, 0, 0)); // Red for loss
        cursor.insertText(QString("NET LOSS: $%1\n").arg(QString::number(-netAmount, 'f', 2)), netFormat);
    } else {
        netFormat.setForeground(Qt::blue); // Blue for break-even
        cursor.insertText("BREAK-EVEN: $0.00\n", netFormat);
    }

    // Additional statistics
    cursor.insertText("\n");
    QTextCharFormat statsFormat;
    statsFormat.setFontWeight(QFont::Bold);
    statsFormat.setForeground(Qt::darkBlue);
    cursor.insertText("STATISTICS:\n", statsFormat);

    if (rowCount > 0) {
        double incomePercentage = (totalIncome / (totalIncome + totalExpenses)) * 100;
        double expensePercentage = (totalExpenses / (totalIncome + totalExpenses)) * 100;

        cursor.insertText(QString("• Income/Expense Ratio: %1% / %2%\n")
                              .arg(QString::number(incomePercentage, 'f', 1))
                              .arg(QString::number(expensePercentage, 'f', 1)));

        if (incomeCount > 0) {
            cursor.insertText(QString("• Average Income per Transaction: $%1\n")
                                  .arg(QString::number(totalIncome / incomeCount, 'f', 2)));
        }

        if (expenseCount > 0) {
            cursor.insertText(QString("• Average Expense per Transaction: $%1\n")
                                  .arg(QString::number(totalExpenses / expenseCount, 'f', 2)));
        }
    }

    cursor.insertText(QString("• Total Transactions: %1\n").arg(rowCount));

    // Print to PDF
    document.print(&printer);

    // Success message with financial summary
    QString successMsg = QString("Financial report exported successfully!\n\n"
                                 "File: %1\n"
                                 "Total Transactions: %2\n\n"
                                 "INCOME: $%3 (%4 transactions)\n"
                                 "EXPENSES: $%5 (%6 transactions)\n"
                                 "NET: $%7")
                             .arg(fileName)
                             .arg(rowCount)
                             .arg(QString::number(totalIncome, 'f', 2))
                             .arg(incomeCount)
                             .arg(QString::number(totalExpenses, 'f', 2))
                             .arg(expenseCount)
                             .arg(QString::number(netAmount, 'f', 2));

    QMessageBox::information(nullptr, "Success", successMsg);
}
