#include "GrayscaleFilter.h"

void GrayscaleFilter::Apply(Image& img) {
    const int32_t width = img.Width();
    const int32_t height = img.Height();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            const float old_blue = static_cast<float>(img.GetPixel(Color::Blue, i, j));
            const float old_green = static_cast<float>(img.GetPixel(Color::Green, i, j));
            const float old_red = static_cast<float>(img.GetPixel(Color::Red, i, j));

            const float gray = static_cast<float>(GrayscaleFilter::R * old_red + GrayscaleFilter::G * old_green +
                                                  GrayscaleFilter::B * old_blue);

            img.SetPixel(Color::Blue, i, j, gray);
            img.SetPixel(Color::Green, i, j, gray);
            img.SetPixel(Color::Red, i, j, gray);
        }
    }
}
