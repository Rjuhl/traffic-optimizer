#include "map.h"
#include "garage.h"


std::vector<std::tuple<int, int>> Map::getIntersectionTimes() {
    std::vector<std::tuple<int, int>> intersectionTimes;
    for (int i  = 0; i < intersections.size(); i++) {
        intersectionTimes.push_back(intersections[i]->getIntersectionTimes());
    }
    return intersectionTimes;
}

MapStats Map::getStats() {
    return MapStats{tripsComplete, timeTravled, expectedTimeTraved};
}

std::vector<IntersectionData> Map::getIntersectionsData(int range) {
    std::vector<IntersectionData> data;
    for (Intersection* intersection : intersections) {
        data.push_back(intersection->getIntersectionData(range));
    }
    return data;
}

std::vector<Road*> Map::getRoads() { return roads; }
std::vector<Intersection*> Map::getIntersections() { return intersections; };
std::vector<Vehicle*> Map::getVehicles() { return vehicles; };
std::vector<Garage*> Map::getGarages() { return garages; };
std::vector<VehicleLifetimeStatus> Map::getVehicleData() { return vehicleData; };