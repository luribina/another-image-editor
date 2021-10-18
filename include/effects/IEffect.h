#ifndef IMAGE_PROCESSING_EFFECT_H
#define IMAGE_PROCESSING_EFFECT_H

#include "Image.h"
#include <memory>

class IEffect {
public:
    IEffect() = default;

    virtual ~IEffect() = default;

    using create_plugin_fn = std::add_pointer_t<IEffect *()>;

    virtual Image apply_effect(const Image &image) = 0;
};

#endif //IMAGE_PROCESSING_EFFECT_H
