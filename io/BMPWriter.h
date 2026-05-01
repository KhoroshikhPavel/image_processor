#ifndef CPP_HSE_BMPWRITER_H
#define CPP_HSE_BMPWRITER_H

#include "Writer.h"

#include <string_view>

class BMPWriter : public Writer {
public:
    void Write(std::string_view path, const Image& img) const override;
};

#endif  // CPP_HSE_BMPWRITER_H
