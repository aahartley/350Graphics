#include <GL/glut.h>
#include <math.h>

GLsizei ww = 512, wh = 512;
GLfloat theta[3] = {0, 0, 0};
GLint axis = 3;

void axes()
{
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.8, 0, 0);
	glVertex3f(-1.5, 0, 0);
	glVertex3f(1.5, 0, 0);

	glColor3f(0, 0.8, 0);
	glVertex3f(0, -1.5, 0);
	glVertex3f(0, 1.5, 0);

	glColor3f(0, 0, 0.8);
	glVertex3f(0, 0, -1.5);
	glVertex3f(0, 0, 1.5);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	axes();

	//--------------------- rotation animation ---------------------
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	//--------------------------------------------------------------

	//axes();

	////-------------- glut cube --------------
	//glColor3f(1, 0, 1);
	//glLineWidth(3);
	//glutWireCube(2);
	//glColor3f(0, 1, 1);
	//glutSolidCube(2);

	////------------- glut sphere -------------
	//glColor3f(1, 0, 1);
	//glutWireSphere(1.005, 80, 40);
	//glColor3f(0, 1, 1);
	//glutSolidSphere(1, 80, 40);

	////------------- glut teapot -------------
	//glColor3f(1, 0, 1);
	//glutWireTeapot(1.005);
	//glColor3f(0, 1, 1);
	//glutSolidTeapot(1);

	////------------- glut torus --------------
	//glColor3f(1, 0, 1);
	//glutWireTorus(0.201, 1.5005, 20, 40);
	//glColor3f(0, 1, 1);
	//glutSolidTorus(0.2, 1.5, 20, 40);

	////-------------- glut cone --------------
	//glColor3f(1, 0, 1);
	//glutWireCone(1, 2, 30, 10);
	//glColor3f(0, 1, 1);
	//glutSolidCone(1, 2, 30, 10);

	////---------- glut Tetrahedron (4 faces)-----------
	//glColor3f(1, 0, 1);
	//glutWireTetrahedron();
	//glColor3f(0, 1, 1);
	//glutSolidTetrahedron();

	//---------- glut  Octahedron (8 faces)-----------
	glColor3f(1, 0, 1);
	glutWireOctahedron();
	glColor3f(0, 1, 1);
	glutSolidOctahedron();

	////---------- glut Dodecahedron (12 faces)----------
	//glColor3f(1, 0, 1);
	//glutWireDodecahedron();
	//glColor3f(0, 1, 1);
	//glutSolidDodecahedron();

	////---------- glut Icosahedron (20 faces)-----------
	//glColor3f(1, 0, 1);
	//glutWireIcosahedron();
	//glColor3f(0, 1, 1);
	//glutSolidIcosahedron();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-2.0*w/h, 2.0*w/h, -2, 2, -20, 20);
	else
		glOrtho(-2, 2, -2*h/w, 2*h/w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void init()
{
	glClearColor(0.625, 0.625, 0.625, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -20, 20);
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
	theta[axis] += 0.01;
	if (theta[axis] > 360.0)
		theta[axis] -= 360.0;
	glutPostRedisplay();
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("glut object");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}