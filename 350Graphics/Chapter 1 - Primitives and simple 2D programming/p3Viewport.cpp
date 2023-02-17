#include <GL\glut.h>

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
	////-------viewport in a specified retangular region
	//glViewport(0, 0, 150, 150);
	//glPointSize(4);
	//glBegin(GL_POINTS);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.8, 0.0);

	//glColor3f(0, 1, 0);
	//glVertex2f(-0.2, -0.6);

	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.0);

	//glColor3f(0, 1, 1);
	//glVertex2f(0.7, 0.7);

	//glColor3f(1, 0, 1);
	//glVertex2f(0.0, 0.8);

	//glColor3f(1, 1, 0);
	//glVertex2f(-0.6, 0.5);
	//glEnd();
	////---------------------------------------

	//------ display on the lower left quarter --------
	glViewport(0, 0, ww/2, wh/2);	//(x, y, width, height)
	glPointSize(4);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2f(-0.8, 0.0);

	glColor3f(0, 1, 0);
	glVertex2f(-0.2, -0.6);

	glColor3f(0, 0, 1);
	glVertex2f(0.5, 0.0);

	glColor3f(0, 1, 1);
	glVertex2f(0.7, 0.7);

	glColor3f(1, 0, 1);
	glVertex2f(0.0, 0.8);

	glColor3f(1, 1, 0);
	glVertex2f(-0.6, 0.5);
	glEnd(); 
	//---------------------------------------

	//------- display on lower right quarter -------------
	glViewport(ww/2, 0, ww/2, wh/2);
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.8, 0.0);

	glColor3f(0, 1, 0);
	glVertex2f(-0.2, -0.6);

	glColor3f(0, 0, 1);
	glVertex2f(0.5, 0.0);

	glColor3f(0, 1, 1);
	glVertex2f(0.7, 0.7);

	glColor3f(1, 0, 1);
	glVertex2f(0.0, 0.8);

	glColor3f(1, 1, 0);
	glVertex2f(-0.6, 0.5);
	glEnd();
	//-----------------------------------------------------

	//------- display on upper left quarter -------------
	glViewport(0, wh/2, ww/2, wh/2);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.8, 0.0);

	glColor3f(0, 1, 0);
	glVertex2f(-0.2, -0.6);

	glColor3f(0, 0, 1);
	glVertex2f(0.5, 0.0);

	glColor3f(0, 1, 1);
	glVertex2f(0.7, 0.7);

	glColor3f(1, 0, 1);
	glVertex2f(0.0, 0.8);

	glColor3f(1, 1, 0);
	glVertex2f(-0.6, 0.5);
	glEnd();
	//-----------------------------------------------------

	//------- display on upper right quarter -------------
	glViewport(ww/2, wh/2, ww/2, wh/2);
	glLineWidth(2);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.8, 0.0);

	glColor3f(0, 1, 0);
	glVertex2f(-0.2, -0.6);

	glColor3f(0, 0, 1);
	glVertex2f(0.5, 0.0);

	glColor3f(0, 1, 1);
	glVertex2f(0.7, 0.7);

	glColor3f(1, 0, 1);
	glVertex2f(0.0, 0.8);

	glColor3f(1, 1, 0);
	glVertex2f(-0.6, 0.5);
	glEnd();
	//-----------------------------------------------------

	glFlush();
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glColor3f(0, 1, 1);

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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(800, 200); // defualt at (0, 0)
	glutCreateWindow("viewport");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	// envoked when the window is reshaped or moved; also envoked when the window is displayed at the first time

	glutMainLoop();

	return 0;
}