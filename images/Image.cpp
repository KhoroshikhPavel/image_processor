#include "Image.h"

#include "../help.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

Image::Image(int32_t width, int32_t height) : width_(width), height_(height) {
    if (width < 0 || height < 0) {
        throw std::runtime_error(ErrorWrongImageDimensions.data());
    }
    pixel_values_.resize(3ULL * static_cast<size_t>(width) * static_cast<size_t>(height), 0.0);
}

void Image::SetPixelValues(std::vector<float> values) {
    if (values.size() != pixel_values_.size()) {
        throw std::runtime_error(ErrorSizeMismatch.data());
    }

    pixel_values_ = std::move(values);
}

double Image::GetPixel(Color c, int32_t row, int32_t col) const {
    return pixel_values_[GetPixelIndex(c, row, col, width_, height_)];
}

void Image::SetPixel(Color c, int32_t row, int32_t col, float intensity) {
    pixel_values_[GetPixelIndex(c, row, col, width_, height_)] = intensity;
}

double Image::GetPixelClamped(Color c, int32_t row, int32_t col) const {
    const int32_t clamped_row = std::clamp(row, 0, height_ - 1);
    const int32_t clamped_col = std::clamp(col, 0, width_ - 1);
    return GetPixel(c, clamped_row, clamped_col);
}

std::size_t Image::GetPixelIndex(Color c, int32_t row, int32_t col, int32_t width, int32_t height) {
    return static_cast<std::size_t>(c) * width * std::abs(height) + static_cast<std::size_t>(row) * width + col;
}
