#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);

float R = 1.0, G = 1.0, B = 1.0;

bool repeat = false;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");

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
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(R, G, B, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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
	case 'c':
		R = 0.0, G = 1.0, B = 1.0;
		break;
	case 'm':
		R = 1.0, G = 0.0, B = 1.0;
		break;
	case 'y':
		R = 1.0, G = 1.0, B = 0.0;
		break;
	case 'w':
		R = 1.0, G = 1.0, B = 1.0;
		break;
	case 'k':
		R = 0.0, G = 0.0, B = 0.0;
		break;
	case 'a':
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case 't':
		glutTimerFunc(100, TimerFunction, 1);
		repeat = true;
		break;
	case 's':
		repeat = false;
		break;
	case 'q':
		glutLeaveMainLoop();
	}

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::normal_distribution<float> dis(0, 1);
	R = dis(mt), B = dis(mt), G = dis(mt);

	glutPostRedisplay();

	if (repeat)
	{
		glutTimerFunc(100, TimerFunction, 1);
	}
}