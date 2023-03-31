#include "sharpening.h"
Image Sharpening::Apply(const Image& image) {
    return ApplyMatrixFilter(image);
}

const MatrixFilter::Matrix& Sharpening::GetMatrix() {
    return SHARPENING_MATRIX;
}
