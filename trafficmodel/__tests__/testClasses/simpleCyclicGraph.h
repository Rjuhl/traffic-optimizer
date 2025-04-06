#pragma once
#include "road.h"
#include "intersection.h"
#include <vector>

class SimpleCyclicGraph {
    /*
        ###############
        ###0-------0###
        ####\#####/####
        ######\#/######
        #######0#######
        ###############
    */

    private:
        std::vector<Road*> roads;
        std::vector<Intersection*> intersections;

    public:
        SimpleCyclicGraph();
        ~SimpleCyclicGraph();
        std::vector<Road*> getRoads();
};