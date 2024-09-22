#ifndef BMP_READER_BMP_H
#define BMP_READER_BMP_H
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

class BMP {
private:
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    std::vector<uint8_t> data;

public:
    bool openBMP(const std::string &fileName);
    void displayBMP(std::ostream& out = std::cout) const;
    void closeBMP();
};


#endif //BMP_READER_BMP_H
