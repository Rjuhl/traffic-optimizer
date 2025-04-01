#pragma once
#include "config.h"
#include "road.h"
#include "pos.h"
#include "map.h"
#include <functional>

class Map;

class Garage {
    private:
        int numCars;
        
        Pos pos;
        Road* exit;
        Map* map;

        std::function<int(int)> sizeDist;
        std::function<Road*()> destinationDist;
        
    public:
        Garage(int numCars, Pos pos, Road* exit, Map* map, 
            std::function<Road*()> destinationDist
        );
        Garage(
            int numCars, Pos pos, Road* exit, Map* map, 
            std::function<Road*()> destinationDist, 
            std::function<int(int)> sizeDist
        );

        bool isEmpty();
        void update();

};