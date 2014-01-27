#include "stdafx.h"
#include "windows.h"
#include "set.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;

/* Функция вызывается при изменении размеров окна. 
	ВНИМАНИЕ! 
	1. Необходимо синхронизировать параметры gluOrtho*
	во всех вызовах.	
	2. В данном варианте установки проекции позиции 
	объектов НЕ центрируются, а только привязываются
	к левой-нижней координате. 
	3. Абсолютный размер объектов также НЕ ИЗМЕНЯЕТСЯ. */
void Reshape(GLint w, GLint h)
{
	// раскомментировать, если определены глобальные переменные:
	// Width = w;
	// Height = h;
	/* устанавливаем размеры области отображения */
	glViewport(0, 0, w, h);
	/* ортографическая проекция */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(oL, w, oB, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Display()
{
	glClearColor(0.8,0.8,0.8,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_QUADS);
		glColor3ub(255,255,255);
		glVertex2i(0,0);
		glVertex2i(0,400);
		glVertex2i(600,400);
		glVertex2i(600,0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(25,25,125);
		glVertex2i(100,100);
		glVertex2i(100,200);
		glVertex2i(200,200);
		glVertex2i(200,100);
	glEnd();	
	
	glFlush();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // см. справочник клавиатурных кодов ASCII здесь: http://www.theasciicode.com.ar/
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
		case 61: // вернуться к первоначальным значениям
			//eyeX=EX;
			//eyeY=EY;
			//eyeZ=EZ;
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
void Init()
{
	gluOrtho2D(oL,oR,oB,oT);
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
	glutReshapeFunc(Reshape);
	glutMainLoop();
}