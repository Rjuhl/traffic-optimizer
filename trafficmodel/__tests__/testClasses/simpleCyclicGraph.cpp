#include "simpleCyclicGraph.h"

SimpleCyclicGraph::SimpleCyclicGraph() {
    // Create three intersections
    for (int i = 0; i < 3; i++) {
        intersections.push_back(new Intersection(Pos(0, 0), 1, 1, false));
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

SimpleCyclicGraph::~SimpleCyclicGraph() {
    for (int i = 0; i < intersections.size(); i++) {
        delete intersections[i];
    }

    for (int i = 0; i < roads.size(); i++) {
        delete roads[i];
    }
}

std::vector<Road*> SimpleCyclicGraph::getRoads() { return roads; }
