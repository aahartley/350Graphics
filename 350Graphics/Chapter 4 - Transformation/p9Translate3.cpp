#include <GL/glut.h>
#include <math.h>
//#include "../myObjects2023.cpp"


GLfloat shift[3] = {0, 0, 0};
GLfloat step = 0.1;
GLfloat increment = step;
GLsizei ww = 512, wh = 512;
GLfloat fov = 45.0;
GLfloat aspect = 1;
GLfloat near = 5.0;
GLfloat far = 15.0;
GLfloat theta = 30, phi = 60, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
float DtoR = 0.017453;



void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);

	glTranslatef(shift[0], shift[1], shift[2]);

	//glutWireCube(1);
	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glColor3f(1, 0, 0);
	glutWireCube(1);
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect*w/h, near, far);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect, near, far);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		shift[0] += increment;

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		shift[1] += increment;

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		shift[2] += increment;

	display();
}

void keyboard(unsigned char k, int x, int y)
{
	if ( k == 'p' || k == 'P' )
		increment = 1.0 * step;
	else if ( k == 'n' || k == 'N' )
		increment = -1.0 * step;
	else if (k == '+')
		rho -= dRho;
	else if (k == '-')
		rho += dRho;
}

void specialKeys(int k, int x, int y)
{
	if (k == GLUT_KEY_LEFT)
		theta -= dTheta;
	else if (k == GLUT_KEY_RIGHT)
		theta += dTheta;
	else if (k == GLUT_KEY_UP)
	{
		if (phi > dPhi)
			phi -= dPhi;
		else if (phi == dPhi)
			phi = 0.01;		// to keep the direction vector of the camera
	}
	else if (k == GLUT_KEY_DOWN)
	{
		if (phi <= 180 - dPhi)
			phi += dPhi;
	}
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("translate cube");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);

	init();
	glutMainLoop();
}

