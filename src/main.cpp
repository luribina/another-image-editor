#include <iostream>
#include <memory>
#include <boost/program_options.hpp>

#include "formats/IFormat.h"
#include "effects/IEffect.h"
#include "PluginLoader.h"

namespace po = boost::program_options;

//todo add more effects
//todo update readme

int main(int argc, char **argv) {
    std::string input;
    std::string format;
    std::string effect;

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "print command usage")
            ("input,i", po::value<std::string>(&input), "input file")
            ("format,f", po::value<std::string>(&format), "file format")
            ("effect,e", po::value<std::string>(&effect), "file effect");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    auto available_formats = PluginLoader::available_plugins("./src/formats");
    auto available_effects = PluginLoader::available_plugins("./src/effects");

    if (vm.count("help")) {
        std::cout << "Usage:\n"
                     "./image_processing -i file_input -e effect -f format" << std::endl;
        std::cout<<desc<<std::endl;
        std::cout<<"Available formats:"<<std::endl;
        for (const auto &[key, value]:available_formats) {
            std::cout<<key.substr(3, key.length()-9)<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<"Available effects:"<<std::endl;
        for (const auto &[key, value]:available_effects) {
            std::cout<<key.substr(3, key.length()-9)<<std::endl;
        }
        std::cout<<std::endl;
        return 0;
    }

    std::string lib_format = "lib"+format+"format";
    std::string lib_effect = "lib"+effect+"effect";
    if (!available_formats.count(lib_format)) {
        std::cout<<"This format is not available"<<std::endl;
        return 0;
    }
    if (!available_effects.count(lib_effect)) {
        std::cout<<"This effect doesn't exist"<<std::endl;
        return 0;
    }
    auto input_path = fs::path(input);
    std::string output = input_path.stem().string()+"_"+effect+".bmp";
    std::unique_ptr<IFormat> format_plugin;
    std::unique_ptr<IEffect> effect_plugin;
    try {
        format_plugin = PluginLoader::load_plugin<IFormat>(available_formats.at(lib_format).string());
        effect_plugin = PluginLoader::load_plugin<IEffect>(available_effects.at(lib_effect).string());
    } catch (std::runtime_error &error) {
        std::cout<<error.what()<<std::endl;
        return -1;
    }

    try {
        Image original = format_plugin->get_image(input_path);
        Image copy = effect_plugin->apply_effect(original);
        format_plugin->save_image(copy, fs::path(output));
    } catch (std::runtime_error &error) {
        std::cout<<error.what()<<std::endl;
        return -1;
    }

//    try {
//        format_plugin->save_image(copy, fs::path(output));
//    } catch (std::runtime_error &error) {
//        std::cout<<"Error while saving file"<<std::endl;
//        std::cout<<error.what()<<std::endl;
//        return -1;
//    }

    return 0;
}
