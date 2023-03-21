#include "crop.h"
#include <algorithm>

Image Crop::Apply(const Image& image) {
    size_t correct_height = std::min(height_, image.Height());
    size_t correct_width = std::min(width_, image.Width());
    Image result(correct_height, correct_width);
    for (size_t i = image.Height() - correct_height, j = 0; i < image.Height(); ++i, ++j) {
        std::copy(image[i].begin(), image[i].begin() + static_cast<ssize_t>(correct_width), result[j].begin());
    }
    return result;
}

Crop::Crop(size_t width, size_t height) : Filter(), width_(width), height_(height) {
}
