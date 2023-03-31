#pragma once

#include "matrix_filter.h"

class Sharpening : public MatrixFilter {
public:
    Image Apply(const Image& image) override;

    const Matrix& GetMatrix() override;

private:
    inline static const Matrix SHARPENING_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};
