#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QTime>
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
#include <QTimeEdit>

// Forward declaration
namespace Ui {
class EmployerAdmin;
}

class Activity : public QObject
{
    Q_OBJECT

public:
    explicit Activity(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Activity();

    // Setup functions
    void setupActivityTable();
    
    // Activity management functions
    void onEditActivity(int row);
    void onDeleteActivity(int row);
    void onSortActivities(int index);
    void onExportActivities();

private:
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    
    // Helper functions
    void sortTableByName(QTableWidget* table, int nameColumnIndex = 1);
    bool exportTableToCsv(QTableWidget* table, const QString& defaultName);
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);
};

#endif // ACTIVITY_H