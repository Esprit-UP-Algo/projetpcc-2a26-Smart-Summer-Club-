#include "membersmainwindow.h"
#include "ui_membersmainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>

membersMainWindow::membersMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::membersMainWindow)
    , currentEditingRow(-1)
{
    ui->setupUi(this);

    // Appliquer les styles (garder votre code existant)
    QString tabStyle =
        "QTabWidget::pane {"
        "    border: 3px solid #16A6B3;"
        "    border-radius: 15px;"
        "    background-color: #FFFFFF;"
        "    margin-top: 10px;"
        "    padding: 10px;"
        "}"
        ""
        "QTabWidget::tab-bar {"
        "    alignment: center;"
        "    left: 20px;"
        "}"
        ""
        "QTabBar::tab {"
        "    background-color: #E8F4F8;"
        "    border: 2px solid #16A6B3;"
        "    border-bottom: 2px solid #16A6B3;"
        "    border-top-left-radius: 12px;"
        "    border-top-right-radius: 12px;"
        "    border-bottom-left-radius: 0px;"
        "    border-bottom-right-radius: 0px;"
        "    width: 180px;"
        "    padding: 12px 20px;"
        "    margin-right: 5px;"
        "    font-weight: bold;"
        "    font-size: 12px;"
        "    color: #16A6B3;"
        "    height: 45px;"
        "}"
        ""
        "QTabBar::tab:selected {"
        "    background-color: #16A6B3;"
        "    color: white;"
        "    border-color: #118C8C;"
        "    border-bottom: 2px solid #16A6B3;"
        "}"
        ""
        "QTabBar::tab:hover:!selected {"
        "    background-color: #B1CEC2;"
        "    color: #333333;"
        "    border-color: #118C8C;"
        "}"
        ""
        "QTabBar::tab:pressed {"
        "    background-color: #0D6E6E;"
        "    color: white;"
        "}";

    ui->tabWidget->setStyleSheet(tabStyle);

    QString sidebarStyle =
        "QFrame#sidebar {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop:0 #ffffff, stop:1 #118C8C);"
        "    border-radius: 26px;"
        "}"
        ""
        "QPushButton {"
        "    background-color: rgba(255, 255, 255, 0.2);"
        "    border: 2px solid rgba(255, 255, 255, 0.3);"
        "    border-radius: 25px;"
        "    color: white;"
        "    font: 700 11pt \"Segoe UI\";"
        "    padding: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: rgba(255, 255, 255, 0.3);"
        "    border: 2px solid rgba(255, 255, 255, 0.5);"
        "}"
        ""
        "QPushButton:pressed {"
        "    background-color: rgba(255, 255, 255, 0.4);"
        "}";

    ui->sidebar->setStyleSheet(sidebarStyle);

    // Configuration initiale du tableau
    setupMembersTable();

    // Connexions des signaux
    connect(ui->pushButton_add, &QPushButton::clicked, this, &membersMainWindow::onAddMemberClicked);
    connect(ui->pushButton_upload, &QPushButton::clicked, this, &membersMainWindow::onUploadImageClicked);
    connect(ui->pushButton_update, &QPushButton::clicked, this, &membersMainWindow::onUpdateMemberClicked);
    connect(ui->pushButton_exportPdf, &QPushButton::clicked, this, &membersMainWindow::onExportToPDFClicked);
    connect(ui->pushButton_exportExcel, &QPushButton::clicked, this, &membersMainWindow::onExportToExcelClicked);
    connect(ui->lineEdit_search, &QLineEdit::textChanged, this, &membersMainWindow::onSearchTextChanged);
    connect(ui->comboBox_sort, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &membersMainWindow::onSortComboBoxChanged);
    connect(ui->comboBox_filter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &membersMainWindow::onFilterComboBoxChanged);
}

void membersMainWindow::setupMembersTable()
{
    ui->tableWidget_members->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_members->verticalHeader()->setVisible(false);
    ui->tableWidget_members->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_members->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // S'assurer que la colonne Actions est visible et configurée
    ui->tableWidget_members->setColumnWidth(8, 150); // Largeur pour les boutons
}

void membersMainWindow::onAddMemberClicked()
{
    QString cin = ui->lineEdit_cin->text();
    QString firstName = ui->lineEdit_firstName->text();
    QString lastName = ui->lineEdit_lastName->text();
    QString age = QString::number(ui->spinBox_age->value());
    QString gender = ui->comboBox_gender->currentText();
    QString email = ui->lineEdit_email->text();
    QString phone = ui->lineEdit_phone->text();
    QString subscription = ui->comboBox_subscription->currentText();

    if (cin.isEmpty() || firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all required fields!");
        return;
    }

    // Vérifier si le CIN existe déjà
    for (int i = 0; i < ui->tableWidget_members->rowCount(); ++i) {
        if (ui->tableWidget_members->item(i, 0)->text() == cin) {
            QMessageBox::warning(this, "Error", "Member with this CIN already exists!");
            return;
        }
    }

    // Ajouter le membre à la table
    int row = ui->tableWidget_members->rowCount();
    ui->tableWidget_members->insertRow(row);

    // Ajouter les données dans les colonnes (selon le fichier UI)
    ui->tableWidget_members->setItem(row, 0, new QTableWidgetItem(cin));
    ui->tableWidget_members->setItem(row, 1, new QTableWidgetItem(firstName));
    ui->tableWidget_members->setItem(row, 2, new QTableWidgetItem(lastName));
    ui->tableWidget_members->setItem(row, 3, new QTableWidgetItem(age));
    ui->tableWidget_members->setItem(row, 4, new QTableWidgetItem(gender));
    ui->tableWidget_members->setItem(row, 5, new QTableWidgetItem(email));
    ui->tableWidget_members->setItem(row, 6, new QTableWidgetItem(phone));
    ui->tableWidget_members->setItem(row, 7, new QTableWidgetItem(subscription));

    // Ajouter les boutons d'actions dans la colonne 8 (Actions)
    addActionButtons(row);

    // Réinitialiser le formulaire
    resetForm();

    QMessageBox::information(this, "Success", "Member added successfully!");
}

void membersMainWindow::addActionButtons(int row)
{
    QWidget *actionsWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
    layout->setContentsMargins(5, 2, 5, 2);
    layout->setSpacing(5);

    QPushButton *editButton = new QPushButton("Edit");
    QPushButton *deleteButton = new QPushButton("Delete");

    // Style des boutons
    editButton->setStyleSheet("QPushButton { "
                              "background-color: #16A6B3; "
                              "color: white; "
                              "border: none; "
                              "border-radius: 5px; "
                              "padding: 6px 12px; "
                              "font-size: 11px; "
                              "min-width: 50px; "
                              "}"
                              "QPushButton:hover { "
                              "background-color: #118C8C; "
                              "}");

    deleteButton->setStyleSheet("QPushButton { "
                                "background-color: #E74C3C; "
                                "color: white; "
                                "border: none; "
                                "border-radius: 5px; "
                                "padding: 6px 12px; "
                                "font-size: 11px; "
                                "min-width: 50px; "
                                "}"
                                "QPushButton:hover { "
                                "background-color: #C0392B; "
                                "}");

    // Stocker le numéro de ligne dans les propriétés des boutons
    editButton->setProperty("row", row);
    deleteButton->setProperty("row", row);

    connect(editButton, &QPushButton::clicked, this, &membersMainWindow::onEditMemberClicked);
    connect(deleteButton, &QPushButton::clicked, this, &membersMainWindow::onDeleteMemberClicked);

    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    layout->setAlignment(Qt::AlignCenter);

    actionsWidget->setLayout(layout);

    // IMPORTANT: Utiliser la colonne 8 pour les Actions (selon le fichier UI)
    ui->tableWidget_members->setCellWidget(row, 8, actionsWidget);
}

void membersMainWindow::onEditMemberClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int row = button->property("row").toInt();
    if (row < 0 || row >= ui->tableWidget_members->rowCount()) return;

    // Remplir le formulaire avec les données du membre
    ui->lineEdit_cin->setText(ui->tableWidget_members->item(row, 0)->text());
    ui->lineEdit_firstName->setText(ui->tableWidget_members->item(row, 1)->text());
    ui->lineEdit_lastName->setText(ui->tableWidget_members->item(row, 2)->text());
    ui->spinBox_age->setValue(ui->tableWidget_members->item(row, 3)->text().toInt());

    // Définir le genre
    QString gender = ui->tableWidget_members->item(row, 4)->text();
    int genderIndex = ui->comboBox_gender->findText(gender);
    if (genderIndex >= 0) {
        ui->comboBox_gender->setCurrentIndex(genderIndex);
    }

    ui->lineEdit_email->setText(ui->tableWidget_members->item(row, 5)->text());
    ui->lineEdit_phone->setText(ui->tableWidget_members->item(row, 6)->text());

    // Définir le type d'abonnement
    QString subscription = ui->tableWidget_members->item(row, 7)->text();
    int subscriptionIndex = ui->comboBox_subscription->findText(subscription);
    if (subscriptionIndex >= 0) {
        ui->comboBox_subscription->setCurrentIndex(subscriptionIndex);
    }

    // Stocker la ligne en cours de modification
    currentEditingRow = row;

    // Aller à l'onglet Add Members
    ui->tabWidget->setCurrentIndex(1);

    // Changer le texte du bouton pour indiquer qu'on est en mode édition
    ui->pushButton_add->setEnabled(false);
    ui->pushButton_update->setEnabled(true);
}

void membersMainWindow::onDeleteMemberClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int row = button->property("row").toInt();
    if (row < 0 || row >= ui->tableWidget_members->rowCount()) return;

    // Récupérer le nom du membre pour le message de confirmation
    QString memberName = ui->tableWidget_members->item(row, 1)->text() + " " +
                         ui->tableWidget_members->item(row, 2)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  "Are you sure you want to delete member:\n" + memberName + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        ui->tableWidget_members->removeRow(row);

        // Mettre à jour les propriétés "row" des boutons pour les lignes restantes
        updateActionButtonsRows(row);

        QMessageBox::information(this, "Success", "Member deleted successfully!");
    }
}

void membersMainWindow::updateActionButtonsRows(int deletedRow)
{
    // Mettre à jour les numéros de ligne pour tous les boutons après la ligne supprimée
    for (int i = deletedRow; i < ui->tableWidget_members->rowCount(); ++i) {
        QWidget *widget = ui->tableWidget_members->cellWidget(i, 8); // Colonne Actions
        if (widget) {
            QList<QPushButton*> buttons = widget->findChildren<QPushButton*>();
            for (QPushButton *button : buttons) {
                button->setProperty("row", i);
            }
        }
    }
}

void membersMainWindow::onUpdateMemberClicked()
{
    if (currentEditingRow == -1) {
        QMessageBox::warning(this, "Error", "No member selected for update!");
        return;
    }

    QString cin = ui->lineEdit_cin->text();
    QString firstName = ui->lineEdit_firstName->text();
    QString lastName = ui->lineEdit_lastName->text();
    QString age = QString::number(ui->spinBox_age->value());
    QString gender = ui->comboBox_gender->currentText();
    QString email = ui->lineEdit_email->text();
    QString phone = ui->lineEdit_phone->text();
    QString subscription = ui->comboBox_subscription->currentText();

    if (cin.isEmpty() || firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all required fields!");
        return;
    }

    // Mettre à jour les données dans la table
    ui->tableWidget_members->item(currentEditingRow, 0)->setText(cin);
    ui->tableWidget_members->item(currentEditingRow, 1)->setText(firstName);
    ui->tableWidget_members->item(currentEditingRow, 2)->setText(lastName);
    ui->tableWidget_members->item(currentEditingRow, 3)->setText(age);
    ui->tableWidget_members->item(currentEditingRow, 4)->setText(gender);
    ui->tableWidget_members->item(currentEditingRow, 5)->setText(email);
    ui->tableWidget_members->item(currentEditingRow, 6)->setText(phone);
    ui->tableWidget_members->item(currentEditingRow, 7)->setText(subscription);

    // Réinitialiser
    resetForm();
    currentEditingRow = -1;

    // Réactiver le bouton Add et désactiver Update
    ui->pushButton_add->setEnabled(true);
    ui->pushButton_update->setEnabled(false);

    QMessageBox::information(this, "Success", "Member updated successfully!");
}

void membersMainWindow::resetForm()
{
    ui->lineEdit_cin->clear();
    ui->lineEdit_firstName->clear();
    ui->lineEdit_lastName->clear();
    ui->spinBox_age->setValue(18);
    ui->lineEdit_email->clear();
    ui->lineEdit_phone->clear();
    ui->comboBox_subscription->setCurrentIndex(0);
    ui->comboBox_gender->setCurrentIndex(0);
    ui->label_imagePreview->setText("No Image");
    ui->label_imagePreview->setPixmap(QPixmap());
}

// Les autres fonctions restent inchangées...
void membersMainWindow::onUploadImageClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Profile Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);
        if (!pixmap.isNull()) {
            pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_imagePreview->setPixmap(pixmap);
            ui->label_imagePreview->setText("");
        }
    }
}

void membersMainWindow::onSearchTextChanged(const QString &text)
{
    for (int i = 0; i < ui->tableWidget_members->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < ui->tableWidget_members->columnCount() - 1; ++j) {
            QTableWidgetItem *item = ui->tableWidget_members->item(i, j);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget_members->setRowHidden(i, !match && !text.isEmpty());
    }
}

void membersMainWindow::onSortComboBoxChanged(int index)
{
    switch (index) {
    case 0: ui->tableWidget_members->sortItems(0); break; // CIN
    case 1: ui->tableWidget_members->sortItems(3, Qt::DescendingOrder); break; // Age
    case 2: ui->tableWidget_members->sortItems(1); break; // Name
    }
}

void membersMainWindow::onFilterComboBoxChanged(int index)
{
    QString filterText = "";
    switch (index) {
    case 1: filterText = "Mensuel"; break;
    case 2: filterText = "Trimestriel"; break;
    case 3: filterText = "Annuel"; break;
    }

    for (int i = 0; i < ui->tableWidget_members->rowCount(); ++i) {
        QTableWidgetItem *item = ui->tableWidget_members->item(i, 7); // Subscription column
        if (item) {
            bool match = (index == 0) || (item->text() == filterText);
            ui->tableWidget_members->setRowHidden(i, !match);
        }
    }
}

void membersMainWindow::onExportToPDFClicked()
{
    QMessageBox::information(this, "Export PDF", "PDF export functionality will be implemented!");
}

void membersMainWindow::onExportToExcelClicked()
{
    QMessageBox::information(this, "Export Excel", "Excel export functionality will be implemented!");
}

membersMainWindow::~membersMainWindow()
{
    delete ui;
}
