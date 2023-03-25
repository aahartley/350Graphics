//#include <math.h>
#include "../myObjects2023.cpp"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 10, far = 40;
const float REGION_DIM = 4;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat a = 1, b = 1, c = 1;
GLfloat dA = 0.1, dB = 0.1, dC = 0.1;
GLfloat direction = 1.0;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void mouse(int, int, int, int);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 10, 15, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glScalef(a, a, a);
	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glColor3f(1, 0, 0);
	glutWireCube(1);

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void init(void)
{
	float ratio = ww * 1.0 / (wh*1.0);

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
	glFrustum(left, right, bottom, top, near, far);	
	// perspective projection with frustum. use it as same time in reshape
	//gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w * 1.0 / (h*1.0);

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
	glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in init
													//gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

								//------ reset the window size
	ww = w;
	wh = h;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		a *= 2;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		a = 1;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		a /= 2;
	}
}


int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("3D programming");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}