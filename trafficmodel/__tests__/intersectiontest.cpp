#include <gtest/gtest.h>
#include "intersection.h"
#include "road.h"

std::tuple<Intersection*, Road*, Road*, Road*> getBasicIntersection(int vertCount, int horCount) {
    Intersection* intersection = new Intersection(Pos(0, 0), vertCount, horCount, true);
    Road* vertical = new Road(Pos(1, 1), Pos(1, 0), intersection);
    Road* horizontal = new Road(Pos(0, 0), Pos(1, 0), intersection);
    Road* outgoing = new Road(Pos(1, 0), Pos(2, 0), intersection);
    intersection->assignIncomingRoad(vertical, Direction::TOP);
    intersection->assignIncomingRoad(horizontal, Direction::LEFT);
    intersection->assignOutgoingRoad(outgoing, Direction::RIGHT);
    return {intersection, vertical, horizontal, outgoing};
}

// Test update
TEST(IntersectionSuite, IntersectionUpdateTests) {
    // Test that updates switch back and forth
    auto [i, v, h, o] = getBasicIntersection(2, 2);



    // Test that countdown is correct

    // Test that countdown is correct when the lights are timed differently
};

// Test Crossing
TEST(IntersectionSuite, CrossingTests) {
    // Test Cross all directions while light is green

    // Test Cross all direction while light is red

    // Test crossing when road is full
};