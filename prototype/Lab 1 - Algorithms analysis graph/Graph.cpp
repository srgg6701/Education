#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;
// API ��� ������� ��������� ��������:
// ������ ����:
float wWidth 	= 350.0; 	// window width
float wHeight 	= 450.0; 	// window height
// ���������� ����:
float offLeft 	= 800.0;	// offset left
float offTop 	= 650.0;	// offset top

void Draw() // callback-�������; �������� ����� ���� �����
{
	glClear(GL_COLOR_BUFFER_BIT); 				// ������� ��� ���������� ������
	glColor3f(0.0,1.0,0.0);						// ������� �������������� �������
	glPointSize(15.0); 							// ���� �����, ������ �� ������ (� ��������)
	glBegin(GL_POINTS); // ������ ����� 		// ����������� ����������� ������
	glVertex2f(0.0,0.0);						// ��������� ������� (����� � ������������)
	glEnd();									// ����������� ����������� ������
	glFlush();									// ������� ������������� ��������� ����������
}

void Keyboard(unsigned char key, int x, int y)
{
	// ������� ���� �� ������� ��. "������":
	if(key==32) exit(0);
}

void init() // �������� ������� ����� ���� �����
{
	glClearColor(0.5,0.5,0.5,1.0); 				// ������ ���� ������� ������
	glMatrixMode(GL_PROJECTION); 				// ������� ��� �������
	glLoadIdentity(); 							// ��������� ������� �������
	glOrtho( // ���������� ���:
		-wWidth/2, 	// ����� ������������ ��������� ���������
		wWidth/2,	// ������ ������������ ��������� ���������
		-wHeight/2, // ������� �������������� ��������� ���������
		wHeight/2, // ������ �������������� ��������� ���������
		-5.0,		// ������� ��������� �� �����������
		5.0		// ������� ��������� �� �����������
		); 
	/*	�������� ������� ������� �� ��������������� 
	������� (��������������� = ����������������).
	��. BlueBook, ���. 210.		*/
} 

int _tmain(int argc, char** argv)
{
	glutInit(&argc, argv); 						// ���������������� GLUT
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 	//
	glutInitWindowSize(wWidth,wHeight);			// ������ �������������� ������� ����
	glutInitWindowPosition(offLeft,offTop); 	// ������ ������� ���� � �������� ������������ ���� ��������� (���������� �����)
	glutCreateWindow("Window name"); 				// ������� ������ ���� � ��������� ���������
	glutDisplayFunc(Draw); 						// ������� ������� ������� ���������
	glutKeyboardFunc(Keyboard);
	init();
	glutMainLoop();								// ������� �������� (�����������) ���� ���������� ���������
	return 0;
}		

