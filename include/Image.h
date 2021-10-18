
#ifndef IMAGE_PROCESSING_IMAGE_H
#define IMAGE_PROCESSING_IMAGE_H

#include <vector>
#include <cstdint>

class Image {
public:
    struct __attribute__((packed)) Pixel {

        Pixel() = default;

        Pixel(uint8_t r, uint8_t g, uint8_t b);

        uint8_t b, g, r;
    };

    Image() = default;

    Image(uint32_t width, uint32_t height);

    uint32_t get_width() const;

    uint32_t get_height() const;

    std::vector<Pixel> &operator[](uint32_t row);

    const std::vector<Pixel> &operator[](uint32_t row) const;


private:
    uint32_t width;
    uint32_t height;
    std::vector<std::vector<Pixel>> pixels;
};


#endif //IMAGE_PROCESSING_IMAGE_H
