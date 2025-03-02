#include "config.h"
#include "model/road.h"
#include "utils/pos.h"
#include "enums/directions.h"
#include "model/vehicle.h"
#include "model/intersection.h"
#include "utils/math.h"
#include <tuple>
#include <cassert>

Intersection::Intersection(
    std::vector<Road*>& roads,
    int verticalCountStart, 
    int horizontalCountStart,
    bool verticalCrossing
) : 
    roads(roads),
    verticalCountStart(verticalCountStart),
    horizontalCountStart(horizontalCountStart),
    verticalCrossing(verticalCrossing) 
{
    (verticalCrossing) ? countDown = verticalCountStart : countDown = horizontalCountStart;

    Direction directions[4] = {Direction::LEFT, Direction::RIGHT, Direction::TOP, Direction::BOTTOM};
    assert(roads.size() == 8);
    int loops = roads.size() / 2;
    for (int i = 0; i < loops; i++) {
        outgoing[directions[i]] = roads[i];
        incoming[roads[loops + i]] = directions[i];
    }

};

void Intersection::update() {
    countDown -= 1;
    if (countDown == 0) {
        verticalCrossing = !verticalCrossing;
        (verticalCrossing) ? countDown = verticalCountStart : countDown = horizontalCountStart;
    }
}

Road* Intersection::link(Direction direction) {
    return outgoing[direction];
}

std::tuple<Pos, Road*> Intersection::cross(Road* road, Pos pos, Direction dir) {
    Direction rfrom = incoming[road];
    if (((rfrom == Direction::TOP || rfrom == Direction::BOTTOM) && verticalCrossing) ||
        ((rfrom == Direction::LEFT || rfrom == Direction::RIGHT) && !verticalCrossing)) {
        if (!(outgoing[dir]->isFull())) {
            return std::tuple<Pos, Road*>(outgoing[dir]->getStart(), outgoing[dir]);
        }
    }
    return std::tuple<Pos, Road*>(pos, road);
};