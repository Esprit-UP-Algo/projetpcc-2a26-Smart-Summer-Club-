#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set payment button as active by default
    ui->paymentsButton->setChecked(true);
    ui->equipmentButton->setChecked(false);

    // Setup tables
    setupPaymentTable();
    setupEquipmentTable();
    updatePaymentStatistics();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPaymentTable()
{
    // Set column widths for payment table
    ui->paymentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Add sample data to payment table
    QStringList paymentHeaders = {"Transaction ID", "Date", "Description", "Type", "Amount", "Method", "Status", "Member ID"};
    ui->paymentTable->setColumnCount(paymentHeaders.size());
    ui->paymentTable->setHorizontalHeaderLabels(paymentHeaders);

    // Add sample payment data
    QStringList samplePayment1 = {"TXN001", "2024-01-15", "Monthly Membership", "Income", "TND 150.00", "Cash", "Completed", "MEM001"};
    QStringList samplePayment2 = {"TXN002", "2024-01-16", "Equipment Maintenance", "Expense", "TND 75.50", "Bank Transfer", "Completed", ""};

    ui->paymentTable->setRowCount(2);
    for(int i = 0; i < samplePayment1.size(); i++) {
        ui->paymentTable->setItem(0, i, new QTableWidgetItem(samplePayment1[i]));
        ui->paymentTable->setItem(1, i, new QTableWidgetItem(samplePayment2[i]));
    }
}

void MainWindow::setupEquipmentTable()
{
    // Set column widths for equipment table
    ui->equipmentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Add sample data to equipment table
    QStringList equipmentHeaders = {"Equipment ID", "Name", "Type", "Purchase Date", "Condition", "Status"};
    ui->equipmentTable->setColumnCount(equipmentHeaders.size());
    ui->equipmentTable->setHorizontalHeaderLabels(equipmentHeaders);

    // Add sample equipment data
    QStringList sampleEquipment1 = {"EQ001", "Treadmill Pro", "Cardio", "2023-05-10", "Good", "Available"};
    QStringList sampleEquipment2 = {"EQ002", "Weight Bench", "Strength", "2023-08-15", "Excellent", "Available"};

    ui->equipmentTable->setRowCount(2);
    for(int i = 0; i < sampleEquipment1.size(); i++) {
        ui->equipmentTable->setItem(0, i, new QTableWidgetItem(sampleEquipment1[i]));
        ui->equipmentTable->setItem(1, i, new QTableWidgetItem(sampleEquipment2[i]));
    }
}

void MainWindow::updatePaymentStatistics()
{
    // Update statistics cards with TND currency
    ui->totalIncomeValue->setText("TND 5,250.00");
    ui->totalExpenseValue->setText("TND 1,875.50");
    ui->netBalanceValue->setText("TND 3,374.50");

    // Setup payment method statistics table
    QStringList statsHeaders = {"Payment Method", "Total Transactions", "Total Amount", "Percentage"};
    ui->paymentMethodStatsTable->setColumnCount(statsHeaders.size());
    ui->paymentMethodStatsTable->setHorizontalHeaderLabels(statsHeaders);

    // Add sample statistics data
    QStringList stats1 = {"Cash", "45", "TND 2,250.00", "42.9%"};
    QStringList stats2 = {"Credit Card", "32", "TND 1,920.00", "36.6%"};
    QStringList stats3 = {"Bank Transfer", "18", "TND 1,080.00", "20.5%"};

    ui->paymentMethodStatsTable->setRowCount(3);
    for(int i = 0; i < stats1.size(); i++) {
        ui->paymentMethodStatsTable->setItem(0, i, new QTableWidgetItem(stats1[i]));
        ui->paymentMethodStatsTable->setItem(1, i, new QTableWidgetItem(stats2[i]));
        ui->paymentMethodStatsTable->setItem(2, i, new QTableWidgetItem(stats3[i]));
    }
}

void MainWindow::on_equipmentButton_clicked()
{
    ui->paymentsButton->setChecked(false);
    ui->equipmentButton->setChecked(true);
    ui->stackedWidget->setCurrentIndex(1); // Switch to equipment page
}

void MainWindow::on_paymentsButton_clicked()
{
    ui->paymentsButton->setChecked(true);
    ui->equipmentButton->setChecked(false);
    ui->stackedWidget->setCurrentIndex(0); // Switch to payment page
}

void MainWindow::on_exportStatsButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Export Statistics as CSV", "", "CSV Files (*.csv)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << "Payment Method,Total Transactions,Total Amount,Percentage\n";

    int rowCount = ui->paymentMethodStatsTable->rowCount();
    int colCount = ui->paymentMethodStatsTable->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem *item = ui->paymentMethodStatsTable->item(row, col);
            if (item) {
                out << item->text();
            }
            if (col < colCount - 1) {
                out << ",";
            }
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "Export Successful",
                             "Statistics exported to CSV successfully!");
}

void MainWindow::on_addPaymentButton_clicked()
{
    QString description = ui->paymentDescriptionEdit->text();
    double amount = ui->paymentAmountSpinBox->value();

    if (description.isEmpty() || amount <= 0) {
        QMessageBox::warning(this, "Error", "Please fill all required fields!");
        return;
    }

    QMessageBox::information(this, "Success",
                             QString("Payment added successfully!\nDescription: %1\nAmount: TND %2")
                                 .arg(description).arg(amount, 0, 'f', 2));

    // Clear form
    on_clearPaymentFormButton_clicked();
}

void MainWindow::on_clearPaymentFormButton_clicked()
{
    ui->paymentDescriptionEdit->clear();
    ui->paymentAmountSpinBox->setValue(0.0);
    ui->paymentMemberEdit->clear();
    ui->paymentTypeCombo->setCurrentIndex(0);
    ui->paymentMethodCombo->setCurrentIndex(0);
    ui->paymentStatusCombo->setCurrentIndex(0);
}

void MainWindow::on_addEquipmentButton_clicked()
{
    QString name = ui->equipmentNameLineEdit->text();
    QString type = ui->equipmentTypeComboBox->currentText();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter equipment name!");
        return;
    }

    QMessageBox::information(this, "Success",
                             QString("Equipment added successfully!\nName: %1\nType: %2")
                                 .arg(name).arg(type));

    // Clear form
    ui->equipmentNameLineEdit->clear();
    ui->equipmentTypeComboBox->setCurrentIndex(0);
    ui->conditionComboBox->setCurrentIndex(0);
}

void MainWindow::on_paymentSearchButton_clicked()
{
    QString searchText = ui->paymentSearchLineEdit->text();
    if (!searchText.isEmpty()) {
        QMessageBox::information(this, "Search",
                                 QString("Searching for: %1").arg(searchText));
    }
}

void MainWindow::on_paymentSortButton_clicked()
{
    QMessageBox::information(this, "Sort", "Payments sorted by date");
}
