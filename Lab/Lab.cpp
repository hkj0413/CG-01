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

char* filetobuf(const char* file);

GLfloat vPositionList[] = {
	1.0, 0.0, 0.0,   -1.0, 0.0, 0.0,   0.0, -1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 0.0, 1.0,   0.0, 0.0, -1.0,

	-0.25, -0.25, -0.25,  0.25, -0.25, -0.25,  -0.25, 0.25, -0.25,   0.25, -0.25, -0.25,  0.25, 0.25, -0.25,  -0.25, 0.25, -0.25,
	-0.25, 0.0, -0.25,  0.25, 0.0, -0.25,  -0.25, 0.0, 0.25,   0.25, 0.0, -0.25,  0.25, 0.0, 0.25,  -0.25, 0.0, 0.25,
	-0.25, 0.5, 0.0,  0.25, 0.5, 0.0,  -0.25, 0.0, 0.0,   0.25, 0.5, 0.0,   0.25, 0.0, 0.0,   -0.25, 0.0, 0.0,
	-0.25, -0.25, 0.25,  0.25, -0.25, 0.25,  -0.25, -0.25, -0.25,   0.25, -0.25, 0.25,  0.25, -0.25, -0.25,  -0.25, -0.25, -0.25,
	-0.25, -0.25, -0.25,  -0.25, 0.25, -0.25,  -0.25, -0.25, 0.25,   -0.25, -0.25, 0.25,  -0.25, 0.25, -0.25,  -0.25, 0.25, 0.25,
	0.25, 0.25, -0.25,  0.25, -0.25, -0.25,  0.25, 0.25, 0.25,   0.25, 0.25, 0.25,  0.25, -0.25, -0.25,  0.25, -0.25, 0.25,

	-0.25, -0.25, -0.25,  0.25, -0.25, -0.25,  0.25, -0.25, 0.25,  -0.25, -0.25, -0.25,  0.25, -0.25, 0.25,  -0.25, -0.25, 0.25,

	-0.25, -0.25, -0.25,  0.25, -0.25, -0.25,  0.0, 0.25, 0.0,
	0.25, -0.25, -0.25,  0.25, -0.25, 0.25,  0.0, 0.25, 0.0,
	0.25, -0.25, 0.25,  -0.25, -0.25, 0.25,  0.0, 0.25, 0.0,
	-0.25, -0.25, 0.25,  -0.25, -0.25, -0.25,  0.0, 0.25, 0.0,
};

GLfloat colors[] = { 
	0.9, 0.9, 0.9,  0.9, 0.9, 0.9,  0.9, 0.9, 0.9,   0.9, 0.9, 0.9,  0.9, 0.9, 0.9,   0.9, 0.9, 0.9,

	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   0.0, 1.0, 0.0,  1.0, 1.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,   1.0, 1.0, 1.0,  0.0, 1.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   0.0, 1.0, 0.0,  1.0, 1.0, 1.0,   0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,   1.0, 1.0, 1.0,  0.0, 1.0, 0.0,   1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  0.0, 0.0, 1.0,   1.0, 0.0, 0.0,
	1.0, 1.0, 1.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  0.0, 1.0, 0.0,   1.0, 1.0, 1.0,

	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,   1.0, 0.0, 0.0,  0.0, 0.0, 1.0,   1.0, 1.0, 1.0,
	1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
	0.0, 1.0, 0.0,  0.0, 0.0, 1.0,  1.0, 1.0, 1.0,
	0.0, 0.0, 1.0,  1.0, 1.0, 1.0,  1.0, 0.0, 0.0,
	1.0, 1.0, 1.0,  1.0, 0.0, 0.0,  0.0, 1.0, 0.0
};

GLuint VAO, VBO_pos[2];

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.5f);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view = glm::mat4(1.0f);

int check = 0, front6Rotate = 0, side6Translate = 0, back6Scale = 0;

float all = 0.0, top6 = 0.0, front6 = 0.0, side6 = 0.0, back6 = 1.0;

bool hide, allyRotate, top6Rotate;

int main(int argc, char** argv)
{
	width = 800;
	height = 800;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
	glutMainLoop();
}

GLvoid drawScene()
{
	GLfloat rColor, gColor, bColor;

	rColor = bColor = gColor = 0.0;
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramID);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vPositionList), vPositionList);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);

	int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");
	int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
	int projLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");

	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);
	
	glm::mat4 T1y = glm::mat4(1.0f);
	glm::mat4 T1z = glm::mat4(1.0f);
	glm::mat4 R1x = glm::mat4(1.0f);
	glm::mat4 R1y = glm::mat4(1.0f);
	glm::mat4 TR1 = glm::mat4(1.0f);

	glm::mat4 T2y = glm::mat4(1.0f);
	glm::mat4 R2x = glm::mat4(1.0f);
	glm::mat4 TR2 = glm::mat4(1.0f);

	glm::mat4 TR3 = glm::mat4(1.0f);

	glm::mat4 T4y = glm::mat4(1.0f);
	glm::mat4 TR4 = glm::mat4(1.0f);

	glm::mat4 T5y = glm::mat4(1.0f);
	glm::mat4 TR5 = glm::mat4(1.0f);

	glm::mat4 S6xyz = glm::mat4(1.0f);
	glm::mat4 TRS6 = glm::mat4(1.0f);

	Rx = glm::rotate(Rx, glm::radians(20.0f), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(20.0f), glm::vec3(0.0, 1.0, 0.0));
	R = Rx * Ry;
	
	T1y = glm::translate(T1y, glm::vec3(0.0, -0.25, 0.0));
	T1z = glm::translate(T1z, glm::vec3(0.0, 0.0, 0.25));
	R1x = glm::rotate(R1x, glm::radians(front6), glm::vec3(1.0, 0.0, 0.0));
	R1y = glm::rotate(R1y, glm::radians(all), glm::vec3(0.0, 1.0, 0.0));
	TR1 = R * R1y * T1y * T1z * R1x;

	T2y = glm::translate(T2y, glm::vec3(0.0, 0.25, 0.0));
	R2x = glm::rotate(R2x, glm::radians(top6), glm::vec3(1.0, 0.0, 0.0));
	TR2 = R * R1y * T2y * R2x;

	TR3 = R * R1y;

	T4y = glm::translate(T4y, glm::vec3(0.0, side6, 0.0));
	TR4 = R * R1y * T4y;

	T5y = glm::translate(T5y, glm::vec3(0.0, side6, 0.0));
	TR5 = R * R1y * T5y;

	S6xyz = glm::scale(S6xyz, glm::vec3(back6, back6, 1.0));
	TRS6 = R * R1y * S6xyz;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &R[0][0]);

	glm::mat4 vTransform = glm::mat4(1.0f);
	vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &vTransform[0][0]);

	glm::mat4 pTransform = glm::mat4(1.0f);
	pTransform = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &pTransform[0][0]);

	for (int i = 0; i < 3; i++)
	{
		glDrawArrays(GL_LINES, i * 2, 2);
	}

	if (check == 0)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TRS6[0][0]);

		glDrawArrays(GL_TRIANGLES, 6, 6);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR2[0][0]);

		glDrawArrays(GL_TRIANGLES, 12, 6);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR1[0][0]);

		glDrawArrays(GL_TRIANGLES, 18, 6);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR3[0][0]);

		glDrawArrays(GL_TRIANGLES, 24, 6);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR4[0][0]);

		glDrawArrays(GL_TRIANGLES, 30, 6);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR5[0][0]);

		glDrawArrays(GL_TRIANGLES, 36, 6);
	}

	else if (check == 1)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR1[0][0]);

		glDrawArrays(GL_TRIANGLES, 42, 18);

	}

	glutSwapBuffers();
}


GLvoid Reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'h':
		if (!hide)
		{
			glEnable(GL_DEPTH_TEST);


			hide = true;
		}

		else if (hide)
		{
			glDisable(GL_DEPTH_TEST);

			hide = false;
		}
		break;
	case 'y':
		if (!allyRotate)
		{
			allyRotate = true;
		}

		else if (allyRotate)
		{
			all = 0.0;

			allyRotate = false;
		}
		break;
	case 't':
		if (!top6Rotate)
		{
			top6Rotate = true;
		}

		else if (top6Rotate)
		{
			top6 = 0.0;

			top6Rotate = false;
		}
		break;
	case 'f':
		if (front6Rotate == 0)
		{
			front6Rotate = 1;
		}

		else if (front6Rotate == 2)
		{
			front6Rotate = 3;
		}
		break;
	case 's':
		if (side6Translate == 0)
		{
			side6Translate = 1;
		}

		else if (side6Translate == 2)
		{
			side6Translate = 3;
		}
		break;
	case 'b':
		if (back6Scale == 0)
		{
			back6Scale = 1;
		}

		else if (back6Scale == 2)
		{
			back6Scale = 3;
		}
		break;
	case 'z':
		cameraPos.z += 0.1;;
		break;
	case 'Z':
		cameraPos.z -= 0.1;;
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
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (allyRotate)
	{
		all -= 1.0;
	}

	if (top6Rotate)
	{
		top6 += 1.0;
	}

	if (front6Rotate == 1)
	{
		front6 += 1.0;

		if (front6 == 90.0)
		{
			front6Rotate = 2;
		}
	}

	else if (front6Rotate == 3)
	{
		front6 -= 1.0;

		if (front6 == 0.0)
		{
			front6Rotate = 0;
		}
	}

	if (side6Translate == 1)
	{
		side6 += 0.01;

		if (side6 >= 0.5)
		{
			side6 = 0.5;

			side6Translate = 2;
		}
	}

	else if (side6Translate == 3)
	{
		side6 -= 0.01;

		if (side6 <= 0.0)
		{
			side6 = 0.0;

			side6Translate = 0;
		}
	}

	if (back6Scale == 1)
	{
		back6 -= 0.01;

		if (back6 <= 0.0)
		{
			back6 = 0.0;

			back6Scale = 2;
		}
	}

	else if (back6Scale == 3)
	{
		back6 += 0.01;

		if (back6 >= 1.0)
		{
			back6 = 1.0;

			back6Scale = 0;
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