#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>

#include "vars.h"

#include "funx.h"

#include <iostream>
//#include "funx.cpp"
using namespace std;

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
}/**/
void Initialize()
{
	glClearColor(0.4,0.4,0.4,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//сетка
	glOrtho(-ww2,	// левый
		     ww2,	// правый
			-wh2,	// нижний
			 wh2,	// верхний
			-200.0,	// ближняя плоскость отсечений
			 200.0	// задняя плоскость отсечения
		   ); 
}
int _tmain(int argc, char** argv)
{
	// инициализация
	glutInit(&argc, argv); 
	// 3 нижележащие функции можно располагать в любом порядке
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WinW,WinH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Grid");
	// регистрация
	glutDisplayFunc(Draw);
	Initialize();
	glutMainLoop();
	return 0;
}