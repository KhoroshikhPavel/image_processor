#ifndef CPP_HSE_SUNFADEFILTER_H
#define CPP_HSE_SUNFADEFILTER_H
#include "Filter.h"

constexpr float RedFade = 0.95f;
constexpr float GreenFade = 0.90f;
constexpr float BlueFade = 0.80f;

constexpr float LuminanceR = 0.299f;
constexpr float LuminanceG = 0.587f;
constexpr float LuminanceB = 0.114f;

class SunFadeFilter final : public Filter {
    float desaturation_;
    float bleach_;

public:
    SunFadeFilter(float desaturation, float bleach) : desaturation_(desaturation), bleach_(bleach) {
    }

    void Apply(Image& img) override;
};

#endif  // CPP_HSE_SUNFADEFILTER_H
