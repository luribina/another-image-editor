#include "formats/BMPFormat.h"

#include <fstream>


Image BMPFormat::get_image(std::filesystem::path filename) {
    if (!exists(filename)) throw std::runtime_error("File does not exist");
    std::ifstream file{filename, std::ios_base::binary};
    if (!file) throw std::runtime_error("Can not open file");

    read_header(file);
    const uint32_t width = bmp_header.biWidth;
    const uint32_t height = bmp_header.biHeight;
    const uint32_t row_padding = width % 4;
    const uint32_t padded_row_size = width * 3 + row_padding;

    Image image{width, height};
    for (uint32_t i = 0; i < height; i++) {
        file.seekg(bmp_header.bOffBits + (i * padded_row_size));
        file.read(reinterpret_cast<char *>(&(image)[height - 1 - i][0]), width * sizeof(Image::Pixel));
        if (file.fail()) throw std::runtime_error("Failed to read file");
    }
    return image;
}

void BMPFormat::save_image(const Image &image, std::filesystem::path filename) {
    std::ofstream file{filename, std::ios_base::binary};
    if (!file) throw std::runtime_error("Can not open file");


    static uint8_t zero[3] = {0, 0, 0};
    const uint32_t row_padding = image.get_width() % 4;
    const uint32_t width = bmp_header.biWidth;
    const uint32_t height = bmp_header.biHeight;

    update_header(image);
    file.write(reinterpret_cast<char *>(&bmp_header), sizeof(BMPHeader));
    if (file.fail()) {
        throw std::runtime_error("Can not write to file");
    }

    for (uint32_t i = 0; i < height; i++) {
        file.write(reinterpret_cast<const char *>(&(image)[height - 1 - i][0]), width * sizeof(Image::Pixel));
        file.write(reinterpret_cast<char *>(&zero[0]), row_padding);
        if (file.fail()) throw std::runtime_error("Can not write to file");
    }
}

void BMPFormat::read_header(std::ifstream &file) {
    file.read(reinterpret_cast<char *>(&bmp_header), sizeof(BMPHeader));
    if (file.fail()) throw std::runtime_error("Failed to read file");
    if (bmp_header.bfType[0] != 'B' || bmp_header.bfType[1] != 'M') {
        throw std::runtime_error("Wrong file format");
    }
    if (bmp_header.biBitCount != 24) {
        throw std::runtime_error("Non 24 bitcount is not supported");
    }
    if (bmp_header.biCompression != 0) {
        throw std::runtime_error("Compressed files are not supported");
    }
}

void BMPFormat::update_header(const Image &image) {
    uint32_t row_padding = image.get_width() % 4;
    uint32_t size = image.get_height() * (image.get_width() * sizeof(Image::Pixel) + row_padding);
    uint32_t header_size = sizeof(BMPHeader);
    bmp_header.bfileSize = size + header_size;
    bmp_header.biWidth = image.get_width();
    bmp_header.biHeight = image.get_height();
    bmp_header.biSizeImage = size;
}


extern "C" {
IFormat *create_format_plugin() {
    return new BMPFormat;
}
}