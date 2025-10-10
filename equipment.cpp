#include "equipment.h"
#include "ui_equipment.h"
#include <QMessageBox>

Equipment::Equipment(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Equipment)
{
    ui->setupUi(this);
}

Equipment::~Equipment()
{
    delete ui;
}

void Equipment::on_addEquipmentButton_clicked()
{
    QMessageBox::information(this, "Success", "Equipment added successfully!");
}
