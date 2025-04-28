#include "fpsTracker.h"

FPSTracker:: FPSTracker(GLFWwindow* window) : window(window) {};

void FPSTracker::update() {
    frameCount += 1;
    float time = glfwGetTime();
    if (time - lastCall >= updateTime) {
        std::stringstream windowTitle;
        windowTitle << "Traffic Optimizer FPS: " << static_cast<int>(frameCount);
        glfwSetWindowTitle(window, windowTitle.str().c_str());
        lastCall = time;
        frameCount = 0;
    }
}