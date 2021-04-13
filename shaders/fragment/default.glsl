#version 330 core

in vec3 v_colour;

out vec4 colour;

uniform float transparency;

void main()
{
	colour = vec4(v_colour.xyz * transparency, 1.0);
}