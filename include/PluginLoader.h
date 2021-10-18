#ifndef IMAGE_PROCESSING_PLUGINLOADER_H
#define IMAGE_PROCESSING_PLUGINLOADER_H

#include <dlfcn.h>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include <algorithm>

#include "effects/IEffect.h"
#include "formats/IFormat.h"

namespace fs = std::filesystem;

class PluginLoader {
public:
    template<class PluginType, std::enable_if_t<std::is_same_v<IEffect, PluginType>, bool> = true>
    static std::unique_ptr<PluginType> load_plugin(const std::string &plugin_path) {
        return _load_plugin<PluginType>(plugin_path, "create_effect_plugin");
    }

    template<class PluginType, std::enable_if_t<std::is_same_v<IFormat, PluginType>, bool> = true>
    static std::unique_ptr<PluginType> load_plugin(const std::string &plugin_path) {
        return _load_plugin<PluginType>(plugin_path, "create_format_plugin");
    }

    static std::unordered_map<std::string, fs::path> available_plugins(const std::string &dir_path) {
        std::unordered_map<std::string, fs::path> plugins;
        for (const auto &file : fs::directory_iterator(dir_path)) {
            if (!file.is_regular_file()) {
                continue;
            }

            const fs::path &path = file.path();
            if (path.extension() != ".so") {
                continue;
            }
            std::string name_lowered = path.stem();
            std::transform(name_lowered.begin(), name_lowered.end(), name_lowered.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            plugins.emplace(name_lowered, path);
        }

        return plugins;
    }

private:

    template<class PluginType>
    static std::unique_ptr<PluginType> _load_plugin(const std::string &plugin_path, std::string &&plugin_fn) {
        void *plugin_lib = dlopen(plugin_path.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (!plugin_lib) {
            throw std::runtime_error("Failed to load plugin \"" + plugin_path + "\": " + dlerror());
        }

        auto create_plugin_fn = reinterpret_cast<typename PluginType::create_plugin_fn>(dlsym(plugin_lib,
                                                                                              plugin_fn.c_str()));
        if (!create_plugin_fn) {
            throw std::runtime_error("Failed to load plugin \"" + plugin_path + "\" factory function: : " + dlerror());
        }

        return std::unique_ptr<PluginType>(create_plugin_fn());
    }

};

#endif //IMAGE_PROCESSING_PLUGINLOADER_H
