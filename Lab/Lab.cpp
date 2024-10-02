#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <vector>
#include <algorithm>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> start(5, 10);
std::uniform_int_distribution<int> chance(0, 3);
std::uniform_real_distribution<float> dis(0, 1);
std::uniform_real_distribution<float> fea(-1, 0.6);
std::uniform_real_distribution<float> mut(0.2, 0.4);

float R = 1.0, G = 1.0, B = 1.0;

float ox = 0, oy = 0, fire;

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
		
	}
}

GLvoid TimerFunction(int value)
{
	
}