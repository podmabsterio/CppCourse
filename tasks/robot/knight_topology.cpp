#include "knight_topology.h"

namespace {
const int KNIGHT_MOVE2 = 2;
const int KNIGHT_MOVE1 = 1;
}  // namespace

KnightTopology::KnightTopology(TrapsField given_field) : Topology(given_field) {
}

std::vector<Point> KnightTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> result;
    for (int8_t i = -1; i < 2; i += 2) {
        for (int8_t j = -1; j < 2; j += 2) {
            if (map_.IsInBound(point, i * KNIGHT_MOVE2, j * KNIGHT_MOVE1)) {
                result.push_back({point.x + i * KNIGHT_MOVE2, point.y + j * KNIGHT_MOVE1});
            }
        }
    }
    for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
            if (map_.IsInBound(point, i * KNIGHT_MOVE1, j * KNIGHT_MOVE2)) {
                result.push_back({point.x + i * KNIGHT_MOVE1, point.y + j * KNIGHT_MOVE2});
            }
        }
    }
    return result;
}
