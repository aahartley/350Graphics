//#include <math.h>
//#include <GL\glut.h>
#include "../myObjects2023.cpp"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top;
GLfloat fov = 45.0;	// field of view/vision; angle in the y-direction
GLfloat aspect = 1;	// width to height; x/y
GLfloat near = 1.0;
GLfloat far = 10.0;
const float REGION_DIM = 2;
//const GLfloat DtoR = 0.017453;
GLfloat theta = 0, phi = 90, rho = 5;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat direction = 1.0;


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
	gluLookAt(rho * sin(theta * DtoR) * sin(phi * DtoR), rho * cos(phi * DtoR), rho * cos(theta * DtoR) * sin(phi * DtoR), 0, 0, 0, 0, 1, 0);

	//----------- the object --------------------------
	//axes(2*REGION_DIM);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1, 0, 0);

	cone(1, 2);

	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect * w / h, near, far);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect, near, far);
	glMatrixMode(GL_MODELVIEW);
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

		if (theta > 360)
			theta -= 360;
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

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		direction = 1.0;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		direction = -1.0;
	}
}


void main()
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
	glutMouseFunc(mouse);

	glutMainLoop();
}