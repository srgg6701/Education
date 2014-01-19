#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include "vars.h"
#include <iostream>
using namespace std;

void init(void)
{
	//Выбрать фоновый (очищающий) цвет
	glClearColor(0.4,0.0,0.0,0.0);
	//Установить проекцию
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}
void display(void)
{
	//Очистить экран 
	glClear(GL_COLOR_BUFFER_BIT);
	//Нарисовать белый полигон (квадрат) с углами //в (0.25, 0.25, 0.0) и (0.75, 0.75, 0.0)
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
	//Не ждем. Начинаем выполнять буферизованные
	//команды OpenGL
	glFlush();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // см. справочник клавиатурных кодов ASCII здесь: http://www.theasciicode.com.ar/
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
		case 61: // = вернуться к первоначальным значениям
			trnslX=trnslInit;
			trnslY=trnslInit;
			trnslZ=trnslInit;
			break;
			// Закрыть окно по нажатию кл. "Пробел":
		case 32: exit(0);
			break;
	}
	if(key!=32) glutPostRedisplay(); // перерисовать окно  
}


//Установить начальные характеристики окна,
//открыть окно с заголовком «hello».
//Зарегистрировать дисплейную функцию обратного вызова
//Войти в главный цикл
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