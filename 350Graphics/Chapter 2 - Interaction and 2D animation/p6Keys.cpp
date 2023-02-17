#include <iostream>
#include <GL/glut.h>

void keys(unsigned char k, int x, int y)
{
	if ( (glutGetModifiers()==GLUT_ACTIVE_SHIFT) )
		printf( "shift '%c' is pressed, while the mouse is at (%d, %d)\n", k, x, y);
	else
		printf( "Key '%c' is pressed, while the mouse is at (%d, %d)\n", k, x, y);
}

void specialKeys(int k, int x, int y)
{
	printf( "Special key '%d' is pressed, while the mouse is at (%d, %d)\n", k, x, y);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow( "temp" );

	glutKeyboardFunc( keys );
	glutSpecialFunc( specialKeys );
	glutDisplayFunc( display );
	glutMainLoop();
}