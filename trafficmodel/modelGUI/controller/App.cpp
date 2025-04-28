#include "App.h"
#include "config.h"
#include "shaders.h"
#include "rectangleMesh.h"
#include "pos.h"
#include "guiHelpers.h"
#include "camera.h"
#include "fpsTracker.h"

App::App() {};

int App::run(){
    std::cout << "In Main" << std::endl;

    GLFWwindow* window;

    if(!glfwInit()){
        std::cout << "GLFW would not start" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(640, 480, "Traffic Optimizer FPS: ...", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Glad loader failed" << std::endl;
        return -1;
    }

    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Set the rendering region to the actual screen size
	int w,h;
	glfwGetFramebufferSize(window, &w, &h);
	// (left, top, width, height)
	glViewport(0,0,w,h);

    unsigned int shader = make_shader(
		"../trafficmodel/modelGUI/shaders/GPU/vertex.txt", 
		"../trafficmodel/modelGUI/shaders/GPU/fragment.txt"
	);
    glUseProgram(shader);

	//fetch uniform locations
	unsigned int viewLocation = glGetUniformLocation(shader, "view");
    unsigned int projLocation = glGetUniformLocation(shader, "projection");

    Camera* camera = new Camera(window, viewLocation, projLocation);
    FPSTracker* windowTitle = new FPSTracker(window);


    RectangleMesh* rect1 = new RectangleMesh(Pos(-0.5, -0.5), Pos(0.5, 0.5), 0.25, 2.0f);
    RectangleMesh* rect2 = new RectangleMesh(Pos(2, 2), 1, 0.25, 1.0f);
    std::vector<RectangleMesh*> renderables = {rect1, rect2};

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        camera->update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader);

        for (auto rect : renderables) {
            rect->draw();
        }

        windowTitle->update();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    glfwTerminate();

    delete rect1;
    delete rect2;

    delete camera;
    delete windowTitle;

    return 0;
};