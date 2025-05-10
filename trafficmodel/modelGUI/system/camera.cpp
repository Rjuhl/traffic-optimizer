#include "camera.h"

Camera::Camera(GLFWwindow* window, unsigned int shader) : 
window(window), shader(shader),
screenspaceLocation(glGetUniformLocation(shader, "screenspace")) {
    glfwGetFramebufferSize(window, &width, &height);
};

void Camera::update(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cameraPos.y += 1.f * scale * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cameraPos.y -= 1.f * scale * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cameraPos.x += 1.f * scale * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cameraPos.x -= 1.f * scale * deltaTime;
    }


    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        scale -= 10.f * deltaTime;
        scale = std::max(scale, 10.f);
    }

    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        scale += 10.f * deltaTime;
        scale = std::min(scale, 1000.f);
    }

    
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        rotation.z += 30.f * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        rotation.z -= 30.f * deltaTime;
    }

    cameraTarget = cameraPos;
    cameraTarget.z = 0.f;
    cameraPos.z = scale;

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) reset();

    glm::mat4 view = glm::rotate(glm::lookAt(cameraPos, cameraTarget, up), glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    glm::mat4 projection = glm::ortho(-scale, scale, -scale, scale, 0.1f, scale);
    screenspace = projection * view;

    glUniformMatrix4fv(screenspaceLocation, 1, GL_FALSE, glm::value_ptr(screenspace));
};

void Camera::setUIView() {
    glm::mat4 ortho = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height)); 
    glUniformMatrix4fv(screenspaceLocation, 1, GL_FALSE, glm::value_ptr(ortho));
}

void Camera::reset() {
    scale = 10.f;
    cameraPos = {0.0f, 0.0f, scale};
    cameraTarget = {0.0f, 0.0f, 0.0f};
    up = {0.0f, 1.0f, 0.0f};
    rotation = {0.0f, 0.0f, 0.0f};
};

GLFWwindow* Camera::getWindow() { return window; };
glm::mat4 Camera::getScreenSpace() { return screenspace; };
glm::vec2 Camera::getScreenSize() { return glm::vec2(width, height); };