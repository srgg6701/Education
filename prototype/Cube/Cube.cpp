#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include <iostream>
using namespace std;

bool lookAt = true;
//bool lookAt = false;

void showLog()
{
	cout<<"lookAt: "<<lookAt<<endl
		<<"CAMERA:"<<endl
		<<"eyeX (<:>) : "<<eyeX<<endl
		<<"eyeY (,:.) : "<<eyeY<<endl
		<<"eyeZ ([:]) : "<<eyeZ<<endl
		<<"centerX (x:X) : "<<centerX<<endl
		<<"centerY (y:Y) : "<<centerY<<endl
		<<"centerZ (z:Z) : "<<centerZ<<endl
		<<"TRANSFORMATIONS:"<<endl
		<<"scl (+:-) : "<<scl<<endl
		<<"trnslX (4:6) : "<<trnslX<<endl
		<<"trnslY (8:2) : "<<trnslY<<endl;
}
//�������������
void init(void)
{
	glClearColor(0.2,0.0,0.3,1.0);
	glShadeModel(GL_FLAT);
}
//�����������
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// ���� ������ ������ ����� ����� � ������������, ������� ��� ����� ������
	if(eyeZ==0) glClearColor(0.0,0.0,0.0,1.0);
	else
	{
		// ���� ������ ��������� �� ����� ����������, ��� ����� �����, ��� �������
		if(eyeZ>0)	glClearColor(0.2,0.0,0.3,1.0);
		// ���� ������ ����� �� ����� ����������, ������� ��������
		else		glClearColor(0.3,0.0,0.2,1.0);
	}
	// ���� ������� ������� ���� �������������, ������� ��� �����
	if(scl<0)	glColor3f(1.0,1.0,0.0);
	// ����� - �����
	else		glColor3f(1.0,1.0,1.0);

	if(lookAt)
	{
		//�������� �������
		glLoadIdentity();
		//������� �������������(������)
		gluLookAt(	// ������ ������� ������� � �������� �� ��� ������� �������
					// ������� �����������; ����� ����������
					eyeX, // eye x
					eyeY, // eye y
					eyeZ, // eye z
					// ����������� ������ (������� �����������)
					centerX, // x
					centerY, // y 
					centerZ, // z
					// 
					0.0,
					1.0,
					0.0 
				 );
		glutWireCube(1.0);
	}
	else
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// left, right, bottom, top, near, far
		glOrtho(-1.0,1.0,-1.0,1.0,-5.0,1.0);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//��������� �������������
		glScalef( scl, scl, scl	);
		glTranslatef ( trnslX, trnslY, trnslZ );
		glutWireCube(0.25);
	}
	/**/
	showLog();
	glFlush();
}
//��������� �������� ����
void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
	glMatrixMode(GL_MODELVIEW);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // ��. ���������� ������������ ����� ASCII �����: http://www.theasciicode.com.ar/
	{
		case 96: // `
			lookAt=(lookAt)? false:true;
			break;
		case 60:	// <
			eyeX-=stepXY;
			//lookAt=true;
			break;
		case 62:	// >
			eyeX+=stepXY;
			//lookAt=true;
			break;
		case 44:	// ,
			eyeY-=stepXY;
			//lookAt=true;
			break;
		case 46:	// .
			eyeY+=stepXY;
			//lookAt=true;
			break;
		case 91:	// [
			eyeZ-=stepXY;
			//lookAt=true;
			break;
		case 93:	// ]
			eyeZ+=stepXY;
			//lookAt=true;
			break;
		//..................
		case 120:	// x
			centerX-=stepXY;
			//lookAt=true;
			break;
		case 88:	// X
			centerX+=stepXY;
			//lookAt=true;
			break;
		case 121:	// y
			centerY-=stepXY;
			//lookAt=true;
			break;
		case 89:	// Y
			centerY+=stepXY;
			//lookAt=true;
			break;
		case 122:	// z
			centerZ-=stepCZ;
			//lookAt=true;
			break;
		case 90:	// Z
			centerZ+=stepCZ;
			//lookAt=true;
			break;
		// --------------------------------------
		// transformations beyound gluLookAt():
		case 43: // +
			scl+=stepTransform;
			//lookAt=false;
			break;
		case 45: // -
			scl-=stepTransform;
			//lookAt=false;
			break;
		case 52:	// 4
			trnslX-=stepTransform;
			//lookAt=false;
			break;
		case 54:	// 6
			trnslX+=stepTransform;
			//lookAt=false;
			break;
		case 56:	// 8
			trnslY+=stepTransform;
			//lookAt=false;
			break;
		case 50:	// 2
			trnslY-=stepTransform;
			//lookAt=false;
			break;
		/*case :

			break;
		case :

			break;
		*/
		case 61: // ��������� � �������������� ���������
			eyeX	= EX;
			eyeY	= EY;
			eyeZ	= EZ;
			centerX	= CnX;
			centerY	= CnY;
			centerZ	= CnZ;
			//-------------------------------------------
			scl		= scaleInit;
			//lookAt	= true;
			trnslX	= trnslY = trnslZ = trnslInit;
			break;
		// ������� ���� �� ������� ��. "������":
		case 32: exit(0);
			break;
	}
	if(key!=32) 
	{
		cout<<"pushed: "<<key<<endl;
		glutPostRedisplay(); // ������������ ���� 
	}
}
//
int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(800,100);
	glutCreateWindow("Transformed Cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}