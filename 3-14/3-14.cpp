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

GLuint VAO, VBO_pos[2];

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
	glm::mat4 TR = glm::mat4(1.0f);

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glRectf(-1.0, -0.005, 1.0, 0.005);
	glRectf(-0.005, -1.0, 0.005, 1.0);

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

	if (check == 1)
	{
		if (!object)
		{
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		else if (object)
		{
			glDrawArrays(GL_LINES, 0, 36);
		}
	}

	else if (check == 2)
	{
		if (!object)
		{
			glDrawArrays(GL_TRIANGLES, 36, 18);
		}

		else if (object)
		{
			glDrawArrays(GL_LINES, 36, 18);
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