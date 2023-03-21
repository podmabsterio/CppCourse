#pragma once

#include "basic_filter.h"

class Negative : public Filter {
public:
    Image Apply(const Image& image) override;

private:
    inline static const int16_t COLOR_MAX = static_cast<int16_t>(255);
};
