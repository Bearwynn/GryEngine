#version 330 core

layout (location = 0) out vec4 colour;

uniform vec4 frag_colour;
uniform vec2 light_position;
uniform float light_intensity;

in vec4 pos;

void main()
{
	float intensity = 1.0f / length(pos.xy - light_position) * light_intensity;
	colour = frag_colour * intensity;
}