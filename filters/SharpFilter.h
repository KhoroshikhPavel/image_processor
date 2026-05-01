#ifndef CPP_HSE_SHARPFILTER_H
#define CPP_HSE_SHARPFILTER_H
#include "Filter.h"

class SharpFilter final : public Filter {
public:
    void Apply(Image& img) override;
};

#endif  // CPP_HSE_SHARPFILTER_H
