#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
#include "vars.h"
#include "markers.h"
using namespace std;

// построить сетку дл€ графика
void setGrid()
{
// set 20 vertical lines
	int vCount=0; // установить индикатор вертикали маркера
	for (float offsetLeft = -ww2; offsetLeft <= ww2; offsetLeft+=grid_step) // -ww2 = -(400/2)
	{         //-200,-180,-160,-140,-120,-100 // 200
		//cout<<"offsetLeft,-wh2, offsetLeft, wh2: "<<offsetLeft<<","<<-wh2<<","<<offsetLeft<<","<<wh2<<endl;
			
		// выделим цветом каждую 4-ю вертикаль (там, где размещаетс€ маркер нового файла):
		if( vCount>0 && vCount%4==0 ) 
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(0.4,0.4,0.4);
		vCount++;

		glVertex2f(offsetLeft,-wh2); // WinH/2; // -400/2
		glVertex2f(offsetLeft, wh2); // WinH/2; // 400/2			
	}
	glColor3f(0.4,0.4,0.4);
	// set horizontal lines
	for (float offsetBottom = -wh2; offsetBottom <= wh2; offsetBottom+=grid_step)
	{
		glVertex2f(-ww2,offsetBottom);
		glVertex2f( ww2,offsetBottom);
	}
}
// построить сетку маркера и заполнить еЄ закрашенными €чейками дл€ создани€ контуров цифр
void buildMarkerRow(int &arrayNumbersRow,float currentRowBottomPos, float currentX)
{
	//cout<<"currentRowBottomPos: "<<currentRowBottomPos<<endl;
	for (int col = 1; col <= cols; col++)
	{   
		float Left		= currentX+colWidth*col;
		float Top		= currentRowBottomPos+rowHeight;
		float Right		= currentX+colWidth*col+colWidth;
		float Bottom	= currentRowBottomPos;

		/*cout<<"\tleft/bottom -\t"<<Left<<":"<<Bottom<<endl
			<<"\tleft/top -\t"<<Left<<":"<<Top<<endl
			<<"\tright/top -\t"<<Right<<":"<<Top<<endl
			<<"\tright/bottom -\t"<<Right<<":"<<Bottom<<endl<<endl; */
		// 
		if(Numbers[arrayNumbersRow][col-1]>0)
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(1.0,1.0,1.0);
		// создать €чейки сетки маркера:
		// лева€-нижн€€
		glVertex2f(Left,Bottom);
		// лева€-верхн€€
		glVertex2f(Left,Top);
		// права€-верхн€€
		glVertex2f(Right,Top);
		// права€-нижн€€
		glVertex2f(Right,Bottom);
	}
	arrayNumbersRow++;
}
// создать маркеры загружаемых файлов
void setMarkers()
{
	// создать внутреннюю 2-D матрицу дл€ построени€ цифр от 1 до 5. 
	// —м. схему здесь: http://www.canstockphoto.com/pixel-art-numbers-and-mathematical-signs-12800261.html
	// Ќарисовать маркеры файлов
	glBegin(GL_QUADS);
		int arrayNumbersRow=0;
		for (int i = 1; i <= mrxValue; i++) // mrxValue - количество маркеров (файлов)
		{	
			/* установить левый отступ маркера
                             -200+20.0     *i*4-50 */
			float currentX = -ww2+	 // -200 левый край сетки
                              WinW/mrxValue // 400/5 = 80 длина отрезка дл€ одного (всего 5, по количеству файлов) маркера
							  *i	 // обща€ текуща€ длина отрезков
							  -10;   // смещение маркера влево дл€ центрировани€ с вертикалью сетки

			// построить блок с маркером (сетка 5х4)
			for (int row = 1; row <= rows; row++)
			{
				// построить маркеры
				buildMarkerRow( arrayNumbersRow,	// текущий индекс массива с цифрами (определ€ет строку сетки маркера)
								mrxTopLine-rowHeight*row, // нижн€€ позици€ текущей строки в сетке маркера
								currentX // левый отступ текущего маркера	
							  );
			}
		}
	glEnd();
}
//
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE); // включить шаблон пунктирной линии
	glLineWidth (1.0);
	glLineStipple(1,0xAAAA);
	glBegin(GL_LINES);
		// построить сетку
		setGrid();
	glEnd();
	glDisable(GL_LINE_STIPPLE);
		// построить маркеры файлов
		setMarkers();
	glFlush();
}
//
void Initialize()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//сетка - left-bottom / right-top
	gluOrtho2D(-ww2-offset*2,	//-200 - 20*	2	левый, x	= -160	
				ww2+offset*2,	// 200 + 20*2	правый, x	=  240
			   -wh2-offset*2,	//-200 - 20*	2	нижний, y	= -160
				wh2+offset		// 200 + 20		верхний, y	= 220
			  ); 
}
//
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
		case 61: // вернутьс€ к первоначальным значени€м
		//eyeX=EX;
		//eyeY=EY;
		//eyeZ=EZ;
		//centerX=CX;
		//centerY=CY;
		//centerZ=CZ;
		break; */
		// «акрыть окно по нажатию кл. "ѕробел":
	case 32: exit(0);
		break;
	}
	if(key!=32) glutPostRedisplay(); // перерисовать окно  
}
//
int _tmain(int argc, char** argv)
{
	// инициализаци€
	glutInit(&argc, argv); 
	// 3 нижележащие функции можно располагать в любом пор€дке
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WinW,WinH);
	glutInitWindowPosition(850,200);
	glutCreateWindow("Grid");
	// регистраци€
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	Initialize();
	glutMainLoop();
	return 0;
}