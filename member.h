#ifndef MEMBER_H
#define MEMBER_H

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

class Member : public QObject
{
    Q_OBJECT

public:
    explicit Member(Ui::EmployerAdmin *ui, QWidget *parent = nullptr);
    ~Member();

    // Setup functions
    void setupMemberTable();
    
    // Member management functions
    void onEditMember(int row);
    void onDeleteMember(int row);
    void onSortMembers();
    void onExportMembers();

private:
    Ui::EmployerAdmin *ui;
    QWidget *parentWidget;
    
    // Helper functions
    void sortTableByName(QTableWidget* table, int nameColumnIndex = 1);
    bool exportTableToCsv(QTableWidget* table, const QString& defaultName);
    bool exportTableToPdf(QTableWidget* table, const QString& defaultName, const QString& title);
};

#endif // MEMBER_H