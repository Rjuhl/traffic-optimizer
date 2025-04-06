#include "helpers.h"

DebugHelpers helpers = DebugHelpers();

void DebugHelpers::printDirections(std::vector<Direction> directions) {
    std::cout << "Directions ";
    for (int i = 0; i < directions.size(); i++) {
        Direction direction = directions[i];
        switch (direction) {
            case Direction::TOP: std::cout << "Top "; break;
            case Direction::BOTTOM: std::cout << "Bottom "; break;
            case Direction::LEFT: std::cout << "Left "; break;
            case Direction::RIGHT: std::cout << "Right "; break;
            default: std::cout << "Unknown "; break;
        }
    }
    std::cout << std::endl;
};

std::tuple<Intersection*, Road*, Road*, Road*> DebugHelpers::getBasicIntersection(int vertCount, int horCount) {
    Intersection* intersection = new Intersection(Pos(0, 0), vertCount, horCount, true);
    Road* vertical = new Road(Pos(1, 1), Pos(1, 0), intersection);
    Road* horizontal = new Road(Pos(0, 0), Pos(1, 0), intersection);
    Road* outgoing = new Road(Pos(1, 0), Pos(2, 0), intersection);
    intersection->assignIncomingRoad(vertical, Direction::TOP);
    intersection->assignIncomingRoad(horizontal, Direction::LEFT);
    intersection->assignOutgoingRoad(outgoing, Direction::RIGHT);
    return {intersection, vertical, horizontal, outgoing};
};

std::tuple<Road*, Road*, Road*> DebugHelpers::exstendBasicIntersection(Intersection* basicIntersection) {
    Road* left = new Road(Pos(1, 0), Pos(0, 0), basicIntersection);
    Road* top = new Road(Pos(1, 0), Pos(1, 1), basicIntersection);
    Road* bottom = new Road(Pos(1, 0), Pos(1, -1), basicIntersection);
    basicIntersection->assignOutgoingRoad(left, Direction::LEFT);
    basicIntersection->assignOutgoingRoad(top, Direction::TOP);
    basicIntersection->assignOutgoingRoad(bottom, Direction::BOTTOM);
    return {left, top, bottom};
};

void DebugHelpers::deleteBasicIntersection(std::tuple<Intersection*, Road*, Road*, Road*> pointers) {
    delete std::get<1>(pointers);
    delete std::get<2>(pointers);
    delete std::get<3>(pointers);
    delete std::get<0>(pointers);
};

void DebugHelpers::updateIntersection(Intersection* interesection, int times) {
    for (int i = 0; i < times; i++) {interesection->update(); };
};

SimpleCyclicGraph DebugHelpers::getSimpleCyclicGraph() { return SimpleCyclicGraph(); };
SimpleAcyclicGraph DebugHelpers::getSimpleAcyclicGraph() { return SimpleAcyclicGraph(); };

void DebugHelpers::vehicleUpdate(Vehicle* vehicle, int timeSteps) {
    for (int i = 0; i < timeSteps; i++) { 
        vehicle->updatePos(); 
        vehicle->move();
    };    
};
