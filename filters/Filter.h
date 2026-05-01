#ifndef CPP_HSE_FILTER_H
#define CPP_HSE_FILTER_H
#include "../images/Image.h"

class Filter {
public:
    virtual void Apply(Image& img) = 0;
    virtual ~Filter() = default;
};

#endif  // CPP_HSE_FILTER_H
