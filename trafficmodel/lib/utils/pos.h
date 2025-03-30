#pragma once
#include "config.h"

class Pos {
    public:
        void update(float x, float y);
        Pos(float x, float y);
        ~Pos();
        float x;
        float y;
};