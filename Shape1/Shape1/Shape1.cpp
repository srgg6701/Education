// prototype.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <gl/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

float WinW=400.0;
float ww2=WinW/2;

float WinH=400.0;
float wh2=WinH/2;

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.8,0.8,0.8);
	glBegin(GL_LINES);
		// set vertical lines
		for (float i = -ww2; i <= ww2; i+=20.0)
		{
			glVertex2f(i,-wh2);
			glVertex2f(i, wh2);
		}
		// set horizontal lines
		for (float i = -wh2; i <= wh2; i+=20.0)
		{
			glVertex2f(-ww2,i);
			glVertex2f( ww2,i);
		}
	glEnd();
	glFlush();
}
void Initialize()
{
	glClearColor(0.4,0.4,0.4,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//сетка
	glOrtho(-ww2,ww2,-wh2,wh2,-200.0,200.0); 
}
int _tmain(int argc, char** argv)
{
	// инициализаци€
	glutInit(&argc, argv); 
	// 3 нижележащие функции можно располагать в любом пор€дке
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WinW,WinH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Shape 1");
	// регистраци€
	glutDisplayFunc(Draw);
	Initialize();
	glutMainLoop();
	return 0;
}