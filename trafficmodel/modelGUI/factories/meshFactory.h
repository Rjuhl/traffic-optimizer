#pragma once
#include "pos.h"
#include "textureConstants.h"


class MeshFactory {
    private:
        int textWidth, textHeight;
        unsigned int UV_MIN, UV_MAX;
    public:
        MeshFactory();
        ~MeshFactory();

        void makeRectangle(Pos p1, Pos p2, float width);
};