//#include <math.h>
#include <cmath>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -4;
GLfloat right = 4;
GLfloat bottom = -4;
GLfloat top = 4;
const float REGION_DIM = 2;
const GLfloat DtoR = 0.017453;
const float Pi = 3.1415926535;

float Alpha = 0;
float Beta = 0;
float Gama = 0;
float Theta = 0;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void idle(void);
void mouse(int, int, int, int);
void passiveMotion(int, int);
void mouseMotion(int x, int y);
void entry(int state);
void curve(void);
void movingPoint(void);

void movingPoint(void)
{
	float r, x, y;
	
	//------------- the moving point in the curve --------------
	glPointSize(9);
	glBegin(GL_POINTS);
		r = cos(2 * Theta);
		x = r * cos(Theta);
		y = r * sin(Theta);
		glVertex2f(x, y);
	glEnd();

	////------------- connecting the moving point with the origin -----------
	//glColor3f(0.3, 0.3, 0.3);
	//glBegin(GL_LINES);
	//r = cos(2 * Theta);
	//x = r*cos(Theta);
	//y = r*sin(Theta);
	//glVertex2f(x, y);
	//glVertex2f(0, 0);
	//glEnd();
}

void curve(void)
{
	float r, theta;
	float alpha = 0;
	float beta = 2 * Pi;
	float x, y;
	float dTheta = 0.01;

	glBegin(GL_LINE_STRIP);
	theta = alpha;
	while (theta <= beta)
	{
		r = cos(2 * theta);

		x = r * cos(theta);
		y = r * sin(theta);
		glVertex2f(x, y);

		theta += dTheta;
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glColor3f(0, 1, 1);
	curve();

	glColor3f(1, 0, 0);
	glPointSize(4);
	movingPoint();

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
	gluOrtho2D(left, right, bottom, top);
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
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void idle()
{
	Theta += 0.001;

	if (Theta >= 2*Pi)
		Theta -= 2*Pi;

	glutPostRedisplay();
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(800, 100); // defualt at (0, 0)
	glutCreateWindow("2D animation and interaction");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();
}