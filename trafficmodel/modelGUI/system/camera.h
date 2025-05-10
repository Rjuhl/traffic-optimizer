#pragma once
#include "config.h"

class Camera {
    private:
        GLFWwindow* window;
        int width, height;
        unsigned int shader, screenspaceLocation;
        float scale = 10.f;
        glm::mat4 screenspace;
        glm::vec3 cameraPos = {0.0f, 0.0f, scale};
        glm::vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
        glm::vec3 up = {0.0f, 1.0f, 0.0f};
        glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
        
        void reset();

    public:
        Camera(GLFWwindow* window, unsigned int shader);

        GLFWwindow* getWindow();
        glm::mat4 getScreenSpace();
        glm::vec2 getScreenSize();
        void update(float deltaTime);
        void setUIView();
};
