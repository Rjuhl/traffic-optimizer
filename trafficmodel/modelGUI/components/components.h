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

template<typename T>
struct WithId {
    uint32_t id;
    T value;
    WithId(uint32_t id, const T& value) : id(id), value(value) {};
};
