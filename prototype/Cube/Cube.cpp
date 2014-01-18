#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;

void Display()
{
	glBegin(GL_POLYGON);
		glVertex3f(0.25,0.25,0.0);
		glVertex3f(0.75,0.25,0.0);
		glVertex3f(0.75,0.75,0.0);
		glVertex3f(0.25,0.75,0.0);
	glEnd();
}
void main(int argcv, char** argv)
{
	glutInit(&argcv, argv);
	glutInitWindowSize(400,400);			// ������ �������������� ������� ����
	glutInitWindowPosition(600,200); 	// ������ ������� ���� � �������� ������������ 
	glutCreateWindow("Window");

	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
	glutDisplayFunc(Display);
	glutMainLoop();
	glFlush();
}

