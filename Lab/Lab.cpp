#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>

void InitBuffer();
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

char* filetobuf(const char* file);

GLfloat vPositionList[10][12] = {};
GLfloat colors[10][12] = {};
GLint index[10][6] = {};
GLuint VAO, VBO_pos[2], EBO;

void drawing(GLfloat vPositionList[10][12], GLfloat colors[10][12], GLint index[10][6], float ox, float oy, int ultimate, int check);

std::random_device rd;
std::mt19937 mt(rd());

float ox = 0.0, oy = 0.0;

int ultimate = 0, check[10] = {}, shadow = 0, superior = 0;

bool execute = false, nightmare = false;

int main(int argc, char** argv)
{
	width = 800;
	height = 800;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(Mouse);
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

	glBindBuffer(GL_ARRAY_BUFFER, EBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(index), index);

	for (int i = 0; i < ultimate; i++)
	{
		if (check[i] == 1)
		{
			glPointSize(10.0);
			glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 6));
		}

		else if (check[i] == 2)
		{
			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 6));
		}
		
		else if (check[i] == 3)
		{
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 6));
		}

		else if (check[i] == 4)
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 6));
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
	case 'p':
		check[ultimate] = 1;

		execute = true;
		break;
	case 'l':
		check[ultimate] = 2;

		execute = true;
		break;
	case 't':
		check[ultimate] = 3;

		execute = true;
		break;
	case 'r':
		check[ultimate] = 4;

		execute = true;
		break;
	case 'w':
		if (!nightmare)
		{
			std::uniform_int_distribution<int> chance(0, superior);

			shadow = chance(mt);

			glutTimerFunc(10, TimerFunction, 1);

			nightmare = true;
		}
		break;
	case 'a':
		if (!nightmare)
		{
			std::uniform_int_distribution<int> chance(0, superior);

			shadow = chance(mt);

			glutTimerFunc(10, TimerFunction, 2);

			nightmare = true;
		}
		break;
	case 's':
		if (!nightmare)
		{
			std::uniform_int_distribution<int> chance(0, superior);

			shadow = chance(mt);

			glutTimerFunc(10, TimerFunction, 3);

			nightmare = true;
		}
		break;
	case 'd':
		if (!nightmare)
		{
			std::uniform_int_distribution<int> chance(0, superior);

			shadow = chance(mt);

			glutTimerFunc(10, TimerFunction, 4);

			nightmare = true;
		}
		break;
	case 'c':
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				index[i][j] = 0;
			}
		}

		ultimate = 0;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		if (nightmare)
		{

			nightmare = false;
		}
		break;
	case 'a':
		if (nightmare)
		{

			nightmare = false;
		}
		break;
	case 's':
		if (nightmare)
		{

			nightmare = false;
		}
		break;
	case 'd':
		if (nightmare)
		{

			nightmare = false;
		}
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	ox = (float)(x - 400.0) / 400.0;
	oy = -(float)(y - 400.0) / 400.0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && execute)
	{
		drawing(vPositionList, colors, index, ox, oy, ultimate, check[ultimate]);

		ultimate++;

		superior = ultimate - 1;

		execute = false;
	}
}

GLvoid TimerFunction(int value)
{
	glutPostRedisplay();

	if (value == 1 && nightmare)
	{
		if (check[shadow] == 1)
		{
			vPositionList[shadow][1] += 0.01;
		}

		else if (check[shadow] == 2)
		{
			vPositionList[shadow][1] += 0.01;
			vPositionList[shadow][4] += 0.01;
		}

		else if (check[shadow] == 3)
		{
			vPositionList[shadow][1] += 0.01;
			vPositionList[shadow][4] += 0.01;
			vPositionList[shadow][7] += 0.01;
		}

		else if (check[shadow] == 4)
		{
			vPositionList[shadow][1] += 0.01;
			vPositionList[shadow][4] += 0.01;
			vPositionList[shadow][7] += 0.01;
			vPositionList[shadow][10] += 0.01;
		}

		glutTimerFunc(10, TimerFunction, 1);
	}

	else if (value == 2 && nightmare)
	{
		if (check[shadow] == 1)
		{
			vPositionList[shadow][0] -= 0.01;
		}

		else if (check[shadow] == 2)
		{
			vPositionList[shadow][0] -= 0.01;
			vPositionList[shadow][3] -= 0.01;
		}

		else if (check[shadow] == 3)
		{
			vPositionList[shadow][0] -= 0.01;
			vPositionList[shadow][3] -= 0.01;
			vPositionList[shadow][6] -= 0.01;
		}

		else if (check[shadow] == 4)
		{
			vPositionList[shadow][0] -= 0.01;
			vPositionList[shadow][3] -= 0.01;
			vPositionList[shadow][6] -= 0.01;
			vPositionList[shadow][9] -= 0.01;
		}

		glutTimerFunc(10, TimerFunction, 2);
	}

	else if (value == 3 && nightmare)
	{
		if (check[shadow] == 1)
		{
			vPositionList[shadow][1] -= 0.01;
		}

		else if (check[shadow] == 2)
		{
			vPositionList[shadow][1] -= 0.01;
			vPositionList[shadow][4] -= 0.01;
		}

		else if (check[shadow] == 3)
		{
			vPositionList[shadow][1] -= 0.01;
			vPositionList[shadow][4] -= 0.01;
			vPositionList[shadow][7] -= 0.01;
		}

		else if (check[shadow] == 4)
		{
			vPositionList[shadow][1] -= 0.01;
			vPositionList[shadow][4] -= 0.01;
			vPositionList[shadow][7] -= 0.01;
			vPositionList[shadow][10] -= 0.01;
		}

		glutTimerFunc(10, TimerFunction, 3);
	}

	else if (value == 4 && nightmare)
	{
		if (check[shadow] == 1)
		{
			vPositionList[shadow][0] += 0.01;
		}

		else if (check[shadow] == 2)
		{
			vPositionList[shadow][0] += 0.01;
			vPositionList[shadow][3] += 0.01;
		}

		else if (check[shadow] == 3)
		{
			vPositionList[shadow][0] += 0.01;
			vPositionList[shadow][3] += 0.01;
			vPositionList[shadow][6] += 0.01;
		}

		else if (check[shadow] == 4)
		{
			vPositionList[shadow][0] += 0.01;
			vPositionList[shadow][3] += 0.01;
			vPositionList[shadow][6] += 0.01;
			vPositionList[shadow][9] += 0.01;
		}

		glutTimerFunc(10, TimerFunction, 4);
	}
}

void drawing(GLfloat vPositionList[10][12], GLfloat colors[10][12], GLint index[10][6], float ox, float oy, int ultimate, int check)
{
	if (check == 1)
	{
		vPositionList[ultimate][0] = ox;
		vPositionList[ultimate][1] = oy;

		colors[ultimate][2] = 1.0;

		index[ultimate][0] = ultimate * 4;
	}

	else if (check == 2)
	{
		vPositionList[ultimate][0] = ox - 0.1;
		vPositionList[ultimate][1] = oy;
		vPositionList[ultimate][3] = ox + 0.1;
		vPositionList[ultimate][4] = oy;

		colors[ultimate][1] = 1.0;
		colors[ultimate][4] = 1.0;

		index[ultimate][0] = ultimate * 4;
		index[ultimate][1] = ultimate * 4 + 1;
	}

	else if (check == 3)
	{
		vPositionList[ultimate][0] = ox;
		vPositionList[ultimate][1] = oy + 0.1;
		vPositionList[ultimate][3] = ox - 0.1;
		vPositionList[ultimate][4] = oy - 0.14;
		vPositionList[ultimate][6] = ox + 0.1;
		vPositionList[ultimate][7] = oy - 0.14;

		colors[ultimate][0] = 1.0;
		colors[ultimate][3] = 1.0;
		colors[ultimate][6] = 1.0;

		index[ultimate][0] = ultimate * 4;
		index[ultimate][1] = ultimate * 4 + 1;
		index[ultimate][2] = ultimate * 4 + 2;
	}

	else if (check == 4)
	{
		vPositionList[ultimate][0] = ox - 0.1;
		vPositionList[ultimate][1] = oy + 0.1;
		vPositionList[ultimate][3] = ox - 0.1;
		vPositionList[ultimate][4] = oy - 0.1;
		vPositionList[ultimate][6] = ox + 0.1;
		vPositionList[ultimate][7] = oy - 0.1;
		vPositionList[ultimate][9] = ox + 0.1;
		vPositionList[ultimate][10] = oy + 0.1;

		colors[ultimate][0] = 1.0;
		colors[ultimate][4] = 1.0;
		colors[ultimate][8] = 1.0;
		colors[ultimate][9] = 1.0;
		colors[ultimate][10] = 1.0;
		colors[ultimate][11] = 1.0;

		index[ultimate][0] = ultimate * 4;
		index[ultimate][1] = ultimate * 4 + 1;
		index[ultimate][2] = ultimate * 4 + 2;
		index[ultimate][3] = ultimate * 4;
		index[ultimate][4] = ultimate * 4 + 2;
		index[ultimate][5] = ultimate * 4 + 3;
	}
}

void InitBuffer()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO_pos);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
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