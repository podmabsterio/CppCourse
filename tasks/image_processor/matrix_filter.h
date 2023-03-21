#pragma once

#include "basic_filter.h"

class MatrixFilter : public Filter {
public:
    using SignedSizeT = std::make_signed<std::size_t>;

    using Matrix = std::vector<std::vector<int64_t> >;

    Image ApplyMatrixFilter(const Image& image);

    virtual const Matrix& GetMatrix() = 0;

private:
    Color<int16_t> MatrixValue(const Image& image, size_t pos_h, size_t pos_w);
};
