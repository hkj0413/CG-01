#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <vector>
#include <algorithm>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dis(0, 1);
std::uniform_real_distribution<float> fea(-1.0, 0.8);

int max = 0;

float R = 1.0, G = 1.0, B = 1.0;

float ox = 0, oy = 0, nx = 0, ny = 0;

bool move;

struct Rect
{
	float x1;
	float y1;
	float x2;
	float y2;
	float R;
	float G;
	float B;

}typedef Rect;

Rect temp = {}, check = {}, die = {};

std::vector<Rect> rect;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Example");

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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
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
		if (max < 10)
		{
			temp.x1 = fea(mt);
			temp.y1 = fea(mt);
			temp.x2 = temp.x1 + 0.2;
			temp.y2 = temp.y1 + 0.2;
			temp.R = dis(mt);
			temp.G = dis(mt);
			temp.B = dis(mt);

			max++;

			rect.push_back(temp);
		}
		break;
	}

	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y)
{
	ox = (float)(x - 400.0) / 400.0;
	oy = -(float)(y - 400.0) / 400.0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		nx = 0, ny = 0;

		for (auto iter = rect.begin(); iter != rect.end();)
		{
			if (check.x1 < iter->x2 && check.y1 < iter->y2 && check.x2 > iter->x1 && check.y2 > iter->y1 && check.x1 != iter->x1 && check.y1 != iter->y1 && check.x2 != iter->x2 && check.y2 != iter->y2)
			{
				die.x1 = iter->x1;
				die.y1 = iter->y1;
				die.x2 = iter->x2;
				die.y2 = iter->y2;

				iter = rect.erase(iter);

				for (auto& list : rect)
				{
					if (check.x1 == list.x1 && check.y1 == list.y1 && check.x2 == list.x2 && check.y2 == list.y2)
					{
						list.x1 = MIN(die.x1, list.x1);
						list.y1 = MIN(die.y1, list.y1);
						list.x2 = MAX(die.x2, list.x2);
						list.y2 = MAX(die.y2, list.y2);
						list.R = dis(mt);
						list.G = dis(mt);
						list.B = dis(mt);
					}
				}

				break;
			}

			else
			{
				++iter;
			}
		}
	}
}

GLvoid Motion(int x, int y)
{
	ox = (float)(x - 400.0) / 400.0;
	oy = -(float)(y - 400.0) / 400.0;

	for (auto& list : rect)
	{
		if (ox > list.x1 && oy > list.y1 && ox < list.x2 && oy < list.y2 && nx != 0 && ny != 0)
		{
			list.x1 += ox - nx;
			list.y1 += oy - ny;
			list.x2 += ox - nx;
			list.y2 += oy - ny;

			check.x1 = list.x1;
			check.y1 = list.y1;
			check.x2 = list.x2;
			check.y2 = list.y2;
		}
	}

	nx = ox, ny = oy;

	glutPostRedisplay();
}