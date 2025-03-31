#include "config.h"
#include "model/road.h"
#include "utils/pos.h"
#include "enums/directions.h"
#include "model/intersection.h"
#include "utils/mymath.h"
#include "utils/astar.h"
#include "utils/node.h"
#include <tuple>
#include <queue>

Astar::Astar() : directions{Direction::LEFT, Direction::RIGHT, Direction::TOP, Direction::BOTTOM} {};

std::tuple<int, std::vector<Direction>> Astar::reconstructPath(Node* start, Node* end) {
    int cost = end->cost;
    std::vector<Direction> path;
    while (end->road != start->road) {
        path.push_back(end->dir);
        end = end->parent;
    }
    std::reverse(path.begin(), path.end());
    return std::tuple<int, std::vector<Direction>>(cost, path);
}

std::tuple<int, std::vector<Direction>> Astar::astar(Road* beginning, Road* finish) {
    Node* start = new Node();
    std::unordered_map<Road*, Node*> seen;
    std::priority_queue<Node*, std::vector<Node*>, Node::ComparePointers> nodeHeap;
    
    start->cost = 0;
    start->road = beginning;
    start->dir = Direction::NONE;
    seen[start->road] = start;
    nodeHeap.push(start);

    while (!nodeHeap.empty()) {
        Node* current = nodeHeap.top();
        nodeHeap.pop();

        if (current->road == finish) { return reconstructPath(start, current); }

        for (Direction direction : directions) {
            Node* neighbior = new Node();
            Road* neighbiorRoad = current->road->getIntersection()->link(direction);

            // Check for a nullptr which means there is not a road in that direction
            if (neighbiorRoad == nullptr) { continue; }

            if (seen.count(neighbiorRoad) > 0) {
                neighbior = seen[neighbiorRoad];
            }
            
            neighbior->road = neighbiorRoad;
            seen[neighbior->road] = neighbior;
            auto test = neighbior->road->getStart();

            //  Check if the new path is shorter and update info if so
            if (neighbior->cost > current->cost + current->road->length()) {
                neighbior->cost = current->cost + current->road->length();
                neighbior->heuristic = neighbior->cost + euclideanDistance(neighbior->road->getStart(), finish->getStart());
                neighbior->parent = current;
                neighbior->dir = direction;
            }

            // If node is not fully explored add it to the heap
            if (!neighbior->fullyExplored) {
                nodeHeap.push(neighbior);
            }

        }

        //Mark node as fully explored
        current->fullyExplored = true;
    }

    return  std::tuple<int, std::vector<Direction>>(-1, std::vector<Direction>());
};