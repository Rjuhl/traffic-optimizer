#pragma once
#include "config.h"
#include "road.h"

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

    struct ComparePointers {
        bool operator()(const Node* a, const Node* b) const {
            return *a > *b;  
        }
    };
};