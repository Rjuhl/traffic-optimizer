#pragma once
#include "road.h"
#include "intersection.h"
#include <vector>

// Simple Test Graph
class SimpleAcyclicGraph {
    /*
        ##################
        ###0----------0###
        ####\########/####
        ######\####/######
        #######0--0#######
        ##################
    */

    private:
        std::vector<Road*> roads;
        std::vector<Intersection*> intersections;

    public:
        SimpleAcyclicGraph();
        ~SimpleAcyclicGraph();
        std::vector<Road*> getRoads();
};