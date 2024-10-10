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

void drawingLeft(GLfloat vPositionList[12][9], GLfloat colors[12][9], GLint index[12][3], float ox, float oy, int ultimate[4], int check[12]);
void drawingRight(GLfloat vPositionList[12][9], GLfloat colors[12][9], GLint index[12][3], float ox, float oy, int ultimate[4], int check[12]);


std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dis(0, 1);
std::uniform_real_distribution<float> fea(-0.1, 0.1);
std::uniform_real_distribution<float> plus(0.1, 0.9);
std::uniform_real_distribution<float> minus(-0.9, -0.1);

float ox = 0.0, oy = 0.0, nx = 0.0, ny = 0.0;

int ultimate[4] = {}, check[12] = {}, shadow = 0;

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

	nx = plus(mt), ny = plus(mt);

	vPositionList[0][0] = nx;
	vPositionList[0][1] = ny + 0.1;
	vPositionList[0][3] = nx - 0.075;
	vPositionList[0][4] = ny - 0.1;
	vPositionList[0][6] = nx + 0.075;
	vPositionList[0][7] = ny - 0.1;

	nx = minus(mt), ny = plus(mt);

	vPositionList[3][0] = nx;
	vPositionList[3][1] = ny + 0.1;
	vPositionList[3][3] = nx - 0.075;
	vPositionList[3][4] = ny - 0.1;
	vPositionList[3][6] = nx + 0.075;
	vPositionList[3][7] = ny - 0.1;

	nx = minus(mt), ny = minus(mt);

	vPositionList[6][0] = nx;
	vPositionList[6][1] = ny + 0.1;
	vPositionList[6][3] = nx - 0.075;
	vPositionList[6][4] = ny - 0.1;
	vPositionList[6][6] = nx + 0.075;
	vPositionList[6][7] = ny - 0.1;

	nx = plus(mt), ny = minus(mt);

	vPositionList[9][0] = nx;
	vPositionList[9][1] = ny + 0.1;
	vPositionList[9][3] = nx - 0.075;
	vPositionList[9][4] = ny - 0.1;
	vPositionList[9][6] = nx + 0.075;
	vPositionList[9][7] = ny - 0.1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			colors[i * 3][j] = dis(mt);
			colors[i * 3][j + 3] = colors[i * 3][j];
			colors[i * 3][j + 6] = colors[i * 3][j];
		}

		index[i * 3][0] = 9 * i;
		index[i * 3][1] = 9 * i + 1;
		index[i * 3][2] = 9 * i + 2;

		check[i] = 0;

		ultimate[i]++;
	}

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
		if (check[i] == 0)
		{
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 3));
		}

		else if (check[i] == 1)
		{
			glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 3));
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

void drawingLeft(GLfloat vPositionList[12][9], GLfloat colors[12][9], GLint index[12][3], float ox, float oy, int ultimate[4], int check[12])
{
	if (ox >= 0 && oy >= 0)
	{
		if (ultimate[0] == 1)
		{
			shadow = fea(mt);

			vPositionList[0][0] = ox;
			vPositionList[0][1] = oy + 0.1 + fea(mt);
			vPositionList[0][3] = ox - 0.075 + shadow;
			vPositionList[0][4] = oy - 0.1;
			vPositionList[0][6] = ox + 0.075 + shadow;
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

			if (execute)
			{
				check[0] = 0;
			}

			else if (!execute)
			{
				check[0] = 1;
			}
		}

		else if (ultimate[0] == 2)
		{
			shadow = fea(mt);

			vPositionList[1][0] = vPositionList[0][0];
			vPositionList[1][1] = vPositionList[0][1];
			vPositionList[1][3] = vPositionList[0][3];
			vPositionList[1][4] = vPositionList[0][4];
			vPositionList[1][6] = vPositionList[0][6];
			vPositionList[1][7] = vPositionList[0][7];

			vPositionList[0][0] = ox;
			vPositionList[0][1] = oy + 0.1 + fea(mt);
			vPositionList[0][3] = ox - 0.075 + shadow;
			vPositionList[0][4] = oy - 0.1;
			vPositionList[0][6] = ox + 0.075 + shadow;
			vPositionList[0][7] = oy - 0.1;

			for (int i = 0; i < 9; i++)
			{
				colors[1][i] = colors[0][i];
			}

			for (int i = 0; i < 3; i++)
			{
				colors[0][i] = dis(mt);
				colors[0][i + 3] = colors[0][i];
				colors[0][i + 6] = colors[0][i];
			}

			for (int i = 0; i < 2; i++)
			{
				index[i][0] = i * 3;
				index[i][1] = i * 3 + 1;
				index[i][2] = i * 3 + 2;
			}

			check[1] = check[0];

			if (execute)
			{
				check[0] = 0;
			}

			else if (!execute)
			{
				check[0] = 1;
			}
		}

		else if (ultimate[0] == 3)
		{
			shadow = fea(mt);

			vPositionList[2][0] = vPositionList[1][0];
			vPositionList[2][1] = vPositionList[1][1];
			vPositionList[2][3] = vPositionList[1][3];
			vPositionList[2][4] = vPositionList[1][4];
			vPositionList[2][6] = vPositionList[1][6];
			vPositionList[2][7] = vPositionList[1][7];

			vPositionList[1][0] = vPositionList[0][0];
			vPositionList[1][1] = vPositionList[0][1];
			vPositionList[1][3] = vPositionList[0][3];
			vPositionList[1][4] = vPositionList[0][4];
			vPositionList[1][6] = vPositionList[0][6];
			vPositionList[1][7] = vPositionList[0][7];

			vPositionList[0][0] = ox;
			vPositionList[0][1] = oy + 0.1 + fea(mt);
			vPositionList[0][3] = ox - 0.075 + shadow;
			vPositionList[0][4] = oy - 0.1;
			vPositionList[0][6] = ox + 0.075 + shadow;
			vPositionList[0][7] = oy - 0.1;

			for (int i = 0; i < 9; i++)
			{
				colors[2][i] = colors[1][i];

				colors[1][i] = colors[0][i];
			}

			for (int i = 0; i < 3; i++)
			{
				colors[0][i] = dis(mt);
				colors[0][i + 3] = colors[0][i];
				colors[0][i + 6] = colors[0][i];

				index[i][0] = i * 3;
				index[i][1] = i * 3 + 1;
				index[i][2] = i * 3 + 2;
			}

			check[2] = check[1];

			check[1] = check[0];

			if (execute)
			{
				check[0] = 0;
			}

			else if (!execute)
			{
				check[0] = 1;
			}
		}
	}

	else if (ox < 0 && oy >= 0)
	{
		if (ultimate[1] < 3)
		{
			shadow = fea(mt);

			vPositionList[ultimate[1] + 3][0] = ox;
			vPositionList[ultimate[1] + 3][1] = oy + 0.1 + fea(mt);
			vPositionList[ultimate[1] + 3][3] = ox - 0.075 + shadow;
			vPositionList[ultimate[1] + 3][4] = oy - 0.1;
			vPositionList[ultimate[1] + 3][6] = ox + 0.075 + shadow;
			vPositionList[ultimate[1] + 3][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[ultimate[1] + 3][i] = dis(mt);
				colors[ultimate[1] + 3][i + 3] = colors[ultimate[1] + 3][i];
				colors[ultimate[1] + 3][i + 6] = colors[ultimate[1] + 3][i];
			}

			index[ultimate[1] + 3][0] = ultimate[1] * 3 + 9;
			index[ultimate[1] + 3][1] = ultimate[1] * 3 + 10;
			index[ultimate[1] + 3][2] = ultimate[1] * 3 + 11;

			if (execute)
			{
				check[ultimate[1] + 3] = 0;
			}

			else if (!execute)
			{
				check[ultimate[1] + 3] = 1;
			}

			ultimate[1]++;
		}
	}

	else if (ox < 0 && oy < 0)
	{
		if (ultimate[2] < 3)
		{
			shadow = fea(mt);

			vPositionList[ultimate[2] + 6][0] = ox;
			vPositionList[ultimate[2] + 6][1] = oy + 0.1 + fea(mt);
			vPositionList[ultimate[2] + 6][3] = ox - 0.075 + shadow;
			vPositionList[ultimate[2] + 6][4] = oy - 0.1;
			vPositionList[ultimate[2] + 6][6] = ox + 0.075 + shadow;
			vPositionList[ultimate[2] + 6][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[ultimate[2] + 6][i] = dis(mt);
				colors[ultimate[2] + 6][i + 3] = colors[ultimate[2] + 6][i];
				colors[ultimate[2] + 6][i + 6] = colors[ultimate[2] + 6][i];
			}

			index[ultimate[2] + 6][0] = ultimate[2] * 3 + 18;
			index[ultimate[2] + 6][1] = ultimate[2] * 3 + 19;
			index[ultimate[2] + 6][2] = ultimate[2] * 3 + 20;

			if (execute)
			{
				check[ultimate[2] + 6] = 0;
			}

			else if (!execute)
			{
				check[ultimate[2] + 6] = 1;
			}

			ultimate[2]++;
		}
	}

	else if (ox >= 0 && oy < 0)
	{
		if (ultimate[3] < 3)
		{
			shadow = fea(mt);

			vPositionList[ultimate[3] + 9][0] = ox;
			vPositionList[ultimate[3] + 9][1] = oy + 0.1 + fea(mt);
			vPositionList[ultimate[3] + 9][3] = ox - 0.075 + shadow;
			vPositionList[ultimate[3] + 9][4] = oy - 0.1;
			vPositionList[ultimate[3] + 9][6] = ox + 0.075 + shadow;
			vPositionList[ultimate[3] + 9][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[ultimate[3] + 9][i] = dis(mt);
				colors[ultimate[3] + 9][i + 3] = colors[ultimate[3] + 9][i];
				colors[ultimate[3] + 9][i + 6] = colors[ultimate[3] + 9][i];
			}

			index[ultimate[3] + 9][0] = ultimate[3] * 3 + 27;
			index[ultimate[3] + 9][1] = ultimate[3] * 3 + 28;
			index[ultimate[3] + 9][2] = ultimate[3] * 3 + 29;

			if (execute)
			{
				check[ultimate[3] + 9] = 0;
			}

			else if (!execute)
			{
				check[ultimate[3] + 9] = 1;
			}

			ultimate[3]++;
		}
	}
}

void drawingRight(GLfloat vPositionList[12][9], GLfloat colors[12][9], GLint index[12][3], float ox, float oy, int ultimate[4], int check[12])
{
	if (ox >= 0 && oy >= 0)
	{
		if (ultimate[0] < 3)
		{
			shadow = fea(mt);

			vPositionList[ultimate[0]][0] = ox;
			vPositionList[ultimate[0]][1] = oy + 0.1 + fea(mt);
			vPositionList[ultimate[0]][3] = ox - 0.075 + shadow;
			vPositionList[ultimate[0]][4] = oy - 0.1;
			vPositionList[ultimate[0]][6] = ox + 0.075 + shadow;
			vPositionList[ultimate[0]][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[ultimate[0]][i] = dis(mt);
				colors[ultimate[0]][i + 3] = colors[ultimate[0]][i];
				colors[ultimate[0]][i + 6] = colors[ultimate[0]][i];
			}

			index[ultimate[0]][0] = ultimate[0] * 3;
			index[ultimate[0]][1] = ultimate[0] * 3 + 1;
			index[ultimate[0]][2] = ultimate[0] * 3 + 2;

			if (execute)
			{
				check[ultimate[0]] = 0;
			}

			else if (!execute)
			{
				check[ultimate[0]] = 1;
			}

			ultimate[0]++;
		}
	}

	else if (ox < 0 && oy >= 0)
	{
		if (ultimate[1] < 3)
		{
			shadow = fea(mt);

			vPositionList[ultimate[1] + 3][0] = ox;
			vPositionList[ultimate[1] + 3][1] = oy + 0.1 + fea(mt);
			vPositionList[ultimate[1] + 3][3] = ox - 0.075 + shadow;
			vPositionList[ultimate[1] + 3][4] = oy - 0.1;
			vPositionList[ultimate[1] + 3][6] = ox + 0.075 + shadow;
			vPositionList[ultimate[1] + 3][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[ultimate[1] + 3][i] = dis(mt);
				colors[ultimate[1] + 3][i + 3] = colors[ultimate[1] + 3][i];
				colors[ultimate[1] + 3][i + 6] = colors[ultimate[1] + 3][i];
			}

			index[ultimate[1] + 3][0] = ultimate[1] * 3 + 9;
			index[ultimate[1] + 3][1] = ultimate[1] * 3 + 10;
			index[ultimate[1] + 3][2] = ultimate[1] * 3 + 11;

			if (execute)
			{
				check[ultimate[1] + 3] = 0;
			}

			else if (!execute)
			{
				check[ultimate[1] + 3] = 1;
			}

			ultimate[1]++;
		}
	}

	else if (ox < 0 && oy < 0)
	{
		if (ultimate[2] < 3)
		{
			shadow = fea(mt);

			vPositionList[ultimate[2] + 6][0] = ox;
			vPositionList[ultimate[2] + 6][1] = oy + 0.1 + fea(mt);
			vPositionList[ultimate[2] + 6][3] = ox - 0.075 + shadow;
			vPositionList[ultimate[2] + 6][4] = oy - 0.1;
			vPositionList[ultimate[2] + 6][6] = ox + 0.075 + shadow;
			vPositionList[ultimate[2] + 6][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[ultimate[2] + 6][i] = dis(mt);
				colors[ultimate[2] + 6][i + 3] = colors[ultimate[2] + 6][i];
				colors[ultimate[2] + 6][i + 6] = colors[ultimate[2] + 6][i];
			}

			index[ultimate[2] + 6][0] = ultimate[2] * 3 + 18;
			index[ultimate[2] + 6][1] = ultimate[2] * 3 + 19;
			index[ultimate[2] + 6][2] = ultimate[2] * 3 + 20;

			if (execute)
			{
				check[ultimate[2] + 6] = 0;
			}

			else if (!execute)
			{
				check[ultimate[2] + 6] = 1;
			}

			ultimate[2]++;
		}
	}

	else if (ox >= 0 && oy < 0)
	{
		if (ultimate[3] < 3)
		{
			shadow = fea(mt);

			vPositionList[ultimate[3] + 9][0] = ox;
			vPositionList[ultimate[3] + 9][1] = oy + 0.1 + fea(mt);
			vPositionList[ultimate[3] + 9][3] = ox - 0.075 + shadow;
			vPositionList[ultimate[3] + 9][4] = oy - 0.1;
			vPositionList[ultimate[3] + 9][6] = ox + 0.075 + shadow;
			vPositionList[ultimate[3] + 9][7] = oy - 0.1;

			for (int i = 0; i < 3; i++)
			{
				colors[ultimate[3] + 9][i] = dis(mt);
				colors[ultimate[3] + 9][i + 3] = colors[ultimate[3] + 9][i];
				colors[ultimate[3] + 9][i + 6] = colors[ultimate[3] + 9][i];
			}

			index[ultimate[3] + 9][0] = ultimate[3] * 3 + 27;
			index[ultimate[3] + 9][1] = ultimate[3] * 3 + 28;
			index[ultimate[3] + 9][2] = ultimate[3] * 3 + 29;

			if (execute)
			{
				check[ultimate[3] + 9] = 0;
			}

			else if (!execute)
			{
				check[ultimate[3] + 9] = 1;
			}

			ultimate[3]++;
		}
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