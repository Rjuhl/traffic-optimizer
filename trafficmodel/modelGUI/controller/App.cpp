#include "App.h"
#include "config.h"
#include "shaders.h"
#include "rectangleMesh.h"
#include "pos.h"
#include "guiHelpers.h"

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

    window = glfwCreateWindow(640, 480, "Traffic Optimizer", NULL, NULL);
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
	unsigned int view_location = glGetUniformLocation(shader, "view");
    unsigned int proj_location = glGetUniformLocation(shader, "projection");

	glm::vec3 camera_pos = {0.0f, 0.0f, 5.0f};
	glm::vec3 camera_target = {0.0f, 0.0f, 0.0f};
	glm::vec3 up = {0.0f, 1.0f, 0.0f};
	glm::mat4 view = glm::lookAt(camera_pos, camera_target, up);
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(projection));

    RectangleMesh* rect1 = new RectangleMesh(Pos(-0.5, -0.5), Pos(0.5, 0.5), 0.25, 2.0f);
    RectangleMesh* rect2 = new RectangleMesh(Pos(2, 2), 1, 0.25, 1.0f);
    std::vector<RectangleMesh*> renderables = {rect1, rect2};

    guiHelpers.printVertex(rect1->getVertices());
    guiHelpers.printVertex(rect2->getVertices());

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader);

        for (auto rect : renderables) {
            rect->draw();
        }

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    glfwTerminate();

    delete rect1;
    delete rect2;

    return 0;
};