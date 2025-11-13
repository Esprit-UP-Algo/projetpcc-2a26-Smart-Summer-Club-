#include "login.h"
#include "ui_login.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTimer>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    // Logo is now handled by CSS styling in the UI file
    
    // Set window properties
    setModal(true);
    setFixedSize(size());
    
    // Connect signals and slots
    connect(ui->nextButton, &QPushButton::clicked, this, &Login::onNextClicked);
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::onLoginClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &Login::onBackClicked);
    
    // Enable Enter key to trigger appropriate action
    ui->nextButton->setDefault(true);
    
    // Start with email page and set focus to email field
    ui->loginStackedWidget->setCurrentIndex(0);
    ui->emailLineEdit->setFocus();
    ui->emailLineEdit->setText("adembg91@gmail.com");
    
    // Clear any error message initially
    clearError();
}

Login::~Login()
{
    delete ui;
}

void Login::onNextClicked()
{
    QString email = ui->emailLineEdit->text().trimmed();
    
    // Clear previous error
    ui->emailErrorLabel->clear();
    
    // Validate email input
    if (email.isEmpty()) {
        ui->emailErrorLabel->setText("Please enter your email address");
        ui->emailLineEdit->setFocus();
        return;
    }
    
    // Simple email format validation
    if (!email.contains("@") || !email.contains(".")) {
        ui->emailErrorLabel->setText("Please enter a valid email address");
        ui->emailLineEdit->setFocus();
        return;
    }
    
    // Store email and trigger success animation
    ui->emailLabel->setText(email);
    successAnimationEmail();
}

void Login::onLoginClicked()
{
    QString username = ui->emailLabel->text().trimmed(); // Get email from label
    QString password = ui->passwordLineEdit->text();
    
    // Clear previous error
    ui->passwordErrorLabel->clear();
    
    // Validate input
    if (password.isEmpty()) {
        ui->passwordErrorLabel->setText("Please enter a password");
        ui->passwordLineEdit->setFocus();
        return;
    }
    
    // Validate credentials
    if (validateCredentials(username, password)) {
        // Login successful - trigger success animation
        successAnimationLogin();
    } else {
        // Login failed - trigger shake animation and error styling
        ui->passwordErrorLabel->setText("Invalid username or password");
        shakePasswordField();
        ui->passwordLineEdit->clear();
        ui->passwordLineEdit->setFocus();
    }
}

void Login::onBackClicked()
{
    // Go back to email page
    ui->loginStackedWidget->setCurrentIndex(0);
    ui->emailLineEdit->setFocus();
    ui->nextButton->setDefault(true);
    ui->passwordErrorLabel->clear();
}

bool Login::validateCredentials(const QString &username, const QString &password)
{
    // Simple hardcoded validation
    return (username == ADMIN_USERNAME && password == ADMIN_PASSWORD);
}

void Login::showError(const QString &message)
{
    // Show error on current page
    if (ui->loginStackedWidget->currentIndex() == 0) {
        ui->emailErrorLabel->setText(message);
    } else {
        ui->passwordErrorLabel->setText(message);
    }
}

void Login::clearError()
{
    ui->emailErrorLabel->clear();
    ui->passwordErrorLabel->clear();
}

void Login::shakePasswordField()
{
    // This styling is now handled above with the icon
    
    // Show error icon using QLineEdit action with proper styling
    QAction *errorAction = ui->passwordLineEdit->addAction(QIcon(":/icons/icons/notverified.png"), QLineEdit::TrailingPosition);
    errorAction->setToolTip("Invalid password");
    
    // Style the password field with better icon positioning
    ui->passwordLineEdit->setStyleSheet(
        "QLineEdit {"
        "    padding: 15px 45px 15px 15px;"  // Extra right padding for icon
        "    border: 2px solid #e74c3c;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "    background-color: #ffeaea;"
        "    margin-bottom: 15px;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #c0392b;"
        "    outline: none;"
        "}"
    );
    ui->passwordLineEdit->setPlaceholderText("Invalid password - try again");
    
    // Create shake animation
    QPropertyAnimation *animation = new QPropertyAnimation(ui->passwordLineEdit, "geometry");
    animation->setDuration(500);
    
    // Get current geometry
    QRect originalGeometry = ui->passwordLineEdit->geometry();
    
    // Define shake positions (moving left and right)
    animation->setKeyValueAt(0.0, originalGeometry);
    animation->setKeyValueAt(0.1, QRect(originalGeometry.x() - 10, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(0.2, QRect(originalGeometry.x() + 10, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(0.3, QRect(originalGeometry.x() - 8, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(0.4, QRect(originalGeometry.x() + 8, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(0.5, QRect(originalGeometry.x() - 6, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(0.6, QRect(originalGeometry.x() + 6, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(0.7, QRect(originalGeometry.x() - 4, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(0.8, QRect(originalGeometry.x() + 4, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(0.9, QRect(originalGeometry.x() - 2, originalGeometry.y(), originalGeometry.width(), originalGeometry.height()));
    animation->setKeyValueAt(1.0, originalGeometry);
    
    // Start the animation
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    
    // Reset the field style back to normal after 2 seconds
    QTimer::singleShot(2000, [this]() {
        ui->passwordLineEdit->setStyleSheet(
            "QLineEdit {"
            "    padding: 15px;"
            "    border: 2px solid #e0e4e7;"
            "    border-radius: 8px;"
            "    font-size: 14px;"
            "    background-color: white;"
            "    margin-bottom: 15px;"
            "}"
            "QLineEdit:focus {"
            "    border-color: #4DB6C3;"
            "    outline: none;"
            "}"
        );
        
        // Clear any actions (icons) from password field
        QList<QAction*> actions = ui->passwordLineEdit->actions();
        for(QAction* action : actions) {
            ui->passwordLineEdit->removeAction(action);
        }
        
        ui->passwordLineEdit->setPlaceholderText("🔒 Enter your password");
    });
}

void Login::successAnimationEmail()
{
    // Show success icon using QLineEdit action with proper styling
    QAction *successAction = ui->emailLineEdit->addAction(QIcon(":/icons/icons/verified.png"), QLineEdit::TrailingPosition);
    successAction->setToolTip("Email verified");
    
    // Change email field style to green/success state with better icon positioning
    ui->emailLineEdit->setStyleSheet(
        "QLineEdit {"
        "    padding: 15px 45px 15px 15px;"  // Extra right padding for icon
        "    border: 2px solid #27ae60;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "    background-color: #eafaf1;"
        "    margin-bottom: 15px;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #229954;"
        "    outline: none;"
        "}"
    );
    ui->emailLineEdit->setPlaceholderText("Email verified!");
    
    // Create success animation (gentle pulse and scale)
    QPropertyAnimation *scaleAnimation = new QPropertyAnimation(ui->emailLineEdit, "geometry");
    scaleAnimation->setDuration(300);
    
    // Get current geometry
    QRect originalGeometry = ui->emailLineEdit->geometry();
    QRect scaledGeometry = QRect(
        originalGeometry.x() - 5, 
        originalGeometry.y() - 2, 
        originalGeometry.width() + 10, 
        originalGeometry.height() + 4
    );
    
    // Scale up then back to normal
    scaleAnimation->setKeyValueAt(0.0, originalGeometry);
    scaleAnimation->setKeyValueAt(0.5, scaledGeometry);
    scaleAnimation->setKeyValueAt(1.0, originalGeometry);
    
    scaleAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    
    // Move to password page after animation
    QTimer::singleShot(400, [this]() {
        ui->loginStackedWidget->setCurrentIndex(1);
        ui->passwordLineEdit->setFocus();
        ui->loginButton->setDefault(true);
        
        // Reset email field style after moving to next page
        // Clear any actions (icons) from email field
        QList<QAction*> actions = ui->emailLineEdit->actions();
        for(QAction* action : actions) {
            ui->emailLineEdit->removeAction(action);
        }
        
        ui->emailLineEdit->setStyleSheet(
            "QLineEdit {"
            "    padding: 15px;"
            "    border: 2px solid #e0e4e7;"
            "    border-radius: 8px;"
            "    font-size: 14px;"
            "    background-color: white;"
            "    margin-bottom: 15px;"
            "}"
            "QLineEdit:focus {"
            "    border-color: #4DB6C3;"
            "    outline: none;"
            "}"
        );
        ui->emailLineEdit->setPlaceholderText("📧 Enter your email address");
    });
}

void Login::successAnimationLogin()
{
    // Show success icon using QLineEdit action with proper styling
    QAction *successAction = ui->passwordLineEdit->addAction(QIcon(":/icons/icons/verified.png"), QLineEdit::TrailingPosition);
    successAction->setToolTip("Login successful");
    
    // Change password field style to green/success state with better icon positioning
    ui->passwordLineEdit->setStyleSheet(
        "QLineEdit {"
        "    padding: 15px 45px 15px 15px;"  // Extra right padding for icon
        "    border: 2px solid #27ae60;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "    background-color: #eafaf1;"
        "    margin-bottom: 15px;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #229954;"
        "    outline: none;"
        "}"
    );
    ui->passwordLineEdit->setPlaceholderText("Login successful!");
    
    // Create success animation (gentle pulse and scale)
    QPropertyAnimation *scaleAnimation = new QPropertyAnimation(ui->passwordLineEdit, "geometry");
    scaleAnimation->setDuration(300);
    
    // Get current geometry
    QRect originalGeometry = ui->passwordLineEdit->geometry();
    QRect scaledGeometry = QRect(
        originalGeometry.x() - 5, 
        originalGeometry.y() - 2, 
        originalGeometry.width() + 10, 
        originalGeometry.height() + 4
    );
    
    // Scale up then back to normal
    scaleAnimation->setKeyValueAt(0.0, originalGeometry);
    scaleAnimation->setKeyValueAt(0.5, scaledGeometry);
    scaleAnimation->setKeyValueAt(1.0, originalGeometry);
    
    scaleAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    
    // Complete login after animation
    QTimer::singleShot(400, [this]() {
        accept(); // This closes the dialog with QDialog::Accepted result
    });
}

