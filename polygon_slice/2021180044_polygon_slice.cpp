#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <vector>
#include <ctime>

void InitBuffer();
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid TimerFunction(int value);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

char* filetobuf(const char* file);

std::vector<GLfloat> vPositionList = {
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,

	-0.2, -0.85, 0.0,   0.2, -0.85, 0.0,   0.2, -0.8, 0.0,
	-0.2, -0.85, 0.0,   0.2, -0.8, 0.0,   -0.2, -0.8, 0.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
};
std::vector<GLfloat> colors = {
	1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,

	0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
};

std::vector<int> direction = {};

std::vector<int> shape = {};

std::vector<float> gravity = {};

GLuint VAO, VBO_pos[2];

std::clock_t lastTime = 0;

int ran = 0, shap = 0;

float ox = 0.0, oy = 0.0, ny = 0.0, qx = 0.0, qy = 0.0, R = 0.0, G = 0.0, B = 0.0, speed = 0.0;

bool cut, basket, object, viewroute;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> obc(0, 1);
std::uniform_int_distribution<int> dir(0, 3);
std::uniform_int_distribution<int> sha(0, 1);
std::uniform_real_distribution<float> ry(-0.7, 0.7);

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

	glutTimerFunc(10, TimerFunction, 1);

	InitBuffer();
	make_vertexShaders();
	make_fragmentShaders();
	shaderProgramID = make_shaderProgram();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
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
	glBufferData(GL_ARRAY_BUFFER, vPositionList.size() * sizeof(GLfloat), &vPositionList[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 12, 6);

	if (viewroute)
	{
		if (vPositionList.size() > 54 && direction.size() > 0 && shape.size() > 0)
		{
			for (int i = 0; i < direction.size(); i++)
			{
				glDrawArrays(GL_LINES, i * 12 + 33, 2);
			}
		}
	}

	if (!object)
	{
		if (vPositionList.size() > 54 && direction.size() > 0 && shape.size() > 0)
		{
			for (int i = 0; i < direction.size(); i++)
			{
				glDrawArrays(GL_TRIANGLES, i * 12 + 24, 9);
			}
		}
	}
	
	else if (object)
	{
		if (vPositionList.size() > 54 && direction.size() > 0 && shape.size() > 0)
		{
			for (int i = 0; i < direction.size(); i++)
			{
				glDrawArrays(GL_LINE_LOOP, i * 12 + 24, 9);
			}
		}
	}

	if (cut)
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
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
	case 'w':
		if (!object)
		{
			object = true;
		}

		else if (object)
		{
			object = false;
		}
		break;
	case 'e':
		if (!viewroute)
		{
			viewroute = true;
		}

		else if (viewroute)
		{
			viewroute = false;
		}
		break;
	case '+':
		if (speed < 0.004)
		{
			speed += 0.001;
		}
		break;
	case '-':
		if (speed > -0.003)
		{
			speed -= 0.001;
		}
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
		vPositionList[0] = ox - 0.0025;
		vPositionList[1] = oy - 0.0025;
		
		vPositionList[3] = ox + 0.0025;
		vPositionList[4] = oy - 0.0025;

		vPositionList[6] = ox + 0.0025;
		vPositionList[7] = oy + 0.0025;

		vPositionList[9] = ox - 0.0025;
		vPositionList[10] = oy - 0.0025;

		vPositionList[12] = ox + 0.0025;
		vPositionList[13] = oy + 0.0025;

		vPositionList[15] = ox - 0.0025;
		vPositionList[16] = oy + 0.0025;

		cut = true;
	}
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && cut)
	{
		if (vPositionList.size() > 72 && direction.size() > 0 && shape.size() > 0)
		{
			for (int i = 0; i < direction.size(); i++)
			{
				if (vPositionList[0] > vPositionList[i * 36 + 72] && vPositionList[3] < vPositionList[i * 36 + 75] && vPositionList[7] > vPositionList[i * 36 + 79] && vPositionList[1] < vPositionList[i * 36 + 73])
				{
					if (shape[i] == 0)
					{
						vPositionList.insert(vPositionList.end(), {
						vPositionList[i * 36 + 90], vPositionList[i * 36 + 91], 0.0f,
						vPositionList[i * 36 + 93], vPositionList[i * 36 + 94], 0.0f,
						vPositionList[i * 36 + 96], vPositionList[i * 36 + 97], 0.0f,
						vPositionList[i * 36 + 90], vPositionList[i * 36 + 91], 0.0f,
						vPositionList[i * 36 + 93], vPositionList[i * 36 + 94], 0.0f,
						vPositionList[i * 36 + 96], vPositionList[i * 36 + 97], 0.0f,
						vPositionList[i * 36 + 90], vPositionList[i * 36 + 91], 0.0f,
						vPositionList[i * 36 + 93], vPositionList[i * 36 + 94], 0.0f,
						vPositionList[i * 36 + 96], vPositionList[i * 36 + 97], 0.0f,
						vPositionList[i * 36 + 96], vPositionList[i * 36 + 97], 0.0f,
						vPositionList[i * 36 + 96], -1.0f, 0.0f,
						0.0f, 0.0f, 0.0f
							});

						colors.insert(colors.end(), {
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						1.0, 0.0, 0.0,    0.0, 1.0, 0.0,   0.0, 0.0, 0.0
							});

						direction.insert(direction.end(), 4);

						shape.insert(shape.end(), 2);

						gravity.insert(gravity.end(), 0.001);

						vPositionList[i * 36 + 90] = vPositionList[i * 36 + 81];
						vPositionList[i * 36 + 91] = vPositionList[i * 36 + 82];
						vPositionList[i * 36 + 93] = vPositionList[i * 36 + 84];
						vPositionList[i * 36 + 94] = vPositionList[i * 36 + 85];
						vPositionList[i * 36 + 96] = vPositionList[i * 36 + 87];
						vPositionList[i * 36 + 97] = vPositionList[i * 36 + 88];

						shape[i] += 1;
						break;
					}

					else if (shape[i] == 1)
					{
						vPositionList.insert(vPositionList.end(), {
						vPositionList[i * 36 + 72] + 0.05f, vPositionList[i * 36 + 73], 0.0f,
						vPositionList[i * 36 + 75] + 0.05f, vPositionList[i * 36 + 76], 0.0f,
						vPositionList[i * 36 + 78] + 0.05f, vPositionList[i * 36 + 79], 0.0f,
						vPositionList[i * 36 + 72] + 0.05f, vPositionList[i * 36 + 73], 0.0f,
						vPositionList[i * 36 + 75] + 0.05f, vPositionList[i * 36 + 76], 0.0f,
						vPositionList[i * 36 + 78] + 0.05f, vPositionList[i * 36 + 79], 0.0f,
						vPositionList[i * 36 + 72] + 0.05f, vPositionList[i * 36 + 73], 0.0f,
						vPositionList[i * 36 + 75] + 0.05f, vPositionList[i * 36 + 76], 0.0f,
						vPositionList[i * 36 + 78] + 0.05f, vPositionList[i * 36 + 79], 0.0f,
						vPositionList[i * 36 + 75], vPositionList[i * 36 + 73], 0.0f,
						vPositionList[i * 36 + 75], -1.0f, 0.0f,
						0.0f, 0.0f, 0.0f
							});

						colors.insert(colors.end(), {
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						colors[i * 36 + 72], colors[i * 36 + 73], colors[i * 36 + 74],
						1.0, 0.0, 0.0,    0.0, 1.0, 0.0,   0.0, 0.0, 0.0
							});

						direction.insert(direction.end(), 4);

						shape.insert(shape.end(), 2);

						gravity.insert(gravity.end(), 0.003);

						vPositionList[i * 36 + 72] = vPositionList[i * 36 + 81];
						vPositionList[i * 36 + 73] = vPositionList[i * 36 + 82];
						vPositionList[i * 36 + 75] = vPositionList[i * 36 + 84];
						vPositionList[i * 36 + 76] = vPositionList[i * 36 + 85];
						vPositionList[i * 36 + 78] = vPositionList[i * 36 + 87];
						vPositionList[i * 36 + 79] = vPositionList[i * 36 + 88];

						vPositionList[i * 36 + 90] = vPositionList[i * 36 + 81];
						vPositionList[i * 36 + 91] = vPositionList[i * 36 + 82];
						vPositionList[i * 36 + 93] = vPositionList[i * 36 + 84];
						vPositionList[i * 36 + 94] = vPositionList[i * 36 + 85];
						vPositionList[i * 36 + 96] = vPositionList[i * 36 + 87];
						vPositionList[i * 36 + 97] = vPositionList[i * 36 + 88];

						vPositionList[i * 36 + 99] = vPositionList[i * 36 + 81] + 0.05f;
						vPositionList[i * 36 + 100] = vPositionList[i * 36 + 82];
						vPositionList[i * 36 + 102] = vPositionList[i * 36 + 81] + 0.05f;
						vPositionList[i * 36 + 103] = -1.0f;

						shape[i] += 1;

						direction[i] = 4;

						gravity[i] = 0.002;
						break;
					}

					else if (shape[i] == 2)
					{
						vPositionList.erase(vPositionList.begin() + i * 36 + 72, vPositionList.begin() + i * 36 + 108);
						colors.erase(colors.begin() + i * 36 + 72, colors.begin() + i * 36 + 108);
						direction.erase(direction.begin() + i);
						shape.erase(shape.begin() + i);
						gravity.erase(gravity.begin() + i);
						break;
					}
				}
				
			}
		}

		qx = 0, qy = 0;

		cut = false;
	}

	glutPostRedisplay();
}

GLvoid Motion(int x, int y)
{
	ox = (float)(x - 400.0) / 400.0;
	oy = -(float)(y - 400.0) / 400.0;

	if (qx != 0 && qy != 0 && cut)
	{
		vPositionList[0] += ox - qx;
		vPositionList[3] += ox - qx;
		vPositionList[9] += ox - qx;

		vPositionList[1] += oy - qy;
		vPositionList[4] += oy - qy;
		vPositionList[10] += oy - qy;
	}

	qx = ox, qy = oy;

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (!basket)
	{
		for (int i = 0; i < 6; i++)
		{
			vPositionList[i * 3 + 36] += 0.01;
		}

		if (vPositionList[39] > 1)
		{
			for (int i = 0; i < 6; i++)
			{
				vPositionList[i * 3 + 36] -= 0.01;
			}

			basket = true;
		}
	}

	else if (basket)
	{
		for (int i = 0; i < 6; i++)
		{
			vPositionList[i * 3 + 36] -= 0.01;
		}

		if (vPositionList[36] < -1)
		{
			for (int i = 0; i < 6; i++)
			{
				vPositionList[i * 3 + 36] += 0.01;
			}
			
			basket = false;
		}
	}

	if ((std::clock() - lastTime) / CLOCKS_PER_SEC >= 2)
	{
		ran = dir(mt);

		R = obc(mt), G = obc(mt), B = obc(mt);

		ny = ry(mt);

		shap = sha(mt);

		if (ran == 0)
		{
			if (shap == 0)
			{
				vPositionList.insert(vPositionList.end(), {
				1.0f, ny, 0.0f,   1.2f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,
				1.0f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,   1.0f, ny + 0.2f, 0.0f,
				1.0f, ny, 0.0f,   1.2f, ny, 0.0f,   1.1f, ny - 0.1f, 0.0f,
				1.0f, ny + 0.05f, 0.0f,   -1.0f, ny - 0.35f, 0.0f,   0.0f, 0.0f, 0.0f
					});
			}

			else if (shap == 1)
			{
				vPositionList.insert(vPositionList.end(), {
				1.0f, ny, 0.0f,   1.2f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,
				1.0f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,   1.0f, ny + 0.2f, 0.0f,
				1.0f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,   1.0f, ny + 0.2f, 0.0f,
				1.0f, ny + 0.1f, 0.0f,   -1.0f, ny - 0.3f, 0.0f,   0.0f, 0.0f, 0.0f
					});
			}
		}

		else if(ran == 1)
		{
			if (shap == 0)
			{
				vPositionList.insert(vPositionList.end(), {
				1.0f, ny, 0.0f,   1.2f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,
				1.0f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,   1.0f, ny + 0.2f, 0.0f,
				1.0f, ny, 0.0f,   1.2f, ny, 0.0f,   1.1f, ny - 0.1f, 0.0f,
				1.0f, ny + 0.05f, 0.0f,   -1.0f, ny + 0.45f, 0.0f,   0.0f, 0.0f, 0.0f
					});
			}

			else if (shap == 1)
			{
				vPositionList.insert(vPositionList.end(), {
				1.0f, ny, 0.0f,   1.2f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,
				1.0f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,   1.0f, ny + 0.2f, 0.0f,
				1.0f, ny, 0.0f,   1.2f, ny + 0.2f, 0.0f,   1.0f, ny + 0.2f, 0.0f,
				1.0f, ny + 0.1f, 0.0f,   -1.0f, ny + 0.5f, 0.0f,   0.0f, 0.0f, 0.0f
					});
			}
		}

		else if (ran == 2)
		{
			if (shap == 0)
			{
				vPositionList.insert(vPositionList.end(), {
				-1.2f, ny, 0.0f,   -1.0f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,
				-1.2f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,   -1.2f, ny + 0.2f, 0.0f,
				-1.2f, ny, 0.0f,   -1.0f, ny, 0.0f,   -1.1f, ny - 0.1f, 0.0f,
				-1.0f, ny + 0.05f, 0.0f,   1.0f, ny - 0.35f, 0.0f,   0.0f, 0.0f, 0.0f
					});
			}

			else if (shap == 1)
			{
				vPositionList.insert(vPositionList.end(), {
				-1.2f, ny, 0.0f,   -1.0f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,
				-1.2f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,   -1.2f, ny + 0.2f, 0.0f,
				-1.2f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,   -1.2f, ny + 0.2f, 0.0f,
				-1.0f, ny + 0.1f, 0.0f,   1.0f, ny - 0.3f, 0.0f,   0.0f, 0.0f, 0.0f
					});
			}
		}

		else if (ran == 3)
		{
			if (shap == 0)
			{
				vPositionList.insert(vPositionList.end(), {
				-1.2f, ny, 0.0f,   -1.0f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,
				-1.2f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,   -1.2f, ny + 0.2f, 0.0f,
				-1.2f, ny, 0.0f,   -1.0f, ny, 0.0f,   -1.1f, ny - 0.1f, 0.0f,
				-1.0f, ny + 0.05f, 0.0f,   1.0f, ny + 0.45f, 0.0f,   0.0f, 0.0f, 0.0f
					});
			}

			else if (shap == 1)
			{
				vPositionList.insert(vPositionList.end(), {
				-1.2f, ny, 0.0f,   -1.0f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,
				-1.2f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,   -1.2f, ny + 0.2f, 0.0f,
				-1.2f, ny, 0.0f,   -1.0f, ny + 0.2f, 0.0f,   -1.2f, ny + 0.2f, 0.0f,
				-1.0f, ny + 0.1f, 0.0f,   1.0f, ny + 0.5f, 0.0f,   0.0f, 0.0f, 0.0f
					});
			}
		}

		colors.insert(colors.end(), {
			R, G, B,   R, G, B,   R, G, B,
			R, G, B,   R, G, B,   R, G, B,
			R, G, B,   R, G, B,   R, G, B,
			1.0, 0.0, 0.0,    0.0, 1.0, 0.0,   0.0, 0.0, 0.0
			});

		direction.insert(direction.end(), ran);

		shape.insert(shape.end(), shap);

		gravity.insert(gravity.end(), 0.001);

		lastTime = std::clock();
	}

	if (vPositionList.size() > 72 && direction.size() > 0 && shape.size() > 0)
	{
		for (int i = 0; i < direction.size(); i++)
		{
			if (direction[i] == 0)
			{
				vPositionList[i * 36 + 72] -= 0.005f + speed;
				vPositionList[i * 36 + 75] -= 0.005f + speed;
				vPositionList[i * 36 + 78] -= 0.005f + speed;
				vPositionList[i * 36 + 81] -= 0.005f + speed;
				vPositionList[i * 36 + 84] -= 0.005f + speed;
				vPositionList[i * 36 + 87] -= 0.005f + speed;
				vPositionList[i * 36 + 90] -= 0.005f + speed;
				vPositionList[i * 36 + 93] -= 0.005f + speed;
				vPositionList[i * 36 + 96] -= 0.005f + speed;

				vPositionList[i * 36 + 73] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 76] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 79] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 82] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 85] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 88] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 91] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 94] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 97] -= 0.001f + speed / 5;

				if (vPositionList[i * 36 + 75] < -1 && !cut)
				{
					vPositionList.erase(vPositionList.begin() + i * 36 + 72, vPositionList.begin() + i * 36 + 108);
					colors.erase(colors.begin() + i * 36 + 72, colors.begin() + i * 36 + 108);
					direction.erase(direction.begin() + i);
					shape.erase(shape.begin() + i);
					gravity.erase(gravity.begin() + i);
				}
			}

			else if (direction[i] == 1)
			{
				vPositionList[i * 36 + 72] -= 0.005f + speed;
				vPositionList[i * 36 + 75] -= 0.005f + speed;
				vPositionList[i * 36 + 78] -= 0.005f + speed;
				vPositionList[i * 36 + 81] -= 0.005f + speed;
				vPositionList[i * 36 + 84] -= 0.005f + speed;
				vPositionList[i * 36 + 87] -= 0.005f + speed;
				vPositionList[i * 36 + 90] -= 0.005f + speed;
				vPositionList[i * 36 + 93] -= 0.005f + speed;
				vPositionList[i * 36 + 96] -= 0.005f + speed;

				vPositionList[i * 36 + 73] += 0.001f + speed / 5;
				vPositionList[i * 36 + 76] += 0.001f + speed / 5;
				vPositionList[i * 36 + 79] += 0.001f + speed / 5;
				vPositionList[i * 36 + 82] += 0.001f + speed / 5;
				vPositionList[i * 36 + 85] += 0.001f + speed / 5;
				vPositionList[i * 36 + 88] += 0.001f + speed / 5;
				vPositionList[i * 36 + 91] += 0.001f + speed / 5;
				vPositionList[i * 36 + 94] += 0.001f + speed / 5;
				vPositionList[i * 36 + 97] += 0.001f + speed / 5;

				if (vPositionList[i * 36 + 75] < -1 && !cut)
				{
					vPositionList.erase(vPositionList.begin() + i * 36 + 72, vPositionList.begin() + i * 36 + 108);
					colors.erase(colors.begin() + i * 36 + 72, colors.begin() + i * 36 + 108);
					direction.erase(direction.begin() + i);
					shape.erase(shape.begin() + i);
					gravity.erase(gravity.begin() + i);
				}
			}

			else if (direction[i] == 2)
			{
				vPositionList[i * 36 + 72] += 0.005f + speed;
				vPositionList[i * 36 + 75] += 0.005f + speed;
				vPositionList[i * 36 + 78] += 0.005f + speed;
				vPositionList[i * 36 + 81] += 0.005f + speed;
				vPositionList[i * 36 + 84] += 0.005f + speed;
				vPositionList[i * 36 + 87] += 0.005f + speed;
				vPositionList[i * 36 + 90] += 0.005f + speed;
				vPositionList[i * 36 + 93] += 0.005f + speed;
				vPositionList[i * 36 + 96] += 0.005f + speed;

				vPositionList[i * 36 + 73] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 76] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 79] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 82] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 85] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 88] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 91] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 94] -= 0.001f + speed / 5;
				vPositionList[i * 36 + 97] -= 0.001f + speed / 5;

				if (vPositionList[i * 36 + 72] > 1 && !cut)
				{
					vPositionList.erase(vPositionList.begin() + i * 36 + 72, vPositionList.begin() + i * 36 + 108);
					colors.erase(colors.begin() + i * 36 + 72, colors.begin() + i * 36 + 108);
					direction.erase(direction.begin() + i);
					shape.erase(shape.begin() + i);
					gravity.erase(gravity.begin() + i);
				}
			}

			else if (direction[i] == 3)
			{
				vPositionList[i * 36 + 72] += 0.005f + speed;
				vPositionList[i * 36 + 75] += 0.005f + speed;
				vPositionList[i * 36 + 78] += 0.005f + speed;
				vPositionList[i * 36 + 81] += 0.005f + speed;
				vPositionList[i * 36 + 84] += 0.005f + speed;
				vPositionList[i * 36 + 87] += 0.005f + speed;
				vPositionList[i * 36 + 90] += 0.005f + speed;
				vPositionList[i * 36 + 93] += 0.005f + speed;
				vPositionList[i * 36 + 96] += 0.005f + speed;

				vPositionList[i * 36 + 73] += 0.001f + speed / 5;
				vPositionList[i * 36 + 76] += 0.001f + speed / 5;
				vPositionList[i * 36 + 79] += 0.001f + speed / 5;
				vPositionList[i * 36 + 82] += 0.001f + speed / 5;
				vPositionList[i * 36 + 85] += 0.001f + speed / 5;
				vPositionList[i * 36 + 88] += 0.001f + speed / 5;
				vPositionList[i * 36 + 91] += 0.001f + speed / 5;
				vPositionList[i * 36 + 94] += 0.001f + speed / 5;
				vPositionList[i * 36 + 97] += 0.001f + speed / 5;

				if (vPositionList[i * 36 + 72] > 1 && !cut)
				{
					vPositionList.erase(vPositionList.begin() + i * 36 + 72, vPositionList.begin() + i * 36 + 108);
					colors.erase(colors.begin() + i * 36 + 72, colors.begin() + i * 36 + 108);
					direction.erase(direction.begin() + i);
					shape.erase(shape.begin() + i);
					gravity.erase(gravity.begin() + i);
				}
			}

			else if (direction[i] == 4)
			{
				vPositionList[i * 36 + 73] -= gravity[i];
				vPositionList[i * 36 + 76] -= gravity[i];
				vPositionList[i * 36 + 79] -= gravity[i];
				vPositionList[i * 36 + 82] -= gravity[i];
				vPositionList[i * 36 + 85] -= gravity[i];
				vPositionList[i * 36 + 88] -= gravity[i];
				vPositionList[i * 36 + 91] -= gravity[i];
				vPositionList[i * 36 + 94] -= gravity[i];
				vPositionList[i * 36 + 97] -= gravity[i];

				gravity[i] += 0.0001;

				if (vPositionList[i * 36 + 72] > vPositionList[36] && vPositionList[i * 36 + 75] < vPositionList[39] && vPositionList[i * 36 + 73] < vPositionList[43] && vPositionList[i * 36 + 73] > vPositionList[37])
				{
					vPositionList[i * 36 + 73] += gravity[i];
					vPositionList[i * 36 + 76] += gravity[i];
					vPositionList[i * 36 + 79] += gravity[i];
					vPositionList[i * 36 + 82] += gravity[i];
					vPositionList[i * 36 + 85] += gravity[i];
					vPositionList[i * 36 + 88] += gravity[i];
					vPositionList[i * 36 + 91] += gravity[i];
					vPositionList[i * 36 + 94] += gravity[i];
					vPositionList[i * 36 + 97] += gravity[i];

					vPositionList[i * 36 + 99] = 0.0f;
					vPositionList[i * 36 + 100] = 0.0f;
					vPositionList[i * 36 + 102] = 0.0f;
					vPositionList[i * 36 + 103] = 0.0f;

					direction[i] = 5;

					gravity[i] = 0.0f;
				}

				else if (vPositionList[i * 36 + 73] < -1 && !cut)
				{
					vPositionList.erase(vPositionList.begin() + i * 36 + 72, vPositionList.begin() + i * 36 + 108);
					colors.erase(colors.begin() + i * 36 + 72, colors.begin() + i * 36 + 108);
					direction.erase(direction.begin() + i);
					shape.erase(shape.begin() + i);
					gravity.erase(gravity.begin() + i);
				}
			}

			else if (direction[i] == 5)
			{
				if (!basket)
				{
					vPositionList[i * 36 + 72] += 0.01f;
					vPositionList[i * 36 + 75] += 0.01f;
					vPositionList[i * 36 + 78] += 0.01f;
					vPositionList[i * 36 + 81] += 0.01f;
					vPositionList[i * 36 + 84] += 0.01f;
					vPositionList[i * 36 + 87] += 0.01f;
					vPositionList[i * 36 + 90] += 0.01f;
					vPositionList[i * 36 + 93] += 0.01f;
					vPositionList[i * 36 + 96] += 0.01f;
					vPositionList[i * 36 + 99] += 0.01f;
					vPositionList[i * 36 + 102] += 0.01f;
				}

				else if (basket)
				{
					vPositionList[i * 36 + 72] -= 0.01f;
					vPositionList[i * 36 + 75] -= 0.01f;
					vPositionList[i * 36 + 78] -= 0.01f;
					vPositionList[i * 36 + 81] -= 0.01f;
					vPositionList[i * 36 + 84] -= 0.01f;
					vPositionList[i * 36 + 87] -= 0.01f;
					vPositionList[i * 36 + 90] -= 0.01f;
					vPositionList[i * 36 + 93] -= 0.01f;
					vPositionList[i * 36 + 96] -= 0.01f;
					vPositionList[i * 36 + 99] -= 0.01f;
					vPositionList[i * 36 + 102] -= 0.01f;
				}
			}
		}
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
	glBufferData(GL_ARRAY_BUFFER, vPositionList.size() * sizeof(GLfloat), &vPositionList[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
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