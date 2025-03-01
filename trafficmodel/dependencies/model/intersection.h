#pragma once
#include "config.h"
#include "road.h"
#include "../utils/pos.h"

class Road;

class Intersection {
    private:
        Road* leftRoad;
        Road* rightRoad;
        Road* topRoad;
        Road* bottomRoad;
        std::unordered_map<Direction, Road*> directionMap;
        
        int countDown;
        int verticalCountStart;
        int horizontalCountStart;

        bool verticalCrossing;

    public:
        Intersection(
            Road* leftRoad,
            Road* rightRoad, 
            Road* topRoad, 
            Road* bottomRoad, 
            int verticalCountStart, 
            int horizontalCountStart, 
            bool verticalCrossing
        );
        ~Intersection();

        std::tuple<Pos, Road*> cross(Road* road, Pos pos, Direction dir);
        void update();
};