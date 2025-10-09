#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"

DashboardWindow::DashboardWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DashboardWindow)
{
    ui->setupUi(this);

    // Initialisation des pages
    memberPage = new MemberManagement(this);
    activityPage = new ActivityManagement(this);

    // Ajout dans le stackedWidget
    ui->stackedWidget->addWidget(memberPage);    // index 0
    ui->stackedWidget->addWidget(activityPage);  // index 1

    // Page par défaut
    ui->stackedWidget->setCurrentIndex(0);
}

DashboardWindow::~DashboardWindow()
{
    delete ui;
}

void DashboardWindow::on_dashboardButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // Dashboard/Members
}

void DashboardWindow::on_membersButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(memberPage);
}

void DashboardWindow::on_activitiesButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(activityPage);
}

void DashboardWindow::on_exitButton_clicked()
{
    close();
}
