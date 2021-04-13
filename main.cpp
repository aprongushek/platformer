#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <cmath>

#include "ogl.h"
#include "renderer.h"
#include "shader.h"

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

	std::vector<GLfloat> vertex_data = {
		-0.5, 0.5, 0.0, 	// vertex 1
		1.0, 1.0, 1.0, 		// colour 1
		-0.5, -0.5, 0.0, 	// vertex 2
		1.0, 0.0, 0.0,		// colour 2
		0.5, -0.5, 0.0, 	// vertex 3
		0.0, 1.0, 0.0,		// colour 3
		0.5, 0.5, 0.0, 		// vertex 4
		0.0, 0.0, 1.0		// colour 4
	};

	std::vector<GLuint> attrib_sizes;
	attrib_sizes.push_back(3);
	attrib_sizes.push_back(3);

	info.gen_VBO(vertex_data);
	info.gen_VAO(attrib_sizes, 6);
	// info.gen_shader_prog(
	// 	"shaders\\vertex\\default.glsl",
	// 	"shaders\\fragment\\default.glsl");

	c_shader shader;
	shader.attach_shader("shaders\\vertex\\default.glsl", 
		GL_VERTEX_SHADER);
	shader.attach_shader("shaders\\fragment\\default.glsl", 
		GL_FRAGMENT_SHADER);
	shader.link_program();

	GLfloat transp = sin((float)clock()/(float)CLOCKS_PER_SEC)
		* 0.5 + 0.5;
	shader.attach_uniform("transparency", VEC_1F, 1, &transp);

	info.shader = &shader;
 
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
 
        info.draw();
 
        glfwSwapBuffers(window);
        glfwPollEvents();

        transp = sin((float)clock()/(float)CLOCKS_PER_SEC)
		* 0.5 + 0.5;
    }
 
    glfwTerminate();
    return 0;
}