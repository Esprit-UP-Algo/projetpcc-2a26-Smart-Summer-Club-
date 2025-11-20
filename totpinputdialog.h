#ifndef TOTPINPUTDIALOG_H
#define TOTPINPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <QKeyEvent>

class DigitLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit DigitLineEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;

signals:
    void digitEntered();
    void backspacePressed();
};

class TOTPInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TOTPInputDialog(QWidget *parent = nullptr);
    QString getCode() const;
    void setTitle(const QString &title);
    void setMessage(const QString &message);
    void showError(const QString &error);
    void clearError();

private slots:
    void onDigitEntered();
    void onBackspacePressed();
    void checkCodeComplete();

private:
    void setupUI();
    void focusNextDigit();
    void focusPreviousDigit();
    void clearAllDigits();
    
    QVBoxLayout *m_mainLayout;
    QLabel *m_titleLabel;
    QLabel *m_messageLabel;
    QLabel *m_errorLabel;
    QHBoxLayout *m_digitLayout;
    
    QList<DigitLineEdit*> m_digitEdits;
    
    static const int DIGIT_COUNT = 6;
};

#endif // TOTPINPUTDIALOG_H