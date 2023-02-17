#include <GL/glut.h>

GLsizei ww = 500;
GLsizei hh = 500;

int xx = 0, yy = 0;
int count = 0;



void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

void passiveMotion( int x, int y)
{
	glBegin(GL_POINTS);
			glVertex2f(x, hh-y);
	glEnd();

	glFlush();
}

void init()
{
	glClearColor(0.3, 0.3, 0.3, 1);

	glColor3f(0.2, 0.8, 0.8);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, ww, 0, hh, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, hh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow( "mouse motion" );

	init();
	glutPassiveMotionFunc( passiveMotion );
	glutDisplayFunc( display );
	glutMainLoop();
}