#include <gtest/gtest.h>
#include "road.h"
#include "pos.h"
#include "astar.h"
#include "config.h"
#include "helpers.h"
#include "intersection.h"
#include <tuple>

DebugHelpers helpers = DebugHelpers();

// Simple Test Graph
class SimpleCyclicGraph {
    /*
        ###############
        ###0-------0###
        ####\#####/####
        ######\#/######∏
        #######0#######
        ###############
    */

    private:
        std::vector<Road*> roads;
        std::vector<Intersection*> intersections;

    public:
        SimpleCyclicGraph() {
            // Create three intersections
            for (int i = 0; i < 3; i++) {
                intersections.push_back(new Intersection(1, 1, false));
            }

            // Create roads
            Road* r0 = new Road(Pos(0, 0), Pos(0, 3), intersections[0]);
            Road* r1 = new Road(Pos(0, 3), Pos(8, 3), intersections[1]);
            Road* r2 = new Road(Pos(8, 3), Pos(0, 3), intersections[0]);
            Road* r3 = new Road(Pos(0, 3), Pos(4, 0), intersections[2]);
            Road* r4 = new Road(Pos(4, 0), Pos(0, 3), intersections[0]);
            Road* r5 = new Road(Pos(4, 0), Pos(8, 3), intersections[1]);
            Road* r6 = new Road(Pos(8, 3), Pos(4, 0), intersections[2]);

            //Link roads to intersections
            intersections[0]->assignOutgoingRoad(r1, Direction::RIGHT);
            intersections[0]->assignOutgoingRoad(r3, Direction::BOTTOM);
            intersections[0]->assignIncomingRoad(r0, Direction::LEFT);
            intersections[0]->assignIncomingRoad(r2, Direction::RIGHT);
            intersections[0]->assignIncomingRoad(r4, Direction::BOTTOM);
            intersections[1]->assignOutgoingRoad(r2, Direction::LEFT);
            intersections[1]->assignOutgoingRoad(r6, Direction::BOTTOM);
            intersections[1]->assignIncomingRoad(r1, Direction::LEFT);
            intersections[1]->assignIncomingRoad(r5, Direction::BOTTOM);
            intersections[2]->assignOutgoingRoad(r4, Direction::LEFT);
            intersections[2]->assignOutgoingRoad(r5, Direction::RIGHT);
            intersections[2]->assignIncomingRoad(r3, Direction::LEFT);
            intersections[2]->assignIncomingRoad(r6, Direction::RIGHT);

            //Add roads to roads vecotor
            roads = {r0, r1, r2, r3, r4, r5, r6};
        }
        
        ~SimpleCyclicGraph() {
            for (int i = 0; i < intersections.size(); i++) {
                delete intersections[i];
            }

            for (int i = 0; i < roads.size(); i++) {
                delete roads[i];
            }
        }

        std::vector<Road*> getRoads() { return roads; }

};


// Test Single Node
TEST(AStarSuite, SingleRoad) {
    Astar pathFinder = Astar();
    Intersection* intersection = new Intersection(1, 1, false);
    Road* start = new Road(Pos(1, 1), Pos(2, 2), intersection);
    
    std::tuple<int, std::vector<Direction>> shortestPath = pathFinder.astar(start, start);
    std::vector<Direction> path = std::get<1>(shortestPath);
    
    int cost = std::get<0>(shortestPath);

    EXPECT_EQ(cost, 0);
    EXPECT_EQ(path.size(), 0);

    delete start;
    delete intersection;
}


// Test invalid end node

// Test invalid start node

// Test simple graph
TEST(AstarSuite, SimpleGraphTests) {
    SimpleCyclicGraph graph = SimpleCyclicGraph();
    std::vector<Road*> roads = graph.getRoads();
    Astar pathFinder = Astar();

    std::cout << "Testing if shortest path is found between to valid roads with a simple network" << std::endl;
    auto [cost, path] = pathFinder.astar(roads[0], roads[2]);

    std::cout << "Cost " << cost << std::endl;
    std::cout << "Path size " << path.size() << std::endl;
    helpers.printDirections(path);


    EXPECT_EQ(1, 2);
}

// Test medium graph

// Test large graph