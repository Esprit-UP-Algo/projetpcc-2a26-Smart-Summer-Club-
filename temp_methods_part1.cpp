
// ============================================================================
// EQUIPMENT RESERVATION METHODS
// ============================================================================

void Activity::setupEquipmentReservation()
{
    if (!ui) return;
    
    // Connecter les boutons de réservation
    connect(ui->refreshEquipmentButton, &QPushButton::clicked,
            this, &Activity::refreshAvailableEquipment);
    connect(ui->addToReservationButton, &QPushButton::clicked,
            this, &Activity::addSelectedToReservation);
    connect(ui->confirmReservationButton, &QPushButton::clicked,
            this, &Activity::confirmEquipmentReservation);
    connect(ui->clearReservationButton, &QPushButton::clicked,
            this, &Activity::clearReservation);
    
    // Quand la date change, rafraîchir les équipements disponibles
    connect(ui->eventDateEdit, &QDateEdit::dateChanged,
            this, &Activity::refreshAvailableEquipment);
    
    // Initialiser les tables
    setupAvailableEquipmentTable();
    setupReservedEquipmentTable();
}

void Activity::setupAvailableEquipmentTable()
{
    if (!ui) return;
    
    ui->availableEquipmentTable->setColumnCount(5);
    QStringList headers = {"Select", "Equipment Name", "Category", "Available Qty", "Reserve Qty"};
    ui->availableEquipmentTable->setHorizontalHeaderLabels(headers);
    ui->availableEquipmentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // Set column widths
    ui->availableEquipmentTable->setColumnWidth(0, 60);   // Select
    ui->availableEquipmentTable->setColumnWidth(1, 200);  // Name
    ui->availableEquipmentTable->setColumnWidth(2, 150);  // Category
    ui->availableEquipmentTable->setColumnWidth(3, 100);  // Available Qty
    ui->availableEquipmentTable->setColumnWidth(4, 100);  // Reserve Qty
}

void Activity::setupReservedEquipmentTable()
{
    if (!ui) return;
    
    ui->reservedEquipmentTable->setColumnCount(3);
    QStringList headers = {"Equipment Name", "Reserved Qty", "Actions"};
    ui->reservedEquipmentTable->setHorizontalHeaderLabels(headers);
    ui->reservedEquipmentTable->setColumnWidth(0, 200);  // Name
    ui->reservedEquipmentTable->setColumnWidth(1, 100);  // Qty
    ui->reservedEquipmentTable->setColumnWidth(2, 100);  // Actions
}

void Activity::refreshAvailableEquipment()
{
    if (!ui) return;
    
    QDate selectedDate = ui->eventDateEdit->date();
    QSqlQueryModel* model = getAvailableEquipment(selectedDate);
    
    if (!model) return;
    
    ui->availableEquipmentTable->setRowCount(0);
    
    for (int row = 0; row < model->rowCount(); ++row) {
        int equipmentId = model->record(row).value("ID_EQ").toInt();
        QString name = model->record(row).value("NAME").toString();
        QString category = model->record(row).value("CATEGORY").toString();
        int availableQty = model->record(row).value("QTY_AVAILABLE").toInt();
        
        ui->availableEquipmentTable->insertRow(row);
        
        // Checkbox for selection
        QTableWidgetItem* selectItem = new QTableWidgetItem();
        selectItem->setCheckState(Qt::Unchecked);
        ui->availableEquipmentTable->setItem(row, 0, selectItem);
        
        // Equipment info
        ui->availableEquipmentTable->setItem(row, 1, new QTableWidgetItem(name));
        ui->availableEquipmentTable->setItem(row, 2, new QTableWidgetItem(category));
        ui->availableEquipmentTable->setItem(row, 3, new QTableWidgetItem(QString::number(availableQty)));
        
        // Quantity spinbox
        QSpinBox* quantitySpinBox = new QSpinBox();
        quantitySpinBox->setMinimum(1);
        quantitySpinBox->setMaximum(availableQty);
        quantitySpinBox->setValue(1);
        ui->availableEquipmentTable->setCellWidget(row, 4, quantitySpinBox);
    }
    
    delete model;
}

QSqlQueryModel* Activity::getAvailableEquipment(const QDate& date)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    // Query to get equipment that's available on the selected date
    // This excludes equipment already reserved for other activities on the same date
    QString query = 
        "SELECT e.ID_EQ, e.NAME, e.CATEGORY, "
        "NVL(e.QUANTITY_AVAILABLE, e.AVAILABLE) AS QTY_AVAILABLE "
        "FROM EQUIPEMENTS e "
        "WHERE (NVL(e.QUANTITY_AVAILABLE, e.AVAILABLE) > 0) "
        "AND e.ID_EQ NOT IN ("
        "    SELECT r.ID_EQ FROM RESERVATIONS r "
        "    JOIN ACTIVITIES a ON r.ID_ACTIVITY = a.ID_A "
        "    WHERE a.EVENT_DATE = :selectedDate"
        ") "
        "ORDER BY e.NAME";
    
    QSqlQuery q;
    q.prepare(query);
    q.bindValue(":selectedDate", date);
    
    if (q.exec()) {
        model->setQuery(q);
    } else {
        qDebug() << "Error fetching available equipment:" << q.lastError().text();
        delete model;
        return nullptr;
    }
    
    return model;
}
