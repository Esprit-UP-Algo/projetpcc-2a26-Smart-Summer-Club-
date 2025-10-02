#include "login.h"
#include "ui_login.h"
#include "membersmainwindow.h"
#include <QMessageBox>
login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_log_in_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password ->text();
    if (username=="admin"&&password=="1234"){
        this->close();
        membersMainWindow *h = new membersMainWindow();
        h->show();

    }else {
        QMessageBox::warning(this,"Incorrect username or password!","sorry");

    }

}

