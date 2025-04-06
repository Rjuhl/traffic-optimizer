#pragma once
#include "directions.h"
#include "road.h"
#include <vector>

struct VehicleLifetimeStatus {
    bool status = false;
    int expectedLifespan = -1;
    int age = -1;
    std::vector<Direction> path = {Direction::NONE};
    Road* start = nullptr;
    Road* end = nullptr;

    VehicleLifetimeStatus() = default;

    VehicleLifetimeStatus(bool s, int life, int a, std::vector<Direction> p, Road* st, Road* en)
        : status(s), expectedLifespan(life), age(a), path(std::move(p)), start(st), end(en) {};

    bool operator==(const VehicleLifetimeStatus& other) const {

        for (int i = 0; i < path.size(); i++) {
            if (path[i] != other.path[i]) {
                return false;
            }
        }

        return (
            status == other.status &&
            expectedLifespan ==  other.expectedLifespan &&
            age == other.age && 
            start == other.start &&
            end == other.end &&
            path.size() == other.path.size() 
        );
    };
};
