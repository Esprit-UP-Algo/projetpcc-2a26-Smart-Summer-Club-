#include "employee.h"
#include "ui_employeradmin.h"
#include <QPixmap>
#include <QFile>
#include <QStringConverter>
#include <QTextCursor>
#include <QDateTime>

Employee::Employee(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), ui(ui), parentWidget(parent)
{
}

Employee::~Employee()
{
}

void Employee::setupEmployeeTable()
{
    ui->employeeTable->setColumnCount(13);
    QStringList headers = {"Employee ID", "First Name", "Last Name", "Position", "Department", 
                          "Gender", "Age", "Salary", "Email", "Phone", "Hire Date", "Status", "Actions"};
    ui->employeeTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->employeeTable->setColumnWidth(0, 100);  // Employee ID
    ui->employeeTable->setColumnWidth(1, 120);  // First Name
    ui->employeeTable->setColumnWidth(2, 120);  // Last Name
    ui->employeeTable->setColumnWidth(3, 120);  // Position
    ui->employeeTable->setColumnWidth(4, 130);  // Department
    ui->employeeTable->setColumnWidth(5, 80);   // Gender
    ui->employeeTable->setColumnWidth(6, 60);   // Age
    ui->employeeTable->setColumnWidth(7, 100);  // Salary
    ui->employeeTable->setColumnWidth(8, 200);  // Email
    ui->employeeTable->setColumnWidth(9, 130);  // Phone
    ui->employeeTable->setColumnWidth(10, 100); // Hire Date
    ui->employeeTable->setColumnWidth(11, 80);  // Status
    ui->employeeTable->setColumnWidth(12, 150); // Actions
    
    // Make table read-only
    ui->employeeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Employee::onSearchEmployees()
{
    QString searchTerm = ui->searchLineEdit->text().toLower();
    
    for (int i = 0; i < ui->employeeTable->rowCount(); ++i) {
        bool showRow = false;
        
        // Search in all columns except actions
        for (int j = 0; j < 6; ++j) {
            QTableWidgetItem *item = ui->employeeTable->item(i, j);
            if (item && item->text().toLower().contains(searchTerm)) {
                showRow = true;
                break;
            }
        }
        
        ui->employeeTable->setRowHidden(i, !showRow);
    }
    
    if (searchTerm.isEmpty()) {
        // Show all rows if search is empty
        for (int i = 0; i < ui->employeeTable->rowCount(); ++i) {
            ui->employeeTable->setRowHidden(i, false);
        }
    }
}

void Employee::onUploadPhoto()
{
    QString fileName = QFileDialog::getOpenFileName(parentWidget,
        tr("Select Employee Photo"), "",
        tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));
    
    if (!fileName.isEmpty()) {
        ui->photoLabel->setText("Photo Selected: " + QFileInfo(fileName).fileName());
        QMessageBox::information(parentWidget, "Photo Upload", "Photo selected successfully!\n\nFile: " + QFileInfo(fileName).fileName());
    }
}

void Employee::onConfirmAdd()
{
    // Validate required fields
    if (ui->empIdLineEdit->text().isEmpty() || 
        ui->firstNameLineEdit->text().isEmpty() || 
        ui->lastNameLineEdit->text().isEmpty() ||
        ui->emailLineEdit->text().isEmpty()) {
        
        QMessageBox::warning(parentWidget, "Validation Error", "Please fill in all required fields:\n- Employee ID\n- First Name\n- Last Name\n- Email");
        return;
    }
    
    // Show confirmation message
    QMessageBox::information(parentWidget, "Employee Added", 
        QString("Employee %1 %2 has been successfully added to the system!")
        .arg(ui->firstNameLineEdit->text())
        .arg(ui->lastNameLineEdit->text()));
    
    // Clear form
    clearEmployeeForm();
}

void Employee::onConfirmUpdate()
{
    // Validate required fields
    if (ui->empIdLineEdit->text().isEmpty() || 
        ui->firstNameLineEdit->text().isEmpty() || 
        ui->lastNameLineEdit->text().isEmpty() ||
        ui->emailLineEdit->text().isEmpty()) {
        
        QMessageBox::warning(parentWidget, "Validation Error", "Please fill in all required fields:\n- Employee ID\n- First Name\n- Last Name\n- Email");
        return;
    }
    
    // Show confirmation message
    QMessageBox::information(parentWidget, "Employee Updated", 
        QString("Employee %1 %2 information has been successfully updated!")
        .arg(ui->firstNameLineEdit->text())
        .arg(ui->lastNameLineEdit->text()));
    
    // Clear form
    clearEmployeeForm();
}

void Employee::clearEmployeeForm()
{
    ui->empIdLineEdit->clear();
    ui->firstNameLineEdit->clear();
    ui->lastNameLineEdit->clear();
    ui->positionLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->phoneLineEdit->clear();
    ui->salaryLineEdit->clear();
    
    ui->departmentComboBox->setCurrentIndex(0);
    ui->genderComboBox->setCurrentIndex(0);
    ui->statusComboBox->setCurrentIndex(0);
    ui->ageSpinBox->setValue(25);
    ui->hireDateEdit->setDate(QDate::currentDate());
    
    ui->photoLabel->setText("Upload Employee Photo");
}

void Employee::onEditEmployee(int row)
{
    // Get employee data from the selected row
    QString id = ui->employeeTable->item(row, 0)->text();
    QString name = ui->employeeTable->item(row, 1)->text();
    QString position = ui->employeeTable->item(row, 2)->text();
    QString department = ui->employeeTable->item(row, 3)->text();
    QString hireDate = ui->employeeTable->item(row, 4)->text();
    QString status = ui->employeeTable->item(row, 5)->text();
    
    // Switch to Add Employee tab and populate form with existing data
    ui->employeeTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    QMessageBox::information(parentWidget, "Edit Employee", 
        QString("Editing employee: %1\nID: %2\nPosition: %3").arg(name, id, position));
}

void Employee::onDeleteEmployee(int row)
{
    // Get employee data from the selected row
    QString id = ui->employeeTable->item(row, 0)->text();
    QString name = ui->employeeTable->item(row, 1)->text();
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(parentWidget, 
        "Delete Employee", 
        QString("Are you sure you want to delete employee:\n%1 (ID: %2)?").arg(name, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->employeeTable->removeRow(row);
        
        QMessageBox::information(parentWidget, "Employee Deleted", 
            QString("Employee %1 has been deleted successfully.").arg(name));
    }
}

void Employee::onSortEmployees()
{
    // Sort by Hire Date column (index 4)
    sortTableByName(ui->employeeTable, 4);
}

void Employee::onExportEmployees()
{
    exportTableToPdf(ui->employeeTable, "employees.pdf", tr("List of Employees"));
}

// Generic sort by Name column (default index 1)
void Employee::sortTableByName(QTableWidget* table, int nameColumnIndex)
{
    if (!table) return;

    // Toggle sorting order: if already sorted ascending, switch to descending
    static Qt::SortOrder lastOrder = Qt::AscendingOrder;
    lastOrder = (lastOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

    table->sortItems(nameColumnIndex, lastOrder);
}

// Export a QTableWidget to CSV (visible rows only, excluding action button cells)
bool Employee::exportTableToCsv(QTableWidget* table, const QString& defaultName)
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

bool Employee::exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title)
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