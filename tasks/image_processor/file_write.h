#pragma once

#include "image.h"

#include <string>
#include <vector>
#include <fstream>

class FileWrite {
public:
    inline static const size_t CHAR_SIZE = 256;
    inline static const size_t ALIGNMENT = 4;
    inline static const size_t SIZE_OF_FILE_POS = 0x2;
    inline static const size_t SIZE_OF_ARRAY_POS = 0x12;
    inline static const size_t HEADER_SIZE = 54;
    inline static const size_t RAW_BITMAP_SIZE_POS = 0x22;
    inline static const size_t BYTES_PER_PIXEL = 3;

    explicit FileWrite(const Image& image, std::vector<uint8_t> header);

    void WriteFile(const std::string& given_path);

    size_t CalculateArraySize();
    void RefillHeader(size_t start, size_t size, size_t value);

private:
    std::string path_;
    std::ofstream file_out_;
    const Image* image_;
    std::vector<uint8_t> header_;
};
