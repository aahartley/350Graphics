#include <stdlib.h>
#include <GL\glut.h>
#include <iostream>
//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -4.0;
GLfloat right = 4.0;
GLfloat bottom = -4.0;
GLfloat top = 4.0;

const float	DtoR = 0.017453f;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);

void drawSolidOval(float x0, float y0, float a, float b) {
	// x^2/a^2 + y^2/b^2 =1              
	//x= a cos theta      0<= theta <=2pi
	//y= bsin theta
	// x = x0 + a costheta
	//y= y0 + bsintheta
	float x, y;
	float theta;
	glBegin(GL_POLYGON);
	for (int t = 0; t <= 360; t += 10) {
		theta = t * DtoR;
		x = x0 + a * std::cos(theta);
		y = y0 + b * std::sin(theta);
		//std::cout << x << ' ' << y << '\n';
		glVertex2f(x, y);
	}
	glEnd();
}
void drawOval(float x0, float y0, float a, float b) {
	// x^2/a^2 + y^2/b^2 =1              
	//x= a cos theta      0<= theta <=2pi
	//y= bsin theta
	// x = x0 + a costheta
	//y= y0 + bsintheta
	float x, y;
	float theta;
	glBegin(GL_LINE_LOOP); //gl_line_strip
	for (int t = 0; t <= 360; t += 10) {
		theta = t * DtoR;
		x = x0+a*std::cos(theta);
		y = y0+b*std::sin(theta);
		//std::cout << x << ' ' << y << '\n';
		glVertex2f(x, y);
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	//---------- graphics objects -------------
	glLineWidth(4);
	glColor3f(1, 0, 1);
	drawSolidOval(1, -1, 2, 1);

	glColor3f(1, 1, 0);
	drawOval(1,-1,2,1);

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
	float ratio = w * 1.0 / (h * 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left * ratio, right * ratio, bottom, top);
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
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}