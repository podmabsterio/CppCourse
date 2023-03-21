#include "grayscale.h"

Image GrayScale::Apply(const Image& image) {
    Image result(image.Height(), image.Width());
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            int16_t gray_scale_color =
                static_cast<int16_t>((static_cast<int64_t>(image[i][j].Green) * GREEN_COEFFICIENT +
                                      static_cast<int64_t>(image[i][j].Red) * RED_COEFFICIENT +
                                      static_cast<int64_t>(image[i][j].Blue) * BLUE_COEFFICIENT) /
                                     DIVISOR);
            result[i][j].Red = result[i][j].Blue = result[i][j].Green = gray_scale_color;
        }
    }
    return result;
}
