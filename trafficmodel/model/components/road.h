#pragma once
#include "config.h"
#include "pos.h"
#include "directions.h"
#include "intersection.h"
#include <tuple>

class Intersection;

class Road {
    private:
        Pos start;
        Pos end;
        Intersection* intersection;

        float slope;
        float eucDistance;
        int integerLength;
        std::unordered_map<int, bool> vehicles;
        
        // Converts a Positions into an index to vehivles
        int posToIndex(Pos pos);

        // Determines if there is space for a vehicale at pos to move
        Pos isSpace(Pos pos);

        // Determines if a vehicle can cross the intersection
        std::tuple<Pos, Road*> crossIntersection(Pos pos, Direction dir);
    public:

        // Called by vehicle to detemines next turns positions
        std::tuple<Pos, Road*> travelRoad(Pos pos, Direction dir);

        // Returns the start pos
        Pos getStart();

        // Gets length of road = numVehicles
        int length();

        //Get Intersection
        Intersection* getIntersection();

        // Determines if a car can enter road
        bool isFull();

        // Set all road values to false
        void clearRoad();

        //Places vehicle at pos
        void moveVehicle(Pos pos, int size);

        // Deletes a vehicle at pos
        void deleteVehicle(Pos pos);

        // Return if vehicle is at index (for testing)
        bool vehicleAtIndex(int index);

        // Returns a vector that can be saved to represented the road
        std::tuple<std::vector<float>, Intersection*> serialize();

        Road(Pos start, Pos end, Intersection* intersection);
        ~Road();

};