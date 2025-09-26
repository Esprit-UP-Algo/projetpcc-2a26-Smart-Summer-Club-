#ifndef MEMBERMAINWINDOW_H
#define MEMBERMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class membermainwindow;
}
QT_END_NAMESPACE

class membermainwindow : public QMainWindow
{
    Q_OBJECT

public:
    membermainwindow(QWidget *parent = nullptr);
    ~membermainwindow();

private:
    Ui::membermainwindow *ui;
};
#endif // MEMBERMAINWINDOW_H
