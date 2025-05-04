#pragma once
#include "config.h"
#include "pos.h"

class RectangleMesh {
    private:

        unsigned int TILE_SIZE = 64;
        unsigned int ELEM_COUNT = 6;
        unsigned int EBO, VBO, VAO;
        unsigned int UV_MIN, UV_MAX;

        std::vector<float> uvMinMax;
        std::vector<float> vertices;
        std::vector<int> indicies;

        std::vector<float> getUVMinMax(
            int textureId, int textWidth, int textHeight
        );

        void bindVAO();
    public:
        RectangleMesh(
            Pos p1, Pos p2,
            float w, float z, bool isRepeating,
            int textureId, int textWidth, int textHeight,
            unsigned int UV_MIN, unsigned int UV_MAX
        );
        RectangleMesh(
            Pos p, 
            float h, float w, float z, 
            int textureId, int textWidth, int textHeight,
            unsigned int UV_MIN, unsigned int UV_MAX
        );
        ~RectangleMesh();

        void draw();

        std::vector<float> getVertices();
        std::vector<int> getIndicies();
        
};