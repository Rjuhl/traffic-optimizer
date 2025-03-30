#include "config.h"

int viewerLoop() {

    std::cout << "In Main" << std::endl;

    GLFWwindow* window;

    if(!glfwInit()){
        std::cout << "GLFW would not start" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "test_window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Glad loader failed" << std::endl;
        return -1;
    }

    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}