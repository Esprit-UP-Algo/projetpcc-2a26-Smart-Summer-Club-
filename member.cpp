#include "member.h"
#include "ui_employeradmin.h"
#include <QPixmap>
#include <QFile>
#include <QStringConverter>
#include <QTextCursor>
#include <QDateTime>

Member::Member(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), ui(ui), parentWidget(parent)
{
}

Member::~Member()
{
}

void Member::setupMemberTable()
{
    ui->memberTable->setColumnCount(10);
    QStringList headers = {"Member ID", "First Name", "Last Name", "Gender", "Age", 
                          "Email", "Phone Number", "Subscription Plan", "Join Date", "Actions"};
    ui->memberTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->memberTable->setColumnWidth(0, 100);  // Member ID
    ui->memberTable->setColumnWidth(1, 120);  // First Name
    ui->memberTable->setColumnWidth(2, 120);  // Last Name
    ui->memberTable->setColumnWidth(3, 80);   // Gender
    ui->memberTable->setColumnWidth(4, 60);   // Age
    ui->memberTable->setColumnWidth(5, 200);  // Email
    ui->memberTable->setColumnWidth(6, 130);  // Phone
    ui->memberTable->setColumnWidth(7, 120);  // Subscription
    ui->memberTable->setColumnWidth(8, 100);  // Join Date
    ui->memberTable->setColumnWidth(9, 150);  // Actions
}

void Member::onEditMember(int row)
{
    // Get member data from the selected row
    QString id = ui->memberTable->item(row, 0)->text();
    QString firstName = ui->memberTable->item(row, 1)->text();
    QString lastName = ui->memberTable->item(row, 2)->text();
    QString gender = ui->memberTable->item(row, 3)->text();
    QString age = ui->memberTable->item(row, 4)->text();
    QString email = ui->memberTable->item(row, 5)->text();
    QString phone = ui->memberTable->item(row, 6)->text();
    QString subscription = ui->memberTable->item(row, 7)->text();
    QString joinDate = ui->memberTable->item(row, 8)->text();
    
    // Switch to Add Member tab for editing
    ui->memberTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    // Populate the form fields with selected member data
    ui->memberIdLineEdit->setText(id);
    ui->memberFirstNameLineEdit->setText(firstName);
    ui->memberLastNameLineEdit->setText(lastName);
    ui->memberAgeSpinBox->setValue(age.toInt());
    ui->memberEmailLineEdit->setText(email);
    ui->memberPhoneLineEdit->setText(phone);
    
    // Set gender combo box
    int genderIndex = ui->memberGenderComboBox->findText(gender);
    if (genderIndex >= 0) {
        ui->memberGenderComboBox->setCurrentIndex(genderIndex);
    }
    
    // Set subscription combo box
    int subscriptionIndex = ui->memberSubscriptionComboBox->findText(subscription);
    if (subscriptionIndex >= 0) {
        ui->memberSubscriptionComboBox->setCurrentIndex(subscriptionIndex);
    }
    
    // Set join date
    QDate date = QDate::fromString(joinDate, "yyyy-MM-dd");
    ui->memberJoinDateEdit->setDate(date);
    
    QMessageBox::information(parentWidget, "Edit Member", 
        QString("Editing member: %1 %2\nID: %3").arg(firstName, lastName, id));
}

void Member::onDeleteMember(int row)
{
    // Get member data from the selected row
    QString id = ui->memberTable->item(row, 0)->text();
    QString firstName = ui->memberTable->item(row, 1)->text();
    QString lastName = ui->memberTable->item(row, 2)->text();
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(parentWidget, 
        "Delete Member", 
        QString("Are you sure you want to delete member:\n%1 %2 (ID: %3)?").arg(firstName, lastName, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->memberTable->removeRow(row);
        
        QMessageBox::information(parentWidget, "Member Deleted", 
            QString("Member %1 %2 has been successfully deleted.").arg(firstName, lastName));
    }
}

void Member::onSortMembers()
{
    // Sort by First Name column (index 1)
    sortTableByName(ui->memberTable, 1);
}

void Member::onExportMembers()
{
    exportTableToPdf(ui->memberTable, "members.pdf", tr("List of Members"));
}

// Generic sort by Name column (default index 1)
void Member::sortTableByName(QTableWidget* table, int nameColumnIndex)
{
    if (!table) return;

    // Toggle sorting order: if already sorted ascending, switch to descending
    static Qt::SortOrder lastOrder = Qt::AscendingOrder;
    lastOrder = (lastOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

    table->sortItems(nameColumnIndex, lastOrder);
}

// Export a QTableWidget to CSV (visible rows only, excluding action button cells)
bool Member::exportTableToCsv(QTableWidget* table, const QString& defaultName)
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

bool Member::exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title)
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