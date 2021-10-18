#ifndef IMAGE_PROCESSING_NEGATIVEEFFECT_H
#define IMAGE_PROCESSING_NEGATIVEEFFECT_H

#include "IEffect.h"

class NegativeEffect: public IEffect {
public:
    NegativeEffect() = default;

    Image apply_effect(const Image &image) override;

};

extern "C" {
    IEffect *create_effect_plugin();
}


#endif //IMAGE_PROCESSING_NEGATIVEEFFECT_H
