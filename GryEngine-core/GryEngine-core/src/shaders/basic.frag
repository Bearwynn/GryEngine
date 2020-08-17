#version 330 core

layout (location = 0) out vec4 colour;

uniform vec2 light_position;
uniform vec4 frag_colour;

in DATA
{
	in vec4 position;
	in vec4 colour;
} fs_in;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_position);
	//colour = frag_colour * intensity;
	colour = fs_in.colour * intensity;
}