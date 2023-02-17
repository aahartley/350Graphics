#include <iostream>
#include <GL/glut.h>

GLsizei ww = 512;
GLsizei hh = 512;

//int points[100][2];
//int count = 0;



void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

void mouse( int button, int state, int x, int y)
{
	if ( (state == GLUT_DOWN) && (button == GLUT_LEFT_BUTTON) )
		printf("The left button is clicked at (x = %i, y = %i)\n", x, y);
	else if ( (state == GLUT_DOWN) && (button == GLUT_MIDDLE_BUTTON) )
		printf("The middle button is clicked at (x = %i, y = %i)\n", x, y);
	else if ( (state == GLUT_DOWN) && (button == GLUT_RIGHT_BUTTON) )
		printf("The right button is clicked at (x = %i, y= %i)\n", x, y);
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
	glutInitWindowPosition(800, 200);
	glutCreateWindow( "mouse motion" );

	init();
	glutMouseFunc( mouse );
	glutDisplayFunc( display );
	glutMainLoop();
}