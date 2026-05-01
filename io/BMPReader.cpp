#include "BMPReader.h"

#include "../Utils.h"
#include "../help.h"
#include "../images/Image.h"

#include <fstream>
#include <format>
#include <stdexcept>

BasicBMPHeader BMPReader::ReadBMPHeader(std::ifstream& f) {
    BasicBMPHeader header;
    f.read(reinterpret_cast<char*>(&header), sizeof(BasicBMPHeader));
    if (!f) {
        throw std::runtime_error(std::vformat(ErrorFileOpen, std::make_format_args("Failed to read BMP header")));
    }
    if (header.ID != BmpId) {
        throw std::runtime_error(std::vformat(ErrorFileFormat, std::make_format_args("wrong magic number")));
    }
    return header;
}

BasicDIBHeader BMPReader::ReadDIBHeader(std::ifstream& f) {
    f.seekg(BMPHeaderSize);

    BasicDIBHeader header;
    f.read(reinterpret_cast<char*>(&header), sizeof(BasicDIBHeader));
    if (!f) {
        throw std::runtime_error(std::vformat(ErrorFileOpen, std::make_format_args("Failed to read DIB header")));
    }

    if (header.HeaderBytesCount != DIBHeaderByteSize) {
        throw std::runtime_error(ErrorUnsupportedBmpHeader.data());
    }
    if (header.ColorPlanesCount != 1) {
        throw std::runtime_error(ErrorBmpColorPlanes.data());
    }
    if (header.BitsPerPixel != ExpectedBitsPerPixel) {
        throw std::runtime_error(ErrorBmpBitsPerPixel.data());
    }
    if (header.BiRGB != 0) {
        throw std::runtime_error(ErrorBmpCompressed.data());
    }
    if (header.PaletteColorsCount != 0) {
        throw std::runtime_error(ErrorBmpPalette.data());
    }
    if (header.BitmapHeight == 0) {
        throw std::runtime_error(ErrorBmpZeroHeight.data());
    }

    return header;
}

Image BMPReader::Read(std::string_view path) const {
    std::ifstream f(path.data(), std::ios::binary);
    if (!f) {
        throw std::runtime_error("бро ты бездарь и тд");
    }

    if (!f.is_open()) {
        throw std::runtime_error(std::vformat(ErrorFileOpen, std::make_format_args(path)));
    }

    BasicBMPHeader bmp_header = ReadBMPHeader(f);
    BasicDIBHeader dib_header = ReadDIBHeader(f);

    const int32_t width = dib_header.BitmapWidth;
    const int32_t height = dib_header.BitmapHeight;
    const int32_t abs_height = std::abs(height);

    Image img(width, abs_height);

    f.seekg(bmp_header.Offset);

    const uint32_t row_size = RoundUpToMultipleOfFour(3 * static_cast<uint32_t>(width));
    const uint32_t padding = row_size - 3 * static_cast<uint32_t>(width);

    if (height > 0) {
        for (int32_t i = height - 1; i >= 0; --i) {
            for (int32_t j = 0; j < width; ++j) {
                uint8_t bgr[3];
                f.read(reinterpret_cast<char*>(bgr), 3);
                img.SetPixel(Color::Blue, i, j, static_cast<float>(bgr[0]) / MaxPixelValue);
                img.SetPixel(Color::Green, i, j, static_cast<float>(bgr[1]) / MaxPixelValue);
                img.SetPixel(Color::Red, i, j, static_cast<float>(bgr[2]) / MaxPixelValue);
            }
            f.seekg(padding, std::ios::cur);
        }
    } else {
        for (int32_t i = 0; i < abs_height; ++i) {
            for (int32_t j = 0; j < width; ++j) {
                uint8_t bgr[3];
                f.read(reinterpret_cast<char*>(bgr), 3);
                img.SetPixel(Color::Blue, i, j, static_cast<float>(bgr[0]) / MaxPixelValue);
                img.SetPixel(Color::Green, i, j, static_cast<float>(bgr[1]) / MaxPixelValue);
                img.SetPixel(Color::Red, i, j, static_cast<float>(bgr[2]) / MaxPixelValue);
            }
            f.seekg(padding, std::ios::cur);
        }
    }

    if (!f) {
        throw std::runtime_error(ErrorUnexpectedEof.data());
    }

    return img;
}
