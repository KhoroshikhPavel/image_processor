#ifndef CPP_HSE_IMAGEFORMATFACTORY_H
#define CPP_HSE_IMAGEFORMATFACTORY_H

#include "Reader.h"
#include "Writer.h"

#include <memory>
#include <string_view>

std::unique_ptr<Reader> CreateReader(std::string_view path);
std::unique_ptr<Writer> CreateWriter(std::string_view path);

#endif  // CPP_HSE_IMAGEFORMATFACTORY_H
