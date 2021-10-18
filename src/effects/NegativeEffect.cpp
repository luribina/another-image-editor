#include "effects/NegativeEffect.h"

Image NegativeEffect::apply_effect(const Image &image) {
    Image negative_image{image.get_width(), image.get_height()};
    for (uint32_t i = 0; i < negative_image.get_height(); ++i) {
        for (uint32_t j = 0; j < negative_image.get_width(); ++j) {
            negative_image[i][j].r = 255 - image[i][j].r;
            negative_image[i][j].g = 255 - image[i][j].g;
            negative_image[i][j].b = 255 - image[i][j].b;
        }
    }
    return negative_image;
}

extern "C" {
    IEffect *create_effect_plugin() {
        return new NegativeEffect;
    }
}