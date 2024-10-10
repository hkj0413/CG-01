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
GLvoid Mouse(int button, int state, int x, int y);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

char* filetobuf(const char* file);

GLfloat vPositionList[12][9] = {};
GLfloat colors[12][9] = {};
GLint index[12][3] = {};
GLuint VAO, VBO_pos[2], EBO;

void drawingLeft(GLfloat vPositionList[12][9], GLfloat colors[12][9], GLint index[12][3], float ox, float oy, int ultimate[4], int check[4][3]);
void drawingRight(GLfloat vPositionList[12][9], GLfloat colors[12][9], GLint index[12][3], float ox, float oy, int ultimate[4], int check[4][3]);


std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dis(0, 1);

float ox = 0.0, oy = 0.0;

int ultimate[4] = {}, check[4][3] = {}, shadow = 0;

bool execute = true, nightmare = false;

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

	glRectf(-1.0, -0.005, 1.0, 0.005);
	glRectf(-0.005, -1.0, 0.005, 1.0);

	for (int i = 0; i < 12; i++)
	{
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 3));
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
	case 'a':
		execute = true;
		break;
	case 'b':
		execute = false;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y)
{
	ox = (float)(x - 400.0) / 400.0;
	oy = -(float)(y - 400.0) / 400.0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		drawingLeft(vPositionList, colors, index, ox, oy, ultimate, check);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		drawingRight(vPositionList, colors, index, ox, oy, ultimate, check);
	}
}

void drawingLeft(GLfloat vPositionList[12][9], GLfloat colors[12][9], GLint index[12][3], float ox, float oy, int ultimate[4], int check[4][3])
{
	if (ox >= 0 && oy >= 0)
	{
		if (ultimate[0] == 0)
		{
			vPositionList[0][0] = ox;
			vPositionList[0][1] = oy + 0.1;
			vPositionList[0][3] = ox - 0.075;
			vPositionList[0][4] = oy - 0.1;
			vPositionList[0][6] = ox + 0.075;
			vPositionList[0][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[0][i] = dis(mt);
				colors[0][i + 3] = colors[0][i];
				colors[0][i + 6] = colors[0][i];
			}

			index[0][0] = 0;
			index[0][1] = 1;
			index[0][2] = 2;
		}
	}

	else if (ox < 0 && oy >= 0)
	{
		if (ultimate[1] == 0)
		{
			vPositionList[3][0] = ox;
			vPositionList[3][1] = oy + 0.1;
			vPositionList[3][3] = ox - 0.075;
			vPositionList[3][4] = oy - 0.1;
			vPositionList[3][6] = ox + 0.075;
			vPositionList[3][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[3][i] = dis(mt);
				colors[3][i + 3] = colors[3][i];
				colors[3][i + 6] = colors[3][i];
			}

			index[3][0] = 9;
			index[3][1] = 10;
			index[3][2] = 11;
		}
	}

	else if (ox < 0 && oy < 0)
	{
		if (ultimate[2] == 0)
		{
			vPositionList[6][0] = ox;
			vPositionList[6][1] = oy + 0.1;
			vPositionList[6][3] = ox - 0.075;
			vPositionList[6][4] = oy - 0.1;
			vPositionList[6][6] = ox + 0.075;
			vPositionList[6][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[6][i] = dis(mt);
				colors[6][i + 3] = colors[6][i];
				colors[6][i + 6] = colors[6][i];
			}

			index[6][0] = 18;
			index[6][1] = 19;
			index[6][2] = 20;
		}
	}

	else if (ox >= 0 && oy < 0)
	{
		if (ultimate[3] == 0)
		{
			vPositionList[9][0] = ox;
			vPositionList[9][1] = oy + 0.1;
			vPositionList[9][3] = ox - 0.075;
			vPositionList[9][4] = oy - 0.1;
			vPositionList[9][6] = ox + 0.075;
			vPositionList[9][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[9][i] = dis(mt);
				colors[9][i + 3] = colors[9][i];
				colors[9][i + 6] = colors[9][i];
			}

			index[9][0] = 27;
			index[9][1] = 28;
			index[9][2] = 29;
		}
	}
}

void drawingRight(GLfloat vPositionList[12][9], GLfloat colors[12][9], GLint index[12][3], float ox, float oy, int ultimate[4], int check[4][3])
{

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