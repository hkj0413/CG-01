#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 in_Color;

uniform mat4 modelTransform;
out vec3 out_Color;

void main(void) 
{
	gl_Position = modelTransform * vec4(vPos, 1.0); 

	out_Color = in_Color;
}