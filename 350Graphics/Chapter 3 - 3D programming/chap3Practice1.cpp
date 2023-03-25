#include <stdlib.h>
#include <GL\glut.h>
#include <math.h>


//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 0, far = 10;
const float REGION_DIM = 2;
const GLfloat DtoR = 0.017453;
GLfloat theta = 0, phi = 90, rho = 5;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;


//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void keys(unsigned char k, int x, int y);
void specialKeys(int k, int x, int y);


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);
	

	//----------- the object --------------------------
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex3f(0, 2, 0);
	glColor3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glColor3f(1, 0, 1);
	glVertex3f(-1, 0, 1);

	glColor3f(1, 0, 0);
	glVertex3f(1, 0, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 0, -1);
	glColor3f(0, 0, 1);
	glVertex3f(0, 2, 0);

	glColor3f(0, 0, 1);
	glVertex3f(1, 0, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 0, 1);
	glColor3f(1, 1, 0);
	glVertex3f(0, 2, 0);

	glColor3f(0, 1, 1);
	glVertex3f(0, 2, 0);
	glColor3f(1, 0, 1);
	glVertex3f(-1, 0, 1);
	glColor3f(0, 0, 1);
	glVertex3f(-1, 0, -1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);
	glVertex3f(-1, 0, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, 0, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, 0, -1);
	glColor3f(0, 1, 0);
	glVertex3f(1, 0, 1);
	glEnd();

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(0.8, 0.8, 0.8, 1.0);	// background color; default black; (R, G, B, Opacity)
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

	glOrtho(left, right, bottom, top, near, far);
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

	glOrtho(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void keys(unsigned char k, int x, int y)
{
	if (k == '+')
		rho += dRho;
	else if (k == '-')
		rho -= dRho;
	else if (k == 'R' || k == 'r')
	{
		theta = 0; phi = 90; rho = 5;
	}
}

void specialKeys(int k, int x, int y)
{
	if (k == GLUT_KEY_LEFT)
	{
		theta -= dTheta;

		if (theta < -360)
			theta += 360;
	}
	else if (k == GLUT_KEY_RIGHT)
	{
		theta += dTheta;

		if (theta > -360)
			theta += 360;
	}
	else if (k == GLUT_KEY_UP)
	{
		phi -= dPhi;
		if (phi < -360)
			phi += 360;
	}
	else if (k == GLUT_KEY_DOWN)
	{
		phi += dPhi;
		if (phi > 360)
			phi -= 360;
	}
}


int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("3D programming");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);

	glutMainLoop();
	return 0;
}