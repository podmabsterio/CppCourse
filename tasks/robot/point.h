#pragma once

#include <cstddef>
#include <utility>

static const size_t HASH_SEPARATOR = 1000000007;

struct Point {
    size_t x = 0;
    size_t y = 0;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
template<>
struct hash<Point> {
    size_t operator()(const Point& point) const {
        return point.x + point.y * HASH_SEPARATOR;
    }
};
}  // namespace std
