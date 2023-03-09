#pragma once

#include "topology.h"

class KnightTopology : public Topology {
public:
    std::vector<Point> GetNeighbours(const Point &point) const override;

    explicit KnightTopology(TrapsField);

    ~KnightTopology() override = default;
};
