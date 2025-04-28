#pragma once
#include "config.h"

class FPSTracker {
    private:
        int frameCount = 0;
        float updateTime = 1.f;
        float lastCall = 0.f;
        GLFWwindow* window;
    public:
        FPSTracker(GLFWwindow* window);
        void update();
};