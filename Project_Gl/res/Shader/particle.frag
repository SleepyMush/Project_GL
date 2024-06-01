#version 460 core
out vec4 FragColor;

uniform vec4 color[100];
flat in int index;

void main()
{
	FragColor = color[index];
}
