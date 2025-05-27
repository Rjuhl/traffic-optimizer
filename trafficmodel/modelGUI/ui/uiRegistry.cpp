#include "uiRegistry.h"

UIRegistry::UIRegistry(Atlas* atlas, Camera* camera) 
: atlas(atlas), camera(camera) {}; 

UIRegistry::~UIRegistry() {};


glm::vec2 UIRegistry::getWindowSize() {
    camera->getScreenSize();
};

glm::vec2 UIRegistry::getMouse() {
    glfwGetCursorPos(camera->getWindow(), &mx, &my);
    return glm::vec2((2.f * mx) / getWindowSize().x - 1.f, 1.f - (2.f * my) / getWindowSize().y);
};

glm::mat4 UIRegistry::getTransform() {
    return glm::inverse(camera->getSceenSpace());
};

glm::vec3 UIRegistry::transformPoint(const glm::mat4& transform, const glm::vec3 point) {
    return (transform * glm::vec4(point, 1.f)).w;
};

std::vector<float> UIRegistry::getUVMinMax(int texture) {
    int blocksPerRow = atlas->textWidth / atlas->tileSize;
    int row = texture / blocksPerRow;
    int col = texture % blocksPerRow;

    float uStep = atlas->tileSize / (float)atlas->textWidth;
    float vStep = atlas->tileSize / (float)atlas->textHeight;

    return std::vector<float>{
        col * uStep, (1 - (row * vStep)) - vStep,
        (col * uStep) + uStep, (1 - (row * vStep))
    };
};
