#include "totpinputdialog.h"
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QTimer>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

// DigitLineEdit Implementation
DigitLineEdit::DigitLineEdit(QWidget *parent) : QLineEdit(parent)
{
    setMaxLength(1);
    setAlignment(Qt::AlignCenter);
    setFixedSize(45, 50);
    
    // Modern styling
    setStyleSheet(
        "DigitLineEdit {"
        "    border: 2px solid #e1e5e9;"
        "    border-radius: 8px;"
        "    background-color: #ffffff;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    padding: 0px;"
        "}"
        "DigitLineEdit:focus {"
        "    border-color: #3498db;"
        "    background-color: #f8fbff;"
        "    outline: none;"
        "}"
        "DigitLineEdit:hover {"
        "    border-color: #bdc3c7;"
        "}"
    );
    
    // Add subtle shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(8);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 2);
    setGraphicsEffect(shadow);
    
    // Only allow digits
    QRegularExpression rx("[0-9]");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);
    setValidator(validator);
}

void DigitLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace) {
        if (text().isEmpty()) {
            emit backspacePressed();
        } else {
            clear();
        }
        return;
    }
    
    QLineEdit::keyPressEvent(event);
    
    if (!text().isEmpty()) {
        emit digitEntered();
    }
}

void DigitLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    selectAll();
}

// TOTPInputDialog Implementation
TOTPInputDialog::TOTPInputDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();
    setFixedSize(360, 280);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    
    // Set window modality
    setModal(true);
}

void TOTPInputDialog::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    m_mainLayout->setSpacing(20);
    
    // Create main container with rounded corners and shadow
    QWidget *container = new QWidget();
    container->setStyleSheet(
        "QWidget {"
        "    background-color: #ffffff;"
        "    border-radius: 16px;"
        "    border: 1px solid #e1e5e9;"
        "}"
    );
    
    // Add shadow to container
    QGraphicsDropShadowEffect *containerShadow = new QGraphicsDropShadowEffect();
    containerShadow->setBlurRadius(20);
    containerShadow->setColor(QColor(0, 0, 0, 25));
    containerShadow->setOffset(0, 4);
    container->setGraphicsEffect(containerShadow);
    
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);
    containerLayout->setSpacing(20);
    
    // Lock icon (Unicode)
    QLabel *iconLabel = new QLabel("🔒");
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 32px;"
        "    color: #3498db;"
        "    background-color: #f0f8ff;"
        "    border-radius: 30px;"
        "    min-width: 60px;"
        "    min-height: 60px;"
        "    max-width: 60px;"
        "    max-height: 60px;"
        "}"
    );
    iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    iconLabel->setAlignment(Qt::AlignCenter);
    
    // Center the icon
    QHBoxLayout *iconLayout = new QHBoxLayout();
    iconLayout->addStretch();
    iconLayout->addWidget(iconLabel);
    iconLayout->addStretch();
    
    // Title
    m_titleLabel = new QLabel("Authentication Required");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    margin: 0px;"
        "}"
    );
    
    // Message
    m_messageLabel = new QLabel("Enter your 6-digit authentication code");
    m_messageLabel->setAlignment(Qt::AlignCenter);
    m_messageLabel->setWordWrap(true);
    m_messageLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 14px;"
        "    color: #7f8c8d;"
        "    margin: 0px;"
        "}"
    );
    
    // Digit input layout
    m_digitLayout = new QHBoxLayout();
    m_digitLayout->setSpacing(12);
    m_digitLayout->setContentsMargins(0, 10, 0, 10);
    
    // Create 6 digit input fields
    for (int i = 0; i < DIGIT_COUNT; ++i) {
        DigitLineEdit *digitEdit = new DigitLineEdit();
        connect(digitEdit, &DigitLineEdit::digitEntered, this, &TOTPInputDialog::onDigitEntered);
        connect(digitEdit, &DigitLineEdit::backspacePressed, this, &TOTPInputDialog::onBackspacePressed);
        connect(digitEdit, &QLineEdit::textChanged, this, &TOTPInputDialog::checkCodeComplete);
        
        m_digitEdits.append(digitEdit);
        m_digitLayout->addWidget(digitEdit);
    }
    
    // Center the digit layout
    QHBoxLayout *centeredDigitLayout = new QHBoxLayout();
    centeredDigitLayout->addStretch();
    centeredDigitLayout->addLayout(m_digitLayout);
    centeredDigitLayout->addStretch();
    
    // Error label
    m_errorLabel = new QLabel();
    m_errorLabel->setAlignment(Qt::AlignCenter);
    m_errorLabel->setWordWrap(true);
    m_errorLabel->setStyleSheet(
        "QLabel {"
        "    color: #e74c3c;"
        "    font-size: 12px;"
        "    background-color: #fdf2f2;"
        "    border: 1px solid #fecaca;"
        "    border-radius: 6px;"
        "    padding: 8px;"
        "    margin: 0px;"
        "}"
    );
    m_errorLabel->hide();
    
    // Add all elements to container
    containerLayout->addLayout(iconLayout);
    containerLayout->addWidget(m_titleLabel);
    containerLayout->addWidget(m_messageLabel);
    containerLayout->addLayout(centeredDigitLayout);
    containerLayout->addWidget(m_errorLabel);
    containerLayout->addStretch();
    
    m_mainLayout->addWidget(container);
    
    // Focus first digit
    if (!m_digitEdits.isEmpty()) {
        m_digitEdits.first()->setFocus();
    }
}

QString TOTPInputDialog::getCode() const
{
    QString code;
    for (const DigitLineEdit *edit : m_digitEdits) {
        code += edit->text();
    }
    return code;
}

void TOTPInputDialog::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
}

void TOTPInputDialog::setMessage(const QString &message)
{
    m_messageLabel->setText(message);
}

void TOTPInputDialog::showError(const QString &error)
{
    m_errorLabel->setText(error);
    m_errorLabel->show();
    
    // Shake animation for error
    for (DigitLineEdit *edit : m_digitEdits) {
        edit->setStyleSheet(
            "DigitLineEdit {"
            "    border: 2px solid #e74c3c;"
            "    border-radius: 8px;"
            "    background-color: #fdf2f2;"
            "    font-size: 18px;"
            "    font-weight: bold;"
            "    color: #2c3e50;"
            "    padding: 0px;"
            "}"
        );
    }
    
    // Reset style after 2 seconds
    QTimer::singleShot(2000, this, &TOTPInputDialog::clearError);
}

void TOTPInputDialog::clearError()
{
    m_errorLabel->hide();
    
    // Reset digit styles
    for (DigitLineEdit *edit : m_digitEdits) {
        edit->setStyleSheet(
            "DigitLineEdit {"
            "    border: 2px solid #e1e5e9;"
            "    border-radius: 8px;"
            "    background-color: #ffffff;"
            "    font-size: 18px;"
            "    font-weight: bold;"
            "    color: #2c3e50;"
            "    padding: 0px;"
            "}"
            "DigitLineEdit:focus {"
            "    border-color: #3498db;"
            "    background-color: #f8fbff;"
            "    outline: none;"
            "}"
            "DigitLineEdit:hover {"
            "    border-color: #bdc3c7;"
            "}"
        );
    }
}

void TOTPInputDialog::onDigitEntered()
{
    focusNextDigit();
    checkCodeComplete();
}

void TOTPInputDialog::onBackspacePressed()
{
    focusPreviousDigit();
}

void TOTPInputDialog::checkCodeComplete()
{
    QString code = getCode();
    if (code.length() == DIGIT_COUNT) {
        // Auto-submit when all 6 digits are entered
        QTimer::singleShot(200, this, &QDialog::accept);
    }
}

void TOTPInputDialog::focusNextDigit()
{
    for (int i = 0; i < m_digitEdits.size() - 1; ++i) {
        if (m_digitEdits[i]->hasFocus() && !m_digitEdits[i]->text().isEmpty()) {
            m_digitEdits[i + 1]->setFocus();
            return;
        }
    }
}

void TOTPInputDialog::focusPreviousDigit()
{
    for (int i = 1; i < m_digitEdits.size(); ++i) {
        if (m_digitEdits[i]->hasFocus()) {
            m_digitEdits[i - 1]->setFocus();
            return;
        }
    }
}

void TOTPInputDialog::clearAllDigits()
{
    for (DigitLineEdit *edit : m_digitEdits) {
        edit->clear();
    }
    if (!m_digitEdits.isEmpty()) {
        m_digitEdits.first()->setFocus();
    }
}