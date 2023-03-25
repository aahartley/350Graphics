#include <GL/glut.h>
#include <math.h>



#define DtoR 0.017453

GLsizei ww = 500, wh = 500;
GLfloat alpha = 0, beta = 0, gama = 0;
GLfloat halfWidth = 5;
GLfloat halfHeight = 5;


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

	gluLookAt(1, 1, 8, 0, 0, 0, 0, 1, 0);

	//------------- the center cube -----------------
	glPushMatrix();
		glRotatef(alpha, 1, 0, 0);	//rotation about the x-axis
		glColor3f(1, 0.2, 0.2);
		glutSolidCube(1);
		glColor3f(0.5, 0.5, 0.5);
		glutWireCube(1.01);
	glPopMatrix();
	//-----------------------------------------------

	glRotatef(beta, 0, 0, 1);	// revolution around the center
	
	glTranslatef(3, 0, 0);	// shift to the side
	glRotatef(-beta, 0, 0, 1);	// to cancel the revolution by a negative rotation

	//---------- the other cube -------------
	glPushMatrix();
		glRotatef(gama, 0, 1, 0); //rotation about the y-axis
		glColor3f(0.1, 0.8, 1);
		glutSolidCube(1);
		glColor3f(0.5, 0.5, 0.5);
		glutWireCube(1.01);
	glPopMatrix();
	//---------------------------------------

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


void idle()
{
	alpha += 0.005;
	if(alpha > 360) alpha -= 360;

	beta += 0.01;
	if(beta > 360) beta -= 360;

	gama += 0.015;
	if(gama > 360) gama -= 360;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(idle);

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(NULL);

	glutPostRedisplay();
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("relative movements");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}

