#include "SunFadeFilter.h"

#include <algorithm>

void SunFadeFilter::Apply(Image& img) {
    const int32_t height = img.Height();
    const int32_t width = img.Width();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            const float r = static_cast<float>(img.GetPixel(Color::Red, i, j));
            const float g = static_cast<float>(img.GetPixel(Color::Green, i, j));
            const float b = static_cast<float>(img.GetPixel(Color::Blue, i, j));

            const float luminance = static_cast<float>(LuminanceR * r + LuminanceG * g + LuminanceB * b);
            const float r1 =
                (1.0f - static_cast<float>(desaturation_)) * r + static_cast<float>(desaturation_) * luminance;
            const float g1 =
                (1.0f - static_cast<float>(desaturation_)) * g + static_cast<float>(desaturation_) * luminance;
            const float b1 =
                (1.0f - static_cast<float>(desaturation_)) * b + static_cast<float>(desaturation_) * luminance;

            const float r2 = r1 + static_cast<float>(bleach_) * (1.0f - r1);
            const float g2 = g1 + static_cast<float>(bleach_) * (1.0f - g1);
            const float b2 = b1 + static_cast<float>(bleach_) * (1.0f - b1);

            img.SetPixel(Color::Red, i, j, std::clamp<float>(r2 * RedFade, 0.0f, 1.0f));
            img.SetPixel(Color::Green, i, j, std::clamp<float>(g2 * GreenFade, 0.0f, 1.0f));
            img.SetPixel(Color::Blue, i, j, std::clamp<float>(b2 * BlueFade, 0.0f, 1.0f));
        }
    }
}
