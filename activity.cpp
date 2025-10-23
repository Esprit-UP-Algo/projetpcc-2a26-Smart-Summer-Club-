#include "activity.h"
#include "ui_employeradmin.h"
#include <QPixmap>
#include <QFile>
#include <QStringConverter>
#include <QTextCursor>
#include <QDateTime>

Activity::Activity(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), ui(ui), parentWidget(parent)
{
}

Activity::~Activity()
{
}

void Activity::setupActivityTable()
{
    ui->activityTable->setColumnCount(8);
    QStringList headers = {"Activity ID", "Type", "Event Date", "Time", "Responsible", 
                          "Age", "Status", "Actions"};
    ui->activityTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->activityTable->setColumnWidth(0, 100);  // Activity ID
    ui->activityTable->setColumnWidth(1, 150);  // Type
    ui->activityTable->setColumnWidth(2, 120);  // Event Date
    ui->activityTable->setColumnWidth(3, 80);   // Time
    ui->activityTable->setColumnWidth(4, 150);  // Responsible
    ui->activityTable->setColumnWidth(5, 60);   // Age
    ui->activityTable->setColumnWidth(6, 100);  // Status
    ui->activityTable->setColumnWidth(7, 150);  // Actions
}

void Activity::onEditActivity(int row)
{
    // Get activity data from the selected row
    QString activityId = ui->activityTable->item(row, 0)->text();
    QString type = ui->activityTable->item(row, 1)->text();
    QString eventDate = ui->activityTable->item(row, 2)->text();
    QString time = ui->activityTable->item(row, 3)->text();
    QString responsible = ui->activityTable->item(row, 4)->text();
    QString age = ui->activityTable->item(row, 5)->text();
    QString status = ui->activityTable->item(row, 6)->text();
    
    // Switch to Add Activity tab for editing
    ui->activityTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    // Populate the form fields with selected activity data
    ui->activityIdLineEdit->setText(activityId);
    ui->responsibleLineEdit->setText(responsible);
    ui->activityAgeSpinBox->setValue(age.toInt());
    
    // Set type combo box
    int typeIndex = ui->activityTypeComboBox->findText(type);
    if (typeIndex >= 0) {
        ui->activityTypeComboBox->setCurrentIndex(typeIndex);
    }
    
    // Set status combo box
    int statusIndex = ui->activityStatusComboBox->findText(status);
    if (statusIndex >= 0) {
        ui->activityStatusComboBox->setCurrentIndex(statusIndex);
    }
    
    // Set event date
    QDate date = QDate::fromString(eventDate, "yyyy-MM-dd");
    ui->eventDateEdit->setDate(date);
    
    // Set event time
    QTime timeObj = QTime::fromString(time, "hh:mm");
    ui->eventTimeEdit->setTime(timeObj);
    
    QMessageBox::information(parentWidget, "Edit Activity", 
        QString("Editing activity: %1\nID: %2\nType: %3").arg(responsible, activityId, type));
}

void Activity::onDeleteActivity(int row)
{
    // Get activity data from the selected row
    QString activityId = ui->activityTable->item(row, 0)->text();
    QString type = ui->activityTable->item(row, 1)->text();
    QString responsible = ui->activityTable->item(row, 4)->text();
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(parentWidget, 
        "Delete Activity", 
        QString("Are you sure you want to delete activity:\n%1 - %2 (ID: %3)?").arg(type, responsible, activityId),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->activityTable->removeRow(row);
        
        QMessageBox::information(parentWidget, "Activity Deleted", 
            QString("Activity %1 has been successfully deleted.").arg(activityId));
    }
}

void Activity::onSortActivities(int index)
{
    // Sort based on ComboBox selection:
    // 0: Sort by Date (Event Date column - index 2)
    // 1: Sort by Age (Age column - index 5) 
    // 2: Sort by Activity (Activity ID column - index 0)
    
    switch(index) {
        case 0: // Sort by Date
            sortTableByName(ui->activityTable, 2); // Event Date column
            break;
        case 1: // Sort by Age
            sortTableByName(ui->activityTable, 5); // Age column
            break;
        case 2: // Sort by Activity
            sortTableByName(ui->activityTable, 0); // Activity ID column
            break;
        default:
            sortTableByName(ui->activityTable, 2); // Default to Date
            break;
    }
}

void Activity::onExportActivities()
{
    exportTableToPdf(ui->activityTable, "activities.pdf", tr("List of Activities"));
}

// Generic sort by Name column (default index 1)
void Activity::sortTableByName(QTableWidget* table, int nameColumnIndex)
{
    if (!table) return;

    // Toggle sorting order: if already sorted ascending, switch to descending
    static Qt::SortOrder lastOrder = Qt::AscendingOrder;
    lastOrder = (lastOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

    table->sortItems(nameColumnIndex, lastOrder);
}

// Export a QTableWidget to CSV (visible rows only, excluding action button cells)
bool Activity::exportTableToCsv(QTableWidget* table, const QString& defaultName)
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

bool Activity::exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title)
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