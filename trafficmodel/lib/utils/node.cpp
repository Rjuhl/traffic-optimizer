#include "config.h"
#include "utils/node.h"
#include <limits>

Node::Node() : 
    heuristic(std::numeric_limits<float>::max()),
    cost(std::numeric_limits<float>::max()),
    parent(nullptr), road(nullptr), dir(Direction::NONE), fullyExplored(false) {};

Node::~Node() {};

bool Node::operator>(const Node& other) const { return heuristic > other.heuristic; }

