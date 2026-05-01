#ifndef CPP_HSE_BLURFILTER_H
#define CPP_HSE_BLURFILTER_H
#include "Filter.h"

class BlurFilter final : public Filter {
    double sigma_;

public:
    explicit BlurFilter(double sigma) : sigma_(sigma) {
    }

    void Apply(Image& img) override;
};

#endif  // CPP_HSE_BLURFILTER_H
