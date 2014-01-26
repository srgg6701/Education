#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
#include "vars.h"
#include "markers.h"
using namespace std;

// ��������� ����� ��� �������
void setGrid()
{
// set 20 vertical lines
	int vCount=0; // ���������� ��������� ��������� �������
	for (float offsetLeft = -ww2; offsetLeft <= ww2; offsetLeft+=grid_step) // -ww2 = -(400/2)
	{         //-200,-180,-160,-140,-120,-100 // 200
		//cout<<"offsetLeft,-wh2, offsetLeft, wh2: "<<offsetLeft<<","<<-wh2<<","<<offsetLeft<<","<<wh2<<endl;
			
		// ������� ������ ������ 4-� ��������� (���, ��� ����������� ������ ������ �����):
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
// ��������� ����� ������� � ��������� � ������������ �������� ��� �������� �������� ����
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
		// ������� ������ ����� �������:
		// �����-������
		glVertex2f(Left,Bottom);
		// �����-�������
		glVertex2f(Left,Top);
		// ������-�������
		glVertex2f(Right,Top);
		// ������-������
		glVertex2f(Right,Bottom);
	}
	arrayNumbersRow++;
}
// ������� ������� ����������� ������
void setMarkers()
{
	// ������� ���������� 2-D ������� ��� ���������� ���� �� 1 �� 5. 
	// ��. ����� �����: http://www.canstockphoto.com/pixel-art-numbers-and-mathematical-signs-12800261.html
	// ���������� ������� ������
	glBegin(GL_QUADS);
		int arrayNumbersRow=0;
		for (int i = 1; i <= mrxValue; i++) // mrxValue - ���������� �������� (������)
		{	
			/* ���������� ����� ������ �������
                             -200+20.0     *i*4-50 */
			float currentX = -ww2+	 // -200 ����� ���� �����
                              WinW/mrxValue // 400/5 = 80 ����� ������� ��� ������ (����� 5, �� ���������� ������) �������
							  *i	 // ����� ������� ����� ��������
							  -10;   // �������� ������� ����� ��� ������������� � ���������� �����

			// ��������� ���� � �������� (����� 5�4)
			for (int row = 1; row <= rows; row++)
			{
				// ��������� �������
				buildMarkerRow( arrayNumbersRow,	// ������� ������ ������� � ������� (���������� ������ ����� �������)
								mrxTopLine-rowHeight*row, // ������ ������� ������� ������ � ����� �������
								currentX // ����� ������ �������� �������	
							  );
			}
		}
	glEnd();
}
//
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE); // �������� ������ ���������� �����
	glLineWidth (1.0);
	glLineStipple(1,0xAAAA);
	glBegin(GL_LINES);
		// ��������� �����
		setGrid();
	glEnd();
	glDisable(GL_LINE_STIPPLE);
		// ��������� ������� ������
		setMarkers();
	glFlush();
}
//
void Initialize()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//����� - left-bottom / right-top
	gluOrtho2D(-ww2-offset*2,	//-200 - 20*	2	�����, x	= -160	
				ww2+offset*2,	// 200 + 20*2	������, x	=  240
			   -wh2-offset*2,	//-200 - 20*	2	������, y	= -160
				wh2+offset		// 200 + 20		�������, y	= 220
			  ); 
}
//
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // ��. ���������� ������������ ����� ASCII �����: http://www.theasciicode.com.ar/
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
		case 61: // ��������� � �������������� ���������
		//eyeX=EX;
		//eyeY=EY;
		//eyeZ=EZ;
		//centerX=CX;
		//centerY=CY;
		//centerZ=CZ;
		break; */
		// ������� ���� �� ������� ��. "������":
	case 32: exit(0);
		break;
	}
	if(key!=32) glutPostRedisplay(); // ������������ ����  
}
//
int _tmain(int argc, char** argv)
{
	// �������������
	glutInit(&argc, argv); 
	// 3 ����������� ������� ����� ����������� � ����� �������
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WinW,WinH);
	glutInitWindowPosition(850,200);
	glutCreateWindow("Grid");
	// �����������
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	Initialize();
	glutMainLoop();
	return 0;
}