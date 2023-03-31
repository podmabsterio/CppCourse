#pragma once

#include "basic_filter.h"

class Crop : public Filter {
public:
    Image Apply(const Image& image) override;

    Crop(size_t width, size_t height);

private:
    size_t width_;
    size_t height_;
};
