#include <gtest/gtest.h>
#include "vehicle.h"
#include "helpers.h"

TEST(VehicleSuite, TestStats) {
    SimpleAcyclicGraph graph = helpers.getSimpleAcyclicGraph();
    Road* start = graph.getRoads()[3];
    Road* end = graph.getRoads()[5];
    Vehicle* vehicle = new Vehicle(start, end, 1);

    helpers.vehicleUpdate(vehicle, 1);
    auto [_1, age1, currStep1] = vehicle->getPositionalInfo();
    
    EXPECT_EQ(age1, 1);
    EXPECT_EQ(currStep1, 0);
    EXPECT_EQ(vehicle->reachedDestination(), VehicleLifetimeStatus());

    helpers.vehicleUpdate(vehicle, 1);
    auto [_2, age2, currStep2] = vehicle->getPositionalInfo();

    EXPECT_EQ(age2, 2);
    EXPECT_EQ(currStep2, 1);
    EXPECT_EQ(vehicle->reachedDestination(), VehicleLifetimeStatus(
        true, 2, 2,
        std::vector<Direction>{Direction::TOP},
        start, end
    ));

    delete vehicle;
}
