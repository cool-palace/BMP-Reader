#include "bmp.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Using: " << argv[0] << " <BMP file path>" << std::endl;
        return 1;
    }

    BMP bmp;
    if (bmp.openBMP(argv[1])) {
        bmp.displayBMP();
        bmp.closeBMP();
    } else {
        return 1;
    }

    return 0;
}