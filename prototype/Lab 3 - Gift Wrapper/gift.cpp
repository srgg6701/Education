// A C++ program to find convex hull of a set of points
// http://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
// Refer http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
// for explanation of orientation()
#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
#include "funx.h"
using namespace std;

// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

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
 
// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{

	// There must be at least 3 points
    if (n < 3) return;
 
    // Initialize Result
    int *next = new int[n];
    for (int i = 0; i < n; i++)
        next[i] = -1;
 
    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
 
    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again
    int p = l, q;
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
    } while (p != l);
 
    // Print Result
    for (int i = 0; i < n; i++)
    {
        if (next[i] != -1)
           cout << "(" << points[i].x << ", " << points[i].y << ")\n";
    } 
}
 
// Driver program to test above functions
int main(int argvc, char**argv)
{
    /*Point points[] = {
						{0, 3}, {2, 2}, {1, 1}, {2, 1},
						{3, 0}, {0, 0}, {3, 3}
					};
    int n = sizeof(points)/sizeof(points[0]);*/
    
	//convexHull(points, n);
	glutInit(&argvc, argv);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(800,400);
	glutCreateWindow("Dots");
	glutDisplayFunc(Display);
	//init();
	glutMainLoop();
    return 0;
}
void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.1,0.0,0.3,1.0);
	glOrtho(-4.0,4.0,-4.0,4.0,-10.0,10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}
// show gets here!
void Display()
{
	//glClearColor(1.0,1.0,4.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.0,1.0,0.0);	
	//cout<<"Look at it, Dude: "<<endl;
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(-4.0,4.0,-4.0,4.0,-10.0,10.0); // left right bottom top
	//glMatrixMode(GL_MODELVIEW);
	//�������� �������
	//glLoadIdentity();
	//������� �������������(������)
	//gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
	glFlush;
}

// ���������:
// http://habrahabr.ru/post/144921/ -> http://habrahabr.ru/post/144571/
// http://marknelson.us/2007/08/22/convex/