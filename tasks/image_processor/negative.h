#pragma once

#include "basic_filter.h"

class Negative : public Filter {
public:
    Image Apply(const Image& image) override;

private:
    inline static const int32_t COLOR_MAX = 255;
};
