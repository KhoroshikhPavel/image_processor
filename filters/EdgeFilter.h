#ifndef CPP_HSE_EDGEFILTER_H
#define CPP_HSE_EDGEFILTER_H
#include "Filter.h"

class EdgeFilter final : public Filter {
    double threshold_;

public:
    explicit EdgeFilter(double threshold) : threshold_(threshold) {
    }

    void Apply(Image& img) override;
};

#endif  // CPP_HSE_EDGEFILTER_H
