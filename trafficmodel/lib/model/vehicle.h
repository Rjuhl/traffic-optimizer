#pragma once
#include "config.h"
#include "road.h"
#include "utils/pos.h"
#include "utils/astar.h"
#include "vehicleInfo.h"

class Vehicle {
    private:
        int size;
        int age;
        int currStep;
        int expectedLifespan;

        Road* road;
        Road* start;
        Road* destination;

        Pos pos;
        std::vector<Direction> path;

    public:
        Vehicle(Road* road, Road* destination, int size);
        
        // Sets cars pos to next pos (does not move the car to that pos)
        void updatePos();

        // moves car along road
        void move();

        // Checks if the destination has been reached and returns travel info
        VehicleLifetimeStatus reachedDestination();
};