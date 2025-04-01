#include "config.h"
#include "garage.h"
#include "map.h"

Garage::Garage(
    int numCars, 
    Pos pos, 
    Road* exit,
    Map* map,
    std::function<Road*()> destinationDist
) : 
    numCars(numCars),
    pos(pos),
    exit(exit),
    map(map),
    destinationDist(destinationDist),
    sizeDist([](int) { return 1; })
{};

Garage::Garage(
    int numCars, 
    Pos pos, 
    Road* exit,
    Map* map,
    std::function<Road*()> destinationDist,
    std::function<int(int)> sizeDist
) : 
    numCars(numCars),
    pos(pos),
    exit(exit),
    map(map),
    destinationDist(destinationDist),
    sizeDist(sizeDist)
{};

void Garage::update() {
    if (!exit->isFull() && numCars > 0) {
        Vehicle* vehicle = new Vehicle(
            exit, destinationDist(), sizeDist(numCars)
        );
        map->addVehicle(vehicle);
        numCars -= 1;
    }
}

bool Garage::isEmpty() { return numCars <= 0; }
