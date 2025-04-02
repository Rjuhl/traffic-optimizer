#pragma once
#include "config.h"
#include "road.h"
#include "pos.h"
#include "map.h"
#include "garagePatterns.h"
#include <functional>

class Map;
class GaragePatterns;

class Garage {
    private:
        Pos pos;
        Road* exit;
        Map* map;

        std::unique_ptr<GaragePatterns> patterns;
        
    public:
        Garage(Pos pos, Road* exit, Map* map);
       
        void assignPattern(GaragePatterns* pattern);
        void update();
        Map* getMap();
};