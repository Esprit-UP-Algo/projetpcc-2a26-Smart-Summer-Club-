#include "login.h"
#include "ui_login.h"
#include <QPixmap>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/khali/OneDrive/Desktop/projetpcc-2a26-vibraclub-integration/assests/VibraClubLogo.png");
    ui->logo->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));
    
    // Set window properties
    setModal(true);
    setFixedSize(size());
    
    // Connect signals and slots
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::onLoginClicked);
    
    // Enable Enter key to trigger login
    ui->loginButton->setDefault(true);
    
    // Set focus to username field
    ui->usernameLineEdit->setFocus();
    
    // Clear any error message initially
    clearError();
}

Login::~Login()
{
    delete ui;
}

void Login::onLoginClicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    
    // Clear previous error
    clearError();
    
    // Validate input
    if (username.isEmpty()) {
        showError("Please enter a username");
        ui->usernameLineEdit->setFocus();
        return;
    }
    
    if (password.isEmpty()) {
        showError("Please enter a password");
        ui->passwordLineEdit->setFocus();
        return;
    }
    
    // Validate credentials
    if (validateCredentials(username, password)) {
        // Login successful
        accept(); // This closes the dialog with QDialog::Accepted result
    } else {
        // Login failed
        showError("Invalid username or password");
        ui->passwordLineEdit->clear();
        ui->usernameLineEdit->setFocus();
        ui->usernameLineEdit->selectAll();
    }
}

bool Login::validateCredentials(const QString &username, const QString &password)
{
    // Simple hardcoded validation
    return (username == ADMIN_USERNAME && password == ADMIN_PASSWORD);
}

void Login::showError(const QString &message)
{
    ui->errorLabel->setText(message);
    ui->errorLabel->setStyleSheet("color: #e74c3c; font-size: 13px; font-weight: normal; margin-top: 10px;");
}

void Login::clearError()
{
    ui->errorLabel->clear();
}