#include <gtest/gtest.h>
#include "road.h"
#include "intersection.h"
#include "mymath.h"

// Test Move Vehicle
TEST(RoadSuite, MoveVehicleTest) {
    Intersection* intersection = new Intersection(1, 1, false);
    Road* straight = new Road(Pos(0, 0), Pos(5, 0), intersection); 
    Road* diagonal = new Road(Pos(0, 0), Pos(5, 5), intersection);

    straight->moveVehicle(Pos(0, 0), 2);
    straight->moveVehicle(Pos(3.3, 0), 2);
    diagonal->moveVehicle(Pos(0, 0), 2);
    diagonal->moveVehicle(Pos(3.05, 3.12), 2);

    std::vector<bool> straightExpected = {true, false, true, true, false};
    for (int i = 0; i < straightExpected.size(); i++) {
        EXPECT_EQ(straight->vehicleAtIndex(i), straightExpected[i]);
    }

    std::vector<bool> diagonalExpected = {true, false, false, true, true, false, false};
    for (int i = 0; i < diagonalExpected.size(); i++) {
        EXPECT_EQ(diagonal->vehicleAtIndex(i), diagonalExpected[i]);
    }

    delete straight;
    delete diagonal;
    delete intersection;
};

// Test travel road
TEST(RoadSuite, TravelRoadTest) {
    Intersection* intersection = new Intersection(1, 1, false);
    Road* outgoingRoad = new Road(Pos(10, 10), Pos(10, 11), intersection);
    Road* straight = new Road(Pos(0, 0), Pos(5, 0), intersection); 
    Road* diagonal = new Road(Pos(0, 0), Pos(5, 5), intersection);

    intersection->assignOutgoingRoad(outgoingRoad, Direction::RIGHT);
    intersection->assignIncomingRoad(straight, Direction::LEFT);
    intersection->assignIncomingRoad(diagonal, Direction::RIGHT);

    // diagonalStepSize = [x/y movemenet] / [# of steps]
    float diagonalStepSize = 5 / std::floor(euclideanDistance(Pos(0, 0), Pos(5, 5)));

    // Travel from second postion top third
    auto [pos1, road1] = straight->travelRoad(Pos(2, 0), Direction::NONE);
    auto [pos2, road2] = diagonal->travelRoad(Pos(2, 2), Direction::NONE);
   
    EXPECT_EQ(pos1.x, 3);
    EXPECT_EQ(pos1.y, 0);
    EXPECT_EQ(straight, road1);

    EXPECT_EQ(pos2.x, 2 + diagonalStepSize);
    EXPECT_EQ(pos2.y, 2 + diagonalStepSize);
    EXPECT_EQ(diagonal, road2);

    // Test that we dont travel through other vehicles
    straight->moveVehicle(Pos(3, 0), 1);
    diagonal->moveVehicle(Pos(3, 3), 1);

    auto [pos3, road3] = straight->travelRoad(Pos(2, 0), Direction::NONE);
    auto [pos4, road4] = diagonal->travelRoad(Pos(2.5, 2.5), Direction::NONE);

    EXPECT_EQ(pos3.x, 2);
    EXPECT_EQ(pos3.y, 0);
    EXPECT_EQ(straight, road3);

    EXPECT_EQ(pos4.x, 2.5);
    EXPECT_EQ(pos4.y, 2.5);
    EXPECT_EQ(diagonal, road4);

    std::cout << std::endl << std::endl << std::endl;

    // Test that we can cross an intersection
    auto [pos5, road5] = straight->travelRoad(Pos(4, 0), Direction::RIGHT);
    auto [pos6, road6] = diagonal->travelRoad(Pos(4.5, 4.5), Direction::RIGHT);

    EXPECT_EQ(pos5.x, 10);
    EXPECT_EQ(pos5.y, 10);
    EXPECT_EQ(outgoingRoad, road5);

    EXPECT_EQ(pos6.x, 10);
    EXPECT_EQ(pos6.y, 10);
    EXPECT_EQ(outgoingRoad, road6);

    delete straight;
    delete diagonal;
    delete outgoingRoad;
    delete intersection;
}



