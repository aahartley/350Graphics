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
float Alpha = 0, Beta = 0, Gama = 0;
const GLfloat DtoR = 0.017453;


//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void idle(void);
void mouseClick(int, int, int, int);
void passiveMotion(int, int);
void mouseMotion(int x, int y);
void entry(int state);
void keys(unsigned char k, int x, int y);
void timer(int v);
void right_menu(int id);



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	
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

	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		;
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

}

void timer(int v)
{

	glutPostRedisplay();

	glutTimerFunc(1000, timer, v);
}

void right_menu(int id)
{
	
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("2D animation and interaction");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	//glutMotionFunc(mouseMotion);
	//glutPassiveMotionFunc(passiveMotion);
	//glutEntryFunc(entry);
	//glutTimerFunc(1000, timer, 1);
	glutKeyboardFunc(keys);
	glutIdleFunc(idle);

	//glutCreateMenu(right_menu);
	//glutAddMenuEntry("1", 1);
	//glutAddMenuEntry("2", 2);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}