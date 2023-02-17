#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left;
GLfloat right;
GLfloat bottom;
GLfloat top;
GLfloat REGION_DIM = 2;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void mouseClick(int, int, int, int);



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glColor3f(1, 0, 0);
	glRectf(left, top, 0, 0);

	glColor3f(0, 1, 0);
	glRectf(0, right, top, 0);

	glColor3f(0, 0, 1);
	glRectf(left, bottom, 0, 0);

	glColor3f(1, 1, 0);
	glRectf(0, bottom, right, 0);

	glColor3f(0, 0, 0);

	glFlush();
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 0, 0);	// drawing color; default white

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


void mouseClick(int button, int state, int x, int y)
{
	char red[] = "RED";
	char green[] = "GREEN";
	char blue[] = "BLUE";
	char yellow[] = "YELLOW";
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x < ww / 2 && y > wh / 2) //left bottom
		{
			display();
			glRasterPos2f(left/2, bottom/2);
			for (char* c = blue; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
			}
		}
		else if(x > ww / 2 && y > wh / 2)
		{
			display();
			glRasterPos2f(right / 2, bottom / 2);
			for (char* c = yellow; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
			}
		}
		else if (x > ww / 2 && y < wh / 2)
		{
			display();
			glRasterPos2f(right / 2, top / 2);
			for (char* c = green; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
			}
		}
		else if (x < ww / 2 && y < wh / 2)
		{
			display();
			glRasterPos2f(left / 2, top / 2);
			for (char* c = red; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
			}
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		;
	}

	glFlush();
}


void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("2D interaction");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	
	glutMainLoop();
}