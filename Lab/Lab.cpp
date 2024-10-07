#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

float halfmoon(float x, float y);

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> start(5, 10);
std::uniform_int_distribution<int> chance(0, 3);
std::uniform_real_distribution<float> dis(0, 1);
std::uniform_real_distribution<float> fea(-1, 0.6);
std::uniform_real_distribution<float> mut(0.2, 0.4);

float R = 1.0, G = 1.0, B = 1.0;

float ox = 0.0, oy = 0.0, fire = 0.0, meteor = 0.0;

struct Rect
{
	float x1;
	float y1;
	float x2;
	float y2;
	float R;
	float G;
	float B;
	int state;

}typedef Rect;

Rect temp = {};

std::vector<Rect> rect, alpha;

int ran = 0;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Example");

	ran = start(mt);

	for (int i = 0; i < ran; i++)
	{
		fire = mut(mt);

		temp.x1 = fea(mt);
		temp.y1 = fea(mt);
		temp.x2 = temp.x1 + fire;
		temp.y2 = temp.y1 + fire;
		temp.R = dis(mt);
		temp.G = dis(mt);
		temp.B = dis(mt);

		rect.push_back(temp);
	}

	glutTimerFunc(10, TimerFunction, 1);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(R, G, B, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto& list : rect)
	{
		glColor3f(list.R, list.G, list.B);
		glRectf(list.x1, list.y1, list.x2, list.y2);
	}

	for (auto& list : alpha)
	{
		glColor3f(list.R, list.G, list.B);
		glRectf(list.x1, list.y1, list.x2, list.y2);
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	ox = (float)(x - 400.0) / 400.0;
	oy = -(float)(y - 400.0) / 400.0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (auto iter = rect.begin(); iter != rect.end();)
		{
			if (ox > iter->x1 && oy > iter->y1 && ox < iter->x2 && oy < iter->y2)
			{
				meteor = chance(mt);

				if (meteor == 0)
				{
					temp.x1 = iter->x1;
					temp.y1 = halfmoon(iter->y1, iter->y2);
					temp.x2 = halfmoon(iter->x1, iter->x2);
					temp.y2 = iter->y2;
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 1;

					alpha.push_back(temp);

					temp.x1 = halfmoon(iter->x1, iter->x2);
					temp.y1 = halfmoon(iter->y1, iter->y2);
					temp.x2 = iter->x2;
					temp.y2 = iter->y2;
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 2;

					alpha.push_back(temp);

					temp.x1 = iter->x1;
					temp.y1 = iter->y1;
					temp.x2 = halfmoon(iter->x1, iter->x2);
					temp.y2 = halfmoon(iter->y1, iter->y2);
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 3;

					alpha.push_back(temp);

					temp.x1 = halfmoon(iter->x1, iter->x2);
					temp.y1 = iter->y1;
					temp.x2 = iter->x2;
					temp.y2 = halfmoon(iter->y1, iter->y2);
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 4;

					alpha.push_back(temp);
				}
				
				else if (meteor == 1)
				{
					temp.x1 = iter->x1;
					temp.y1 = halfmoon(iter->y1, iter->y2);
					temp.x2 = halfmoon(iter->x1, iter->x2);
					temp.y2 = iter->y2;
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 1;

					alpha.push_back(temp);

					temp.x1 = halfmoon(iter->x1, iter->x2);
					temp.y1 = halfmoon(iter->y1, iter->y2);
					temp.x2 = iter->x2;
					temp.y2 = iter->y2;
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 2;

					alpha.push_back(temp);

					temp.x1 = iter->x1;
					temp.y1 = iter->y1;
					temp.x2 = halfmoon(iter->x1, iter->x2);
					temp.y2 = halfmoon(iter->y1, iter->y2);
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 3;

					alpha.push_back(temp);

					temp.x1 = halfmoon(iter->x1, iter->x2);
					temp.y1 = iter->y1;
					temp.x2 = iter->x2;
					temp.y2 = halfmoon(iter->y1, iter->y2);
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 4;

					alpha.push_back(temp);
				}

				else if (meteor == 2)
				{
					temp.x1 = iter->x1;
					temp.y1 = halfmoon(iter->y1, iter->y2);
					temp.x2 = halfmoon(iter->x1, iter->x2);
					temp.y2 = iter->y2;
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 1;

					alpha.push_back(temp);

					temp.x1 = halfmoon(iter->x1, iter->x2);
					temp.y1 = halfmoon(iter->y1, iter->y2);
					temp.x2 = iter->x2;
					temp.y2 = iter->y2;
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 2;

					alpha.push_back(temp);

					temp.x1 = iter->x1;
					temp.y1 = iter->y1;
					temp.x2 = halfmoon(iter->x1, iter->x2);
					temp.y2 = halfmoon(iter->y1, iter->y2);
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 3;

					alpha.push_back(temp);

					temp.x1 = halfmoon(iter->x1, iter->x2);
					temp.y1 = iter->y1;
					temp.x2 = iter->x2;
					temp.y2 = halfmoon(iter->y1, iter->y2);
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 4;

					alpha.push_back(temp);
				}

				else if (meteor == 3)
				{
					temp.x1 = iter->x1;
					temp.y1 = halfmoon(iter->y1, iter->y2);
					temp.x2 = halfmoon(iter->x1, iter->x2);
					temp.y2 = iter->y2;
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 1;

					alpha.push_back(temp);

					temp.x1 = halfmoon(iter->x1, iter->x2);
					temp.y1 = halfmoon(iter->y1, iter->y2);
					temp.x2 = iter->x2;
					temp.y2 = iter->y2;
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 2;

					alpha.push_back(temp);

					temp.x1 = iter->x1;
					temp.y1 = iter->y1;
					temp.x2 = halfmoon(iter->x1, iter->x2);
					temp.y2 = halfmoon(iter->y1, iter->y2);
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 3;

					alpha.push_back(temp);

					temp.x1 = halfmoon(iter->x1, iter->x2);
					temp.y1 = iter->y1;
					temp.x2 = iter->x2;
					temp.y2 = halfmoon(iter->y1, iter->y2);
					temp.R = iter->R;
					temp.G = iter->G;
					temp.B = iter->B;
					temp.state = 4;

					alpha.push_back(temp);
				}

				iter = rect.erase(iter);

				break;
			}

			else
			{
				++iter;
			}
		}
	}
}

GLvoid TimerFunction(int value)
{
	for (auto iter = alpha.begin(); iter != alpha.end();)
	{
		if ((MAX(abs(iter->x1), abs(iter->x2))) - abs(halfmoon(iter->x1, iter->x2)) < 0.025)
		{
			iter = alpha.erase(iter);
		}

		else
		{
			if (iter->state == 1)
			{
				iter->x1 += 0.0005;
				iter->y1 += 0.0005;
				iter->x2 -= 0.0005;
				iter->y2 -= 0.0005;

				iter->x1 -= 0.005;
				iter->x2 -= 0.005;
			}

			else if (iter->state == 2)
			{
				iter->x1 += 0.0005;
				iter->y1 += 0.0005;
				iter->x2 -= 0.0005;
				iter->y2 -= 0.0005;

				iter->y1 += 0.005;
				iter->y2 += 0.005;
			}

			else if (iter->state == 3)
			{
				iter->x1 += 0.0005;
				iter->y1 += 0.0005;
				iter->x2 -= 0.0005;
				iter->y2 -= 0.0005;

				iter->y1 -= 0.005;
				iter->y2 -= 0.005;
			}

			else if (iter->state == 4)
			{
				iter->x1 += 0.0005;
				iter->y1 += 0.0005;
				iter->x2 -= 0.0005;
				iter->y2 -= 0.0005;

				iter->x1 += 0.005;
				iter->x2 += 0.005;
			}

			++iter;
		}
	}

	glutPostRedisplay();

	glutTimerFunc(10, TimerFunction, 1);
}

float halfmoon(float x, float y)
{
	if (x > 0 && y > 0)
	{
		return (x + y) / 2;
	}

	else if (x < 0 && y < 0)
	{
		return (abs(x) + abs(y)) / -2;
	}

	else if (x < 0 && y > 0 && x + y == 0)
	{
		return 0.0;
	}

	else if (x < 0 && y > 0 && x + y > 0)
	{
		return y - ((abs(x) + abs(y)) / 2);
	}

	else if (x < 0 && y > 0 && x + y < 0)
	{
		return x + ((abs(x) + abs(y)) / 2);
	}

	else if (x == 0 && y != 0)
	{
		return y / 2;
	}

	else if (x != 0 && y == 0)
	{
		return x / 2;
	}
}