#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;

void Draw()
{

}
void Display()
{
	glClearColor(0.0,0.0,0.6,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
		glColor3ub(255,255,255);
		glVertex2i(0,0);
		glVertex2i(0,400);
		glVertex2i(600,400);
		glVertex2i(600,0);
	glEnd();
	glFlush();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // ��. ���������� ������������ ����� ASCII �����: http://www.theasciicode.com.ar/
	{
		/*
		case 60:	// <
		//eyeX-=stepXY;
		break;
		case 62:	// >
		//eyeX+=stepXY;
		break;
		case 44:	// ,
		//eyeY-=stepXY;
		break;
		case 46:	// .
		//eyeY+=stepXY;
		break;
		case 91:	// [
		//eyeZ-=stepXY;
		break;
		case 93:	// ]
		//eyeZ+=stepXY;
		break;	*/
		/*
		//..................
		case 120:	// x
		//centerX-=stepXY;
		break;
		case 88:	// X
		//centerX+=stepXY;
		break;
		case 121:	// y
		//centerY-=stepXY;
		break;
		case 89:	// Y
		//centerY+=stepXY;
		break;
		case 122:	// z
		//centerZ-=stepCZ;
		break;
		case 90:	// Z
		//centerZ+=stepCZ;
		break; 	*/
		/*
		// arrows:
		case 52:	// 4
		//trnslX-=stepTransform;
		break;
		case 54:	// 6
		//trnslX+=stepTransform;
		break;
		case 56:	// 8
		//trnslY+=stepTransform;
		break;
		case 50:	// 2
		//trnslY-=stepTransform;
		break;	*/
		/*
		// zoom:
		case 43: // +
		//
		break;
		case 45: // -
		//
		break;	*/
		//..................
		case 61: // ��������� � �������������� ���������
			//eyeX=EX;
			//eyeY=EY;
			//eyeZ=EZ;
			//centerX=CX;
			//centerY=CY;
			//centerZ=CZ;
			break;
			// ������� ���� �� ������� ��. "������":
		case 32: exit(0);
			break;
	}
	if(key!=32) glutPostRedisplay(); // ������������ ����  
}
void Init()
{
	gluOrtho2D(-10.0,610,-10.0,410);
}
void main(int arcv, char**argv)
{
	glutInit(&arcv,argv);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(600,200);
	glutCreateWindow("Sample");
	Init();
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}