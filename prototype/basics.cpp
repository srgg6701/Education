// prototype.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <gl/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(0.0,0.0);
	glEnd();
	glFlush();
}
void Initialize()
{
	glClearColor(0.8,1.0,0.6,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//сетка
	glOrtho(-200.0,200.0,-200.0,200.0,-5.0,5.0); 
}

int _tmain(int argc, char** argv)
{
	// инициализаци€
	glutInit(&argc, argv); 
	// 3 нижележащие функции можно располагать в любом пор€дке
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("example1");
	// регистраци€
	glutDisplayFunc(Draw);
	Initialize();
	glutMainLoop();
	return 0;
}

