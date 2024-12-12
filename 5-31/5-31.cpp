#define _CRT_SECURE_NO_WARNINGS 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

void InitBuffer();
void InitTexture();
void BackgroundBuffer();
void drawBackground();
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid SpecialKeyboardUp(int key, int x, int y);
GLvoid TimerFunction(int value);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

char* filetobuf(const char* file);

GLfloat vPositionList[] = {
	-0.25, -0.25, -0.5,  0.25, -0.25, -0.5,  -0.25, 0.25, -0.5,   0.25, -0.25, -0.5,  0.25, 0.25, -0.5,  -0.25, 0.25, -0.5,
	-0.25, 0.25, -0.5,  0.25, 0.25, -0.5,  -0.25, 0.25, 0.0,   0.25, 0.25, -0.5,  0.25, 0.25, 0.0,  -0.25, 0.25, 0.0,
	-0.25, 0.25, 0.0,  0.25, 0.25, 0.0,  -0.25, -0.25, 0.0,   0.25, 0.25, 0.0,   0.25, -0.25, 0.0,   -0.25, -0.25, 0.0,
	-0.25, -0.25, 0.0,  0.25, -0.25, 0.0,  -0.25, -0.25, -0.5,   0.25, -0.25, 0.0,  0.25, -0.25, -0.5,  -0.25, -0.25, -0.5,
	-0.25, -0.25, -0.5,  -0.25, 0.25, -0.5,  -0.25, -0.25, 0.0,   -0.25, -0.25, 0.0,  -0.25, 0.25, -0.5,  -0.25, 0.25, 0.0,
	0.25, 0.25, -0.5,  0.25, -0.25, -0.5,  0.25, 0.25, 0.0,   0.25, 0.25, 0.0,  0.25, -0.25, -0.5,  0.25, -0.25, 0.0,

	-0.25, -0.25, -0.5,  0.25, -0.25, -0.5,  0.25, -0.25, 0.0,  -0.25, -0.25, -0.5,  0.25, -0.25, 0.0,  -0.25, -0.25, 0.0,

	-0.25, -0.25, -0.5,  0.25, -0.25, -0.5,  0.0, 0.25, -0.25,
	0.25, -0.25, -0.5,  0.25, -0.25, 0.0,  0.0, 0.25, -0.25,
	0.25, -0.25, 0.0,  -0.25, -0.25, 0.0,  0.0, 0.25, -0.25,
	-0.25, -0.25, 0.0,  -0.25, -0.25, -0.5,  0.0, 0.25, -0.25,
};

GLfloat colors[] = {
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   0.0, 1.0, 0.0,  1.0, 1.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,   1.0, 1.0, 1.0,  0.0, 1.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   0.0, 1.0, 0.0,  1.0, 1.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,   1.0, 1.0, 1.0,  0.0, 1.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  0.0, 0.0, 1.0,   1.0, 0.0, 0.0,
	1.0, 1.0, 1.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  0.0, 1.0, 0.0,   1.0, 1.0, 1.0,

	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   1.0, 0.0, 0.0,  0.0, 0.0, 1.0,   1.0, 1.0, 1.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
	0.0, 1.0, 0.0,  0.0, 0.0, 1.0,  1.0, 1.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,
	1.0, 1.0, 1.0,  1.0, 0.0, 0.0,  0.0, 1.0, 0.0
};

GLfloat vertexData[] = {

	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,

	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	1.0, 1.0,  0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0, 1.0, 1.0
};

GLfloat backgroundVertices[] = {
	-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
	 1.0f,  1.0f, 0.0f,  1.0f, 1.0f
};

GLuint VAO, VBO_pos[3];
unsigned int textures[6];
BITMAPINFO* bmpInfo;
GLuint bgVAO, bgVBO;
unsigned int backgroundTexture;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.5f);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view = glm::mat4(1.0f);

int check = 0, xRotate = 0, yRotate = 0;

float a = 0.0, b = 0.0, c = 0.0, d = 0.0;

bool hide, object, up, left, down, right;

int main(int argc, char** argv)
{
	width = 800;
	height = 800;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example");

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutTimerFunc(10, TimerFunction, 1);

	InitBuffer();
	InitTexture();
	BackgroundBuffer();
	make_vertexShaders();
	make_fragmentShaders();
	shaderProgramID = make_shaderProgram();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMainLoop();
}

GLvoid drawScene()
{
	GLfloat rColor, gColor, bColor;

	rColor = bColor = gColor = 0.8;
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");
	int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
	int projLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");

	glUseProgram(shaderProgramID);

	glm::mat4 identityMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(identityMatrix));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(identityMatrix));
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(identityMatrix));

	glDisable(GL_DEPTH_TEST);
	drawBackground();
	glEnable(GL_DEPTH_TEST);

	glUseProgram(0);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(-1.0, -0.005, 1.0, 0.005);
	glRectf(-0.005, -1.0, 0.005, 1.0);
	glEnable(GL_TEXTURE_2D);

	glUseProgram(shaderProgramID);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vPositionList), vPositionList);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[2]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexData), vertexData);

	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Ty = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 TR = glm::mat4(1.0f);

	Tx = glm::translate(Tx, glm::vec3(a, 0.0, 0.0));
	Ty = glm::translate(Ty, glm::vec3(0.0, b, 0.0));
	Rx = glm::rotate(Rx, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0));
	TR = Tx * Ty * Rx * Ry;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));

	glm::mat4 Nx = glm::mat4(1.0f);
	glm::mat4 Ny = glm::mat4(1.0f);
	glm::mat4 NR = glm::mat4(1.0f);

	Nx = glm::rotate(Nx, glm::radians(c), glm::vec3(1.0, 0.0, 0.0));
	Ny = glm::rotate(Ny, glm::radians(d), glm::vec3(0.0, 1.0, 0.0));
	NR = Nx * Ny * TR;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(NR));

	glm::mat4 vTransform = glm::mat4(1.0f);
	vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &vTransform[0][0]);

	glm::mat4 pTransform = glm::mat4(1.0f);

	pTransform = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 50.0f);
	pTransform = glm::translate(pTransform, glm::vec3(0.0, 0.0, -2.0));

	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &pTransform[0][0]);

	if (check == 1)
	{
		if (!object)
		{
			for (int i = 0; i < 6; i++)
			{
				glBindTexture(GL_TEXTURE_2D, textures[i]);
				glDrawArrays(GL_TRIANGLES, i * 6, 6);
			}
		}

		else if (object)
		{
			glDrawArrays(GL_LINE_LOOP, 0, 36);
		}
	}

	else if (check == 2)
	{
		if (!object)
		{
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glDrawArrays(GL_TRIANGLES, 36, 6);

			for (int i = 0; i < 4; i++)
			{
				glBindTexture(GL_TEXTURE_2D, textures[i + 1]);
				glDrawArrays(GL_TRIANGLES, i * 3 + 42, 3);
			}
		}

		else if (object)
		{
			glDrawArrays(GL_LINE_LOOP, 36, 18);
		}
	}

	glutSwapBuffers();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		check = 1;
		break;
	case 'p':
		check = 2;
		break;
	case 'h':
		if (!hide)
		{
			glEnable(GL_DEPTH_TEST);


			hide = true;
		}

		else if (hide)
		{
			glDisable(GL_DEPTH_TEST);

			hide = false;
		}
		break;
	case 'w':
		object = true;
		break;
	case 'W':
		object = false;
		break;
	case 'x':
		xRotate = 1;
		break;
	case 'X':
		xRotate = -1;
		break;
	case 'y':
		yRotate = 1;
		break;
	case 'Y':
		yRotate = -1;
		break;
	case 's':
		a = 0.0;
		b = 0.0;
		c = 0.0;
		d = 0.0;
		xRotate = 0;
		yRotate = 0;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		up = true;
		break;
	case GLUT_KEY_LEFT:
		left = true;
		break;
	case GLUT_KEY_DOWN:
		down = true;
		break;
	case GLUT_KEY_RIGHT:
		right = true;
		break;
	}

	glutPostRedisplay();
}

GLvoid SpecialKeyboardUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		up = false;
		break;
	case GLUT_KEY_LEFT:
		left = false;
		break;
	case GLUT_KEY_DOWN:
		down = false;
		break;
	case GLUT_KEY_RIGHT:
		right = false;
		break;
	}

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (up)
	{
		b += 0.01;
	}

	if (left)
	{
		a -= 0.01;
	}

	if (down)
	{
		b -= 0.01;
	}

	if (right)
	{
		a += 0.01;
	}

	if (xRotate == 1)
	{
		c += 1.0;
	}

	else if (xRotate == -1)
	{
		c -= 1.0;
	}

	if (yRotate == 1)
	{
		d += 1.0;
	}

	else if (yRotate == -1)
	{
		d -= 1.0;
	}

	glutPostRedisplay();

	glutTimerFunc(10, TimerFunction, 1);
}

void InitBuffer()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(3, VBO_pos);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
}

void InitTexture()
{
	glGenTextures(6, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width1, height1, channels1;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data1 = stbi_load("Block (1).png", &width1, &height1, &channels1, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data1);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width2, height2, channels2;
	unsigned char* data2 = stbi_load("Block (3).png", &width2, &height2, &channels2, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data2);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width3, height3, channels3;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data3 = stbi_load("Block (5).png", &width3, &height3, &channels3, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data3);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width4, height4, channels4;
	unsigned char* data4 = stbi_load("Block (11).png", &width4, &height4, &channels4, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width4, height4, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data4);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width5, height5, channels5;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data5 = stbi_load("Block (14).png", &width5, &height5, &channels5, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width5, height5, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data5);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width6, height6, channels6;
	unsigned char* data6 = stbi_load("Block (15).png", &width6, &height6, &channels6, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width6, height6, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data6);

	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int texWidth, texHeight, texChannels;
	unsigned char* image = stbi_load("Background (2).png", &texWidth, &texHeight, &texChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image);
}

void BackgroundBuffer()
{
	glGenVertexArrays(1, &bgVAO);
	glGenBuffers(1, &bgVBO);

	glBindVertexArray(bgVAO);

	glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(backgroundVertices), backgroundVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawBackground()
{
	glUseProgram(shaderProgramID);
	glBindVertexArray(bgVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glUniform1i(glGetUniformLocation(shaderProgramID, "backgroundTexture"), 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
}

void make_vertexShaders()
{
	GLchar* vertexSource;
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader error\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	fragmentSource = filetobuf("fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader error\n" << errorLog << std::endl;
		return;
	}
}

GLuint make_shaderProgram()
{
	GLuint shaderID;
	make_vertexShaders();
	make_fragmentShaders();
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program error\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(shaderID);

	return shaderID;
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;
	return buf;
}

GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE* fp;
	GLubyte* bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(fp);
		return NULL;
	}

	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	if ((bits = (unsigned char*)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}