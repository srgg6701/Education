#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include <iostream>
using namespace std;

bool lookAt = true;

void showLog()
{
	cout<<"Switch between projections (`)"<<endl
		<<"Drop state to default: = "
		<<"++++++++++++++++++++++++++++++"<<endl
		<<"Perspective projection:"<<endl
		<<".............................."<<endl
		<<"Position X (<:>) :\t"<<eyeX<<endl
		<<"Position Y (,:.) :\t"<<eyeY<<endl
		<<"Position Z ([:]) :\t"<<eyeZ<<endl
		<<"Direction X (x:X) :\t"<<centerX<<endl
		<<"Direction Y (y:Y) :\t"<<centerY<<endl
		<<"Direction Z (z:Z) :\t"<<centerZ<<endl
		<<"------------------------------"<<endl
		<<"Ortographic projection:"<<endl
		<<".............................."<<endl
		<<"Scaling (+:-) :\t\t"<<scl<<endl
		<<"Move left/right (4:6) :\t"<<trnslX<<endl
		<<"Move up/down (8:2) :\t"<<trnslY<<endl<<endl;
}
//Инициализация
void init(void)
{
	glClearColor(0.2,0.0,0.3,1.0);
	glShadeModel(GL_FLAT);
}
//Отображение
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// если объект достиг одной линии с наблюдателем, сделаем фон сцены чёрным
	if(eyeZ==0) glClearColor(0.0,0.0,0.0,1.0);
	else
	{
		// если объект находится ДО линии наблюдения, фон более синий, чем красный
		if(eyeZ>0)	glClearColor(0.2,0.0,0.3,1.0);
		// если объект зашёл ЗА линию наблюдения, добавим красного
		else		glClearColor(0.3,0.0,0.2,1.0);
	}
	// если масштаб объекта стал отрицательным, сделаем его жёлтым
	if(scl<0)	glColor3f(1.0,1.0,0.0);
	// иначе - белым
	else		glColor3f(1.0,1.0,1.0);

	if(lookAt)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(50.0, 1.0, 3.0, 7.0);

		glMatrixMode(GL_MODELVIEW);/**/
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
		glScalef( scl, scl, scl	);
		glRotatef(rAngle,0.0,0.0,1.0);
		glutWireCube(1.0);
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// left, right, bottom, top, near, far
		glOrtho(-1.0,1.0,-1.0,1.0,-5.0,1.0);
		//Модельная трансформация
		glScalef( scl, scl, scl	);
		glTranslatef ( trnslX, trnslY, trnslZ );
		glutWireCube(0.5);
	}
	/**/
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
//Сбросить всё на состояние по умолчанию
void setDefaultState()
{
	eyeX	= EX;
	eyeY	= EY;
	eyeZ	= EZ;
	centerX	= CnX;
	centerY	= CnY;
	centerZ	= CnZ;
	//-------------------------------------------
	scl		= scaleInit;
	rAngle	= 0.0;
	trnslX	= trnslY = trnslZ = trnslInit;
}
//Оработать события клавиатуры
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
		// --------------------------------------
		// transformations beyound gluLookAt():
		case 43: // +
			scl+=stepTransform;
			break;
		case 45: // -
			scl-=stepTransform;
			break;
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
		case 47:	// /
			rAngle -=5.0;
			break;
		case 42:	// *
			rAngle +=5.0;
			break;
		// переключиться между проекциями
		case 96: // `
			lookAt=(lookAt)? false:true;
			break;
		/**/
		case 61: // = 
			setDefaultState();
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