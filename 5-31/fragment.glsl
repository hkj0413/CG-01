#version 330 core

in vec3 Normal;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D outTexture;

void main(void) 
{
	//FragColor = vec4 (Normal, 1.0);

	FragColor = texture (outTexture, TexCoord);
}