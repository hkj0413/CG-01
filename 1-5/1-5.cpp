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
GLvoid Motion(int x, int y);

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> start(20, 40);
std::uniform_real_distribution<float> dis(0, 1);
std::uniform_real_distribution<float> fea(-1, 0.9);

float R = 1.0, G = 1.0, B = 1.0;

float ox = 0, oy = 0, kill = 0.1;

bool execute;

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

Rect temp = {}, eraser = {};

std::vector<Rect> rect;

int ran = 0;

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

	if (execute)
	{
		glColor3f(eraser.R, eraser.G, eraser.B);
		glRectf(eraser.x1, eraser.y1, eraser.x2, eraser.y2);
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
	case 'r':
		for (auto iter = rect.begin(); iter != rect.end();)
		{
			iter = rect.erase(iter);
		}

		ran = start(mt);

		for (int i = 0; i < ran; i++)
		{
			temp.x1 = fea(mt);
			temp.y1 = fea(mt);
			temp.x2 = temp.x1 + 0.1;
			temp.y2 = temp.y1 + 0.1;
			temp.R = dis(mt);
			temp.G = dis(mt);
			temp.B = dis(mt);

			rect.push_back(temp);
		}

		kill = 0.1;
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
		execute = true;
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		execute = false;

		eraser.R = 0.0, eraser.G = 0.0, eraser.B = 0.0;
	}
}

GLvoid Motion(int x, int y)
{
	ox = (float)(x - 400.0) / 400.0;
	oy = -(float)(y - 400.0) / 400.0;

	eraser.x1 = ox - kill;
	eraser.y1 = oy - kill;
	eraser.x2 = ox + kill;
	eraser.y2 = oy + kill;

	for (auto iter = rect.begin(); iter != rect.end();)
	{
		if (eraser.x1 < iter->x2 && eraser.y1 < iter->y2 && eraser.x2 > iter->x1 && eraser.y2 > iter->y1)
		{
			eraser.R = iter->R;
			eraser.G = iter->G;
			eraser.B = iter->B;

			iter = rect.erase(iter);

			kill += 0.025;
		}

		else
		{
			++iter;
		}
	}

	glutPostRedisplay();
}