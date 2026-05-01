#ifndef CPP_HSE_FILTERUTILS_H
#define CPP_HSE_FILTERUTILS_H

#include "images/Image.h"

#include <algorithm>
#include <vector>

inline void ApplyKernel(Image& img, const std::vector<std::vector<float>>& kernel) {
    const int32_t radius = static_cast<int32_t>(kernel.size()) / 2;
    const int32_t height = img.Height();
    const int32_t width = img.Width();

    const std::size_t total = 3ULL * width * height;
    std::vector result(total, 0.0f);

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            for (int color = 0; color < 3; ++color) {
                const auto c = static_cast<Color>(color);
                float sum = 0.0f;
                for (int32_t di = -radius; di <= radius; ++di) {
                    for (int32_t dj = -radius; dj <= radius; ++dj) {
                        sum += kernel[di + radius][dj + radius] *
                               static_cast<float>(img.GetPixelClamped(c, i + di, j + dj));
                    }
                }
                result[Image::GetPixelIndex(c, i, j, width, height)] = std::clamp(sum, 0.0f, 1.0f);
            }
        }
    }
    img.SetPixelValues(std::move(result));
}

#endif  // CPP_HSE_FILTERUTILS_H
