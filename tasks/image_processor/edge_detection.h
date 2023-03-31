#pragma once

#include "matrix_filter.h"

class EdgeDetection : public MatrixFilter {
public:
    explicit EdgeDetection(double threshold);

    Image Apply(const Image& image) override;

    const Matrix& GetMatrix() override;

private:
    inline static const Matrix EDGE_DETECTION_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

    int16_t threshold_;
};
