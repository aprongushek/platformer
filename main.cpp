#include <iostream>
#include <conio.h>
#include <vector>

#include "inc_ogl.h"
#include "renderer.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
}

int main ()
{
	if (!glfwInit()) {
		std::cout << "Failed to initialise GLFW" << std::endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	int width = 800;
	int height = 600;
	GLFWwindow* window = glfwCreateWindow(width, height, "game", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback); 
	  
	glViewport(0, 0, width, height);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	c_render_info info;

	std::vector<GLfloat> vertices = {
		-0.5, 0.5, 0.0,
		-0.5, -0.5, 0.0,
		0.5, -0.5, 0.0,
		0.5, 0.5, 0.0,
	};

	info.gen_VBO(vertices);
	info.gen_VAO();
	info.gen_shader_prog(
		"e:\\proj\\platformer\\shaders\\vertex\\default.glsl",
		"e:\\proj\\platformer\\shaders\\fragment\\default.glsl");
 
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
 
        info.draw();
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwTerminate();
    return 0;
}