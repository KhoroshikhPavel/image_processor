#include "SharpFilter.h"

#include "../FilterUtils.h"

void SharpFilter::Apply(Image& img) {
    const std::vector<std::vector<float>> kernel = {
        {0.0f, -1.0f, 0.0f},
        {-1.0f, 5.0f, -1.0f},
        {0.0f, -1.0f, 0.0f},
    };

    ApplyKernel(img, kernel);
}
