#ifndef CPP_HSE_WRITER_H
#define CPP_HSE_WRITER_H

#include "../images/Image.h"

#include <string_view>

class Writer {
public:
    virtual ~Writer() = default;
    virtual void Write(std::string_view path, const Image& img) const = 0;
};

#endif  // CPP_HSE_WRITER_H
