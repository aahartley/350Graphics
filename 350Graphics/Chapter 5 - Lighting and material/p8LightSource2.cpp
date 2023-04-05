#include <GL/glut.h>

GLfloat ww = 500, wh = 500;
GLfloat dx = 1, dy = 1, dz = 1;
GLfloat lightPos[] = {1, 2, 3, 1};
GLfloat diffuse[] = {0.2, 0.7, 0.2, 1};
GLfloat specular[] = {0.3, 1, 0.3, 1};
GLfloat ambient[] = {0.1, 0.6, 0.1, 1};
GLfloat theta = 0;

GLfloat global_ambient[] = {1.0, 0.0, 0.0, 1.0};  // independent of any of the sources



void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);    // GL_DEPTH_TEST must be enabled if the z buffer is used.

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2, 1, 3, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
		glRotatef(theta, dx, dy, dz);
		glutSolidCube(1);
		//glutWireCube(1);
		//glutSolidTeapot(1);
		//glutWireTeapot(1);
		//glColor3f(1, 1, 0); glutSolidIcosahedron(); glColor3f(0, 1, 0); glutWireIcosahedron();
		//glutSolidDodecahedron();
		//glutSolidOctahedron();
		//glutSolidTetrahedron();
		//glutSolidSphere(1, 50, 50);
		//glutSolidCone(1, 2, 50, 50);
		//glutSolidTorus(0.5, 1, 50, 50);
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
	theta += 0.01;
	if (theta > 360)
		theta -= 360;

	glutPostRedisplay();
}

void init()
{
	glClearColor(0.1, 0.1, 0.1, 1);
	glColor3f(1, 0, 0);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

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
	return 0;
}