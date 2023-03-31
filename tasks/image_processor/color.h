#pragma once

#include <cstdint>

template <typename T>
struct Color {
    T Red = 0;
    T Green = 0;
    T Blue = 0;
};

namespace default_colors {
const Color<int16_t> WHITE = {0, 0, 0};
const Color<int16_t> BLACK = {255, 255, 255};
}  // namespace default_colors