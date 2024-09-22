#include "bmp.h"

bool BMP::openBMP(const std::string &fileName) {
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return false;
    }

    // Чтение заголовка файла
    inFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

    // Проверка на формат BMP
    if (fileHeader.bfType != 0x4D42) {  // 'BM' в ASCII
        std::cerr << "File format is not BMP." << std::endl;
        return false;
    }

    // Чтение заголовка изображения
    inFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Проверка глубины цвета (24 или 32 бита)
    if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) {
        std::cerr << "Only 24-bit and 32-bit BMP files supported." << std::endl;
        return false;
    }

    // Чтение пиксельных данных
    size_t dataSize = fileHeader.bfSize - fileHeader.bfOffBits;
    data.resize(dataSize);
    inFile.seekg(fileHeader.bfOffBits, std::ios::beg);
    inFile.read(reinterpret_cast<char*>(data.data()), dataSize);

    inFile.close();
    return true;
}

void BMP::displayBMP(std::ostream& out) const {
    // Расчёт длины строки в байтах с учётом выравнивания (значение подгоняется вверх для ближайшего кратного 4-м)
    int rowStride = ((infoHeader.biWidth * (infoHeader.biBitCount / 8) + 3) & ~3);
    for (int y = 0; y < abs(infoHeader.biHeight); ++y) {
        int row = (infoHeader.biHeight > 0) ? abs(infoHeader.biHeight) - y - 1 : y; // BMP может быть перевёрнут
        for (int x = 0; x < infoHeader.biWidth; ++x) {
            int index = row * rowStride + x * (infoHeader.biBitCount / 8);
            uint8_t blue = data[index];
            uint8_t green = data[index + 1];
            uint8_t red = data[index + 2];

//                std::cout << y << ' ' << x << ' ' << (int)(blue) << ' ' << (int)(green) << ' ' << (int)(red) << std::endl;
            if (red == 255 && green == 255 && blue == 255) {
                out << " ";       // Белый цвет
            } else if (red == 0 && green == 0 && blue == 0) {
                out << "#";       // Чёрный цвет
            } else {
                out << "?";       // Неизвестный цвет
            }
        }
        out << std::endl;
    }
}

void BMP::closeBMP() {
    data.clear();
}