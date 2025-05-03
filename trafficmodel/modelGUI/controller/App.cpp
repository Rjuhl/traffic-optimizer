#include "App.h"
#include "config.h"
#include "shaders.h"
#include "rectangleMesh.h"
#include "pos.h"
#include "guiHelpers.h"
#include "camera.h"
#include "fpsTracker.h"

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
    int textWidth, textHeight, textChannels;
    unsigned char* textureImg =  stbi_load(
        "../shaders/textures/texture_map.png", 
        &textWidth, &textHeight, &textChannels, 0
    );
    
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textWidth, textHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImg);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureImg);
    glBindTexture(GL_TEXTURE_2D, 0);


    // Create some sample objects
    RectangleMesh* rect1 = new RectangleMesh(Pos(-0.5, -0.5), Pos(0.5, 0.5), 0.25, 2.0f, 0);
    RectangleMesh* rect2 = new RectangleMesh(Pos(2, 2), 1, 0.25, 1.0f, 0);
    std::vector<RectangleMesh*> renderables = {rect1, rect2};

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

    glDeleteTextures(1, &texture);
    glDeleteProgram(shader);
    glfwTerminate();

    delete rect1;
    delete rect2;

    delete camera;
    delete windowTitle;

    return 0;
};