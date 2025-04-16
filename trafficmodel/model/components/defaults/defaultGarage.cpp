#include "defaultGarage.h"
#include <random>

size_t DefaultGaragePattern::assignDestination(unsigned long time) {
    size_t numChoices = garage->getMap()->getRoads().size();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, numChoices - 1);
    return dist(gen);
}

bool DefaultGaragePattern::vehicleExits(unsigned long time) {return true; }
int DefaultGaragePattern::assignSize() { return 1; }