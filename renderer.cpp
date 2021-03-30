#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "inc_ogl.h"


GLuint gen_VBO (std::vector<GLfloat> vertices)
{
	GLuint VBO;
    glGenBuffers(1, &VBO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 
    	sizeof(GLfloat) * vertices.size(),
    	vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return VBO;
}

GLuint gen_VAO (GLuint VBO)
{
	GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    	3 * sizeof(GLfloat), (void*)0);
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
    glBindVertexArray(0);

    return VAO;
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
    	std::cout << "ERROR::SHADER::CAN\'T_OPEN_FILE" 
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

GLuint link_program ()
{
	
}

GLuint gen_shader_prog (
	std::string vertex_path, 
	std::string fragment_path)
{
	GLint success;
	GLchar infoLog[512];

	std::string vertex_src;
	get_shader_source(&vertex_src, vertex_path);
	GLuint vert = compile_shader(vertex_src, GL_VERTEX_SHADER);

	std::string fragment_src;
	get_shader_source(&fragment_src, fragment_path);
	GLuint frag = compile_shader(fragment_src, GL_FRAGMENT_SHADER);

	GLuint shader_prog = glCreateProgram();
	glAttachShader(shader_prog, vert);
	glAttachShader(shader_prog, frag);
	glLinkProgram(shader_prog);
	glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_prog, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vert);
	glDeleteShader(frag);

	return shader_prog;
}

void draw (renderer_info info)
{
	glUseProgram(info.shader_prog);
	glBindVertexArray(info.VAO);
	glEnableVertexAttribArray(0);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glUseProgram(0);
}