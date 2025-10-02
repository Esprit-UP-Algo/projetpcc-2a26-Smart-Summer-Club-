#ifndef MEMBERSMAINWINDOW_H
#define MEMBERSMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class membersMainWindow;
}
QT_END_NAMESPACE

class membersMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    membersMainWindow(QWidget *parent = nullptr);
    ~membersMainWindow();

private slots:
    void onAddMemberClicked();
    void onUploadImageClicked();
    void onUpdateMemberClicked();
    void onSearchTextChanged(const QString &text);
    void onSortComboBoxChanged(int index);
    void onFilterComboBoxChanged(int index);
    void onExportToPDFClicked();
    void onExportToExcelClicked();
    void onDeleteMemberClicked();
    void onEditMemberClicked();

private:
    Ui::membersMainWindow *ui;
    int currentEditingRow;

    void setupMembersTable();
    void addActionButtons(int row);
    void updateActionButtonsRows(int deletedRow);
    void resetForm();
};

#endif // MEMBERSMAINWINDOW_H
