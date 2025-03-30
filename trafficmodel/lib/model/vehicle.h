#pragma once
#include "config.h"
#include "road.h"
#include "utils/pos.h"
#include "utils/astar.h"

class Vehicle {
    private:
        int size;
        int age;
        int expected_lifespan;

        Pos* pos;
        Road* road;
        Road* destination;
        Astar* gps;
        std::vector<Direction> path;

    public:
        Vehicle(Road* road, Road* destination, int size);
        ~Vehicle();
        
        // Sets cars pos to next pos (does not move the car to that pos)
        void updatePos();

        // moves car along road
        void move();
};