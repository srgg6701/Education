#include "stdafx.h"
#include "windows.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;
const float Deg		= 0.0;
static double deg	= Deg;
void drawCyl()
{
   GLUquadricObj* cyl;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(35.0, 1.0, 1.0, 100.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (30.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
   glColor3f(1.0f, 1.0f, 0.5f); //Defining color
   glRotatef(deg, 1.0, 0.0, 0.0); // Rotate by deg
   cyl = gluNewQuadric();
   gluQuadricDrawStyle(cyl, GLU_LINE);
   gluCylinder(cyl, 1.0, 1.0, 5, 35, 15);
   glFlush();
}
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   drawCyl();
   glFlush ();
}
void init (void) 
{
   glClearColor (0.5, 0.5, 0.5, 0.0);
   glEnable(GL_DEPTH_TEST); //enabling z-buffer
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(35.0, 1.0, 1.0, 100.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (30.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 65:	// A 
            deg -= 25.0;
            break;
        case 97:	// a 
            deg += 25.0;    
            break;
		case 61:
			deg = Deg;
			break;
    }
	if(key!=27) 
		glutPostRedisplay();
	else // “esc” on keyboard
		exit(0);
}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Rotation...");
   init ();
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
