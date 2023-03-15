#include "world.h"

#include <algorithm>

World::World(const Topology& topology, Point start, Point end)
    : topology_(topology), start_(start), end_(end), current_position_(start) {
}

const Point& World::GetStart() const {
    return start_;
}

const Point& World::GetEnd() const {
    return end_;
}

const Point& World::GetCurrentPosition() const {
    return current_position_;
}

std::unordered_map<Point, Topology::Distance> World::Lookup() const {
    std::unordered_map<Point, Topology::Distance> result;
    for (auto& neighbor : topology_.GetNeighbours(current_position_)) {
        result[neighbor] = topology_.MeasureDistance(neighbor, end_);
    }
    return result;
}

void World::Move(const Point& to) {
    auto neighbors = topology_.GetNeighbours(current_position_);
    if (std::find(neighbors.begin(), neighbors.end(), to) == neighbors.end()) {
        throw IllegalMoveException();
    }
    current_position_ = to;
}
