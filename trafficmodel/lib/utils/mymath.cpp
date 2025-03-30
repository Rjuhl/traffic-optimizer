#include "config.h"
#include "mymath.h"
#include "utils/pos.h"

float euclideanDistance(const Pos& p1, const Pos& p2) {
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

float euclideanEstimate(Pos p1, Pos p2) {
    return 1.f;
}