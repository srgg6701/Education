#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
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
	glutMainLoop();
	return 0;
}