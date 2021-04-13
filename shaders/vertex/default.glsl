# version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

out vec3 v_colour;

void main ()
{
	v_colour = colour;
	gl_Position = vec4(pos, 1.0);
}