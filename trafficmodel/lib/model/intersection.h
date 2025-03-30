#pragma once
#include "config.h"
#include "road.h"
#include "../utils/pos.h"

class Road;

class Intersection {
    private:
        std::unordered_map<Direction, Road*> outgoing;
        std::unordered_map<Road*, Direction> incoming;
        Direction directions[4];

        int countDown;
        int verticalCountStart;
        int horizontalCountStart;

        bool verticalCrossing;

    public:
        Intersection(
            int verticalCountStart, 
            int horizontalCountStart, 
            bool verticalCrossing
        );

        Road* link(Direction dir);
        std::tuple<Pos, Road*> cross(Road* road, Pos pos, Direction dir);
        void update();
        void assignIncomingRoad(Road* road, Direction dir);
        void assignOutgoingRoad(Road* road, Direction dir);
};