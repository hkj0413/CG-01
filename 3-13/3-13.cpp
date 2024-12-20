#define _CRT_SECURE_NO_WARNINGS 
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
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

char* filetobuf(const char* file);

GLfloat vPositionList[] = {
	-0.25, -0.25, -0.25,  0.25, -0.25,-0.25,  -0.25, 0.25, -0.25,   0.25, -0.25, -0.25,  0.25, 0.25, -0.25,  -0.25, 0.25, -0.25,
	-0.25, 0.25, -0.25,  0.25, 0.25, -0.25,  -0.25, 0.25, 0.25,   0.25, 0.25, -0.25,  0.25, 0.25, 0.25,  -0.25, 0.25, 0.25,
	-0.25, 0.25, 0.25,  0.25, 0.25, 0.25,  -0.25, -0.25, 0.25,   0.25, 0.25, 0.25,   0.25, -0.25, 0.25,   -0.25, -0.25, 0.25,
	-0.25, -0.25, 0.25,  0.25, -0.25, 0.25,  -0.25, -0.25, -0.25,   0.25, -0.25, 0.25,  0.25, -0.25, -0.25,  -0.25, -0.25, -0.25,
	-0.25, -0.25, -0.25,  -0.25, 0.25, -0.25,  -0.25, -0.25, 0.25,   -0.25, -0.25, 0.25,  -0.25, 0.25, -0.25,  -0.25, 0.25, 0.25,
	0.25, 0.25, -0.25,  0.25, -0.25, -0.25,  0.25, 0.25, 0.25,   0.25, 0.25, 0.25,  0.25, -0.25, -0.25,  0.25, -0.25, 0.25,
	-0.25, -0.25, 0.25,  0.25, -0.25, 0.25,  0.0, -0.25, -0.183,
	-0.25, -0.25, 0.25,  0.25, -0.25, 0.25,  0.0, 0.25, 0.0835,
	-0.25, -0.25, 0.25,  0.0, -0.25, -0.183,  0.0, 0.25, 0.0835,
	0.0, -0.25, -0.183,  0.25, -0.25, 0.25,  0.0, 0.25, 0.0835
};

GLfloat colors[] = {
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   0.0, 1.0, 0.0,  1.0, 1.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,   1.0, 1.0, 1.0,  0.0, 1.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   0.0, 1.0, 0.0,  1.0, 1.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,   1.0, 1.0, 1.0,  0.0, 1.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  0.0, 0.0, 1.0,   1.0, 0.0, 0.0,
	1.0, 1.0, 1.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  0.0, 1.0, 0.0,   1.0, 1.0, 1.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  1.0, 1.0, 1.0,
	1.0, 0.0, 0.0,  0.0, 0.0, 1.0,  1.0, 1.0, 1.0,
	0.0, 0.0, 1.0,  0.0, 1.0, 0.0,  1.0, 1.0, 1.0
};

GLuint VAO, VBO_pos[2];

int check = 0;

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

	InitBuffer();
	make_vertexShaders();
	make_fragmentShaders();
	shaderProgramID = make_shaderProgram();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid drawScene()
{
	GLfloat rColor, gColor, bColor;

	rColor = bColor = gColor = 1.0;
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramID);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vPositionList), vPositionList);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);

	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Ty = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 TR = glm::mat4(1.0f);

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glRectf(-1.0, -0.005, 1.0, 0.005);
	glRectf(-0.005, -1.0, 0.005, 1.0);

	Rx = glm::rotate(Rx, glm::radians(-10.0f), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(10.0f), glm::vec3(0.0, 1.0, 0.0));
	TR = Rx * Ry;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));

	if (check == 1 or check == 11 or check == 12 or check == 13 or check == 14 or check == 15)
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	if (check == 2 or check == 11 or check == 16 or check == 17 or check == 18 or check == 19)
	{
		glDrawArrays(GL_TRIANGLES, 6, 6);
	}

	if (check == 3 or check == 12 or check == 16 or check == 20 or check == 21 or check == 22)
	{
		glDrawArrays(GL_TRIANGLES, 12, 6);
	}

	if (check == 4 or check == 13 or check == 17 or check == 20 or check == 23 or check == 24)
	{
		glDrawArrays(GL_TRIANGLES, 18, 6);
	}

	if (check == 5 or check == 14 or check == 18 or check == 21 or check == 23 or check == 25)
	{
		glDrawArrays(GL_TRIANGLES, 24, 6);
	}

	if (check == 6 or check == 15 or check == 19 or check == 22 or check == 24 or check == 25)
	{
		glDrawArrays(GL_TRIANGLES, 30, 6);
	}

	if (check == 7 or check == 26 or check == 27 or check == 28)
	{
		glDrawArrays(GL_TRIANGLES, 36, 3);
	}

	if (check == 8 or check == 26 or check == 29 or check == 30)
	{
		glDrawArrays(GL_TRIANGLES, 39, 3);
	}

	if (check == 9 or check == 27 or check == 29 or check == 31)
	{
		glDrawArrays(GL_TRIANGLES, 42, 3);
	}

	if (check == 10 or check == 28 or check == 30 or check == 31)
	{
		glDrawArrays(GL_TRIANGLES, 45, 3);
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
	case '1':
		check = 1;
		break;
	case '2':
		check = 2;
		break;
	case '3':
		check = 3;
		break;
	case '4':
		check = 4;
		break;
	case '5':
		check = 5;
		break;
	case '6':
		check = 6;
		break;
	case '7':
		check = 7;
		break;
	case '8':
		check = 8;
		break;
	case '9':
		check = 9;
		break;
	case '0':
		check = 10;
		break;
	case 'c':
		check = fea(mt);
		break;
	case 't':
		check = mut(mt);
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}

void InitBuffer()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO_pos);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
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