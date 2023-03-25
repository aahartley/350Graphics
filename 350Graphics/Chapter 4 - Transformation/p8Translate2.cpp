//#include <GL/glut.h>
//#include <math.h>
#include "../myObjects2023.cpp"

GLsizei ww = 512, wh = 512;
GLfloat step = 0.1;
GLfloat halfWidth = 5;
GLfloat halfHeight = 5;


void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

void display1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);

	glColor3f(1, 0, 0);		// red cube
	glutWireCube(1);

	glTranslatef(2, 0, 0);	// only affects the blue cube
	glColor3f(0, 0, 1);		// blue cube
	glutWireCube(1);
	glutSwapBuffers();
}

void display2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);

	glTranslatef(1, 0, 0);	// affects both the red cube and the blue cube
	glColor3f(1, 0, 0);		// red cube
	glutWireCube(1);

	glTranslatef(2, 0, 0);	// affects the blue cube
	glColor3f(0, 0, 1);		// blue cube
	glutWireCube(1);
	glutSwapBuffers();
}

void display3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);

	glTranslatef(1, 0, 0);	// affects the subsequent objects
	glColor3f(1, 0, 0);		// red cube
	glutWireCube(1);

	glLoadIdentity();		// disables the above transformations and also disables gluLookAt
	glTranslatef(2, 0, 0);	// affects the blue cube
	glColor3f(0, 0, 1);		// blue cube
	glutWireCube(1);

	glutSwapBuffers();
}


void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-halfWidth*w/h, halfWidth*w/h, -halfHeight, halfHeight, -20, 20);
	else
		glOrtho(-halfWidth, halfWidth, -halfHeight*h/w, halfHeight*h/w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutDisplayFunc(display1); //display1();

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		glutDisplayFunc(display2); //display2();

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		glutDisplayFunc(display3); //display3();

	glutPostRedisplay();
}


void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("translate cube");

	glutDisplayFunc(display1);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	init();
	glutMainLoop();
}

