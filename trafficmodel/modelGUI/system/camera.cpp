#include "camera.h"

Camera::Camera(GLFWwindow* window, unsigned int viewLocation, unsigned int projectionLocation) : 
window(window), viewLocation(viewLocation) projectionLocation(projectionLocation), {};

void Camera::update(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cameraPos.y += 0.1 * scale * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cameraPos.y -= 0.1 * scale * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cameraPos.x += 0.1 * scale * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cameraPos.x -= 0.1 * scale * deltaTime;
    }

    // if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
    //     scale *= 1.1;
    // }

    // if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
    //     rotation.z += 1.f * deltaTime;
    // }

    
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        rotation.z += 1.f * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        rotation.z -= 1.f * deltaTime;
    }

    
};