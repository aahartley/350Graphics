#include <GL/glut.h>
#include <math.h>
//#include <iostream> // for printf

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

	glColor3f(1, 0, 0);
	glLineWidth(6);

	//------------- the center cube -----------------
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT); // lots of bits. could use GL_ALL_ATTRIB_BITS
		glLineWidth(1);
		glColor3f(0, 0, 1);
		glRotatef(alpha, 1, 0, 0); //self rotation
		glutWireCube(1);
	glPopAttrib();
	glPopMatrix();
	//-----------------------------------------------

	//----------- revolve about the center cube -----------
	glRotatef(beta, 0, 0, 1); //the following object revolves about the z-axis

	glPushMatrix();
		/*glLineWidth(3);
		glColor3f(0, 1, 0);*/
		//glRotatef(-beta, 0, 0, 1); //don't use it. it would cancel the revolution about the z-axis
		glTranslatef(3, 0, 0);
		glRotatef(-beta, 0, 0, 1); //put it after translation to cancel the rotation about the z-axis

		glRotatef(gama, 0, 1, 0); //self rotation
		glutWireCube(1);
	glPopMatrix();
	//-----------------------------------------------------


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
	alpha += 0.01;
	if(alpha > 360) alpha -= 360;

	beta += 0.01;
	if(beta > 360) beta -= 360;

	gama += 0.01;
	if(gama > 360) gama -= 360;

	glutPostRedisplay();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
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

