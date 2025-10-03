#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCalendarButtonClicked();  // Pour la date
    void onTimeButtonClicked();      // Pour l'heure - AJOUTEZ CETTE LIGNE
    void onEditButtonClicked();    // AJOUT
    void onDeleteButtonClicked();  // AJOUT

private:
    Ui::MainWindow *ui;
    void initializeTableWithButtons();  // AJOUT
    void addTableRow(const QString &cin, const QString &activity,
                     const QString &age, const QString &date,
                     const QString &time, const QString &disponibility,
                     const QString &price, const QString &facilitator);
};

#endif // MAINWINDOW_H
