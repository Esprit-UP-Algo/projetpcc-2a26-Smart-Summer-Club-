#include "equipment.h"
#include "ui_employeradmin.h"
#include <QPixmap>
#include <QFile>
#include <QStringConverter>
#include <QTextCursor>
#include <QDateTime>

Equipment::Equipment(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent), ui(ui), parentWidget(parent), 
      equipmentDetailsTable(nullptr), equipmentDetailsWidget(nullptr), 
      isDetailsTableVisible(false)
{
}

Equipment::~Equipment()
{
    if (equipmentDetailsWidget) {
        delete equipmentDetailsWidget;
    }
}

void Equipment::setupEquipmentTable()
{
    ui->equipmentTable->setColumnCount(6);
    QStringList headers = {"Equipment ID", "Name", "Category", "Total Stock", "Status", "Actions"};
    ui->equipmentTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    ui->equipmentTable->setColumnWidth(0, 100);  // Equipment ID
    ui->equipmentTable->setColumnWidth(1, 150);  // Name
    ui->equipmentTable->setColumnWidth(2, 120);  // Category
    ui->equipmentTable->setColumnWidth(3, 80);   // Total Stock
    ui->equipmentTable->setColumnWidth(4, 100);  // Status
    ui->equipmentTable->setColumnWidth(5, 220);  // Actions
    
    // Make table read-only
    ui->equipmentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Equipment::setupEquipmentDetailsTable()
{
    // Create the dynamic details widget and table
    equipmentDetailsWidget = new QWidget();
    equipmentDetailsWidget->setFixedSize(400, 400);
    equipmentDetailsWidget->setVisible(false);
    isDetailsTableVisible = false;
    
    // Set styling for the details widget
    equipmentDetailsWidget->setStyleSheet(
        "QWidget { "
        "background-color: white; "
        "border: 2px solid #16a5b3; "
        "border-radius: 8px; "
        "}"
    );
    
    // Create the details table
    equipmentDetailsTable = new QTableWidget();
    equipmentDetailsTable->setColumnCount(2);
    equipmentDetailsTable->setRowCount(6);
    equipmentDetailsTable->setHorizontalHeaderLabels(QStringList() << "Property" << "Value");
    equipmentDetailsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    equipmentDetailsTable->verticalHeader()->setVisible(false);
    equipmentDetailsTable->setAlternatingRowColors(true);
    equipmentDetailsTable->setFixedSize(360, 300);
    
    // Set row height for better visibility
    equipmentDetailsTable->verticalHeader()->setDefaultSectionSize(40);
    
    // Set column widths
    equipmentDetailsTable->setColumnWidth(0, 170);
    equipmentDetailsTable->setColumnWidth(1, 170);
    
    // Style the details table
    equipmentDetailsTable->setStyleSheet(
        "QTableWidget { "
        "border: 1px solid #e0e4e7; "
        "border-radius: 4px; "
        "background-color: #f8fbfc; "
        "font-size: 14px; "
        "} "
        "QHeaderView::section { "
        "background-color: #16a5b3; "
        "color: white; "
        "padding: 10px; "
        "border: none; "
        "font-weight: bold; "
        "font-size: 14px; "
        "}"
    );
    
    // Create layout for details widget
    QVBoxLayout *detailsLayout = new QVBoxLayout(equipmentDetailsWidget);
    
    // Add title label
    QLabel *titleLabel = new QLabel("Equipment Details");
    titleLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #2c3e50; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    // Add close button
    QPushButton *closeBtn = new QPushButton("×");
    closeBtn->setFixedSize(25, 25);
    closeBtn->setStyleSheet(
        "QPushButton { "
        "background-color: #c0392b; "
        "color: white; "
        "border: none; "
        "border-radius: 12px; "
        "font-size: 16px; "
        "font-weight: bold; "
        "} "
        "QPushButton:hover { "
        "background-color: #a93226; "
        "}"
    );
    
    connect(closeBtn, &QPushButton::clicked, this, &Equipment::hideEquipmentDetailsTable);
    
    // Create top layout with title and close button
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();
    topLayout->addWidget(closeBtn);
    
    detailsLayout->addLayout(topLayout);
    detailsLayout->addWidget(equipmentDetailsTable);
    detailsLayout->setContentsMargins(10, 10, 10, 10);
    
    // Create a horizontal layout container for the equipmentListTab
    if (ui->equipmentListTab) {
        // Create a main horizontal layout for the tab content
        QHBoxLayout *mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(15);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        
        // Create a container widget for the existing equipment table and controls
        QWidget *tableContainer = new QWidget();
        QVBoxLayout *tableLayout = new QVBoxLayout(tableContainer);
        tableLayout->setContentsMargins(0, 0, 0, 0);
        
        // Add the table container and details widget to the main layout
        mainLayout->addWidget(tableContainer, 3); // Table takes 75% of width
        mainLayout->addWidget(equipmentDetailsWidget, 1); // Details take 25% of width
        
        // If the tab already has a layout, we need to work with it
        QLayout *existingLayout = ui->equipmentListTab->layout();
        if (!existingLayout) {
            // If no layout exists, set our new layout
            ui->equipmentListTab->setLayout(mainLayout);
        } else {
            // If layout exists, we'll add our details widget as a child of the tab
            // and position it manually (fallback approach)
            equipmentDetailsWidget->setParent(ui->equipmentListTab);
        }
    }
}

void Equipment::onEquipmentDetails(const QStringList &equipmentData)
{
    // Debug output
    qDebug() << "Details button clicked, isDetailsTableVisible:" << isDetailsTableVisible;
    qDebug() << "equipmentDetailsWidget exists:" << (equipmentDetailsWidget != nullptr);
    qDebug() << "equipmentDetailsTable exists:" << (equipmentDetailsTable != nullptr);
    
    // Toggle the details table visibility
    if (isDetailsTableVisible) {
        hideEquipmentDetailsTable();
    } else {
        showEquipmentDetailsTable(equipmentData);
    }
}

void Equipment::onEquipmentManage(const QStringList &equipmentData)
{
    // Extract equipment data from the passed list
    QString equipmentId = equipmentData[0];
    QString name = equipmentData[1];
    QString category = equipmentData[2];
    
    // Switch to Add Equipment tab for editing
    ui->equipmentTabWidget->setCurrentIndex(1); // Switch to Add tab (index 1)
    
    // Populate the form fields with selected equipment data
    ui->equipmentNameLineEdit->setText(name);
    
    // Set category combo box
    int categoryIndex = ui->equipmentCategoryComboBox->findText(category);
    if (categoryIndex >= 0) {
        ui->equipmentCategoryComboBox->setCurrentIndex(categoryIndex);
    }
    
    QMessageBox::information(parentWidget, "Edit Equipment", 
        QString("Editing equipment: %1\nID: %2\nCategory: %3").arg(name, equipmentId, category));
}

void Equipment::onEquipmentDelete(const QStringList &equipmentData, int row)
{
    // Extract equipment data from the passed list
    QString equipmentId = equipmentData[0];
    QString name = equipmentData[1];
    QString category = equipmentData[2];
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(parentWidget, 
        "Delete Equipment", 
        QString("Are you sure you want to delete equipment:\n%1 - %2 (ID: %3)?").arg(category, name, equipmentId),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Remove the row from the table
        ui->equipmentTable->removeRow(row);
        
        QMessageBox::information(parentWidget, "Equipment Deleted", 
            QString("Equipment %1 has been successfully deleted.").arg(name));
    }
}

void Equipment::onSortEquipment()
{
    // Sort by equipment name (index 1)
    sortTableByName(ui->equipmentTable, 1);
}

void Equipment::onExportEquipment()
{
    exportTableToPdf(ui->equipmentTable, "equipment.pdf", tr("Equipment Inventory Report"));
}

void Equipment::showEquipmentDetailsTable(const QStringList &equipmentData)
{
    qDebug() << "showEquipmentDetailsTable called";
    if (!equipmentDetailsTable || !equipmentDetailsWidget) {
        qDebug() << "equipmentDetailsTable or equipmentDetailsWidget is null!";
        return;
    }
    
    // Extract data from the equipment data list
    QString equipmentId = equipmentData[0];
    QString name = equipmentData[1];
    QString category = equipmentData[2];
    QString totalStock = equipmentData[3];
    QString available = equipmentData[4];
    QString inUse = equipmentData[5];
    QString maintenance = equipmentData[6];
    
    // Calculate percentages
    double totalStockNum = totalStock.toDouble();
    double usageRate = totalStockNum > 0 ? (inUse.toDouble() / totalStockNum) * 100 : 0;
    double availableRate = totalStockNum > 0 ? (available.toDouble() / totalStockNum) * 100 : 0;
    
    // Populate the details table
    equipmentDetailsTable->setItem(0, 0, new QTableWidgetItem("Equipment ID"));
    equipmentDetailsTable->setItem(0, 1, new QTableWidgetItem(equipmentId));
    
    equipmentDetailsTable->setItem(1, 0, new QTableWidgetItem("Available"));
    equipmentDetailsTable->setItem(1, 1, new QTableWidgetItem(available + " units"));
    
    equipmentDetailsTable->setItem(2, 0, new QTableWidgetItem("In Use"));
    equipmentDetailsTable->setItem(2, 1, new QTableWidgetItem(inUse + " units"));
    
    equipmentDetailsTable->setItem(3, 0, new QTableWidgetItem("Under Maintenance"));
    equipmentDetailsTable->setItem(3, 1, new QTableWidgetItem(maintenance + " units"));
    
    equipmentDetailsTable->setItem(4, 0, new QTableWidgetItem("Usage Rate"));
    equipmentDetailsTable->setItem(4, 1, new QTableWidgetItem(QString::number(usageRate, 'f', 1) + "%"));
    
    equipmentDetailsTable->setItem(5, 0, new QTableWidgetItem("Availability Rate"));
    equipmentDetailsTable->setItem(5, 1, new QTableWidgetItem(QString::number(availableRate, 'f', 1) + "%"));
    
    // Position the details widget to the right side of the tab
    if (ui->equipmentListTab && ui->equipmentTable) {
        // Get the equipment table position and size
        QRect tableGeometry = ui->equipmentTable->geometry();
        QSize tabSize = ui->equipmentListTab->size();
        
        // Position the details widget to the right of the equipment table
        int x = tableGeometry.right() + 20; // 20 pixels margin from the table
        int y = tableGeometry.top(); // Align with the top of the table
        
        // Make sure it fits within the tab bounds
        if (x + equipmentDetailsWidget->width() > tabSize.width()) {
            x = tabSize.width() - equipmentDetailsWidget->width() - 10;
        }
        
        // Ensure it doesn't go off screen
        if (x < tableGeometry.right() + 10) {
            x = tableGeometry.right() + 10;
        }
        
        equipmentDetailsWidget->move(x, y);
    }
    
    // Show the details widget
    qDebug() << "Setting widget visible at position:" << equipmentDetailsWidget->pos();
    qDebug() << "Widget size:" << equipmentDetailsWidget->size();
    equipmentDetailsWidget->setVisible(true);
    equipmentDetailsWidget->raise(); // Bring to front
    isDetailsTableVisible = true;
    qDebug() << "Widget visibility set to:" << equipmentDetailsWidget->isVisible();
}

void Equipment::hideEquipmentDetailsTable()
{
    if (equipmentDetailsWidget) {
        equipmentDetailsWidget->setVisible(false);
        isDetailsTableVisible = false;
    }
}

// Generic sort by Name column (default index 1)
void Equipment::sortTableByName(QTableWidget* table, int nameColumnIndex)
{
    if (!table) return;

    // Toggle sorting order: if already sorted ascending, switch to descending
    static Qt::SortOrder lastOrder = Qt::AscendingOrder;
    lastOrder = (lastOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

    table->sortItems(nameColumnIndex, lastOrder);
}

// Export a QTableWidget to CSV (visible rows only, excluding action button cells)
bool Equipment::exportTableToCsv(QTableWidget* table, const QString& defaultName)
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

bool Equipment::exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title)
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