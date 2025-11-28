
void Activity::addSelectedToReservation()
{
    if (!ui) return;
    
    for (int row = 0; row < ui->availableEquipmentTable->rowCount(); ++row) {
        QTableWidgetItem* selectItem = ui->availableEquipmentTable->item(row, 0);
        
        if (selectItem && selectItem->checkState() == Qt::Checked) {
            QString equipmentName = ui->availableEquipmentTable->item(row, 1)->text();
            int availableQty = ui->availableEquipmentTable->item(row, 3)->text().toInt();
            
            QSpinBox* quantitySpinBox = qobject_cast<QSpinBox*>(
                ui->availableEquipmentTable->cellWidget(row, 4));
            
            if (quantitySpinBox) {
                int reserveQty = quantitySpinBox->value();
                
                // Get equipment ID (you might need to store this in the table)
                QSqlQuery q;
                q.prepare("SELECT ID_EQ FROM EQUIPEMENTS WHERE NAME = :name");
                q.bindValue(":name", equipmentName);
                if (q.exec() && q.next()) {
                    int equipmentId = q.value(0).toInt();
                    reservedEquipment[equipmentId] = reserveQty;
                    
                    // Add to reserved table
                    addToReservedTable(equipmentId, equipmentName, reserveQty);
                }
            }
        }
    }
    
    updateReservedTotal();
}

void Activity::addToReservedTable(int equipmentId, const QString& name, int quantity)
{
    if (!ui) return;
    
    int row = ui->reservedEquipmentTable->rowCount();
    ui->reservedEquipmentTable->insertRow(row);
    
    ui->reservedEquipmentTable->setItem(row, 0, new QTableWidgetItem(name));
    ui->reservedEquipmentTable->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
    
    // Remove button
    QPushButton* removeButton = new QPushButton("Remove");
    connect(removeButton, &QPushButton::clicked, this, [this, equipmentId, row]() {
        reservedEquipment.remove(equipmentId);
        ui->reservedEquipmentTable->removeRow(row);
        updateReservedTotal();
    });
    
    ui->reservedEquipmentTable->setCellWidget(row, 2, removeButton);
}

void Activity::updateReservedTotal()
{
    if (!ui) return;
    
    int totalItems = 0;
    for (int quantity : reservedEquipment) {
        totalItems += quantity;
    }
    
    ui->reservedTotalLabel->setText(QString("Total Reserved Items: %1").arg(totalItems));
}

void Activity::confirmEquipmentReservation()
{
    if (reservedEquipment.isEmpty()) {
        QMessageBox::information(parentWidget, "Info", "No equipment selected for reservation.");
        return;
    }
    
    if (currentActivityId <= 0) {
        QMessageBox::warning(parentWidget, "Warning", "Please save the activity first before reserving equipment.");
        return;
    }
    
    // Save reservations to database
    bool success = true;
    for (auto it = reservedEquipment.begin(); it != reservedEquipment.end(); ++it) {
        if (!reserveEquipment(it.key(), it.value(), currentActivityId)) {
            success = false;
        }
    }
    
    if (success) {
        QMessageBox::information(parentWidget, "Success", "Equipment reserved successfully!");
        clearReservation();
    } else {
        QMessageBox::warning(parentWidget, "Warning", "Some equipment could not be reserved.");
    }
}

bool Activity::reserveEquipment(int equipmentId, int quantity, int activityId)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO RESERVATIONS (ID_ACTIVITY, ID_EQ, QUANTITY, DATE_DEBUT, DATE_FIN, STATUS) "
        "VALUES (:activityId, :equipmentId, :quantity, :startDate, :endDate, 'Reserved')"
    );
    
    QDate eventDate = ui->eventDateEdit->date();
    
    query.bindValue(":activityId", activityId);
    query.bindValue(":equipmentId", equipmentId);
    query.bindValue(":quantity", quantity);
    query.bindValue(":startDate", eventDate);
    query.bindValue(":endDate", eventDate); // Same day reservation
    
    if (query.exec()) {
        // Update equipment quantities
        QSqlQuery updateQuery;
        updateQuery.prepare(
            "UPDATE EQUIPEMENTS SET "
            "QUANTITY_AVAILABLE = QUANTITY_AVAILABLE - :qty, "
            "QUANTITY_RESERVED = QUANTITY_RESERVED + :qty "
            "WHERE ID_EQ = :id"
        );
        updateQuery.bindValue(":qty", quantity);
        updateQuery.bindValue(":id", equipmentId);
        
        return updateQuery.exec();
    }
    
    return false;
}

void Activity::clearReservation()
{
    if (!ui) return;
    
    reservedEquipment.clear();
    ui->reservedEquipmentTable->setRowCount(0);
    updateReservedTotal();
    
    // Uncheck all items in available table
    for (int row = 0; row < ui->availableEquipmentTable->rowCount(); ++row) {
        QTableWidgetItem* item = ui->availableEquipmentTable->item(row, 0);
        if (item) {
            item->setCheckState(Qt::Unchecked);
        }
    }
}
