#include "checkers_topology.h"
#include <unordered_set>
#include <queue>

std::vector<Point> CheckersTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> result;

    for (int8_t i = -1; i < 2; i += 2) {
        for (int8_t j = -1; j < 2; j += 2) {
            if (!map_.IsInBound(point, i, j)) {
                continue;
            }
            Point neighbor = {.x = point.x + i, .y = point.y + j};
            if (!map_.IsObstacle(neighbor)) {
                result.push_back(neighbor);
            }
        }
    }

    std::unordered_set<Point, HashPoint> processed;
    std::queue<Point> not_processed;
    not_processed.push(point);
    processed.insert(point);
    while (!not_processed.empty()) {
        Point current = not_processed.front();
        not_processed.pop();
        for (int8_t i = -1; i < 2; i += 2) {
            for (int8_t j = -1; j < 2; j += 2) {
                if (!map_.IsInBound(current, i, j)) {
                    continue;
                }
                Point obstacle = {.x = current.x + i, .y = current.y + j};
                if (!map_.IsObstacle(obstacle)) {
                    continue;
                }
                if (!map_.IsInBound(obstacle, i, j)) {
                    continue;
                }
                Point neighbor = {.x = obstacle.x + i, .y = obstacle.y + j};
                if (!map_.IsObstacle(neighbor) && processed.count(neighbor) == 0) {
                    not_processed.push(neighbor);
                    processed.insert(neighbor);
                    result.push_back(neighbor);
                }
            }
        }
    }
    return result;
}

CheckersTopology::CheckersTopology(TrapsField given_field) : Topology(given_field) {
}
