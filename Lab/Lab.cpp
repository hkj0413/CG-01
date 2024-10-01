#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <vector>
#include <algorithm>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dis(0, 1);
std::uniform_real_distribution<float> fea(-1.0, 0.8);

int max = 0;

float R = 0.2, G = 0.2, B = 0.2;

float ox = 0, oy = 0;

bool one, two, three, four;

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

Rect temp = {};

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
	case '1':
		glutTimerFunc(100, TimerFunction, 1);
		one = true;
		break;

	case '2':

		break;

	case '3':

		break;

	case '4':
		if (!four)
		{
			glutTimerFunc(100, TimerFunction, 4);
			four = true;
		}

		else if (four)
		{
			four = false;
		}
		break;

	case 's':

		break;

	case 'm':

		break;

	case 'r':
		for (auto iter = rect.begin(); iter != rect.end();)
		{
			iter = rect.erase(iter);

			max = 0;
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
		if (max < 5)
		{
			temp.x1 = ox - 0.1;
			temp.y1 = oy - 0.1;
			temp.x2 = ox + 0.1;
			temp.y2 = oy + 0.1;
			temp.R = dis(mt);
			temp.G = dis(mt);
			temp.B = dis(mt);

			max++;

			rect.push_back(temp);
		}
	}
}

GLvoid TimerFunction(int value)
{
	if (value == 1 && one)
	{
		for (auto& list : rect)
		{
			glColor3f(list.R, list.G, list.B);
			glRectf(list.x1, list.y1, list.x2, list.y2);
		}

		glutTimerFunc(100, TimerFunction, 1);
	}

	if (value == 4 && four)
	{
		for (auto& list : rect)
		{
			list.R = dis(mt), list.B = dis(mt), list.G = dis(mt);
		}

		glutTimerFunc(100, TimerFunction, 4);
	}

	glutPostRedisplay();
}