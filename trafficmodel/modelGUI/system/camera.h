#pragma once
#include "config.h"

class Camera {
    private:
        GLFWwindow* window;
        unsigned int viewLocation;
        unsigned int projLocation;
        glm::vec3 cameraPos = {0.0f, 0.0f, 5.0f};
        glm::vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
        glm::vec3 up = {0.0f, 1.0f, 0.0f};
        glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
        float scale = 10.f;
        
        void reset();

    public:
        Camera(GLFWwindow* window, unsigned int viewLocation, unsigned int projLocation);
        void update(float deltaTime);
};
