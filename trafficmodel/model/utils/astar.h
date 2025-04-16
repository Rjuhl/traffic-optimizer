#pragma once
#include "config.h"
#include "road.h"
#include "node.h"

class Astar {
    private:
        Direction directions[4];
        std::tuple<int, std::vector<Direction>> reconstructPath(Node* start, Node* end);
    public:
        Astar();
        std::tuple<int, std::vector<Direction>>  astar(Road* beginning, Road* finish);
};
