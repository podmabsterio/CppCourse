#include "overflow_topology.h"

std::vector<Point> OverflowTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> result;
    for (int8_t i = -1; i < 2; i += 2) {
        Point possible_neighbor1{.x =((point.x + map_.SizeX()) + i) % map_.SizeX(), .y = point.y};
        Point possible_neighbor2{.x = point.x, .y =((point.y + map_.SizeY()) + i) % map_.SizeY()};
        if (!map_.IsObstacle(possible_neighbor1)) {
            result.push_back(possible_neighbor1);
        }
        if (!map_.IsObstacle(possible_neighbor2)) {
            result.push_back(possible_neighbor2);
        }
    }
    return result;
}
OverflowTopology::OverflowTopology(TrapsField given_field) : Topology(given_field) {
}
