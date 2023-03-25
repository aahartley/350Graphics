#include <math.h>
#include <GL/glut.h>

GLsizei ww = 512, wh = 512;
GLfloat halfWidth = 4;
GLfloat halfHeight = 4;

float angle = 0;

void display1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//	gluLookAt(2, 1, 10, 0, 0, 0, 0, 1, 0);

	//-------- rotate before translate
	glTranslatef(2, 0, 0);
	glRotatef(angle, 0, 0, 1);
	
	glColor3f(0, 1, 1);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glutWireCube(1.01);

	glutSwapBuffers();
}

void display2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//	gluLookAt(2, 1, 10, 0, 0, 0, 0, 1, 0);

	glColor3f(0, 1, 1);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glutWireCube(1.01);

	glutSwapBuffers();
}

void display3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//	gluLookAt(2, 1, 10, 0, 0, 0, 0, 1, 0);

	//---------- translate before rotate
	glRotatef(angle, 0, 0, 1);
	glTranslatef(2, 0, 0);

	glColor3f(0, 1, 1);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glutWireCube(1.01);

	glutSwapBuffers();
}



void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutDisplayFunc(display1);

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		glutDisplayFunc(display2);

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		angle = 0;
		glutDisplayFunc(display3);
	}

	glutPostRedisplay();
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


void idle()
{
	angle += 0.005;
	if(angle > 360) angle -= 360;

	glutPostRedisplay();
}



void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("rotations");

	glutDisplayFunc(display1);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
}

