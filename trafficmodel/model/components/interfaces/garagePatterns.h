#pragma once
#include "garage.h"

class Garage;

class GaragePatterns {
    public:
        std::shared_ptr<Garage> garage;

        GaragePatterns(Garage* garage) : garage(std::unique_ptr<Garage>(garage)) {};
        virtual size_t assignDestination(unsigned long time) = 0;
        virtual bool vehicleExits(unsigned long time) = 0;
        virtual int assignSize() = 0;

        virtual ~GaragePatterns() = default;
};