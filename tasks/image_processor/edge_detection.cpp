#include "edge_detection.h"
#include "grayscale.h"

Image EdgeDetection::Apply(const Image& image) {
    GrayScale gray_scale;
    Image result = gray_scale.Apply(image);
    result = ApplyMatrixFilter(result);
    for (size_t i = 0; i < result.Height(); ++i) {
        for (size_t j = 0; j < result.Width(); ++j) {
            if (result[i][j].Red > threshold_) {
                result[i][j] = default_colors::BLACK;
            } else {
                result[i][j] = default_colors::WHITE;
            }
        }
    }
    return result;
}

const MatrixFilter::Matrix& EdgeDetection::GetMatrix() {
    return EDGE_DETECTION_MATRIX;
}

EdgeDetection::EdgeDetection(double threshold) {
    threshold_ = static_cast<int16_t>(threshold * static_cast<double>(UINT8_MAX));
}
