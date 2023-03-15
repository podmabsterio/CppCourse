#include "robot.h"

namespace robot {
Path FindPath(World& world) {
    Path result;
    result.emplace_back(world.GetStart());
    if (world.GetCurrentPosition() == world.GetEnd()) {
        return result;
    }
    if (world.Lookup().empty()) {
        return Path();
    }
    Topology::Distance current_distance = world.Lookup().begin()->second;
    Point best_point = world.Lookup().begin()->first;
    for (auto& [to, distance] : world.Lookup()) {
        if (distance < current_distance) {
            best_point = to;
            current_distance = distance;
        }
    }
    if (current_distance == Topology::UNREACHABLE) {
        return Path();
    }
    result.emplace_back(best_point);
    world.Move(best_point);
    while (world.GetCurrentPosition() != world.GetEnd()) {
        for (auto& [to, distance] : world.Lookup()) {
            if (distance == current_distance - 1) {
                result.emplace_back(to);
                world.Move(to);
                --current_distance;
                break;
            }
        }
    }
    return result;
}
}  // namespace robot