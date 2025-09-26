#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class adminmainwindow;
}
QT_END_NAMESPACE

class adminmainwindow : public QMainWindow
{
    Q_OBJECT

public:
    adminmainwindow(QWidget *parent = nullptr);
    ~adminmainwindow();

private slots:

private:
    Ui::adminmainwindow *ui;
};
#endif // ADMINMAINWINDOW_H
