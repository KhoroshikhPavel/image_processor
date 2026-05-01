#include "EdgeFilter.h"

#include "../FilterUtils.h"
#include "GrayscaleFilter.h"

void EdgeFilter::Apply(Image& img) {
    GrayscaleFilter{}.Apply(img);

    const std::vector<std::vector<float>> kernel = {
        {0.0f, -1.0f, 0.0f},
        {-1.0f, 4.0f, -1.0f},
        {0.0f, -1.0f, 0.0f},
    };

    ApplyKernel(img, kernel);

    const int32_t height = img.Height();
    const int32_t width = img.Width();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            const float value = img.GetPixel(Color::Red, i, j) > threshold_ ? 1.0f : 0.0f;
            img.SetPixel(Color::Red, i, j, value);
            img.SetPixel(Color::Green, i, j, value);
            img.SetPixel(Color::Blue, i, j, value);
        }
    }
}
