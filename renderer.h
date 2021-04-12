#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>

#include "inc_ogl.h"

class c_render_info {
	public:

	GLuint VBO;
	GLuint VAO;
	GLuint shader_prog;

	c_render_info ();
	~c_render_info ();

	void gen_VBO (std::vector<GLfloat> vertices);

	void gen_VAO ();

	void gen_shader_prog (
		std::string vertex_path, 
		std::string fragment_path); 

	void draw ();
};

// struct renderer_info {
// 	GLuint VBO;
// 	GLuint VAO;
// 	GLuint shader_prog;
// };

// GLuint gen_VBO (std::vector<GLfloat> vertices);

// GLuint gen_VAO (GLuint VBO);

// GLuint gen_shader_prog (
// 	std::string vertex_path, 
// 	std::string fragment_path); 

// void draw (renderer_info info);

#endif