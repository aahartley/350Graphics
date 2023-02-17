#include <stdlib.h>
//#include <iostream>
#include <GL/glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -1.0;
GLfloat right = 1.0;
GLfloat bottom = -1.0;
GLfloat top = 1.0;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);


void display() // display points and lines
{
	glClearColor(0.75, 0.75, 0.75, 1.0); // background color; values are in [0, 1]; default RGB are 0s
	glClear(GL_COLOR_BUFFER_BIT);

	//----points with single color----------
	//glColor3f(1, 0, 1); // default drawing color is white (1, 1, 1)
	//glPointSize(4); // default size is 1
	//glBegin(GL_POINTS);
	//glVertex2f(-0.5, -0.5);
	//glVertex2f(0.5, -0.5);
	//glVertex2f(0.5, 0.5);
	//glVertex2f(-0.5, 0.5);
	//glVertex2f(-0.7, 0.2);
	//glVertex2f(-0.6, -0.3);
	//glEnd();
	//---------------------------------------------------------

	////----points with multi colors------------
	//glPointSize(4);	// property before the primitive type
	//glBegin(GL_POINTS);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.5, -0.5);
	//
	//glColor3f(0, 1, 0);
	//glVertex2f(0.5, -0.5);
	//
	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.5);
	//
	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.5);
	//
	//glColor3f(1, 1, 0);
	//glVertex2f(-0.7, 0.2);
	//glVertex2f(-0.6, -0.3);
	//glEnd();
	////----------------------------------------------------

	////------line segments---------------------
	glLineWidth(2); //default value is 1; property before type
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, -0.5);

	glColor3f(0, 1, 0);
	glVertex2f(0.5, -0.5);

	glColor3f(0, 0, 1);
	glVertex2f(0.5, 0.5);

	glColor3f(1, 1, 1);
	glVertex2f(-0.5, 0.5);

	glColor3f(1, 1, 0);
	glVertex2f(-0.7, 0.2);
	glVertex2f(-0.6, -0.3);
	glEnd();
	////----------------------------------------------------

	////------line strip-----------------------
	//glBegin(GL_LINE_STRIP);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.5, -0.5);

	//glColor3f(0, 1, 0);
	//glVertex2f(0.5, -0.5);

	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.5);

	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.5);

	//glColor3f(1, 1, 0);
	//glVertex2f(-0.7, 0.2);
	//glVertex2f(-0.6, -0.3);
	//glEnd();
	////----------------------------------------------------

	////-----line loop----------------------------
	//glBegin(GL_LINE_LOOP);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.5, -0.5);

	//glColor3f(0, 1, 0);
	//glVertex2f(0.5, -0.5);

	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.5);

	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.5);

	//glColor3f(1, 1, 0);
	//glVertex2f(-0.7, 0.2);
    //glVertex2f(-0.6, -0.3);
	//glEnd();
	////----------------------------------------------------
	
	glFlush(); // force to render; works with GLUT_SINGLE_BUFFER
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

						//---the following segment could be included in the reshape callback-----
	float ratio = ww * 1.0 / (wh*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	// default (-1, 1, -1, 1)
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, ww, wh);
	//-------------------------------------
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w * 1.0 / (h*1.0);

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
	glutCreateWindow("Primitive Types");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	// envoked when the window is reshaped or moved; also envoked when the window is displayed at the first time

	glutMainLoop();

	return 0;
}