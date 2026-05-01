#include "BlurFilter.h"

#include <algorithm>
#include <cmath>
#include <vector>

void BlurFilter::Apply(Image& img) {
    const int32_t height = img.Height();
    const int32_t width = img.Width();

    const int32_t half = std::max(static_cast<int32_t>(std::ceil(3.0 * sigma_)), 1);

    std::vector<float> kernel(static_cast<size_t>(2 * half + 1));
    float sum = 0.0f;
    for (int32_t k = -half; k <= half; ++k) {
        const float w = std::exp(-static_cast<float>(k) * static_cast<float>(k) /
                                 (2.0f * static_cast<float>(sigma_) * static_cast<float>(sigma_)));
        kernel[static_cast<size_t>(k + half)] = w;
        sum += w;
    }
    for (auto& w : kernel) {
        w /= sum;
    }
    
    const std::size_t total = 3ULL * width * height;

    std::vector<float> temp_pixels(total, 0.0f);
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            for (int color = 0; color < 3; ++color) {
                const auto c = static_cast<Color>(color);
                float val = 0.0f;
                for (int32_t k = -half; k <= half; ++k) {
                    val += kernel[static_cast<size_t>(k + half)] * static_cast<float>(img.GetPixelClamped(c, i, j + k));
                }
                temp_pixels[Image::GetPixelIndex(c, i, j, width, height)] = val;
            }
        }
    }

    Image temp_img(width, height);
    temp_img.SetPixelValues(std::move(temp_pixels));

    std::vector<float> out_pixels(total, 0.0f);
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            for (int color = 0; color < 3; ++color) {
                const auto c = static_cast<Color>(color);
                float val = 0.0f;
                for (int32_t k = -half; k <= half; ++k) {
                    val += kernel[static_cast<size_t>(k + half)] *
                           static_cast<float>(temp_img.GetPixelClamped(c, i + k, j));
                }
                out_pixels[Image::GetPixelIndex(c, i, j, width, height)] = std::clamp(val, 0.0f, 1.0f);
            }
        }
    }

    img.SetPixelValues(std::move(out_pixels));
}
