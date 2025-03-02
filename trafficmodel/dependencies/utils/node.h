#pragma once
#include "config.h"
#include "model/road.h"

struct Node {
    Node();
    ~Node();

    float heuristic;
    int cost;
    bool fullyExplored;

    Node* parent;
    Road* road;
    Direction dir;

    bool operator>(const Node& other) const;
};