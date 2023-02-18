//Austin Hartley
#include <stdlib.h>
#include "GL/glut.h"
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
float secondTheta = 90.0f;
float minuteTheta = 180.0f;
float hourTheta = 337.5f;
bool pause = false;
//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void timer(int v);




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
	//---------- draw the stippled clock ---------------
	glEnable(GL_POLYGON_STIPPLE);
	glColor3f(1, 0, 0);
	glPolygonStipple(mask);

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10) {
		theta = i * DtoR;
		x = r * std::cos(theta);
		y = r * std::sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	glLineWidth(10);
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
	glVertex2f(mR * std::cos(minuteTheta * DtoR), mR * std::sin(minuteTheta * DtoR));

	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(sR * std::cos(secondTheta * DtoR), sR * std::sin(secondTheta * DtoR));

	//-22.5 degree     30*3/4
	glColor3f(0, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(hR * std::cos(hourTheta * DtoR), hR * std::sin(hourTheta * DtoR));
	glEnd();

}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background


	glViewport(0, 0, ww, wh);
	drawClock();





	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE
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
void timer(int v)
{
		if (secondTheta < 0.0)
			secondTheta += 360.0;
		secondTheta -= 6;

		if (minuteTheta < 0.0)
			minuteTheta += 360.0;
		minuteTheta -= (float)((1.0f / 60.0f) * 6.0f);

		if (hourTheta < 0.0)
			hourTheta += 360.0;
		hourTheta -= (float)((1.0f / 720.0f) * 6.0f);


		glutTimerFunc(100, timer, v);
	
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 50); // defualt at (0, 0)
	glutCreateWindow("Homework2-Clock Austin Hartley");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(10, timer, 1);

	glutMainLoop();

	return 0;
}