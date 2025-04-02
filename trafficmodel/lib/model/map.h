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
        

        void update();
        void setStrategy(Strategy stategy);
        void loadMap(const std::string& filePath);
        void saveMap(const std::string& filePath);
        void addVehicle(Vehicle* vehicle);
        unsigned long getTime();
        
        
        MapStats getStats();
        std::vector<Road*> getRoads();
        std::vector<Intersection*> getIntersections();
        std::vector<Vehicle*> getVehicles();
        std::vector<Garage*> getGarages();
        std::vector<VehicleLifetimeStatus> getVehicleData();
        std::vector<IntersectionData> getIntersectionsData(int range);
        std::vector<std::tuple<int, int>> getIntersectionTimes();
};