#include "planar_topology.h"

std::vector<Point> PlanarTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> neighbours;
    if (point.x > 0 && !map_.IsObstacle({point.x - 1, point.y})) {
        neighbours.push_back({.x = point.x - 1, .y = point.y});
    }
    if (point.y > 0 && !map_.IsObstacle({point.x, point.y - 1})) {
        neighbours.push_back({.x = point.x, .y = point.y - 1});
    }
    if (!map_.IsObstacle({point.x + 1, point.y})) {
        neighbours.push_back({.x = point.x + 1, .y = point.y});
    }
    if (!map_.IsObstacle({point.x, point.y + 1})) {
        neighbours.push_back({.x = point.x, .y = point.y + 1});
    }
    return neighbours;
}

PlanarTopology::PlanarTopology(TrapsField given_field) : Topology(given_field) {
}
