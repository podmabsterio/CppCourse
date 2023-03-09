#pragma once

#include "topology.h"

class CheckersTopology : public Topology {
public:
    std::vector<Point> GetNeighbours(const Point &point) const override;

    explicit CheckersTopology(TrapsField);

    ~CheckersTopology() override = default;
};
