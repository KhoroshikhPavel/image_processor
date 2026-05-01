#ifndef CPP_HSE_UTILS_H
#define CPP_HSE_UTILS_H

#include <charconv>
#include <cstdint>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>

constexpr uint8_t MaxByteValue = 255;

inline uint32_t RoundUpToMultipleOfFour(uint32_t x) {
    switch (x % 4) {
        case 0:
            return x;
        case 1:
            return x + 3;
        case 2:
            return x + 2;
        case 3:
            return x + 1;
        default:
            throw std::runtime_error("MATH STOPPED WORKING");
    }
}

inline int32_t TryParseInt(std::string_view str) {
    int32_t result = 0;
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
    if (ec == std::errc::invalid_argument) {
        throw std::runtime_error(std::format("'{}' is not a valid integer", str));
    }
    if (ec == std::errc::result_out_of_range) {
        throw std::runtime_error(std::format("'{}' is out of integer range", str));
    }
    if (ptr != str.data() + str.size()) {
        throw std::runtime_error(std::format("'{}' is not a valid integer", str));
    }
    return result;
}

inline double TryParseDouble(std::string_view str) {
    double result = 0.0;
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
    if (ec == std::errc::invalid_argument) {
        throw std::runtime_error(std::format("'{}' is not a valid number", str));
    }
    if (ec == std::errc::result_out_of_range) {
        throw std::runtime_error(std::format("'{}' is out of range", str));
    }
    if (ptr != str.data() + str.size()) {
        throw std::runtime_error(std::format("'{}' is not a valid number", str));
    }
    return result;
}

inline std::string_view GetExtension(std::string_view path) {
    const auto pos = path.rfind('.');
    if (pos == std::string_view::npos) {
        return {};
    }
    return path.substr(pos + 1);
}

#endif  // CPP_HSE_UTILS_H
