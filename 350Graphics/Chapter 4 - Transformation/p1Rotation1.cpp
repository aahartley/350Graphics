//#include <math.h>
//#include <GL/glut.h>
#include "../myObjects2023.cpp"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 5, far = 20;
const float REGION_DIM = 4;
//const GLfloat DtoR = 0.017453;
GLfloat theta = 30, phi = 60, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;

GLfloat axis[3] = {1, 0, 0};
GLfloat angle = 0;
GLfloat increment = 5; 


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);

	axes(2*REGION_DIM);
	glRotatef(angle, axis[0], axis[1], axis[2]);	// one rotation, starting from the original position

	glColor3f(0, 1, 1);
	glutSolidCube(1);

	glColor3f(1, 0, 0);
	glutWireCube(1.01);

	glutSwapBuffers();
	glutPostRedisplay();
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

	glFrustum(left, right, bottom, top, near, far);	

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

	glFrustum(left, right, bottom, top, near, far);	

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		

	//------ reset the window size
	ww = w;
	wh = h;
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		axis[0] = 1; axis[1] = 0; axis[2] = 0;	// the x-axis
	}

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		axis[0] = 0; axis[1] = 1; axis[2] = 0;	// the y-axis
	}

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		axis[0] = 0; axis[1] = 0; axis[2] = 1;	// the z-axis
	}

	angle += increment;

	display();
}

void keyboard(unsigned char k, int x, int y)
{
	if ( k == 'p' || k == 'P' )
		if ( increment < 0 )
			increment = -1.0 * increment;
	else if ( k == 'n' || k == 'N' )
		if ( increment > 0 )
			increment = -1.0 * increment;
}


void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("translate cube");
	init();
	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}

