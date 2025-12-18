#include "equipment.h"
#include "ui_employeradmin.h"
#include "employeelogspanel.h"
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
#include <QJsonObject>
#include <QJsonDocument>
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
#include <QSqlDatabase>

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
    connect(ui->equipmentSearchLineEdit, &QLineEdit::textChanged,
            this, &Equipment::onSearchEquipment);
    connect(ui->equipmentRefreshButton, &QPushButton::clicked,
            this, &Equipment::onRefreshEquipment);
    connect(ui->equipmentSortButton, &QPushButton::clicked,
            this, &Equipment::onSortEquipment);
    connect(ui->equipmentExportButton, &QPushButton::clicked,
            this, &Equipment::onExportEquipment);

    // Connect tab change to populate statistics when statistics tab is accessed
    // Statistics tab is at index 2 (0=list, 1=add, 2=statistics)
    if (ui->equipmentTabWidget) {
        connect(ui->equipmentTabWidget, &QTabWidget::currentChanged,
                this, [this](int index) {
                    if (index == 2) { // Statistics tab index
                        populateEquipmentStatistics();
                    }
                });
    }

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
        "SELECT ID_EQ, NAME, CATEGORY, TOTAL_QUANTITY, AVAILABLE, IN_USE, "
        "UNDER_MAINTENANCE, NVL(LOCATION,'Non spécifié') "
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
        int avail = q.value(4).toInt();
        int inUse = q.value(5).toInt();
        int maint = q.value(6).toInt();
        QString loc = q.value(7).toString();

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
        QString status = QString("%1 avail").arg(avail);
        if (inUse) status += QString(", %1 in use").arg(inUse);
        if (maint) status += QString(", %1 maint").arg(maint);
        QTableWidgetItem *itStat = new QTableWidgetItem(status);

        // Set colors that work well on light background
        if (maint) {
            itStat->setForeground(QBrush(QColor(220, 53, 69))); // Bootstrap danger red
            itStat->setBackground(QBrush(QColor(255, 243, 245))); // Light red background
        } else if (inUse) {
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
                    
                    // Log the DELETE action
                    QJsonObject beforeData;
                    beforeData["id"] = QString::number(id);
                    beforeData["name"] = name;
                    
                    QJsonDocument doc(beforeData);
                    EmployeeLogsPanel::logAction("DELETE", "Equipment", QString::number(id), 
                                               doc.toJson(QJsonDocument::Compact), "", 
                                               QString("Equipment deleted: %1 (ID: %2)")
                                               .arg(name, QString::number(id)));
                    
                    QMessageBox::information(parentWidget, "Success",
                                             QString("Equipment '%1' has been deleted successfully.").arg(name));
                    loadEquipmentTable(); // Refresh the table
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
    int qty = ui->equipmentQuantitySpinBox->value();
    QString status = ui->equipmentStatusComboBox->currentText();
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

    QSqlQuery q;
    q.prepare(
        "INSERT INTO EQUIPEMENTS (EQUIP_CODE, NAME, CATEGORY, TOTAL_QUANTITY, AVAILABLE, "
        "IN_USE, UNDER_MAINTENANCE, STATUS, BRAND, MODEL, PURCHASE_DATE, PURCHASE_PRICE, LOCATION) "
        "VALUES (:code, :name, :cat, :qty, :avail, 0, 0, :status, :brand, :model, :date, :price, 'N/A')"
        );
    q.bindValue(":code", code);
    q.bindValue(":name", name);
    q.bindValue(":cat", cat);
    q.bindValue(":qty", qty);
    q.bindValue(":avail", qty);
    q.bindValue(":status", status);
    q.bindValue(":brand", brand);
    q.bindValue(":model", model);
    q.bindValue(":date", pDate);
    q.bindValue(":price", priceValue);

    qDebug() << "=== Starting onConfirmAdd() ===";
    qDebug() << "Price value:" << priceValue;
    qDebug() << "Price is null:" << priceValue.isNull();
    qDebug() << "Price is valid:" << priceValue.isValid();

    if (q.exec()) {
        qDebug() << "Add successful";
        
        // Log the CREATE action
        QJsonObject equipmentData;
        equipmentData["equip_code"] = code;
        equipmentData["name"] = name;
        equipmentData["category"] = cat;
        equipmentData["total_quantity"] = qty;
        equipmentData["available"] = qty;
        equipmentData["status"] = status;
        equipmentData["brand"] = brand;
        equipmentData["model"] = model;
        equipmentData["purchase_date"] = pDate.toString("yyyy-MM-dd");
        equipmentData["purchase_price"] = priceValue.isNull() ? "NULL" : priceValue.toString();
        equipmentData["location"] = "N/A";
        
        QJsonDocument doc(equipmentData);
        EmployeeLogsPanel::logAction("CREATE", "Equipment", code, "", 
                                   doc.toJson(QJsonDocument::Compact), 
                                   QString("New equipment added: %1 (%2)")
                                   .arg(name, code));
        
        clearForm();
        loadEquipmentTable();  // DISPLAYS IMMEDIATELY
        QMessageBox::information(parentWidget, "Success", "Added!");
    } else {
        qDebug() << "Add failed:" << q.lastError().text();
        QMessageBox::critical(parentWidget, "Error", "Failed to add equipment: " + q.lastError().text());
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
    int qty = ui->equipmentQuantitySpinBox->value();
    QString status = ui->equipmentStatusComboBox->currentText();
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

    QSqlQuery q;
    q.prepare("UPDATE EQUIPEMENTS SET NAME=:n, CATEGORY=:c, TOTAL_QUANTITY=:q, STATUS=:s, BRAND=:b, MODEL=:m, PURCHASE_PRICE=:p WHERE ID_EQ=:id");
    q.bindValue(":n", name);
    q.bindValue(":c", cat);
    q.bindValue(":q", qty);
    q.bindValue(":s", status);
    q.bindValue(":b", brand);
    q.bindValue(":m", model);
    q.bindValue(":p", priceValue);
    q.bindValue(":id", id);

    qDebug() << "=== Starting onConfirmUpdate() ===";
    qDebug() << "Updating equipment ID:" << id;
    qDebug() << "Price value:" << priceValue;
    qDebug() << "Price is null:" << priceValue.isNull();
    qDebug() << "Price is valid:" << priceValue.isValid();

    if (q.exec()) {
        qDebug() << "Update successful";
        
        // Log the UPDATE action
        QJsonObject afterData;
        afterData["id"] = QString::number(id);
        afterData["name"] = name;
        afterData["category"] = cat;
        afterData["total_quantity"] = qty;
        afterData["status"] = status;
        afterData["brand"] = brand;
        afterData["model"] = model;
        afterData["purchase_price"] = priceValue.isNull() ? "NULL" : priceValue.toString();
        
        QJsonDocument doc(afterData);
        EmployeeLogsPanel::logAction("UPDATE", "Equipment", QString::number(id), "", 
                                   doc.toJson(QJsonDocument::Compact), 
                                   QString("Equipment modified: %1 (ID: %2)")
                                   .arg(name, QString::number(id)));
        
        loadEquipmentTable();
        clearForm();
        QMessageBox::information(parentWidget, "Success", "Updated!");
    } else {
        qDebug() << "Update failed:" << q.lastError().text();
        QMessageBox::critical(parentWidget, "Error", "Failed to update equipment: " + q.lastError().text());
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
    q.prepare("SELECT ID_EQ, NAME, CATEGORY, TOTAL_QUANTITY, AVAILABLE, IN_USE, UNDER_MAINTENANCE, NVL(LOCATION,'Non spécifié') "
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
        int inUse = q.value(5).toInt();
        int maint = q.value(6).toInt();
        QString loc = q.value(7).toString();

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
        QString status = QString("%1 avail").arg(avail);
        if (inUse) status += QString(", %1 in use").arg(inUse);
        if (maint) status += QString(", %1 maint").arg(maint);
        QTableWidgetItem *itStat = new QTableWidgetItem(status);

        // Set colors that work well on light background
        if (maint) {
            itStat->setForeground(QBrush(QColor(220, 53, 69))); // Bootstrap danger red
            itStat->setBackground(QBrush(QColor(255, 243, 245))); // Light red background
        } else if (inUse) {
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
                    
                    // Log the DELETE action (from search)
                    QJsonObject beforeData;
                    beforeData["id"] = QString::number(id);
                    beforeData["name"] = name;
                    beforeData["deleted_from"] = "search_results";
                    
                    QJsonDocument doc(beforeData);
                    EmployeeLogsPanel::logAction("DELETE", "Equipment", QString::number(id), 
                                               doc.toJson(QJsonDocument::Compact), "", 
                                               QString("Equipment deleted from search: %1 (ID: %2)")
                                               .arg(name, QString::number(id)));
                    
                    QMessageBox::information(parentWidget, "Success",
                                             QString("Equipment '%1' has been deleted successfully.").arg(name));
                    loadEquipmentTable(); // Refresh the table
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

    // REMOVED: ui->equipmentTable->resizeColumnsToContents(); // This was causing columns to become narrower

    qDebug() << "=== onSearchEquipment() Completed ===";
}

void Equipment::onRefreshEquipment()
{
    qDebug() << "=== Starting onRefreshEquipment() ===";
    
    // Clear search field
    ui->equipmentSearchLineEdit->clear();
    
    // Reload all equipment from database
    loadEquipmentTable();
    
    QMessageBox::information(parentWidget, "Refresh", "Equipment list refreshed successfully!");
    
    qDebug() << "=== onRefreshEquipment() Completed ===";
}

void Equipment::onSortEquipment()
{
    qDebug() << "=== Starting onSortEquipment() ===";

    // Cycle through sort options: Name -> Type -> Status -> Quantity
    static int sortColumn = 0; // 0=Name, 1=Type, 2=Total Qty, 4=Status
    static bool ascending = true;
    
    QString sortOption;
    
    switch(sortColumn) {
        case 0:
            sortOption = "Name";
            break;
        case 1:
            sortOption = "Type";
            break;
        case 2:
            sortOption = "Quantity";
            break;
        case 4:
            sortOption = "Status";
            break;
    }
    
    ui->equipmentTable->sortByColumn(sortColumn, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    
    QString direction = ascending ? "Ascending" : "Descending";
    ui->equipmentSortButton->setText(QString("Sort by %1 (%2)").arg(sortOption).arg(direction.left(3)));
    
    qDebug() << "Sorting by" << sortOption << direction;
    
    // Toggle direction
    ascending = !ascending;
    
    // If we've done both ascending and descending, move to next column
    if (ascending) {
        sortColumn++;
        if (sortColumn == 3) sortColumn = 4; // Skip Location column (index 3)
        if (sortColumn > 4) sortColumn = 0; // Reset to Name
    }

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
    if (ui->outOfOrderNumber) {
        ui->outOfOrderNumber->setText(QString::number(outOfOrderCount));
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
        
        // Set size constraints to prevent chart from being too large
        chartView->setMinimumSize(420, 360);
        chartView->setMaximumSize(600, 480);

        // Add to UI Frame - equipmentChartFrame
        QVBoxLayout *chartLayout = qobject_cast<QVBoxLayout*>(ui->equipmentChartFrame->layout());
        
        if (!chartLayout) {
            // Fallback: create new layout if somehow missing
            chartLayout = new QVBoxLayout(ui->equipmentChartFrame);
        }
        
        // Set proper margins and spacing
        chartLayout->setContentsMargins(5, 5, 5, 5);
        chartLayout->setSpacing(0);

        // Remove any previous chart widgets
        while (chartLayout->count() > 0) {
            QLayoutItem *item = chartLayout->takeAt(0);
            if (item->widget()) item->widget()->deleteLater();
            delete item;
        }

        // Add chart to layout
        chartLayout->addWidget(chartView);
        
        qDebug() << "Pie chart created and added to UI (bottom-right anchored)";
    } else {
        qDebug() << "No data for chart";
    }
    
    qDebug() << "=== populateEquipmentStatistics() Completed ===";
}