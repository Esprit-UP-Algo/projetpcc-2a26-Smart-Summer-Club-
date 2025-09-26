#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include <QDebug>
#include <QPixmap>
adminmainwindow::adminmainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::adminmainwindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Khalil/Documents/Admin/assests/VibraClubLogo.png");

    // Connect buttons to stacked widget page switching
    connect(ui->adminBtnAddEmployee, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetEditAndAdd->setCurrentWidget(ui->addEmployeePage);
    });
    connect(ui->adminBtnEditEmployee, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetEditAndAdd->setCurrentWidget(ui->editEmplyerPage);
    });

    // Toggle stats/main panel in stackedWidgetMainContentView
    connect(ui->adminBtnShowStats, &QPushButton::clicked, this, [this]() {
        int statsIndex = ui->stackedWidgetMainContentView->indexOf(ui->stats);
        int mainIndex = ui->stackedWidgetMainContentView->indexOf(ui->mainPanel);
        int currentIndex = ui->stackedWidgetMainContentView->currentIndex();
        if (currentIndex == mainIndex) {
            ui->stackedWidgetMainContentView->setCurrentIndex(statsIndex);
            ui->adminBtnShowStats->setText("Show Main Panel");
        } else {
            ui->stackedWidgetMainContentView->setCurrentIndex(mainIndex);
            ui->adminBtnShowStats->setText("Show Statistics");
        }
    });

}

adminmainwindow::~adminmainwindow()
{
    delete ui;
}

