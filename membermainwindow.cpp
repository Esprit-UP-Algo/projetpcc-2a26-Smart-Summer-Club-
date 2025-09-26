#include "membermainwindow.h"
#include "ui_membermainwindow.h"

membermainwindow::membermainwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::membermainwindow)
{
    ui->setupUi(this);
}

membermainwindow::~membermainwindow()
{
    delete ui;
}
