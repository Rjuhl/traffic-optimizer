#include "config.h"
#include "model/road.h"
#include "utils/pos.h"
#include "enums/directions.h"
#include "model/vehicle.h"
#include "model/intersection.h"
#include "utils/math.h"
#include <tuple>

Intersection::Intersection(
    Road* leftRoad, 
    Road* rightRoad, 
    Road* topRoad, 
    Road* bottomRoad, 
    int verticalCountStart, 
    int horizontalCountStart,
    bool verticalCrossing
) : 
    leftRoad(leftRoad), 
    rightRoad(rightRoad), 
    topRoad(topRoad), 
    bottomRoad(bottomRoad), 
    verticalCountStart(verticalCountStart),
    horizontalCountStart(horizontalCountStart),
    verticalCrossing(verticalCrossing) 
{
    (verticalCrossing) ? countDown = verticalCountStart : countDown = horizontalCountStart;
    directionMap[Direction::LEFT] = leftRoad;
    directionMap[Direction::RIGHT] = rightRoad;
    directionMap[Direction::TOP] = topRoad;
    directionMap[Direction::BOTTOM] = bottomRoad;

};

void Intersection::update() {
    countDown -= 1;
    if (countDown == 0) {
        verticalCrossing = !verticalCrossing;
        (verticalCrossing) ? countDown = verticalCountStart : countDown = horizontalCountStart;
    }
}

std::tuple<Pos, Road*> Intersection::cross(Road* road, Pos pos, Direction dir) {
    if (((dir == Direction::TOP || dir == Direction::BOTTOM) && verticalCrossing) ||
        ((dir == Direction::LEFT || dir == Direction::RIGHT) && !verticalCrossing)) {
        if (!(directionMap[dir]->isFull())) {
            return std::tuple<Pos, Road*>(directionMap[dir]->getStart(), directionMap[dir]);
        }
    }
    return std::tuple<Pos, Road*>(pos, road);
};