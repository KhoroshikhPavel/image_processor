#include "NegativeFilter.h"

void NegativeFilter::Apply(Image& img) {
    const int32_t height = img.Height();
    const int32_t width = img.Width();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            img.SetPixel(Color::Red, i, j, 1.0f - static_cast<float>(img.GetPixel(Color::Red, i, j)));
            img.SetPixel(Color::Green, i, j, 1.0f - static_cast<float>(img.GetPixel(Color::Green, i, j)));
            img.SetPixel(Color::Blue, i, j, 1.0f - static_cast<float>(img.GetPixel(Color::Blue, i, j)));
        }
    }
}
