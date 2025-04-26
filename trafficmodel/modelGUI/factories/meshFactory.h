#pragma once
#include "pos.h"

class MeshFactory {
    private:
    public:
        MeshFactory();
        ~MeshFactory();

        void makeRectangle(Pos p1, Pos p2, float width);
};