#pragma once

#include "topology.h"

class OverflowTopology : public Topology {
public:
    std::vector<Point> GetNeighbours(const Point &point) const override;

    explicit OverflowTopology(TrapsField);

    ~OverflowTopology() override = default;
};
