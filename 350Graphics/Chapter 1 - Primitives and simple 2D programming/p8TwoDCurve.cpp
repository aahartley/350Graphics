#include <GL\glut.h>
#include <math.h>

//------ global variables and constants------------
const float DtoR = 0.017453;
const float Pi = 3.14159;
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -10;
GLfloat right = 10;
GLfloat bottom = -10;
GLfloat top = 10;

//----- prototypes ----------
void displayCurve(void);
void displayParameterCurve(void);
void displayPolarCurve(void);
void coordAxes(void);
void init(void);
void reshape(GLsizei w, GLsizei h);

void coordAxes()
{
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_LINES);
	glVertex2f(left, 0);
	glVertex2f(right, 0);
	glVertex2f(0, bottom);
	glVertex2f(0, top);
	glEnd();
}

void displayCurve(void)
{
	float x, y;
	float dx = 0.1;
	float a = left;
	float b = right;

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background
	coordAxes();

	glLineWidth(2);
	glColor3f(0, 1, 1);
	glBegin(GL_LINE_STRIP);
	x = a;
	while (x <= b)
	{
		y = sin(x);//(x*x*x + 2 * x*x + 3 * x - 1) / (x*x + x + 2);//1 / x; //atan(x); //pow(x, 0.5); //exp(x); //log(x);
		glVertex2f(x, y);

		x += dx;
	}
	glEnd();

	glFlush();	// force to render, work with single buffer
}


void displayParametrizedCurve(void)
{
	float x, y, t;
	float dt = 5;
	float a = 0;
	float b = 360;

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background
	coordAxes();

	glLineWidth(2);
	glColor3f(0, 1, 1);
	glBegin(GL_LINE_STRIP);
	t = a;
	
	while(t <= b)
	{
		x = 5*cos(t*DtoR);
		y = 5*sin(t*DtoR);
		glVertex2f(x, y);

		t += dt;
	}
	glEnd();

	glFlush();	// force to render, work with single buffer
}

void displayPolarCurve(void)
{
	float r, theta;
	float alpha = 0;
	float beta = 2 * Pi;
	float x, y;
	float dTheta = 0.01;

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background
	coordAxes();

	glLineWidth(2);
	glColor3f(0, 1, 1);
	glBegin(GL_LINE_STRIP);
	theta = alpha;
	while (theta <= beta)
	{
		r = 4 * cos(8*theta);
		
		x = r * cos(theta);
		y = r * sin(theta);
		glVertex2f(x, y);

		theta += dTheta;
	}
	glEnd();

	glFlush();	// force to render, work with single buffer
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	float ratio = ww * 1.0 / (wh*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	// default (-1, 1, -1, 1)
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, ww, wh);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w * 1.0 / (h*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	//------ reset the window size
	ww = w;
	wh = h;
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(800, 200); // defualt at (0, 0)
	glutCreateWindow("2D Program");
	init();

	glutDisplayFunc(displayCurve);
	//glutDisplayFunc(displayParametrizedCurve);
	//glutDisplayFunc(displayPolarCurve);
	glutReshapeFunc(reshape);

	glutMainLoop();
}