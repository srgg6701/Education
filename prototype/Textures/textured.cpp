#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include <GL/glaux.h>
#include <iostream>
using namespace std;

#pragma comment (lib, "glaux.lib") 

unsigned int textures[1];

void showLog()
{
	cout<<"pX: "<<pX<<", pY: "<<pY<<", pZ: "<<pZ<<endl
		<<"sx: "<<sX<<", sY: "<<sY<<", sZ: "<<sZ<<endl;
		/*<<"gluLookAt:"<<endl
		<<"eyeX (<:>) : "<<eyeX<<endl
		<<"eyeY (,:.) : "<<eyeY<<endl
		<<"eyeZ ([:]) : "<<eyeZ<<endl
		<<"centerX (x:X) : "<<centerX<<endl
		<<"centerY (y:Y) : "<<centerY<<endl
		<<"centerZ (z:Z) : "<<centerZ<<endl;*/
}

void loadTextures()
{
	// образ текстуры 
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("stone2.bmp");
	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D,textures[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}

void init()
{
	loadTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.5,0.5,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0,4.0,-4.0,4.0,-10.0,10.0); // left right bottom top
	glMatrixMode(GL_MODELVIEW);
}

void Display()
{	
	showLog();
	
	GLUquadricObj* qobj;
	//Очистить экран 
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.0,0.0,0.0); - если раскомментировать, пропадёт текстура.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(sX,sY,sZ);
	glTranslatef(pX,pY,pZ);

	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj,GLU_FILL);
	gluQuadricNormals(qobj,GLU_SMOOTH);
	gluQuadricTexture(qobj, true);
	
	gluSphere(qobj,0.33,50,20);

	glFlush();
}

void Keyboard(unsigned char key, int x, int y)
{
		switch(key) // см. справочник клавиатурных кодов ASCII здесь: http://www.theasciicode.com.ar/
	{
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
			break;
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
			break;

		// arrows:
		case 52:	// 4
			pX-=distStep;
			break;
		case 54:	// 6
			pX+=distStep;
			break;
		case 56:	// 8
			pY+=distStep;
			break;
		case 50:	// 2
			pY-=distStep;
			break;
		// zoom
		case 43: // +
			sX+=zoom;
			sY+=zoom;
			break;
		case 45: // -
			sX-=zoom;
			sY-=zoom;
			break;
		//..................
		case 61: // вернуться к первоначальным значениям
			pX=PX;
			pY=PY;
			pZ=PZ;
			sX=sY=sZ=sDefault;
			//centerX=CX;
			//centerY=CY;
			//centerZ=CZ;
			break;
		// Закрыть окно по нажатию кл. "Пробел":
		case 32: exit(0);
			break;
	}
	if(key!=32) glutPostRedisplay(); // перерисовать окно  
}

void main(int argvc, char**argv)
{
	glutInit(&argvc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(800,250);
	glutCreateWindow("Shape");
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Display);
	init();
	glutMainLoop();
}