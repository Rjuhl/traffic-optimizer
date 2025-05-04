#pragma once
#include "config.h"
#include "rectangleMesh.h"

struct TransformComponent {
    glm::vec2 position;
    glm::vec2 eulers;
    float scale;
};

struct MeshComponent {
    RectangleMesh vertexes;
    // PixelMap pixelColors;
};

struct ObjectComponent {
    MeshComponent mesh;
    TransformComponent transform;
};