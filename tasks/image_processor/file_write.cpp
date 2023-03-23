#include "file_write.h"
#include <iostream>

namespace {
std::vector<uint8_t> NumToBytes(size_t value, size_t bytes_quantity) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < bytes_quantity; ++i) {
        result.push_back(static_cast<uint8_t>(value % FileWrite::CHAR_SIZE));
        value /= FileWrite::CHAR_SIZE;
    }
    return result;
}

size_t LineWithPadding(size_t line_size) {
    return line_size + (FileWrite::ALIGNMENT - line_size % FileWrite::ALIGNMENT) % FileWrite::ALIGNMENT;
}
}  // namespace

FileWrite::FileWrite(const Image& image, std::vector<uint8_t> header) : image_(&image), header_(std::move(header)) {
}

size_t FileWrite::CalculateArraySize() {
    return image_->Height() * LineWithPadding(image_->Width());
}

void FileWrite::RefillHeader(size_t start, size_t size, size_t value) {
    auto new_value = NumToBytes(value, size);
    for (size_t i = 0; i < size; ++i) {
        header_[start + i] = new_value[i];
    }
}

void FileWrite::WriteFile(const std::string& given_path) {
    file_out_.open(given_path, std::ios::binary);
    RefillHeader(SIZE_OF_FILE_POS, 4, HEADER_SIZE + BYTES_PER_PIXEL * CalculateArraySize());
    RefillHeader(SIZE_OF_ARRAY_POS, 4, image_->Width());
    RefillHeader(SIZE_OF_ARRAY_POS + 4, 4, image_->Height());
    RefillHeader(RAW_BITMAP_SIZE_POS, 4, CalculateArraySize());

    for (size_t i = 0; i < header_.size(); ++i) {
        file_out_.put(static_cast<char>(header_[i]));
    }

    for (size_t i = 0; i < image_->Height(); ++i) {
        size_t bytes_count = 0;
        for (size_t j = 0; j < image_->Width(); ++j) {
            auto current_pixel = image_->operator[](i)[j];
            file_out_.put(static_cast<char>(current_pixel.Blue));
            file_out_.put(static_cast<char>(current_pixel.Green));
            file_out_.put(static_cast<char>(current_pixel.Red));
            bytes_count += BYTES_PER_PIXEL;
        }

        while (bytes_count % ALIGNMENT != 0) {
            file_out_.put(0);
            ++bytes_count;
        }
    }
    file_out_.close();
}
