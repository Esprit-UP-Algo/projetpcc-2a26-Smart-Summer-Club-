#include <QApplication>
#include "finance_dashboard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FinanceDashboard dashboard;
    dashboard.show();

    return app.exec();
}
