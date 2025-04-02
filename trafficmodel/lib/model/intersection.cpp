#include "config.h"
#include "road.h"
#include "utils/pos.h"
#include "enums/directions.h"
#include "vehicle.h"
#include "model/intersection.h"
#include "utils/mymath.h"
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
    if (verticalCrossing) {
        updateQueue(IntersectionData(carsCrossed, 0, carsCrossed / carsThatCouldCross, 1));
    } else {
        updateQueue(IntersectionData(0, carsCrossed, 1, carsCrossed / carsThatCouldCross));
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
        if (!(outgoing[dir]->isFull())) {
            carsCrossed += 1;
            return std::tuple<Pos, Road*>(outgoing[dir]->getStart(), outgoing[dir]);
        }
        carsThatCouldCross += 1;
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
    size_t start = std::max<size_t>(0, intersectionData.size() - range);
    for (int i = start; i < intersectionData.size(); i++) {
        data = data + intersectionData.back();
        dataToPutBack.push_back(intersectionData.back());
        intersectionData.pop_back();
    }

    while (dataToPutBack.size() > 0) {
        intersectionData.push_back(dataToPutBack[dataToPutBack.size() - 1]);
        dataToPutBack.pop_back();
    }

    data.verticalEfficiency /= range;
    data.horizontalEfficiency /= range;
    return data;
};