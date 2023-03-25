#include <GL/glut.h>
#include <math.h>

GLsizei ww = 512, wh = 512;
GLfloat theta[3] = {0, 0, 0};
GLint axis = 0;

void display()
{
	GLUquadricObj *myObject;
	myObject = gluNewQuadric();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// rotation animation
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);

	glLineWidth(3);
	//---------- glu sphere -------------------------
	glColor3f(1, 0, 1);
	gluQuadricDrawStyle(myObject, GLU_LINE);
	gluSphere(myObject, 1, 10, 5);				//glu sphere
	glColor3f(0, 1, 1);
	gluQuadricDrawStyle(myObject, GLU_FILL);
	gluSphere(myObject, 1, 10, 5);
	//-----------------------------------------------

	////---------- glu cylinder -----------------------
	//glColor3f(1, 0, 1);
	//gluQuadricDrawStyle(myObject, GLU_LINE);
	//gluCylinder(myObject, 1.5, 1.5, 2, 60, 20);	//glu cylinder
	//glColor3f(0, 1, 1);
	//gluQuadricDrawStyle(myObject, GLU_FILL);
	//gluCylinder(myObject, 1.5, 1.5, 2, 60, 20);
	////------------------------------------------------

	////----------------- glu disk ---------------------
	//glColor3f(1, 0, 1);
	//gluQuadricDrawStyle(myObject, GLU_LINE);
	//gluDisk(myObject, 0.5, 1, 20, 10);			//glu disk
	//glColor3f(0, 1, 1);
	//gluQuadricDrawStyle(myObject, GLU_FILL);
	//gluDisk(myObject, 0.5, 1, 20, 10);
	////------------------------------------------------

	////----------------- glu partial disk -------------
	//glColor3f(1, 0, 1);
	//gluQuadricDrawStyle(myObject, GLU_LINE);
	//gluPartialDisk(myObject, 0.5, 1, 20, 20, 0, 180);	//glu partial disk	
	//glColor3f(0, 1, 1);
	//gluQuadricDrawStyle(myObject, GLU_FILL);
	//gluPartialDisk(myObject, 0.5, 1, 20, 20, 0, 180);
	////------------------------------------------------

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-3.0*w/h, 3.0*w/h, -3, 3, -20, 20);
	else
		glOrtho(-3, 3, -3*h/w, 3*h/w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = w;
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3, 3, -3, 3, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}

void idle()
{
	theta[axis] += 0.005;
	if (theta[axis] > 360.0)
		theta[axis] -= 360.0;
	glutPostRedisplay();
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("objects");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	return 0;
}