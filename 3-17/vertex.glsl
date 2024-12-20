#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 in_Color;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
out vec3 out_Color;

void main(void) 
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0); 

	out_Color = in_Color;
}