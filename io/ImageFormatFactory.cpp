#include "ImageFormatFactory.h"

#include "BMPReader.h"
#include "BMPWriter.h"
#include "../Utils.h"
#include "../help.h"

#include <algorithm>
#include <format>
#include <stdexcept>
#include <string>

namespace {

std::string ToLower(std::string_view s) {
    std::string result(s);
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

}  // namespace

std::unique_ptr<Reader> CreateReader(std::string_view path) {
    const auto ext = GetExtension(path);
    if (ext.empty()) {
        throw std::runtime_error(std::vformat(ErrorNoExtension, std::make_format_args(path)));
    }

    const auto ext_lower = ToLower(ext);
    if (ext_lower == "bmp") {
        return std::make_unique<BMPReader>();
    }

    throw std::runtime_error(std::vformat(ErrorUnsupportedFormat, std::make_format_args(ext)));
}

std::unique_ptr<Writer> CreateWriter(std::string_view path) {
    const auto ext = GetExtension(path);
    if (ext.empty()) {
        throw std::runtime_error(std::vformat(ErrorNoExtension, std::make_format_args(path)));
    }

    const auto ext_lower = ToLower(ext);
    if (ext_lower == "bmp") {
        return std::make_unique<BMPWriter>();
    }

    throw std::runtime_error(std::vformat(ErrorUnsupportedFormat, std::make_format_args(ext)));
}
