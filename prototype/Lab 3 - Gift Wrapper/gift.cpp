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

std::vector<int> stars;

/*	Define the next dot's direction 
	This is the main formula	*/
int getDotDirection( int indexA, // P	// A
					int indexB,	// i	// B
					int indexC	// q	// C
				  )
{
	/*	// Taken from here: http://habrahabr.ru/post/144921/
		A,B,C
		P, - текуща€ точка обЄртки
		i, - текуща€ точка из общего массива точек
		q  - следующа€ (за точкой из обЄртки) точка 

		( B[0] - A[0] ) * ( C[1] - B[1] ) - ( B[1] - A[1] ) * ( C[0] - B[0] )
		
		A[0] = pX[P]	A[1] = pY[P]
		B[0] = pX[i]	B[1] = pY[i] 
		C[0] = pX[q]	C[1] = pY[q] 
	
		( pX[i]-pX[P] ) * ( pY[q]-pY[i] ) - ( pY[i]-pY[P] ) * ( pX[q]-pX[i] ) */

	// filter points
	int val =	(pX[indexB]-pX[indexA]) * (pY[indexC]-pY[indexB]) -
				(pY[indexB]-pY[indexA]) * (pX[indexC]-pX[indexB]);
	
	if (val == 0) return 0;  // colinear
	bool test = false;
	if (test)
	{	
		cout<<"P: pXY["<<indexA<<"] = "<<pX[indexA]<<","<<pY[indexA]
			<<"\ti: pXY["<<indexB<<"] = "<<pX[indexB]<<","<<pY[indexB]
			<<"\tq: pXY["<<indexC<<"] = "<<pX[indexC]<<","<<pY[indexC]
			<<endl
			<<"val = "<<val<<",";
		if(val>0)
			cout<<"\tskip ";
		else
			cout<<"\tapply ";		
		cout<<"dot ["<<indexB<<"]"<<endl;
	}
	return (val > 0)? 1: 2; // we use clockwise direction
}
//
void wrapStars()
{
	int L = 0;
	
	for (int i = 1; i < starsCounterTest; i++)
		if(pX[i]<pX[L])
			L = i; 
	
	cout<<"\tstarting point is vertex["<<L<<"]:"<<pX[L]<<","<<pY[L]<<endl
		<<".............................................."<<endl;

	int orient;
	int q = 0;
	int P = L;
	int cnt = 0;
	do
	{
		q = P+1;
		for (int i = 0; i < starsCounterTest; i++)
		{
			/*	Get direction of the next dot. If it located from right of vector, 
				we will add this dot to our path */
			orient=getDotDirection(P,i,q);
			// if the next (q) dot is the right one, assign to it the current index
			if(orient==2)
				q=i;  
		}
		cout<<"ADD dot to the vector: pXY["<<q<<"] = "<<pX[q]<<","<<pY[q]<<endl;	
		stars.push_back(q);
		P = q;
		cnt++;
	
		if(cnt>500) 
		{
			cout<<endl<<"Too much! Something went wrong, Dude."<<endl;
			break;
		}
	}
	while(P!=L);
	// test stars:
	if(starsCounterTest)
		for (size_t i=0; i<stars.size(); i++)
		{	if(stars[i])
				cout<<"Dot pXY["<<stars[i]<<"] = "<<pX[stars[i]]<<","<<pY[stars[i]]<<endl;
		}
}
// main
int main(int argvc, char**argv)
{
	glutInit(&argvc, argv);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(660,200);
	glutCreateWindow("Dots");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	bigBang();
	// implement wrapper
	wrapStars();
	glutMainLoop();
    return 0;
}
// Generate donts on the space
void generateStars()
{	
	const int strz = 40;
	starsCounterTest=strz;
	// to turn it on, go to the vars.h
	if(random) // random mode
	{
		for (int i = 0; i < starsCounterTest; i++)
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
		// winWidth x winHeight 
		float cWidth[strz]			={  200, 150, 300, 100, 200, 100, 250, 125,  50, 350, 100, 150, 200, 375, 250, 200 };
		
		float cHeight[strz]			={	100, 200, 150,  50, 150, 250, 100, 125, 100, 250, 175,  75, 275,  25, 200, 200 };
		
		float dotColors[strz][3]	={  {1.0,0.0,0.0}, {1.0,0.0,1.0}, 
										{0.0,0.0,1.0}, {0.0,1.0,0.0},
										{1.0,1.0,0.0}, {1.0,0.5,0.0}, 
										{0.5,1.0,1.0}, {0.0,0.0,0.0},
										{1.0,0.0,0.0}, {1.0,0.0,1.0}, 
										{0.0,0.0,1.0}, {0.0,1.0,0.0},
										{1.0,1.0,0.0}, {1.0,0.5,0.0}, 
										{0.5,1.0,1.0}, {0.0,0.0,0.0}
									}; 
			
		for (int i = 0; i < strz; i++)
		{
			pX[i]	= cWidth[i];
			pY[i]	= cHeight[i];
			r[i]	= dotColors[i][0];
			g[i]	= dotColors[i][1];
			b[i]	= dotColors[i][2];
		}
	}
}
// The Universe starts here!
void bigBang()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(10.0,winWidth-10.0,10.0,winHeight-10.0,-10.0,10.0);
	generateStars();
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
	//ќчистить матрицу
	glLoadIdentity();
	glScalef(0.9,0.9,0.9);
	
	srand(time(NULL));
    setlocale(LC_ALL, "rus");

	glPointSize(12.0);
	glBegin(GL_POINTS);
		for (int i = 0; i < starsCounterTest; i++)
		{
			glColor3f(r[i],g[i],b[i]);
			// build stars
			glVertex2f(pX[i],pY[i]);
		}
	glEnd();
	
	if(random)
	{
		glLineWidth(4.0);
		if(wrapper_path==stars.size())
		{
			glBegin(GL_LINE_LOOP);
				//Set wrapper's lines colors 
				// build wrapper
				buildStarTrackPath();
			glEnd();		
		}
		else
		{	glBegin(GL_LINE_STRIP);
				//Set wrapper's lines colors 
				// build wrapper
				buildStarTrackPath();
			glEnd();
			
		}
	}
	glFlush();
}
//
void buildStarTrackPath()
{
	glColor3f(1.0,0.0,1.0);
		
	int cnt=0;
	int ccnt=0;
	
	glColor3f(1.0,0.0,1.0);

	if(wrapper_path==0)
		glVertex2f(pX[stars[stars.size()-1]],pY[stars[stars.size()-1]]);
	
	// Walk through our constellation
	for (size_t i=0; i<wrapper_path; i++)//stars.size()
	{		
		if(clrs&&ccnt&&!clrs[ccnt])
			ccnt=0; // Drop colors counter to get them again

		if(clrs[ccnt])
		{   
			if(!i || i%2==0) 
			{
				ccnt=i-cnt;
				glColor3f(clrs[ccnt][0],clrs[ccnt][1],clrs[ccnt][2]);
				cnt++; 
			}
		}
		glVertex2f(pX[stars[i]],pY[stars[i]]);
	}
}
// handle keys events
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // см. справочник клавиатурных кодов ASCII здесь: http://www.theasciicode.com.ar/
	{
		case 52:	// 4
			if(wrapper_path)
				wrapper_path--;
			break;
		case 54:	// 6
			if(wrapper_path<stars.size())
				wrapper_path++;
			break;
			//..................
		case 61: // вернутьс€ к первоначальным значени€м
			wrapper_path==0;
			break;
			// «акрыть окно по нажатию кл. "ѕробел":
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