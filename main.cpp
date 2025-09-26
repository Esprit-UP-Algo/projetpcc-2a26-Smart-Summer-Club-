#include "adminmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    adminmainwindow w;
    w.show();
    return a.exec();
}
