#include <gtest/gtest.h>
#include "helpers.h"

// Test setting intersection timeings
TEST(IntersectionSuite, TestGetSetLightTimings) {
    auto [i, v, h, o] = helpers.getBasicIntersection(2, 2);
    auto [t1, t2] = i->getIntersectionTimes();

    EXPECT_EQ(t1, 2);
    EXPECT_EQ(t2, 2);

    i->updateLightTiming(10, 20);
    auto [t3, t4] = i->getIntersectionTimes();

    EXPECT_EQ(t3, 10);
    EXPECT_EQ(t4, 20);    

    helpers.deleteBasicIntersection({i, v, h, o});
};

// Test update
TEST(IntersectionSuite, IntersectionUpdateTests) {
    // Test that updates switch back and forth
    auto [i, v, h, o] = helpers.getBasicIntersection(2, 2);

    // Test that countdown is correct
    auto [_1, r1] = i->cross(v, Pos(-1, -1), Direction::RIGHT);
    auto [_2, r2] = i->cross(h, Pos(-1, -1), Direction::RIGHT);
    EXPECT_EQ(r1, o);
    EXPECT_EQ(r2, h);  
    helpers.updateIntersection(i, 2);
    auto [_3, r3] = i->cross(v, Pos(-1, -1), Direction::RIGHT);
    auto [_4, r4] = i->cross(h, Pos(-1, -1), Direction::RIGHT);
    EXPECT_EQ(r3, v);
    EXPECT_EQ(r4, o); 


    // Test that countdown is correct when the lights are timed differently
    i->updateLightTiming(3, 2);
    helpers.updateIntersection(i, 2);
    auto [_5, r5] = i->cross(v, Pos(-1, -1), Direction::RIGHT);
    auto [_6, r6] = i->cross(h, Pos(-1, -1), Direction::RIGHT);
    EXPECT_EQ(r5, o);
    EXPECT_EQ(r6, h); 
    helpers.updateIntersection(i, 2);
    auto [_7, r7] = i->cross(v, Pos(-1, -1), Direction::RIGHT);
    auto [_8, r8] = i->cross(h, Pos(-1, -1), Direction::RIGHT);
    EXPECT_EQ(r7, o);
    EXPECT_EQ(r8, h); 
    helpers.updateIntersection(i, 2);
    auto [_9, r9] = i->cross(v, Pos(-1, -1), Direction::RIGHT);
    auto [_10, r10] = i->cross(h, Pos(-1, -1), Direction::RIGHT);
    EXPECT_EQ(r9, v);
    EXPECT_EQ(r10, o);

    helpers.deleteBasicIntersection({i, v, h, o});
};

// Test Crossing
TEST(IntersectionSuite, CrossingTests) {
    // Test Cross all directions while light is green
    auto [i, v, h, oR] = helpers.getBasicIntersection(2, 2);
    auto [oL, oT, oB] = helpers.exstendBasicIntersection(i);


    auto [_1, r1] = i->cross(v,  Pos(-1, -1), Direction::LEFT);
    auto [_2, r2] = i->cross(v,  Pos(-1, -1), Direction::RIGHT);
    auto [_3, r3] = i->cross(v,  Pos(-1, -1), Direction::TOP);
    auto [_4, r4] = i->cross(v,  Pos(-1, -1), Direction::BOTTOM);
    EXPECT_EQ(r1, oL);
    EXPECT_EQ(r2, oR);
    EXPECT_EQ(r3, oT);
    EXPECT_EQ(r4, oB);

    // Test Cross all direction while light is red'
    auto [_5, r5] = i->cross(h,  Pos(-1, -1), Direction::LEFT);
    auto [_6, r6] = i->cross(h,  Pos(-1, -1), Direction::RIGHT);
    auto [_7, r7] = i->cross(h,  Pos(-1, -1), Direction::TOP);
    auto [_8, r8] = i->cross(h,  Pos(-1, -1), Direction::BOTTOM);
    EXPECT_EQ(r5, h);
    EXPECT_EQ(r6, h);
    EXPECT_EQ(r7, h);
    EXPECT_EQ(r8, h);

    // Test crossing when road is full
    oR->moveVehicle(Pos(1, 0), 1);
    auto [_9, r9] = i->cross(v,  Pos(-1, -1), Direction::RIGHT);
    EXPECT_EQ(r9, v);


    delete oL;
    delete oT;
    delete oB;
    helpers.deleteBasicIntersection({i, v, h, oR});
};

// Test Seriaralize
TEST(IntersectionSuite, TestSerialize) {
    auto [i, v, h, o] = helpers.getBasicIntersection(2, 2);
    auto [data, roads] = i->serialize();

    EXPECT_EQ(data[0], 0);
    EXPECT_EQ(data[1], 0);
    EXPECT_EQ(data[2], 2);
    EXPECT_EQ(data[3], 2);
    EXPECT_EQ(data[4], 1);
    
    EXPECT_EQ(roads[0], v);
    EXPECT_EQ(roads[1], nullptr);
    EXPECT_EQ(roads[2], h);
    EXPECT_EQ(roads[3], nullptr);
    EXPECT_EQ(roads[4], nullptr);
    EXPECT_EQ(roads[5], nullptr);
    EXPECT_EQ(roads[6], nullptr);
    EXPECT_EQ(roads[7], o);

    helpers.deleteBasicIntersection({i, v, h, o});

};

// Test Data Collection
TEST(IntersectionSuite, TestDataCollection) {
    auto [i, v, h, o] = helpers.getBasicIntersection(2, 2);
    i->cross(v,  Pos(-1, -1), Direction::RIGHT);
    i->cross(v,  Pos(-1, -1), Direction::RIGHT);
    helpers.updateIntersection(i, 2);
    i->cross(h,  Pos(-1, -1), Direction::RIGHT);
    helpers.updateIntersection(i, 12);
    i->cross(h,  Pos(-1, -1), Direction::RIGHT);
    i->update();

    // Test small range
    IntersectionData data1 = i->getIntersectionData(1);
    EXPECT_TRUE(data1 == IntersectionData(0, 1, 1, 1));

    // Test that data is kept between calls
    IntersectionData data2 = i->getIntersectionData(1);
    EXPECT_TRUE(data2 == IntersectionData(0, 1, 1, 1));

    // Test full range
    IntersectionData data3 = i->getIntersectionData(15);
    EXPECT_TRUE(data3 == IntersectionData(2, 2, 1, 1));

    // Test invalid range
    IntersectionData data4 = i->getIntersectionData(100);
    EXPECT_TRUE(data4 == IntersectionData(2, 2, 1, 1));

    // Test that is cycles through 
    helpers.updateIntersection(i, 121);
    IntersectionData data5 = i->getIntersectionData(10);
    EXPECT_TRUE(data5 == IntersectionData(0, 0, 1, 1));

    helpers.deleteBasicIntersection({i, v, h, o});
};