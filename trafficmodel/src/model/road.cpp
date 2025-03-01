#include "config.h"
#include "model/road.h"
#include "utils/pos.h"
#include "enums/directions.h"
#include "model/vehicle.h"
#include "model/intersection.h"
#include "utils/math.h"
#include <tuple>

Road::Road(Pos start, Pos end, Intersection* intersection) : start(start), end(end), intersection(intersection) {
    slope = (end.y - start.y) / (end.x - start.x);
    eucDistance = euclideanDistance(start, end);
    numVehicles = std::floor(eucDistance);
    vehicles = {};
};

Road::~Road() {
};

int Road::posToIndex(Pos pos) {
    float distanceFromStart = euclideanDistance(start, pos);
    float stepSize = eucDistance / numVehicles;
    int indx = std::floor(distanceFromStart / stepSize);

    if (indx < 0 || indx >= numVehicles) {
        std::cout << "Error in posToIndex Calculation" << std::endl;
        return -1;
    }

    return indx;
};

std::tuple<Pos, Road*> Road::travelRoad(Pos pos, Direction dir) {
    int index = posToIndex(pos);
    if (index == numVehicles - 1) {
        return crossIntersection(pos, dir);
    }
    return std::tuple<Pos, Road*>(isSpace(pos), this);
};

Pos Road::isSpace(Pos pos) {
    int index = posToIndex(pos);
    if (vehicles.count(index + 1) < 1) {
        float dx = (end.x - start.x) / numVehicles;
        float dy = slope * dx;
        pos.update(pos.x + dx, pos.y + dy);
        return pos;
    }
    return pos;
}

std::tuple<Pos, Road*> Road::crossIntersection(Pos pos, Direction dir) { return intersection->cross(this, pos, dir); }

void Road::deleteVehicle(Pos pos) { vehicles.erase(posToIndex(pos)); };

void Road::moveVehicle(Pos pos) { vehicles[posToIndex(pos)] = true; };

Pos Road::getStart() { return start; };

bool Road::isFull() { return vehicles.count(0) > 0; };

void Road::clearRoad() { vehicles = {}; };
