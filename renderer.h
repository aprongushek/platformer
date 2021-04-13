#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>

#include "ogl.h"
#include "shader.h"

class c_render_info {
	public:

	GLuint attrib_number;
	GLuint VBO;
	GLuint VAO;
	c_shader *shader;

	c_render_info ();
	~c_render_info ();

	void gen_VBO (std::vector<GLfloat> data);
	
	void gen_VAO (std::vector<GLuint> attrib_sizes, 
		GLuint stride);
	
	// void gen_shader_prog (
	// 	std::string vertex_path, 
	// 	std::string fragment_path); 

	void draw ();
};

#endif