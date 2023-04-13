#include <GL/glut.h>
#include <math.h>

GLsizei ww = 400, wh = 400;
GLfloat theta[3] = {0, 0, 0};

GLubyte image[200][200][3];


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(0, 0, 1);
	
	glRectf(-50, -50, 50, 50);

	// read from the frame buffer and store in image
	glReadPixels(ww/2-100, wh/2-100, 200, 200, GL_RGB, GL_UNSIGNED_BYTE, image); 

	glRasterPos2f(-0.5*ww, -0.5*wh); // the lower left corner
	glDrawPixels(200, 200, GL_RGB, GL_UNSIGNED_BYTE, image);

	glRasterPos2f(-0.5*ww, 0.5*wh-200); // upper left
	glDrawPixels(200, 200, GL_RGB, GL_UNSIGNED_BYTE, image);

	glRasterPos2f(0.5*ww-200, -0.5*wh); // lower right
	glDrawPixels(200, 200, GL_RGB, GL_UNSIGNED_BYTE, image);

	glRasterPos2f(0.5*ww - 200, 0.5*wh-200); // upper right
	glDrawPixels(200, 200, GL_RGB, GL_UNSIGNED_BYTE, image);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(-0.5*w, 0.5*w, -0.5*h, 0.5*h);
	
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-0.5*ww, 0.5*ww, -0.5*wh, 0.5*wh);
	glMatrixMode(GL_MODELVIEW);
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("objects");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
}