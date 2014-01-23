// A C++ program to find convex hull of a set of points
// http://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
// Refer http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
// for explanation of orientation()
#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include "funx.h"
#include "vars.h"
using namespace std;

// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

std::vector<int> data;

struct Point
{
    int x;
    int y;
};
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    /*  ��� ������ ����� ���� - "������� ����� ����!"
		...������ ��-��������������� - �����-�� ��� ����.
		��������� (�) ����������� (��������������� � ����� 
		������) �������, ��� ���, � ����������, ��� ������������
		�������, ���������� �� ������� �����, ����� ��������� - 
		������ ��� �����. 
	*/
	int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int getOrientation(int indexA, int indexB, int indexC)
{
	/*	A = pX[i]	, pY[i], 
		B = pX[i+1] , pY[i+1], 
		C = pX[i+2] , pY[i+2], 
		
		A[0]A[1] - pX[i]		pY[i]
		B[0]B[1] - pX[i+1]	pY[i+1]
		C[0]C[1] - pX[i+2]	pY[i+2]
		if returns positiv value, the C dot is from left,
		otherwise - from right	*/
	//return (B[0]-A[0])				* (C[1]-B[1]) - 
	//		 (B[1]-A[1])				* (C[0]-B[0]);
	int val =	(pX[indexB]-pX[indexA]) * (pY[indexC]-pY[indexB]) -
				(pY[indexB]-pY[indexA]) * (pX[indexC]-pX[indexB]);
	if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
// Prints convex hull of a set of n points.
void convexHull2(Point points[], int n)
{

	// There must be at least 3 points
    if (n < 3) return;
 
    // Initialize Result
    int *next = new int[n];
    for (int i = 0; i < n; i++)
        next[i] = -1;
 
    // Find the leftmost point
    int L = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[L].x)
            L = i;
 
    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again
    int p = L, q;
    do
    {
        // Search for a point 'q' such that orientation(p, i, q) is
        // counterclockwise for all points 'i'
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
          if (orientation(points[p], points[i], points[q]) == 2)
             q = i;
 
        next[p] = q;  // Add q to result as a next point of p
        p = q; // Set p as q for next iteration
    } while (p != L);
 
    // Print Result
    for (int i = 0; i < n; i++)
    {
        if (next[i] != -1)
           cout << "(" << points[i].x << ", " << points[i].y << ")\n";
    } 
}

void convexHull()
{
	// Initialize Result
    int *next = new int[starsCounter];
    for (int i = 0; i < starsCounter; i++)
        next[i] = -1;
 
    // Find the leftmost point
    int L = 0;
    for (int i = 1; i < starsCounter; i++)
        if (pX[1] < pX[L]) L = i; 
 
    
	/*float orient;
	for (int i = 0; i < starsCounter-2; i++)
	{
		orient = getOrientation(i, i+1, i+2);
		if(orient>=0)
		{
			cout<<"x: "<<pX[i]<<", y: "<<pY[i]<<", orient: "<<orient<<endl;
			// save the index of the dot:
			data.push_back(i);
		}
	}*/

	// Start from leftmost point, keep moving counterclockwise
    // until reach the start point again
    int p = L, q;
    do
    {
        // Search for a point 'q' such that orientation(p, i, q) is
        // counterclockwise for all points 'i'
        q = (p+1)%starsCounter;
        for (int i = 0; i < starsCounter; i++)
          if (getOrientation(p,i,q) == 2)
             q = i;
 
        next[p] = q;  // Add q to result as a next point of p
        p = q; // Set p as q for next iteration
    } while (p != L); /**/
 
    
	// Print Result
    for (int i = 0; i < starsCounter; i++)
    {
        if (next[i] != -1)
		{
			cout << "i = "<<i<<"(" << pX[i] << ", " << pY[i] << ")\n";
			data.push_back(i);
		}
    } /**/
}

// Driver program to test above functions
int main(int argvc, char**argv)
{
	glutInit(&argvc, argv);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(660,200);
	glutCreateWindow("Dots");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	init();
	/*Point points[] = {
						{0, 3}, {2, 2}, {1, 1}, {2, 1},
						{3, 0}, {0, 0}, {3, 3}
					};
    int n = sizeof(points)/sizeof(points[0]);
	convexHull2(points, n);*/
    /*
	Point points[starsCounter]={};
	for (int i = 0; i < starsCounter; i++)
	{
		Point points[] = {0,3};
	}*/
	convexHull();
	glutMainLoop();
    return 0;
}

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(10.0,winWidth-10.0,10.0,winHeight-10.0,-10.0,10.0);
	for (int i = 0; i < starsCounter; i++)
	{
		pX[i]	= getRandom(winWidth);
		pY[i]	= getRandom(winHeight);
		r[i]	= getRandom(0.5);
		g[i]	= getRandom(0.5);
		b[i]	= getRandom(0.5);
	}
}
// get the trully random value
float getRandom(float val)
{	
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)) * val;
}
// show gets here!
void Display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//�������� �������
	glLoadIdentity();
	glScalef(0.9,0.9,0.9);
	
	srand(time(NULL));
    setlocale(LC_ALL, "rus");

	glPointSize(6.0);
	glBegin(GL_POINTS);
		for (int i = 0; i < starsCounter; i++)
		{
			//cout<<"pX = "<<pX<<", pY = "<<pY<<"; r: "<<r<<", g: "<<g<<", b: "<<b<<endl;
			glColor3f(r[i],g[i],b[i]);
			glVertex2f(pX[i],pY[i]);
		}
	glEnd();
	glFlush();
}
// handle keys events
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // ��. ���������� ������������ ����� ASCII �����: http://www.theasciicode.com.ar/
	{
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
		break;
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
		break;

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
		break;

		// zoom:
	case 43: // +
		//
		break;
	case 45: // -
		//
		break;
		//..................
	case 61: // ��������� � �������������� ���������
		//eyeX=EX;
		//eyeY=EY;
		//eyeZ=EZ;
		//centerX=CX;
		//centerY=CY;
		//centerZ=CZ;
		break;
		// ������� ���� �� ������� ��. "������":
	case 32: exit(0);
		break;
	}
	if(key!=32) glutPostRedisplay(); // ������������ ����  
}
//=====================================================================
//.....................................................................
// ���������:
// http://habrahabr.ru/post/144921/ -> http://habrahabr.ru/post/144571/
// http://marknelson.us/2007/08/22/convex/