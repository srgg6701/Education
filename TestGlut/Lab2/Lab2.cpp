#include "stdafx.h"
#include <GL/glut.h>
//Reshape
void Reshape (int width, int height) 
{
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (-1, 1, -1, 1);
	glMatrixMode (GL_MODELVIEW);
}
void Draw (void) 
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0f, 0.0f, 1.0f);
	glLineWidth (1);
	glBegin (GL_LINES);
	glVertex2f (0, 0.5f);
	glVertex2f (0, -0.5f) ;
	glEnd ();
	glFlush();
}
int main (int argc, char** argv) 
{
	glutInit (&argc, argv);
	glutInitWindowSize (400, 300) ;
	glutInitWindowPosition (100, 100) ;
	glutInitDisplayMode (GLUT_RGB); 
	glutCreateWindow("Romka Demo");
	glutReshapeFunc (Reshape);
	glutDisplayFunc (Draw);
	glClearColor (0, 0, 0, 0); //задать цвет подложки окна (RGBA)
	glutMainLoop();
	return 0;
}
