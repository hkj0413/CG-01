#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

void InitBuffer();
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

char* filetobuf(const char* file);

GLfloat vPositionList[4][15] = {};
GLfloat colors[4][15] = {};
GLint index[4][9] = {};
GLuint VAO, VBO_pos[2], EBO;

int direct[4] = { 0, 1, 2, 3 }, a[4] = {}, x = 0;

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

	vPositionList[0][0] = -0.25;
	vPositionList[0][1] = 0.75;
	vPositionList[0][3] = -0.75;
	vPositionList[0][4] = 0.25;
	vPositionList[0][6] = -0.25;
	vPositionList[0][7] = 0.25;
	vPositionList[0][9] = -0.75;
	vPositionList[0][10] = 0.75;
	vPositionList[0][12] = -0.5;
	vPositionList[0][13] = 0.9;

	vPositionList[1][0] = 0.75;
	vPositionList[1][1] = 0.75;
	vPositionList[1][3] = 0.25;
	vPositionList[1][4] = 0.25;
	vPositionList[1][6] = 0.75;
	vPositionList[1][7] = 0.25;
	vPositionList[1][9] = 0.25;
	vPositionList[1][10] = 0.75;
	vPositionList[1][12] = 0.5;
	vPositionList[1][13] = 0.9;


	vPositionList[2][0] = -0.25;
	vPositionList[2][1] = -0.25;
	vPositionList[2][3] = -0.75;
	vPositionList[2][4] = -0.75;
	vPositionList[2][6] = -0.25;
	vPositionList[2][7] = -0.75;
	vPositionList[2][9] = -0.75;
	vPositionList[2][10] = -0.25;
	vPositionList[2][12] = -0.5;
	vPositionList[2][13] = -0.1;

	vPositionList[3][0] = 0.75;
	vPositionList[3][1] = -0.25;
	vPositionList[3][3] = 0.25;
	vPositionList[3][4] = -0.75;
	vPositionList[3][6] = 0.75;
	vPositionList[3][7] = -0.75;
	vPositionList[3][9] = 0.25;
	vPositionList[3][10] = -0.25;
	vPositionList[3][12] = 0.5;
	vPositionList[3][13] = -0.1;

	for (int i = 0; i < 5; i++)
	{
		colors[0][i * 3 + 2] = 1.0;

		colors[1][i * 3] = 1.0;
		colors[1][i * 3 + 1] = 1.0;

		colors[2][i * 3 + 1] = 1.0;

		colors[3][i * 3] = 1.0;
	}

	for (int i = 0; i < 4; i++)
	{
		index[i][0] = 5 * i;
		index[i][1] = 5 * i + 1;
		index[i][2] = 5 * i + 2;
		index[i][3] = 5 * i;
		index[i][4] = 5 * i + 1;
		index[i][5] = 5 * i + 3;
		index[i][6] = 5 * i;
		index[i][7] = 5 * i + 3;
		index[i][8] = 5 * i + 4;
	}

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

	glBindBuffer(GL_ARRAY_BUFFER, EBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(index), index);

	glRectf(-1.0, -0.005, 1.0, 0.005);
	glRectf(-0.005, -1.0, 0.005, 1.0);

	for (int i = 0; i < 4; i++)
	{
		if (direct[i] == 0)
		{
			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 9));
		}

		else if(direct[i] == 1)
		{
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 9));
		}

		else if (direct[i] == 2)
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 9));
		}

		else if (direct[i] == 3)
		{
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 9));
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
	case 'l':
		for (int i = 0; i < 4; i++)
		{
			if (direct[i] == 0)
			{
				direct[i] = 1;

				a[i] = 1;

				vPositionList[i][7] += 0.49;
			}
		}
		glutTimerFunc(10, TimerFunction, 1);
		break;
	case 't':
		for (int i = 0; i < 4; i++)
		{
			if (direct[i] == 1)
			{
				direct[i] = 2;

				a[i] = 2;

				vPositionList[i][10] -= 0.49;
			}
		}
		glutTimerFunc(10, TimerFunction, 2);
		break;
	case 'r':
		glutTimerFunc(10, TimerFunction, 3);
		break;
	case 'p':
		glutTimerFunc(10, TimerFunction, 4);
		break;
	case 'a':
		for (int i = 0; i < 4; i++)
		{
			direct[i] = i;
		}
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (value == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (a[i] == 1)
			{
				vPositionList[i][7] -= 0.01;
			}
		}
		
		x++;

		if (x < 49)
		{
			glutPostRedisplay();

			glutTimerFunc(10, TimerFunction, 1);
		}

		else
		{
			for (int i = 0; i < 4; i++)
			{
				a[i] = 0;
			}

			x = 0;

			glutPostRedisplay();
		}
	}

	else if (value == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			if (a[i] == 2)
			{
				vPositionList[i][10] += 0.01;
			}
		}

		x++;

		if (x < 49)
		{
			glutPostRedisplay();

			glutTimerFunc(10, TimerFunction, 2);
		}

		else
		{
			for (int i = 0; i < 4; i++)
			{
				a[i] = 0;
			}

			x = 0;

			glutPostRedisplay();
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