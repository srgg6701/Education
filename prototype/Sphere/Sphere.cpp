#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include "light.h"
#include <iostream>
using namespace std;
//��������� ������ �������� (�������������/���������������)
bool lookAt = false;
// �������� �����
void showLog()
{
	cout<<"Move it: left - 4, right - 6, up - 8, down - 2"
		<<endl
		<<"Rotation data:"<<endl
		<<"axis - "<<endl
		<<"rX (x): "<<rX<<endl
		<<"rY (y): "<<rY<<endl
		<<"rZ (z): "<<rZ<<endl
		<<"angles for axis (rAngle, no keys) - "<<endl
		<<"aX: "<<aX<<endl
		<<"aY: "<<aY<<endl
		<<"aZ: "<<aZ<<endl
		<<"Lights:"<<endl
		<<"left:"<<endl
		<<"x (l:L): "<<lposLeft[0]<<endl
		<<"y (;::): "<<lposLeft[1]<<endl
		<<"z (':\"): "<<lposLeft[2]<<endl
		<<"right:"<<endl
		<<"x (a:A): "<<lposLeft[0]<<endl // l:L ;:: ':"
		<<"y (s:S): "<<lposLeft[1]<<endl //
		<<"z (d:D): "<<lposLeft[2]<<endl;//
}
//���������� ���������� �������� ����� ����������������
void prepareTranslation()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( -0.5, // left
			  0.5, // right
			 -0.5, // bottom
			  0.5, // top
			 -1.0, // near
			  1.0  // far
		   );
}
//����������� ��������
void prepareMaterial()
{
	//������� ������� (���������) ����
	glClearColor(0.1,0.0,0.3,1.0);
	//������ ��� ����������
	glShadeModel(GL_SMOOTH);
	//������ ��������
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}
//�������� ���������
void enableLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
//������ ���������
//�����
void setLightLeft()
{
	//������ �������� � ���������
	GLfloat light_position[]={lposLeft[0],lposLeft[1],lposLeft[2],lposLeft[3]}; // x,y,z,w
	GLfloat light_color[]	={0.8,0.6,1.0,1.0};
	//����������� ��������
	prepareMaterial();
	//������ ���������
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_color);
	enableLight();
	glEnable(GL_LIGHT0);
}
//������
void setLightRight()
{
	//������ �������� � ���������
	GLfloat light_position[]={lposRight[0],lposRight[1],lposRight[2],lposRight[3]}; // x,y,z,w
	GLfloat light_color[]	={1.0,0.6,0.8,1.0};
	//����������� ��������
	prepareMaterial();
	//������ ���������
	glLightfv(GL_LIGHT1,GL_POSITION,light_position);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light_color);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light_color);
	//�������� ����
	enableLight();
	glEnable(GL_LIGHT1);
}
//������ ��������� ���������
void init(void)
{
	//���������� ��������
	//prepareTranslation();
	//���������� ���������
	setLightLeft();
	setLightRight();
}
//������ ���
void display(void)
{
	showLog();
	//�������� ����� 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//������ ���� �������
	glColor3f(1.0,1.0,1.0);
	//���������� ���������
	setLightLeft();
	setLightRight();

	if(lookAt)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(50.0, 1.0, 3.0, 7.0);

		glMatrixMode(GL_MODELVIEW);/**/
		//�������� �������
		glLoadIdentity();
		//������� �������������(������); ������ ������� ������� � �������� �� ��� ������� �������
		gluLookAt(	eyeX,	eyeY,	eyeZ, // ������� �����������; ����� ����������
					centerX,centerY,centerZ, // ����������� ������ (������� �����������)
					0.0,	1.0,	0.0 
				 );
		//��������� �������������
		glScalef( scl, scl, scl	);
		glRotatef(rAngle,0.0,0.0,1.0);
		glutWireCube(1.0);
		//������� ������
		glutSolidSphere(1.0,50,15);
	}
	else
	{
		//������������� � ��������������
		prepareTranslation();
	
		//����������� �����-������
		glTranslatef ( trnslX, trnslY, trnslZ );
		//������� ������ ��������� ���
		glRotatef(rAngle,rX,rY,rZ);
		//������� ������
		glutSolidSphere(0.2,50,15);
	}
	//�� ����. �������� ��������� ��������������
	//������� OpenGL
	glFlush();
}
//��������� ����� ���������
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
//�������������� ��������� ��������� �����
void setLightRightPos(float &light, int sign)
{
	if(sign==1) light+=lposStep;
	if(sign==-1)light-=lposStep;
}
//���������� ������� ������ ����������
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // ��. ���������� ������������ ����� ASCII �����: http://www.theasciicode.com.ar/
	{	
		// ������������� ��������
				case 60:	// <
			eyeX-=stepXY;
			break;
		case 62:	// >
			eyeX+=stepXY;
			break;
		case 44:	// ,
			eyeY-=stepXY;
			break;
		case 46:	// .
			eyeY+=stepXY;
			break;
		case 91:	// [
			eyeZ-=stepXY;
			break;
		case 93:	// ]
			eyeZ+=stepXY;
			break;
		//..................
		case 120:	// x
			centerX-=stepXY;
			break;
		case 88:	// X
			centerX+=stepXY;
			break;
		case 121:	// y
			centerY-=stepXY;
			break;
		case 89:	// Y
			centerY+=stepXY;
			break;
		case 122:	// z
			centerZ-=stepCZ;
			break;
		case 90:	// Z
			centerZ+=stepCZ;			
			break;
		// ��������������� ��������
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
		case 113:	// q
			setRotationAngle(aX, rX);
			break;
		case 119:	// w
			setRotationAngle(aY,rY);
			break;
		case 101:	// e
			setRotationAngle(aZ,rZ);
			break;
		//-------------------------
		case 97:	//a
			setLightRightPos(lposLeft[0],-1);
			break;
		case 65:	//A
			setLightRightPos(lposLeft[0],1);
			break;
		case 115:	//s
			setLightRightPos(lposLeft[1],-1);
			break;
		case 83:	//S
			setLightRightPos(lposLeft[1],1);
			break;
		case 100:	//d
			setLightRightPos(lposLeft[2],-1);
			break;
		case 68:	//D
			setLightRightPos(lposLeft[2],1);
			break;
		case 108:	//l
			setLightRightPos(lposRight[0],-1);
			break;
		case 76:	//L
			setLightRightPos(lposRight[0],1);
			break;
		case 59:	//;
			setLightRightPos(lposRight[1],-1);
			break;
		case 58:	//:
			setLightRightPos(lposRight[1],1);
			break;
		case 39:	//'
			setLightRightPos(lposRight[2],-1);
			break;
		case 34:	//"
			setLightRightPos(lposRight[2],1);
			break;
		// ������������� ����� ����������
		case 96: // `
			lookAt=(lookAt)? false:true;
			break;
		//..................
		case 61: // = ��������� � �������������� ���������
			// ������������� ��������:
			eyeX	= EX;
			eyeY	= EY;
			eyeZ	= EZ;
			centerX	= CnX;
			centerY	= CnY;
			centerZ	= CnZ;
			//-------------------------------------------
			scl		= scaleInit;
			rAngle	= 0.0;
			
			trnslX = trnslY = trnslZ = trnslInit;
			//-----------------------------------
			// �������� ��� �������� ��������:
			aX = aY = aZ = rX = rY = rZ = rAngle = 0.0;
			// ��������� � �������� ��������� �� ���� ����:
			glRotatef(0.0,1.0,0.0,0.0);
			glRotatef(0.0,0.0,1.0,0.0);
			glRotatef(0.0,0.0,0.0,1.0);
			//--------------------------
			lposLeft[0]=LPLeft[0];
			lposLeft[1]=LPLeft[1];
			lposLeft[2]=LPLeft[2];
			lposLeft[3]=LPLeft[3];
			//--------------------------
			lposRight[0]=LPRight[0];
			lposRight[1]=LPRight[1];
			lposRight[2]=LPRight[2];
			lposRight[3]=LPRight[3];
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
	glutInitWindowPosition(1000,100);
	glutCreateWindow("Square");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}