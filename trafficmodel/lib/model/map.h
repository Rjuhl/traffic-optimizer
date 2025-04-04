#pragma once
#include "vehicle.h"
#include "road.h"
#include "intersection.h"
#include "garage.h"
#include "strategy.h"
#include "mapStats.h"
#include "vehicleInfo.h"
#include "intersectionData.h"
#include <functional>

class Garage;
class Strategy;

class Map {
    private:
        unsigned long time;

        std::vector<Road*> roads;
        std::vector<Intersection*> intersections;
        std::vector<Vehicle*> vehicles;
        std::vector<Garage*> garages;

        uint tripsComplete;
        uint timeTravled;
        uint expectedTimeTraved;
        std::vector<VehicleLifetimeStatus> vehicleData;

        uint strategyUpdateClock;
        uint strategyUpdateClockStart;
        std::shared_ptr<Strategy> lightStrategy; 

        void updateTime();

    public:
        Map();
        ~Map(); 
        Map(const std::string& filePath);
        

        // Performs all logic to next step in simulation
        void update();

        // Updates the light timeing strategy with a custom provided strategy
        void setStrategy(Strategy* stategy);

        // Loads roads, intersection, and garages
        void loadMap(const std::string& filePath);

        // Save roads, intersection, and garage positions to be loaded again
        void saveMap(const std::string& filePath);

        // Adds a new vehicle to the map
        void addVehicle(Vehicle* vehicle);

        // Get the number of times update has been called mod 86400
        unsigned long getTime();
        
        // Return general stats about traffic
        MapStats getStats();

        // Returns all roads on the map
        std::vector<Road*> getRoads();

        // Return all intersections on the map
        std::vector<Intersection*> getIntersections();

        // Returns all vehicles currently on the road
        std::vector<Vehicle*> getVehicles();

        // Returns al garages on the map
        std::vector<Garage*> getGarages();

        // Returns data about all vehicles that have reached their destination
        std::vector<VehicleLifetimeStatus> getVehicleData();

        // Returns data about each intersection over a time range
        std::vector<IntersectionData> getIntersectionsData(int range);

        // Returns the light timeing for each intersection on the map
        std::vector<std::tuple<int, int>> getIntersectionTimes();
};