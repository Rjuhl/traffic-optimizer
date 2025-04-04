#include "map.h"
#include "garage.h"
#include "defaultStrategy.h"
#include "vehicleInfo.h"
#include <fstream>
#include <cmath>

Map::Map(){};
Map::~Map(){
    for (int i = 0; i < vehicles.size(); i++) {
        delete vehicles[i];
    }
    for (int i = 0; i < garages.size(); i++) {
        delete garages[i];
    }
    for (int i = 0; i < roads.size(); i++) {
        delete roads[i];
    }
    for (int i = 0; i < intersections.size(); i++) {
        delete intersections[i];
    }
};

Map::Map(const std::string& filePath) {
    loadMap(filePath);
    setStrategy(new DefaultStrategy(this));
}

void Map::saveMap(const std::string& filePath) {
    std::unordered_map<Road*, int> roadIndexs;
    for (int i = 0; i < roads.size(); i++) {
        roadIndexs[roads[i]] = i;
    }

    std::unordered_map<Intersection*, int> intersectionIndexs;
    for (int i = 0; i  < intersections.size(); i++) {
        intersectionIndexs[intersections[i]] = i;
    }

    /* Save intersections
        intersection data: [posx, posy, verticalStartCount, horizontalStartCount, verticalCrossing]  
        intersection roads [x1, x2, x3, x4, x5, x6, x7, x8] -- x_x = road index, -1 = nullptrs
    */

    std::vector<float> interData;
    std::vector<int> interRoadData;
    for (int i = 0; i < intersections.size(); i++) {
        auto [attr, connections] = intersections[i]->seriralize();
        interData.insert(interData.end(), attr.begin(), attr.end());
        for (int j = 0; j < connections.size(); j++) {
            (connections[j] == nullptr) ? 
            interRoadData.push_back(-1) : interRoadData.push_back(roadIndexs[connections[j]]);
        }
    }

    /* Save roads
        road data: [startx, stary, endx, endy, intersection index]
    */

    std::vector<float> roadData;
    for (int i = 0; i < roads.size(); i++) {
        auto [positions, intersection] = roads[i]->serialize();
        positions.push_back((float)intersectionIndexs[intersection]);
        roadData.insert(roadData.end(), positions.begin(), positions.end());
    }

    /* Save Garages
        garage data: [posx, posy, exit road index]
    */

    std::vector<float> garageData;
    for (int i = 0; i < garages.size(); i++) {
        auto [pos, exit] = garages[i]->serialize();
        garageData.push_back(pos.x);
        garageData.push_back(pos.y);
        garageData.push_back((float)roadIndexs[exit]);
    }

    /* Save everything to the file
        intersection data,
        intersection roads,
        road data,
        garage data
    */
   
    std::ofstream file(filePath, std::ios::binary);
    if (file.is_open()) {
        
        size_t interDataSize = interData.size();
        file.write(reinterpret_cast<const char*>(&interDataSize), sizeof(interDataSize));
        file.write(reinterpret_cast<const char*>(interData.data()), interDataSize * sizeof(float));
    
        size_t interRoadDataSize = interRoadData.size();
        file.write(reinterpret_cast<const char*>(&interRoadDataSize), sizeof(interRoadDataSize));
        file.write(reinterpret_cast<const char*>(interRoadData.data()), interRoadDataSize * sizeof(int));

        size_t roadDataSize = roadData.size();
        file.write(reinterpret_cast<const char*>(&roadDataSize), sizeof(roadDataSize));
        file.write(reinterpret_cast<const char*>(roadData.data()), roadDataSize * sizeof(float));

        size_t garageDataSize = garageData.size();
        file.write(reinterpret_cast<const char*>(&garageDataSize), sizeof(garageDataSize));
        file.write(reinterpret_cast<const char*>(garageData.data()), garageDataSize * sizeof(float));

        file.close();
    } else {
        std::cerr << "Error opening file for writing: " << filePath << std::endl;
    }

};

void Map::loadMap(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    
    std::vector<float> interData;
    std::vector<int> interRoadData;
    std::vector<float> roadData;
    std::vector<float> garageData;

    if (file.is_open()) {

        size_t interDataSize;
        file.read(reinterpret_cast<char*>(&interDataSize), sizeof(interDataSize));
        interData.resize(interDataSize);
        file.read(reinterpret_cast<char*>(interData.data()), interDataSize * sizeof(float));

        size_t interRoadDataSize;
        file.read(reinterpret_cast<char*>(&interRoadDataSize), sizeof(interRoadDataSize));
        interRoadData.resize(interRoadDataSize);
        file.read(reinterpret_cast<char*>(interRoadData.data()), interRoadDataSize * sizeof(int));

        size_t roadDataSize;
        file.read(reinterpret_cast<char*>(&roadDataSize), sizeof(roadDataSize));
        roadData.resize(roadDataSize);
        file.read(reinterpret_cast<char*>(roadData.data()), roadDataSize * sizeof(float));

        size_t garageDataSize;
        file.read(reinterpret_cast<char*>(&garageDataSize), sizeof(garageDataSize));
        garageData.resize(garageDataSize);
        file.read(reinterpret_cast<char*>(garageData.data()), garageDataSize * sizeof(float));

        file.close();
    } else {
        std::cerr << "Error opening file for reading: " << filePath << std::endl;
    }

    // Create Intersections
    int chunkSize = 5;
    for (int i = 0; i < interData.size(); i += chunkSize) {
        intersections.push_back(new Intersection(
            Pos(interData[i], interData[i + 1]),
            (int)interData[i + 2], (int)interData[i + 3],
            (bool)interData[i + 4]
        ));
    }

    // Create Roads
    chunkSize = 5;
    for (int i = 0; i < roadData.size(); i += chunkSize) {
        roads.push_back(new Road(
            Pos(roadData[i], roadData[i + 1]),
            Pos(roadData[i + 2], roadData[i + 3]),
            intersections[(int)roadData[i + 4]]
        ));
    }

    // Assign roads to intersections
    chunkSize = 8;
    const std::unordered_map<int, Direction> indexToDir = { 
        {0, Direction::TOP},
        {1, Direction::BOTTOM},
        {2, Direction::LEFT},
        {3, Direction::RIGHT}
    };
    for (int i = 0; i < interRoadData.size(); i += chunkSize) {
        for (int j = 0; j < chunkSize; j++) {
            if (interRoadData[i + j] != -1) {
                int interIndex = std::floor(i / chunkSize);
                (j < chunkSize / 2) ? 
                intersections[interIndex]->assignIncomingRoad(roads[roadData[i + j]], indexToDir.at(j % (chunkSize / 2))) : 
                intersections[interIndex]->assignOutgoingRoad(roads[roadData[i + j]], indexToDir.at(j % (chunkSize / 2)));
            }
        }
    }

    // Create garages;
    chunkSize = 3;
    for (int i = 0; i < garageData.size(); i += chunkSize) {
        garages.push_back(new Garage(
            Pos(garageData[i], garageData[i + 1]),
            roads[(int)garageData[i + 2]],
            this
        ));
    }
}

void Map::update() {
    for (Vehicle* vehicle : vehicles) { vehicle->updatePos(); };
    for (Garage* garage :  garages) { garage->update(); };
    for (Intersection* intersection: intersection) { intersection->update(); };
    for (int i = vehicles.size() - 1; i >= 0; i--) {
        vehicles[i]->move();
        VehicleLifetimeStatus status = vehicles[i]->reachedDestination(); 
        if (status.status) {
            vehicleData.push_back(status);
            delete vehicles[i];
            vehicles.erase(vehicles.begin() + i);
        }
    }
    
    updateTime();
    if (time % strategyUpdateClock == 0) {
        lightStrategy->setUpdateSchedule();
        lightStrategy->updateLightTimers();
    }
}

std::vector<std::tuple<int, int>> Map::getIntersectionTimes() {
    std::vector<std::tuple<int, int>> intersectionTimes;
    for (int i = 0; i < intersections.size(); i++) {
        intersectionTimes.push_back(intersections[i]->getIntersectionTimes());
    }
    return intersectionTimes;
}

MapStats Map::getStats() {
    return MapStats{tripsComplete, timeTravled, expectedTimeTraved};
}

std::vector<IntersectionData> Map::getIntersectionsData(int range) {
    std::vector<IntersectionData> data;
    for (Intersection* intersection : intersections) {
        data.push_back(intersection->getIntersectionData(range));
    }
    return data;
}

void Map::updateTime() {
    if (time >= 86400) {
        time = 0;
    } else {
        time += 1;
    }
}


void Map::setStrategy(Strategy* stategy) { 
    lightStrategy = std::unique_ptr<Strategy>(stategy); 
    lightStrategy->setUpdateSchedule();
    lightStrategy->updateLightTimers();
};

void Map::addVehicle(Vehicle* vehicle) { vehicles.push_back(vehicle); };

std::vector<Road*> Map::getRoads() { return roads; }
std::vector<Intersection*> Map::getIntersections() { return intersections; };
std::vector<Vehicle*> Map::getVehicles() { return vehicles; };
std::vector<Garage*> Map::getGarages() { return garages; };
std::vector<VehicleLifetimeStatus> Map::getVehicleData() { return vehicleData; };
unsigned long Map::getTime() { return time; };