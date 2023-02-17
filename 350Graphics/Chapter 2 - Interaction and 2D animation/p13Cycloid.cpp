#include <math.h>
#include "GL/glut.h"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -1;
GLfloat right = 7;
GLfloat bottom = -3;
GLfloat top = 5;
GLfloat alpha=0, beta=0, theta=0; 
GLfloat p_x;
const GLfloat DtoR = 0.017453;
const GLfloat Pi = 3.14159;
GLfloat a = 1;
GLfloat b = -1;
GLfloat c = 0;


//----- prototypes ----------
void init(void);
void reshape(GLsizei w, GLsizei h);
void idle(void);
void circle(float x0, float y0, float r);
void alongCycloid(void);


void circle(float x0, float y0, float r)
{
	float theta, dTheta = 1;
	int count;
	float x, y;

	count = (int)(360.0 / dTheta);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= count; i++)
	{
		theta = i * dTheta*DtoR;
		x = x0 + r * cos(theta);
		y = y0 + r * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void alongCycloid(void)
{
	GLfloat x, y, a = 1;
	GLfloat x0 = 0, y0 = 0;
	GLfloat t, dt = 5;
	int count; 

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	count = (int)(360.0 / dt);

	glColor3f(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= count; i++)
	{
		t = i*dt*DtoR;

		x = a*(t - sin(t));
		y = a*(1 - cos(t));
		glVertex2f(x, y);
	}
	glEnd();

	x0 = a*(beta - sin(beta));
	y0 = a*(1 - cos(beta));

	glColor3f(1, 0, 0);
	circle(x0, y0, 0.1);

	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	circle(beta, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_LINES);
	glVertex2f(beta, 1);
	glVertex2f(a*(beta - sin(beta)), a * (1 - cos(beta)));
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(left, 0);
	glVertex2f(right, 0);
	glEnd();

	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE
}


void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(0.8, 0.8, 0.8, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	// default (-1, 1, -1, 1)
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);
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

	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;	
	wh = h;
}

void idle()
{
	beta += 0.0001;
	if ( beta > 2*Pi)
		beta -= 2*Pi;

	glutPostRedisplay();
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("2D animation and interaction");
	init();

	left = -1; right = 7; bottom = -3; top = 5; glutDisplayFunc(alongCycloid);

	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();
}