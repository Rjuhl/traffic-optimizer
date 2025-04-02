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
       
        // Assigns a custom GaragePattern to the garage which is used to dictate its behaviour
        void assignPattern(GaragePatterns* pattern);

        // Called once per time step, possiable adding a vehicle to the network
        void update();

        // Return the map which the garge is part off
        Map* getMap();
};