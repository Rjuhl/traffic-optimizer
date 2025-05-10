#include "App.h"
#include "shaders.h"
#include "rectangleMesh.h"
#include "pos.h"
#include "guiHelpers.h"
#include "camera.h"
#include "fpsTracker.h"
#include "meshFactory.h"
#include "textureConstants.h"
#include "atlas.h"
#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

App::App() {};

int App::run(){
    std::cout << "In Main" << std::endl;

    GLFWwindow* window;
    if (glfwWindowInit(&window) != 0) return -1;

    //load shaders
    unsigned int shader = make_shader(
		"../trafficmodel/modelGUI/shaders/GPU/vertex.txt", 
		"../trafficmodel/modelGUI/shaders/GPU/fragment.txt"
	);
    glUseProgram(shader);

    //Create camera
    Camera* camera = new Camera(window, shader);
    FPSTracker* windowTitle = new FPSTracker(window);

    //Create texture map
    Atlas* atlas = new Atlas("../trafficmodel/modelGUI/shaders/textures/texture_map.png", shader, 64.f);
  
    // Create mesh factory
    MeshFactory* meshFactory = new MeshFactory(atlas);

    // Create some sample objects
    RectangleMesh* rect3 = meshFactory->makeDestination(Pos(0,6));
    RectangleMesh* rect1 = meshFactory->makeTwoWayRoad(Pos(-1, 0), Pos(-9, 0));
    RectangleMesh* rect4 = meshFactory->makeCar(Pos(-3, 0), Pos(-1, 0), Pos(-9, 0), 1);
    RectangleMesh* rect2 = meshFactory->makeCar(Pos(-7, 0), Pos(-9, 0), Pos(-1, 0), 2);
    RectangleMesh* rect5 = meshFactory->makeTwoWayRoad(Pos(0,-8), Pos(8, 0));
    RectangleMesh* rect6 = meshFactory->makeCar(Pos(4, -4), Pos(0, -8), Pos(8, 0), 0);

    std::vector<RectangleMesh*> renderables = {rect1, rect3, rect2, rect4, rect5, rect6};

    // Create Renderer 
    Renderer* renderer = new Renderer(camera, shader);
    for (auto rect : renderables) {
        renderer->addGameObj(rect);
    }

    //Init delta time 
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader);

        renderer->renderFrame(deltaTime);

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
    delete renderer;

    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
};

int App::glfwWindowInit(GLFWwindow** window) {
    if(!glfwInit()){
        std::cout << "GLFW would not start" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    *window = glfwCreateWindow(640, 480, "Traffic Optimizer FPS: ...", NULL, NULL);
    glfwMakeContextCurrent(*window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Glad loader failed" << std::endl;
        return -1;
    }

    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Set the rendering region to the actual screen size
	int w,h;
	glfwGetFramebufferSize(*window, &w, &h);
	// (left, top, width, height)
	glViewport(0,0,w,h);
    return 0;
};