#ifndef CPP_HSE_IMAGE_H
#define CPP_HSE_IMAGE_H

#include <span>
#include <vector>
#include <cstdint>

constexpr float MaxPixelValue = 255.0f;

enum class Color {
    Blue = 0,
    Green = 1,
    Red = 2,
};

class Image {
    std::vector<float> pixel_values_;
    int32_t width_ = 0;
    int32_t height_ = 0;

public:
    Image() = default;
    Image(int32_t width, int32_t height);

    int32_t Width() const {
        return width_;
    }
    int32_t Height() const {
        return height_;
    }

    double GetPixel(Color c, int32_t row, int32_t col) const;
    void SetPixel(Color c, int32_t row, int32_t col, float intensity);

    double GetPixelClamped(Color c, int32_t row, int32_t col) const;

    static std::size_t GetPixelIndex(Color c, int32_t row, int32_t col, int32_t width, int32_t height);

    std::span<const float> GetPixelValues() const {
        return pixel_values_;
    }
    std::span<float> GetPixelValues() {
        return pixel_values_;
    }

    void SetPixelValues(std::vector<float> values);
};

#endif  // CPP_HSE_IMAGE_H
