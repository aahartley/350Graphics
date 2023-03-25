#include <GL/glut.h>
#include <math.h>

#define DtoR 0.017453

GLsizei ww = 500, wh = 500;
GLfloat sunRotation = 0, earthRotation = 0, moonRotation = 0;
GLfloat earthRevolution = 0, moonRevolution = 0;
GLfloat increment = 0.001;
GLfloat halfWidth = 5;
GLfloat halfHeight = 5;

GLfloat left = -3.0;
GLfloat right = 3.0;
GLfloat bottom = -3.0;
GLfloat top = 3.0;
GLfloat near = 10.0;
GLfloat far = 20.0;


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(10, 10, 3, 0, 0, 0, 0, 0, 1); // for perspective view

	//----------------------- the sun ---------------------
	glPushMatrix();
		glRotatef(sunRotation, 0, 0, 1);

		glColor3f(1, 0.2, 0.2);
		glutSolidSphere(1, 20, 10);
		glColor3f(1, 1, 0);
		glutWireSphere(1.01, 20, 10);
	glPopMatrix();
	//-----------------------------------------------------

	//-------------- revolve about the sun ----------------
	glPushMatrix();
		glTranslatef(3*cos(earthRevolution*DtoR), 3*sin(earthRevolution*DtoR), 0);

		//------- the moon revolves around the earth ------
		glRotatef(moonRevolution, 0, 0, 1);

		//------------------- the earth -------------------
		glPushMatrix();
			glRotatef(earthRotation - moonRevolution, 0, 0, 1);
	
			glColor3f(0.1, 0.8, 1);
			glutSolidSphere(0.5, 10, 20);
			glColor3f(0, 0, 1);
			glutWireSphere(0.505, 10, 20);
		glPopMatrix();
		//-------------------------------------------------

		glTranslatef(1, 0, 0);
		//------------------ the moon --------------------
		glColor3f(1, 0.8, 0);
		glutSolidSphere(0.25, 16, 8);
		glColor3f(0.5, 0.5, 0.5);
		glutWireSphere(0.255, 16, 8);
	glPopMatrix();

	glutSwapBuffers();
}

// ============================= perspective view ====================================
void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glFrustum(left*w/h, right*w/h, bottom, top, near, far);
	else
		glFrustum(left, right, bottom*h/w, top*h/w, near, far);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = w;
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
}
// =================================================================================

void idle()
{
	earthRevolution += increment; 
	if ( earthRevolution > 360 ) earthRevolution -= 360;

	sunRotation += 14.92 * increment;
	if ( sunRotation > 360 ) sunRotation -= 360;
	glutPostRedisplay();

	earthRotation += 365 * increment;
	if ( earthRotation > 360 ) earthRotation -= 360;
	glutPostRedisplay();

	moonRevolution += 12.36 * increment;
	if ( moonRevolution > 360 ) moonRevolution -= 360;
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
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}

