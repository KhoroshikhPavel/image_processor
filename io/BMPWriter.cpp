#include "BMPWriter.h"

#include "BMPTypes.h"
#include "../Utils.h"
#include "../help.h"
#include "../images/Image.h"

#include <algorithm>
#include <fstream>
#include <format>
#include <stdexcept>

static uint32_t CalculateFileSize(int32_t width, int32_t height) {
    const uint32_t pixel_data_size =
        RoundUpToMultipleOfFour(3 * static_cast<uint32_t>(width)) * static_cast<uint32_t>(height);
    return pixel_data_size + BMPHeaderSize + DIBHeaderByteSize;
}

void BMPWriter::Write(std::string_view path, const Image& img) const {
    std::ofstream out(path.data(), std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error(std::vformat(ErrorFileWrite, std::make_format_args(path)));
    }

    const int32_t width = img.Width();
    const int32_t height = img.Height();

    const uint32_t file_size = CalculateFileSize(width, height);
    constexpr uint32_t PixelDataOffset = BMPHeaderSize + DIBHeaderByteSize;
    const uint32_t pixel_data_size =
        RoundUpToMultipleOfFour(3 * static_cast<uint32_t>(width)) * static_cast<uint32_t>(height);

    BasicBMPHeader bmp_header = {BmpId, file_size, 0, 0, PixelDataOffset};
    out.write(reinterpret_cast<const char*>(&bmp_header), sizeof(BasicBMPHeader));

    BasicDIBHeader dib_header = {
        DIBHeaderByteSize, width, height, 1, ExpectedBitsPerPixel, 0, pixel_data_size, 0, 0, 0, 0,
    };
    out.write(reinterpret_cast<const char*>(&dib_header), sizeof(BasicDIBHeader));

    const uint32_t row_size = RoundUpToMultipleOfFour(3 * static_cast<uint32_t>(width));
    const uint32_t padding = row_size - 3 * static_cast<uint32_t>(width);

    for (int32_t i = height - 1; i >= 0; --i) {
        for (int32_t j = 0; j < width; ++j) {
            const auto clamp_byte = [](float v) {
                return static_cast<uint8_t>(std::clamp(v * MaxPixelValue, 0.0f, MaxPixelValue));
            };

            uint8_t bgr[3] = {
                clamp_byte(static_cast<float>(img.GetPixel(Color::Blue, i, j))),
                clamp_byte(static_cast<float>(img.GetPixel(Color::Green, i, j))),
                clamp_byte(static_cast<float>(img.GetPixel(Color::Red, i, j))),
            };
            out.write(reinterpret_cast<const char*>(bgr), 3);
        }
        out.write("\0\0\0", padding);
    }
}
