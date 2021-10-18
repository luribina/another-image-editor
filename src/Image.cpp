#include "Image.h"

Image::Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b) : b(b), g(g), r(r) {}

Image::Image(uint32_t width, uint32_t height) : width(width), height(height),
                                                pixels(height, std::vector<Pixel>(width)) {}

std::vector<Image::Pixel> &Image::operator[](uint32_t row) {
    return pixels[row];
}

const std::vector<Image::Pixel> &Image::operator[](uint32_t row) const {
    return pixels[row];
}

uint32_t Image::get_width() const {
    return width;
}

uint32_t Image::get_height() const {
    return height;
}


