#include <gtest/gtest.h>
#include "road.h"
#include "pos.h"
#include "astar.h"
#include "config.h"
#include "helpers.h"
#include "intersection.h"
#include <tuple>


// // Simple Test Graph
// class SimpleCyclicGraph {
//     /*
//         ###############
//         ###0-------0###
//         ####\#####/####
//         ######\#/######
//         #######0#######
//         ###############
//     */

//     private:
//         std::vector<Road*> roads;
//         std::vector<Intersection*> intersections;

//     public:
//         SimpleCyclicGraph() {
//             // Create three intersections
//             for (int i = 0; i < 3; i++) {
//                 intersections.push_back(new Intersection(Pos(0, 0), 1, 1, false));
//             }

//             // Create roads
//             Road* r0 = new Road(Pos(0, 0), Pos(0, 3), intersections[0]);
//             Road* r1 = new Road(Pos(0, 3), Pos(8, 3), intersections[1]);
//             Road* r2 = new Road(Pos(8, 3), Pos(0, 3), intersections[0]);
//             Road* r3 = new Road(Pos(0, 3), Pos(4, 0), intersections[2]);
//             Road* r4 = new Road(Pos(4, 0), Pos(0, 3), intersections[0]);
//             Road* r5 = new Road(Pos(4, 0), Pos(8, 3), intersections[1]);
//             Road* r6 = new Road(Pos(8, 3), Pos(4, 0), intersections[2]);

//             //Link roads to intersections
//             intersections[0]->assignOutgoingRoad(r1, Direction::RIGHT);
//             intersections[0]->assignOutgoingRoad(r3, Direction::BOTTOM);
//             intersections[0]->assignIncomingRoad(r0, Direction::LEFT);
//             intersections[0]->assignIncomingRoad(r2, Direction::RIGHT);
//             intersections[0]->assignIncomingRoad(r4, Direction::BOTTOM);
//             intersections[1]->assignOutgoingRoad(r2, Direction::LEFT);
//             intersections[1]->assignOutgoingRoad(r6, Direction::BOTTOM);
//             intersections[1]->assignIncomingRoad(r1, Direction::LEFT);
//             intersections[1]->assignIncomingRoad(r5, Direction::BOTTOM);
//             intersections[2]->assignOutgoingRoad(r4, Direction::LEFT);
//             intersections[2]->assignOutgoingRoad(r5, Direction::RIGHT);
//             intersections[2]->assignIncomingRoad(r3, Direction::LEFT);
//             intersections[2]->assignIncomingRoad(r6, Direction::RIGHT);

//             //Add roads to roads vecotor
//             roads = {r0, r1, r2, r3, r4, r5, r6};
//         }
        
//         ~SimpleCyclicGraph() {
//             for (int i = 0; i < intersections.size(); i++) {
//                 delete intersections[i];
//             }

//             for (int i = 0; i < roads.size(); i++) {
//                 delete roads[i];
//             }
//         }

//         std::vector<Road*> getRoads() { return roads; }

// };

// // Simple Test Graph
// class SimpleAcyclicGraph {
//     /*
//         ##################
//         ###0----------0###
//         ####\########/####
//         ######\####/######
//         #######0--0#######
//         ##################
//     */

//     private:
//         std::vector<Road*> roads;
//         std::vector<Intersection*> intersections;

//     public:
//         SimpleAcyclicGraph() {
//             // Create three intersections
//             for (int i = 0; i < 4; i++) {
//                 intersections.push_back(new Intersection(Pos(0, 0), 1, 1, false));
//             }

//             // Create roads
//             Road* r0 = new Road(Pos(0, 0), Pos(0, 3), intersections[0]);
//             Road* r1 = new Road(Pos(0, 3), Pos(10, 3), intersections[1]);
//             Road* r2 = new Road(Pos(0, 3), Pos(4, 0), intersections[2]);
//             Road* r3 = new Road(Pos(4, 0), Pos(6, 0), intersections[3]);
//             Road* r4 = new Road(Pos(10, 3), Pos(6, 0), intersections[3]);
//             Road* r5 = new Road(Pos(6, 0), Pos(10, 3), intersections[1]);

//             //Link roads to intersections
//             intersections[0]->assignIncomingRoad(r0, Direction::BOTTOM);
//             intersections[0]->assignOutgoingRoad(r1, Direction::RIGHT);
//             intersections[0]->assignOutgoingRoad(r2, Direction::BOTTOM);
//             intersections[1]->assignIncomingRoad(r1, Direction::LEFT);
//             intersections[1]->assignIncomingRoad(r5, Direction::BOTTOM);
//             intersections[1]->assignOutgoingRoad(r4, Direction::BOTTOM);
//             intersections[2]->assignOutgoingRoad(r3, Direction::RIGHT);
//             intersections[3]->assignIncomingRoad(r4, Direction::TOP);
//             intersections[3]->assignOutgoingRoad(r5, Direction::TOP);

//             //Add roads to roads vecotor
//             roads = {r0, r1, r2, r3, r4, r5};
//         }
        
//         ~SimpleAcyclicGraph() {
//             for (int i = 0; i < intersections.size(); i++) {
//                 delete intersections[i];
//             }

//             for (int i = 0; i < roads.size(); i++) {
//                 delete roads[i];
//             }
//         }

//         std::vector<Road*> getRoads() { return roads; }

// };

// Test Single Node
TEST(AStarSuite, SingleRoad) {
    Astar pathFinder = Astar();
    Intersection* intersection = new Intersection(Pos(0, 0), 1, 1, false);
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
TEST(AstartSuite, InvalidEndNode) {
    SimpleAcyclicGraph graph = helpers.getSimpleAcyclicGraph();
    Intersection* seperateIntersection = new Intersection(Pos(0, 0), 1, 1, false);
    Road* seperateRoad = new Road(Pos(20, 20), Pos(20, 21), seperateIntersection);
    Astar pathFinder = Astar();

    std::cout << "Testing that no path is found with invalid end node" << std::endl;

    // Try to reach an end node not in the graph
    auto [cost, path] = pathFinder.astar(graph.getRoads()[0], seperateRoad);
    std::cout << "Cost " << cost << std::endl;
    std::cout << "Path size " << path.size() << std::endl;
    helpers.printDirections(path);

    EXPECT_EQ(cost, -1);
    EXPECT_EQ(path.size(), 0);

    // Try to reach a node that is impossiable to reach in the graph
    auto [cost2, path2] = pathFinder.astar(graph.getRoads()[2], graph.getRoads()[1]);
    std::cout << "Cost " << cost2 << std::endl;
    std::cout << "Path size " << path2.size() << std::endl;
    helpers.printDirections(path2);

    EXPECT_EQ(cost2, -1);
    EXPECT_EQ(path2.size(), 0);

    std::cout << std::endl;

    delete seperateRoad;
    delete seperateIntersection;
}

// Test invalid start node
TEST(AstartSuite, InvalidStartNode) {
    // Test a start node not in the graph
    SimpleAcyclicGraph graph = helpers.getSimpleAcyclicGraph();
    Intersection* seperateIntersection = new Intersection(Pos(0, 0), 1, 1, false);
    Road* seperateRoad = new Road(Pos(20, 20), Pos(20, 21), seperateIntersection);
    Astar pathFinder = Astar();

    auto [cost, path] = pathFinder.astar(seperateRoad, graph.getRoads()[0]);
    EXPECT_EQ(cost, -1);
    EXPECT_EQ(path.size(), 0);

    delete seperateRoad;
    delete seperateIntersection;
}

// Test simple graph
TEST(AstarSuite, SimpleGraphTests) {
    SimpleCyclicGraph cyclicGraph = helpers.getSimpleCyclicGraph();
    SimpleAcyclicGraph acyclicGraph = helpers.getSimpleAcyclicGraph();
    std::vector<Road*> roads = cyclicGraph.getRoads();
    std::vector<Road*> roads2 = acyclicGraph.getRoads();
    Astar pathFinder = Astar();

    std::cout << "Testing if shortest path is found between to valid roads with a simple network" << std::endl;
    auto [cost, path] = pathFinder.astar(roads[0], roads[2]);
    std::cout << "Cost " << cost << std::endl;
    std::cout << "Path size " << path.size() << std::endl;
    helpers.printDirections(path);

    EXPECT_EQ(11, cost);
    EXPECT_EQ(std::vector<Direction>({Direction::RIGHT, Direction::LEFT}), path);

    auto [cost2, path2] = pathFinder.astar(roads2[0], roads2[4]);
    std::cout << "Cost " << cost2 << std::endl;
    std::cout << "Path size " << path2.size() << std::endl;
    helpers.printDirections(path2);

    EXPECT_EQ(13, cost2);
    EXPECT_EQ(std::vector<Direction>({Direction::RIGHT, Direction::BOTTOM}), path2);

    auto [cost3, path3] = pathFinder.astar(roads2[0], roads2[5]);
    std::cout << "Cost " << cost3 << std::endl;
    std::cout << "Path size " << path3.size() << std::endl;
    helpers.printDirections(path3);

    EXPECT_EQ(10, cost3);
    EXPECT_EQ(std::vector<Direction>({
        Direction::BOTTOM, Direction::RIGHT, Direction::TOP
    }), path3);

    std::cout << std::endl;
}

// Test large graph (Complete once editor/saver/loader are complete)