#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include <iostream>
using namespace std;

void init(void)
{
	//������� ������� (���������) ����
	glClearColor(0.4,0.0,0.0,0.0);
	//���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}
void display(void)
{
	//�������� ����� 
	glClear(GL_COLOR_BUFFER_BIT);
	//���������� ����� ������� (�������) � ������ //� (0.25, 0.25, 0.0) � (0.75, 0.75, 0.0)
	glColor3f(1.0,1.0,1.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
	glTranslatef ( trnslX, trnslY, trnslZ );
	
	glBegin(GL_POLYGON);
		glVertex3f(0.25,0.25,0.0);
		glVertex3f(0.75,0.25,0.0);
		glVertex3f(0.75,0.75,0.0);
		glVertex3f(0.25,0.75,0.0);
	glEnd();
	//�� ����. �������� ��������� ��������������
	//������� OpenGL
	glFlush();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // ��. ���������� ������������ ����� ASCII �����: http://www.theasciicode.com.ar/
	{
		case 52:	// 4
			trnslX-=stepTransform;
			break;
		case 54:	// 6
			trnslX+=stepTransform;
			break;
		case 56:	// 8
			trnslY+=stepTransform;
			break;
		case 50:	// 2
			trnslY-=stepTransform;
			break;
			//..................
		case 61: // = ��������� � �������������� ���������
			trnslX=trnslInit;
			trnslY=trnslInit;
			trnslZ=trnslInit;
			break;
			// ������� ���� �� ������� ��. "������":
		case 32: exit(0);
			break;
	}
	if(key!=32) glutPostRedisplay(); // ������������ ����  
}


//���������� ��������� �������������� ����,
//������� ���� � ���������� �hello�.
//���������������� ���������� ������� ��������� ������
//����� � ������� ����
int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Square");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}