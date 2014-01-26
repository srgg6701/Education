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
	//�����
	glOrtho(-ww2,	// �����
		     ww2,	// ������
			-wh2,	// ������
			 wh2,	// �������
			-200.0,	// ������� ��������� ���������
			 200.0	// ������ ��������� ���������
		   ); 
}
int _tmain(int argc, char** argv)
{
	// �������������
	glutInit(&argc, argv); 
	// 3 ����������� ������� ����� ����������� � ����� �������
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WinW,WinH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Grid");
	// �����������
	glutDisplayFunc(Draw);
	Initialize();
	glutMainLoop();
	return 0;
}