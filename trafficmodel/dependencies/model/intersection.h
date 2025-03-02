#pragma once
#include "config.h"
#include "road.h"
#include "../utils/pos.h"

class Road;

class Intersection {
    private:
        std::vector<Road*> roads;
        std::unordered_map<Direction, Road*> outgoing;
        std::unordered_map<Road*, Direction> incoming;
        
        int countDown;
        int verticalCountStart;
        int horizontalCountStart;

        bool verticalCrossing;

    public:
        Intersection(
            std::vector<Road*>& roads,
            int verticalCountStart, 
            int horizontalCountStart, 
            bool verticalCrossing
        );
        ~Intersection();

        Road* link(Direction dir);
        std::tuple<Pos, Road*> cross(Road* road, Pos pos, Direction dir);
        void update();
};