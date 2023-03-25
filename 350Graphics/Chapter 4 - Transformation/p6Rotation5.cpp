#include <math.h>
#include "../myObjects2023.cpp"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 5, far = 20;
const float REGION_DIM = 2;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat direction = 1.0;
GLfloat alpha = 0;

//----- prototypes ----------
void init(void);
void reshape(GLsizei w, GLsizei h);
void idle(void);
void mouse(int, int, int, int);


void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 4, 5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glLineWidth(1);
	axes(4);	// axes for the entire space

	//------------------ rotate about x=1, z=0 
	glColor3f(0, 0, 0);
	glLineWidth(4);
	glBegin(GL_LINES);
		glVertex3f(1, -2, 0);
		glVertex3f(1, 2, 0);
	glEnd();

	glTranslatef(1, 0, 0);
	glRotatef(alpha, 0, 1, 0);
	glTranslatef(-1, 0, 0);
	//-----------------------------------------------

	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glColor3f(1, 0, 0);
	glutWireCube(1);

	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 4, 6, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glLineWidth(1);
	axes(4);	// axes for the space

	//------------------ rotate about x=1 and z=1
	glTranslatef(1, 0, 1);
	glRotatef(alpha, 0, 1, 0);
	glTranslatef(-1, 0, -1);
	//-----------------------------------------------

	//------ the line x=1, z=1
	glColor3f(0, 0, 0);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glEnd();
	//---------------------------------------------------------------
	
	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glColor3f(1, 0, 0);
	glutWireCube(1);

	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE
}


void display3(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(8, 6, 8, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glLineWidth(1);
	axes(4);	// axes for space

	//---- rotate about the axis determined by (-2, -1, 0) and (1, 2, 0);
	glTranslatef(-2, -1, 0);	// move to the desired lacation
	glRotatef(alpha, 3, 3, 0);	// then the below line rotates about itself
	glTranslatef(2, 1, 0);	// so the below line passes through the origin

	glColor3f(0, 0, 0);
	glLineWidth(4);
	glBegin(GL_LINES);
		glVertex3f(-2, -1, 0);
		glVertex3f(1, 2, 0);
	glEnd();
	//---------------------------------------------------------------

	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glColor3f(1, 0, 0);
	glutWireCube(1);

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	//----------- just use one of the following -------------------
//	glOrtho(left, right, bottom, top, near, far);	// orthogonal projection
	glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in reshape

	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w*1.0 / (h*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	// ------------------------ just use one of the following -----------------------
	//glOrtho(left, right, bottom, top, near, far);	// orthogonal projection
	glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in init

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void idle()
{
	alpha += 0.01;

	if (alpha >= 360)
		alpha -= 360.0;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutDisplayFunc(display1);

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		glutDisplayFunc(display2);

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		glutDisplayFunc(display3);

	glutPostRedisplay();
}

void keys(unsigned char k, int x, int y)
{
	if (k == 'p')
		direction = 1.0;
	else if (k == 'n')
		direction = -1.0;
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("3D programming");
	init();

	glutDisplayFunc(display1);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);

	glutMainLoop();

	return 0;
}