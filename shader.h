#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <string>

#include "ogl.h"

enum e_uniform_types {
	VEC_1F,
	VEC_2F,
	VEC_3F,
	VEC_4F,
};

struct s_uniform {
	GLuint location;
	e_uniform_types type;
	GLuint size;
	void *src;
};

class c_shader {
	public:

	std::vector<s_uniform> uniforms;

	GLuint vert;
	GLuint geom;
	GLuint frag;
	GLuint program;

	c_shader ();
	~c_shader ();

	void attach_shader (std::string path, GLenum type);

	void link_program ();

	void attach_uniform (std::string name, 
		e_uniform_types type, GLuint size, void *src);

	void use ();
};

#endif