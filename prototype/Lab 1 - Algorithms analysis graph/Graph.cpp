#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;
// API для задания начальных значений:
// размер окна:
float wWidth 	= 350.0; 	// window width
float wHeight 	= 450.0; 	// window height
// координаты окна:
float offLeft 	= 800.0;	// offset left
float offTop 	= 650.0;	// offset top

void Draw() // callback-функция; название может быть любым
{
	glClear(GL_COLOR_BUFFER_BIT); 				// указать тип очищаемого буфера
	glColor3f(0.0,1.0,0.0);						// создать первоначальную заливку
	glPointSize(15.0); 							// если точки, укажем их размер (в пикселах)
	glBegin(GL_POINTS); // рисуем точки 		// открывающая операторная скобка
	glVertex2f(0.0,0.0);						// построить вершину (точку в пространстве)
	glEnd();									// закрывающая операторная скобка
	glFlush();									// команда принудительно завершить построение
}

void Keyboard(unsigned char key, int x, int y)
{
	// Закрыть окно по нажатию кл. "Пробел":
	if(key==32) exit(0);
}

void init() // название функции может быть любым
{
	glClearColor(0.5,0.5,0.5,1.0); 				// задать цвет очистки экрана
	glMatrixMode(GL_PROJECTION); 				// выбрать тип матрицы
	glLoadIdentity(); 							// загрузить текущую матрицу
	glOrtho( // координаты для:
		-wWidth/2, 	// левой вертикальной плоскости отсечения
		wWidth/2,	// правой вертикальной плоскости отсечения
		-wHeight/2, // верхней горизонтальной плоскости отсечения
		wHeight/2, // нижней горизонтальной плоскости отсечения
		-5.0,		// ближняя дистанция от наблюдателя
		5.0		// дальняя дистанция от наблюдателя
		); 
	/*	умножает текущую матрицу на ортографическую 
	матрицу (ортографический = перпендикулярный).
	См. BlueBook, стр. 210.		*/
} 

int _tmain(int argc, char** argv)
{
	glutInit(&argc, argv); 						// инициализировать GLUT
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 	//
	glutInitWindowSize(wWidth,wHeight);			// задать первоначальные размеры окна
	glutInitWindowPosition(offLeft,offTop); 	// задать отступы окна с графикой относительно окна программы (предыдущий вызов)
	glutCreateWindow("Window name"); 				// создать объект окна и присвоить заголовок
	glutDisplayFunc(Draw); 						// вызвать основую функцию отрисовки
	glutKeyboardFunc(Keyboard);
	init();
	glutMainLoop();								// вызвать основной (бесконечный) цикл выполнения программы
	return 0;
}		

