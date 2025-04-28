#pragma once
#include "config.h"

class Camera {
    private:
        GLFWwindow* window;
        unsigned int viewLocation;
        unsigned int projectionLocation;
        glm::vec3 cameraPos = {0.0f, 0.0f, 5.0f};
        glm::vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
        glm::vec3 up = {0.0f, 1.0f, 0.0f};
        glm::vec3 rotation(0.f);
        float scale = 1;

    public:
        Camera(GLFWwindow* window, unsigned int viewLocation, unsigned int projectionLocation);
}       void update(float deltaTime);
