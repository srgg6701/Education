#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <string> // http://en.cppreference.com/w/cpp/string/basic_string/to_string
#include <sstream>
#include <fstream>
//----------------------------------------------------------------------------------
#include <GL/glut.h>
#include "vars.h"
#include "markers.h"
#include <ctime> // если будем измерять время выполнения процедур
using namespace std;

// построить сетку для графа
void setGrid(bool copier=false)
{
// set 20 vertical lines
	int vCount=0; // установить индикатор вертикали маркера
	float GridLeftEdge, GridRightEdge; // установить пространственные пределы генерации сеток 
	// если строим вторую сетку, сделаем поправку базиса для координат объектов
	// см. gluOrtho2D:: левый: -50, правый: 875, нижний: -50, верхний: 450 
	if(copier)
	{
		GridLeftEdge	= ww2+offset*2;		// 450
		GridRightEdge	= WinW + offset*2;	// 825
	}
	else
	{
		GridLeftEdge	= 0;				//   0
		GridRightEdge	= ww2;				// 400
	}
	const float grid_left_start		= GridLeftEdge;
	const float grid_right_finish	= GridRightEdge;
	cout<<"Start grid"<<endl<<"........................."<<endl;
	while(GridLeftEdge<=grid_right_finish)
	{	// cout<<"GridLeftEdge: "<<GridLeftEdge<<endl;
		// установить вертикали	
		// выделим цветом каждую 4-ю вертикаль (там, где размещается маркер нового файла):
		if( vCount>0 && vCount%4==0 ) 
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(0.4,0.4,0.4);
		vCount++;

		glVertex2f(GridLeftEdge, 0); // 
		glVertex2f(GridLeftEdge, WinH);		// 
		GridLeftEdge+=grid_step;
	}
	glColor3f(0.4,0.4,0.4);
	// установить горизонтали
	for ( float offsetBottom  = 0;	// 
				offsetBottom <= WinH;		// <= 400
				offsetBottom += grid_step )
	{   cout<<"offsetBottom: "<<offsetBottom<<"\t";
		glVertex2f(grid_left_start,offsetBottom);
		glVertex2f(grid_right_finish,offsetBottom);
	}	cout<<endl;
}
// построить сетку маркера и заполнить её закрашенными ячейками для создания контуров цифр
void buildMarkerRow( int &arrayNumbersRow,
					 float Bottom, 
					 float currentLeft
				   )
{
	//cout<<"Bottom: "<<Bottom<<endl;
	for (int col = 1; col <= cols; col++)
	{   
		// Позиции текущей ячейки в строке сетки маркера
		float Left		= currentLeft+colWidth*col;
		float Top		= Bottom+rowHeight;
		float Right		= currentLeft+colWidth*col+colWidth;
		//		Bottom	- получена в качестве аргумента функции, равна нижней позиции строки сетки маркера;
		/*cout<<"\tleft/bottom -\t"<<Left<<":"<<Bottom<<endl
			<<"\tleft/top -\t"<<Left<<":"<<Top<<endl
			<<"\tright/top -\t"<<Right<<":"<<Top<<endl
			<<"\tright/bottom -\t"<<Right<<":"<<Bottom<<endl<<endl; */
		// 
		if(Numbers[arrayNumbersRow][col-1]>0)
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(1.0,1.0,1.0);
		// создать ячейки сетки маркера:
		// левая-нижняя
		glVertex2f(Left,Bottom);
		// левая-верхняя
		glVertex2f(Left,Top);
		// правая-верхняя
		glVertex2f(Right,Top);
		// правая-нижняя
		glVertex2f(Right,Bottom);
	}
	arrayNumbersRow++;
}
// создать маркеры загружаемых файлов
void setMarkers()
{
	// создать внутреннюю 2-D матрицу для построения цифр от 1 до 5. 
	// См. схему здесь: http://www.canstockphoto.com/pixel-art-numbers-and-mathematical-signs-12800261.html
	// Нарисовать маркеры файлов
	glBegin(GL_QUADS);
		int arrayNumbersRow=0;
		for (int i = 1; i <= mrxValue; i++) // mrxValue - количество маркеров (файлов)
		{	
			/* установить левый отступ маркера
                             -200+20.0     *i*4-50 */
			float currentX = -ww2+	 // -200 левый край сетки
                              WinW/2/mrxValue // 400/5 = 80 длина отрезка для одного (всего 5, по количеству файлов) маркера
							  *i	 // общая текущая длина отрезков
							  -10;   // смещение маркера влево для центрирования с вертикалью сетки

			// построить блок с маркером (сетка 5х4)
			for (int row = 1; row <= rows; row++)
			{
				// построить маркеры
				buildMarkerRow( arrayNumbersRow,	// текущий индекс массива с цифрами (определяет строку сетки маркера)
								mrxTopLine-rowHeight*row, // нижняя позиция текущей строки в сетке маркера
								currentX // левый отступ текущего маркера	
							  );
			}
		}
	glEnd();
}
// cоздать файлы
void makeFiles()
{
	// отличный сборник решений по канкатенации строк здесь: http://stackoverflow.com/a/900035/1522479
	std::string file_name="file_";
	std::string file_full_name;
	
	// http://ru.cppreference.com/w/cpp/numeric/random/rand
	srand(time(NULL));

	bool run  = true;		// позволить процессу начаться
	/*	если захотим уменьшить количество строк, разделим значения массива
		files_volumes на нижележащее значение: */
	int decreaser = 100;	
	
	for (int i = 0, len = sizeof(files_volumes)/sizeof(int); i < len; i++)
	{
		std::stringstream sstm;
		sstm << file_name << files_volumes[i];
		file_full_name = sstm.str();

		ofstream f(file_full_name); // создать/пересоздать файл
		int val;
		int jLen = files_volumes[i];
		// для теста - если установили уменьшитель, используем его
		if(decreaser>1) jLen/=decreaser;
		
		if(run)
		{				
			while(jLen)
			{
					//сгенерировать случайное число от 0 до 400000
					val = int(double(rand())/RAND_MAX*400000); 
					//cout<<"val : "<<val<<endl;
				f<<val; // сохранить сгенерированный номер в строке
				jLen--; // декременировать счётчик
				if(jLen) f<<endl; // добавить перенос строки, если счётчик не кончился
			}
		}		
	}
}
// построить всё!
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE); // включить шаблон пунктирной линии
	glLineWidth (1.0);
	glLineStipple(1,0xAAAA);
	glBegin(GL_LINES);
		// построить первую (левую) сетку
		setGrid();
		// построить вторую (правую) сетку
		setGrid(true);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
		// построить маркеры файлов
		setMarkers();
	glFlush();
}
// инициализировать процесс
void Initialize()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//сетка - left-bottom / right-top
	gluOrtho2D(-offset*2,		// -50	левый, x	
				WinW+offset*3,	// 875	правый, x	
			   -offset*2,		// -50	нижний, y	
				WinH+offset		// 450	верхний, y	
			  ); 
}
// обработать события клавиатуры
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
		/*
		case 61: // вернуться к первоначальным значениям
		//eyeX=EX;
		//eyeY=EY;
		//eyeZ=EZ;
		//centerX=CX;
		//centerY=CY;
		//centerZ=CZ;
		break; */
		// Закрыть окно по нажатию кл. "Пробел":
	case 32: exit(0);
		break;
	}
	if(key!=32) glutPostRedisplay(); // перерисовать окно  
}
//
int _tmain(int argc, char** argv)
{
	// сгенеирировать/перезаписать файлы
	makeFiles();
	// инициализация
	glutInit(&argc, argv); 
	// 3 нижележащие функции можно располагать в любом порядке
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WinW,WinH);
	glutInitWindowPosition(450,200);
	glutCreateWindow("Grid");
	// регистрация
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	Initialize();
	glutMainLoop();
	return 0;
}