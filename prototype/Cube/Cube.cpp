#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include <iostream>
using namespace std;

void showLog()
{
	cout<<"gluLookAt:"<<endl
		<<"eyeX (<:>) : "<<eyeX<<endl
		<<"eyeY (,:.) : "<<eyeY<<endl
		<<"eyeZ ([:]) : "<<eyeZ<<endl
		<<"centerX (x:X) : "<<centerX<<endl
		<<"centerY (y:Y) : "<<centerY<<endl
		<<"centerZ (z:Z) : "<<centerZ<<endl;
}

//Инициализация
void init(void)
{
	glClearColor(0.3,0.0,0.2,1.0);
	glShadeModel(GL_FLAT);
}
//Отображение
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	//Очистить матрицу
	glLoadIdentity();
	//Видовая трансформация(камера)
	gluLookAt(	// Задает видовую матрицу и умножает на нее текущую матрицу
				// позиция наблюдателя; точка наблюдения
				eyeX, // eye x
				eyeY, // eye y
				eyeZ, // eye z
				// направление камеры (взгляда наблюдателя)
				centerX, // x
				centerY, // y 
				centerZ, // z
				// 
				0.0,
				1.0,
				0.0
			 );
	//Модельная трансформация
	glScalef( 1.5,
			  1.5,
			  1.5
			);
	glutWireCube(1.0);
	showLog();
	glFlush();
}
//Изменение размеров окна
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
	switch(key) // см. справочник клавиатурных кодов ASCII здесь: http://www.theasciicode.com.ar/
	{
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
		/**/
		case 61: // вернуться к первоначальным значениям
			eyeX=EX;
			eyeY=EY;
			eyeZ=EZ;
			centerX=CnX;
			centerY=CnY;
			centerZ=CnZ;
			break;
		// Закрыть окно по нажатию кл. "Пробел":
		case 32: exit(0);
			break;
	}
	if(key!=32) 
	{
		cout<<"pushed: "<<key<<endl;
		glutPostRedisplay(); // перерисовать окно 
	}
}


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