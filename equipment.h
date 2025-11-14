#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QBrush>
#include <QColor>
#include <QRandomGenerator>

namespace Ui {
class EmployerAdmin;
}

class Equipment : public QObject
{
    Q_OBJECT

public:
    explicit Equipment(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Equipment();

    void setupEquipmentTable();
    void loadEquipmentTable();
    void clearForm();

private:
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    QTableWidget *equipmentDetailsTable;
    QWidget *equipmentDetailsWidget;
    QWidget *sidePanelWidget;
    bool isDetailsTableVisible;
    bool isSidePanelVisible;
    int currentSelectedRow;

    void setupEquipmentDetailsTable();
    void createSidePanel();
    bool codeExists(const QString &code);

public slots:
    void onConfirmAdd();
    void onConfirmUpdate();
    void onSearchEquipment();
    void onSortEquipment();
    void onExportEquipment();
    void onTableRowClicked(int row, int column);
    void hideEquipmentDetailsTable();

    // REMOVED: onEditEquipment(), onDeleteEquipment()
    // THEY ARE NOW LAMBDA-ONLY
};

#endif // EQUIPMENT_H
