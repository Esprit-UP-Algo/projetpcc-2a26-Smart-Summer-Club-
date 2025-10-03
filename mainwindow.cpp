#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QCalendarWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimeEdit>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QTime>
#include <QTableWidget>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix_logo(":/logo.png");
    if(!pix_logo.isNull()) {
        ui->label_logo->setPixmap(pix_logo.scaled(200,150,Qt::KeepAspectRatio));
        qDebug() << "Logo chargé avec succès!";
    } else {
        qDebug() << "Erreur: Impossible de charger le logo";
    }

    // Connexion du bouton calendrier (date)
    connect(ui->pushButton_calendar, &QPushButton::clicked, this, &MainWindow::onCalendarButtonClicked);

    // Connexion du bouton heure
    connect(ui->pushButton_time, &QPushButton::clicked, this, &MainWindow::onTimeButtonClicked);

    // Initialiser le tableau avec les boutons
    initializeTableWithButtons();
}

void MainWindow::initializeTableWithButtons()
{
    // Définir les en-têtes des colonnes - Actions en premier
    QStringList headers;
    headers << "Actions" << "CIN" << "Activité" << "Âge" << "Date" << "Heure"
            << "Disponibilité" << "Prix" << "Animateur";
    ui->tableWidget_members->setHorizontalHeaderLabels(headers);

    ui->tableWidget_members->setColumnWidth(0, 220);
    ui->tableWidget_members->setColumnWidth(1, 80);
    ui->tableWidget_members->setColumnWidth(2, 150);
    ui->tableWidget_members->setColumnWidth(3, 50);
    ui->tableWidget_members->setColumnWidth(4, 100);
    ui->tableWidget_members->setColumnWidth(5, 80);
    ui->tableWidget_members->setColumnWidth(6, 100);
    ui->tableWidget_members->setColumnWidth(7, 80);
    ui->tableWidget_members->setColumnWidth(8, 150);

    // Ajouter quelques lignes de test avec boutons
    addTableRow("123456", "Yoga", "25", "15/12/2024", "10:00", "Oui", "50€", "Jean Dupont");
    addTableRow("789012", "Pilates", "30", "16/12/2024", "14:00", "Non", "60€", "Marie Martin");
    addTableRow("345678", "Natation", "22", "17/12/2024", "16:00", "Oui", "40€", "Pierre Lambert");
}

void MainWindow::addTableRow(const QString &cin, const QString &activity,
                             const QString &age, const QString &date,
                             const QString &time, const QString &disponibility,
                             const QString &price, const QString &facilitator)
{
    int row = ui->tableWidget_members->rowCount();
    ui->tableWidget_members->insertRow(row);

    // COLONNE 0: Actions (boutons)
    // Créer un widget pour contenir les boutons
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(5, 2, 5, 2);
    layout->setSpacing(5);

    QPushButton *btnEdit = new QPushButton("✏️");
    btnEdit->setStyleSheet("QPushButton { background-color: #16A6B3; color: white; border: none; border-radius: 5px; padding: 5px; font-size: 12px; } QPushButton:hover { background-color: #118C8C; }");
    btnEdit->setFixedSize(30, 35);
    btnEdit->setProperty("row", row);

    QPushButton *btnDelete = new QPushButton("🗑️");
    btnDelete->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; border-radius: 5px; padding: 5px; font-size: 12px; } QPushButton:hover { background-color: #c0392b; }");
    btnDelete->setFixedSize(30, 35);
    btnDelete->setProperty("row", row);

    layout->addWidget(btnEdit);
    layout->addWidget(btnDelete);
    layout->addStretch();

    widget->setLayout(layout);

    // Ajouter le widget dans la première colonne (Actions)
    ui->tableWidget_members->setCellWidget(row, 0, widget);

    ui->tableWidget_members->setItem(row, 2, new QTableWidgetItem(activity));

    ui->tableWidget_members->setItem(row, 3, new QTableWidgetItem(age));

    ui->tableWidget_members->setItem(row, 4, new QTableWidgetItem(date));

    ui->tableWidget_members->setItem(row, 5, new QTableWidgetItem(time));

    ui->tableWidget_members->setItem(row, 6, new QTableWidgetItem(disponibility));

    ui->tableWidget_members->setItem(row, 7, new QTableWidgetItem(price));

    ui->tableWidget_members->setItem(row, 8, new QTableWidgetItem(facilitator));

    // Connecter les boutons
    connect(btnEdit, &QPushButton::clicked, this, &MainWindow::onEditButtonClicked);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
}

void MainWindow::onEditButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int row = button->property("row").toInt();
        qDebug() << "Modifier la ligne:" << row;

        // Récupérer les données de la ligne sélectionnée
        // Note: Les indices commencent à 1 maintenant car la colonne 0 est Actions
        QString cin = ui->tableWidget_members->item(row, 1)->text();
        QString activity = ui->tableWidget_members->item(row, 2)->text();
        QString age = ui->tableWidget_members->item(row, 3)->text();
        QString date = ui->tableWidget_members->item(row, 4)->text();
        QString time = ui->tableWidget_members->item(row, 5)->text();
        QString disponibility = ui->tableWidget_members->item(row, 6)->text();
        QString price = ui->tableWidget_members->item(row, 7)->text();
        QString facilitator = ui->tableWidget_members->item(row, 8)->text();

        qDebug() << "Données à modifier - CIN:" << cin << "Activité:" << activity;

        // Ici vous pouvez implémenter la logique pour remplir le formulaire de modification
        ui->tabWidget->setCurrentIndex(1); // Aller à l'onglet d'ajout

        // Pré-remplir les champs
        ui->lineEdit_cin->setText(cin);
        ui->lineEdit_firstName->setText(activity);
        ui->spinBox_age->setValue(age.toInt());
        // Continuer pour les autres champs...
    }
}

void MainWindow::onDeleteButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int row = button->property("row").toInt();
        qDebug() << "Supprimer la ligne:" << row;

        // Récupérer le CIN pour identification
        QString cin = ui->tableWidget_members->item(row, 1)->text();
        QString activity = ui->tableWidget_members->item(row, 2)->text();

        qDebug() << "Suppression de l'activité:" << activity << "pour CIN:" << cin;

        // Ici vous pouvez implémenter la logique de suppression
        // ui->tableWidget_members->removeRow(row); // Décommentez pour supprimer la ligne
    }
}

void MainWindow::onCalendarButtonClicked()
{
    // Créer un dialogue pour afficher le calendrier
    QDialog *calendarDialog = new QDialog(this);
    calendarDialog->setWindowTitle("Sélectionner une date");
    calendarDialog->setFixedSize(400, 400);

    // Créer un widget calendrier
    QCalendarWidget *calendarWidget = new QCalendarWidget(calendarDialog);
    calendarWidget->setGridVisible(true);

    // Créer un layout pour le dialogue
    QVBoxLayout *layout = new QVBoxLayout(calendarDialog);
    layout->addWidget(calendarWidget);

    // Créer un bouton pour confirmer la sélection
    QPushButton *confirmButton = new QPushButton("Confirmer", calendarDialog);
    layout->addWidget(confirmButton);

    // Connecter le bouton de confirmation
    connect(confirmButton, &QPushButton::clicked, calendarDialog, &QDialog::accept);

    // Afficher le dialogue et attendre la sélection
    if (calendarDialog->exec() == QDialog::Accepted) {
        QDate selectedDate = calendarWidget->selectedDate();

        // Formater la date en français
        QString formattedDate = selectedDate.toString("dd/MM/yyyy");

        // Mettre à jour le champ de texte avec la date sélectionnée
        ui->lineEdit_email->setText(formattedDate);

        qDebug() << "Date sélectionnée:" << formattedDate;
    }

    delete calendarDialog;
}

void MainWindow::onTimeButtonClicked()
{
    // Créer un dialogue pour afficher le sélecteur d'heure
    QDialog *timeDialog = new QDialog(this);
    timeDialog->setWindowTitle("Sélectionner une heure");
    timeDialog->setFixedSize(300, 200);

    // Créer un widget de sélection d'heure
    QTimeEdit *timeEdit = new QTimeEdit(timeDialog);
    timeEdit->setDisplayFormat("HH:mm");
    timeEdit->setTime(QTime::currentTime()); // Heure actuelle par défaut

    // Créer un layout pour le dialogue
    QVBoxLayout *layout = new QVBoxLayout(timeDialog);
    layout->addWidget(timeEdit);

    // Créer un bouton pour confirmer la sélection
    QPushButton *confirmButton = new QPushButton("Confirmer", timeDialog);
    layout->addWidget(confirmButton);

    // Connecter le bouton de confirmation
    connect(confirmButton, &QPushButton::clicked, timeDialog, &QDialog::accept);

    // Afficher le dialogue et attendre la sélection
    if (timeDialog->exec() == QDialog::Accepted) {
        QTime selectedTime = timeEdit->time();
        QString formattedTime = selectedTime.toString("HH:mm");
        ui->pushButton_time->setText("🕒 " + formattedTime);

        qDebug() << "Heure sélectionnée:" << formattedTime;
    }

    delete timeDialog;
}

MainWindow::~MainWindow()
{
    delete ui;
}
