#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_equipmentButton_clicked();
    void on_paymentsButton_clicked();
    void on_exportStatsButton_clicked();
    void on_addPaymentButton_clicked();
    void on_clearPaymentFormButton_clicked();
    void on_addEquipmentButton_clicked();
    void on_paymentSearchButton_clicked();
    void on_paymentSortButton_clicked();

private:
    Ui::MainWindow *ui;
    void setupPaymentTable();
    void setupEquipmentTable();
    void updatePaymentStatistics();
};
#endif // MAINWINDOW_H
