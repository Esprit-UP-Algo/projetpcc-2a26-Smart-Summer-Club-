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
    QSqlQueryModel* model = paymentModel->getAllPayments();
    QTableWidget* paymentTable = ui->paymentTable;

    paymentTable->setRowCount(0);

    for (int i = 0; i < model->rowCount(); ++i) {
        QString transactionId = model->record(i).value("transaction_id").toString();
        QString date = model->record(i).value("payment_date").toString();
        QString description = model->record(i).value("description").toString();
        QString type = model->record(i).value("payment_type").toString();
        QString amount = QString("$%1").arg(model->record(i).value("amount").toDouble(), 0, 'f', 2);
        QString method = model->record(i).value("payment_method").toString();
        QString status = model->record(i).value("status").toString();
        QString memberId = model->record(i).value("member_id").toString();

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
    }

    populatePaymentStatistics();
    delete model;
}

QString Payment::generateTransactionId()
{
    QSqlQuery query;

    // Get the maximum existing transaction_id from TRANSACTIONS table
    query.exec("SELECT MAX(TO_NUMBER(REGEXP_SUBSTR(transaction_id, '[0-9]+'))) FROM transactions WHERE transaction_id LIKE 'TXN%'");

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


void Payment::onPaymentSearchTextChanged()
{
    QString searchText = ui->paymentSearchLineEdit->text().trimmed().toLower();
    QTableWidget* paymentTable = ui->paymentTable;

    for (int i = 0; i < paymentTable->rowCount(); ++i) {
        bool shouldShow = false;

        // Search in relevant columns (Transaction ID, Description, Member ID)
        QList<int> searchColumns = {0, 2, 7}; // Transaction ID, Description, Member ID

        for (int col : searchColumns) {
            QTableWidgetItem* item = paymentTable->item(i, col);
            if (item && item->text().toLower().contains(searchText)) {
                shouldShow = true;
                break;
            }
        }

        paymentTable->setRowHidden(i, !shouldShow);
    }
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
