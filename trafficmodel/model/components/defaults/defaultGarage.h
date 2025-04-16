#pragma once
#include "garagePatterns.h"

class DefaultGaragePattern : public GaragePatterns {
    public:
        DefaultGaragePattern(Garage* garage) : GaragePatterns(garage) {};
        size_t assignDestination(unsigned long time) override;
        bool vehicleExits(unsigned long time) override;
        int assignSize() override;
};