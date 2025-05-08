#include "App.h"
#include "config.h"
#include "shaders.h"
#include "rectangleMesh.h"
#include "pos.h"
#include "guiHelpers.h"
#include "camera.h"
#include "fpsTracker.h"
#include "meshFactory.h"
#include "textureConstants.h"
#include "atlas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

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

    //load shaders
    unsigned int shader = make_shader(
		"../trafficmodel/modelGUI/shaders/GPU/vertex.txt", 
		"../trafficmodel/modelGUI/shaders/GPU/fragment.txt"
	);
    glUseProgram(shader);

	//fetch uniform locations
	unsigned int viewLocation = glGetUniformLocation(shader, "view");
    unsigned int projLocation = glGetUniformLocation(shader, "projection");

    //Create camera
    Camera* camera = new Camera(window, viewLocation, projLocation);
    FPSTracker* windowTitle = new FPSTracker(window);

    //Create texture map
    Atlas* atlas = new Atlas("../trafficmodel/modelGUI/shaders/textures/texture_map.png", shader, 64.f);

    // Create mesh factory
    MeshFactory* meshFactory = new MeshFactory(atlas);

    // Create some sample objects
    RectangleMesh* rect3 = meshFactory->makeOneWayRoad(Pos(-8, 0), Pos(-6, 4));
    RectangleMesh* rect1 = meshFactory->makeTwoWayRoad(Pos(-1, 0), Pos(-9, 0));
    RectangleMesh* rect4 = meshFactory->makeCar(Pos(-3, 0), Pos(-1, 0), Pos(-9, 0), 1);
    RectangleMesh* rect2 = meshFactory->makeCar(Pos(-7, 0), Pos(-9, 0), Pos(-1, 0), 2);
    RectangleMesh* rect5 = meshFactory->makeTwoWayRoad(Pos(0,-8), Pos(8, 0));
    RectangleMesh* rect6 = meshFactory->makeCar(Pos(4, -4), Pos(0, -8), Pos(8, 0), 0);


    std::vector<RectangleMesh*> renderables = {rect1, rect2, rect4, rect5, rect6};

    //Init delta time 
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

    delete rect1;
    delete rect2;
    delete rect3;
    delete rect4;
    delete rect5;
    delete rect6;

    delete camera;
    delete windowTitle;
    delete atlas;
    delete meshFactory;

    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
};