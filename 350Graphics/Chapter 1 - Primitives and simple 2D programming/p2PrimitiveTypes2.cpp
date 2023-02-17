#include <GL/glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -1.0;
GLfloat right = 1.0;
GLfloat bottom = -1.0;
GLfloat top = 1.0;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);


void display() // display polygons
{
	glClearColor(0.75, 0.75, 0.75, 1.0); // background color; values are in [0, 1]; default RGB are 0s
	glClear(GL_COLOR_BUFFER_BIT);

	//-----polygon modes-------------------
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL (default mode),GL_LINE,GL_POINT
	glLineWidth(4);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPointSize(4);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	//----------------------------------------------

	//-----polygon with a single color-------------------------------
	//glBegin(GL_POLYGON);
	//glColor3f(1, 0, 1); // could be before the type definition
	//glVertex2f(-0.5, -0.5);
	//glVertex2f(0.5, -0.5);
	//glVertex2f(0.5, 0.5);
	//glVertex2f(-0.5, 0.5);
	//glVertex2f(-0.7, 0.2);
	//glVertex2f(-0.6, -0.3);
	//glEnd();
	//---------------------------------------------------------

	////-----triangles with multi colors----------------------
	//glBegin(GL_TRIANGLES);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.5, -0.5);

	//glColor3f(0, 1, 0);
	//glVertex2f(0.5, -0.5);

	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.5);

	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.5);

	//glColor3f(1, 1, 0);
	//glVertex2f(-0.7, 0.2);

	//glColor3f(0, 0, 0);
	//glVertex2f(-0.6, -0.3);
	//glEnd();
	////----------------------------------------------------

	////----triangle strip----------------
	//glBegin(GL_TRIANGLE_STRIP);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.5, -0.5);

	//glColor3f(0, 1, 0);
	//glVertex2f(0.5, -0.5);

	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.5);

	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.5);

	//glColor3f(1, 1, 0);
	//glVertex2f(-0.7, 0.2);

	//glColor3f(0, 0, 0);
	//glVertex2f(-0.6, -0.3);
	//glEnd();
	////-----------------------------------------

	////------one triangle fan----------------
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, -0.5);

	glColor3f(0, 1, 0);
	glVertex2f(0.5, -0.5);

	glColor3f(0, 0, 1);
	glVertex2f(0.5, 0.5);

	glColor3f(1, 1, 1);
	glVertex2f(-0.5, 0.5);

	glColor3f(1, 1, 0);
	glVertex2f(-0.7, 0.2);

	glColor3f(0, 0, 0);
	glVertex2f(-0.6, -0.3);
	glEnd();
	////----------------------------------------------

	////-----quads---------------------
 //   glBegin(GL_QUADS);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.5, -0.5);	//v1

	//glColor3f(0, 1, 0);
	//glVertex2f(0.5, -0.5);	//v2

	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.5);		//v3

	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.5);	//v4

	//glColor3f(1, 1, 0);
	//glVertex2f(-0.7, 0.2);	//v5

	//glColor3f(0, 0, 0);
	//glVertex2f(-0.6, -0.3);	//v6

	//glVertex2f(-0.7, -0.4);	//v7
	//glVertex2f(-0.9, 0.4);	//v8
	//glEnd();
	////---------------------------------------------------------------

	////---------order matters------------------
	//glBegin(GL_QUAD_STRIP);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.5, -0.5);	//v1

	//glColor3f(0, 1, 0);
	//glVertex2f(0.5, -0.5);	//v2

	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.5);		//v3

	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.5);	//v4

	//glColor3f(1, 1, 0);
	//glVertex2f(-0.7, 0.2);	//v5

	//glColor3f(0, 0, 0);
	//glVertex2f(-0.6, -0.3);	//v6

	//glVertex2f(-0.7, -0.4);	//v7
	//glVertex2f(-0.9, 0.4);	//v8
	//glEnd();
	////----------------------------------------------------------

	////-------order matters, depending on what you want------------------
	//glBegin(GL_QUAD_STRIP);
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.5, -0.5);		//v1

	//glColor3f(0, 1, 0);
	//glVertex2f(0.5, -0.5);		//v2

	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.5);		//v4

	//glColor3f(0, 0, 1);
	//glVertex2f(0.5, 0.5);		//v3

	//glColor3f(1, 1, 0);
	//glVertex2f(-0.7, 0.2);		//v5

	//glColor3f(0, 0, 0);
	//glVertex2f(-0.6, -0.3);		//v6

	//glVertex2f(-0.9, 0.4);		//v8
	//glVertex2f(-0.7, -0.4);		//v7
	//glEnd();
	////----------------------------------------------------------
	glFlush();
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glColor3f(0, 1, 1);

	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

						//---the following segment could be included in the reshape callback-----
	float ratio = ww * 1.0 / (wh*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	// default (-1, 1, -1, 1)
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, ww, wh);
	//-------------------------------------
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(800, 200); // defualt at (0, 0)
	glutCreateWindow("Primitive Types");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	// envoked when the window is reshaped or moved; also envoked when the window is displayed at the first time

	glutMainLoop();

	return 0;
}