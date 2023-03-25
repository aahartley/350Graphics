#include <math.h>
#include "GL/glut.h"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 0, far = 20;
const float REGION_DIM = 4;
const GLfloat DtoR = 0.017453;
//GLfloat fov = 45.0, aspect = 1;
GLfloat theta = 0, phi = 90, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat a = 1, b = 1, c = 1;
GLfloat dA = 0.1, dB = 0.1;
GLfloat direction = 1.0;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void keys(unsigned char k, int x, int y);
void mouse(int, int, int, int);


void cone(float r, float h)
{
	//glBegin(GL_QUAD_STRIP);
	//for (int theta = 0; theta <= 360; theta += 5)
	//{
	//	glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);
	//	glVertex3f(0, 0, h);
	//}
	//glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, h);
	for (int theta = 0; theta <= 360; theta += 5)
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);
		
	glEnd();
}


void cylinder(float r, float h)
{
	glBegin(GL_QUAD_STRIP);
	for (int theta = 0; theta <= 360; theta += 5)
	{
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), h);
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);
	//----- draw in FILL mode -----------------
	glColor3f(1, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//cylinder(a, b);
	cone(a, b);

	//------- draw in LINE mode -----------
	glColor3f(1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//cylinder(a*1.01, b*1.01);
	cone(a*1.01, b*1.01);

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color; default black; (R, G, B, Opacity)
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

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		theta += dTheta * direction;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		rho += dRho * direction;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		phi += dPhi * direction;
	}
}

void keys(unsigned char k, int x, int y)
{
	if (k == 'p' || k == 'P')
		direction = 1.0;
	else if (k == 'n' || k == 'N')
		direction = -1.0;
	else if (k == 'a' || k == 'A')
		a += dA * direction;
	else if (k == 'b' || k == 'B')
		b += dB * direction;
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
	glutKeyboardFunc(keys);

	glutMainLoop();
	return 1; 
}