#include "rectangleMesh.h"
#include "mymath.h"
#include "guiHelpers.h"

RectangleMesh::RectangleMesh(
    Pos p1, Pos p2, 
    float w, float z, bool isRepeating, 
    int textureId, int textWidth, int textHeight,
    unsigned int UV_MIN, unsigned int UV_MAX
) : UV_MIN(UV_MIN), UV_MAX(UV_MAX)
{

    float M, Z, Xbar, Ybar, repeat;
    isRepeating ? repeat = euclideanDistance(p1, p2) / w : repeat = 1.f;
    if (std::abs(p2.y - p1.y) < 1e-6) {
        Xbar = 0.0f;
        Ybar = w / 2.0f;
    } else if (std::abs(p2.x - p1.x) < 1e-6) {
        Xbar = w / 2.0f;
        Ybar = 0.0f;
    } else {
        M = slope(p1, p2);
        Z = -1 / M;
        Xbar = std::sqrt(std::pow(w / 2.0, 2) / (1 + std::pow(Z, 2)));
        Ybar =  Z * Xbar;
    }

    uvMinMax = getUVMinMax(textureId, textWidth, textHeight);

    vertices = {                      
        p1.x + Xbar, p1.y + Ybar, z, 1.f, 0.f,   
        p1.x - Xbar, p1.y - Ybar, z, 0.f, 0.f,
        p2.x + Xbar, p2.y + Ybar, z, 1.f, repeat,
        p2.x - Xbar, p2.y - Ybar, z, 0.f, repeat
    };

    indicies = {
        0, 1, 3, 0, 3, 2
    };

    bindVAO();
};

RectangleMesh::RectangleMesh(
    Pos p, 
    float h, float w, float z, 
    int textureId, int textWidth, int textHeight,
    unsigned int UV_MIN, unsigned int UV_MAX
) : UV_MIN(UV_MIN), UV_MAX(UV_MAX)
{
    float Xbar = w / 2;
    float Ybar = h / 2;

    uvMinMax = getUVMinMax(textureId, textWidth, textHeight);

    vertices = {
        p.x - Xbar, p.y - Ybar, z, 0.f, 0.f, 
        p.x - Xbar, p.y + Ybar, z, 0.f, 1.f,
        p.x + Xbar, p.y + Ybar, z, 1.f, 1.f,
        p.x + Xbar, p.y - Ybar, z, 1.f, 0.f
    };

    indicies = {
        0, 1, 2, 0, 2, 3
    };

    bindVAO();
};


RectangleMesh::~RectangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
};

std::vector<float> RectangleMesh::getUVMinMax(int textureId, int textWidth, int textHeight) {
    int blocksPerRow = textWidth / TILE_SIZE;
    int row = textureId / blocksPerRow;
    int col = textureId % blocksPerRow;

    float uStep = (float)TILE_SIZE / (float)textWidth;
    float vStep = (float)TILE_SIZE / (float)textHeight;

    return std::vector<float>{
        col * uStep, (1 - (row * vStep)) - vStep,
        (col * uStep) + uStep, (1 - (row * vStep))
    };
}

void RectangleMesh::bindVAO() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //position
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(int), indicies.data(), GL_STATIC_DRAW);
};

void RectangleMesh::draw() {
    glBindVertexArray(VAO);
    glUniform2f(UV_MIN, uvMinMax[0], uvMinMax[1]);
    glUniform2f(UV_MAX, uvMinMax[2], uvMinMax[3]);
    glDrawElements(GL_TRIANGLES, ELEM_COUNT, GL_UNSIGNED_INT, 0);
};

std::vector<float> RectangleMesh::getVertices() { return vertices; };
std::vector<int> RectangleMesh::getIndicies() {return indicies; };