#include "config.h"
#include "model/road.h"
#include "utils/node.h"

class Astar {
    private:
        Direction directions[4];
        std::tuple<int, std::vector<Direction>> reconstructPath(Node* start, Node* end);
    public:
        Astar();

        std::tuple<int, std::vector<Direction>>  astar(Road* beginning, Road* finish);
};
