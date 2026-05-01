#ifndef CPP_HSE_GRAYSCALEFILTER_H
#define CPP_HSE_GRAYSCALEFILTER_H
#include "Filter.h"

class GrayscaleFilter final : public Filter {
public:
    static constexpr float R = 0.299f;
    static constexpr float G = 0.587f;
    static constexpr float B = 0.114f;

    void Apply(Image& img) override;
};

#endif  // CPP_HSE_GRAYSCALEFILTER_H
