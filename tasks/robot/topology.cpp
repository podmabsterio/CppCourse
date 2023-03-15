#include "topology.h"
#include <queue>
#include <unordered_map>

Topology::Field::Field(TrapsField given_field) : field_(given_field) {
}
bool Topology::Field::IsObstacle(const Point& point) const {
    return point.y >= field_.size() || point.x >= field_[0].size() || field_[point.y][point.x];
}

size_t Topology::Field::SizeY() const {
    return field_.size();
}

size_t Topology::Field::SizeX() const {
    if (field_.empty()) {
        return 0;
    }
    return field_[0].size();
}

bool Topology::Field::IsInBound(Point point, int8_t dif_x, int8_t dif_y) const {
    if (dif_x < 0 && point.x < static_cast<size_t>(-dif_x)) {
        return false;
    }
    if (dif_y < 0 && point.y < static_cast<size_t>(-dif_y)) {
        return false;
    }
    if (dif_x > 0 && (field_[0].size() <= static_cast<size_t>(dif_x) ||
                      point.x > field_[0].size() - static_cast<size_t>(dif_x) - 1)) {
        return false;
    }
    if (dif_y > 0 &&
        (field_.size() <= static_cast<size_t>(dif_y) || point.y > field_.size() - static_cast<size_t>(dif_y) - 1)) {
        return false;
    }
    return true;
}

Topology::Topology(TrapsField given_field) : map_(given_field) {
}

Topology::Distance Topology::MeasureDistance(const Point& from, const Point& to) const {
    if (from == to) {
        return 0;
    }
    std::queue<Point> not_processed;
    Topology::DistanceMap distance_map(map_.field_.size(), std::vector<Distance>(map_.field_[0].size(), 0));
    not_processed.push(to);
    bool reachable = false;
    std::unordered_map<Point, bool> used;
    used[to] = true;
    while (!not_processed.empty() && !reachable) {
        Point current = not_processed.front();
        not_processed.pop();
        for (auto& neighbor : GetNeighbours(current)) {
            if (!used[neighbor]) {
                used[neighbor] = true;
                not_processed.push(neighbor);
                distance_map[neighbor.y][neighbor.x] = distance_map[current.y][current.x] + 1;
                if (neighbor == from) {
                    reachable = true;
                }
            }
        }
    }
    if (!reachable) {
        return Topology::UNREACHABLE;
    }
    return distance_map[from.y][from.x];
}
