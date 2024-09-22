#include "bmp.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Using: " << argv[0] << " <BMP file path> [--save]" << std::endl;
        return 1;
    }

    std::string filename = std::string(argv[1]);
    BMP bmp;
    if (!bmp.openBMP(filename)) {
        return 1;
    }
    bool saveToFile = (argc == 3 && std::string(argv[2]) == "--save");

    if (saveToFile) {
        filename.replace(filename.size()-3,3,"txt");

        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Failed to create an output file." << std::endl;
            return 1;
        }
        // Сохраняем вывод в файл
        bmp.displayBMP(outFile);
        std::cout << "Output saved to " << filename << std::endl;
        outFile.close();
    } else {
        // Вывод в консоль
        bmp.displayBMP();
    }

    bmp.closeBMP();

    return 0;
}