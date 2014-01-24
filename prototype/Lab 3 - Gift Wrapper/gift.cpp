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

// Define InfbigBange (Using INT_MAX caused overflow problems)
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
    /*   ак сказал Ўурик —вин - "головой биццо тута!"
		...говор€ по-интеллигентному - здесь-то вс€ соль.
		ѕатамушта (с) нижележаща€ (широкоизвестна€ в узких 
		кругах) формула, как раз, и определ€ет, где относительно
		вектора, исход€щего из текущей точки, лежит следующа€ - 
		справа или слева. 
	*/
	int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
// Define the next dot's direction 
int getOrientation( int indexA, // P	// A
					int indexB,	// i	// B
					int indexC	// q	// C
				  )
{
	/*	A,B,C
		P, - текуща€ точка обЄртки
		i, - текуща€ точка из общего массива
		q  - следующа€ (за точкой из обЄртки) точка 

		( B[0] - A[0] ) * ( C[1] - B[1] ) - ( B[1] - A[1] ) * ( C[0] - B[0] )
		
		A[0] = pX[P]	A[1] = pY[P]
		B[0] = pX[i]	B[1] = pY[i] 
		C[0] = pX[q]	C[1] = pY[q] 
	
		( pX[i]-pX[P] ) * ( pY[q]-pY[i] ) - ( pY[i]-pY[P] ) * ( pX[q]-pX[i] )
	
	*/

		/*
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
	cout<<"P: pXY["<<indexA<<"] = "<<pX[indexA]<<","<<pY[indexA]
		<<"\ti: pXY["<<indexB<<"] = "<<pX[indexB]<<","<<pY[indexB]
		<<"\tq: pXY["<<indexC<<"] = "<<pX[indexC]<<","<<pY[indexC]
		<<endl
		<<"val = "<<val<<",";
	if(val>0) 
	{
		cout<<"\tskip ";
	}
	else
	{
		cout<<"\tapply ";
	}
	cout<<"dot ["<<indexB<<"]"
	//cout<<":: ("<<pX[indexB]<<"-"<<pX[indexA]<<") * ("<<pY[indexC]<<"-"<<pY[indexB]<<") - "
		//<<"("<<pY[indexB]<<"-"<<pY[indexA]<<") * ("<<pX[indexC]<<"-"<<pX[indexB]<<") = " <<val
		<<endl;

	return (val > 0)? 1: 2; // clock or counterclock wise
}
// Prints convex hull of a set of n points.
void convexHull2(Point points[], int n)
{

	// There must be at least 3 points
    if (n < 3) return;
 
    // initialize Result
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
	// bigBangialize Result
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
	{	//cout<<"pXY[i] :: pX[0]. pXY["<<i<<"] = "<<pX[i]<<","<<pY[i]<<" :: pX[0] = "<<pX[0]<<endl;
		if(pX[i]<pX[L]) 
		{	//cout<<endl<<"exchange "<<pX[0]<<" to "<<pX[i]<<", L = "<<i<<endl;
			L = i; 
		}
	}
	cout<<"\tstarting point is vertex["<<L<<"]:"<<pX[L]<<","<<pY[L]<<endl
		<<".............................................."<<endl;

	int orient;
	int q = 0; //=-1
	int P = L;
	// initialize Result
    //int *next = new int[starsCounter];
	//std::vector<int> dots;
	int cnt = 0;
	do
	{
		//cout<<"164. BEFORE - P = "<<P<<", q = "<<q<<endl;
		// q is following P vertex
		q = P+1;
		//
		//cout<<"167. AFTER - P = "<<P<<", q (P+1) = "<<q<<endl;
		//if(P!=q)
		//{
			for (int i = 0; i < starsCounter; i++)
			{
				orient=getOrientation(P,i,q);
				// if the next (q) dot is the right one, assign to it the current index
				if(orient==2)  
				{
					q=i;
					cout<<"\tP = "<<P<<", ADD DOT: pXY["<<q<<"] = "<<pX[q]<<","<<pY[q]<<endl;
					
				}/*
				else
				{
					
					cout<<"------------------------------"
						<<endl
						<<"["<<i<<"] NO CCWs"
						<<endl
						<<"P:: pXY["<<P<<"] = "<<pX[P]<<","<<pY[P]
						<<endl
						<<"i:: pXY["<<i<<"] = "<<pX[i]<<","<<pY[i]
						<<endl
						<<"q:: pXY["<<q<<"] = "<<pX[q]<<","<<pY[q]
						<<endl;
				}*/
			}
			//next[P]=q; //cout<<"next["<<P<<"] = "<<q<<endl;
			data.push_back(q);
			P = q;
			cnt++;
	
			if(cnt>300) 
			{
				cout<<endl<<"Too much!"<<endl;
				break;
			}
		//}
	}
	while(P!=L);
	for (size_t i=0; i<data.size(); i++)
	//for (int i = 0; i < starsCounter; i++)
    {	//if (next[i]&&next[i]!= -1)
		if(data[i])
			cout<<"Dot pXY["<<data[i]<<"] = "<<pX[data[i]]<<","<<pY[data[i]]<<endl;
        /*if (next[i] != -1)
			cout << " vertex next["<<i<< "] = "<<next[i]
			<<", pX["<<next[i]<<"] = "<<pX[next[i]]
			<<", pY["<<next[i]<<"] = "<<pY[next[i]];*/
    } 
	/*data.push_back(L);
	int counter = 20;
	while (counter)
	{
		int right = 0;
		int orient = 0;
		for(int i=0; i < starsCounter; i++)
		{
		  //if (rotate(A[H[-1]],A[P[right]],A[P[i]])<0):
			orient=getOrientation(i-1,i,i+1);
			if (orient== 2) right = i;
			//cout<<"orient: "<<orient<<", right = "<<right<<endl;
		}
		if(L==right) 
			break;
		else
		{
		  data.push_back(right);
		}  
		//H.append(P[right])
		  //del P[right]
		counter--;
	}*/
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
	bigBang();
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
void generateStars()
{	
	const int strz = 16;
	starsCounter=strz;

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
		for (int i = 0; i < starsCounter; i++)
		{
			//cout<<"pX = "<<pX[i]<<", pY = "<<pY[i]<<endl
			//	<<"; r: "<<r[i]<<", g: "<<g[i]<<", b: "<<b[i]<<endl;
			if(random)
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
				}/**/
			else
				glColor3f(r[i],g[i],b[i]);
			
			glVertex2f(pX[i],pY[i]);
		}
	glEnd();/**/
	
	if(random)
	{
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
				/*cout<<endl<<"index: "<<data[i]
					<<", pX: "<<pX[data[i]]
					<<", pY: "<<pY[data[i]];*/
				glVertex2f(pX[data[i]],pY[data[i]]);
			}/**/
		glEnd();
	}
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
	case 61: // вернутьс€ к первоначальным значени€м
		//eyeX=EX;
		//eyeY=EY;
		//eyeZ=EZ;
		//centerX=CX;
		//centerY=CY;
		//centerZ=CZ;
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