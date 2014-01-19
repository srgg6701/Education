#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include <iostream>
using namespace std;
void showLog()
{
	cout<<"Rotation data:"<<endl
		<<"axis - "<<endl
		<<"rX: "<<rX<<endl
		<<"rY: "<<rY<<endl
		<<"rZ: "<<rZ<<endl
		<<"angles for axis (rAngle) - "<<endl
		<<"aX: "<<aX<<endl
		<<"aY: "<<aY<<endl
		<<"aZ: "<<aZ<<endl;
}


// ���������� ���������� �������� ����� ����������������
void prepareTranslation()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}
void init(void)
{
	//������� ������� (���������) ����
	glClearColor(0.4,0.0,0.0,0.0);
	//���������� ��������
	prepareTranslation();
}
void display(void)
{
	showLog();
	//�������� ����� 
	glClear(GL_COLOR_BUFFER_BIT);
	//���������� ����� ������� (�������) � ������ //� (0.25, 0.25, 0.0) � (0.75, 0.75, 0.0)
	glColor3f(1.0,1.0,1.0);
	
	prepareTranslation();
	glTranslatef ( trnslX, trnslY, trnslZ );
	glRotatef(rAngle,rX,rY,rZ);
	
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
void setRotationAngle(float &aXYZ, float &rXYZ)
{	
	// �������� ��� ���
	rX=rY=rZ=0.0;		
	/* rX, rY, rZ	��������� ��� �������� - 
	��������� ��������� �������� �������������� ���������� ���������� 
	(��������� �� ������)	*/
	rXYZ = 1.0;			
	// ����������� ���� �������� ��� ��������� ��� 
	aXYZ+=angleStep;	
	/* ��������� �������� ���� �������� ��� ��������� ��� � 
	��������������� ���������� ���������� (�� ������)	*/
	rAngle=aXYZ;		
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
		//-------------------------
		case 120:	// x
			setRotationAngle(aX, rX);
			break;
		case 121:	// y
			setRotationAngle(aY,rY);
			break;
		case 122:	// z
			setRotationAngle(aZ,rZ);
			break;
		//..................
		case 61: // = ��������� � �������������� ���������
			trnslX = trnslY = trnslZ = trnslInit;
			//-----------------------------------
			// �������� ��� �������� ��������:
			aX = aY = aZ = rX = rY = rZ = rAngle = 0.0;
			// ��������� � �������� ��������� �� ���� ����:
			glRotatef(0.0,1.0,0.0,0.0);
			glRotatef(0.0,0.0,1.0,0.0);
			glRotatef(0.0,0.0,0.0,1.0);
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