#ifndef CPP_HSE_BMPTYPES_H
#define CPP_HSE_BMPTYPES_H

#include <cstdint>

#pragma pack(push, 1)
struct BasicBMPHeader {
    uint16_t ID;
    uint32_t FileSize;
    uint16_t Reserved1;
    uint16_t Reserved2;
    uint32_t Offset;
};

struct BasicDIBHeader {
    uint32_t HeaderBytesCount;
    int32_t BitmapWidth;
    int32_t BitmapHeight;
    uint16_t ColorPlanesCount;
    uint16_t BitsPerPixel;
    uint32_t BiRGB;
    uint32_t RawBitmapDataSize;
    uint32_t PrintResolution1;
    uint32_t PrintResolution2;
    uint32_t PaletteColorsCount;
    uint32_t ImportantColorsCount;
};
#pragma pack(pop)

constexpr uint16_t BmpId = 0x4D42;
constexpr uint32_t DIBHeaderByteSize = 40;
constexpr uint16_t ExpectedBitsPerPixel = 24;
constexpr int BMPHeaderSize = 14;

#endif
