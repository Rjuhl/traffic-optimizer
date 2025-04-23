#pragma once
#include "config.h"

struct Rectangle {

}

struct TransformComponent {
    glm::vec2 position;
    glm::vec2 eulers;
    float scale;
}

struct PixelMap {

}

struct MeshComponent {
    Rectangle vetexes;
    PixelMap pixelColors;
}

struct ObjectComponent {
    MeshComponent mesh;
    TransformComponent transform;
}