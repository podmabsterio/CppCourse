#pragma once

#include "image.h"

#include <string>
#include <fstream>
#include <vector>

class FileRead {
public:
    inline static const uint8_t CHAR_SIZE = 8;
    inline static const size_t BM_ID = 19778;
    inline static const size_t BITS_PER_PIXEL = 24;
    inline static const size_t BYTES_PER_PIXEL = 3;
    inline static const size_t POS_OF_ARRAY_POS = 0xA;
    inline static const size_t SIZE_OF_ARRAY_POS = 0x12;
    inline static const size_t BPP_POS = 0x1C;
    inline static const size_t ALIGNMENT = 4;
    inline static const size_t HEADER_SIZE_IN_BYTES = 54;
    inline static const size_t PART_SIZE = 4;
    inline static const size_t SMALL_PART_SIZE = 2;

    explicit FileRead(const std::string& given_path);

    std::vector<uint8_t> GetHeader();

    Image ReadFile();

private:
    std::string path_;
    std::ifstream fin_;
    std::size_t start_of_array_ = 0;

    size_t ReadPart(size_t size = 1);
    void SkipPart(size_t size);
    void SetPointerTo(size_t pos);

    void GoodIn() const;
};