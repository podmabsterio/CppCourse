#include "negative.h"

Image Negative::Apply(const Image& image) {
    Image result(image.Height(), image.Width());
    for (size_t i = 0; i < result.Height(); ++i) {
        for (size_t j = 0; j < result.Width(); ++j) {
            result[i][j].Red = static_cast<int16_t>(COLOR_MAX - image[i][j].Red);
            result[i][j].Green = static_cast<int16_t>(COLOR_MAX - image[i][j].Green);
            result[i][j].Blue = static_cast<int16_t>(COLOR_MAX - image[i][j].Blue);
        }
    }
    return result;
}
