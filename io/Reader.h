#ifndef CPP_HSE_READER_H
#define CPP_HSE_READER_H

#include "../images/Image.h"

#include <memory>
#include <string_view>

class Reader {
public:
    virtual ~Reader() = default;
    virtual Image Read(std::string_view path) const = 0;
};

#endif  // CPP_HSE_READER_H
