cmake_minimum_required(VERSION 3.10)
project(ImageProcessor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
        image_processor
        image_processor.cpp
        ArgsParser.cpp
        ArgsParser.h
        FilterRegistry.cpp
        FilterRegistry.h
        Utils.h
        FilterUtils.h
        filters/BlurFilter.cpp
        filters/BlurFilter.h
        filters/Filter.h
        filters/GrayscaleFilter.cpp
        filters/GrayscaleFilter.h
        filters/NegativeFilter.cpp
        filters/NegativeFilter.h
        filters/CropFilter.cpp
        filters/CropFilter.h
        filters/SharpFilter.cpp
        filters/SharpFilter.h
        filters/EdgeFilter.cpp
        filters/EdgeFilter.h
        filters/SunFadeFilter.cpp
        filters/SunFadeFilter.h

        io/Reader.h
        io/Writer.h
        io/BMPReader.h
        io/BMPReader.cpp
        io/BMPWriter.h
        io/BMPWriter.cpp
        io/ImageFormatFactory.h
        io/ImageFormatFactory.cpp

        images/Image.cpp
        abacaba.cpp
        abacaba.h
)

target_compile_options(image_processor PRIVATE -O3)
target_link_options(image_processor PRIVATE -flto=thin)
