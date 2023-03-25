//#include <math.h>
//#include <GL/glut.h>
#include "../myObjects2023.cpp"

GLsizei ww = 512, wh = 512;
GLfloat shift[3] = {0, 0, 0};
GLfloat step = 0.1;
GLfloat increment = step;
GLfloat halfWidth = 4;
GLfloat halfHeight = 4;


void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);

	axes(6);

	glTranslatef(shift[0], shift[1], shift[2]);
	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glColor3f(1, 0, 0);
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
		shift[0] += increment;

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		shift[1] += increment;

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		shift[2] += increment;

	display();
}

void keyboard(unsigned char k, int x, int y)
{
	if ( k == 'p' || k == 'P' )
		increment = 1.0 * step;
	else if ( k == 'n' || k == 'N' )
		increment = -1.0 * step;
}


int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("translate cube");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);

	init();
	glutMainLoop();
	return 0;
}

