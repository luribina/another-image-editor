
#include <effects/NegativeEffect.h>

#include "effects/SepiaEffect.h"

Image SepiaEffect::apply_effect(const Image &image) {
    Image sepia_image{image.get_width(), image.get_height()};
    for (uint32_t i = 0; i < sepia_image.get_height(); ++i) {
        for (uint32_t j = 0; j < sepia_image.get_width(); ++j) {
            sepia_image[i][j].r = std::min(255, (int) (image[i][j].r * 0.393 +
                                                       image[i][j].g * 0.769 +
                                                       image[i][j].b * 0.189));
            sepia_image[i][j].g = std::min(255, (int) (image[i][j].r * 0.349 +
                                                       image[i][j].g * 0.686 +
                                                       image[i][j].b * 0.168));
            sepia_image[i][j].b = std::min(255, (int) (image[i][j].r * 0.272 +
                                                       image[i][j].g * 0.534 +
                                                       image[i][j].b * 0.131));
        }
    }
    return sepia_image;
}

extern "C" {
IEffect *create_effect_plugin() {
    return new SepiaEffect;
}
}
