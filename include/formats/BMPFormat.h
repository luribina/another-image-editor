
#ifndef IMAGE_PROCESSING_BMPFORMAT_H
#define IMAGE_PROCESSING_BMPFORMAT_H

#include "IFormat.h"

class BMPFormat : public IFormat {

    struct __attribute__((packed)) BMPHeader {
        char bfType[2] = {'B', 'M'};
        uint32_t bfileSize{};
        uint32_t bfReserved{};
        uint32_t bOffBits{};
        uint32_t biSize{};
        uint32_t biWidth{};
        uint32_t biHeight{};
        uint16_t biPlanes{};
        uint16_t biBitCount{};
        uint32_t biCompression{};
        uint32_t biSizeImage{};
        uint32_t biXPelsPerMeter{};
        uint32_t biYPelsPerMeter{};
        uint32_t biClrUsed{};
        uint32_t biClrImportant{};
    };

public:
    BMPFormat() = default;

    Image get_image(std::filesystem::path filename) override;

    void save_image(const Image &image, std::filesystem::path filename) override;

private:
    void read_header(std::ifstream &file);

    void update_header(const Image &image);

    BMPHeader bmp_header{};
};

extern "C" {
IFormat *create_format_plugin();
}


#endif //IMAGE_PROCESSING_BMPFORMAT_H
