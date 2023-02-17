#include <stdlib.h>
#include <GL\glut.h>
#include <iostream>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -2.0;
GLfloat right = 2.0;
GLfloat bottom = -2.0;
GLfloat top = 2.0;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glRectf(-0.5, -0.5, 0.5, 0.5);

	glFlush();	// force to render, work with single buffer
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, ww, wh);
	//-------------------------------------
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w*1.0 / (h*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	//------ reset the window size
	ww = w;	
	wh = h;
}

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 50); // defualt at (0, 0)
	glutCreateWindow("2D Program");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	// envoked when the window is reshaped or moved;displayed at the first time

	glutMainLoop();

	return 0;
}