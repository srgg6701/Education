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
    /*  Как сказал Шурик Свин - "головой биццо тута!"
		...говоря по-интеллигентному - здесь-то вся соль.
		Патамушта (с) нижележащая (широкоизвестная в узких 
		кругах) формула, как раз, и определяет, где относительно
		вектора, исходящего из текущей точки, лежит следующая - 
		справа или слева. 
	*/
	int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
// Define the next dot's direction 
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
	/*
	cout<<endl<<
		"( "<<pX[indexB]<<"-"<<pX[indexA]<<" ) * ( "<<pY[indexC]<<"-"<<pY[indexB]<<" ) -"<<endl
		<<"( "<<pY[indexB]<<"-"<<pY[indexA]<<" ) * ( "<<pX[indexC]<<"-"<<pX[indexB]<<" )"<<endl;
	
	cout<<"pX["<<indexA<<"], pY["<<indexA<<"]"<<endl
		<<"pX["<<indexB<<"], pY["<<indexB<<"]"<<endl
		<<"pX["<<indexC<<"], pY["<<indexC<<"]";*/
	if(val>0) 
	{
		//cout<<endl<<"val>0: "<<val;
	}
	else
	{
		cout<<endl<<"indexC = "<<indexC<<", val<0: "<<val;
	}
	cout<<endl;
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
//
void convexHull()
{
	// Initialize Result
    /*int *next = new int[starsCounter];
    for (int i = 0; i < starsCounter; i++)
        next[i] = -1;*/
 
    // Find the leftmost point
    /*int L = 0;
    for (int i = 1; i < starsCounter; i++)
	{
        cout<< "pX[i] = " <<pX[i]<<",  pX[L] = "<<pX[L]<<endl;
		if (pX[i] < pX[L])
		{
			
			cout<<" pX[1] < pX[L] !"<<endl;
			L = i; 
		}
	}*/
	int L = 0;
	for (int i = 1; i < starsCounter; i++)
	{
		if(pX[i]<pX[0]) L = i; 
		//if (A[P[i]][0]<A[P[0]][0])//: # если P[i]-ая точка лежит левее P[0]-ой точки
			//P[i], P[0] = P[0], P[i] # меняем местами номера этих точек 
	}
	cout<<"starting point["<<L<<"] is "<<pX[L]<<","<<pY[L]<<endl;

	data.push_back(L);
	int counter = 20;
	while (counter)
	{
		int right = 0;
		int orient = 0;
		for(int i=0; i < starsCounter; i++)
		{
		  //if (rotate(A[H[-1]],A[P[right]],A[P[i]])<0):
			orient=getOrientation(-1,right,i);
			if (orient== 2) right = i;
			//cout<<"orient: "<<orient<<", right = "<<right<<endl;
		}
		//if P[right]==H[0]: 
		  //break
		if(L==right) 
			break;
		else
		{
		  data.push_back(right);
		}  
		//H.append(P[right])
		  //del P[right]
		counter--;
	}
	//return
    
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
	/*
	// Start from leftmost point, keep moving counterclockwise
    // until reach the start point again
    int p = L, q;
    do
    {
        // Search for a point 'q' such that orientation(p, i, q) is
        // counterclockwise for all points 'i'
        q = (p+1)%starsCounter;
        for (int i = 0; i < starsCounter; i++)
          if (getOrientation(p,i,q) == 2){
			  cout<<endl<<"i= "<<i<<", orientation= "<<getOrientation(p,i,q)
						<<", add point: "<<pX[i]<<","<<pY[i];
			  q = i;
		  }
		cout<<endl;
        next[p] = q;  // Add q to result as a next point of p
        p = q; // Set p as q for next iteration
    } while (p != L); 
 
    
	// Print Result
    for (int i = 0; i < starsCounter; i++)
    {
        if (next[i] != -1)
		{
			cout << "i = "<<i<<"(" << pX[i] << ", " << pY[i] << ")\n";
			data.push_back(i);
		}
    } */
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
// Generate donts on the space
void generateDots()
{	
	if(random) // random mode
	{
		for (int i = 0; i < starsCounter; i++)
		{
			pX[i]	= getRandom(winWidth);
			pY[i]	= getRandom(winHeight);
		
			r[i]	= getRandom(0.5);
			g[i]	= getRandom(0.5);
			b[i]	= getRandom(0.5);
		}
	}
	else // test mode
	{
		// 8 | 400 x 300 
		float cWidth[starsCounter]			={ 200, 150, 300, 100, 200, 100, 300, 100 };
		float cHeight[starsCounter]			={ 100, 200, 150, 50,  150, 250, 100, 150 };
		float dotColors[starsCounter][3]	={ {1.0,0.0,0.0}, {1.0,0.0,1.0}, 
											   {0.0,0.0,1.0}, {0.0,1.0,0.0},
											   {1.0,1.0,0.0}, {1.0,0.5,0.0}, 
											   {0.5,0.5,1.0}, {0.0,0.0,0.0}
											}; 

		for (int i = 0; i < starsCounter; i++)
		{
			pX[i]	= cWidth[i];
			pY[i]	= cHeight[i];
			r[i]	= dotColors[i][0];
			g[i]	= dotColors[i][1];
			b[i]	= dotColors[i][2];
		}
	}
}
//
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(10.0,winWidth-10.0,10.0,winHeight-10.0,-10.0,10.0);
	generateDots();
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
	//Очистить матрицу
	glLoadIdentity();
	glScalef(0.9,0.9,0.9);
	
	srand(time(NULL));
    setlocale(LC_ALL, "rus");

	glPointSize(6.0);
	glBegin(GL_POINTS);
		for (int i = 0; i < starsCounter; i++)
		{
			cout<<"pX = "<<pX[i]<<", pY = "<<pY[i]
			<<"; r: "<<r[i]<<", g: "<<g[i]<<", b: "<<b[i]<<endl;
			switch (i)
			{
				case 0:
					glColor3f(1.0,0.0,0.0); //red
					break;
				case 1:
					glColor3f(1.0,0.0,1.0); //violet
					break;
				case 2:
					glColor3f(0.0,0.0,1.0); //blue
					break;
				case 3:
					glColor3f(0.0,1.0,0.0); //gren
					break;
				case 4:
					glColor3f(1.0,1.0,0.0); //yellow
					break;
				case 5:
					glColor3f(1.0,0.5,0.0); //orange
					break;
				case 6:
					glColor3f(0.0,0.0,0.0); //black
					break;
				
				default:
					glColor3f(r[i],g[i],b[i]);
					break;
			}
			
			glVertex2f(pX[i],pY[i]);
		}
	glEnd();/**/
	glLineWidth(4.0);
	float clrs[12][3]={
		{1.0,0.0,0.0},{1.0,0.0,1.0},{0.0,0.0,1.0},{1.0,1.0,0.0},
		{1.0,0.0,0.0},{1.0,0.0,1.0}/*,{0.0,0.0,1.0},{1.0,1.0,0.0},
		{1.0,0.0,0.0},{1.0,0.0,1.0},{0.0,0.0,1.0},{1.0,1.0,0.0}*/
	};
	glBegin(GL_LINE_LOOP);
			glColor3f(1.0,0.0,1.0);
		/*glVertex2f(10.0,10.0);
		glVertex2f(10.0,100.0);
		glVertex2f(100.0,100.0);
		glVertex2f(200.0,50.0);
		//glVertex2f(200.0,90.0);
		glVertex2f(100.0,10.0);
		
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,30.0);
		glVertex2f(40.0,30.0);
		glVertex2f(60.0,15.0);
		glVertex2f(40.0,0.0);*/	
		
		int cnt=0;
		int ccnt=0;
		for (size_t i=0; i<data.size(); i++)
		{
			glColor3f(1.0,0.0,1.0);
			if( clrs[ccnt] && (!i || i%2==0) )
			{   ccnt=i-cnt;
				/*cout<<endl<<"SHOW COLORS: i = "<<i<<", ccnt = "<<ccnt<<", colors: "
					<<clrs[ccnt][0]<<","
					<<clrs[ccnt][1]<<","
					<<clrs[ccnt][2]; */
				glColor3f(clrs[ccnt][0],clrs[ccnt][1],clrs[ccnt][2]);
				cnt++; 
			}
			cout<<endl<<"index: "<<data[i]
				<<", pX: "<<pX[data[i]]
				<<", pY: "<<pY[data[i]];
			glVertex2f(pX[data[i]],pY[data[i]]);
		}/**/
	glEnd();
	glFlush();
}
// handle keys events
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // см. справочник клавиатурных кодов ASCII здесь: http://www.theasciicode.com.ar/
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
	case 61: // вернуться к первоначальным значениям
		//eyeX=EX;
		//eyeY=EY;
		//eyeZ=EZ;
		//centerX=CX;
		//centerY=CY;
		//centerZ=CZ;
		break;
		// Закрыть окно по нажатию кл. "Пробел":
	case 32: exit(0);
		break;
	}
	if(key!=32) glutPostRedisplay(); // перерисовать окно  
}
//=====================================================================
//.....................................................................
// материалы:
// http://habrahabr.ru/post/144921/ -> http://habrahabr.ru/post/144571/
// http://marknelson.us/2007/08/22/convex/