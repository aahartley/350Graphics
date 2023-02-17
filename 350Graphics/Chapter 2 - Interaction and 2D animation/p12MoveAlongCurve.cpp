#include <math.h>
#include "GL/glut.h"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -2;
GLfloat right = 2;
GLfloat bottom = -2;
GLfloat top = 2;
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
void parabola(float a, float b, float c, float x1, float x2);
void alongParabola(void);
void alongCircle(void);
void alongBowditchCurve(void);
void circle(float x0, float y0, float r);


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

void alongCircle(void)
{
	GLfloat x1, y1, x2, y2;
	GLfloat R1 = 1, R2 = 1.5; 

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glColor3f(0.5, 0.5, 0.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	circle(0, 0, R1);
	circle(0, 0, R2);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	x1 = R1*cos(theta);
	y1 = R1*sin(theta);
	glColor3f(1, 0, 0);
	circle(x1, y1, 0.05);

	x2 = R2*cos(alpha);
	y2 = R2*sin(alpha);
	glColor3f(0, 1, 0);
	circle(x2, y2, 0.05);

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void parabola(float a, float b, float c, float x1, float x2)
{
	float x, y;
	float dx = 0.01;

	//glClear(GL_COLOR_BUFFER_BIT);

	x = x1;
	glBegin(GL_LINE_STRIP);
	while (x <= x2)
	{
		y = a * x*x + b * x + c;

		glVertex2f(x, y);

		x += dx;
	}
	glEnd();
}

void alongParabola(void)
{
	GLfloat x, y, dx = 0.01;
	float p_y;
	int count;

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glColor3f(0, 0, 1);
	parabola(a, b, c, -1, 1);

	glColor3f(1, 0, 0);
	p_y = a * p_x*p_x + b*p_x + c;
	circle(p_x, p_y, 0.05);
	
	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void alongBowditchCurve(void)
{
	GLfloat x, y;
	GLfloat a = 3, b = 2;
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

		x = sin(a*t);
		y = sin(b*t);
		glVertex2f(x, y);
	}
	glEnd();

	x0 = sin(a*beta);
	y0 = sin(b*beta);

	glColor3f(1, 0, 0);
	circle(x0, y0, 0.1);

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
	theta += 0.0001;
	if (theta > 2*Pi)
		theta -= 2*Pi;

	alpha -= 0.0002;
	if (alpha < -1*Pi)
		alpha += 2*Pi;

	beta += 0.0001;
	if ( beta > 2*Pi)
		beta -= 2*Pi;

	p_x += 0.0001;
	if (p_x > 1)
		p_x = -1;

	glutPostRedisplay();
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("2D animation and interaction");
	init();

	glutDisplayFunc(alongParabola);
	//glutDisplayFunc(alongCircle);
	//glutDisplayFunc(alongBowditchCurve);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();
}