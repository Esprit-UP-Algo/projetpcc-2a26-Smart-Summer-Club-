#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QFileInfo>
#include <QIcon>
#include <QDebug>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDateEdit>

// Forward declaration
namespace Ui {
class EmployerAdmin;
}

class Equipment : public QObject
{
    Q_OBJECT

public:
    explicit Equipment(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Equipment();

    // Setup functions
    void setupEquipmentTable();
    void setupEquipmentDetailsTable();
    
    // Equipment management functions
    void onEquipmentDetails(const QStringList &equipmentData);
    void onEquipmentManage(const QStringList &equipmentData);
    void onEquipmentDelete(const QStringList &equipmentData, int row);
    void onSortEquipment();
    void onExportEquipment();
    
    // Details table functions
    void showEquipmentDetailsTable(const QStringList &equipmentData);
    void hideEquipmentDetailsTable();

private:
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    
    // Dynamic equipment details table
    QTableWidget *equipmentDetailsTable;
    QWidget *equipmentDetailsWidget;
    bool isDetailsTableVisible;
    
    // Helper functions
    void sortTableByName(QTableWidget* table, int nameColumnIndex = 1);
    bool exportTableToCsv(QTableWidget* table, const QString& defaultName);
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);
};

#endif // EQUIPMENT_H