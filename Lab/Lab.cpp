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

Rect rect[4] = { -0.75, 0.75, -0.25, 0.25, 1.0, 0.75, 0.0, 
				  0.25, 0.25, 0.75, 0.75, 0.25, 1.0, 0.0,
				 -0.75, -0.75, -0.25, -0.25, 1.0, 0.5, 0.0, 
				  0.25, -0.25, 0.75, -0.75, 0.5, 0.75, 1.0 };

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
	std::random_device rd;
	std::mt19937 mt(rd());
	std::normal_distribution<float> dis(0, 1);
	R = dis(mt), B = dis(mt), G = dis(mt);
}