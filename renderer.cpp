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

GLuint gen_VAO (std::vector<GLfloat> vertices)
{
	GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 
    	sizeof(GLfloat) * vertices.size(),
    	vertices.data(), GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    	3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
    glBindVertexArray(0);

    return VAO;
}

GLuint gen_shader_prog (
	std::string vertex_path, 
	std::string fragment_path)
{
	GLint success;
	GLchar infoLog[512];

	std::string vertex_src = "";
	std::ifstream in(vertex_path.c_str());
    if (in.is_open())
    {
    	std::string tmp;
    	// std::cout << "Vertex shader:" << std::endl;
        while (getline(in, tmp))
        {
            // std::cout << tmp << std::endl;
            vertex_src += '\n' + tmp;
        }
        // std::cout << std::endl;
    } else {
    	std::cout << "ERROR::SHADER::VERTEX::CAN\'T OPEN FILE\n" << vertex_path << std::endl;
    }
    in.close(); 
    const GLchar *vertex_ptr = vertex_src.c_str();
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertex_ptr, NULL);
	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vert, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	std::string fragment_src = "";
	in.open(fragment_path.c_str());
    if (in.is_open())
    {
    	std::string tmp;
    	// std::cout << "Fragment shader:" << std::endl;
        while (getline(in, tmp))
        {
            // std::cout << tmp << std::endl;
            fragment_src += '\n' + tmp;
        }
        // std::cout  << std::endl;
    } else {
    	std::cout << "ERROR::SHADER::FRAGMENT::CAN\'T OPEN FILE\n" << fragment_path << std::endl;
    }
    in.close(); 
    const GLchar *fragment_ptr = fragment_src.c_str();
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragment_ptr, NULL);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(frag, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

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
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	
	glBindVertexArray(0);
	glUseProgram(0);
}