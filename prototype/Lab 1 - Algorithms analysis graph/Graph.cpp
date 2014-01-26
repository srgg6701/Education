#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
#include "vars.h"
using namespace std;

#define drawOneLine(x1,y1,x2,y2)

//
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE); // �������� ������ ���������� �����
	glLineWidth (1.0);
	glLineStipple(1,0xAAAA);
	glColor3f(0.4,0.4,0.4);
	glBegin(GL_LINES);
		// set 10 vertical lines
		for (float offsetLeft = -ww2; offsetLeft <= ww2; offsetLeft+=grid_step) // -ww2 = -(400/2)
		{         //-200,-180,-160,-140,-120,-100 // 200
			//cout<<"offsetLeft,-wh2, offsetLeft, wh2: "<<offsetLeft<<","<<-wh2<<","<<offsetLeft<<","<<wh2<<endl;
			glVertex2f(offsetLeft,-wh2); // WinH/2; // -400/2
			glVertex2f(offsetLeft, wh2); // WinH/2; // 400/2
		}
		// set horizontal lines
		for (float offsetBottom = -wh2; offsetBottom <= wh2; offsetBottom+=grid_step)
		{
			glVertex2f(-ww2,offsetBottom);
			glVertex2f( ww2,offsetBottom);
		}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(1.0,0.0,0.5);
	// ���������� ��������� ���� (�������� ������� ������ ��� ���� � �����):
	float mW = 20.0;	// ������ �����
	float mH = 20.0;	// ������
	float mBottom = -ww2-mH-10.0; // ������� ����� ��������
	// ������ ����������� ����� ��� ����� �������
	float rows = 5;		// ���������� ����� � ����� �������
	float cols = 4;		// ���������� �������� � ����� �������
	float rowHeight = mH/rows;	// ������ ������ � ����� �������
	float colWidth  = mW/cols;	// ������ �������
	// ���������� ������� ������
	glBegin(GL_QUADS);
		for (int i = 1; i <= 5; i++) // 5 - ���������� �������� (������)
		{	
			/* ���������� ����� ������ �������
                             -200+20.0     *i*4-50 */
			float currentX = -ww2+	 // -200 ����� ���� �����
                              WinW/5 // 400/5 = 80 ����� ������� ��� ������ (����� 5, �� ���������� ������) �������
							  *i	 // ����� ������� ����� ��������
							  -10;   // �������� ������� ����� ��� ������������� � ���������� �����

			// ������ ����� - 4px
			// ����� ������� - 
			// �����-������
			//glVertex2f(currentX,mBottom); // 15 � 20   
			// �����-�������
			//glVertex2f(currentX,mBottom+mH);
			// ��������� ���� � �������� (����� 5�4)
			for (int row = 1; row <= rows; row++)
			{
				float currentRowBottom = mBottom+rowHeight*row;
				cout<<"currentRowBottom: "<<currentRowBottom<<endl;
				for (int col = 1; col <= cols; col++)
				{   
					float Left		= currentX+colWidth*col;
					float Top		= currentRowBottom+rowHeight;
					float Right		= currentX+colWidth*col+colWidth;
					float Bottom	= currentRowBottom;

					cout<<"\tleft/bottom -\t"<<Left<<":"<<Bottom<<endl
						<<"\tleft/top -\t"<<Left<<":"<<Top<<endl
						<<"\tright/top -\t"<<Right<<":"<<Top<<endl
						<<"\tright/bottom -\t"<<Right<<":"<<Bottom<<endl<<endl;
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
			}
			// ������-�������
			//glVertex2f(currentX+mH,mBottom+mH);
			// ������-������
			//glVertex2f(currentX+mH,mBottom);
		}
	glEnd();
	
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