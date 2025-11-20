#include "qrcodegenerator.h"
#include <QPainter>
#include <QBitArray>
#include <QtMath>

QRCodeGenerator::QRCodeGenerator()
{
}

QPixmap QRCodeGenerator::generateQRCode(const QString &text, int size, int margin)
{
    return generateQRCode(text, size, margin, Qt::black, Qt::white);
}

QPixmap QRCodeGenerator::generateQRCode(const QString &text, int size, int margin, 
                                        const QColor &foreground, const QColor &background)
{
    int matrixSize = 0;
    QVector<QVector<bool>> matrix = generateQRMatrix(text, matrixSize);
    
    if (matrixSize == 0) {
        qWarning() << "Failed to generate QR matrix";
        return QPixmap();
    }
    
    // Calculate module size (each black/white square)
    int totalSize = size - (2 * margin);
    int moduleSize = totalSize / matrixSize;
    int actualSize = (moduleSize * matrixSize) + (2 * margin);
    
    // Create pixmap
    QPixmap pixmap(actualSize, actualSize);
    pixmap.fill(background);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setBrush(QBrush(foreground));
    painter.setPen(Qt::NoPen);
    
    // Draw QR code modules
    for (int y = 0; y < matrixSize; ++y) {
        for (int x = 0; x < matrixSize; ++x) {
            if (matrix[y][x]) {
                int pixelX = margin + (x * moduleSize);
                int pixelY = margin + (y * moduleSize);
                painter.drawRect(pixelX, pixelY, moduleSize, moduleSize);
            }
        }
    }
    
    return pixmap;
}

bool QRCodeGenerator::saveQRCode(const QString &text, const QString &filename, int size)
{
    QPixmap qrCode = generateQRCode(text, size);
    return !qrCode.isNull() && qrCode.save(filename);
}

QVector<QVector<bool>> QRCodeGenerator::generateQRMatrix(const QString &text, int &matrixSize)
{
    // For simplicity, we'll create a basic QR-like pattern
    // In production, you'd use a proper QR library like libqrencode
    
    // Determine matrix size based on data length
    int dataLength = text.length();
    if (dataLength <= 25) {
        matrixSize = 21; // Version 1
    } else if (dataLength <= 47) {
        matrixSize = 25; // Version 2
    } else if (dataLength <= 77) {
        matrixSize = 29; // Version 3
    } else {
        matrixSize = 33; // Version 4
    }
    
    // Initialize matrix
    QVector<QVector<bool>> matrix(matrixSize, QVector<bool>(matrixSize, false));
    
    // Add finder patterns (corner squares)
    addFinderPatterns(matrix, matrixSize);
    
    // Add timing patterns
    addTimingPatterns(matrix, matrixSize);
    
    // Add dark module
    addDarkModule(matrix, matrixSize);
    
    // Encode and place data
    QByteArray encodedData = encodeData(text);
    placeData(matrix, encodedData, matrixSize);
    
    // Apply mask pattern
    applyMask(matrix, matrixSize, 0);
    
    return matrix;
}

QByteArray QRCodeGenerator::encodeData(const QString &text)
{
    QByteArray data;
    
    // Simple byte mode encoding
    // Mode indicator (4 bits) + Character count (8 bits) + Data
    QBitArray bits;
    
    // Mode indicator: 0100 (byte mode)
    bits.resize(4);
    bits.setBit(2, true); // 0100
    
    // Character count
    QBitArray countBits(8);
    int length = text.length();
    for (int i = 0; i < 8; ++i) {
        countBits.setBit(7 - i, (length >> i) & 1);
    }
    
    // Convert text to bytes
    QByteArray textBytes = text.toUtf8();
    QBitArray dataBits(textBytes.size() * 8);
    for (int i = 0; i < textBytes.size(); ++i) {
        unsigned char byte = textBytes.at(i);
        for (int j = 0; j < 8; ++j) {
            dataBits.setBit(i * 8 + (7 - j), (byte >> j) & 1);
        }
    }
    
    // Combine all bits
    QBitArray finalBits(bits.size() + countBits.size() + dataBits.size());
    int pos = 0;
    
    // Copy mode bits
    for (int i = 0; i < bits.size(); ++i) {
        finalBits.setBit(pos++, bits.testBit(i));
    }
    
    // Copy count bits
    for (int i = 0; i < countBits.size(); ++i) {
        finalBits.setBit(pos++, countBits.testBit(i));
    }
    
    // Copy data bits
    for (int i = 0; i < dataBits.size(); ++i) {
        finalBits.setBit(pos++, dataBits.testBit(i));
    }
    
    // Convert bits to bytes
    int byteCount = (finalBits.size() + 7) / 8;
    data.resize(byteCount);
    for (int i = 0; i < byteCount; ++i) {
        unsigned char byte = 0;
        for (int j = 0; j < 8 && (i * 8 + j) < finalBits.size(); ++j) {
            if (finalBits.testBit(i * 8 + j)) {
                byte |= (1 << (7 - j));
            }
        }
        data[i] = byte;
    }
    
    return data;
}

void QRCodeGenerator::addFinderPatterns(QVector<QVector<bool>> &matrix, int size)
{
    // Top-left finder pattern
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            bool dark = false;
            if ((y == 0 || y == 6) && x <= 6) dark = true;
            if ((x == 0 || x == 6) && y <= 6) dark = true;
            if (y >= 2 && y <= 4 && x >= 2 && x <= 4) dark = true;
            if (y == 7 || x == 7) dark = false; // Separator
            
            if (x < size && y < size) {
                matrix[y][x] = dark;
            }
        }
    }
    
    // Top-right finder pattern
    int offset = size - 8;
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 8; ++x) {
            bool dark = false;
            if ((y == 0 || y == 6) && x >= 1) dark = true;
            if ((x == 1 || x == 7) && y <= 6) dark = true;
            if (y >= 2 && y <= 4 && x >= 3 && x <= 5) dark = true;
            if (x == 0) dark = false; // Separator
            
            int actualX = offset + x;
            if (actualX < size && y < size) {
                matrix[y][actualX] = dark;
            }
        }
    }
    
    // Bottom-left finder pattern
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 9; ++x) {
            bool dark = false;
            if ((y == 1 || y == 7) && x <= 6) dark = true;
            if ((x == 0 || x == 6) && y >= 1) dark = true;
            if (y >= 3 && y <= 5 && x >= 2 && x <= 4) dark = true;
            if (y == 0 || x == 7) dark = false; // Separator
            
            int actualY = size - 8 + y;
            if (x < size && actualY < size) {
                matrix[actualY][x] = dark;
            }
        }
    }
}

void QRCodeGenerator::addTimingPatterns(QVector<QVector<bool>> &matrix, int size)
{
    // Horizontal timing pattern
    for (int x = 8; x < size - 8; ++x) {
        matrix[6][x] = (x % 2 == 0);
    }
    
    // Vertical timing pattern
    for (int y = 8; y < size - 8; ++y) {
        matrix[y][6] = (y % 2 == 0);
    }
}

void QRCodeGenerator::addDarkModule(QVector<QVector<bool>> &matrix, int size)
{
    // Dark module at (4*version + 9, 8)
    int version = (size - 17) / 4;
    int moduleY = 4 * version + 9;
    if (moduleY < size) {
        matrix[moduleY][8] = true;
    }
}

void QRCodeGenerator::addFormatInfo(QVector<QVector<bool>> &matrix, int size)
{
    // Simplified format info pattern
    // This would normally contain error correction level and mask pattern info
    QBitArray formatBits(15);
    // Default format: L error correction, mask pattern 0
    // This is a simplified version - real QR codes use Reed-Solomon encoding
    
    // Place format info around finder patterns
    for (int i = 0; i < 6; ++i) {
        matrix[8][i] = formatBits.testBit(i);
        matrix[size - 1 - i][8] = formatBits.testBit(i);
    }
    
    matrix[8][7] = formatBits.testBit(6);
    matrix[8][8] = formatBits.testBit(7);
    matrix[7][8] = formatBits.testBit(8);
    
    for (int i = 9; i < 15; ++i) {
        matrix[14 - i][8] = formatBits.testBit(i);
        matrix[8][size - 15 + i] = formatBits.testBit(i);
    }
}

void QRCodeGenerator::placeData(QVector<QVector<bool>> &matrix, const QByteArray &data, int size)
{
    // Simplified data placement
    // In a real QR code, this follows a specific zigzag pattern
    
    int dataIndex = 0;
    int bitIndex = 7;
    
    // Place data in available modules (avoiding function patterns)
    for (int y = size - 1; y >= 0; y -= 2) {
        if (y == 6) y--; // Skip timing column
        
        for (int x = size - 1; x >= 0; --x) {
            for (int col = 0; col < 2; ++col) {
                int actualX = x - col;
                if (actualX < 0) continue;
                
                // Skip if this position is already used by function patterns
                if (isReservedModule(actualX, y, size)) continue;
                
                // Place data bit
                bool dataBit = false;
                if (dataIndex < data.size()) {
                    dataBit = (data.at(dataIndex) >> bitIndex) & 1;
                    bitIndex--;
                    if (bitIndex < 0) {
                        bitIndex = 7;
                        dataIndex++;
                    }
                }
                
                matrix[y][actualX] = dataBit;
            }
        }
    }
}

bool QRCodeGenerator::isReservedModule(int x, int y, int size)
{
    // Check finder patterns
    if ((x < 9 && y < 9) || // Top-left
        (x >= size - 8 && y < 9) || // Top-right
        (x < 9 && y >= size - 8)) { // Bottom-left
        return true;
    }
    
    // Check timing patterns
    if (x == 6 || y == 6) {
        return true;
    }
    
    // Check dark module
    int version = (size - 17) / 4;
    int darkModuleY = 4 * version + 9;
    if (x == 8 && y == darkModuleY) {
        return true;
    }
    
    return false;
}

void QRCodeGenerator::applyMask(QVector<QVector<bool>> &matrix, int size, int maskPattern)
{
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (!isReservedModule(x, y, size)) {
                if (getMaskPattern(x, y, maskPattern)) {
                    matrix[y][x] = !matrix[y][x];
                }
            }
        }
    }
}

bool QRCodeGenerator::getMaskPattern(int x, int y, int pattern)
{
    switch (pattern) {
    case 0: return (x + y) % 2 == 0;
    case 1: return y % 2 == 0;
    case 2: return x % 3 == 0;
    case 3: return (x + y) % 3 == 0;
    case 4: return (x / 3 + y / 2) % 2 == 0;
    case 5: return ((x * y) % 2) + ((x * y) % 3) == 0;
    case 6: return (((x * y) % 2) + ((x * y) % 3)) % 2 == 0;
    case 7: return (((x + y) % 2) + ((x * y) % 3)) % 2 == 0;
    default: return false;
    }
}