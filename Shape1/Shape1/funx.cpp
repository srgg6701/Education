#include "funx.h"
#include "vars.h"
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.8,0.8,0.8);
	glBegin(GL_LINES);
		// set vertical lines
		for (float i = -ww2; i <= ww2; i+=20.0)
		{
			glVertex2f(i,-wh2);
			glVertex2f(i, wh2);
		}
		// set horizontal lines
		for (float i = -wh2; i <= wh2; i+=20.0)
		{
			glVertex2f(-ww2,i);
			glVertex2f( ww2,i);
		}
	glEnd();
	glFlush();
}