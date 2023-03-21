#pragma once

#include "color.h"
#include <vector>

class Image {
public:
    using ColorLine = std::vector<Color<int16_t> >;
    using Map = std::vector<ColorLine>;

    Image(const size_t height, const size_t width);

    size_t Height() const;
    size_t Width() const;

    ColorLine& operator[](size_t index);
    const ColorLine& operator[](size_t index) const;

    void ConsoleRepr();
private:
    Map field_;
    size_t height_ = 0;
    size_t width_ = 0;
};