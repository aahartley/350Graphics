#include <iostream>
#include <GL/glut.h>

GLsizei ww = 512, wh = 512;
GLfloat z = 1;
GLfloat left = -0.8, right = 1.2, bottom = -0.8, top = 1.2;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 1, 3, 0, 0, 0, 0, 1, 0);

	glBegin(GL_QUADS);
	//--------- face 1-------------------------------
	glColor3f(0, 0, 0); glVertex3f(0, 0, 0);
	glColor3f(1, 0, 0); glVertex3f(1, 0, 0);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 1, 0);
	//-----------------------------------------------

	//--------- face 2-------------------------------
	glColor3f(1, 1, 0); glVertex3f(1, 1, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 1, 0);
	glColor3f(0, 1, z); glVertex3f(0, 1, z);
	glColor3f(1, 1, z); glVertex3f(1, 1, z);
	//-----------------------------------------------

	//--------- face 3-------------------------------
	glColor3f(1, 1, z); glVertex3f(1, 1, z);
	glColor3f(0, 1, z); glVertex3f(0, 1, z);
	glColor3f(0, 0, z); glVertex3f(0, 0, z);
	glColor3f(1, 0, z); glVertex3f(1, 0, z);
	//-----------------------------------------------

	//--------- face 4-------------------------------
	glColor3f(0, 0, z); glVertex3f(0, 0, z);
	glColor3f(1, 0, z); glVertex3f(1, 0, z);
	glColor3f(1, 0, 0); glVertex3f(1, 0, 0);
	glColor3f(0, 0, 0); glVertex3f(0, 0, 0);
	//-----------------------------------------------

	//--------- face 5-------------------------------
	glColor3f(1, 0, 0); glVertex3f(1, 0, 0);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 0);
	glColor3f(1, 1, z); glVertex3f(1, 1, z);
	glColor3f(1, 0, z); glVertex3f(1, 0, z);
	//-----------------------------------------------

	//--------- face 6-------------------------------
	glColor3f(0, 0, 0); glVertex3f(0, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 1, 0);
	glColor3f(0, 1, z); glVertex3f(0, 1, z);
	glColor3f(0, 0, z); glVertex3f(0, 0, z);
	//-----------------------------------------------

	glEnd();
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

void idle()
{
	z -= 0.0001;

	if (z <= 0)
		z = 0;

	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(NULL);

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		z = 1; 
		glutIdleFunc(idle);
	}

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(idle);
}

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("inside of the color cube");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}