#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

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
GLUquadricObj* qobj;;

char* filetobuf(const char* file);

GLfloat vPositionList[] = {
	1.0, 0.0, 0.0,   -1.0, 0.0, 0.0,   0.0, -1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 0.0, 1.0,   0.0, 0.0, -1.0,
	-0.25, -0.25, -0.5,  0.25, -0.25, -0.5,  -0.25, 0.25, -0.5,   0.25, -0.25, -0.5,  0.25, 0.25, -0.5,  -0.25, 0.25, -0.5,
	-0.25, 0.25, -0.5,  0.25, 0.25, -0.5,  -0.25, 0.25, 0.0,   0.25, 0.25, -0.5,  0.25, 0.25, 0.0,  -0.25, 0.25, 0.0,
	-0.25, 0.25, 0.0,  0.25, 0.25, 0.0,  -0.25, -0.25, 0.0,   0.25, 0.25, 0.0,   0.25, -0.25, 0.0,   -0.25, -0.25, 0.0,
	-0.25, -0.25, 0.0,  0.25, -0.25, 0.0,  -0.25, -0.25, -0.5,   0.25, -0.25, 0.0,  0.25, -0.25, -0.5,  -0.25, -0.25, -0.5,
	-0.25, -0.25, -0.5,  -0.25, 0.25, -0.5,  -0.25, -0.25, 0.0,   -0.25, -0.25, 0.0,  -0.25, 0.25, -0.5,  -0.25, 0.25, 0.0,
	0.25, 0.25, -0.5,  0.25, -0.25, -0.5,  0.25, 0.25, 0.0,   0.25, 0.25, 0.0,  0.25, -0.25, -0.5,  0.25, -0.25, 0.0,
};

GLfloat colors[] = {
	0.0, 0.0, 0.0,  0.0, 0.0, 0.0,  0.0, 0.0, 0.0,   0.0, 0.0, 0.0,  0.0, 0.0, 0.0,   0.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   0.0, 1.0, 0.0,  1.0, 1.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,   1.0, 1.0, 1.0,  0.0, 1.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   0.0, 1.0, 0.0,  1.0, 1.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,   1.0, 1.0, 1.0,  0.0, 1.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  0.0, 0.0, 1.0,   1.0, 0.0, 0.0,
	1.0, 1.0, 1.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  0.0, 1.0, 0.0,   1.0, 1.0, 1.0,
};

GLuint VAO, VBO_pos[2];

int check = 0, xRotate = 0, yRotate = 0, YRotate = 0, object = 0;

float a = 0.0, b = 0.0, c = 0.0, d = 0.0, e = 0.0, f = 0.0;

int main(int argc, char** argv)
{
	width = 800;
	height = 800;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example");
	glEnable(GL_DEPTH_TEST);

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
	glutMainLoop();
}

GLvoid drawScene()
{
	GLfloat rColor, gColor, bColor;

	rColor = bColor = gColor = 0.9;
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramID);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vPositionList), vPositionList);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");

	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);

	glm::mat4 T1x = glm::mat4(1.0f);
	glm::mat4 T1y = glm::mat4(1.0f);
	glm::mat4 T1z = glm::mat4(1.0f);
	glm::mat4 R1x = glm::mat4(1.0f);
	glm::mat4 R1y = glm::mat4(1.0f);
	glm::mat4 R1Y = glm::mat4(1.0f);
	glm::mat4 TR1 = glm::mat4(1.0f);

	glm::mat4 T2x = glm::mat4(1.0f);
	glm::mat4 T2y = glm::mat4(1.0f);
	glm::mat4 T2z = glm::mat4(1.0f);
	glm::mat4 R2x = glm::mat4(1.0f);
	glm::mat4 R2y = glm::mat4(1.0f);
	glm::mat4 R2Y = glm::mat4(1.0f);
	glm::mat4 TR2 = glm::mat4(1.0f);

	glm::mat4 Nx = glm::mat4(1.0f);
	glm::mat4 Ny = glm::mat4(1.0f);
	glm::mat4 NR = glm::mat4(1.0f);

	Rx = glm::rotate(Rx, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0));
	R = Rx * Ry;

	T1x = glm::translate(T1x, glm::vec3(-0.5, 0.0, 0.0));
	T1y = glm::translate(T1y, glm::vec3(0.0, 0.3, 0.0));
	R1x = glm::rotate(R1x, glm::radians(a), glm::vec3(1.0, 0.0, 0.0));
	R1y = glm::rotate(R1y, glm::radians(b), glm::vec3(0.0, 1.0, 0.0));
	R1Y = glm::rotate(R1Y, glm::radians(c), glm::vec3(0.0, 1.0, 0.0));
	TR1 = R * R1Y * T1x * T1y * R1x * R1y;

	T2x = glm::translate(T2x, glm::vec3(0.5, 0.0, 0.0));
	T2y = glm::translate(T2y, glm::vec3(0.0, 0.3, 0.0));
	T2z = glm::translate(T2z, glm::vec3(0.0, 0.0, -0.25));
	R2x = glm::rotate(R2x, glm::radians(d), glm::vec3(1.0, 0.0, 0.0));
	R2y = glm::rotate(R2y, glm::radians(e), glm::vec3(0.0, 1.0, 0.0));
	R2Y = glm::rotate(R2Y, glm::radians(f), glm::vec3(0.0, 1.0, 0.0));
	TR2 = R * R2Y * T2x * T2y * T2z * R2x * R2y;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(R));

	for (int i = 0; i < 3; i++)
	{
		glDrawArrays(GL_LINES, i * 2, 2);
	}

	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);

	if (check == 0)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1));

		glDrawArrays(GL_TRIANGLES, 6, 36);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2));

		gluCylinder(qobj, 0.25, 0, 0.5, 20, 10);
	}

	else if (check == 1)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1));

		gluCylinder(qobj, 0.25, 0.25, 0.5, 20, 10);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2));

		gluSphere(qobj, 0.25, 20, 10);
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
		object = 1;
		break;
	case '2':
		object = 2;
		break;
	case '3':
		object = 0;
		break;
	case 'x':
		xRotate = 1;
		break;
	case 'X':
		xRotate = -1;
		break;
	case 'y':
		yRotate = 1;
		break;
	case 'Y':
		yRotate = -1;
		break;
	case 'r':
		YRotate = 1;
		break;
	case 'R':
		YRotate = -1;
		break;
	case 'c':
		if (check == 0)
		{
			check = 1;
		}

		else if (check == 1)
		{
			check = 0;
		}
		break;
	case 's':
		a = 0.0;
		b = 0.0;
		c = 0.0;
		d = 0.0;
		e = 0.0;
		f = 0.0;
		object = 0;
		xRotate = 0;
		yRotate = 0;
		YRotate = 0;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (xRotate == 1)
	{
		if (object == 0)
		{
			a += 1.0;
			d += 1.0;
		}

		else if (object == 1)
		{
			a += 1.0;
		}

		else if (object == 2)
		{
			d += 1.0;
		}
	}

	else if (xRotate == -1)
	{
		if (object == 0)
		{
			a -= 1.0;
			d -= 1.0;
		}

		else if (object == 1)
		{
			a -= 1.0;
		}

		else if (object == 2)
		{
			d -= 1.0;
		}
	}

	if (yRotate == 1)
	{
		if (object == 0)
		{
			b += 1.0;
			e += 1.0;
		}

		else if (object == 1)
		{
			b += 1.0;
		}

		else if (object == 2)
		{
			e += 1.0;
		}
	}

	else if (yRotate == -1)
	{
		if (object == 0)
		{
			b -= 1.0;
			e -= 1.0;
		}

		else if (object == 1)
		{
			b -= 1.0;
		}

		else if (object == 2)
		{
			e -= 1.0;
		}
	}

	if (YRotate == 1)
	{
		if (object == 0)
		{
			c += 1.0;
			f += 1.0;
		}

		else if (object == 1)
		{
			c += 1.0;
		}

		else if (object == 2)
		{
			f += 1.0;
		}
	}

	else if (YRotate == -1)
	{
		if (object == 0)
		{
			c -= 1.0;
			f -= 1.0;
		}

		else if (object == 1)
		{
			c -= 1.0;
		}

		else if (object == 2)
		{
			f -= 1.0;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
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