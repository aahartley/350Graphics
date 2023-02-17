#include <GL/glut.h>  

GLsizei ww = 512;
GLsizei hh = 512;
GLfloat left = -2.0;
GLfloat right = 2.0;
GLfloat bottom = -2.0;
GLfloat top = 2.0;

void displayLines()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//--------draw the axis for reference-----------------
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINES);			
		glVertex2f(left, 0);	// the horizontal axis
		glVertex2f(right, 0);

		glVertex2f(0, bottom);	// the vertical axis
		glVertex2f(0, top);
	glEnd();
	//------------------------------------------------------------------

	glEnable(GL_LINE_STIPPLE);	// feature enabled
	glLineStipple(2, 0xfff0);	// stretched pattern; bits are used starting with the lowest bit

	glLineWidth(4);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2f(left, bottom/16);
		glVertex2f(right, bottom/16);

		glColor3f(0, 1, 0);
		glVertex2f(right, top / 16);
		glVertex2f(left, top / 16);

		glColor3f(0, 0, 1);
		glVertex2f(left/16, bottom);
		glVertex2f(left/16, top);

		glColor3f(1, 1, 0);
		glVertex2f(right / 16, top);
		glVertex2f(right / 16, bottom);

		glColor3f(1, 0, 1);
		glVertex2f(left, bottom);
		glVertex2f(right, top);

		glColor3f(0, 1, 1);
		glVertex2f(left, top);
		glVertex2f(right, bottom);
	glEnd();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glRectf(-1, -1, 1, 1);

//	glDisable(GL_LINE_STIPPLE);
	glFlush();
}

void displayLineStrip()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLineStipple(2, 0x00ff);
	glEnable(GL_LINE_STIPPLE);

	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
		glColor3f(1, 0, 0);
		glVertex2f(-1.3, -1.1);

		glColor3f(0, 1, 0);
		glVertex2f(1.2, -1.0);

		glColor3f(0, 0, 1);
		glVertex2f(1.5, 0.9);

		glColor3f(0, 1, 1);
		glVertex2f(0.3, 1.4);

		glColor3f(1, 0, 1);
		glVertex2f(-1.7, 1.1);

		glColor3f(1, 1, 0);
		glVertex2f(-1.9, 0.5);

		glColor3f(0, 0, 0);
		glVertex2f(0.0, 0.0);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
	glFlush();
}

void displayLineLoop()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLineStipple(4, 0x0c0f);
	glEnable(GL_LINE_STIPPLE);

	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glColor3f(1, 0, 0);
		glVertex2f(-1.3, -1.1);

		glColor3f(0, 1, 0);
		glVertex2f(1.2, -1.0);

		glColor3f(0, 0, 1);
		glVertex2f(1.5, 0.9);

		glColor3f(0, 1, 1);
		glVertex2f(0.3, 1.4);

		glColor3f(1, 0, 1);
		glVertex2f(-1.7, 1.1);

		glColor3f(0, 0, 0);
		glVertex2f(-1.9, 0.5);

		glColor3f(0, 0, 0);
		glVertex2f(0.0, 0.0);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
	glFlush();
}

void reshape(GLsizei w, GLsizei h)
{
	GLfloat ratio = (float)h / (float)w;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (ratio <= 1.0)
		gluOrtho2D(left / ratio, right / ratio, bottom, top);
	else
		gluOrtho2D(left, right, bottom*ratio, top*ratio);

	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	hh = h;
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, hh);
	glutInitWindowPosition(800, 200);
	glutCreateWindow("stippled lines");

	glutDisplayFunc(displayLines);
	//glutDisplayFunc(displayLineStrip);
	//glutDisplayFunc(displayLineLoop);

	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
}



