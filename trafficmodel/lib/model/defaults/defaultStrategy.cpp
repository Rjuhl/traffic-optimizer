#include "defaultStrategy.h"

int DefaultStrategy::setUpdateSchedule() { return 360; }
std::unordered_map<int, std::tuple<int, int>> DefaultStrategy::updateLightTimers() {
    std::unordered_map<int, std::tuple<int, int>> timings;
    for (int i = 0; i < map->getIntersections().size(); i++) {
        timings[i] = std::tuple<int, int>(60, 60);
    }
    return timings;
}