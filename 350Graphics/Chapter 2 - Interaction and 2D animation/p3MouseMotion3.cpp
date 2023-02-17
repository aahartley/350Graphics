
#include <iostream>
#include <GL/glut.h>
GLsizei ww = 500;
GLsizei hh = 500;

int points[100][2];
int count = 0;



void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

void entry( int state )
{
	if (state == GLUT_ENTERED)
		printf("The mouse entered.\n");

	if (state == GLUT_LEFT)
		printf("The mouse left.\n");
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
	glutEntryFunc( entry );
	glutDisplayFunc( display );
	glutMainLoop();
}