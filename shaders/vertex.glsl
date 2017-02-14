#version 330 core

in vec3 vertex;

out vec4 position;

void main ( void )
{
	position = vec4(vertex, 1.0f);
}
