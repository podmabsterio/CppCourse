#pragma once

#include "point.h"

#include <vector>

using TrapsField = std::vector<std::vector<bool>>;

class Topology {
public:
    using Distance = ssize_t;
    using DistanceMap = std::vector<std::vector<Distance>>;

    virtual std::vector<Point> GetNeighbours(const Point& point) const = 0;
    Distance MeasureDistance(const Point& from, const Point& to) const;

    static const Distance UNREACHABLE = -1;

    Topology() = delete;
    explicit Topology(TrapsField);
    virtual ~Topology() = default;

protected:
    class Field {
    public:
        TrapsField field_;

        Field() = delete;
        explicit Field(TrapsField);

        bool IsObstacle(const Point&) const;
        bool IsInBound(Point point, int8_t dif_x, int8_t dif_y) const;
        size_t SizeY() const;
        size_t SizeX() const;
    };

    Field map_;
};
