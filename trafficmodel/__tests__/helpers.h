#pragma once
#include "directions.h"
#include "road.h"
#include "intersection.h"
#include "simpleAcyclicGraph.h"
#include "simpleCyclicGraph.h"
#include "vehicle.h"
#include <vector>

class DebugHelpers {
    public:
        void printDirections(std::vector<Direction> directions);

        std::tuple<Intersection*, Road*, Road*, Road*> getBasicIntersection(int vertCount, int horCount);
        std::tuple<Road*, Road*, Road*> exstendBasicIntersection(Intersection* basicIntersection);
        void deleteBasicIntersection(std::tuple<Intersection*, Road*, Road*, Road*> pointers);
        void updateIntersection(Intersection* interesection, int times);

        SimpleCyclicGraph getSimpleCyclicGraph();
        SimpleAcyclicGraph getSimpleAcyclicGraph();

        void vehicleUpdate(Vehicle* vehicle, int timeSteps);
};

extern DebugHelpers helpers;