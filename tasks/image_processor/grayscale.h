#pragma once

#include "basic_filter.h"

class GrayScale : public Filter {
public:
    Image Apply(const Image& image) override;

private:
    inline static const int64_t RED_COEFFICIENT = 299;
    inline static const int64_t GREEN_COEFFICIENT = 587;
    inline static const int64_t BLUE_COEFFICIENT = 114;
    inline static const int64_t DIVISOR = 1000;
};
