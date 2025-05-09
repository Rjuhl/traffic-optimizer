#pragma once
#include "appmode.h"
#include "config.h"
#include <GLFW/glfw3.h> 
#include <string>

class App {
    private:
        int glfwWindowInit(GLFWwindow** window);
    public:
        App();
        // App(AppMode mode);
        // App(const std::string& mapPath);
        // App(AppMode mode, const std::string& mapPath);
        // ~App();

        int run();
};