#include "camera.h"

Camera::Camera(GLFWwindow* window, unsigned int viewLocation, unsigned int projLocation) : 
window(window), viewLocation(viewLocation), projLocation(projLocation) {};

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


    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        scale /= 1.1;
        scale = std::max(scale, 10.f);
    }

    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        scale *= 1.1;
        scale = std::min(scale, 1000.f);
    }

    
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        rotation.z += 2.f * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        rotation.z -= 2.f * deltaTime;
    }

    cameraTarget = cameraPos;
    cameraTarget.z = 0.f;
    cameraPos.z = scale;
    glm::mat4 view = glm::rotate(glm::lookAt(cameraPos, cameraTarget, up), glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    glm::mat4 projection = glm::ortho(-scale, scale, -scale, scale, 0.1f, scale);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
};

void Camera::reset() {};