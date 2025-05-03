#include "rectangleMesh.h"
#include "mymath.h"

RectangleMesh::RectangleMesh(Pos p1, Pos p2, float w, float z, int textureId) {
    float M = (p2.y - p1.y) / (p2.x - p1.x);
    float Z = -1 / M;
    float Xbar = std::sqrt(std::pow(w / 2.0, 2) / (1 + std::pow(M, 2)));
    float Ybar =  Z * Xbar;
    float repeat = euclideanDistance(p1, p2) / w;

    // vertices = {
    //     // Pos                        uv      uMin    uMax 
    //     p1.x + Xbar, p1.y + Ybar, z,  0.f, 0.f,
    //     p1.x - Xbar, p1.y - Ybar, z,  repeat, 0.f,  
    //     p2.x + Xbar, p2.y + Ybar, z,  repeat, 1.f,
    //     p2.x - Xbar, p2.y - Ybar, z,  0.f, 1.f,
    // };

    vertices = {
        p1.x + Xbar, p1.y + Ybar, z, 
        p1.x - Xbar, p1.y - Ybar, z, 
        p2.x + Xbar, p2.y + Ybar, z, 
        p2.x - Xbar, p2.y - Ybar, z
    };

    indicies = {
        0, 1, 3, 0, 3, 2
    };

    bindVAO();
};

RectangleMesh::RectangleMesh(Pos p, float h, float w, float z, int textureId) {
    float Xbar = w / 2;
    float Ybar = h / 2;

    vertices = {
        p.x - Xbar, p.y - Ybar, z,
        p.x - Xbar, p.y + Ybar, z,
        p.x + Xbar, p.y + Ybar, z,
        p.x + Xbar, p.y - Ybar, z
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

void RectangleMesh::bindVAO() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //position
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(int), indicies.data(), GL_STATIC_DRAW);
};

void RectangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, ELEM_COUNT, GL_UNSIGNED_INT, 0);
};

std::vector<float> RectangleMesh::getVertices() { return vertices; };
std::vector<int> RectangleMesh::getIndicies() {return indicies; };