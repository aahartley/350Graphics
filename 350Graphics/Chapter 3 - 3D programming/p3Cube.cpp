#include <GL/glut.h>

GLsizei ww = 512, wh = 512;

GLfloat vertices[][3] = {{-1, -1, 1}, {-1, 1, 1}, {1, 1, 1}, {1, -1, 1},
{-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1}};

GLfloat colors[8][3]= {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}, {0, 0, 1},
{1, 0, 1}, {1, 1, 1}, {0, 1, 1}};

void quad(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);

		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);

		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);

		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorCube()
{
	quad(0, 3, 2, 1);
	quad(2, 3, 7, 6);
	quad(0, 4, 7, 3);
	quad(1, 2, 6, 5);
	quad(4, 5, 6, 7);
	quad(0, 1, 5, 4);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);

	//glShadeModel(GL_FLAT);
	//glShadeModel(GL_SMOOTH);   // default

	colorCube();
	glFlush();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-2.0*w/h, 2.0*w/h, -2, 2, -20, 20);
	else
		glOrtho(-2, 2, -2*h/w, 2*h/w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = w;
}

void init()
{
	glClearColor(0.8, 0.8, 0.8, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}


void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("cube");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
}