#include "config.h"
#include "road.h"
#include "pos.h"
#include "enums/directions.h"
#include "vehicle.h"
#include "intersection.h"
#include "mymath.h"
#include "vehicleInfo.h"
#include <tuple>

Vehicle::Vehicle(Road* road, Road* destination, int size) : 
    road(road), 
    start(road),
    destination(destination), 
    size(size),
    currStep(0),
    age(0),
    pos(road->getStart())
{
    Astar gps = Astar();
    std::tuple<int, std::vector<Direction>> pathInfo = gps.astar(start, destination);
    expectedLifespan = std::get<0>(pathInfo);
    path = std::get<1>(pathInfo);
};

void Vehicle::updatePos() {
    std::tuple<Pos, Road*> newLocationInfo = road->travelRoad(pos, path[currStep]);
    pos = std::get<0>(newLocationInfo);

    Road* updatedRoad = std::get<1>(newLocationInfo);
    if (road != updatedRoad) {
        road = updatedRoad;
        currStep += 1;
    }
};

void Vehicle::move() {
    age += 1;
    road->moveVehicle(pos, size);
};

VehicleLifetimeStatus Vehicle::reachedDestination() {
    if (road != destination) {
        return VehicleLifetimeStatus();
    }

    return VehicleLifetimeStatus(
        true, 
        expectedLifespan,
        age,
        path,
        start, 
        road
    );
};

std::tuple<Pos, int, int> Vehicle::getPositionalInfo() { 
    return std::tuple<Pos, int, int>(pos, age, currStep);
}