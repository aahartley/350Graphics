#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 0, far = 10;
const float REGION_DIM = 2;
const GLfloat DtoR = 0.017453;
GLfloat theta = 0, phi = 90, rho = 5;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat direction = 1;


//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void idle(void);
void mouse(int, int, int, int);
void passiveMotion(int, int);
void mouseMotion(int x, int y);
void entry(int state);



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);//gluLookAt(2, 1, 3, 0, 0, 0, 0, 1, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	//--------- face 1-------------------------------
	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 1); glVertex3f(1, -1, -1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, -1);
	glColor3f(1, 0, 1); glVertex3f(-1, 1, -1);
	//-----------------------------------------------

	//--------- face 2-------------------------------
	glColor3f(1, 1, 1); glVertex3f(1, 1, -1);
	glColor3f(1, 0, 1); glVertex3f(-1, 1, -1);
	glColor3f(1, 0, 0); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 1);
	//-----------------------------------------------

	//--------- face 3-------------------------------
	glColor3f(0, 1, 0); glVertex3f(1, -1, 1);
	glColor3f(0, 0, 0); glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 0); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 1);
	//-----------------------------------------------

	//--------- face 4-------------------------------
	glColor3f(0, 1, 0); glVertex3f(1, -1, 1);
	glColor3f(0, 0, 0); glVertex3f(-1, -1, 1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 1); glVertex3f(1, -1, -1);
	//-----------------------------------------------

	//--------- face 5-------------------------------
	glColor3f(0, 1, 0); glVertex3f(1, -1, 1);
	glColor3f(0, 1, 1); glVertex3f(1, -1, -1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, -1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 1);
	//-----------------------------------------------

	//--------- face 6-------------------------------
	glColor3f(0, 0, 1); glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 1); glVertex3f(-1, 1, -1);
	glColor3f(1, 0, 0); glVertex3f(-1, 1, 1);
	glColor3f(0, 0, 0); glVertex3f(-1, -1, 1);
	//-----------------------------------------------

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

void idle()
{

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		theta +=  dTheta * direction;
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

void passiveMotion(int, int)
{

}

void mouseMotion(int x, int y)
{

}

void entry(int state)
{

}

void keys(unsigned char k, int x, int y)
{
	if (k == 'p')
		direction = 1;
	else if (k == 'n')
		direction = -1;
	else
	{
		theta = 0; phi = 90; rho = 5;
	}
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("cube");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	//glutIdleFunc(idle);
	glutMouseFunc(mouse);
	//glutMotionFunc(mouseMotion);
	//glutPassiveMotionFunc(passiveMotion);
	//glutEntryFunc(entry);

	glutMainLoop();
}