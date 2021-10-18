#ifndef IMAGE_PROCESSING_FORMAT_H
#define IMAGE_PROCESSING_FORMAT_H

#include "Image.h"
#include <memory>
#include <string>
#include <filesystem>

class IFormat {
public:
    IFormat() = default;

    virtual ~IFormat() = default;

    using create_plugin_fn = std::add_pointer_t<IFormat *()>;

    virtual Image get_image(std::filesystem::path filename) = 0;

    virtual void save_image(const Image &image, std::filesystem::path filename) = 0;
};


#endif //IMAGE_PROCESSING_FORMAT_H
