#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);

float R = 0.5, G = 0.5, B = 0.5;

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

Rect rect[4] = { -0.75, 0.25, -0.25, 0.75, 1.0, 0.75, 0.0,
				  0.25, 0.25, 0.75, 0.75, 0.25, 1.0, 0.0,
				 -0.75, -0.75, -0.25, -0.25, 1.0, 0.5, 0.0, 
				  0.25, -0.75, 0.75, -0.25, 0.5, 0.75, 1.0 };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
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
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(R, G, B, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 4; i++)
	{
		glColor3f(rect[i].R, rect[i].G, rect[i].B);
		glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	float ox = 0, oy = 0;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::normal_distribution<float> dis(0, 1);

	ox = (float)(x - 500.0) / 500.0;
	oy = -(float)(y - 500.0) / 500.0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ox > rect[0].x1 && ox < rect[0].x2 && oy > rect[0].y1 && oy < rect[0].y2)
	{
		rect[0].R = dis(mt), rect[0].B = dis(mt), rect[0].G = dis(mt);
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ox > rect[1].x1 && ox < rect[1].x2 && oy > rect[1].y1 && oy < rect[1].y2)
	{
		rect[1].R = dis(mt), rect[1].B = dis(mt), rect[1].G = dis(mt);
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ox > rect[2].x1 && ox < rect[2].x2 && oy > rect[2].y1 && oy < rect[2].y2)
	{
		rect[2].R = dis(mt), rect[2].B = dis(mt), rect[2].G = dis(mt);
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ox > rect[3].x1 && ox < rect[3].x2 && oy > rect[3].y1 && oy < rect[3].y2)
	{
		rect[3].R = dis(mt), rect[3].B = dis(mt), rect[3].G = dis(mt);
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		R = dis(mt), B = dis(mt), G = dis(mt);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && ox > rect[0].x1 && ox < rect[0].x2 && oy > rect[0].y1 && oy < rect[0].y2)
	{
		if (rect[0].x1 < -0.75 && rect[0].y1 < 0.25 && rect[0].x2 > -0.25 && rect[0].y2 > 0.75)
		{
			rect[0].x1 += 0.05;
			rect[0].y1 += 0.05;
			rect[0].x2 -= 0.05;
			rect[0].y2 -= 0.05;
		}
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x > 0 && x < 500 && y > 0 && y < 500)
	{
		rect[0].x1 -= 0.05;
		rect[0].y1 -= 0.05;
		rect[0].x2 += 0.05;
		rect[0].y2 += 0.05;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && ox > rect[1].x1 && ox < rect[1].x2 && oy > rect[1].y1 && oy < rect[1].y2)
	{
		rect[1].R = dis(mt), rect[1].B = dis(mt), rect[1].G = dis(mt);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && ox > rect[2].x1 && ox < rect[2].x2 && oy > rect[2].y1 && oy < rect[2].y2)
	{
		rect[2].R = dis(mt), rect[2].B = dis(mt), rect[2].G = dis(mt);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && ox > rect[3].x1 && ox < rect[3].x2 && oy > rect[3].y1 && oy < rect[3].y2)
	{
		rect[3].R = dis(mt), rect[3].B = dis(mt), rect[3].G = dis(mt);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		R = dis(mt), B = dis(mt), G = dis(mt);
	}
}