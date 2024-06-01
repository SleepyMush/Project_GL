#version 460 core
layout (location = 0) in vec3 position;

uniform mat4 model[100];
uniform mat4 view;
uniform mat4 projection;
flat out int index;

void main()
{
	gl_Position = projection * view * model[gl_InstanceID] * vec4(position, 1.0);
	index = gl_InstanceID;
}

