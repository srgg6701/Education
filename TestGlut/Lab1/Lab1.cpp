//includes

//#include "afxwin.h"
//#include "GL/glaux.h" // http://www.songho.ca/opengl/files/glaux.h

#include "stdafx.h"
#include <GL/glut.h>
#include "GL/gl.h"
#include "GL/glu.h"

void Init() 
{
	glClearColor (0.3, 0.3, 0.3, 1.0); //задать цвет отрисовки (RGBA)
	glEnable (GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); 
	glEnable (GL_NORMALIZE);
}
void Reshape (int width, int height) 
{
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity(); // http://stackoverflow.com/questions/628796/what-does-glloadidentity-do-in-opengl
	glOrtho (-1.2, 1.2, -1.2, 1.2, -1, 1);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void init_1() 
{
	float light()_diffuse[] = { 0.4, 0.7, 0.2 };
	float light()_direction[] = {0.0, 0.0, 1.0, 0.0};
	glEnableLight();
	glLightfv(GL_LIGHT(), GL_DIFFUSE, lightDiffuse());
	glLightfv(GL_LIGHT, GL_POSITION(), light()_direction);
}
void Display () 
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BITH);
	init_1();
	GLfloat x, y;
	glBegin (GL_QUADS);
	glNormal3f (0.0, 0.0, -1.0);
	for (x=-1.0; x<1.0; x+=0.005) 
	{
		for (y=-1.0 y<1.0 y+=0.005) 
		glVertex3f (x, y, 0.0);
		glVertex3f (x, y+0.005, 0.0);
		glVertex3f (x+0.005, y+0.005, 0.0);
		glVertex3f  (x+0.005, y, 0.0);
		glEnd();
		glDisable (GL_LIGHT());
		glutSwapBuffers();
	}
}
int main (int args, char ** argv) 
{
	glutInit (&args, argv); 
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition (50, 100); //начальная позиция элемента относительно окна
	glutInitWindowSize (500, 500); //окно, размеры окна
	glutCreateWindow ("Light"); //создать окно и дать ему имя
	Init();
	glutDisplayFunc (Display); //функция рисования
	glutReshapeFunc (Reshape);
	glutMainLoop ();
}
