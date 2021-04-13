#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "ogl.h"
#include "renderer.h"
#include "shader.h"

c_render_info::c_render_info () : 
	attrib_number (0), VAO (0), VBO (0), shader (nullptr) 
{ }

c_render_info::~c_render_info ()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void c_render_info::gen_VBO (std::vector<GLfloat> data)
{
    glGenBuffers(1, &VBO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 
    	sizeof(GLfloat) * data.size(),
    	data.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void c_render_info::gen_VAO (std::vector<GLuint> attrib_sizes,
	GLuint stride)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    attrib_number = attrib_sizes.size();

    int offset = 0;
    for (int i = 0; i < attrib_number; i++) {
    	glVertexAttribPointer(i, attrib_sizes[i], 
    		GL_FLOAT, GL_FALSE, 
    		stride * sizeof(GLfloat), 
    		(void*)(offset * sizeof(GLfloat)));
    	offset += attrib_sizes[i];
    }
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
    glBindVertexArray(0);
}

void c_render_info::draw ()
{
	// glUseProgram(shader->program);
	shader->use();
	glBindVertexArray(VAO);

	for (int i = 0; i < attrib_number; i++)
		glEnableVertexAttribArray(i);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	
	for (int i = 0; i < attrib_number; i++)
		glDisableVertexAttribArray(i);

	glBindVertexArray(0);
	glUseProgram(0);
}