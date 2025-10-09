#ifndef ACTIVITYMANAGEMENT_H
#define ACTIVITYMANAGEMENT_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <QIcon>
#include <QResource>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class ActivityManagement;
}
QT_END_NAMESPACE

class ActivityManagement : public QMainWindow
{
    Q_OBJECT

public:
    ActivityManagement(QWidget *parent = nullptr);
    ~ActivityManagement();

private slots:
    void onSearchActivities();
    void onConfirmAddActivity();
    void onConfirmUpdateActivity();
    void onEditActivity(int row);
    void onDeleteActivity(int row);

private:
    Ui::ActivityManagement *ui;
    
    void setupConnections();
    void setupActivityTable();
    void setupActivityStatisticsTable();
    void populateActivityTable();
    void populateActivityStatistics();
    void setupIcons();
    void setupTabIcons();
    void clearActivityForm();
};

#endif // ACTIVITYMANAGEMENT_H