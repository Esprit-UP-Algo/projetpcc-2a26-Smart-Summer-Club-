#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QMainWindow>

namespace Ui {
class Equipment;
}

class Equipment : public QMainWindow
{
    Q_OBJECT

public:
    explicit Equipment(QWidget *parent = nullptr);
    ~Equipment();

private slots:
    void on_addEquipmentButton_clicked();

private:
    Ui::Equipment *ui;
};

#endif // EQUIPMENT_H
