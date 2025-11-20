#ifndef QRCODEGENERATOR_H
#define QRCODEGENERATOR_H

#include <QPixmap>
#include <QString>
#include <QPainter>
#include <QColor>
#include <QDebug>

class QRCodeGenerator
{
public:
    QRCodeGenerator();
    
    // Generate QR code as QPixmap
    static QPixmap generateQRCode(const QString &text, int size = 200, int margin = 4);
    
    // Generate QR code with custom colors
    static QPixmap generateQRCode(const QString &text, int size, int margin, 
                                  const QColor &foreground, const QColor &background);
    
    // Save QR code to file
    static bool saveQRCode(const QString &text, const QString &filename, int size = 200);

private:
    // Simple QR code matrix generation (basic implementation)
    static QVector<QVector<bool>> generateQRMatrix(const QString &text, int &matrixSize);
    
    // Error correction and encoding
    static QByteArray encodeData(const QString &text);
    static void addErrorCorrection(QByteArray &data);
    
    // QR code pattern placement
    static void addFinderPatterns(QVector<QVector<bool>> &matrix, int size);
    static void addTimingPatterns(QVector<QVector<bool>> &matrix, int size);
    static void addDarkModule(QVector<QVector<bool>> &matrix, int size);
    static void addFormatInfo(QVector<QVector<bool>> &matrix, int size);
    
    // Data placement
    static void placeData(QVector<QVector<bool>> &matrix, const QByteArray &data, int size);
    
    // Mask patterns
    static void applyMask(QVector<QVector<bool>> &matrix, int size, int maskPattern = 0);
    static bool getMaskPattern(int x, int y, int pattern);
    
    // Helper functions
    static bool isReservedModule(int x, int y, int size);
};

#endif // QRCODEGENERATOR_H