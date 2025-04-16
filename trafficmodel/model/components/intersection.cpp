#include "config.h"
#include "road.h"
#include "pos.h"
#include "directions.h"
#include "vehicle.h"
#include "intersection.h"
#include "mymath.h"
#include <tuple>
#include <cassert>

Intersection::Intersection(
    Pos pos,
    int verticalCountStart, 
    int horizontalCountStart,
    bool verticalCrossing
) :
    pos(pos),
    verticalCountStart(verticalCountStart),
    horizontalCountStart(horizontalCountStart),
    verticalCrossing(verticalCrossing),
    carsCrossed(0),
    carsThatCouldCross(0),
    maxQueueSize(120)
{
    (verticalCrossing) ? countDown = verticalCountStart : countDown = horizontalCountStart;
};

void Intersection::update() {
    float eff = (carsThatCouldCross > 0) ? carsCrossed / carsThatCouldCross : 1;
    if (verticalCrossing) {
        updateQueue(IntersectionData(carsCrossed, 0, eff, 1));
    } else {
        updateQueue(IntersectionData(0, carsCrossed, 1, eff));
    }   

    countDown -= 1;
    carsCrossed = 0;
    carsThatCouldCross = 0;

    if (countDown == 0) {
        verticalCrossing = !verticalCrossing;
        (verticalCrossing) ? countDown = verticalCountStart : countDown = horizontalCountStart;
    }
}

void Intersection::assignOutgoingRoad(Road* road, Direction dir) {
    outgoing[dir] = road;
} 

void Intersection::assignIncomingRoad(Road* road, Direction dir) {
    incoming[road] = dir;
}   

Road* Intersection::link(Direction direction) {
    return outgoing[direction];
}

std::tuple<int, int> Intersection::getIntersectionTimes() {
    return std::tuple<int, int>(verticalCountStart, horizontalCountStart);
}

std::tuple<Pos, Road*> Intersection::cross(Road* road, Pos pos, Direction dir) {
    Direction rfrom = incoming[road];
    if (((rfrom == Direction::TOP || rfrom == Direction::BOTTOM) && verticalCrossing) ||
        ((rfrom == Direction::LEFT || rfrom == Direction::RIGHT) && !verticalCrossing)) {

        carsThatCouldCross += 1;
        if (!(outgoing[dir]->isFull())) {
            carsCrossed += 1;
            return std::tuple<Pos, Road*>(outgoing[dir]->getStart(), outgoing[dir]);
        }
    }
    return std::tuple<Pos, Road*>(pos, road);
};

void Intersection::updateQueue(IntersectionData data) {
    intersectionData.push_back(data);
    if (intersectionData.size() > maxQueueSize) intersectionData.pop_front();
}

IntersectionData Intersection::getIntersectionData(int range) {
    IntersectionData data = IntersectionData();
    std::vector<IntersectionData> dataToPutBack;
    size_t start = (intersectionData.size() > range) ? intersectionData.size() - range : 0;
    size_t end = intersectionData.size();

    for (int i = start; i < end; i++) {
        data = data + intersectionData.back();
        dataToPutBack.push_back(intersectionData.back());
        intersectionData.pop_back();
    }

    while (dataToPutBack.size() > 0) {
        intersectionData.push_back(dataToPutBack[dataToPutBack.size() - 1]);
        dataToPutBack.pop_back();
    }

    data.verticalEfficiency /= std::min<size_t>(range, intersectionData.size());
    data.horizontalEfficiency /= std::min<size_t>(range, intersectionData.size());
    return data;
};

std::tuple<std::vector<float>, std::vector<Road*>> Intersection::serialize() {
    std::vector<float> attr = {pos.x, pos.y, (float)verticalCountStart, (float)horizontalCountStart, (float)verticalCrossing};
    std::vector<Road*> connections(8, nullptr);
    for (const auto& [road, direction] : incoming) {
        connections[directions.at(direction)] = road;
    }

    for (const auto& [direction, road] : outgoing) {
        connections[4 + directions.at(direction)] = road;
    }
    
    return std::tuple<std::vector<float>, std::vector<Road*>>(attr, connections);
};

void Intersection::updateLightTiming(int verticalTiming, int horizontalTiming) { 
    verticalCountStart = verticalTiming;
    horizontalCountStart = horizontalTiming;
}

const std::unordered_map<Direction, int> Intersection::directions = {
    {Direction::TOP, 0},
    {Direction::BOTTOM, 1},
    {Direction::LEFT, 2},
    {Direction::RIGHT, 3}
};

const std::unordered_map<Direction, int>& Intersection::DirMap() { return directions; };