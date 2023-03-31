#include "file_read.h"
#include "image_processor_exception.h"

#include <fstream>

namespace {
size_t PaddingSize(size_t pixel_count) {
    return (FileRead::ALIGNMENT - (pixel_count % FileRead::ALIGNMENT)) % FileRead::ALIGNMENT;
}
}  // namespace

Image FileRead::ReadFile() {
    fin_.open(path_, std::ios::binary);
    if (!fin_.is_open()) {
        throw ImageProcessorException("Path is incorrect");
    }
    if (ReadPart(SMALL_PART_SIZE) != BM_ID) {
        throw ImageProcessorException("Wrong file format");
    }

    SetPointerTo(POS_OF_ARRAY_POS);
    start_of_array_ = ReadPart(PART_SIZE);
    SetPointerTo(SIZE_OF_ARRAY_POS);
    size_t width = ReadPart(PART_SIZE);
    size_t height = ReadPart(PART_SIZE);
    SetPointerTo(BPP_POS);
    if (ReadPart(SMALL_PART_SIZE) != BITS_PER_PIXEL) {
        throw ImageProcessorException("Wrong bits per pixel value");
    }

    Image result(height, width);
    SetPointerTo(start_of_array_);

    for (size_t i = 0; i < height; ++i) {
        size_t pixel_in_row = 0;
        for (size_t j = 0; j < width; ++j) {
            result[i][j].Blue = static_cast<int16_t>(ReadPart());
            result[i][j].Green = static_cast<int16_t>(ReadPart());
            result[i][j].Red = static_cast<int16_t>(ReadPart());
            pixel_in_row += BYTES_PER_PIXEL;
        }
        SkipPart(PaddingSize(pixel_in_row));
    }
    fin_.close();
    return result;
}

FileRead::FileRead(const std::string& given_path) : path_(given_path) {
}

size_t FileRead::ReadPart(size_t size) {
    size_t result = 0;
    for (size_t i = 0; i < size && fin_; ++i) {
        result += static_cast<uint8_t>(fin_.get()) * (static_cast<size_t>(1) << (i * CHAR_SIZE));
    }
    GoodIn();
    return result;
}

void FileRead::SkipPart(size_t size) {
    ReadPart(size);
}

void FileRead::SetPointerTo(size_t pos) {
    fin_.seekg(std::ios::beg + static_cast<std::streamoff>(pos));
    GoodIn();
};

void FileRead::GoodIn() const {
    if (!fin_) {
        throw std::exception();
    }
}

std::vector<uint8_t> FileRead::GetHeader() {
    std::vector<uint8_t> header;
    fin_.open(path_, std::ios::binary);
    for (size_t i = 0; i < HEADER_SIZE_IN_BYTES; ++i) {
        header.push_back(ReadPart());
    }
    fin_.close();
    return header;
}
