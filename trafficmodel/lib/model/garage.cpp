#include "config.h"
#include "garage.h"
#include "map.h"
#include "defaultGarage.h"

Garage::Garage(
    Pos pos, 
    Road* exit,
    Map* map
) : 
    pos(pos),
    exit(exit),
    map(map),
    patterns(std::make_unique<DefaultGaragePattern>(this))
{};

void Garage::update() {
    if (!exit->isFull() && patterns->vehicleExits(map->getTime())) {
        Vehicle* vehicle = new Vehicle(
            exit, 
            map->getRoads()[patterns->assignDestination(map->getTime())], 
            patterns->assignSize()
        );
        map->addVehicle(vehicle);
    }
}

void Garage::assignPattern(GaragePatterns* pattern) {
    patterns = std::unique_ptr<GaragePatterns>(pattern);
}

Map* Garage::getMap() { return map; };