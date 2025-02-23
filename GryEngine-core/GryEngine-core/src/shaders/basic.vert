#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 colour;

uniform mat4 projection_matrix;
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out DATA
{
	out vec4 position;
	out vec4 colour;
} vs_out;

void main()
{
	gl_Position = projection_matrix * view_matrix * model_matrix * position;
	vs_out.position = model_matrix * position;
	vs_out.colour = colour;
}