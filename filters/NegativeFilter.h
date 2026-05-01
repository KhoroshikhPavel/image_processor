#ifndef CPP_HSE_NEGATIVEFILTER_H
#define CPP_HSE_NEGATIVEFILTER_H
#include "Filter.h"

class NegativeFilter final : public Filter {
public:
    void Apply(Image& img) override;
};

#endif  // CPP_HSE_NEGATIVEFILTER_H
