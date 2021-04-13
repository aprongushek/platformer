#include <string>
#include <fstream>
#include <iostream>

#include "ogl.h"
#include "shader.h"

c_shader::c_shader () :
	vert (0), geom (0), frag (0), program (0)
{ }

c_shader::~c_shader ()
{
	glDeleteProgram(program);
}

void get_shader_source (std::string *src, std::string path)
{
	*src = "";
	std::ifstream in;
	in.open(path.c_str());
    if (in.is_open()) {
    	std::string tmp;
        while (getline(in, tmp)) {
            *src += '\n' + tmp;
        }
    } else {
    	std::cout << "ERROR::SHADER::CAN\'T_OPEN_FILE\n" 
    		<< path << '\n';
    }
    in.close();
}

GLuint compile_shader (std::string src, GLenum type)
{
	GLint success;
	GLchar info[512];

	const GLchar *ptr = src.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &ptr, NULL);
	glCompileShader(shader);
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" 
			<< info << std::endl;
	}

	return shader;
}

void c_shader::attach_shader (std::string path, GLenum type)
{
	std::string src;
	get_shader_source(&src, path);

	switch (type) {
		case GL_VERTEX_SHADER:
			vert = compile_shader(src, type);
			break;
		case GL_GEOMETRY_SHADER:
			geom = compile_shader(src, type);
			break;
		case GL_FRAGMENT_SHADER:
			frag = compile_shader(src, type);
			break;
	}
}

void c_shader::link_program ()
{
	GLint success;
	GLchar infoLog[512];

	program = glCreateProgram();
	if (vert != 0)
		glAttachShader(program, vert);
	if (geom != 0)
		glAttachShader(program, geom);
	if (frag != 0)
		glAttachShader(program, frag);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" 
		<< infoLog << std::endl;
	}

	glDeleteShader(vert);
	glDeleteShader(geom);
	glDeleteShader(frag);
}

void c_shader::attach_uniform (std::string name, 
	e_uniform_types type, GLuint size, void *src)
{
	s_uniform uniform;
	uniform.location = glGetUniformLocation(program,
		name.c_str());
	uniform.type = type;
	uniform.size = size;
	uniform.src = src;

	uniforms.push_back(uniform);
}

void c_shader::use ()
{
	glUseProgram(program);

	for (int i = 0; i < uniforms.size(); i++)
		switch (uniforms[i].type) {
			case VEC_1F:
				glUniform1fv(uniforms[i].location,
					uniforms[i].size, 
					(GLfloat *)uniforms[i].src);
				break;
			case VEC_3F:
				glUniform3fv(uniforms[i].location,
					uniforms[i].size, 
					(GLfloat *)uniforms[i].src);
				break;
			case VEC_4F:
				glUniform4fv(uniforms[i].location,
					uniforms[i].size, 
					(GLfloat *)uniforms[i].src);
				break;
		}
}