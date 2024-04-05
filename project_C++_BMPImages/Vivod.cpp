#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

using WORD = uint16_t;
using DWORD = uint32_t;
using LONG = int32_t;
using BITE = unsigned char;


#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER {
    WORD  bfType;
    DWORD bfSize;
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffBits;
} __attribute__((packed)) BITMAPFILEHEADER;
#pragma pack(pop) //это и 7 строка нужна только при работе на винде, если убунта или линух или clion - их не пишем


typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} __attribute__((packed)) BITMAPINFOHEADER;

class Color {
public:
    Color() : red(0), green(0), blue(0) {}
    Color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}

    void applyFilter() {
        blue = 0;
    }

    void toGrayScale() {
        uint8_t gray = static_cast<uint8_t>((red + green + blue) / 3);
        red = green = blue = gray;
    }

    uint8_t getRed() const { return red; }
    uint8_t getGreen() const { return green; }
    uint8_t getBlue() const { return blue; }

private:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class BitmapImage {
public:
    BitmapImage(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Error: Unable to open file " + filename);
        }

        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BITMAPFILEHEADER));
        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BITMAPINFOHEADER));

        if (file.fail()) {
            throw runtime_error("Error: Unable to read bitmap headers from file " + filename);
        }

        size_t imageSize = infoHeader.biWidth * infoHeader.biHeight * 3; // RGB image
        image.resize(imageSize);
        file.seekg(fileHeader.bfOffBits, ios::beg);
        file.read(reinterpret_cast<char*>(image.data()), imageSize);

        if (file.fail()) {
            throw runtime_error("Error: Unable to read bitmap image data from file " + filename);
        }
    }

    void applyFilter() {
        for (size_t i = 2; i < image.size(); i+= 3) {
            image[i] = 0;
        }
    }

    void toGrayScale() {
        for (size_t i = 0; i < image.size(); i += 3) {
            Color color(image[i + 2], image[i + 1], image[i]);
            color.toGrayScale();
            image[i] = color.getBlue();
            image[i + 1] = color.getGreen();
            image[i + 2] = color.getRed();
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Error: Unable to create file " + filename);
        }

        file.write(reinterpret_cast<char*>(&fileHeader), sizeof(BITMAPFILEHEADER));
        file.write(reinterpret_cast<char*>(&infoHeader), sizeof(BITMAPINFOHEADER));
        file.write(reinterpret_cast<char*>(image.data()), image.size());

        if (file.fail()) {
            throw runtime_error("Error: Unable to write bitmap data to file " + filename);
        }
    }

private:
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    vector<uint8_t> image;
};

class FilterController {
public:
    static void applyFilters(BitmapImage& image, const vector<string>& filters) {
        for (const auto& filter : filters) {
            if (filter == "filter1") {
                image.toGrayScale();
            } else if (filter == "filter2") {
                image.applyFilter();
            } else {
                cerr << "Warning: Unknown filter '" << filter << "', skipping..." << endl;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            cerr << "Usage: " << argv[0] << " input_file(.bmp format) output_file(.bmp format) [-filter1 param1 param2 ...] [-filter2 param1 param2 ...] ..." << endl;
            return 1;
        }

        string inputFilename = argv[1];
        string outputFilename = argv[2];

        BitmapImage image(inputFilename);

        vector<string> filters;
        for (int i = 3; i < argc; ++i) {
            filters.push_back(argv[i]);
        }

        FilterController::applyFilters(image, filters);

        image.saveToFile(outputFilename);

        cout << "Image processed successfully." << endl;
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
