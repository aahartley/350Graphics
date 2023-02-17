#include <iostream>		// for printf
#include <GL/glut.h>  // gl.h and glu.h are included in glut.h

// global variables
GLsizei ww = 512;
GLsizei hh = 512;
GLfloat left = -2.0;
GLfloat right = 2.0;
GLfloat bottom = -2.0;
GLfloat top = 2.0;


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//--------------------------- bitmap characters --------------------------
	glColor3f(1, 0, 0);		// color must be before raster position
	glRasterPos2f(-0.5,1.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'A');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'D');

	glRasterPos2f(-0.5,1.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'F');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');

	glRasterPos2f(-0.5,0.5);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'I');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'J');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'K');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'L');

	glRasterPos2f(-0.5,0.0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'M');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'O');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
	
	glRasterPos2f(-0.5,-0.5);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'Q');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'R');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'S');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'T');

	glRasterPos2f(-0.5,-1.0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'U');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'V');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'W');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');
		
	glRasterPos2f(-0.5,-1.5);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'B');
	//------------------------------------------------------------------------

	//------------------- display a string of characters ---------------------
	glColor3f(0, 1, 0);	// color should be specified before the raster position
	glRasterPos2f(0, 0);

	char str[] = "Hello world!";
	for ( char *c=str; *c!='\0'; c++ )
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	//------------------------------------------------------------------------

	glFlush();
}


void reshape(GLsizei w, GLsizei h)
{
	GLfloat ratio = (float)h/(float)w;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if( ratio <= 1.0)
		gluOrtho2D(left/ratio, right/ratio, bottom,top);
	else
		gluOrtho2D(left, right, bottom*ratio, top*ratio);

	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);
	// Reset the window size
	ww = w;
	hh = h;
}


void init()
{
	// Set the clear color. The color must be in RGBA type (A for opacity).
	// The clear color is used to clear the screan. The default clear color is black.
	glClearColor(0.4, 0.4, 0.4, 1.0);

	// Set the fill color.
	glColor3f(0, 0, 0);

	// Set the view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);
}



void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, hh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("text");
	init();

	printf("The width of 'M' in GLUT_BITMAP_TIMES_ROMAN_10 is %d \n", glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_10, 'M'));
	printf("The width of 'M' in GLUT_BITMAP_TIMES_ROMAN_24 is %d \n", glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, 'M'));

	printf("\nThe width of 'M' in GLUT_BITMAP_8_BY_13 is %d \n", glutBitmapWidth(GLUT_BITMAP_8_BY_13, 'M'));
	printf("The width of 'M' in GLUT_BITMAP_9_BY_15 is %d \n", glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'M'));

	printf("\n\nThe width of 'M' in GLUT_BITMAP_HELVETICA_10 is %d \n", glutBitmapWidth(GLUT_BITMAP_HELVETICA_10, 'M'));
	printf("The width of 'M' in GLUT_BITMAP_HELVETICA_12 is %d \n", glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, 'M'));
	printf("The width of 'M' in GLUT_BITMAP_HELVETICA_18 is %d \n\n\n", glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, 'M'));

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}
	

