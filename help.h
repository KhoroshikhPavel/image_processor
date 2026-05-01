#pragma once

#include <string_view>

constexpr std::string_view HelpMessage =
    R"(Usage: ./image_processor {input_path.bmp} {output_path.bmp} [-{filter1_name} [filter1_param1] [filter1_param2] ...] [-{filter2_name} [filter2_param1] [filter2_param2] ...] ...
Apply filters to your BMP image.
Example: ./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5

Filters:
    -crop {width} {height}
        Crop to the given size from the top-left corner. width and height are positive integers.
        If the requested size exceeds the image dimensions, the available portion is returned.

    -gs
        Convert the image to grayscale.

    -neg
        Invert all colors.

    -sharp
        Sharpen the image using a 3x3 convolution kernel.
        Increases local contrast; strong edges become more pronounced.

    -edge {threshold}
        Detect edges. The image is first converted to grayscale, then a convolution kernel
        highlights intensity changes between neighboring pixels. Pixels whose resulting
        intensity exceeds threshold are set to white; the rest to black.
        threshold is in [0, 1]. Higher threshold = fewer, only the strongest edges are shown.

    -blur {sigma}
        Apply Gaussian blur. sigma controls the spread of the blur kernel (must be > 0).
        Larger sigma = more blurring.

    -sunfade {desaturation} {bleach}
        Simulate sun-faded colors. desaturation in [0, 1] controls how much colors shift
        towards gray (0 = no change, 1 = fully grayscale). bleach in [0, 1] controls how
        much colors shift toward white (0 = no change, 1 = fully white). Blue fades fastest,
        red slowest, simulating real pigment degradation.)";

constexpr std::string_view ErrorFileOpen = "Could not open file: {}";
constexpr std::string_view ErrorFileWrite = "Could not open file for writing: {}";
constexpr std::string_view ErrorFileFormat = "Unsupported file format: {}";
constexpr std::string_view ErrorUnsupportedBmpHeader = "Unsupported BMP header type (only BITMAPINFOHEADER supported)";
constexpr std::string_view ErrorBmpColorPlanes = "Invalid color plane count in BMP";
constexpr std::string_view ErrorBmpBitsPerPixel = "Unsupported bits per pixel (only 24-bit BMP supported)";
constexpr std::string_view ErrorBmpCompressed = "Compressed BMP files are not supported";
constexpr std::string_view ErrorBmpPalette = "BMP files with palette are not supported";
constexpr std::string_view ErrorBmpZeroHeight = "BMP has zero height";
constexpr std::string_view ErrorUnexpectedEof = "Unexpected end of file while reading pixel data";
constexpr std::string_view ErrorNotEnoughArgs = "Not enough arguments. Run with no arguments to see help.";
constexpr std::string_view ErrorShowHelp = "Run with no arguments to see help.";
constexpr std::string_view ErrorUnknownFilter = "Unknown filter: {}";
constexpr std::string_view ErrorCropArgs = "-crop requires 2 arguments (width height), but got {}: {}";
constexpr std::string_view ErrorCropDimensions = "-crop requires positive dimensions, got width={}, height={}";
constexpr std::string_view ErrorEdgeArg = "-edge requires 1 argument (threshold), but got {}: {}";
constexpr std::string_view ErrorEdgeThreshold = "-edge threshold must be in [0, 1], got {}";
constexpr std::string_view ErrorBlurArg = "-blur requires 1 argument (sigma), but got {}: {}";
constexpr std::string_view ErrorBlurSigma = "-blur sigma must be > 0, got {}";
constexpr std::string_view ErrorSunfadeArgs = "-sunfade requires 2 arguments (desaturation bleach), but got {}: {}";
constexpr std::string_view ErrorSunfadeParams = "-sunfade parameters must be in [0, 1], got desaturation={}, bleach={}";
constexpr std::string_view ErrorNoExtension = "File has no extension: {}";
constexpr std::string_view ErrorUnsupportedFormat = "Unsupported image format: {}";
constexpr std::string_view ErrorWrongImageDimensions = "Image dimensions must be positive";
constexpr std::string_view ErrorSizeMismatch = "Pixel values size mismatch";