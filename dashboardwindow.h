#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "membermanagement.h"
#include "activitymanagement.h"

namespace Ui {
class DashboardWindow;
}

class DashboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = nullptr);
    ~DashboardWindow();

private slots:
    void on_dashboardButton_clicked();
    void on_membersButton_clicked();
    void on_activitiesButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::DashboardWindow *ui;
    MemberManagement *memberPage;
    ActivityManagement *activityPage;
};

#endif // DASHBOARDWINDOW_H
