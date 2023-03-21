#include "image.h"
#include <iostream>

Image::Image(const size_t height, const size_t width)
    : field_(height, ColorLine(width)), height_(height), width_(width) {
}

Image::ColorLine& Image::operator[](size_t index) {
    return field_[index];
}

const Image::ColorLine& Image::operator[](size_t index) const {
    return field_[index];
}

size_t Image::Height() const {
    return height_;
}

size_t Image::Width() const {
    return width_;
}

void Image::ConsoleRepr() {
    for (const auto& line : field_) {
        for (const auto& pixel : line) {
            std::cout << "[" << pixel.Red << ", " << pixel.Green << ", " << pixel.Blue << "]  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}