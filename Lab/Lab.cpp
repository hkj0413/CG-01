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
GLvoid TimerFunction(int value);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

char* filetobuf(const char* file);

GLfloat vPositionList[15][18] = {};
GLfloat colors[15][18] = {};
GLint index[15][12] = {};
GLuint VAO, VBO_pos[2], EBO;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dis(0, 1);
std::uniform_real_distribution<float> rx(-0.9, 0.9);
std::uniform_real_distribution<float> ry(-0.85, 0.85);

float ox = 0.0, oy = 0.0, nx = 0.0, ny = 0.0;

int object[15] = {}, direct[15] = {}, a[4] = {}, x = 0;

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

	for (int i = 0; i < 5; i++)
	{
		object[i * 3] = i;
		object[i * 3 + 1] = i;
		object[i * 3 + 2] = i;
	}

	for (int i = 0; i < 15; i++)
	{
		nx = rx(mt), ny = ry(mt);

		vPositionList[i][0] = nx;
		vPositionList[i][1] = ny;
		vPositionList[i][3] = nx - 0.1;
		vPositionList[i][4] = ny - 0.1;
		vPositionList[i][6] = nx;
		vPositionList[i][7] = ny - 0.1;
		vPositionList[i][9] = nx - 0.1;
		vPositionList[i][10] = ny;
		vPositionList[i][12] = nx -0.05;
		vPositionList[i][13] = ny + 0.05;
		vPositionList[i][15] = nx - 0.05;
		vPositionList[i][16] = ny - 0.15;

		for (int j = 0; j < 3; j++)
		{
			colors[i][j] = dis(mt);
			colors[i][j + 3] = colors[i][j];
			colors[i][j + 6] = colors[i][j];
			colors[i][j + 9] = colors[i][j];
			colors[i][j + 12] = colors[i][j];
		}

		index[i][0] = 6 * i;
		index[i][1] = 6 * i + 1;
		index[i][2] = 6 * i + 2;
		index[i][3] = 6 * i;
		index[i][4] = 6 * i + 1;
		index[i][5] = 6 * i + 3;
		index[i][6] = 6 * i;
		index[i][7] = 6 * i + 3;
		index[i][8] = 6 * i + 4;
		index[i][9] = 6 * i + 1;
		index[i][10] = 6 * i + 2;
		index[i][11] = 6 * i + 5;
	}

	glutTimerFunc(10, TimerFunction, 1);

	InitBuffer();
	make_vertexShaders();
	make_fragmentShaders();
	shaderProgramID = make_shaderProgram();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
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

	for (int i = 0; i < 15; i++)
	{
		if (object[i] == 0)
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 12));
		}

		else if (object[i] == 1)
		{
			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 12));
		}

		else if (object[i] == 2)
		{
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 12));
		}

		else if (object[i] == 3)
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 12));
		}

		else if (object[i] == 4)
		{
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 12));
		}

		else if (object[i] == 5)
		{
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * i * 12));
		}
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	for (int i = 0; i < 15; i++)
	{
		if (direct[i] == 1)
		{
			vPositionList[i][0] += 0.01 + 0.00333 * i;
			vPositionList[i][1] += 0.01 + 0.00333 * i;
			vPositionList[i][3] += 0.01 + 0.00333 * i;
			vPositionList[i][4] += 0.01 + 0.00333 * i;
			vPositionList[i][6] += 0.01 + 0.00333 * i;
			vPositionList[i][7] += 0.01 + 0.00333 * i;

			if (vPositionList[i][6] > 1 && vPositionList[i][1] > 1)
			{
				vPositionList[i][0] -= 0.01 + 0.00333 * i;
				vPositionList[i][1] -= 0.01 + 0.00333 * i;
				vPositionList[i][3] -= 0.01 + 0.00333 * i;
				vPositionList[i][4] -= 0.01 + 0.00333 * i;
				vPositionList[i][6] -= 0.01 + 0.00333 * i;
				vPositionList[i][7] -= 0.01 + 0.00333 * i;

				direct[i] = 2;
			}

			else if (vPositionList[i][6] > 1)
			{
				vPositionList[i][0] -= 0.01 + 0.00333 * i;
				vPositionList[i][3] -= 0.01 + 0.00333 * i;
				vPositionList[i][6] -= 0.01 + 0.00333 * i;

				direct[i] = 1;
			}

			else if (vPositionList[i][1] > 1)
			{
				vPositionList[i][1] -= 0.01 + 0.00333 * i;
				vPositionList[i][4] -= 0.01 + 0.00333 * i;
				vPositionList[i][7] -= 0.01 + 0.00333 * i;

				direct[i] = 3;
			}
		}

		else if (direct[i] == 2)
		{
			vPositionList[i][0] -= 0.01 + 0.00333 * i;
			vPositionList[i][1] += 0.01 + 0.00333 * i;
			vPositionList[i][3] -= 0.01 + 0.00333 * i;
			vPositionList[i][4] += 0.01 + 0.00333 * i;
			vPositionList[i][6] -= 0.01 + 0.00333 * i;
			vPositionList[i][7] += 0.01 + 0.00333 * i;

			if (vPositionList[i][3] < -1 && vPositionList[i][1] > 1)
			{
				vPositionList[i][0] += 0.01 + 0.00333 * i;
				vPositionList[i][1] -= 0.01 + 0.00333 * i;
				vPositionList[i][3] += 0.01 + 0.00333 * i;
				vPositionList[i][4] -= 0.01 + 0.00333 * i;
				vPositionList[i][6] += 0.01 + 0.00333 * i;
				vPositionList[i][7] -= 0.01 + 0.00333 * i;

				direct[i] = 3;
			}

			else if (vPositionList[i][3] < -1)
			{
				vPositionList[i][0] += 0.01 + 0.00333 * i;
				vPositionList[i][3] += 0.01 + 0.00333 * i;
				vPositionList[i][6] += 0.01 + 0.00333 * i;

				direct[i] = 0;
			}

			else if (vPositionList[i][1] > 1)
			{
				vPositionList[i][1] -= 0.01 + 0.00333 * i;
				vPositionList[i][4] -= 0.01 + 0.00333 * i;
				vPositionList[i][7] -= 0.01 + 0.00333 * i;

				direct[i] = 2;
			}
		}

		else if (direct[i] == 3)
		{
			vPositionList[i][0] -= 0.01 + 0.00333 * i;
			vPositionList[i][1] -= 0.01 + 0.00333 * i;
			vPositionList[i][3] -= 0.01 + 0.00333 * i;
			vPositionList[i][4] -= 0.01 + 0.00333 * i;
			vPositionList[i][6] -= 0.01 + 0.00333 * i;
			vPositionList[i][7] -= 0.01 + 0.00333 * i;

			if (vPositionList[i][3] < -1 && vPositionList[i][4] < -1)
			{
				vPositionList[i][0] += 0.01 + 0.00333 * i;
				vPositionList[i][1] += 0.01 + 0.00333 * i;
				vPositionList[i][3] += 0.01 + 0.00333 * i;
				vPositionList[i][4] += 0.01 + 0.00333 * i;
				vPositionList[i][6] += 0.01 + 0.00333 * i;
				vPositionList[i][7] += 0.01 + 0.00333 * i;

				direct[i] = 0;
			}

			else if (vPositionList[i][3] < -1)
			{
				vPositionList[i][0] += 0.01 + 0.00333 * i;
				vPositionList[i][3] += 0.01 + 0.00333 * i;
				vPositionList[i][6] += 0.01 + 0.00333 * i;

				direct[i] = 3;
			}

			else if (vPositionList[i][4] < -1)
			{
				vPositionList[i][1] += 0.01 + 0.00333 * i;
				vPositionList[i][4] += 0.01 + 0.00333 * i;
				vPositionList[i][7] += 0.01 + 0.00333 * i;

				direct[i] = 1;
			}
		}

		else if (direct[i] == 4)
		{
			vPositionList[i][0] += 0.01 + 0.00333 * i;
			vPositionList[i][1] -= 0.01 + 0.00333 * i;
			vPositionList[i][3] += 0.01 + 0.00333 * i;
			vPositionList[i][4] -= 0.01 + 0.00333 * i;
			vPositionList[i][6] += 0.01 + 0.00333 * i;
			vPositionList[i][7] -= 0.01 + 0.00333 * i;

			if (vPositionList[i][6] > 1 && vPositionList[i][4] < -1)
			{
				vPositionList[i][0] -= 0.01 + 0.00333 * i;
				vPositionList[i][1] += 0.01 + 0.00333 * i;
				vPositionList[i][3] -= 0.01 + 0.00333 * i;
				vPositionList[i][4] += 0.01 + 0.00333 * i;
				vPositionList[i][6] -= 0.01 + 0.00333 * i;
				vPositionList[i][7] += 0.01 + 0.00333 * i;

				direct[i] = 1;
			}

			else if (vPositionList[i][6] > 1)
			{
				vPositionList[i][0] -= 0.01 + 0.00333 * i;
				vPositionList[i][3] -= 0.01 + 0.00333 * i;
				vPositionList[i][6] -= 0.01 + 0.00333 * i;

				direct[i] = 2;
			}

			else if (vPositionList[i][4] < -1)
			{
				vPositionList[i][1] += 0.01 + 0.00333 * i;
				vPositionList[i][4] += 0.01 + 0.00333 * i;
				vPositionList[i][7] += 0.01 + 0.00333 * i;

				direct[i] = 0;
			}

		}

		else if (direct[i] == 5)
		{
			vPositionList[i][0] += 0.01 + 0.00333 * i;
			vPositionList[i][3] += 0.01 + 0.00333 * i;
			vPositionList[i][6] += 0.01 + 0.00333 * i;

			if (vPositionList[i][6] > 1)
			{
				vPositionList[i][0] -= 0.01 + 0.00333 * i;
				vPositionList[i][1] += 0.2;
				vPositionList[i][3] -= 0.01 + 0.00333 * i;
				vPositionList[i][4] += 0.2;
				vPositionList[i][6] -= 0.01 + 0.00333 * i;
				vPositionList[i][7] += 0.2;

				if (vPositionList[i][1] > 1)
				{
					vPositionList[i][1] = 1;
					vPositionList[i][4] = 0.8;
					vPositionList[i][7] = 0.8;

					direct[i] = 2;
				}

				else
				{
					direct[i] = 1;
				}
			}
		}

		else if (direct[i] == 6)
		{
			vPositionList[i][0] -= 0.01 + 0.00333 * i;
			vPositionList[i][3] -= 0.01 + 0.00333 * i;
			vPositionList[i][6] -= 0.01 + 0.00333 * i;

			if (vPositionList[i][3] < -1)
			{
				vPositionList[i][0] += 0.01 + 0.00333 * i;
				vPositionList[i][1] += 0.2;
				vPositionList[i][3] += 0.01 + 0.00333 * i;
				vPositionList[i][4] += 0.2;
				vPositionList[i][6] += 0.01 + 0.00333 * i;
				vPositionList[i][7] += 0.2;

				if (vPositionList[i][1] > 1)
				{
					vPositionList[i][1] = 1;
					vPositionList[i][4] = 0.8;
					vPositionList[i][7] = 0.8;

					direct[i] = 3;
				}

				else
				{
					direct[i] = 0;
				}
			}
		}

		else if (direct[i] == 7)
		{
			vPositionList[i][0] -= 0.01 + 0.00333 * i;
			vPositionList[i][3] -= 0.01 + 0.00333 * i;
			vPositionList[i][6] -= 0.01 + 0.00333 * i;

			if (vPositionList[i][3] < -1)
			{
				vPositionList[i][0] += 0.01 + 0.00333 * i;
				vPositionList[i][1] -= 0.2;
				vPositionList[i][3] += 0.01 + 0.00333 * i;
				vPositionList[i][4] -= 0.2;
				vPositionList[i][6] += 0.01 + 0.00333 * i;
				vPositionList[i][7] -= 0.2;

				if (vPositionList[i][4] < -1)
				{
					vPositionList[i][1] = -0.8;
					vPositionList[i][4] = -1;
					vPositionList[i][7] = -1;

					direct[i] = 0;
				}

				else
				{
					direct[i] = 3;
				}
			}
		}

		else if (direct[i] == 8)
		{
			vPositionList[i][0] += 0.01 + 0.00333 * i;
			vPositionList[i][3] += 0.01 + 0.00333 * i;
			vPositionList[i][6] += 0.01 + 0.00333 * i;

			if (vPositionList[i][6] > 1)
			{
				vPositionList[i][0] -= 0.01 + 0.00333 * i;
				vPositionList[i][1] -= 0.2;
				vPositionList[i][3] -= 0.01 + 0.00333 * i;
				vPositionList[i][4] -= 0.2;
				vPositionList[i][6] -= 0.01 + 0.00333 * i;
				vPositionList[i][7] -= 0.2;

				if (vPositionList[i][4] < -1)
				{
					vPositionList[i][1] = -0.8;
					vPositionList[i][4] = -1;
					vPositionList[i][7] = -1;

					direct[i] = 1;
				}

				else
				{
					direct[i] = 2;
				}
			}
		}
	}

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