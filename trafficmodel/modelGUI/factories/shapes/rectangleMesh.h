#pragma once
#include "config.h"
#include "pos.h"

class RectangleMesh {
    private:
        unsigned int ELEM_COUNT = 6;
        unsigned int EBO, VBO, VAO;

        std::vector<float> vertices;
        std::vector<int> indicies;

        void bindVAO();
    public:
        RectangleMesh(Pos p1, Pos p2, float w, float z, int textureId);
        RectangleMesh(Pos p, float h, float w, float z, int textureId);
        ~RectangleMesh();

        void draw();

        std::vector<float> getVertices();
        std::vector<int> getIndicies();
        
};