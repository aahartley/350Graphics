#include <stdlib.h>
#include <GL\glut.h>
#include <math.h>
#include <iostream>
//------ global variables and constants------------
GLsizei ww = 500;
GLsizei wh = 500;
GLfloat left = -2;
GLfloat right = 2;
GLfloat bottom = -2;
GLfloat top = 2;
const float	DtoR = 0.017453;

//----- prototypes ----------
void display1(void);
void display2(void);
void init(void);
void reshape(GLsizei w, GLsizei h);


void display1(void)
{
	GLfloat theta;
	GLfloat dTheta = 22.5;
	GLfloat r = 0.5;
	GLfloat dr = 0.5;
	GLfloat x, y;
	
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= 4; i++)	// two vertices are created in each round
	{
		theta = dTheta * i *DtoR;
		std::cout << "theta " << theta/DtoR << '\n';
		x = r*cos(theta);
		y = r*sin(theta);
		std::cout << x << ' ' << y << '\n';
		glColor3f(i, i, i);
		glVertex2f(x, y);

		x = (r+dr)*cos(theta);
		y = (r+dr)*sin(theta);
		glColor3f(i, i, i);
		std::cout << x << ' ' << y << '\n';

		glVertex2f(x, y);
	}
	glEnd();

	glFlush();	// force to render, work with single buffer
}

void display2(void)
{
	GLfloat theta;
	GLfloat dTheta = 3;
	GLfloat r = 0.5;
	GLfloat R = 1.0;
	GLfloat x1, y1, x2, y2;

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	theta = 0.0;
	while ( theta <= 360)	// two vertices are created in each round
	{
		x1 = r * cos(theta*DtoR);
		y1 = r * sin(theta*DtoR);

		glVertex2f(x1, y1);

		x2 = R*cos(theta*DtoR);
		y2 = R*sin(theta*DtoR);

		glVertex2f(x2, y2);

		theta += dTheta;
	}
	glEnd();

	glFlush();	// force to render, work with single buffer
}

void display3(void)
{
	GLfloat x, y1, y2;
	GLfloat a = -1;
	GLfloat b = 1;
	GLfloat k = 4;
	GLfloat dx = 0.1;

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	x = a;
	while ( x <= b)	// two vertices are created in each round
	{
		y1 = sin(k*x);
		glColor3ub(255, 0, 0);	// unsigned byte: 0 - 255
		glVertex2f(x, y1);

		y2 = cos(k*x);
		glColor3f(0, 1, 1);		// float: 0 - 1
		glVertex2f(x, y2);

		x += dx;
	}
	glEnd();

	glFlush();	// force to render, work with single buffer
}


void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
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

	glViewport(0, 0, w, h);

	//------ reset the window size
	ww = w;	
	wh = h;
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(800, 200); // defualt at (0, 0)
	glutCreateWindow("connected quadrics");
	init();

	glutDisplayFunc(display3);
	glutReshapeFunc(reshape);

	glutMainLoop();
}