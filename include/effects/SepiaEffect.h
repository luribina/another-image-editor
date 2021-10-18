#ifndef IMAGE_PROCESSING_SEPIAEFFECT_H
#define IMAGE_PROCESSING_SEPIAEFFECT_H

#include "IEffect.h"

class SepiaEffect : public IEffect {
public:
    SepiaEffect() = default;

    Image apply_effect(const Image &image) override;
};

extern "C" {
IEffect *create_effect_plugin();
}

#endif //IMAGE_PROCESSING_SEPIAEFFECT_H
