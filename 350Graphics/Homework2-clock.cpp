//Austin Hartley
#include <stdlib.h>
#include <GL\glut.h>
#include <iostream>
//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -10.0;
GLfloat right = 10.0;
GLfloat bottom = -10.0;
GLfloat top = 10.0;

//cat
GLubyte mask[] = {
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x0C, 0xC0, 0xCC, 0x00,
	0x0B, 0x3F, 0x34, 0x00,
	0x10, 0x00, 0x02, 0x00,
	0x20, 0x00, 0x01, 0x00,
	0x40, 0x00, 0x00, 0x80,
	0x40, 0x00, 0x00, 0x80,
	0x40, 0x00, 0x00, 0x80,
	0x40, 0x00, 0x00, 0x80,
	0x40, 0x00, 0x00, 0x40,
	0x40, 0x00, 0x00, 0x40,
	0x42, 0x80, 0x03, 0xA0,
	0x49, 0x20, 0x04, 0xA0,
	0x40, 0x00, 0x78, 0xA0,
	0x20, 0x00, 0x81, 0x20,
	0x20, 0x00, 0x81, 0x20,
	0x13, 0xF3, 0x00, 0xC0,
	0x14, 0x0A, 0x00, 0x00,
	0x08, 0x04, 0x00, 0x00
};

const float	DtoR = 0.017453f;
const float PI = 3.14159f;

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
		x = x0 + a * std::cos(theta);
		y = y0 + b * std::sin(theta);
		//std::cout << x << ' ' << y << '\n';
		glVertex2f(x, y);
	}
	glEnd();
}
void axes(void) {
	glBegin(GL_LINES);
	glVertex2f(left, 0);
	glVertex2f(right, 0);

	glVertex2f(0, bottom);
	glVertex2f(0, top);
	glEnd();
}

void drawClock() {
	//x=rcostheta, y=rsintheta
	float theta;
	float r = 8.0f;
	float x, y;
	//clock
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10) {
		theta = i * DtoR;
		x = r * std::cos(theta);
		y = r * std::sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
	//ticks
	glColor3f(0, 0.5, 0.5);
	glBegin(GL_LINES);
	for (int i = 0; i < 360; i += 30) {
		theta = i * DtoR;
		x = r * std::cos(theta);
		y = r * std::sin(theta);
		glVertex2f(x, y);
		x = 0.9 * r * std::cos(theta);
		y = 0.9 * r * std::sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
	//hands  3:45:00
	float mR = 5.5f;
	float sR = 6.0f;
	float hR = 4.0f;
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(mR * std::cos(180 * DtoR), mR * std::sin(180 * DtoR));

	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(sR * std::cos(90 * DtoR), sR * std::sin(90 * DtoR));

	//-22.5 degree     30*3/4
	glColor3f(0, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(hR * std::cos(-22.5 * DtoR), hR * std::sin(-22.5 * DtoR));
	glEnd();

}
void drawPolarCurve() {
	// r = 4(1-cos(theta)sin(4theta)), 0 <= theta <= 2PI
	glColor3f(0, 0, 1);
	glLineWidth(2);
	float r, theta;
	float alpha = 0;
	float beta = 2 * PI;
	float x, y;
	float dTheta = 0.01;
	glBegin(GL_LINE_STRIP);
	theta = alpha;
	while (theta <= beta)
	{
		r = 4 * (1 - std::cos(theta) * sin(4 * theta));

		x = r * cos(theta);
		y = r * sin(theta);
		glVertex2f(x, y);

		theta += dTheta;
	}
	glEnd();
}
void drawCurveRegion() {
	//y=sqrt(16-x^2 and y= 2sqrt(16-x^2)
	GLfloat x, y1, y2;
	GLfloat a = -4;
	GLfloat b = 4;
	GLfloat dx = 0.1;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0, 0, 0);
	glBegin(GL_QUAD_STRIP);
	x = a;
	while (x <= b)	// two vertices are created in each round
	{
		y1 = std::sqrtf(16 - std::pow(x, 2));
		//glColor3ub(255, 0, 0);	// unsigned byte: 0 - 255
		glVertex2f(x, y1);

		y2 = 2 * std::sqrtf(16 - std::pow(x, 2));
		//glColor3f(0, 1, 1);		// float: 0 - 1
		glVertex2f(x, y2);

		x += dx;
	}
	glEnd();


	glLineWidth(5);
	glColor3f(1, 0, 1);
	glBegin(GL_LINE_STRIP);
	x = a;
	while (x <= b)	// two vertices are created in each round
	{
		y1 = std::sqrtf(16 - std::pow(x, 2));
		//glColor3ub(255, 0, 0);	// unsigned byte: 0 - 255
		//glVertex2f(x, y1);

		y2 = 2 * std::sqrtf(16 - std::pow(x, 2));
		//glColor3f(0, 1, 1);		// float: 0 - 1
		glVertex2f(x, y2);

		x += 0.1;
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	x = a;
	while (x <= b)	// two vertices are created in each round
	{
		y1 = std::sqrtf(16 - std::pow(x, 2));
		//glColor3ub(255, 0, 0);	// unsigned byte: 0 - 255
		glVertex2f(x, y1);

		y2 = 2 * std::sqrtf(16 - std::pow(x, 2));
		//glColor3f(0, 1, 1);		// float: 0 - 1
		//glVertex2f(x, y2);

		x += 0.1;
	}
	x = a;
	glEnd();



}
void stippledTriangle(void)
{
	//---------- draw the background triangle -----------
	glColor3ub(255, 192, 203);
	glBegin(GL_POLYGON);
	glVertex2f(-8, -6);
	glVertex2f(8, -6);
	glVertex2f(0, 8);
	glEnd();

	//---------- draw the stippled triangle ---------------
	glEnable(GL_POLYGON_STIPPLE);
	glColor3f(1, 0, 0);
	glPolygonStipple(mask);

	glBegin(GL_POLYGON);
	glVertex2f(-8, -6);
	glVertex2f(8, -6);
	glVertex2f(0, 8);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	//lower left corner
	glViewport(0, 0, ww / 2, wh / 2);
	stippledTriangle();

	//lower right corner
	glViewport(ww / 2, 0, ww / 2, wh / 2);
	drawPolarCurve();
	glColor3f(1, 1, 1);
	glLineWidth(1);
	axes();

	//top left corner
	glViewport(0, wh / 2, ww / 2, wh / 2);
	drawClock();

	//top right corner
	glViewport(ww / 2, wh / 2, ww / 2, wh / 2);
	drawCurveRegion();
	glColor3f(1, 1, 1);
	glLineWidth(1);
	axes();



	glFlush();	// force to render, work with single buffer
}

void init(void)
{
	glClearColor(0.7, 0.7, 0.7, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	float ratio = ww * 1.0 / (wh * 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left * ratio, right * ratio, bottom, top);	// default (-1, 1, -1, 1)
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
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
	glutCreateWindow("Homework1- Austin Hartley");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}