#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <cmath>

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

GLfloat vPositionList[4][9] = {};
GLfloat colors[4][9] = {};
GLint index[4][3] = {};
GLuint VAO, VBO_pos[2], EBO;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dis(0, 1);
std::uniform_real_distribution<float> fea(-0.1, 0.1);
std::uniform_real_distribution<float> plus(0.1, 0.9);
std::uniform_real_distribution<float> minus(-0.9, -0.1);

float ox = 0.0, oy = 0.0, nx = 0.0, ny = 0.0, weak[4] = { 1.0, 1.0, 1.0, 1.0 };

int direct[4] = { 0, 1, 2, 3 }, updown[4] = { 0, 0, 0, 0 }, superior = 0, power = 0;

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

	vPositionList[1][0] = nx;
	vPositionList[1][1] = ny + 0.1;
	vPositionList[1][3] = nx - 0.075;
	vPositionList[1][4] = ny - 0.1;
	vPositionList[1][6] = nx + 0.075;
	vPositionList[1][7] = ny - 0.1;

	nx = minus(mt), ny = minus(mt);

	vPositionList[2][0] = nx;
	vPositionList[2][1] = ny + 0.1;
	vPositionList[2][3] = nx - 0.075;
	vPositionList[2][4] = ny - 0.1;
	vPositionList[2][6] = nx + 0.075;
	vPositionList[2][7] = ny - 0.1;

	nx = plus(mt), ny = minus(mt);

	vPositionList[3][0] = nx;
	vPositionList[3][1] = ny + 0.1;
	vPositionList[3][3] = nx - 0.075;
	vPositionList[3][4] = ny - 0.1;
	vPositionList[3][6] = nx + 0.075;
	vPositionList[3][7] = ny - 0.1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			colors[i][j] = dis(mt);
			colors[i][j + 3] = colors[i][j];
			colors[i][j + 6] = colors[i][j];
		}

		index[i][0] = 3 * i;
		index[i][1] = 3 * i + 1;
		index[i][2] = 3 * i + 2;
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

	for (int i = 0; i < 4; i++)
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
	case '1':
		superior = 1;
		glutTimerFunc(10, TimerFunction, 1);
		break;
	case '2':
		superior = 2;
		glutTimerFunc(10, TimerFunction, 2);
		break;
	case '3':
		superior = 3;
		for (int i = 0; i < 4; i++)
		{
			direct[i] = 0;

			updown[i] = 0;

			weak[i] = 1;
		}
		glutTimerFunc(10, TimerFunction, 3);
		break;
	case '4':
		superior = 4;
		for (int i = 0; i < 4; i++)
		{
			direct[i] = i;
		}
		power = 0;
		glutTimerFunc(100, TimerFunction, 4);
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (value == 1 && superior == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (direct[i] == 0)
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

			else if (direct[i] == 1)
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

			else if (direct[i] == 2)
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

			else if (direct[i] == 3)
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
		}
		glutTimerFunc(10, TimerFunction, 1);
	}

	else if (value == 2 && superior == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			if (direct[i] == 0)
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

			else if (direct[i] == 1)
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

			else if (direct[i] == 2)
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

			else if (direct[i] == 3)
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
		glutTimerFunc(10, TimerFunction, 2);
	}

	else if (value == 3 && superior == 3)
	{
		for (int i = 0; i < 4; i++)
		{
			if (direct[i] == 0)
			{
				vPositionList[i][0] += 0.01 + 0.00333 * i;
				vPositionList[i][3] += 0.01 + 0.00333 * i;
				vPositionList[i][6] += 0.01 + 0.00333 * i;

				if (vPositionList[i][6] > weak[i])
				{
					vPositionList[i][0] -= 0.01 + 0.00333 * i;
					vPositionList[i][3] -= 0.01 + 0.00333 * i;
					vPositionList[i][6] -= 0.01 + 0.00333 * i;

					direct[i] = 1;

					updown[i]++;

					if (updown[i] % 4 == 0)
					{
						weak[i] -= 0.2;
					}
				}
			}

			else if (direct[i] == 1)
			{
				vPositionList[i][1] -= 0.01 + 0.00333 * i;
				vPositionList[i][4] -= 0.01 + 0.00333 * i;
				vPositionList[i][7] -= 0.01 + 0.00333 * i;

				if (vPositionList[i][4] < weak[i] * -1.0)
				{
					vPositionList[i][1] += 0.01 + 0.00333 * i;
					vPositionList[i][4] += 0.01 + 0.00333 * i;
					vPositionList[i][7] += 0.01 + 0.00333 * i;


					direct[i] = 2;

					updown[i]++;

					if (updown[i] % 4 == 0)
					{
						weak[i] -= 0.2;
					}
				}
			}

			else if (direct[i] == 2)
			{
				vPositionList[i][0] -= 0.01 + 0.00333 * i;
				vPositionList[i][3] -= 0.01 + 0.00333 * i;
				vPositionList[i][6] -= 0.01 + 0.00333 * i;

				if (vPositionList[i][3] < weak[i] * -1.0)
				{
					vPositionList[i][0] += 0.01 + 0.00333 * i;
					vPositionList[i][3] += 0.01 + 0.00333 * i;
					vPositionList[i][6] += 0.01 + 0.00333 * i;

					direct[i] = 3;

					updown[i]++;

					if (updown[i] % 4 == 0)
					{
						weak[i] -= 0.2;
					}
				}
			}

			else if (direct[i] == 3)
			{
				vPositionList[i][1] += 0.01 + 0.00333 * i;
				vPositionList[i][4] += 0.01 + 0.00333 * i;
				vPositionList[i][7] += 0.01 + 0.00333 * i;

				if (vPositionList[i][1] > weak[i])
				{
					vPositionList[i][1] -= 0.01 + 0.00333 * i;
					vPositionList[i][4] -= 0.01 + 0.00333 * i;
					vPositionList[i][7] -= 0.01 + 0.00333 * i;


					direct[i] = 0;

					updown[i]++;

					if (updown[i] % 4 == 0)
					{
						weak[i] -= 0.2;
					}
				}
			}
		}

		glutTimerFunc(10, TimerFunction, 3);
	}

	else if (value == 4 && superior == 4)
	{
		vPositionList[0][0] += cos(power) / 360 * power;
		vPositionList[0][1] += sin(power) / 360 * power;
		vPositionList[0][3] += cos(power) / 360 * power;
		vPositionList[0][4] += sin(power) / 360 * power;
		vPositionList[0][6] += cos(power) / 360 * power;
		vPositionList[0][7] += sin(power) / 360 * power;

		vPositionList[1][0] -= cos(power) / 270 * power;
		vPositionList[1][1] += sin(power) / 270 * power;
		vPositionList[1][3] -= cos(power) / 270 * power;
		vPositionList[1][4] += sin(power) / 270 * power;
		vPositionList[1][6] -= cos(power) / 270 * power;
		vPositionList[1][7] += sin(power) / 270 * power;

		vPositionList[2][0] += cos(power) / 180 * power;
		vPositionList[2][1] -= sin(power) / 180 * power;
		vPositionList[2][3] += cos(power) / 180 * power;
		vPositionList[2][4] -= sin(power) / 180 * power;
		vPositionList[2][6] += cos(power) / 180 * power;
		vPositionList[2][7] -= sin(power) / 180 * power;

		vPositionList[3][0] -= cos(power) / 90 * power;
		vPositionList[3][1] -= sin(power) / 90 * power;
		vPositionList[3][3] -= cos(power) / 90 * power;
		vPositionList[3][4] -= sin(power) / 90 * power;
		vPositionList[3][6] -= cos(power) / 90 * power;
		vPositionList[3][7] -= sin(power) / 90 * power;

		power++;

		glutTimerFunc(100, TimerFunction, 4);
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