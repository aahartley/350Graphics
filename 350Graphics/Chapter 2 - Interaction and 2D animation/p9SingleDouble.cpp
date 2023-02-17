
#include <math.h>
#include <iostream>	// for printf etc.
#include <GL/glut.h>  // gl.h and glu.h are included in glut.h

#define DtoR 0.017453


// global variables
GLsizei ww = 512;
GLsizei hh = 512;
GLfloat left = -2.0;
GLfloat right = 2.0;
GLfloat bottom = -2.0;
GLfloat top = 2.0;
GLfloat thetaS = 45;
GLfloat thetaD = 45;
int direction = 1;

GLfloat x, y;
int singleb, doubleb;

GLubyte mask[] = {
	0x00, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x30, 0x00,
	0x00, 0x00, 0x70, 0x00,
	0x00, 0x00, 0x70, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x00, 0x00, 0xC0, 0x00,
	0x00, 0x00, 0xCF, 0x80,
	0x00, 0x00, 0xFF, 0xF8,
	0x00, 0xFF, 0xCF, 0xFF,
	0x03, 0xFC, 0xC3, 0xF8,
	0x1F, 0xF0, 0x80, 0x00,
	0x00, 0x00, 0x80, 0x00,
	0x00, 0x38, 0x80, 0x00,
	0x00, 0xFE, 0xB8, 0x00,
	0x00, 0xFF, 0xFC, 0x00,
	0x00, 0x7F, 0xF8, 0x00,
	0x01, 0xFF, 0xF0, 0x00,
	0x03, 0xFF, 0xFE, 0x00,
	0x03, 0xFF, 0xFF, 0x00,
	0x01, 0xFF, 0xFF, 0x00,
	0x00, 0xEF, 0xFF, 0x00,
	0x00, 0x0F, 0xFE, 0x00,
	0x00, 0x1F, 0xC0, 0x00,
	0x00, 0x3F, 0xC0, 0x00,
	0x00, 0x3F, 0x80, 0x00,
	0x00, 0x1F, 0x00, 0x00,
	0x00, 0x1E, 0x00, 0x00,
	0x00, 0x0C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00 };

void square(float theta)
{
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		glVertex2f(cos(DtoR*theta), sin(DtoR*theta));
		glVertex2f(-sin(DtoR*theta), cos(DtoR*theta));
		glVertex2f(-cos(DtoR*theta), -sin(DtoR*theta));
		glVertex2f(sin(DtoR*theta), -cos(DtoR*theta));
		glEnd();

		glEnable(GL_POLYGON_STIPPLE);
		glColor3f(1, 0, 0);
		glPolygonStipple(mask);
		glBegin(GL_POLYGON);
		glVertex2f(cos(DtoR*theta), sin(DtoR*theta));
		glVertex2f(-sin(DtoR*theta), cos(DtoR*theta));
		glVertex2f(-cos(DtoR*theta), -sin(DtoR*theta));
		glVertex2f(sin(DtoR*theta), -cos(DtoR*theta));
		glEnd();
		glDisable(GL_POLYGON_STIPPLE);
}


void displayD()
{
    glClear (GL_COLOR_BUFFER_BIT);
    square(thetaD);
    glutSwapBuffers ();
}

void displayS()
{
    glClear (GL_COLOR_BUFFER_BIT);
    square(thetaS);
    glFlush();
}

void spinDisplayS ()
{
	thetaS += 0.01 * direction;

	if (thetaS > 360.0)
		thetaS -= 360.0;
	else if ( thetaS < 0.0 )
		thetaS += 360.0;

    glutSetWindow(singleb);
    glutPostRedisplay();
}

void spinDisplayD ()
{
	thetaD += 0.01 * direction;

	if (thetaD > 360.0)
		thetaD -= 360.0;
	else if ( thetaD < 0.0 )
		thetaD += 360.0;

    glutSetWindow(doubleb);
    glutPostRedisplay();
}

void init()
{
	glClearColor(0.4, 0.4, 0.4, 1.0);

	glColor3f(0.4, 0.6, 0.8);

//	glShadeModel(GL_FLAT);

	// Set the view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);
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

	glViewport(0,0,w,h);

	// Reset the window size
	ww = w;
	hh = h;
}

void mouse(int btn, int state, int x, int y)
{
     if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
     {
		 glutIdleFunc(spinDisplayS);
	 }
     if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) 
	 {
		 glutIdleFunc(NULL);
	 }
	 if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	 {
		 glutIdleFunc(spinDisplayD);
	 }
}

void keys(unsigned char k, int x, int y)
{
	if ( k == 'u' )
		direction = 1;
	else if ( k == 'd' )
		direction = -1;
}

void main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, hh);
	glutInitWindowPosition(0, 0);
    singleb=glutCreateWindow("single buffered");
    init ();
	glutDisplayFunc(displayS);
    glutReshapeFunc(reshape);
    glutIdleFunc(spinDisplayS);
    glutMouseFunc(mouse);
	glutKeyboardFunc( keys );

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(ww, hh);
	glutInitWindowPosition(ww+24, 0);
    doubleb=glutCreateWindow("double buffered");
    init ();
    glutDisplayFunc(displayD);
    glutReshapeFunc (reshape);
    glutIdleFunc (spinDisplayD);
    glutMouseFunc (mouse);	// could be a different mouse call back
	glutKeyboardFunc( keys );	// could be a different key call back

    glutMainLoop();
}
