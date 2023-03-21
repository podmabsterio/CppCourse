#include "matrix_filter.h"
#include <type_traits>

namespace {
const int64_t COLOR_MAX = 255;

size_t Normalize(size_t pos, MatrixFilter::SignedSizeT dif, size_t boarder) {
    if (dif < 0 && pos < static_cast<size_t>(-dif)) {
        return 0;
    }
    return std::min(boarder - 1, pos + dif);
}

int16_t GetInBoarder(int64_t value) {
    return static_cast<int16_t>(std::max(static_cast<int64_t>(0), std::min(COLOR_MAX, value)));
}
}  // namespace

Color<int16_t> MatrixFilter::MatrixValue(const Image& image, size_t pos_h, size_t pos_w) {
    SignedSizeT balance = static_cast<SignedSizeT>(GetMatrix().size() / 2);
    Color<int64_t> result;
    for (SignedSizeT i = -balance; i <= balance; ++i) {
        for (SignedSizeT j = -balance; j <= balance; ++j) {
            const auto& current_pixel = image[Normalize(pos_h, i, image.Height())][Normalize(pos_w, j, image.Width())];
            result.Red += current_pixel.Red * GetMatrix()[i + balance][j + balance];
            result.Green += current_pixel.Green * GetMatrix()[i + balance][j + balance];
            result.Blue += current_pixel.Blue * GetMatrix()[i + balance][j + balance];
        }
    }
    return {GetInBoarder(result.Red), GetInBoarder(result.Green), GetInBoarder(result.Blue)};
}

Image MatrixFilter::ApplyMatrixFilter(const Image& image) {
    Image result(image.Height(), image.Width());
    for (size_t i = 0; i < result.Height(); ++i) {
        for (size_t j = 0; j < result.Width(); ++j) {
            result[i][j] = MatrixValue(image, i, j);
        }
    }
    return result;
}
