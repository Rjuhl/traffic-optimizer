#include "config.h"
#include "model/road.h"
#include "utils/pos.h"
#include "enums/directions.h"
#include "model/vehicle.h"
#include "model/intersection.h"
#include "utils/mymath.h"
#include <tuple>

Road::Road(Pos start, Pos end, Intersection* intersection) : start(start), end(end), intersection(intersection) {
    slope = (end.y - start.y) / (end.x - start.x);
    eucDistance = euclideanDistance(start, end);
    integerLength = std::floor(eucDistance);
    vehicles = {};
};

Road::~Road() {
};

int Road::posToIndex(Pos pos) {
    float distanceFromStart = euclideanDistance(start, pos);
    float stepSize = eucDistance / integerLength;
    int indx = std::floor(distanceFromStart / stepSize);

    if (indx < 0 || indx >= integerLength) {
        std::cout << "Error in posToIndex Calculation" << std::endl;
        return -1;
    }

    return indx;
};

std::tuple<Pos, Road*> Road::travelRoad(Pos pos, Direction dir) {
    int index = posToIndex(pos);
    if (index == integerLength - 1) {
        return crossIntersection(pos, dir);
    }
    return std::tuple<Pos, Road*>(isSpace(pos), this);
};

Pos Road::isSpace(Pos pos) {
    int index = posToIndex(pos);
    if (vehicles.count(index + 1) < 1) {
        float dx = (end.x - start.x) / integerLength;
        float dy = slope * dx;
        pos.update(pos.x + dx, pos.y + dy);
        return pos;
    }
    return pos;
}

void Road::moveVehicle(Pos pos, int size) { 
    int index = posToIndex(pos);
    for (int i = 0; i < size && index - i >= 0; i++) { vehicles[index - i] = true; }
};

std::tuple<Pos, Road*> Road::crossIntersection(Pos pos, Direction dir) { return intersection->cross(this, pos, dir); }

void Road::deleteVehicle(Pos pos) { vehicles.erase(posToIndex(pos)); };

Intersection* Road::getIntersection() { return intersection; };

Pos Road::getStart() { return start; };

int Road::length() { return integerLength; };

bool Road::isFull() { return vehicles.count(0) > 0; };

bool Road::vehicleAtIndex(int index) { return vehicles.count(index) > 0; }

void Road::clearRoad() { vehicles = {}; };
