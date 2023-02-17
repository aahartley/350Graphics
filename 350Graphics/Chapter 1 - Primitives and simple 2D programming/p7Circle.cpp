#include <GL\glut.h>
#include <math.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -4;
GLfloat right = 4;
GLfloat bottom = -4;
GLfloat top = 4;
const float DtoR = 0.017453;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void circle(float x0, float y0, float r);


void display(void)
{
	float r = 1;
	float x, y;
	float theta = 0; 

	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i += 10)
	{
		theta = i * DtoR;
		x = r * cos(theta);
		y = r * sin(theta);

		glVertex2f(x, y);
	}
	glEnd();
	
	////------- a circle ----------
	//glColor3f(1, 0, 0);
	//circle(2, 0, 1);

	////-------- another circle ---------
	//glColor3f(0, 1, 0);
	//circle(-0.5, 0.5, 1.5);

	glFlush();	// force to render, work with single buffer
}

void circle(float x0, float y0, float r)
{
	float theta;
	float x, y;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i += 10)
	{
		theta = i * DtoR;
		x = x0 + r * cos(theta);
		y = y0 + r * sin(theta);

		glVertex2f(x, y);

	}
	glEnd();
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

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(800, 200); // defualt at (0, 0)
	glutCreateWindow("2D Program");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	// envoked when the window is reshaped or moved; also envoked when the window is displayed at the first time

	glutMainLoop();

	return 0;
}