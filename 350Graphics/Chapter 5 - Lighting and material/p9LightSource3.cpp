#include <GL/glut.h>

GLfloat ww = 500, wh = 500;
GLfloat dx = 1, dy = 1, dz = 1;
GLfloat lightPos[] = {1, 2, 3, 1};
GLfloat diffuse[] = {.7, 0.7, 0.7, 1};
GLfloat specular[] = {1, 1, 1, 1};
GLfloat ambient[] = {0.2, 0.0, 0.0, 1};
GLfloat theta = 0;
GLfloat emission[] = { 0.4, 0.4, 0 };
GLfloat global_ambient[] = {1, 0.0, 0.0, 1.0};  // independent of any of the sources


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);    // GL_DEPTH_TEST must be enabled if the z buffer is used.

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2, 1, 3, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	glRotatef(theta, dx, dy, dz);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1, 0, 0);
		glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
		glTranslatef(1, 0, 0);
		glutSolidSphere(0.5, 50, 50);
	glPopAttrib();
	glPopMatrix();
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-2.0*w/h, 2.0*w/h, -2.0, 2.0, -20, 20);
	else
		glOrtho(-2, 2, -2.0*h/w, 2.0*h/w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	ww = w;
	wh = h;

	glViewport(0, 0, w, h);
}

void idle()
{
	theta += 0.05;
	if (theta > 360)
		theta -= 360;

	glutPostRedisplay();
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	//glColor3f(0.2, 0.2, 0.5);	//color is disabled when light is used
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(idle);
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
	
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(nullptr);
	}
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("light source");

	glutDisplayFunc(display);
	glutIdleFunc(nullptr);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
}