#include "utils/pos.h"

Pos::Pos(float x, float y) : x(x), y(y) {};
Pos::~Pos() {};

void Pos::update(float u_x, float u_y) {
    x = u_y;
    y = u_y;
}