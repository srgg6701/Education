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
#include <ctime> // если будем измерять время выполнения процедур. А ведь придётся!
using namespace std;

// построить сетку для графа
void setGrid(bool copier=false)
{
	/*	Установить индикатор вертикали, пересекающейся с маркером.
		Нужен как инструмент для выделения каждой 4-й вертикали 
		(20 вертикальдных линий / 5 маркеров) цветом, как места, 
		где располагается маркер одного из 5-ти используемых файлов.		*/
	int vCount=0; 
	/*	Создать (и далее - установить) левую и правую границы для 
		сеток графов; Пространство между ними будет заполняться 
		вертикалями графа.	*/
	float GridLeftEdge, GridRightEdge;  
	/*	Рассчитать значения левой и правой границ сеток графа. 
		Передавайемый параметр copier означает, что строим сетку
		для правого графа. Если параметр не передан, то - для левого. 
		.............................................................
		См. параметры gluOrtho2D, на основе которых рассчитывается
		расположение сеток графов - отступы углов от начала координат:
		левый:	-50, правый: 875, 
		нижний: -50, верхний: 450	*/
	if(copier)
	{
		/*	Половина рабочего пространства окна 
			+ пространство для создания визуального отступа */
		GridLeftEdge	= globSceneWidthHalf+glob_offset*2;		// 450
		GridRightEdge	= globSceneWidth + glob_offset*2;	// 825
	}
	else
	{
		GridLeftEdge	= 0;				//   0
		GridRightEdge	= globSceneWidthHalf;				// 400
	}
	const float grid_left_start		= GridLeftEdge;
	const float grid_right_finish	= GridRightEdge;
	//cout<<"Start grid"<<endl<<"........................."<<endl;
	// установить по 20 вертикальных линий для сеток каждого графа
	while(GridLeftEdge<=grid_right_finish)
	{	// cout<<"GridLeftEdge: "<<GridLeftEdge<<endl;
		// установить вертикали	
		// выделим цветом каждую 4-ю вертикаль (там, где размещается маркер нового файла):
		if( vCount>0 && vCount%4==0 ) 
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(0.4,0.4,0.4);
		vCount++;
		// линии
		glVertex2f(GridLeftEdge, 0); // 
		glVertex2f(GridLeftEdge, globSceneHeight);		// 
		GridLeftEdge+=glob_grid_step;
	}
	glColor3f(0.4,0.4,0.4);
	// установить горизонтали
	for ( float offsetBottom  = 0;	// 
				offsetBottom <= globSceneHeight;		// <= 400
				offsetBottom += glob_grid_step )
	{   //cout<<"offsetBottom: "<<offsetBottom<<"\t";
		glVertex2f(grid_left_start,offsetBottom);
		glVertex2f(grid_right_finish,offsetBottom);
	}	//cout<<endl;
}
// построить сетку маркера и заполнить её закрашенными ячейками для создания контуров цифр
void buildMarkerRow( int &arrayNumbersRow,
					 float Bottom, 
					 float currentLeft
				   )
{
	//cout<<"Bottom: "<<Bottom<<endl;
	for (int col = 1; col <= globMrxCols; col++)
	{   
		// Позиции текущей ячейки в строке сетки маркера
		float Left		= currentLeft+globMrxColWidth*col;
		float Top		= Bottom+globMrxRowHeight;
		float Right		= currentLeft+globMrxColWidth*col+globMrxColWidth;
		//		Bottom	- получена в качестве аргумента функции, равна нижней позиции строки сетки маркера;
		/*cout<<"\tleft/bottom -\t"<<Left<<":"<<Bottom<<endl
			<<"\tleft/top -\t"<<Left<<":"<<Top<<endl
			<<"\tright/top -\t"<<Right<<":"<<Top<<endl
			<<"\tright/bottom -\t"<<Right<<":"<<Bottom<<endl<<endl; */
		// 
		if(globNumbers[arrayNumbersRow][col-1]>0)
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
void setMarkers(bool copier=false)
{
	// создать внутреннюю 2-D матрицу для построения цифр от 1 до 5. 
	// См. схему здесь: http://www.canstockphoto.com/pixel-art-globNumbers-and-mathematical-signs-12800261.html
	// Нарисовать маркеры файлов
	glBegin(GL_QUADS);
		int arrayNumbersRow=0;
		float LeftEdge = (copier)? globSceneWidthHalf+glob_offset*2 : 0;	// 400 : 0
		for (int i = 1; i <= globMrxValue; i++) // globMrxValue - количество маркеров (файлов)
		{	
			// установить левый отступ маркера
			float currentX = LeftEdge +		// левый край сетки (0-400)
                             globSceneWidthHalf/globMrxValue	// 400/5 = 80 длина отрезка для одного (всего 5, по количеству файлов) маркера
							 *i				// общая текущая длина отрезков
							 -15;			// смещение маркера влево для визуального центрирования с выделенной вертикалью сетки
			// построить блок с маркером (сетка 5х4)
			for (int row = 1; row <= globMrxRows; row++)
			{
				// построить маркеры
				buildMarkerRow( /*	текущий индекс массива с цифрами globNumbers
									(внутри функции по нему определяется индекс 
									текущей строки в сетке маркера) */
								arrayNumbersRow,
								/*	нижняя позиция текущей строки в сетке маркера */
								globMrxTopLine-globMrxRowHeight*row,
								/*	левая граница текущей ячейки в строке блока маркера */
								currentX	
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
		glob_files_volumes на нижележащее значение: */
	int decreaser = 100;	
	
	for (int i = 0, len = sizeof(glob_files_volumes)/sizeof(int); i < len; i++)
	{
		std::stringstream sstm;
		sstm << file_name << glob_files_volumes[i];
		file_full_name = sstm.str();

		ofstream f(file_full_name); // создать/пересоздать файл
		int val;
		int jLen = glob_files_volumes[i];
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

void sorting()
{
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
		// на левой сетке
		setMarkers();
		// на правой сетке
		setMarkers(true);
	glFlush();
}
// инициализировать процесс
void Initialize()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// сетка - left-bottom / right-top
	// построить ортографическую проекцию
	gluOrtho2D(-glob_offset*2,		// -50	левый, x	
				globSceneWidth+glob_offset*3,	// 875	правый, x	
			   -glob_offset*2,		// -50	нижний, y	
				globSceneHeight+glob_offset		// 450	верхний, y	
			  ); 
}
// обработать события клавиатуры
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // см. справочник клавиатурных кодов ASCII здесь: http://www.theasciicode.com.ar/
	{
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
	glutInitWindowSize(globSceneWidth,globSceneHeight);
	glutInitWindowPosition(450,200);
	glutCreateWindow("Grid");
	// регистрация
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	Initialize();
	glutMainLoop();
	return 0;
}