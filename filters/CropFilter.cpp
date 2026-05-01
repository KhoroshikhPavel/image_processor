#include "CropFilter.h"

#include <algorithm>
#include <vector>

void CropFilter::Apply(Image& img) {
    const int32_t new_width = std::min(width_, img.Width());
    const int32_t new_height = std::min(height_, img.Height());

    const std::size_t total = 3ULL * new_width * new_height;
    std::vector<float> cropped(total, 0.0f);

    for (int32_t i = 0; i < new_height; ++i) {
        for (int32_t j = 0; j < new_width; ++j) {
            cropped[Image::GetPixelIndex(Color::Blue, i, j, new_width, new_height)] =
                static_cast<float>(img.GetPixel(Color::Blue, i, j));
            cropped[Image::GetPixelIndex(Color::Green, i, j, new_width, new_height)] =
                static_cast<float>(img.GetPixel(Color::Green, i, j));
            cropped[Image::GetPixelIndex(Color::Red, i, j, new_width, new_height)] =
                static_cast<float>(img.GetPixel(Color::Red, i, j));
        }
    }

    Image new_img(new_width, new_height);
    new_img.SetPixelValues(cropped);
    img = std::move(new_img);
}
