#ifndef CPP_HSE_BMPREADER_H
#define CPP_HSE_BMPREADER_H

#include "BMPTypes.h"
#include "Reader.h"

#include <fstream>
#include <string_view>

class BMPReader final : public Reader {
public:
    Image Read(std::string_view path) const override;

private:
    static BasicBMPHeader ReadBMPHeader(std::ifstream& f);
    static BasicDIBHeader ReadDIBHeader(std::ifstream& f);
};

#endif
