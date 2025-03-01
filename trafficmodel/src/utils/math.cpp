#include "config.h"
#include "math.h"
#include "utils/pos.h"

float euclideanDistance(Pos p1, Pos p2) {
    return std::sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
}
