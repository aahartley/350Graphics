#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -2;
GLfloat right = 2;
GLfloat bottom = -2;
GLfloat top = 2;
GLfloat theta; 
GLfloat direction = 1; 
const GLfloat DtoR = 0.017453;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void idle(void);
void mouse(int button, int state, int x, int y);


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glBegin(GL_POLYGON);
	glVertex2f(cos(DtoR*theta), sin(DtoR*theta));
	glVertex2f(-sin(DtoR*theta), cos(DtoR*theta));
	glVertex2f(-cos(DtoR*theta), -sin(DtoR*theta));
	glVertex2f(sin(DtoR*theta), -cos(DtoR*theta));
	glEnd();

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
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	// default (-1, 1, -1, 1)
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w*1.0 / (h*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;	
	wh = h;
}

void idle()
{
	theta += direction * 0.01;

	if (theta > 360.0)
		theta -= 360.0;

	if (theta < 0.0)
		theta += 360.0;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		direction = 1;
	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
		direction = -1;
	if ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN))
		direction = 0;
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(800, 200); // defualt at (0, 0)
	glutCreateWindow("2D animation and interaction");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);

	glutMainLoop();
}