#ifndef MEMBERMANAGEMENT_H
#define MEMBERMANAGEMENT_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QFileInfo>
#include <QIcon>
#include <QResource>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QAbstractItemView>
#include <QHeaderView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MemberManagement;
}
QT_END_NAMESPACE

class MemberManagement : public QMainWindow
{
    Q_OBJECT

public:
    MemberManagement(QWidget *parent = nullptr);
    ~MemberManagement();

private slots:
    void onNavigationButtonClicked();
    void onEditMember(int row);
    void onDeleteMember(int row);

private:
    Ui::MemberManagement *ui;
    QButtonGroup *navigationButtonGroup;
    
    void setupConnections();
    void setupIcons();  // Optional icon setup
    void setupTabIcons(); // Set icons for tab widgets
    void setupButtonStyling();  // Apply consistent button styling
    void updateNavigationStyle();
    void populateMemberTable();
    void populateMemberStatistics();
    void setupMemberTable();
    void setupMemberStatisticsTable();
};

#endif // MEMBERMANAGEMENT_H
