#include <iostream>
#include <GL/glut.h>

GLsizei ww = 512, wh = 512;
GLfloat z = 1;
GLfloat left = -2, right = 2, bottom = -2, top = 2;

GLfloat alpha = 0, beta = 0, gama = 0;

GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },
{ 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 }, { -1.0, -1.0, 1.0 },
{ 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };

void polygon(int a, int b, int c, int d)
{
	/* draw a polygon via list of vertices */
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);

	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);

	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);

	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube()
{
	/* map vertices to faces */
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}

void display()
{
	/* display callback, clear frame buffer and z buffer,
	rotate cube and draw, swap buffers */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glLoadIdentity();
	glRotatef(alpha, 1.0, 0.0, 0.0);
	glRotatef(beta, 0.0, 1.0, 0.0);
	glRotatef(gama, 0.0, 0.0, 1.0);

	colorcube();

	glFlush();
}


void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(left*w / h, right*w / h, bottom, top, -20, 20);
	else
		glOrtho(left, right, bottom * h / w, top * h / w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = w;
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		alpha += 5;

		if (alpha >= 360)
			alpha -= 360;
	}

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		beta += 5;

		if (beta >= 360)
			beta -= 360;
	}

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gama += 5;

		if (gama >= 360)
			gama -= 360;
	}

	glutPostRedisplay();
}

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("rotation");

	init();

	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}