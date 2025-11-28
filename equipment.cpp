#include "equipment.h"
#include "ui_employeradmin.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QStackedBarSeries>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>

Equipment::Equipment(Ui::EmployerAdmin *ui, QWidget *parent)
    : QObject(parent)
    , ui(ui)
    , parentWidget(parent)
    , equipmentDetailsTable(nullptr)
    , equipmentDetailsWidget(nullptr)
    , sidePanelWidget(nullptr)
    , isDetailsTableVisible(false)
    , isSidePanelVisible(false)
    , currentSelectedRow(-1)
{
    qDebug() << "=== Equipment Constructor Started ===";

    setupEquipmentTable();
    ui->equipmentTable->show();

    // KEEP THESE WIDGETS HIDDEN AS THEY'RE NOT USED
    setupEquipmentDetailsTable();  // This creates but hides the widget
    createSidePanel();             // This creates but hides the widget

    loadEquipmentTable();

    // ENSURE MAIN TABLE IS VISIBLE
    if (ui->equipmentTable) {
        ui->equipmentTable->show();
    }

    connect(ui->equipmentTable, &QTableWidget::cellClicked,
            this, &Equipment::onTableRowClicked);
    connect(ui->equipmentConfirmButton, &QPushButton::clicked,
            this, &Equipment::onConfirmAdd);
    connect(ui->equipmentUpdateButton, &QPushButton::clicked,
            this, &Equipment::onConfirmUpdate);
    connect(ui->equipmentSearchButton, &QPushButton::clicked,
            this, &Equipment::onSearchEquipment);
    connect(ui->equipmentSortButton, &QPushButton::clicked,
            this, &Equipment::onSortEquipment);
    connect(ui->equipmentExportButton, &QPushButton::clicked,
            this, &Equipment::onExportEquipment);
    
    // Connect tab change to populate statistics when statistics tab is accessed
    // Statistics tab is at index 2 (0=list, 1=add, 2=statistics)
    connect(ui->equipmentTabWidget, &QTabWidget::currentChanged,
            this, [this](int index) {
                if (index == 2) { // Statistics tab index
                    populateEquipmentStatistics();
                }
            });

    qDebug() << "=== Equipment Constructor Completed ===";
}

Equipment::~Equipment()
{
    delete equipmentDetailsWidget;
    delete sidePanelWidget;
}

void Equipment::setupEquipmentTable()
{
    qDebug() << "Setting up equipment table...";

    ui->equipmentTable->setColumnCount(6);
    QStringList hdr = {"Name","Type","Total Qty","Location","Status","Actions"};
    ui->equipmentTable->setHorizontalHeaderLabels(hdr);
    ui->equipmentTable->horizontalHeader()->setStretchLastSection(true);
    ui->equipmentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->equipmentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->equipmentTable->setColumnWidth(0,200);
    ui->equipmentTable->setColumnWidth(1,150);
    ui->equipmentTable->setColumnWidth(2,120);
    ui->equipmentTable->setColumnWidth(3,150);
    ui->equipmentTable->setColumnWidth(4,200);

    // Enable sorting
    ui->equipmentTable->setSortingEnabled(true);

    // ENSURE TABLE IS VISIBLE
    ui->equipmentTable->show();

    qDebug() << "Equipment table setup completed";
}

void Equipment::loadEquipmentTable()
{
    qDebug() << "=== Starting loadEquipmentTable() ===";

    ui->equipmentTable->blockSignals(true);
    ui->equipmentTable->setRowCount(0);

    QSqlQuery q;
    bool querySuccess = q.exec(
        "SELECT ID_EQ, NAME, CATEGORY, TOTAL_QUANTITY, "
        "NVL(QUANTITY_AVAILABLE, AVAILABLE) AS QTY_AVAIL, "
        "NVL(QUANTITY_RESERVED, IN_USE) AS QTY_RESERVED, "
        "NVL(QUANTITY_MAINTENANCE, UNDER_MAINTENANCE) AS QTY_MAINT, "
        "NVL(QUANTITY_OUT_OF_ORDER, 0) AS QTY_OUT_OF_ORDER, "
        "NVL(LOCATION,'Non spécifié') AS LOC "
        "FROM EQUIPEMENTS ORDER BY NAME"
        );

    qDebug() << "Query execution success:" << querySuccess;

    if (!querySuccess) {
        QSqlError error = q.lastError();
        qDebug() << "Database error:" << error.text();
        qDebug() << "Database error type:" << error.type();
        qDebug() << "Database driver:" << q.lastError().driverText();

        QMessageBox::critical(parentWidget, "DB Error", error.text());
        ui->equipmentTable->blockSignals(false);
        return;
    }

    qDebug() << "Query executed successfully";
    qDebug() << "Number of rows returned:" << q.size();

    int row = 0;
    int recordCount = 0;

    while (q.next())
    {
        recordCount++;
        qDebug() << "Processing row" << row << "with data:";

        int id = q.value(0).toInt();
        QString name = q.value(1).toString();
        QString cat = q.value(2).toString();
        int total = q.value(3).toInt();
        int avail = q.value(4).toInt();        // QUANTITY_AVAILABLE
        int reserved = q.value(5).toInt();     // QUANTITY_RESERVED
        int maint = q.value(6).toInt();        // QUANTITY_MAINTENANCE
        int outOfOrder = q.value(7).toInt();   // QUANTITY_OUT_OF_ORDER
        QString loc = q.value(8).toString();   // LOCATION

        qDebug() << "  ID:" << id << "Name:" << name << "Category:" << cat << "Total:" << total;

        ui->equipmentTable->insertRow(row);

        // Create items with dark text for light theme
        QTableWidgetItem *itName = new QTableWidgetItem(name);
        itName->setData(Qt::UserRole, id);
        itName->setForeground(QBrush(QColor(44, 62, 80))); // Dark blue-gray from your theme
        ui->equipmentTable->setItem(row, 0, itName);

        QTableWidgetItem *itCat = new QTableWidgetItem(cat);
        itCat->setForeground(QBrush(QColor(44, 62, 80)));
        ui->equipmentTable->setItem(row, 1, itCat);

        QTableWidgetItem *itTotal = new QTableWidgetItem(QString::number(total));
        itTotal->setForeground(QBrush(QColor(44, 62, 80)));
        ui->equipmentTable->setItem(row, 2, itTotal);

        QTableWidgetItem *itLoc = new QTableWidgetItem(loc);
        itLoc->setForeground(QBrush(QColor(44, 62, 80)));
        ui->equipmentTable->setItem(row, 3, itLoc);

        // Status items with proper colors for light theme
        QString status = QString("%1 available").arg(avail);
        if (reserved) status += QString(", %1 reserved").arg(reserved);
        if (maint) status += QString(", %1 maintenance").arg(maint);
        if (outOfOrder) status += QString(", %1 out of order").arg(outOfOrder);
        QTableWidgetItem *itStat = new QTableWidgetItem(status);

        // Set colors that work well on light background
        if (maint) {
            itStat->setForeground(QBrush(QColor(220, 53, 69))); // Bootstrap danger red
            itStat->setBackground(QBrush(QColor(255, 243, 245))); // Light red background
        } else if (reserved) {
            itStat->setForeground(QBrush(QColor(255, 153, 0))); // Orange
            itStat->setBackground(QBrush(QColor(255, 248, 225))); // Light orange background
        } else {
            itStat->setForeground(QBrush(QColor(40, 167, 69))); // Bootstrap success green
            itStat->setBackground(QBrush(QColor(235, 251, 238))); // Light green background
        }

        // Ensure the item is selectable and has the right text alignment
        itStat->setTextAlignment(Qt::AlignCenter);
        ui->equipmentTable->setItem(row, 4, itStat);

        // Create action buttons with better styling and debugging
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *actionsLayout = new QHBoxLayout(actionsWidget);
        actionsLayout->setContentsMargins(5, 2, 5, 2);
        actionsLayout->setSpacing(5);

        QPushButton *editButton = new QPushButton("Edit");
        QPushButton *deleteButton = new QPushButton("Delete");

        editButton->setFixedSize(60, 25);
        deleteButton->setFixedSize(60, 25);

        // Style buttons to match your theme
        editButton->setStyleSheet(
            "QPushButton { "
            "    background-color: rgba(22, 165, 179, 0.10); "
            "    color: #2c3e50; "
            "    border: 1.5px solid rgba(22, 165, 179, 0.65); "
            "    border-radius: 10px; "
            "    font-size: 11px; "
            "    font-weight: 500; "
            "}"
            "QPushButton:hover { "
            "    background-color: rgba(22, 165, 179, 0.18); "
            "}"
            "QPushButton:pressed { "
            "    background-color: rgba(22, 165, 179, 0.26); "
            "}"
            );

        deleteButton->setStyleSheet(
            "QPushButton { "
            "    background-color: rgba(220, 53, 69, 0.10); "
            "    color: #2c3e50; "
            "    border: 1.5px solid rgba(220, 53, 69, 0.65); "
            "    border-radius: 10px; "
            "    font-size: 11px; "
            "    font-weight: 500; "
            "}"
            "QPushButton:hover { "
            "    background-color: rgba(220, 53, 69, 0.18); "
            "}"
            "QPushButton:pressed { "
            "    background-color: rgba(220, 53, 69, 0.26); "
            "}"
            );

        actionsLayout->addWidget(editButton);
        actionsLayout->addWidget(deleteButton);

        // Remove any existing widget first
        if (ui->equipmentTable->cellWidget(row, 5)) {
            ui->equipmentTable->removeCellWidget(row, 5);
        }
        ui->equipmentTable->setCellWidget(row, 5, actionsWidget);

        qDebug() << "Created action buttons for row" << row << "- Edit and Delete";

        // EDIT BUTTON CONNECTION
        connect(editButton, &QPushButton::clicked, this, [this, row, id, name]() {
            qDebug() << "=== EDIT BUTTON CLICKED ===";
            qDebug() << "Row:" << row << "ID:" << id << "Name:" << name;

            currentSelectedRow = row;
            QSqlQuery query;
            // Try to get new quantity columns first, fallback to old ones
            query.prepare("SELECT NAME, CATEGORY, TOTAL_QUANTITY, "
                         "NVL(QUANTITY_AVAILABLE, AVAILABLE) AS QTY_AVAIL, "
                         "NVL(QUANTITY_RESERVED, IN_USE) AS QTY_RESERVED, "
                         "NVL(QUANTITY_MAINTENANCE, UNDER_MAINTENANCE) AS QTY_MAINT, "
                         "NVL(QUANTITY_OUT_OF_ORDER, 0) AS QTY_OUT_OF_ORDER, "
                         "STATUS, BRAND, MODEL, PURCHASE_PRICE, PURCHASE_DATE "
                         "FROM EQUIPEMENTS WHERE ID_EQ = :id");
            query.bindValue(":id", id);

            if (query.exec() && query.next()) {
                qDebug() << "Loading equipment data for editing...";

                // Populate form fields
                ui->equipmentNameLineEdit->setText(query.value(0).toString());
                ui->equipmentCategoryComboBox->setCurrentText(query.value(1).toString());
                ui->equipmentQuantitySpinBox->setValue(query.value(2).toInt());
                
                // Load quantity values
                int availQty = query.value(3).toInt();
                int reservedQty = query.value(4).toInt();
                int maintQty = query.value(5).toInt();
                int outOfOrderQty = query.value(6).toInt();
                
                ui->equipmentAvailableQtySpinBox->setValue(availQty);
                ui->equipmentReservedQtySpinBox->setValue(reservedQty);
                ui->equipmentMaintenanceQtySpinBox->setValue(maintQty);
                ui->equipmentOutOfOrderQtySpinBox->setValue(outOfOrderQty);
                
                ui->equipmentStatusComboBox->setCurrentText(query.value(7).toString());
                ui->equipmentBrandLineEdit->setText(query.value(8).toString());
                ui->equipmentModelLineEdit->setText(query.value(9).toString());

                double price = query.value(10).toDouble();
                ui->equipmentPriceLineEdit->setText(price > 0 ? QString::number(price, 'f', 2) : "");
                ui->equipmentPurchaseDateEdit->setDate(query.value(11).toDate());

                // Switch to update mode
                ui->equipmentConfirmButton->setVisible(false);
                ui->equipmentUpdateButton->setVisible(true);

                // Switch to the form tab
                ui->equipmentTabWidget->setCurrentIndex(1);

                qDebug() << "Form populated successfully for editing";
                QMessageBox::information(parentWidget, "Edit Mode",
                                         QString("Now editing: %1\nMake your changes and click 'Update'").arg(name));
            } else {
                qDebug() << "Failed to load equipment data:" << query.lastError().text();
                QMessageBox::critical(parentWidget, "Error",
                                      "Failed to load equipment data: " + query.lastError().text());
            }
        });

        // DELETE BUTTON CONNECTION
        connect(deleteButton, &QPushButton::clicked, this, [this, id, name]() {
            qDebug() << "=== DELETE BUTTON CLICKED ===";
            qDebug() << "ID:" << id << "Name:" << name;

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(parentWidget,
                                          "Confirm Deletion",
                                          QString("Are you sure you want to delete:\n\n<b>%1</b>?\n\nThis action cannot be undone.").arg(name),
                                          QMessageBox::Yes | QMessageBox::No,
                                          QMessageBox::No); // Default to No for safety

            if (reply == QMessageBox::Yes) {
                qDebug() << "User confirmed deletion of:" << name;

                QSqlQuery deleteQuery;
                deleteQuery.prepare("DELETE FROM EQUIPEMENTS WHERE ID_EQ = :id");
                deleteQuery.bindValue(":id", id);

                if (deleteQuery.exec()) {
                    qDebug() << "Successfully deleted equipment from database";
                    QMessageBox::information(parentWidget, "Success",
                                             QString("Equipment '%1' has been deleted successfully.").arg(name));
                    loadEquipmentTable(); // Refresh the table
                    populateEquipmentStatistics(); // Update statistics after deleting equipment
                } else {
                    qDebug() << "Failed to delete equipment:" << deleteQuery.lastError().text();
                    QMessageBox::critical(parentWidget, "Error",
                                          "Failed to delete equipment: " + deleteQuery.lastError().text());
                }
            } else {
                qDebug() << "User cancelled deletion";
            }
        });

        ++row;
    }

    qDebug() << "Total records processed:" << recordCount;
    qDebug() << "Final table row count:" << ui->equipmentTable->rowCount();

    ui->equipmentTable->blockSignals(false);

    // REMOVED: ui->equipmentTable->resizeColumnsToContents(); // This was causing columns to become narrower

    qDebug() << "=== loadEquipmentTable() Completed ===";
}

void Equipment::onConfirmAdd()
{
    QString name = ui->equipmentNameLineEdit->text().trimmed();
    QString cat = ui->equipmentCategoryComboBox->currentText();
    int totalQty = ui->equipmentQuantitySpinBox->value();
    
    // Get quantities for each status
    int availQty = ui->equipmentAvailableQtySpinBox->value();
    int reservedQty = ui->equipmentReservedQtySpinBox->value();
    int maintQty = ui->equipmentMaintenanceQtySpinBox->value();
    int outOfOrderQty = ui->equipmentOutOfOrderQtySpinBox->value();
    
    // Calculate sum of all status quantities
    int sumQty = availQty + reservedQty + maintQty + outOfOrderQty;
    
    // Validate that sum equals total quantity
    if (sumQty != totalQty) {
        QMessageBox::warning(parentWidget, "Validation Error", 
            QString("The sum of quantities (Available: %1 + Reserved: %2 + Maintenance: %3 + Out of Order: %4 = %5)\n"
                   "must equal the Total Quantity (%6).\n\n"
                   "Please adjust the quantities.").arg(availQty).arg(reservedQty).arg(maintQty).arg(outOfOrderQty).arg(sumQty).arg(totalQty));
        return;
    }
    
    QString brand = ui->equipmentBrandLineEdit->text().trimmed();
    QString model = ui->equipmentModelLineEdit->text().trimmed();
    QDate pDate = ui->equipmentPurchaseDateEdit->date();

    // FIXED: Proper price conversion with NULL handling - using modern QMetaType
    QString priceText = ui->equipmentPriceLineEdit->text().trimmed();
    QVariant priceValue;
    if (!priceText.isEmpty()) {
        bool ok;
        double price = priceText.toDouble(&ok);
        if (ok && price > 0) {
            priceValue = QVariant(price);
        } else {
            // Invalid price - set to NULL using modern method
            priceValue = QVariant(QMetaType::fromType<double>());
        }
    } else {
        // Empty price - set to NULL using modern method
        priceValue = QVariant(QMetaType::fromType<double>());
    }

    if (name.isEmpty() || brand.isEmpty()) {
        QMessageBox::warning(parentWidget, "Input", "Name and Brand required");
        return;
    }

    QString code;
    do { code = "EQ-" + QString::number(QRandomGenerator::global()->bounded(100000)); }
    while (codeExists(code));

    // Determine overall status based on quantities
    QString overallStatus = "Available";
    if (outOfOrderQty > 0) overallStatus = "Out of Order";
    else if (maintQty > 0) overallStatus = "Under Maintenance";
    else if (reservedQty > 0 && availQty == 0) overallStatus = "In Use";
    else if (reservedQty > 0) overallStatus = "Partially Reserved";

    QSqlQuery q;
    // Try new column names first, fallback to old names if they don't exist
    q.prepare(
        "INSERT INTO EQUIPEMENTS (EQUIP_CODE, NAME, CATEGORY, TOTAL_QUANTITY, "
        "QUANTITY_AVAILABLE, QUANTITY_RESERVED, QUANTITY_MAINTENANCE, QUANTITY_OUT_OF_ORDER, "
        "AVAILABLE, IN_USE, UNDER_MAINTENANCE, STATUS, BRAND, MODEL, PURCHASE_DATE, PURCHASE_PRICE, LOCATION) "
        "VALUES (:code, :name, :cat, :qty, :avail, :reserved, :maint, :outoforder, :avail_old, :inuse_old, :maint_old, :status, :brand, :model, :date, :price, 'N/A')"
        );
    q.bindValue(":code", code);
    q.bindValue(":name", name);
    q.bindValue(":cat", cat);
    q.bindValue(":qty", totalQty);
    q.bindValue(":avail", availQty);
    q.bindValue(":reserved", reservedQty);
    q.bindValue(":maint", maintQty);
    q.bindValue(":outoforder", outOfOrderQty);
    // Also set old columns for backward compatibility
    q.bindValue(":avail_old", availQty);
    q.bindValue(":inuse_old", reservedQty);
    q.bindValue(":maint_old", maintQty);
    q.bindValue(":status", overallStatus);
    q.bindValue(":brand", brand);
    q.bindValue(":model", model);
    q.bindValue(":date", pDate);
    q.bindValue(":price", priceValue);

    qDebug() << "=== Starting onConfirmAdd() ===";
    qDebug() << "Total Qty:" << totalQty << "Available:" << availQty << "Reserved:" << reservedQty 
             << "Maintenance:" << maintQty << "Out of Order:" << outOfOrderQty;

    if (q.exec()) {
        qDebug() << "Add successful";
        clearForm();
        loadEquipmentTable();  // DISPLAYS IMMEDIATELY
        populateEquipmentStatistics(); // Update statistics after adding equipment
        QMessageBox::information(parentWidget, "Success", "Equipment added successfully!");
    } else {
        qDebug() << "Add failed:" << q.lastError().text();
        // Try with only old column names if new ones don't exist
        QSqlQuery q2;
        q2.prepare(
            "INSERT INTO EQUIPEMENTS (EQUIP_CODE, NAME, CATEGORY, TOTAL_QUANTITY, "
            "AVAILABLE, IN_USE, UNDER_MAINTENANCE, STATUS, BRAND, MODEL, PURCHASE_DATE, PURCHASE_PRICE, LOCATION) "
            "VALUES (:code, :name, :cat, :qty, :avail, :reserved, :maint, :status, :brand, :model, :date, :price, 'N/A')"
            );
        q2.bindValue(":code", code);
        q2.bindValue(":name", name);
        q2.bindValue(":cat", cat);
        q2.bindValue(":qty", totalQty);
        q2.bindValue(":avail", availQty);
        q2.bindValue(":reserved", reservedQty);
        q2.bindValue(":maint", maintQty);
        q2.bindValue(":status", overallStatus);
        q2.bindValue(":brand", brand);
        q2.bindValue(":model", model);
        q2.bindValue(":date", pDate);
        q2.bindValue(":price", priceValue);
        
        if (q2.exec()) {
            qDebug() << "Add successful (using old columns)";
            clearForm();
            loadEquipmentTable();
            populateEquipmentStatistics(); // Update statistics after adding equipment
            QMessageBox::information(parentWidget, "Success", "Equipment added successfully!");
        } else {
            QMessageBox::critical(parentWidget, "Error", "Failed to add equipment: " + q2.lastError().text());
        }
    }
}

void Equipment::onConfirmUpdate()
{
    if (currentSelectedRow < 0) {
        QMessageBox::warning(parentWidget, "Select", "Select a row first");
        return;
    }
    int id = ui->equipmentTable->item(currentSelectedRow, 0)->data(Qt::UserRole).toInt();

    QString name = ui->equipmentNameLineEdit->text().trimmed();
    QString cat = ui->equipmentCategoryComboBox->currentText();
    int totalQty = ui->equipmentQuantitySpinBox->value();
    
    // Get quantities for each status
    int availQty = ui->equipmentAvailableQtySpinBox->value();
    int reservedQty = ui->equipmentReservedQtySpinBox->value();
    int maintQty = ui->equipmentMaintenanceQtySpinBox->value();
    int outOfOrderQty = ui->equipmentOutOfOrderQtySpinBox->value();
    
    // Calculate sum of all status quantities
    int sumQty = availQty + reservedQty + maintQty + outOfOrderQty;
    
    // Validate that sum equals total quantity
    if (sumQty != totalQty) {
        QMessageBox::warning(parentWidget, "Validation Error", 
            QString("The sum of quantities (Available: %1 + Reserved: %2 + Maintenance: %3 + Out of Order: %4 = %5)\n"
                   "must equal the Total Quantity (%6).\n\n"
                   "Please adjust the quantities.").arg(availQty).arg(reservedQty).arg(maintQty).arg(outOfOrderQty).arg(sumQty).arg(totalQty));
        return;
    }
    
    QString brand = ui->equipmentBrandLineEdit->text().trimmed();
    QString model = ui->equipmentModelLineEdit->text().trimmed();

    // FIXED: Proper price conversion with NULL handling - using modern QMetaType
    QString priceText = ui->equipmentPriceLineEdit->text().trimmed();
    QVariant priceValue;
    if (!priceText.isEmpty()) {
        bool ok;
        double price = priceText.toDouble(&ok);
        if (ok && price > 0) {
            priceValue = QVariant(price);
        } else {
            // Invalid price - set to NULL using modern method
            priceValue = QVariant(QMetaType::fromType<double>());
        }
    } else {
        // Empty price - set to NULL using modern method
        priceValue = QVariant(QMetaType::fromType<double>());
    }

    // Determine overall status based on quantities
    QString overallStatus = "Available";
    if (outOfOrderQty > 0) overallStatus = "Out of Order";
    else if (maintQty > 0) overallStatus = "Under Maintenance";
    else if (reservedQty > 0 && availQty == 0) overallStatus = "In Use";
    else if (reservedQty > 0) overallStatus = "Partially Reserved";

    QSqlQuery q;
    // Try updating with new column names first
    q.prepare("UPDATE EQUIPEMENTS SET NAME=:n, CATEGORY=:c, TOTAL_QUANTITY=:q, "
              "QUANTITY_AVAILABLE=:avail, QUANTITY_RESERVED=:reserved, QUANTITY_MAINTENANCE=:maint, QUANTITY_OUT_OF_ORDER=:outoforder, "
              "AVAILABLE=:avail_old, IN_USE=:inuse_old, UNDER_MAINTENANCE=:maint_old, STATUS=:s, BRAND=:b, MODEL=:m, PURCHASE_PRICE=:p "
              "WHERE ID_EQ=:id");
    q.bindValue(":n", name);
    q.bindValue(":c", cat);
    q.bindValue(":q", totalQty);
    q.bindValue(":avail", availQty);
    q.bindValue(":reserved", reservedQty);
    q.bindValue(":maint", maintQty);
    q.bindValue(":outoforder", outOfOrderQty);
    q.bindValue(":avail_old", availQty);
    q.bindValue(":inuse_old", reservedQty);
    q.bindValue(":maint_old", maintQty);
    q.bindValue(":s", overallStatus);
    q.bindValue(":b", brand);
    q.bindValue(":m", model);
    q.bindValue(":p", priceValue);
    q.bindValue(":id", id);

    qDebug() << "=== Starting onConfirmUpdate() ===";
    qDebug() << "Updating equipment ID:" << id;
    qDebug() << "Total Qty:" << totalQty << "Available:" << availQty << "Reserved:" << reservedQty 
             << "Maintenance:" << maintQty << "Out of Order:" << outOfOrderQty;

    if (q.exec()) {
        qDebug() << "Update successful";
        loadEquipmentTable();
        populateEquipmentStatistics(); // Update statistics after updating equipment
        clearForm();
        QMessageBox::information(parentWidget, "Success", "Equipment updated successfully!");
    } else {
        qDebug() << "Update failed:" << q.lastError().text();
        // Try with only old column names if new ones don't exist
        QSqlQuery q2;
        q2.prepare("UPDATE EQUIPEMENTS SET NAME=:n, CATEGORY=:c, TOTAL_QUANTITY=:q, "
                   "AVAILABLE=:avail, IN_USE=:reserved, UNDER_MAINTENANCE=:maint, STATUS=:s, BRAND=:b, MODEL=:m, PURCHASE_PRICE=:p "
                   "WHERE ID_EQ=:id");
        q2.bindValue(":n", name);
        q2.bindValue(":c", cat);
        q2.bindValue(":q", totalQty);
        q2.bindValue(":avail", availQty);
        q2.bindValue(":reserved", reservedQty);
        q2.bindValue(":maint", maintQty);
        q2.bindValue(":s", overallStatus);
        q2.bindValue(":b", brand);
        q2.bindValue(":m", model);
        q2.bindValue(":p", priceValue);
        q2.bindValue(":id", id);
        
        if (q2.exec()) {
            qDebug() << "Update successful (using old columns)";
            loadEquipmentTable();
            populateEquipmentStatistics(); // Update statistics after updating equipment
            clearForm();
            QMessageBox::information(parentWidget, "Success", "Equipment updated successfully!");
        } else {
            QMessageBox::critical(parentWidget, "Error", "Failed to update equipment: " + q2.lastError().text());
        }
    }
}

void Equipment::onSearchEquipment()
{
    qDebug() << "=== Starting onSearchEquipment() ===";

    QString txt = ui->equipmentSearchLineEdit->text().trimmed();
    qDebug() << "Search text:" << txt;

    if (txt.isEmpty()) {
        qDebug() << "Empty search text, loading all equipment";
        loadEquipmentTable();
        return;
    }

    QSqlQuery q;
    q.prepare("SELECT ID_EQ, NAME, CATEGORY, TOTAL_QUANTITY, "
              "NVL(QUANTITY_AVAILABLE, AVAILABLE) AS QTY_AVAIL, "
              "NVL(QUANTITY_RESERVED, IN_USE) AS QTY_RESERVED, "
              "NVL(QUANTITY_MAINTENANCE, UNDER_MAINTENANCE) AS QTY_MAINT, "
              "NVL(QUANTITY_OUT_OF_ORDER, 0) AS QTY_OUT_OF_ORDER, "
              "NVL(LOCATION,'Non spécifié') AS LOC "
              "FROM EQUIPEMENTS WHERE UPPER(NAME) LIKE UPPER(:t) OR UPPER(CATEGORY) LIKE UPPER(:t) "
              "OR UPPER(BRAND) LIKE UPPER(:t) OR UPPER(MODEL) LIKE UPPER(:t) ORDER BY NAME");
    q.bindValue(":t", "%" + txt + "%");

    if (!q.exec()) {
        QMessageBox::critical(parentWidget, "Error", q.lastError().text());
        return;
    }

    ui->equipmentTable->blockSignals(true);
    ui->equipmentTable->setSortingEnabled(false); // Disable sorting during update
    ui->equipmentTable->setRowCount(0);

    int row = 0;
    int foundCount = 0;

    while (q.next()) {
        foundCount++;
        int id = q.value(0).toInt();
        QString name = q.value(1).toString();
        QString cat = q.value(2).toString();
        int total = q.value(3).toInt();
        int avail = q.value(4).toInt();
        int reserved = q.value(5).toInt();
        int maint = q.value(6).toInt();
        int outOfOrder = q.value(7).toInt();
        QString loc = q.value(8).toString();

        ui->equipmentTable->insertRow(row);

        // Create items with dark text for light theme
        QTableWidgetItem *itName = new QTableWidgetItem(name);
        itName->setData(Qt::UserRole, id);
        itName->setForeground(QBrush(QColor(44, 62, 80))); // Dark blue-gray from your theme
        ui->equipmentTable->setItem(row, 0, itName);

        QTableWidgetItem *itCat = new QTableWidgetItem(cat);
        itCat->setForeground(QBrush(QColor(44, 62, 80)));
        ui->equipmentTable->setItem(row, 1, itCat);

        QTableWidgetItem *itTotal = new QTableWidgetItem(QString::number(total));
        itTotal->setForeground(QBrush(QColor(44, 62, 80)));
        ui->equipmentTable->setItem(row, 2, itTotal);

        QTableWidgetItem *itLoc = new QTableWidgetItem(loc);
        itLoc->setForeground(QBrush(QColor(44, 62, 80)));
        ui->equipmentTable->setItem(row, 3, itLoc);

        // Status items with proper colors for light theme
        QString status = QString("%1 available").arg(avail);
        if (reserved) status += QString(", %1 reserved").arg(reserved);
        if (maint) status += QString(", %1 maintenance").arg(maint);
        if (outOfOrder) status += QString(", %1 out of order").arg(outOfOrder);
        QTableWidgetItem *itStat = new QTableWidgetItem(status);

        // Set colors that work well on light background
        if (maint || outOfOrder) {
            itStat->setForeground(QBrush(QColor(220, 53, 69))); // Bootstrap danger red
            itStat->setBackground(QBrush(QColor(255, 243, 245))); // Light red background
        } else if (reserved) {
            itStat->setForeground(QBrush(QColor(255, 153, 0))); // Orange
            itStat->setBackground(QBrush(QColor(255, 248, 225))); // Light orange background
        } else {
            itStat->setForeground(QBrush(QColor(40, 167, 69))); // Bootstrap success green
            itStat->setBackground(QBrush(QColor(235, 251, 238))); // Light green background
        }

        // Ensure the item is selectable and has the right text alignment
        itStat->setTextAlignment(Qt::AlignCenter);
        ui->equipmentTable->setItem(row, 4, itStat);

        // Create action buttons for search results
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *actionsLayout = new QHBoxLayout(actionsWidget);
        actionsLayout->setContentsMargins(5, 2, 5, 2);
        actionsLayout->setSpacing(5);

        QPushButton *editButton = new QPushButton("Edit");
        QPushButton *deleteButton = new QPushButton("Delete");

        editButton->setFixedSize(60, 25);
        deleteButton->setFixedSize(60, 25);

        // Style buttons to match your theme
        editButton->setStyleSheet(
            "QPushButton { "
            "    background-color: rgba(22, 165, 179, 0.10); "
            "    color: #2c3e50; "
            "    border: 1.5px solid rgba(22, 165, 179, 0.65); "
            "    border-radius: 10px; "
            "    font-size: 11px; "
            "    font-weight: 500; "
            "}"
            "QPushButton:hover { "
            "    background-color: rgba(22, 165, 179, 0.18); "
            "}"
            "QPushButton:pressed { "
            "    background-color: rgba(22, 165, 179, 0.26); "
            "}"
            );

        deleteButton->setStyleSheet(
            "QPushButton { "
            "    background-color: rgba(220, 53, 69, 0.10); "
            "    color: #2c3e50; "
            "    border: 1.5px solid rgba(220, 53, 69, 0.65); "
            "    border-radius: 10px; "
            "    font-size: 11px; "
            "    font-weight: 500; "
            "}"
            "QPushButton:hover { "
            "    background-color: rgba(220, 53, 69, 0.18); "
            "}"
            "QPushButton:pressed { "
            "    background-color: rgba(220, 53, 69, 0.26); "
            "}"
            );

        actionsLayout->addWidget(editButton);
        actionsLayout->addWidget(deleteButton);
        ui->equipmentTable->setCellWidget(row, 5, actionsWidget);

        connect(editButton, &QPushButton::clicked, this, [this, row, id, name]() {
            qDebug() << "=== EDIT BUTTON CLICKED (from search) ===";
            qDebug() << "Row:" << row << "ID:" << id << "Name:" << name;

            currentSelectedRow = row;
            QSqlQuery query;
            query.prepare("SELECT NAME, CATEGORY, TOTAL_QUANTITY, STATUS, BRAND, MODEL, PURCHASE_PRICE, PURCHASE_DATE "
                          "FROM EQUIPEMENTS WHERE ID_EQ = :id");
            query.bindValue(":id", id);

            if (query.exec() && query.next()) {
                qDebug() << "Loading equipment data for editing...";

                // Populate form fields
                ui->equipmentNameLineEdit->setText(query.value(0).toString());
                ui->equipmentCategoryComboBox->setCurrentText(query.value(1).toString());
                ui->equipmentQuantitySpinBox->setValue(query.value(2).toInt());
                ui->equipmentStatusComboBox->setCurrentText(query.value(3).toString());
                ui->equipmentBrandLineEdit->setText(query.value(4).toString());
                ui->equipmentModelLineEdit->setText(query.value(5).toString());

                double price = query.value(6).toDouble();
                ui->equipmentPriceLineEdit->setText(price > 0 ? QString::number(price, 'f', 2) : "");
                ui->equipmentPurchaseDateEdit->setDate(query.value(7).toDate());

                // Switch to update mode
                ui->equipmentConfirmButton->setVisible(false);
                ui->equipmentUpdateButton->setVisible(true);

                // Switch to the form tab
                ui->equipmentTabWidget->setCurrentIndex(1);

                qDebug() << "Form populated successfully for editing";
                QMessageBox::information(parentWidget, "Edit Mode",
                                         QString("Now editing: %1\nMake your changes and click 'Update'").arg(name));
            } else {
                qDebug() << "Failed to load equipment data:" << query.lastError().text();
                QMessageBox::critical(parentWidget, "Error",
                                      "Failed to load equipment data: " + query.lastError().text());
            }
        });

        connect(deleteButton, &QPushButton::clicked, this, [this, id, name]() {
            qDebug() << "=== DELETE BUTTON CLICKED (from search) ===";
            qDebug() << "ID:" << id << "Name:" << name;

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(parentWidget,
                                          "Confirm Deletion",
                                          QString("Are you sure you want to delete:\n\n<b>%1</b>?\n\nThis action cannot be undone.").arg(name),
                                          QMessageBox::Yes | QMessageBox::No,
                                          QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                qDebug() << "User confirmed deletion of:" << name;

                QSqlQuery deleteQuery;
                deleteQuery.prepare("DELETE FROM EQUIPEMENTS WHERE ID_EQ = :id");
                deleteQuery.bindValue(":id", id);

                if (deleteQuery.exec()) {
                    qDebug() << "Successfully deleted equipment from database";
                    QMessageBox::information(parentWidget, "Success",
                                             QString("Equipment '%1' has been deleted successfully.").arg(name));
                    loadEquipmentTable(); // Refresh the table
                    populateEquipmentStatistics(); // Update statistics after deleting equipment
                } else {
                    qDebug() << "Failed to delete equipment:" << deleteQuery.lastError().text();
                    QMessageBox::critical(parentWidget, "Error",
                                          "Failed to delete equipment: " + deleteQuery.lastError().text());
                }
            } else {
                qDebug() << "User cancelled deletion";
            }
        });

        ++row;
    }

    qDebug() << "Search found" << foundCount << "records";

    ui->equipmentTable->setSortingEnabled(true); // Re-enable sorting
    ui->equipmentTable->blockSignals(false);



    qDebug() << "=== onSearchEquipment() Completed ===";
}

void Equipment::onSortEquipment()
{
    qDebug() << "=== Starting onSortEquipment() ===";


    static bool ascending = true;

    if (ascending) {
        ui->equipmentTable->sortByColumn(0, Qt::AscendingOrder);
        qDebug() << "Sorting by Name (Ascending)";
    } else {
        ui->equipmentTable->sortByColumn(0, Qt::DescendingOrder);
        qDebug() << "Sorting by Name (Descending)";
    }

    ascending = !ascending;

    qDebug() << "=== onSortEquipment() Completed ===";
}

void Equipment::onExportEquipment()
{
    qDebug() << "=== Starting onExportEquipment() ===";

    QString path = QFileDialog::getSaveFileName(parentWidget, "Export CSV", "equipment.csv", "CSV (*.csv)");
    if (path.isEmpty()) {
        qDebug() << "Export cancelled by user";
        return;
    }

    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << path;
        QMessageBox::critical(parentWidget, "Error", "Cannot open file for writing!");
        return;
    }

    QTextStream out(&f);

    // Write headers
    for (int c = 0; c < 5; ++c) {
        out << "\"" << ui->equipmentTable->horizontalHeaderItem(c)->text() << "\"";
        if (c < 4) out << ",";
    }
    out << "\n";

    // Write data
    int rowCount = ui->equipmentTable->rowCount();
    qDebug() << "Exporting" << rowCount << "rows to CSV";

    for (int r = 0; r < rowCount; ++r) {
        for (int c = 0; c < 5; ++c) {
            QTableWidgetItem *it = ui->equipmentTable->item(r, c);
            out << "\"" << (it ? it->text().replace("\"", "\"\"") : "") << "\"";
            out << (c < 4 ? "," : "\n");
        }
    }

    f.close();

    qDebug() << "Export completed successfully to:" << path;
    QMessageBox::information(parentWidget, "Success", QString("Exported %1 records to:\n%2").arg(rowCount).arg(path));

    qDebug() << "=== onExportEquipment() Completed ===";
}

void Equipment::setupEquipmentDetailsTable()
{
    equipmentDetailsWidget = new QWidget(parentWidget);
    equipmentDetailsWidget->hide();  // KEEP HIDDEN - NOT USED
    QVBoxLayout *lay = new QVBoxLayout(equipmentDetailsWidget);
    lay->addWidget(new QLabel("Equipment Details"));
    equipmentDetailsTable = new QTableWidget;
    equipmentDetailsTable->setColumnCount(4);
    equipmentDetailsTable->setHorizontalHeaderLabels({"Name","Qty","Cond","Loc"});
    equipmentDetailsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    lay->addWidget(equipmentDetailsTable);
    QPushButton *close = new QPushButton("Close");
    connect(close, &QPushButton::clicked, this, &Equipment::hideEquipmentDetailsTable);
    lay->addWidget(close);
    ui->equipmentPageLayout->addWidget(equipmentDetailsWidget);
}

void Equipment::createSidePanel()
{
    sidePanelWidget = new QWidget(parentWidget);
    sidePanelWidget->hide();  // KEEP HIDDEN - NOT USED
    ui->equipmentPageLayout->addWidget(sidePanelWidget);
}

void Equipment::onTableRowClicked(int row, int) {
    currentSelectedRow = row;
    qDebug() << "Row clicked:" << row;
}

void Equipment::hideEquipmentDetailsTable() {
    equipmentDetailsWidget->hide();
}

void Equipment::clearForm()
{
    ui->equipmentNameLineEdit->clear();
    ui->equipmentBrandLineEdit->clear();
    ui->equipmentModelLineEdit->clear();
    ui->equipmentPriceLineEdit->clear();
    ui->equipmentQuantitySpinBox->setValue(1);
    ui->equipmentAvailableQtySpinBox->setValue(1);
    ui->equipmentReservedQtySpinBox->setValue(0);
    ui->equipmentMaintenanceQtySpinBox->setValue(0);
    ui->equipmentOutOfOrderQtySpinBox->setValue(0);
    ui->equipmentConfirmButton->setVisible(true);
    ui->equipmentUpdateButton->setVisible(false);
    currentSelectedRow = -1;
}

bool Equipment::codeExists(const QString &code)
{
    QSqlQuery q;
    q.prepare("SELECT 1 FROM EQUIPEMENTS WHERE EQUIP_CODE=:c");
    q.bindValue(":c", code);
    return q.exec() && q.next();
}

void Equipment::populateEquipmentStatistics()
{
    qDebug() << "=== Starting populateEquipmentStatistics() ===";
    
    // Safety check: Ensure UI elements exist before accessing them
    if (!ui || !ui->equipmentStatsFrame) {
        qDebug() << "Warning: Statistics UI elements not available yet";
        return;
    }
    
    // Check if database connection is available
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Warning: Database connection not available";
        return;
    }
    
    // Query total equipment count
    QSqlQuery totalQuery;
    int totalCount = 0;
    if (totalQuery.exec("SELECT SUM(TOTAL_QUANTITY) FROM EQUIPEMENTS")) {
        if (totalQuery.next()) {
            totalCount = totalQuery.value(0).toInt();
        }
    } else {
        qDebug() << "Error querying total equipment:" << totalQuery.lastError().text();
    }
    
    // Query available equipment count
    QSqlQuery availableQuery;
    int availableCount = 0;
    if (availableQuery.exec("SELECT SUM(NVL(QUANTITY_AVAILABLE, AVAILABLE)) FROM EQUIPEMENTS")) {
        if (availableQuery.next()) {
            availableCount = availableQuery.value(0).toInt();
        }
    } else {
        qDebug() << "Error querying available equipment:" << availableQuery.lastError().text();
    }
    
    // Query in-use/reserved equipment count
    QSqlQuery inUseQuery;
    int inUseCount = 0;
    if (inUseQuery.exec("SELECT SUM(NVL(QUANTITY_RESERVED, IN_USE)) FROM EQUIPEMENTS")) {
        if (inUseQuery.next()) {
            inUseCount = inUseQuery.value(0).toInt();
        }
    } else {
        qDebug() << "Error querying in-use equipment:" << inUseQuery.lastError().text();
    }
    
    // Query maintenance equipment count
    QSqlQuery maintenanceQuery;
    int maintenanceCount = 0;
    if (maintenanceQuery.exec("SELECT SUM(NVL(QUANTITY_MAINTENANCE, UNDER_MAINTENANCE)) FROM EQUIPEMENTS")) {
        if (maintenanceQuery.next()) {
            maintenanceCount = maintenanceQuery.value(0).toInt();
        }
    } else {
        qDebug() << "Error querying maintenance equipment:" << maintenanceQuery.lastError().text();
    }
    
    // Query out of order equipment count
    QSqlQuery outOfOrderQuery;
    int outOfOrderCount = 0;
    if (outOfOrderQuery.exec("SELECT SUM(NVL(QUANTITY_OUT_OF_ORDER, 0)) FROM EQUIPEMENTS")) {
        if (outOfOrderQuery.next()) {
            outOfOrderCount = outOfOrderQuery.value(0).toInt();
        }
    } else {
        qDebug() << "Error querying out of order equipment:" << outOfOrderQuery.lastError().text();
    }
    
    qDebug() << "Statistics calculated - Total:" << totalCount << "Available:" << availableCount 
             << "In Use:" << inUseCount << "Maintenance:" << maintenanceCount << "Out of Order:" << outOfOrderCount;
    
    // Update statistics cards with real data (check if labels exist)
    if (ui->totalEquipmentNumber) {
        ui->totalEquipmentNumber->setText(QString::number(totalCount));
    }
    if (ui->availableEquipmentNumber) {
        ui->availableEquipmentNumber->setText(QString::number(availableCount));
    }
    if (ui->maintenanceEquipmentNumber) {
        ui->maintenanceEquipmentNumber->setText(QString::number(maintenanceCount));
    }
    
    // Query category distribution for the table
    QSqlQuery categoryQuery;
    categoryQuery.prepare(
        "SELECT CATEGORY, "
        "SUM(TOTAL_QUANTITY) as TOTAL, "
        "SUM(NVL(QUANTITY_AVAILABLE, AVAILABLE)) as AVAILABLE, "
        "SUM(NVL(QUANTITY_RESERVED, IN_USE)) as IN_USE, "
        "SUM(NVL(QUANTITY_MAINTENANCE, UNDER_MAINTENANCE)) as MAINTENANCE "
        "FROM EQUIPEMENTS "
        "GROUP BY CATEGORY "
        "ORDER BY CATEGORY"
    );
    
    // Populate category table if it exists
    if (ui->equipmentCategoryStatsTable) {
        QTableWidget* categoryTable = ui->equipmentCategoryStatsTable;
        categoryTable->setRowCount(0);
        
        if (categoryQuery.exec()) {
            int row = 0;
            while (categoryQuery.next()) {
                QString category = categoryQuery.value(0).toString();
                int total = categoryQuery.value(1).toInt();
                int available = categoryQuery.value(2).toInt();
                int inUse = categoryQuery.value(3).toInt();
                int maintenance = categoryQuery.value(4).toInt();
                
                categoryTable->insertRow(row);
                categoryTable->setItem(row, 0, new QTableWidgetItem(category));
                categoryTable->setItem(row, 1, new QTableWidgetItem(QString::number(total)));
                categoryTable->setItem(row, 2, new QTableWidgetItem(QString::number(available)));
                categoryTable->setItem(row, 3, new QTableWidgetItem(QString::number(inUse)));
                categoryTable->setItem(row, 4, new QTableWidgetItem(QString::number(maintenance)));
                
                row++;
            }
            categoryTable->resizeColumnsToContents();
        } else {
            qDebug() << "Error querying category distribution:" << categoryQuery.lastError().text();
        }
    } else {
        qDebug() << "Warning: Category stats table not available, skipping table population";
    }
    
    // Calculate percentages for charts
    double totalForPercent = availableCount + inUseCount + maintenanceCount + outOfOrderCount;
    double availablePercent = (totalForPercent > 0) ? (availableCount / totalForPercent) * 100.0 : 0.0;
    double inUsePercent = (totalForPercent > 0) ? (inUseCount / totalForPercent) * 100.0 : 0.0;
    double maintenancePercent = (totalForPercent > 0) ? (maintenanceCount / totalForPercent) * 100.0 : 0.0;
    double outOfOrderPercent = (totalForPercent > 0) ? (outOfOrderCount / totalForPercent) * 100.0 : 0.0;
    
    qDebug() << "Percentages - Available:" << availablePercent << "% In Use:" << inUsePercent 
             << "% Maintenance:" << maintenancePercent << "% Out of Order:" << outOfOrderPercent << "%";
    
        // --- PIE CHART CREATION ---
    if (totalForPercent > 0) {
        // Use QPieSeries directly as QtCharts namespace seems to be causing issues or is implicit
        QPieSeries *series = new QPieSeries();

        // Add slices
        QPieSlice *sliceAvail = series->append("Available", availableCount);
        QPieSlice *sliceReserved = series->append("Reserved", inUseCount);
        QPieSlice *sliceMaint = series->append("Maintenance", maintenanceCount);
        QPieSlice *sliceBroken = series->append("Out of Order", outOfOrderCount);

        // Define colors matching the design system
        QColor colorAvailable(40, 167, 69);   // Success Green
        QColor colorReserved(255, 153, 0);    // Warning Orange
        QColor colorMaintenance(220, 53, 69); // Danger Red
        QColor colorBroken(220, 53, 69);      // Danger Red (same as Maintenance per table style)

        // Customize slices
        sliceAvail->setBrush(colorAvailable);
        sliceAvail->setLabel(QString("Available: %1%").arg(QString::number(availablePercent, 'f', 1)));
        sliceAvail->setLabelVisible(availableCount > 0);
        sliceAvail->setLabelColor(QColor(44, 62, 80));

        sliceReserved->setBrush(colorReserved);
        sliceReserved->setLabel(QString("Reserved: %1%").arg(QString::number(inUsePercent, 'f', 1)));
        sliceReserved->setLabelVisible(inUseCount > 0);
        sliceReserved->setLabelColor(QColor(44, 62, 80));

        sliceMaint->setBrush(colorMaintenance);
        sliceMaint->setLabel(QString("Maintenance: %1%").arg(QString::number(maintenancePercent, 'f', 1)));
        sliceMaint->setLabelVisible(maintenanceCount > 0);
        sliceMaint->setLabelColor(QColor(44, 62, 80));

        sliceBroken->setBrush(colorBroken);
        sliceBroken->setLabel(QString("Out of Order: %1%").arg(QString::number(outOfOrderPercent, 'f', 1)));
        sliceBroken->setLabelVisible(outOfOrderCount > 0);
        sliceBroken->setLabelColor(QColor(44, 62, 80));

        // Explode the largest slice for emphasis
        QPieSlice *largestSlice = nullptr;
        double maxVal = -1;
        if (availableCount > maxVal) { maxVal = availableCount; largestSlice = sliceAvail; }
        if (inUseCount > maxVal) { maxVal = inUseCount; largestSlice = sliceReserved; }
        if (maintenanceCount > maxVal) { maxVal = maintenanceCount; largestSlice = sliceMaint; }
        if (outOfOrderCount > maxVal) { maxVal = outOfOrderCount; largestSlice = sliceBroken; }
        
        if (largestSlice) {
            largestSlice->setExploded(true);
            largestSlice->setLabelVisible(true);
            largestSlice->setPen(QPen(Qt::darkGray, 2));
        }

        // Create Chart
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Equipment Status Breakdown");
        chart->setTitleFont(QFont("Segoe UI", 12, QFont::Bold));
        chart->setTitleBrush(QBrush(QColor(44, 62, 80)));
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setBackgroundVisible(false); // Transparent background

        // Legend customization
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->legend()->setFont(QFont("Segoe UI", 9));
        chart->legend()->setLabelColor(QColor(44, 62, 80));

        // Create Chart View
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFrameShape(QFrame::NoFrame);
        chartView->setStyleSheet("background: transparent;");

        // Add to UI Frame
        // Robustly handle existing layout
        QLayout *existingLayout = ui->equipmentStatsFrame->layout();
        QVBoxLayout *layout = nullptr;

        if (existingLayout) {
            // Check if it's already a QVBoxLayout
            layout = qobject_cast<QVBoxLayout*>(existingLayout);
            
            if (layout) {
                // It is a VBox, clear it
                QLayoutItem *item;
                while ((item = layout->takeAt(0)) != nullptr) {
                    if (item->widget()) delete item->widget();
                    delete item;
                }
            } else {
                // It's some other layout, delete it so we can set a new one
                delete existingLayout;
                existingLayout = nullptr;
            }
        }

        if (!layout) {
            layout = new QVBoxLayout(ui->equipmentStatsFrame);
            // ADJUST PLACEMENT HERE: setContentsMargins(left, top, right, bottom)
            // Adding 30px to left and top to move it "a little to the right and the bottom"
            layout->setContentsMargins(250, 70, 0, 0);
        }
        
        layout->addWidget(chartView);
        
        qDebug() << "Pie chart created and added to UI";
    } else {
        qDebug() << "No data for chart";
    }
    
    qDebug() << "=== populateEquipmentStatistics() Completed ===";
}
