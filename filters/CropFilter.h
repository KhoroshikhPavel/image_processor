#ifndef CPP_HSE_CROPFILTER_H
#define CPP_HSE_CROPFILTER_H
#include "Filter.h"

class CropFilter final : public Filter {
    int32_t width_;
    int32_t height_;

public:
    CropFilter(int32_t width, int32_t height) : width_(width), height_(height) {
    }

    void Apply(Image& img) override;
};

#endif  // CPP_HSE_CROPFILTER_H
