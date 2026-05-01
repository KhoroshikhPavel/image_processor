#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "ArgsParser.h"
#include "FilterRegistry.h"
#include "Utils.h"
#include "help.h"
#include "io/ImageFormatFactory.h"
#include "filters/BlurFilter.h"
#include "filters/CropFilter.h"
#include "filters/EdgeFilter.h"
#include "filters/GrayscaleFilter.h"
#include "filters/NegativeFilter.h"
#include "filters/SharpFilter.h"
#include "filters/SunFadeFilter.h"
#include "images/Image.h"

static void RegisterFilters() {
    FilterRegistry::Register("-gs",
                             [](const std::vector<std::string>&) { return std::make_unique<GrayscaleFilter>(); });

    FilterRegistry::Register("-neg",
                             [](const std::vector<std::string>&) { return std::make_unique<NegativeFilter>(); });

    FilterRegistry::Register("-sharp", [](const std::vector<std::string>&) { return std::make_unique<SharpFilter>(); });

    FilterRegistry::Register("-crop", [](const std::vector<std::string>& params) {
        if (params.size() != 2) {
            std::string args_str;
            for (const auto& p : params) {
                args_str += (args_str.empty() ? "" : " ") + p;
            }
            size_t count = params.size();
            std::string args_display = params.empty() ? "(none)" : args_str;
            throw std::runtime_error(std::vformat(ErrorCropArgs, std::make_format_args(count, args_display)));
        }
        int32_t width = TryParseInt(params[0]);
        int32_t height = TryParseInt(params[1]);
        if (width <= 0 || height <= 0) {
            throw std::runtime_error(std::vformat(ErrorCropDimensions, std::make_format_args(width, height)));
        }
        return std::make_unique<CropFilter>(width, height);
    });

    FilterRegistry::Register("-edge", [](const std::vector<std::string>& params) {
        if (params.size() != 1) {
            std::string args_str;
            for (const auto& p : params) {
                args_str += (args_str.empty() ? "" : " ") + p;
            }
            size_t count = params.size();
            std::string args_display = params.empty() ? "(none)" : args_str;
            throw std::runtime_error(std::vformat(ErrorEdgeArg, std::make_format_args(count, args_display)));
        }
        double threshold = TryParseDouble(params[0]);
        if (threshold < 0.0 || threshold > 1.0) {
            throw std::runtime_error(std::vformat(ErrorEdgeThreshold, std::make_format_args(threshold)));
        }
        return std::make_unique<EdgeFilter>(threshold);
    });

    FilterRegistry::Register("-blur", [](const std::vector<std::string>& params) {
        if (params.size() != 1) {
            std::string args_str;
            for (const auto& p : params) {
                args_str += (args_str.empty() ? "" : " ") + p;
            }
            size_t count = params.size();
            std::string args_display = params.empty() ? "(none)" : args_str;
            throw std::runtime_error(std::vformat(ErrorBlurArg, std::make_format_args(count, args_display)));
        }
        double sigma = TryParseDouble(params[0]);
        if (sigma <= 0.0) {
            throw std::runtime_error(std::vformat(ErrorBlurSigma, std::make_format_args(sigma)));
        }
        return std::make_unique<BlurFilter>(sigma);
    });

    FilterRegistry::Register("-sunfade", [](const std::vector<std::string>& params) {
        if (params.size() != 2) {
            std::string args_str;
            for (const auto& p : params) {
                args_str += (args_str.empty() ? "" : " ") + p;
            }
            size_t count = params.size();
            std::string args_display = params.empty() ? "(none)" : args_str;
            throw std::runtime_error(std::vformat(ErrorSunfadeArgs, std::make_format_args(count, args_display)));
        }
        double desaturation = TryParseDouble(params[0]);
        double bleach = TryParseDouble(params[1]);
        if (desaturation < 0.0 || desaturation > 1.0 || bleach < 0.0 || bleach > 1.0) {
            throw std::runtime_error(std::vformat(ErrorSunfadeParams, std::make_format_args(desaturation, bleach)));
        }
        return std::make_unique<SunFadeFilter>(desaturation, bleach);
    });
}

int main(int argc, char** argv) {
    try {
        RegisterFilters();

        auto [input_path, output_path, filters] = ArgsParser::Parse(argc, argv);

        Image img = CreateReader(input_path)->Read(input_path);

        for (auto& [name, params] : filters) {
            const auto filter = FilterRegistry::Create(name, params);
            filter->Apply(img);
        }

        CreateWriter(output_path)->Write(output_path, img);

    } catch (const std::exception& e) {
        if (e.what() == ErrorShowHelp) {
            std::cout << HelpMessage << '\n';
            return 0;
        }
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
