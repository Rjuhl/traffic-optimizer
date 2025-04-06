#include "simpleAcyclicGraph.h"

SimpleAcyclicGraph::SimpleAcyclicGraph() {
    // Create three intersections
    for (int i = 0; i < 4; i++) {
        intersections.push_back(new Intersection(Pos(0, 0), 1, 1, false));
    }

    // Create roads
    Road* r0 = new Road(Pos(0, 0), Pos(0, 3), intersections[0]);
    Road* r1 = new Road(Pos(0, 3), Pos(10, 3), intersections[1]);
    Road* r2 = new Road(Pos(0, 3), Pos(4, 0), intersections[2]);
    Road* r3 = new Road(Pos(4, 0), Pos(6, 0), intersections[3]);
    Road* r4 = new Road(Pos(10, 3), Pos(6, 0), intersections[3]);
    Road* r5 = new Road(Pos(6, 0), Pos(10, 3), intersections[1]);

    //Link roads to intersections
    intersections[0]->assignIncomingRoad(r0, Direction::BOTTOM);
    intersections[0]->assignOutgoingRoad(r1, Direction::RIGHT);
    intersections[0]->assignOutgoingRoad(r2, Direction::BOTTOM);
    intersections[1]->assignIncomingRoad(r1, Direction::LEFT);
    intersections[1]->assignIncomingRoad(r5, Direction::BOTTOM);
    intersections[1]->assignOutgoingRoad(r4, Direction::BOTTOM);
    intersections[2]->assignOutgoingRoad(r3, Direction::RIGHT);
    intersections[3]->assignIncomingRoad(r4, Direction::TOP);
    intersections[3]->assignOutgoingRoad(r5, Direction::TOP);

    //Add roads to roads vecotor
    roads = {r0, r1, r2, r3, r4, r5};
}

SimpleAcyclicGraph::~SimpleAcyclicGraph() {
    for (int i = 0; i < intersections.size(); i++) {
        delete intersections[i];
    }

    for (int i = 0; i < roads.size(); i++) {
        delete roads[i];
    }
}

std::vector<Road*> SimpleAcyclicGraph::getRoads() { return roads; }
