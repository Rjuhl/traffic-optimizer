#include "config.h"
#include "model/road.h"
#include "utils/pos.h"
#include "enums/directions.h"
#include "model/vehicle.h"
#include "model/intersection.h"
#include "utils/math.h"
#include <tuple>

Vehicle::Vehicle(Road* road, Road* destination, int size) : 
    road(road), 
    destination(destination), 
    size(size),
    age(0)
{
    
};